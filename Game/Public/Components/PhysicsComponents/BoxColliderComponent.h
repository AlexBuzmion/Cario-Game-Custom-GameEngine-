#pragma once
#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/Components/RenderComponents/BoxLineRender.h"
class PhysicsComponent;
class BoxColliderComponent : public PhysicsComponent
{
public:
	BoxColliderComponent() = delete;
	BoxColliderComponent(std::shared_ptr<GameObject> inOwner);
	BoxColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2);
	BoxColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2, bool inHasGravity);
	BoxColliderComponent(std::shared_ptr<GameObject> inOwner, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2, bool inHasGravity, exVector2 inVelocity);
	
	exVector2 GetSize() const; 
	exVector2 GetPoint1() const;
	exVector2 GetPoint2() const;
	void DisableColliderBoxRender();
protected:
	virtual void InitializeComponent();
	virtual CollisionResult CheckCollision(std::shared_ptr<PhysicsComponent> otherComponent, CollisionResult inResultToReturn);

private:
	std::shared_ptr<BoxLineRender> mBoxColliderRender;
	exVector2 mPoint1; 
	exVector2 mPoint2; 
};

