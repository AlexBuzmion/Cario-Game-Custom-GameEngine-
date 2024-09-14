#include "Game/Public/GameObjects/Enemy1.h"


Enemy1::~Enemy1()
{
}

Enemy1::Enemy1(exVector2 inSpawnLoc, exColor inColor, bool inHasGravity, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2)
{
	mSpawnLocation = inSpawnLoc;
	mPoint1 = inPoint1;
	mPoint2 = inPoint2;
	mColor = inColor;
	mHasGravity = inHasGravity;
	mIsStatic = inIsStatic;
}

void Enemy1::Tick(float deltaTime)
{
	/*if (mIsGrounded) {
		mPhysicsComponent->SetVelocity()
	}*/
}

void Enemy1::BeginPlay()
{
	GameObject::BeginPlay();
	mTransform = AddComponentOfType<TransformComponent>(mSpawnLocation);
	mBoxRenderComponent = AddComponentOfType<BoxRenderComponent>(mSpawnLocation, mPoint1, mPoint2, mColor, mHasGravity); 
	mPhysicsComponent = AddComponentOfType<BoxColliderComponent>(mSpawnLocation, mIsStatic, mPoint1, mPoint2, mHasGravity);
	mPhysicsComponent->RegisterListener(std::bind(&Enemy1::OnCollisionDetected, this, std::placeholders::_1, std::placeholders::_2));
}

void Enemy1::OnCollisionDetected(CollisionResult inResults, std::weak_ptr<GameObject> otherObjectHit)
{

}
