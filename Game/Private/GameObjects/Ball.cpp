#include "Game/Public/GameObjects/Ball.h"
#include "Game/Public/GameObjects/Cube.h"
#include "Game/Public/GameObjects/PowerUpOne.h"

Ball::Ball() : GameObject()
{
	mColliderRadius = 100.0f;
	mDirection = exVector2{ 1.0f, 1.0f };
	mColor = exColor{ 255,0,0,255 };
	mSpawnLocation = exVector2{ 400.0f,400.0f };
	mIsGrounded = false; 
	mHasGravity = true;
	mCollisionPoint = { 0,0 };
	mOriginalPosition = { 0,0 };
	mTargetPosition = { 0,0 };
}

Ball::~Ball()
{
}

Ball::Ball(exVector2 inDirection, exVector2 inSpawnLocation, float inColliderRadius, exColor inColor)
{
	mColliderRadius = inColliderRadius;
	mDirection = inDirection;
	mColor = inColor;
	mSpawnLocation = inSpawnLocation;
	mIsGrounded = false;
	mHasGravity = true;
	mCollisionPoint = { 0,0 };
	mOriginalPosition = { 0,0 };
	mTargetPosition = { 0,0 };
}

Ball::Ball(exVector2 inDirection, exVector2 inSpawnLocation, float inColliderRadius, exColor inColor, bool inHasGravity)
{
	mColliderRadius = inColliderRadius;
	mDirection = inDirection;
	mColor = inColor;
	mSpawnLocation = inSpawnLocation;
	mHasGravity = inHasGravity;
	mIsGrounded = false;
	mHasGravity = true;
	mCollisionPoint = { 0,0 };
	mOriginalPosition = { 0,0 };
	mTargetPosition = { 0,0 };
}

void Ball::Tick(float deltaTime)
{
	GameObject::Tick(deltaTime);
	exVector2 currentPosition = mTransform->GetPosition();

	// handles jumping animation
	if (mIsJumping) {
		// Apply the jump force as long as the ball hasn't reached the target height
		if (currentPosition.y > mTargetPosition.y) {
			ENGINE_PRINT("Jumping", 300, 40);
		}
		else {
			// Stop the jump when the target height is reached
			ENGINE_PRINT("Falling", 300, 60);
			mIsJumping = false;
			mIsFalling = true;
			mPhysicsComponent->SetVelocity(exVector2{ mPhysicsComponent->GetVelocity().x, 0 });
		}
	}

	// Check if the ball fell off the screen
	if (currentPosition.y >= 600.0f)
	{
		mPhysicsComponent->SetVelocity(exVector2{ 0, 0 });
		ENGINE_PRINT("You died", 250, 200);
		mTransform->SetPosition({ currentPosition.x, 600 });
	}
}

void Ball::BeginPlay()
{
	GameObject::BeginPlay();
	mTransform = AddComponentOfType<TransformComponent>(mSpawnLocation);
	mCircleRenderComponent = AddComponentOfType<CircleRenderComponent>(mColliderRadius, mColor, 0);
	// constructor parameters taken: bool inIsStatic, float inRadius, bool inHasGravity, exVector2 inVelocity
	mPhysicsComponent = AddComponentOfType<CircleColliderComponent>(false, mColliderRadius, mHasGravity, mDirection);
	mPhysicsComponent->RegisterListener(std::bind(&Ball::OnCollisionDetected, this, std::placeholders::_1, std::placeholders::_2));
}

bool Ball::IsGrounded() const
{
	return mIsGrounded;
}

void Ball::SetGrounded(const bool& inIsGrounded)
{
	mIsGrounded = inIsGrounded;
}

void Ball::CheckGrounded()
{
	
}

float Ball::GetJumpHeight() const
{
	return mJumpHeight;
}

void Ball::SetJumpHeight(const float& inNewJumpHeight)
{
	mJumpHeight = inNewJumpHeight;
}

bool Ball::IsJumping() const
{
	return mIsJumping;
}

void Ball::OnCollisionDetected(CollisionResult inResults, std::weak_ptr<GameObject> otherObjectHit)
{
	if (!otherObjectHit.expired()) {
		if (std::shared_ptr<PowerUpOne> player = std::dynamic_pointer_cast<PowerUpOne>(otherObjectHit.lock())) {
			mPowerUpLvl += 1;
			mTransform->SetScale({ 2,2 });
		}

		if (std::shared_ptr<Ball> player = std::dynamic_pointer_cast<Ball>(otherObjectHit.lock())) {
			ENGINE_PRINT("Collided with ball", 10, 40);
		}
		if (std::shared_ptr<Cube> enemy = std::dynamic_pointer_cast<Cube>(otherObjectHit.lock())) {
			// Handle collisions based on the side hit
			switch (inResults.mCollisionSide) {
			case CollisionSide::Top:
				if (!mIsGrounded && !mIsJumping) {
					// Check if the ball is still supported enough by the box (not past its center)
					if (inResults.mHitPoint.x <= mTransform->GetPosition().x + mColliderRadius * 0.5f &&
						inResults.mHitPoint.x >= mTransform->GetPosition().x - mColliderRadius * 0.5f) {
						mTransform->SetPosition(inResults.mHitPoint + exVector2{ 0, -mColliderRadius }); // Place ball above cube
						mPhysicsComponent->SetVelocity(exVector2{ mPhysicsComponent->GetVelocity().x, 0 });
						ENGINE_PRINT("Ball is grounded on top of the box", 10.0f, 40.0f);
						mIsGrounded = true;
						mIsFalling = false;
					}
					else {
						// The ball is moving off the edge of the box, so it's no longer grounded
						mIsGrounded = false;
					}
				}
				break;

			case CollisionSide::Bottom:
				if (!mIsGrounded && mIsJumping) {
					mTransform->SetPosition(inResults.mHitPoint + exVector2{ 0, + mColliderRadius }); // Place ball below cube
					mPhysicsComponent->SetVelocity(exVector2{ mPhysicsComponent->GetVelocity().x, 0 });
					ENGINE_PRINT("Ball hit the bottom of a box", 10.0f, 40.0f);
					mIsFalling = true;
					mIsJumping = false;
					
				}
				break;

			case CollisionSide::Left:
				if (mPhysicsComponent->GetVelocity().x > 0) {
					if (inResults.mHitPoint.x >= mTransform->GetPosition().x) {
						mIsGrounded = false; 
					}
					mTransform->SetPosition(inResults.mHitPoint + exVector2{ -mColliderRadius, 0 }); // Place ball on the  right cube
					mPhysicsComponent->SetVelocity(exVector2{ 0, mPhysicsComponent->GetVelocity().y });
					ENGINE_PRINT("Ball hit left side of the box", 10.0f, 40.0f);
				}
				break;
			case CollisionSide::Right:
				if (mPhysicsComponent->GetVelocity().x < 0) {
					mTransform->SetPosition(inResults.mHitPoint + exVector2{ +mColliderRadius, 0 }); // Place ball on the left cube
					mPhysicsComponent->SetVelocity(exVector2{ 0, mPhysicsComponent->GetVelocity().y });
					ENGINE_PRINT("Ball hit right side of the box", 10.0f, 40.0f);
				}
				break;

			case CollisionSide::None:
				mIsGrounded = false;
				break;
			
			default:
				break;
			}
		}
	}
}

exVector2 Ball::GetCollisionPoint() const
{
	return mCollisionPoint;
}

void Ball::Jump()
{
	if (!mIsGrounded || mIsJumping) return;  // Prevent jumping if already jumping or not grounded

	// Store the original position when the jump starts
	exVector2 currentPosition = mTransform->GetPosition();
	mOriginalPosition = currentPosition;

	// Calculate the target height (jump height)
	mTargetPosition = currentPosition;
	mTargetPosition.y -= mJumpHeight;  // Negative to move upward in 2D coordinate systems

	// Apply the initial jump force to kick off the jump
	mPhysicsComponent->SetVelocity(exVector2{ mPhysicsComponent->GetVelocity().x, -mJumpForce }); // Smaller jump force applied over time
	mIsJumping = true;
	mIsGrounded = false;
	mIsFalling = false;

}

void Ball::MoveDirection(float directionX)
{
	// Add to the current x velocity instead of setting it directly
	exVector2 currentVelocity = mPhysicsComponent->GetVelocity();
	currentVelocity.x = directionX;  // Add horizontal movement
	mPhysicsComponent->SetVelocity(currentVelocity);  // Set the new velocity
}
