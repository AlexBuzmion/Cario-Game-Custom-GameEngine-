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
	mPowerUpLvl = 0;
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
	mPowerUpLvl = 0;
}

void Ball::Tick(float deltaTime)
{
	GameObject::Tick(deltaTime);
	exVector2 currentPosition = mTransform->GetPosition();
	/*ENGINE_PRINT("Character Pos X: " + std::to_string(mTransform->GetPosition().x), 400, 40);
	ENGINE_PRINT("Character Pos Y: " + std::to_string(mTransform->GetPosition().y), 400, 60);*/
	// handles jumping animation
	if (mIsJumping) {
		// Apply the jump force as long as the ball hasn't reached the target height
		if (currentPosition.y > mTargetPosition.y) {
			ENGINE_PRINT("Jumping", 300, 40);
		}
		else {
			// Stop the jump when the target height is reached
			ENGINE_PRINT("Falling", 300, 70);
			mIsJumping = false;
			mIsFalling = true;
			mPhysicsComponent->SetVelocity(exVector2{ mPhysicsComponent->GetVelocity().x, 0 });
		}
	}
	else {
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

	// to revisit sprite renderer later 
	//mSpriteRender = AddComponentOfType<SpriteRenderComponent>("Resources/mario.bmp");
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
	
	mCollisionPoint = inResults.mHitPoint; // for debugging purposes
	if (!otherObjectHit.expired()) {
		std::shared_ptr<GameObject> hitObject = otherObjectHit.lock();
		//ENGINE_PRINT(typeid(*hitObject).name(), 200, 450); // Check what class this object actually is

		/*if (std::shared_ptr<Ball> player = std::dynamic_pointer_cast<Ball>(otherObjectHit.lock())) {
			ENGINE_PRINT("Collided with ball", 10, 40);
		}*/
		if (std::shared_ptr<Cube> enemy = std::dynamic_pointer_cast<Cube>(otherObjectHit.lock())) {
			// Handle collisions based on the side hit
			auto positivePos = mTransform->GetPosition().x + mColliderRadius * 0.5f;
			auto negativePos = mTransform->GetPosition().x - mColliderRadius * 0.5f;
			switch (inResults.mCollisionSide) {
			case CollisionSide::Top:
				/*if (!mIsJumping) {*/
					// Check if the ball is still supported enough by the box (not past its center)
				if (inResults.mHitPoint.x <= positivePos &&
					inResults.mHitPoint.x >= negativePos) {

					// Place ball above cube
					mTransform->SetPosition(inResults.mHitPoint + exVector2{ 0, -mColliderRadius });
					mPhysicsComponent->SetVelocity(exVector2{ mPhysicsComponent->GetVelocity().x, 0 });

					ENGINE_PRINT("Ball is grounded on top of the box", 10.0f, 40.0f);

					// Ball is grounded, reset grounded and falling flags
					mIsGrounded = true;
					mIsFalling = false;
				}
				else {
					// Predict the next position of the ball using its velocity
					exVector2 predictedPosition = mTransform->GetPosition() + (mPhysicsComponent->GetVelocity() * inResults.deltaTime);

					// Check if the predicted position will be off the edge of the box
					if (predictedPosition.x > inResults.mHitPoint.x + mColliderRadius * 0.5f ||
						predictedPosition.x < inResults.mHitPoint.x - mColliderRadius * 0.5f) {

						// The ball is predicted to move off the edge, so mark it as falling
						ENGINE_PRINT("Ball is falling off the edge of the box", 10.0f, 60.0f);
						mIsGrounded = false;
						mIsFalling = true;
					}
					else {
						// The ball is still close enough to the box edge, keep it grounded
						mIsGrounded = true;
						mIsFalling = false;
					}
				}
				//}
				break;

			case CollisionSide::Bottom:
				if (!mIsGrounded && mIsJumping) {
					mTransform->SetPosition(inResults.mHitPoint + exVector2{ 0, + mColliderRadius }); // Place ball below cube
					mPhysicsComponent->SetVelocity(exVector2{ mPhysicsComponent->GetVelocity().x, 1 });
					ENGINE_PRINT("Ball hit the bottom of a box", 10.0f, 60.0f);
					mIsFalling = true;
					mIsJumping = false;
					std::weak_ptr<GameObject> sendThis = mPhysicsComponent->GetOwner();
					enemy->Interact(mPowerUpLvl);
					
				}
				break;

			case CollisionSide::Left:
				if (mPhysicsComponent->GetVelocity().x > 0) {
					mTransform->SetPosition(inResults.mHitPoint + exVector2{ -mColliderRadius, 0 }); // Place ball on the  right cube
					mPhysicsComponent->SetVelocity(exVector2{ 0, mPhysicsComponent->GetVelocity().y });
					ENGINE_PRINT("Ball hit left side of the box", 10.0f, 80.0f);
				}
				break;
			case CollisionSide::Right:
				if (mPhysicsComponent->GetVelocity().x < 0) {
					mTransform->SetPosition(inResults.mHitPoint + exVector2{ +mColliderRadius, 0 }); // Place ball on the left cube
					mPhysicsComponent->SetVelocity(exVector2{ 0, mPhysicsComponent->GetVelocity().y });
					ENGINE_PRINT("Ball hit right side of the box", 10.0f, 100.0f);
				}
				break;
			
			case CollisionSide::None :
				mIsFalling = true;
				mIsGrounded = false; 
				break;

			default:
				
				break;
			}
			return;
		}

		if (std::shared_ptr<PowerUpOne> mushroom = std::dynamic_pointer_cast<PowerUpOne>(otherObjectHit.lock())) {
			if (inResults.mCollisionSide != CollisionSide::None) {
				mPowerUpLvl += 1;
				AnimateGrowing();
				return;
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
	mIsGrounded = false;
	mIsJumping = true;
	mIsFalling = false;

	// Store the original position when the jump starts
	exVector2 currentPosition = mTransform->GetPosition();
	mOriginalPosition = currentPosition;

	// Calculate the target height (jump height)
	mTargetPosition = currentPosition;
	mTargetPosition.y -= mJumpHeight;  // Negative to move upward in 2D coordinate systems

	// Apply the initial jump force to kick off the jump
	mPhysicsComponent->SetVelocity(exVector2{ mPhysicsComponent->GetVelocity().x, -mJumpForce }); // Smaller jump force applied over time

}

void Ball::Death()
{
}

void Ball::AnimateGrowing()
{
	mTransform->SetScale({ 2,2 });
	mColliderRadius = mColliderRadius * 2;
	FindComponentOfType<CircleColliderComponent>()->SetColliderRadius(mColliderRadius);
}

void Ball::MoveDirection(float directionX, float deltaTime)
{
	// Add to the current x velocity instead of setting it directly
	exVector2 currentVelocity = mPhysicsComponent->GetVelocity();
	float maxSpeed = 4.0f;
	float accelerator = 6.0f;
	// Handle movement based on input direction
	if (directionX != 0) {
		// Accelerate if moving in any direction
		currentVelocity.x += directionX * deltaTime * 2.0f;  // Accelerate based on direction and deltaTime

		// Clamp the velocity within the -4 to +4 range
		if (currentVelocity.x > maxSpeed) {
			currentVelocity.x = maxSpeed;
		}
		else if (currentVelocity.x < -maxSpeed) {
			currentVelocity.x = -maxSpeed;
		}
	}
	else {
		// Decelerate when no input is given
		if (currentVelocity.x > 0) {
			currentVelocity.x -= deltaTime * accelerator;  // Slow down to the right
			if (currentVelocity.x < 0) currentVelocity.x = 0;  // Clamp to zero when stopping
		}
		else if (currentVelocity.x < 0) {
			currentVelocity.x += deltaTime * accelerator;  // Slow down to the left
			if (currentVelocity.x > 0) currentVelocity.x = 0;  // Clamp to zero when stopping
		}
	}
	ENGINE_PRINT("Velocity.x = " + std::to_string(currentVelocity.x), 40, 20);
	ENGINE_PRINT("Velocity.y = " + std::to_string(currentVelocity.y), 40, 5);
	// Set the new velocity in the physics component
	mPhysicsComponent->SetVelocity(currentVelocity);
}
