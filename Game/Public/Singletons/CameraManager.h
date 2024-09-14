#pragma once
#include "Game/Public/Components/TransformComponent.h"

#define CAMERA_MANAGER CameraManager::GetInstance() 

class exEngineInterface; 

class CameraManager
{
public:
	~CameraManager();
	static CameraManager& GetInstance();

	void UpdateWorldObjPos(exVector2 newPos); 

	void FollowObject(std::shared_ptr<TransformComponent> objectToFollow);
	void BoundaryObject(std::shared_ptr<TransformComponent> objectBounds);
	void OnFollowObjectMoved(exVector2 newPosition);
	void AddTransformComponent(std::shared_ptr<TransformComponent> transformToAdd);
	void RemoveTransformComponent(std::shared_ptr<TransformComponent> transformToRemove);

	const std::shared_ptr<TransformComponent> GetFollowingObj();

private:
	CameraManager(int screenWidth);

	void MoveObjects(float inTransform);
	
	static std::unique_ptr<CameraManager> sInstance; 
	std::shared_ptr<TransformComponent> mFollowingObj; 
	std::shared_ptr<TransformComponent> mBoundary;
	int mScreenCenterX;

	std::vector <std::weak_ptr<TransformComponent>> mTransformComponentList;
};

