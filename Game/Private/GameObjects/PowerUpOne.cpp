#include "Game/Public/GameObjects/PowerUpOne.h"
#include "Game/Public/GameObjects/Cube.h"
#include "Game/Public/GameObjects/Ball.h"

PowerUpOne::PowerUpOne()
{
	mColliderRadius = 25.0f; 
	mDirection = { 0, 0.0f };
	mColor = { 180, 180 ,100 ,255 };
	mSpawnLocation = { -20.0f, -20.0f };
	mHasGravity = false;
	mIsGrounded = false;
	mPowerUpLvl = 1;
}

PowerUpOne::~PowerUpOne()
{
}

PowerUpOne::PowerUpOne(exVector2 inDirection, exVector2 inSpawnLocation, float inColliderRadius)
{
	mColliderRadius = inColliderRadius;
	mDirection = inDirection;
	mColor = { 180, 180 ,180 ,255 };
	mSpawnLocation = inSpawnLocation;
	mHasGravity = false;
	mIsGrounded = false;
	mPowerUpLvl = 1;
}

void PowerUpOne::Tick(float deltaTime)
{
	GameObject::Tick(deltaTime);
	/*ENGINE_PRINT("Mushroom Pos X: " + std::to_string(mTransform->GetPosition().x), 200, 40);
	ENGINE_PRINT("Mushroom Pos Y: " + std::to_string(mTransform->GetPosition().y), 200, 60);*/
	if (mInitialSpawn) {
 		mPhysicsComponent->SetVelocity({ 1,0 });
	}
	
}

void PowerUpOne::BeginPlay()
{
	GameObject::BeginPlay();
	mTransform = AddComponentOfType<TransformComponent>(mSpawnLocation);
	mCircleRenderComponent = AddComponentOfType<CircleRenderComponent>(mColliderRadius, mColor, 0);
	mPhysicsComponent = AddComponentOfType<CircleColliderComponent>(false, mColliderRadius, false, mDirection);
	mPhysicsComponent->RegisterListener(std::bind(&PowerUpOne::OnCollisionDetected, this, std::placeholders::_1, std::placeholders::_2));
}

void PowerUpOne::OnCollisionDetected(CollisionResult inResult, std::weak_ptr<GameObject> otherObjectHit)
{
	if (std::shared_ptr<Ball> player = std::dynamic_pointer_cast<Ball>(otherObjectHit.lock())) {
		mTransform->SetPosition(mSpawnLocation); 
		mPhysicsComponent->SetVelocity({ 0,0 });
		mInitialSpawn = false;
	}
	
	if (std::shared_ptr<Cube> box = std::dynamic_pointer_cast<Cube>(otherObjectHit.lock())) {
		auto boxCollider = box->FindComponentOfType<BoxColliderComponent>();
		float boxWidth = boxCollider->GetBoxWidth(); // 50
		auto boxTransform = box->FindComponentOfType<TransformComponent>();
		mIsGrounded = true;
		// Handle collisions based on the side hit
		switch (inResult.mCollisionSide) {
		case CollisionSide::Top:
			// Check if the character is grounded
			if (!mIsGrounded) {
				float boxLengthPos = boxTransform->GetPosition().x + boxWidth * 0.5f;
				float boxLengthNeg = boxTransform->GetPosition().x - boxWidth * 0.5f;
				
				// Check if hit point is within box boundaries
				if (inResult.mHitPoint.x <= boxLengthPos &&
					inResult.mHitPoint.x >= boxLengthNeg) {

					// Character is on top of the box and grounded
					mTransform->SetPosition(inResult.mHitPoint + exVector2{ 0, -mColliderRadius }); // Place ball above cube
					mPhysicsComponent->SetVelocity(exVector2{ mPhysicsComponent->GetVelocity().x, 0 });
					ENGINE_PRINT("Ball is grounded on top of the box", 10.0f, 40.0f);
					mIsGrounded = true;
				}
				else {
					// The character has moved off the edge of the box, no longer grounded
					mIsGrounded = false;
				}
			}
			else {
				// Check if the character has moved off the box after being grounded
				float boxLengthNeg = boxTransform->GetPosition().x - boxWidth * 0.5f;
				float boxLengthPos = boxTransform->GetPosition().x + boxWidth * 0.5f;

				if (inResult.mHitPoint.x < boxLengthPos || inResult.mHitPoint.x > boxLengthNeg) {
					// The character is past the edge of the box, set to not grounded
					
					
				}
				else {
					mIsGrounded = false;
					ENGINE_PRINT("Ball moved off the edge of the box, no longer grounded", 10.0f, 40.0f);
				}
			}
			break;

		case CollisionSide::Bottom:
			if (!mIsGrounded) {
				mTransform->SetPosition(inResult.mHitPoint + exVector2{ 0, +mColliderRadius }); // Place ball below cube
				mPhysicsComponent->SetVelocity(exVector2{ mPhysicsComponent->GetVelocity().x, 0 });
				ENGINE_PRINT("Ball hit the bottom of a box", 10.0f, 40.0f);
			}
			break;

		case CollisionSide::Left:
			if (mIsGrounded) return;
			if (mPhysicsComponent->GetVelocity().x > 0) {
				// If the hit point is beyond the edge of the box, allow gravity
				if (inResult.mHitPoint.x >= mTransform->GetPosition().x + boxWidth / 2) {
					mIsGrounded = false;
				}
				// Place the PowerUp on the right side of the box
				mTransform->SetPosition(inResult.mHitPoint + exVector2{ -mColliderRadius, 0 });
				mPhysicsComponent->SetVelocity(exVector2{ 0, mPhysicsComponent->GetVelocity().y });
				ENGINE_PRINT("PowerUp hit the left side of the box", 10.0f, 40.0f);
			}
			// if the collision point is past the length of the box, apply gravity
			break;
		case CollisionSide::Right:
			if (mIsGrounded) return;
			if (mPhysicsComponent->GetVelocity().x < 0) {
				if (inResult.mHitPoint.x <= mTransform->GetPosition().x - boxWidth / 2) {
					mIsGrounded = false;  // Set grounded to false, allowing gravity to act
				}
				mTransform->SetPosition(inResult.mHitPoint + exVector2{ +mColliderRadius, 0 }); // Place ball on the left cube
				mPhysicsComponent->SetVelocity(exVector2{ 0, mPhysicsComponent->GetVelocity().y });
				ENGINE_PRINT("Ball hit right side of the box", 10.0f, 40.0f);
			}
			// if the collision point is past the length of the box, apply gravity
			break;

		default:
			
			break;
		}
		return;
	}
	if (inResult.mCollisionSide == CollisionSide::None) {
		mIsGrounded = false;
		return;
	}
}

int PowerUpOne::GetPowerUpLvl()
{
	return mPowerUpLvl;
}

void PowerUpOne::AnimateSpawn()
{
	mInitialSpawn = true; 
}

void PowerUpOne::Move()
{

}

void PowerUpOne::SetGravity(const bool& inGravity)
{
	mHasGravity = inGravity;
}
