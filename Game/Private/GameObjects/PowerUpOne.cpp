#include "Game/Public/GameObjects/PowerUpOne.h"
#include "Game/Public/GameObjects/Cube.h"
#include "Game/Public/GameObjects/Ball.h"

PowerUpOne::PowerUpOne()
{
	mColliderRadius = 25.0f; 
	mDirection = { 0, 5.0f };
	mColor = { 180, 180 ,100 ,255 };
	mSpawnLocation = { 150.0f, 250.0f };
	mHasGravity = true; 
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
	mHasGravity = true;
	mIsGrounded = false;
	mPowerUpLvl = 1;
}

void PowerUpOne::Tick(float deltaTime)
{
	GameObject::Tick(deltaTime);

}

void PowerUpOne::BeginPlay()
{
	GameObject::BeginPlay();
	mTransform = AddComponentOfType<TransformComponent>(mSpawnLocation);
	mCircleRenderComponent = AddComponentOfType<CircleRenderComponent>(mColliderRadius, mColor, 0);
	mPhysicsComponent = AddComponentOfType<CircleColliderComponent>(false, mColliderRadius, mHasGravity, mDirection);
	mPhysicsComponent->RegisterListener(std::bind(&PowerUpOne::OnCollisionDetected, this, std::placeholders::_1, std::placeholders::_2));
}

void PowerUpOne::OnCollisionDetected(CollisionResult inResult, std::weak_ptr<GameObject> otherObjectHit)
{
	if (std::shared_ptr<Ball> player = std::dynamic_pointer_cast<Ball>(otherObjectHit.lock())) {

	}
	if (std::shared_ptr<Cube> floor = std::dynamic_pointer_cast<Cube>(otherObjectHit.lock())) {
		// Handle collisions based on the side hit
		switch (inResult.mCollisionSide) {
		case CollisionSide::Top:
			if (!mIsGrounded) {
				// Check if the ball is still supported enough by the box (not past its center)
				if (inResult.mHitPoint.x <= mTransform->GetPosition().x + mColliderRadius * 0.5f &&
					inResult.mHitPoint.x >= mTransform->GetPosition().x - mColliderRadius * 0.5f) {
					mTransform->SetPosition(inResult.mHitPoint + exVector2{ 0, -mColliderRadius }); // Place ball above cube
					mPhysicsComponent->SetVelocity(exVector2{ mPhysicsComponent->GetVelocity().x, 0 });
					ENGINE_PRINT("Ball is grounded on top of the box", 10.0f, 40.0f);
					mIsGrounded = true;
				}
				else {
					// The ball is moving off the edge of the box, so it's no longer grounded
					mIsGrounded = false;
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
			if (mPhysicsComponent->GetVelocity().x > 0) {
				if (inResult.mHitPoint.x >= mTransform->GetPosition().x) {
					mIsGrounded = false;
				}
				mTransform->SetPosition(inResult.mHitPoint + exVector2{ -mColliderRadius, 0 }); // Place ball on the  right cube
				mPhysicsComponent->SetVelocity(exVector2{ 0, mPhysicsComponent->GetVelocity().y });
				ENGINE_PRINT("Ball hit left side of the box", 10.0f, 40.0f);
			}
			break;
		case CollisionSide::Right:
			if (mPhysicsComponent->GetVelocity().x < 0) {
				mTransform->SetPosition(inResult.mHitPoint + exVector2{ +mColliderRadius, 0 }); // Place ball on the left cube
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

int PowerUpOne::GetPowerUpLvl()
{
	return mPowerUpLvl;
}
