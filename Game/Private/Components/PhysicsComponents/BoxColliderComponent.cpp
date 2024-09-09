#include "Game/Public/Components/PhysicsComponents/BoxColliderComponent.h"
#include "Game/Public/GameObject.h"
#include <cmath>

BoxColliderComponent::BoxColliderComponent(std::shared_ptr<GameObject> inOwner) : PhysicsComponent(inOwner)
{
	mPoint1 = exVector2{ 0.0f, 0.0f };
	mPoint2 = exVector2{ 10.0f, 10.0f };
	mIsStatic = true;
	mHasGravity = true; 
	mVelocity = exVector2{ 0.0f, 0.0f };
}

BoxColliderComponent::BoxColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2) : PhysicsComponent(inOwner, inIsStatic)
{
	mPoint1 = inPoint1;
	mPoint2 = inPoint2;
}

BoxColliderComponent::BoxColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2, bool inHasGravity) : PhysicsComponent(inOwner, inIsStatic, inHasGravity)
{
	// Adjust mPoint1 and mPoint2 based on the owning object's position
	std::shared_ptr<TransformComponent> transformComp = inOwner->FindComponentOfType<TransformComponent>();
	if (transformComp) {
		exVector2 spawnPosition = transformComp->GetPosition();
		mPoint1 = inPoint1 + spawnPosition;
		mPoint2 = inPoint2 + spawnPosition;
		AccessEngine()->DrawLineBox(mPoint1, mPoint2, exColor{ 0,255,0,255 }, 1);
	}
}

BoxColliderComponent::BoxColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2, bool inHasGravity, exVector2 inVelocity) : PhysicsComponent(inOwner, inIsStatic, inHasGravity, inVelocity)
{
	mPoint1 = inPoint1;
	mPoint2 = inPoint2;
}

exVector2 BoxColliderComponent::GetSize() const
{
	// Calculate width and height by subtracting the coordinates of the points
	return exVector2 {
		std::abs(mPoint2.x - mPoint1.x),  // Width
		std::abs(mPoint2.y - mPoint1.y)   // Height
	};
}

exVector2 BoxColliderComponent::GetPoint1() const
{
	return mPoint1;
}

exVector2 BoxColliderComponent::GetPoint2() const
{
	return mPoint2;
}

void BoxColliderComponent::InitializeComponent()
{
	PhysicsComponent::InitializeComponent();
	mBoxColliderRender = mOwner.lock()->AddComponentOfType<BoxLineRender>(mPoint1, mPoint2, exColor{ 0, 255, 0, 255 }, 0);
}

CollisionResult BoxColliderComponent::CheckCollision(std::shared_ptr<PhysicsComponent> otherComponent, CollisionResult inResultToReturn)
{
	return inResultToReturn;
}
