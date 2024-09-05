#include "Game/Public/GameObjects/Ball.h"


Ball::Ball() : GameObject()
{
	mColliderRadius = 100.0f;
	mDirection = exVector2{ 1.0f, 1.0f };
	mColor = exColor{ 255,0,0,255 };
	mSpawnLocation = exVector2{ 400.0f,400.0f };
}

Ball::~Ball()
{
}

Ball::Ball(exVector2 inDirection, exVector2 inSpawnLocation, float inColliderRadius, exColor inColor)
{
	mColliderRadius = inColliderRadius;
	mDirection = inDirection;
	mColor = inColor;
	mSpawnLocation = inSpawnLocation;
}

Ball::Ball(exVector2 inDirection, exVector2 inSpawnLocation, float inColliderRadius, exColor inColor, bool inHasGravity)
{
	mColliderRadius = inColliderRadius;
	mDirection = inDirection;
	mColor = inColor;
	mSpawnLocation = inSpawnLocation;
	mHasGravity = inHasGravity;
}

void Ball::Tick(float deltaTime)
{
	GameObject::Tick(deltaTime);
}

void Ball::BeginPlay()
{
	GameObject::BeginPlay();
	mTransform = AddComponentOfType<TransformComponent>(mSpawnLocation);
	mCircleRenderComponent = AddComponentOfType<CircleRenderComponent>(mColliderRadius, mColor, 2);
	// constructor parameters taken: bool inIsStatic, float inRadius, bool inHasGravity, exVector2 inVelocity
	mPhysicsComponent = AddComponentOfType<CircleColliderComponent>(false, mColliderRadius, mHasGravity, mDirection);
}

bool Ball::IsGrounded() const
{
	return mIsGrounded;
}

void Ball::SetGrounded(const bool& inIsGrounded)
{
	mIsGrounded = inIsGrounded;
}

float Ball::GetJumpHeight() const
{
	return mJumpHeight;
}

void Ball::SetJumpHeight(const float& inNewJumpHeight)
{
	mJumpHeight = inNewJumpHeight;
}
