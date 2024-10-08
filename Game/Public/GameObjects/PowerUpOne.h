#pragma once
#include "Game/Public/GameObject.h"
class PowerUpOne : public GameObject
{
	friend class Cube;
public: 
	PowerUpOne(); 
	~PowerUpOne();
	PowerUpOne(exVector2 inDirection, exVector2 inSpawnLocation, float inColliderRadius);

	virtual void Tick(float deltaTime);
	virtual void BeginPlay(); 

	void OnCollisionDetected(CollisionResult inResult, std::weak_ptr<GameObject> otherObjectHit);

	int GetPowerUpLvl();

	std::shared_ptr<TransformComponent> mTransform; 
	std::shared_ptr<CircleRenderComponent> mCircleRenderComponent; 
	std::shared_ptr<PhysicsComponent> mPhysicsComponent; 

private:
	exVector2 mSpawnLocation; 
	exVector2 mDirection; 
	float mColliderRadius;
	exColor mColor; 
	bool mHasGravity; 
	bool mIsGrounded; 
	int mPowerUpLvl;
};

