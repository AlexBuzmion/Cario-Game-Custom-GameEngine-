#pragma once
#include "Game/Public/Components/PhysicsComponent.h"

class PhysicsComponent;
class CircleColliderComponent : public PhysicsComponent
{
public:
	CircleColliderComponent() = delete; 
	CircleColliderComponent(std::shared_ptr<GameObject> inOwner);
	CircleColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic);
	CircleColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, float inRadius);
	CircleColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, float inRadius, bool inHasGravity, exVector2 inVelocity);

protected:
	virtual void InitializeComponent();
	virtual bool IsColliding(std::shared_ptr<PhysicsComponent> otherComponent); 

private:
	float mRadius;
};

