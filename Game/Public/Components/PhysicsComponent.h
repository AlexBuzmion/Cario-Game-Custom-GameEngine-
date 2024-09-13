#pragma once
#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"
#include "Engine/Public/EngineInterface.h"


// To be used in box collision checks
enum class CollisionSide
{
	None,       // No collision
	Top,        // Collision with the top side of the box
	Bottom,     // Collision with the bottom side of the box
	Left,       // Collision with the left side of the box
	Right       // Collision with the right side of the box
};

struct CollisionResult {
	CollisionSide mCollisionSide; 
	exVector2 mHitPoint; 
};

typedef std::function<void(CollisionResult, std::weak_ptr<GameObject>)> OnCollisionEvent;

class PhysicsComponent : public Component, public std::enable_shared_from_this<PhysicsComponent>
{
	friend class PhysicsEngine;

public:
	PhysicsComponent() = delete;
	~PhysicsComponent();

	PhysicsComponent(std::shared_ptr<GameObject> mOwner);
	PhysicsComponent(std::shared_ptr<GameObject> mOwner, bool inIsStatic);
	PhysicsComponent(std::shared_ptr<GameObject> mOwner, bool inIsStatic, bool inHasGravity);
	PhysicsComponent(std::shared_ptr<GameObject> mOwner, bool inIsStatic, bool inHasGravity, exVector2 inVelocity);

	void RegisterListener(OnCollisionEvent eventToAdd);
	void UnregisterListener(OnCollisionEvent eventToRemove);
	virtual CollisionResult CheckCollision(std::shared_ptr<PhysicsComponent> otherComponent);
	virtual void Move(float deltaTime); // Todo: Implement Physics Engine and move to protected

	exVector2 GetVelocity() const;
	void SetVelocity(const exVector2& newVelocity );

	virtual void RemoveFromComponentList(); 
protected:
	virtual void InitializeComponent() override; 
	bool mIsStatic; 
	bool mHasGravity; 
	exVector2 mVelocity; // stores vector and speed 

private:
	const float mGravityConstant = 35.0f;
	std::vector<OnCollisionEvent> mCollisionEvents; // stores all registered collision events
};

