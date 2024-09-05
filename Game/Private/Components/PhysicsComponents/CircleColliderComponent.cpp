#include "Game/Public/Components/PhysicsComponents/CircleColliderComponent.h"
#include "Game/Public/GameObject.h"
#include <cmath>
#include <algorithm>

CircleColliderComponent::CircleColliderComponent(std::shared_ptr<GameObject> inOwner) : PhysicsComponent(inOwner)
{
	mRadius = 15.0f;
}

CircleColliderComponent::CircleColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic) : PhysicsComponent(inOwner, inIsStatic)
{
	mRadius = 15.0f;
}

CircleColliderComponent::CircleColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, float inRadius) : PhysicsComponent(inOwner, inIsStatic)
{
	mRadius = inRadius;
}

CircleColliderComponent::CircleColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, float inRadius, bool inHasGravity, exVector2 inVelocity) : PhysicsComponent(inOwner, inIsStatic, inHasGravity, inVelocity)
{
	mRadius = inRadius;
}

void CircleColliderComponent::InitializeComponent()
{
	PhysicsComponent::InitializeComponent();
}

bool CircleColliderComponent::IsColliding(std::shared_ptr<PhysicsComponent> otherComponent)
{
	static int printYOffset = 0;
	// check if other component has a circle collider 
	if (std::shared_ptr<CircleColliderComponent> otherCircleCollider = std::dynamic_pointer_cast<CircleColliderComponent>(otherComponent)) {
		if (mOwner.expired() || otherCircleCollider->GetOwner().expired()) {
			return false;

		}
		// get the center point of the game object
		std::shared_ptr<TransformComponent> ownerTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>();
		std::shared_ptr<TransformComponent> otherTransformComp = otherCircleCollider->mOwner.lock()->FindComponentOfType<TransformComponent>();

		if (ownerTransformComp && otherTransformComp) { //if both objects are valid
			// Print out debugging information without overlap by adjusting the Y position
			auto ownerTransform = ownerTransformComp->GetPosition();
			auto otherTransform = otherTransformComp->GetPosition();
			exVector2 vectorBetweenCenterPts = ownerTransform - otherTransform;
			// square root of x^2 + y^2 to get the distance between objects
			float distanceBetweenCircle = std::sqrt((vectorBetweenCenterPts.x * vectorBetweenCenterPts.x) + (vectorBetweenCenterPts.y * vectorBetweenCenterPts.y));
			// Print out debugging information without overlap by adjusting the Y position

			if (distanceBetweenCircle <= (mRadius + otherCircleCollider->mRadius)) {
				ENGINE_PRINT("Circle Collided with another Circle" + std::to_string(IsColliding(otherComponent)), 10.0f, 100.0f);
				return true;
			}
		}
	}

	if (std::shared_ptr<BoxColliderComponent> otherBoxCollider = std::dynamic_pointer_cast<BoxColliderComponent>(otherComponent)) {
		if (mOwner.expired() || otherBoxCollider->GetOwner().expired()) {
			return false;
		}

		std::shared_ptr<TransformComponent> ownerTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>();
		std::shared_ptr<TransformComponent> otherTransformComp = otherBoxCollider->GetOwner().lock()->FindComponentOfType<TransformComponent>();

		if (ownerTransformComp && otherTransformComp) {
			// Get the center point of the circle and the box
			exVector2 circleCenter = ownerTransformComp->GetPosition();
			exVector2 boxCenter = otherTransformComp->GetPosition();
			// mRadius is already accessible
			exVector2 boxPoint1 = otherBoxCollider->GetPoint1();
			exVector2 boxPoint2 = otherBoxCollider->GetPoint2();
			// Calculate box dimensions
			float boxX = boxPoint1.x;   // Top-left x-coordinate of the box
			float boxY = boxPoint1.y;   // Top-left y-coordinate of the box
			float boxWidth = std::abs(boxPoint2.x - boxPoint1.x);   // Width of the box
			float boxHeight = std::abs(boxPoint2.y - boxPoint1.y);  // Height of the box

			// Variables to hold the closest point on the box to the circle's center
			float testX = circleCenter.x;
			float testY = circleCenter.y;

			// Find the closest point on the box to the circle's center
			if (circleCenter.x < boxX) testX = boxX;  // Closest to the left edge
			else if (circleCenter.x > boxX + boxWidth) testX = boxX + boxWidth;  // Closest to the right edge

			if (circleCenter.y < boxY) testY = boxY;  // Closest to the top edge
			else if (circleCenter.y > boxY + boxHeight) testY = boxY + boxHeight;  // Closest to the bottom edge

			// Calculate the distance between the circle's center and the closest point
			float distX = circleCenter.x - testX;
			float distY = circleCenter.y - testY;
			float distance = std::sqrt((distX * distX) + (distY * distY));

			// Check if the distance is less than or equal to the circle's radius
			if (distance <= mRadius) {
				// Circle collided with the box!
				ENGINE_PRINT("Circle Collided with Box", 40.0f, 50.0f);
				return true;
			}
		}
	}
	return false;
}


