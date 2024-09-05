#pragma once
#include "Game/Public/GameObject.h"
class Cube : public GameObject
{
public:
	Cube();
	~Cube();
	Cube(exVector2 inSpawnLoc, exColor inColor, bool inHasGravity, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2);
	virtual void Tick(float deltaTime);
	virtual void BeginPlay();
protected:

private:
	std::shared_ptr<TransformComponent> mTransform;
	std::shared_ptr<BoxRenderComponent> mBoxRenderComponent;
	std::shared_ptr<PhysicsComponent> mPhysicsComponent;

	exVector2 mSpawnLocation;
	exVector2 mPoint1; 
	exVector2 mPoint2; 
	exColor mColor; 
	bool mHasGravity; 
	bool mIsStatic; 

	exVector2 mDirection;
};

