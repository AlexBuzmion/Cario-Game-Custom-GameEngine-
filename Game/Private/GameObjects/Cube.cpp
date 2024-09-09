#include "Game/Public/GameObjects/Cube.h"

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

Cube::Cube(exVector2 inSpawnLoc, exColor inColor, bool inHasGravity, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2)
{	
	ENGINE_PRINT("Cube created!", 10.0f, 200.0f);
	mPoint1 = inPoint1;
	mPoint2 = inPoint2;
	mSpawnLocation = inSpawnLoc;
	mColor = inColor;
	mHasGravity = inHasGravity;
	mIsStatic = inIsStatic;
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
	mBoxRenderComponent = AddComponentOfType<BoxRenderComponent>(mPoint1, mPoint2, mColor, 0);
	// bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2, bool inHasGravity, exVector2 inVelocity
	mPhysicsComponent = AddComponentOfType<BoxColliderComponent>(true, mPoint1, mPoint2, false);
	
}
