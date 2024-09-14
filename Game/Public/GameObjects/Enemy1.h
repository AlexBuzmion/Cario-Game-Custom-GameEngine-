#pragma once
#include "Game/Public/GameObject.h"

class Enemy1 : public GameObject
{
public:
	Enemy1() = delete; 
	~Enemy1();
	Enemy1(exVector2 inSpawnLoc, exColor inColor, bool inHasGravity, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2);

	virtual void Tick(float deltaTime);
	virtual void BeginPlay();
	void OnCollisionDetected(CollisionResult inResults, std::weak_ptr<GameObject> otherObjectHit);

private: 
	std::shared_ptr<TransformComponent> mTransform; 
	std::shared_ptr<BoxRenderComponent> mBoxRenderComponent;
	std::shared_ptr<PhysicsComponent> mPhysicsComponent;

	exVector2 mSpawnLocation; 
	exVector2 mPoint1; 
	exVector2 mPoint2; 
	exColor mColor; 
	bool mHasGravity; 
	bool mIsStatic; 
	bool mIsGrounded;
	exVector2 mDirection; 
};

