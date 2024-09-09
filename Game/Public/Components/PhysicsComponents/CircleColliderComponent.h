#pragma once
#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/Components/RenderComponents/CircleLineRender.h"

class PhysicsComponent;

class CircleColliderComponent : public PhysicsComponent
{
public:
	CircleColliderComponent() = delete; 
	CircleColliderComponent(std::shared_ptr<GameObject> inOwner);
	CircleColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic);
	CircleColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, float inRadius);
	CircleColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, float inRadius, bool inHasGravity, exVector2 inVelocity);

	virtual bool GetIsGrounded() override;

protected:
	virtual void InitializeComponent();
	virtual CollisionResult CheckCollision(std::shared_ptr<PhysicsComponent> otherComponent) override;

private:
	CollisionResult CircleCollisionCheck(std::shared_ptr<PhysicsComponent> otherCircle, CollisionResult inResultToReturn) const;
	CollisionResult BoxCollisionCheck(std::shared_ptr<PhysicsComponent> otherBox, CollisionResult inResultToReturn) const;
	std::shared_ptr<CircleLineRender> mCircleColliderRender;
	float mRadius;
	bool mIsGrounded;
};

