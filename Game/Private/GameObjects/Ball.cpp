#include "Game/Public/GameObjects/Ball.h"

Ball::Ball() : GameObject()
{
	mColliderRadius = 100.0f;
	mDirection = exVector2{ 1.0f, 1.0f };
	mColor = exColor{ 255,0,0,255 };
	mSpawnLocation = exVector2{ 400.0f,400.0f };
	mIsGrounded = false; 
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
	mIsGrounded = false;
}

Ball::Ball(exVector2 inDirection, exVector2 inSpawnLocation, float inColliderRadius, exColor inColor, bool inHasGravity)
{
	mColliderRadius = inColliderRadius;
	mDirection = inDirection;
	mColor = inColor;
	mSpawnLocation = inSpawnLocation;
	mHasGravity = inHasGravity;
	mIsGrounded = false;
}

void Ball::Tick(float deltaTime)
{
	GameObject::Tick(deltaTime);
	mIsGrounded = mPhysicsComponent->GetIsGrounded();
}

void Ball::BeginPlay()
{
	GameObject::BeginPlay();
	mIsGrounded = false;
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

void Ball::CheckGrounded()
{
	
}

float Ball::GetJumpHeight() const
{
	return mJumpHeight;
}

void Ball::SetJumpHeight(const float& inNewJumpHeight)
{
	mJumpHeight = inNewJumpHeight;
}

void Ball::Jump()
{
	exVector2 currentVelocity = mPhysicsComponent->GetVelocity();
	exVector2 targetHeight = { currentVelocity.x, currentVelocity.y + mJumpHeight };
	if (!mIsGrounded) return; 
		mIsJumping = true;
		mPhysicsComponent->SetVelocity(targetHeight);
}

void Ball::MoveDirection(float directionX)
{
	// Add to the current x velocity instead of setting it directly
	exVector2 currentVelocity = mPhysicsComponent->GetVelocity();
	currentVelocity.x = directionX;  // Add horizontal movement
	mPhysicsComponent->SetVelocity(currentVelocity);  // Set the new velocity
}
