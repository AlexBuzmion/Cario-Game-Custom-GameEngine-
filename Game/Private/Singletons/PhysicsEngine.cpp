#include "Game/Public/Singletons/PhysicsEngine.h"
#include "Game/Public/Components/PhysicsComponent.h"
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
	Collide(deltaTime);
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

void PhysicsEngine::Collide(float deltaTime)
{
	for (std::weak_ptr<PhysicsComponent> physicsComponentIter : mPhysicsComponentList) {
		for (std::weak_ptr<PhysicsComponent> otherphysicsComponentIter : mPhysicsComponentList) {
			
			if (physicsComponentIter.expired()) continue;
			if (otherphysicsComponentIter.expired()) continue;

			std::shared_ptr<PhysicsComponent> currentComponent = physicsComponentIter.lock();
			std::shared_ptr<PhysicsComponent> otherComponent = otherphysicsComponentIter.lock();

			if (currentComponent == otherComponent || !currentComponent || !otherComponent) continue;
            
			CollisionResult collisionData = currentComponent->CheckCollision(otherComponent);

            if (collisionData.mCollisionSide != CollisionSide::None) {
                // iterates over all the events and send the collision update
                for (OnCollisionEvent& collisionEvent : currentComponent->mCollisionEvents) {
                    collisionEvent(collisionData, otherComponent->GetOwner());
                }
            }
		}
	}
}

