#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/GameObject.h"
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

bool PhysicsComponent::IsColliding(std::shared_ptr<PhysicsComponent> otherComponent)
{
	return false;
}

void PhysicsComponent::Move()
{
	if (mIsStatic) return;
	if (mOwner.expired()) return; 

	std::shared_ptr<GameObject> owner = mOwner.lock();
	if (std::shared_ptr<TransformComponent> transformComponent = owner->FindComponentOfType<TransformComponent>()) {
		exVector2 currentPos = transformComponent->GetPosition();

		if (mHasGravity && !mIsGrounded) {
			mVelocity.y += mGravityConstant;
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

bool PhysicsComponent::IsGrounded() const
{
	return mIsGrounded;
}

void PhysicsComponent::SetIsGrounded(const bool& newIsGrounded)
{
	mIsGrounded = newIsGrounded;
}

void PhysicsComponent::InitializeComponent()
{
	PHYSICS_ENGINE.AddPhysicsComponent(shared_from_this());
}
