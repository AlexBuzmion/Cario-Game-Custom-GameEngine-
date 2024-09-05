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

	// Character movement
	void Jump(); 

	void MoveDirection(float directionX); 

private:

	std::shared_ptr<TransformComponent> mTransform;
	std::shared_ptr<CircleRenderComponent> mCircleRenderComponent;
	std::shared_ptr<PhysicsComponent> mPhysicsComponent;
	
	exVector2 mSpawnLocation;
	float mColliderRadius;
	exColor mColor;
	bool mHasGravity;

	// movement
	bool mIsGrounded = false;
	bool mIsJumping;
	exVector2 mDirection;
	float mJumpHeight = 7.0f;
	
};
