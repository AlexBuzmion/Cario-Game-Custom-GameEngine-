#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/GameObject.h"
#include "Game/Public/GameObjects/Ball.h"
#include "Game/Public/Singletons/PhysicsEngine.h"
#include <cassert>


PhysicsComponent::~PhysicsComponent()
{
}

PhysicsComponent::PhysicsComponent(std::shared_ptr<GameObject> mOwner) : Component(mOwner)
{
	mIsStatic = true; 
	mHasGravity = false; 
	mVelocity = exVector2(0.0f, 0.0f);
}

PhysicsComponent::PhysicsComponent(std::shared_ptr<GameObject> mOwner, bool inIsStatic) : Component(mOwner)
{
	mIsStatic = inIsStatic;
	mHasGravity = false;
	mVelocity = exVector2(0.0f, 0.0f);
}

PhysicsComponent::PhysicsComponent(std::shared_ptr<GameObject> mOwner, bool inIsStatic, bool inHasGravity) : Component(mOwner)
{
	mIsStatic = inIsStatic;
	mHasGravity = inHasGravity;
	mVelocity = exVector2(0.0f, 0.0f);
}

PhysicsComponent::PhysicsComponent(std::shared_ptr<GameObject> mOwner, bool inIsStatic, bool inHasGravity, exVector2 inVelocity) : Component(mOwner)
{
	mIsStatic = inIsStatic;
	mHasGravity = inHasGravity;
	mVelocity = inVelocity;
}

void PhysicsComponent::RegisterListener(OnCollisionEvent eventToAdd)
{
	mCollisionEvents.push_back(eventToAdd);
}

void PhysicsComponent::UnregisterListener(OnCollisionEvent eventToRemove)
{
	auto it = std::find_if(mCollisionEvents.begin(), mCollisionEvents.end(),
		[&](const OnCollisionEvent& event) {
			// Compare event targets, assuming eventToRemove is the same function as registered
			return event.target<void(CollisionResult, std::weak_ptr<GameObject>)>() ==
				eventToRemove.target<void(CollisionResult, std::weak_ptr<GameObject>)>();
		});

	if (it != mCollisionEvents.end()) {
		mCollisionEvents.erase(it);  // Remove the listener
	}
}

bool PhysicsComponent::GetIsGrounded()
{
	return false;
}


CollisionResult PhysicsComponent::CheckCollision(std::shared_ptr<PhysicsComponent> otherComponent)
{
	return CollisionResult();
}

void PhysicsComponent::Move(float deltaTime)
{
	if (mIsStatic) return;
	if (mOwner.expired()) return; 

	std::shared_ptr<GameObject> owner = mOwner.lock();
	
	if (std::shared_ptr<TransformComponent> transformComponent = owner->FindComponentOfType<TransformComponent>()) {
		exVector2 currentPos = transformComponent->GetPosition(); 
		std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(owner);
		if (!ball) return;

		if (mHasGravity && !ball->IsJumping()) {
			mVelocity.y += mGravityConstant * deltaTime; // apply gravity over time
			ENGINE_PRINT(std::to_string(mVelocity.y), 10, 80);
		}
		if (ball->IsGrounded()) {
			mVelocity.y = 0;
		}
		exVector2 newPosition = currentPos + mVelocity;
		transformComponent->SetPosition(newPosition);
	}
}

exVector2 PhysicsComponent::GetVelocity() const
{
	return mVelocity;
}

void PhysicsComponent::SetVelocity(const exVector2& newVelocity)
{
	mVelocity = newVelocity;
}

void PhysicsComponent::RemoveFromComponentList()
{
	PHYSICS_ENGINE.RemovePhysicsComponent(shared_from_this());
}

void PhysicsComponent::InitializeComponent()
{
	PHYSICS_ENGINE.AddPhysicsComponent(shared_from_this());
}

