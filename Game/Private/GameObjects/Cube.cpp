#include "Game/Public/GameObjects/Cube.h"


std::shared_ptr<PowerUpOne> mPowerUpOne = nullptr;
Cube::Cube() : GameObject()
{
	mDirection;
	mSpawnLocation;
	mColor;
	mHasGravity = false;
	mIsStatic = true;
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
}

void Cube::Tick(float deltaTime)
{
	GameObject::Tick(deltaTime);
}

void Cube::BeginPlay()
{
	GameObject::BeginPlay();
	mTransform = AddComponentOfType<TransformComponent>(mSpawnLocation);
	//std::shared_ptr<GameObject> inOwner, exVector2 inPoint1, exVector2 inPoint2, exColor inColor
	mBoxRenderComponent = AddComponentOfType<BoxRenderComponent>(mSpawnLocation, mPoint1, mPoint2, mColor, 0);
	// bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2, bool inHasGravity, exVector2 inVelocity
	mPhysicsComponent = AddComponentOfType<BoxColliderComponent>(mSpawnLocation, true, mPoint1, mPoint2, false);
	
}

void Cube::EndPlay()
{
	mPhysicsComponent->RemoveFromComponentList();
}

void Cube::Interact()
{
	switch (mType) {
	case ObjectType::Brick:
		mBoxRenderComponent->SetColor({ 74, 118, 202, 100 });
		// call the physics engine unregister here
		if (std::shared_ptr<BoxColliderComponent> boxCollider = std::dynamic_pointer_cast<BoxColliderComponent>(mPhysicsComponent)) {
			boxCollider->DisableColliderBoxRender();
			EndPlay();
		}
		break;
	case ObjectType::PowerUpBox:
		mBoxRenderComponent->SetColor({ 100, 100, 0, 255 });
		if (mPowerup) {
			if (mPowerup->mTransform && mTransform) {
				mPowerup->mTransform->SetPosition(mTransform->GetPosition()+exVector2{0, -50});
				mPowerup->AnimateSpawn();
			}
		}
	}
}

void Cube::SetPowerUp(const std::shared_ptr<PowerUpOne> inPowerUp)
{
	mPowerup = inPowerUp;
}
