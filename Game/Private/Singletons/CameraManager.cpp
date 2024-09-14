#include "Game/Public/Singletons/CameraManager.h"
#include "Game/Public/GameObject.h"

std::unique_ptr<CameraManager> CameraManager::sInstance = nullptr;

CameraManager::~CameraManager()
{
}

CameraManager& CameraManager::GetInstance()
{
	if (!sInstance) {
		//int mScreenCenterX = AccessEngine()->GetScreenWidth() * 0.5f;
		std::unique_ptr<CameraManager> newInstance(new CameraManager(400));
		sInstance = std::move(newInstance);
	}
	return *sInstance;
}

void CameraManager::UpdateWorldObjPos(exVector2 newPos)
{
	if (!mFollowingObj) return; // Ensure we're following an object
	ENGINE_PRINT("UpdateWorldObjPos() called", 250, 270);
	std::shared_ptr<PhysicsComponent> objPhysicsComp = mFollowingObj->GetOwner().lock()->FindComponentOfType<PhysicsComponent>();



	// Move all objects in the opposite direction of the followed object’s movement
	for (std::weak_ptr<TransformComponent> transform : mTransformComponentList) {
		if (transform.expired()) continue;

		std::shared_ptr<TransformComponent> currentComp = transform.lock();
		if (!currentComp) continue;
		std::weak_ptr<GameObject> currentObj = currentComp->GetOwner().lock();
		exVector2 currentPos = currentComp->GetPosition();
		// Move the object relative to the player's movement
		exVector2 newPosition = { (currentPos.x - objPhysicsComp->GetVelocity().x), currentPos.y };
		currentComp->SetPosition( newPosition);
		currentComp->mPosition = newPosition;
	}

}

void CameraManager::OnFollowObjectMoved(exVector2 newPosition)
{
	if (mFollowingObj->GetPosition().x < 400) return;
	ENGINE_PRINT("OnFollowObjectMoved() called", 250, 250);
	UpdateWorldObjPos(newPosition);
}

void CameraManager::FollowObject(std::shared_ptr<TransformComponent> objectToFollow)
{
	mFollowingObj = objectToFollow;
	ENGINE_PRINT("Following object X: " + std::to_string(mFollowingObj->GetPosition().x ), 250, 250);
	ENGINE_PRINT("                 Y: " + std::to_string(mFollowingObj->GetPosition().y ), 250, 280);
	// explicitly ensure this lambda function is the same as OnMovementEvent's convention
	objectToFollow->RegisterMovementListener(
		std::bind(&CameraManager::OnFollowObjectMoved, this, std::placeholders::_1));
}

void CameraManager::BoundaryObject(std::shared_ptr<TransformComponent> objectBounds)
{
	mBoundary = objectBounds;
}


void CameraManager::AddTransformComponent(std::shared_ptr<TransformComponent> transformToAdd)
{
	if (transformToAdd == mFollowingObj) {
		return;
	}
	if (transformToAdd->GetPosition().x == 0) {
		return;
	}
	mTransformComponentList.push_back(transformToAdd);
}

void CameraManager::RemoveTransformComponent(std::shared_ptr<TransformComponent> transformToRemove)
{
	//Todo: Implement removal from the list 
}

const std::shared_ptr<TransformComponent> CameraManager::GetFollowingObj()
{
	return mFollowingObj;
}

CameraManager::CameraManager(int screenWidth)
{
	mScreenCenterX = screenWidth;
}

void CameraManager::MoveObjects(float inTransform)
{
}
