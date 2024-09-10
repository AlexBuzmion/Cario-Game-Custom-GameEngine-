#include "Game/Public/Components/PhysicsComponents/CircleColliderComponent.h"
#include "Game/Public/Components/PhysicsComponents/BoxColliderComponent.h"
#include "Game/Public/GameObject.h"
#include <cmath>
#include <algorithm>
#include "Game/Public/GameObjects/Ball.h"
#include "Game/Public/GameObjects/PowerUpOne.h"

CircleColliderComponent::CircleColliderComponent(std::shared_ptr<GameObject> inOwner) : PhysicsComponent(inOwner)
{
	mRadius = 15.0f;
	mIsGrounded = false;
}

CircleColliderComponent::CircleColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic) : PhysicsComponent(inOwner, inIsStatic)
{
	mRadius = 15.0f;
	mIsGrounded = false;
}

CircleColliderComponent::CircleColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, float inRadius) : PhysicsComponent(inOwner, inIsStatic)
{
	mRadius = inRadius;
	mIsGrounded = false;
}

CircleColliderComponent::CircleColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, float inRadius, bool inHasGravity, exVector2 inVelocity) : PhysicsComponent(inOwner, inIsStatic, inHasGravity, inVelocity)
{
	mRadius = inRadius;
	mIsGrounded = false;
}

bool CircleColliderComponent::GetIsGrounded()
{
	return mIsGrounded;
}

void CircleColliderComponent::InitializeComponent()
{
	PhysicsComponent::InitializeComponent();

	// Automatically add a CircleRenderComponent to visualize the collider
	mCircleColliderRender = mOwner.lock()->AddComponentOfType<CircleLineRender>((mRadius+.2f), exColor{ 0, 255, 0, 255 }, 0);
}



CollisionResult CircleColliderComponent::CheckCollision(std::shared_ptr<PhysicsComponent> otherComponent)
{
	// create the result to pass to the collision check and receive back
	CollisionResult result; 
	result.mCollisionSide = CollisionSide::None;
	result.mHitPoint = exVector2{ 0,0 }; 

	//// Check if the other component is a CircleCollider
	if (auto otherCircle = std::dynamic_pointer_cast<CircleColliderComponent>(otherComponent)) {
		return CircleCollisionCheck(otherCircle, result);  // Perform circle-circle collision check
	}

	// Check if the other component is a BoxCollider
	if (auto otherBox = std::dynamic_pointer_cast<BoxColliderComponent>(otherComponent)) {
		return BoxCollisionCheck(otherBox, result);  // Perform circle-box collision check
	}

	return result;  // No collision

}

CollisionResult CircleColliderComponent::CircleCollisionCheck(std::shared_ptr<PhysicsComponent> otherCircle, CollisionResult inResultToReturn) const
{
	if (mOwner.expired() || otherCircle->GetOwner().expired()) return inResultToReturn;

	auto ownerTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>();
	auto otherTransformComp = otherCircle->GetOwner().lock()->FindComponentOfType<TransformComponent>();

	if (!ownerTransformComp && otherTransformComp) return inResultToReturn;

	//Attempt to get the circle collider and validate; tried ! and it doesnt work
	std::shared_ptr<CircleColliderComponent> otherCircleCollider = std::dynamic_pointer_cast<CircleColliderComponent>(otherCircle);
	
	exVector2 vectorBetweenCenters = ownerTransformComp->GetPosition() - otherTransformComp->GetPosition();

	float distanceBetweenCircles = std::sqrt(vectorBetweenCenters.x * vectorBetweenCenters.x + vectorBetweenCenters.y * vectorBetweenCenters.y);

	if (distanceBetweenCircles <= (mRadius + otherCircleCollider->mRadius)) {
		inResultToReturn.mHitPoint = (ownerTransformComp->GetPosition() + otherTransformComp->GetPosition()) * 0.5f;  // Midpoint of the two circles
		inResultToReturn.mCollisionSide = CollisionSide::Top; // top placeholder to bypass sending the collision event
		return inResultToReturn;  // For simplicity, assuming a top collision for now
	}

	return inResultToReturn;
}

CollisionResult CircleColliderComponent::BoxCollisionCheck(std::shared_ptr<PhysicsComponent> otherBox, CollisionResult inResultToReturn) const
{
	
	auto ownerTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>();
    auto boxTransformComp = otherBox->GetOwner().lock()->FindComponentOfType<TransformComponent>();

    if (ownerTransformComp && boxTransformComp) {
		//Attempt to get the circle collider and validate;
		std::shared_ptr<BoxColliderComponent> otherBoxCollider = std::dynamic_pointer_cast<BoxColliderComponent>(otherBox);
		if (!otherBoxCollider){
			return inResultToReturn;
		}
        auto circleCenter = ownerTransformComp->GetPosition();
        // Get box points
        auto boxPoint1 = otherBoxCollider->GetPoint1();
        auto boxPoint2 = otherBoxCollider->GetPoint2();

        // Box dimensions
        float boxX = boxPoint1.x;
        float boxY = boxPoint1.y;
        float boxWidth = std::abs(boxPoint2.x - boxPoint1.x);
        float boxHeight = std::abs(boxPoint2.y - boxPoint1.y);

        // Find the closest point on the box to the circle
        float testX = std::clamp(circleCenter.x, boxX, boxX + boxWidth);
        float testY = std::clamp(circleCenter.y, boxY, boxY + boxHeight);

		inResultToReturn.mHitPoint = exVector2{ testX, testY };
        float distX = circleCenter.x - testX;
        float distY = circleCenter.y - testY;
        float distance = std::sqrt((distX * distX) + (distY * distY));

        if (distance <= mRadius) {

			// Determine which side the collision occurred
			float distToTop = std::abs(circleCenter.y - boxY);
			float distToBottom = std::abs(circleCenter.y - (boxY + boxHeight));
			float distToLeft = std::abs(circleCenter.x - boxX);
			float distToRight = std::abs(circleCenter.x - (boxX + boxWidth));

			// Find the closest side
			float minDist = std::min({ distToTop, distToBottom, distToLeft, distToRight });

            // Determine collision side
			if (testY == boxY) {
				inResultToReturn.mCollisionSide = CollisionSide::Top;
			}
			if (testY == boxY + boxHeight) {
				inResultToReturn.mCollisionSide = CollisionSide::Bottom;
			}
			if (testX == boxX) {
				inResultToReturn.mCollisionSide = CollisionSide::Left;
			}
			if (testX == boxX + boxWidth) {
				inResultToReturn.mCollisionSide = CollisionSide::Right;
			}
        }
    }

    return inResultToReturn;
}


