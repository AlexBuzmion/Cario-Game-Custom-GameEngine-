#include "Game/Public/GameObjects/Cube.h"
#include "Game/Public/GameObjects/Ball.h"

std::shared_ptr<PowerUpOne> mPowerUpOne = nullptr;
Cube::Cube() : GameObject()
{
	mDirection;
	mSpawnLocation;
	mColor;
	mHasGravity = false;
	mIsStatic = true;
	mBumped = false;
}

Cube::~Cube()
{
}

Cube::Cube(exVector2 inSpawnLoc, exColor inColor, bool inHasGravity, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2, ObjectType inType)
{	
	ENGINE_PRINT("Cube created!", 10.0f, 200.0f);
	mSpawnLocation = inSpawnLoc;
	mColor = inColor;
	mHasGravity = inHasGravity;
	mIsStatic = inIsStatic;
	mPoint1 = inPoint1;
	mPoint2 = inPoint2;
	mType = inType;
	mBumped = false;
}

void Cube::Tick(float deltaTime)
{
	GameObject::Tick(deltaTime);
	// If the cube has been bumped, handle the bump animation
	if (mBumped) {
		float moveDirection = 50.0f;
		// Get the current position of the cube
		exVector2 currentPos = mTransform->GetPosition();

		// Define the target position (how far the cube should move upwards)
		exVector2 targetPos = { currentPos.x, mSpawnLocation.y - moveDirection };

		// Check if the cube has reached or passed the target position
		if (currentPos.y <= targetPos.y) {

			// If the target position is reached, reset velocity and position
			mPhysicsComponent->SetVelocity({ 0, 0 });  // Stop movement
			mTransform->SetPosition({ currentPos.x , currentPos.y + moveDirection}); // Reset to original position
			if (mType == ObjectType::Brick) {
				mBumped = false; // Reset the bump state
			}
		}
	}
}

void Cube::BeginPlay()
{
	GameObject::BeginPlay();
	mTransform = AddComponentOfType<TransformComponent>(mSpawnLocation);
	//std::shared_ptr<GameObject> inOwner, exVector2 inPoint1, exVector2 inPoint2, exColor inColor
	mBoxRenderComponent = AddComponentOfType<BoxRenderComponent>(mSpawnLocation, mPoint1, mPoint2, mColor, 0);
	// bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2, bool inHasGravity, exVector2 inVelocity
	mPhysicsComponent = AddComponentOfType<BoxColliderComponent>(mSpawnLocation, mIsStatic, mPoint1, mPoint2, mHasGravity);
	
}

void Cube::EndPlay()
{
	mPhysicsComponent->RemoveFromComponentList();
}

void Cube::Interact(int playerLvl)
{
	if (!mBumped) {
		mBumped = true; 
		mPhysicsComponent->SetVelocity({ 0, -10 });
		switch (mType) {
			case ObjectType::Brick:
				if (playerLvl >= 1) { // if player already has a powerup
					mBoxRenderComponent->SetColor({ 74, 118, 202, 100 });
					if (std::shared_ptr<BoxColliderComponent> boxCollider = std::dynamic_pointer_cast<BoxColliderComponent>(mPhysicsComponent)) {
						
						boxCollider->DisableColliderBoxRender();
						// call the physics engine unregister here
						EndPlay();
						return;
					}
				}
				else {
					
				}
				break;

			case ObjectType::PowerUpBox:
				mBoxRenderComponent->SetColor({ 120, 120, 10, 255 });
				if (mPowerup) {
					if (mPowerup->mTransform && mTransform) {
						mPowerup->mTransform->SetPosition(mTransform->GetPosition()+exVector2{0, -50});
						mPowerup->AnimateSpawn();
						mPowerup->SetGravity(true);
					}
				}
				break;

		}
	}
}

void Cube::SetPowerUp(const std::shared_ptr<PowerUpOne> inPowerUp)
{
	mPowerup = inPowerUp;
}
