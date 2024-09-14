#include "Game/Public/Singletons/PhysicsEngine.h"
#include "Game/Public/GameObject.h"
#include "Game/Public/GameObjects/Ball.h"
#include <thread>

std::unique_ptr<PhysicsEngine> PhysicsEngine::sInstance = nullptr;

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::AddPhysicsComponent(std::shared_ptr<PhysicsComponent> physicsComponentToAdd)
{
	mPhysicsComponentList.push_back(physicsComponentToAdd);
}

void PhysicsEngine::RemovePhysicsComponent(std::shared_ptr<PhysicsComponent> componentToRemove)
{
	for (auto it = mPhysicsComponentList.begin(); it != mPhysicsComponentList.end(); ++it)
	{
		if (auto component = it->lock()) // Check if weak_ptr is valid
		{
			if (component == componentToRemove)
			{
				mPhysicsComponentList.erase(it); // Erase the matching component
				break; // Exit after removing the component
			}
		}
	}
}

PhysicsEngine& PhysicsEngine::GetInstance()
{
	if (!sInstance) {
		std::unique_ptr<PhysicsEngine> newInstance(new PhysicsEngine());
		sInstance = std::move(newInstance);
	}
	return *sInstance;
}

void PhysicsEngine::SimulatePhysics(float deltaTime)
{
	CheckCollisions(deltaTime);
	Move(deltaTime);
}

void PhysicsEngine::Move(float deltaTime)
{
	for (std::weak_ptr<PhysicsComponent> physicsComponentIter : mPhysicsComponentList) {
		if (physicsComponentIter.expired()) {
			continue; 
		}

		std::shared_ptr<PhysicsComponent> currentComponent = physicsComponentIter.lock();
		if (!currentComponent) {
			continue;
		}

		currentComponent->Move(deltaTime);
	}
}

void PhysicsEngine::CheckCollisions(float deltaTime)
{
	for (std::weak_ptr<PhysicsComponent> physicsComponentIter : mPhysicsComponentList) {
		for (std::weak_ptr<PhysicsComponent> otherphysicsComponentIter : mPhysicsComponentList) {
			
			if (physicsComponentIter.expired()) continue;
			if (otherphysicsComponentIter.expired()) continue;

			std::shared_ptr<PhysicsComponent> currentComponent = physicsComponentIter.lock();
			std::shared_ptr<PhysicsComponent> otherComponent = otherphysicsComponentIter.lock();

			if (currentComponent == otherComponent) continue;
			if (!currentComponent || !otherComponent) continue;
            
			CollisionResult collisionData = currentComponent->CheckCollision(otherComponent, deltaTime);

            if (collisionData.mCollisionSide != CollisionSide::None) {
                 //iterates over all the events and send the collision update
                for (OnCollisionEvent& collisionEvent : currentComponent->mCollisionEvents) {
                    collisionEvent(collisionData, otherComponent->GetOwner());
                }
			}
			
		}
	}
}

