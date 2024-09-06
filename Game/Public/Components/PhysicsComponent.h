#pragma once
#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"
#include "Engine/Public/EngineInterface.h"

typedef std::function<void(exVector2)> OnCollisionEvent;

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
	virtual bool GetIsGrounded();
	virtual bool IsColliding(std::shared_ptr<PhysicsComponent> otherComponent);
	virtual void Move(); // Todo: Implement Physics Engine and move to protected

	exVector2 GetVelocity() const;
	void SetVelocity(const exVector2& newVelocity );

protected:
	virtual void InitializeComponent() override; 
	bool mIsStatic; 
	bool mHasGravity; 
	exVector2 mVelocity; // stores vector and speed 

private:
	const float mGravityConstant = 9.8f;
	std::vector<OnCollisionEvent> mCollisionEvents; // stores all registered collision events
};

