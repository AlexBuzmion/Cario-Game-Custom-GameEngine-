#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/GameObject.h"
#include "Game/Public/GameObjects/Ball.h"
#include "Game/Public/GameObjects/PowerUpOne.h"
#include "Game/Public/Singletons/PhysicsEngine.h"
#include <cassert>


PhysicsComponent::~PhysicsComponent()
{
}

PhysicsComponent::PhysicsComponent(std::shared_ptr<GameObject> mOwner) : Component(mOwner)
{
	mIsStatic = false; 
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

CollisionResult PhysicsComponent::CheckCollision(std::shared_ptr<PhysicsComponent> otherComponent, float deltaTime)
{
	return CollisionResult();
}

void PhysicsComponent::Move(float deltaTime)
{
	if (mIsStatic && !mHasGravity) return;
	if (mOwner.expired()) return; 

	std::shared_ptr<GameObject> owner = mOwner.lock();
	
	std::shared_ptr<TransformComponent> transformComponent = owner->FindComponentOfType<TransformComponent>(); 
	if (!transformComponent) return; 

	exVector2 currentPos = transformComponent->GetPosition(); 
	
	if (mHasGravity && !mOwner.lock()->GetGrounded()) {
		mVelocity.y += mGravityConstant * deltaTime;
	}

	// Calculate the new position and movement delta
	exVector2 movementDelta;
	exVector2 newPosition = currentPos + mVelocity;
	movementDelta = newPosition - currentPos;  // Calculate how much the object moved

	// Apply the new position
	transformComponent->SetPosition(newPosition);

	// Update the collider bounds (important!)
	if (std::shared_ptr<BoxColliderComponent> boxCollider = std::dynamic_pointer_cast<BoxColliderComponent>(owner->FindComponentOfType<BoxColliderComponent>())) {
		boxCollider->UpdateColliderBounds();
	}

	// Broadcast the movement delta to listeners
	transformComponent->BroadcastMovement(movementDelta);  // Update this function to take movementDelta
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

