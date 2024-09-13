#pragma once
#include "Game/Public/GameObject.h"

class TransformComponent;
class CircleRenderComponent;

class Ball : public GameObject
{

public:

	Ball();
	~Ball();
	Ball(exVector2 inDirection, exVector2 inSpawnLocation, float inColliderRadius, exColor inColor);
	Ball(exVector2 inDirection, exVector2 inSpawnLocation, float inColliderRadius, exColor inColor, bool inHasGravity);
	virtual void Tick(float deltaTime);
	virtual void BeginPlay();
	
	bool IsGrounded() const;
	void SetGrounded(const bool& inIsGrounded); 
	void CheckGrounded(); 

	float GetJumpHeight() const;
	void SetJumpHeight(const float& inNewJumpHeight);
	bool IsJumping() const;
	
	void OnCollisionDetected(CollisionResult inResults, std::weak_ptr<GameObject> otherObjectHit);
	exVector2 GetCollisionPoint() const; 

	// Character movement
	void Jump(); 
	void Death();
	void AnimateGrowing();
	void MoveDirection(float directionX); 

private:

	std::shared_ptr<TransformComponent> mTransform;
	std::shared_ptr<CircleRenderComponent> mCircleRenderComponent;

	std::shared_ptr<PhysicsComponent> mPhysicsComponent;
	
	exVector2 mSpawnLocation;
	float mColliderRadius;
	exColor mColor;
	bool mHasGravity;

	int mPowerUpLvl;

	// movement
	bool mIsGrounded = false;
	bool mIsJumping = false;
	bool mIsFalling = false;
	exVector2 mDirection;
	float mJumpHeight = 200.0f;
	float mJumpForce = 30.0f;
	// jump tracker
	exVector2 mOriginalPosition;
	exVector2 mTargetPosition;
	exVector2 mCollisionPoint;
};
