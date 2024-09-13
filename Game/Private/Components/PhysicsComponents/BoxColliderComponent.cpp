#include "Game/Public/Components/PhysicsComponents/BoxColliderComponent.h"
#include "Game/Public/GameObject.h"
#include <cmath>

BoxColliderComponent::BoxColliderComponent(std::shared_ptr<GameObject> inOwner) : PhysicsComponent(inOwner)
{
	mPoint1 = exVector2{ 0.0f, 0.0f };
	mPoint2 = exVector2{ 10.0f, 10.0f };
	mIsStatic = false;
	mHasGravity = true; 
	mVelocity = exVector2{ 0.0f, 0.0f };
	mBoxWidth = std::abs(mPoint1.x - mPoint1.x);
	mBoxHeight = std::abs(mPoint2.y - mPoint2.y);
}

BoxColliderComponent::BoxColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2) : PhysicsComponent(inOwner, inIsStatic)
{
	mPoint1 = inPoint1;
	mPoint2 = inPoint2;
	mBoxWidth = std::abs(inPoint1.x - inPoint1.x);
	mBoxHeight = std::abs(inPoint1.y - inPoint1.y);
}

BoxColliderComponent::BoxColliderComponent(std::shared_ptr<GameObject> inOwner, exVector2 inSpawnLoc, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2, bool inHasGravity) : PhysicsComponent(inOwner, inIsStatic, inHasGravity)
{
	// Adjust mPoint1 and mPoint2 based on the owning object's position
	std::shared_ptr<TransformComponent> transformComp = inOwner->FindComponentOfType<TransformComponent>();
	if (transformComp) {
		mPoint1 = inPoint1;
		mPoint2 = inPoint2;
		// Calculate half-width and half-height of the box
		exVector2 halfDimensions = (mPoint2 - mPoint1) * 0.5f;

		// Calculate the top-left and bottom-right corner relative to the center (spawnPoint)
		mPoint1 = inSpawnLoc - halfDimensions;
		mPoint2 = inSpawnLoc + halfDimensions;
		AccessEngine()->DrawLineBox(mPoint1, mPoint2, exColor{ 0,255,0,255 }, 1);
	}
	mBoxWidth = std::abs(inPoint2.x - inPoint1.x);
	mBoxHeight = std::abs(inPoint2.y - inPoint1.y);
}

BoxColliderComponent::BoxColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2, bool inHasGravity, exVector2 inVelocity) : PhysicsComponent(inOwner, inIsStatic, inHasGravity, inVelocity)
{
	mPoint1 = inPoint1;
	mPoint2 = inPoint2;
	mBoxWidth = std::abs(inPoint1.x - inPoint1.x);
	mBoxHeight = std::abs(inPoint1.y - inPoint1.y);
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

float BoxColliderComponent::GetBoxWidth() const
{
	return mBoxWidth;
}

float BoxColliderComponent::GetBoxHeight() const
{
	return mBoxHeight;
}

void BoxColliderComponent::DisableColliderBoxRender()
{
	mBoxColliderRender->SetColor({ 0,0,0,0 });
}

void BoxColliderComponent::UpdateColliderBounds()
{
	std::shared_ptr<TransformComponent> transformComp = mOwner.lock()->FindComponentOfType<TransformComponent>();
	if (transformComp) {
		exVector2 currentPos = transformComp->GetPosition();

		// Calculate half-width and half-height of the box
		exVector2 halfDimensions = (mPoint2 - mPoint1) * 0.5f;

		// Update mPoint1 and mPoint2 to reflect the new position
		mPoint1 = currentPos - halfDimensions;
		mPoint2 = currentPos + halfDimensions;
	}
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
