#pragma once
#include "Game/Public/GameObject.h"

class PowerUpOne;
enum class ObjectType {
	Brick, 
	PowerUpBox,
};

class Cube : public GameObject
{
public:
	Cube();
	~Cube();
	Cube(exVector2 inSpawnLoc, exColor inColor, bool inHasGravity, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2, ObjectType inType);
	virtual void Tick(float deltaTime);
	virtual void BeginPlay();
	virtual void EndPlay();

	void Interact(); 
	void SetPowerUp(const std::shared_ptr<PowerUpOne> inPowerUp); 
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
	ObjectType mType; 
	exVector2 mDirection;
	std::shared_ptr<PowerUpOne> mPowerup; 
};

