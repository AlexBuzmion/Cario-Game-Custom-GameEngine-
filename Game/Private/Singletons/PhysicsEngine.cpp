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

void PhysicsEngine::SimulatePhysics()
{
	Collide(); 
	Move();
}

void PhysicsEngine::Move()
{
	for (std::weak_ptr<PhysicsComponent> physicsComponentIter : mPhysicsComponentList) {
		if (physicsComponentIter.expired()) {
			continue; 
		}

		std::shared_ptr<PhysicsComponent> currentComponent = physicsComponentIter.lock();
		if (!currentComponent) {
			continue;
		}

		currentComponent->Move();
	}
}

void PhysicsEngine::Collide()
{
	for (std::weak_ptr<PhysicsComponent> physicsComponentIter : mPhysicsComponentList) {
		for (std::weak_ptr<PhysicsComponent> otherphysicsComponentIter : mPhysicsComponentList) {
			
			if (physicsComponentIter.expired()) continue;
			if (otherphysicsComponentIter.expired()) continue;

			std::shared_ptr<PhysicsComponent> currentComponent = physicsComponentIter.lock();
			std::shared_ptr<PhysicsComponent> otherComponent = otherphysicsComponentIter.lock();

			if (currentComponent == otherComponent) continue;
			if (!currentComponent) continue;
			if (!otherComponent) continue;

			if (currentComponent->IsColliding(otherComponent)) {
				// logic specific to Ball/Character colliding with the top side of a box and setting it to isGrounded. 
				//if (std::shared_ptr<CircleColliderComponent> circle = std::dynamic_pointer_cast<CircleColliderComponent>(currentComponent)) {
				//	// Retrieve the GameObject that owns this CircleCollider
				//	std::shared_ptr<GameObject> owningObject = circle->GetOwner().lock();
				//	// Check if the owning object is a Ball or Character
				//	if (std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(owningObject)) {
				//		// Now you have access to the Ball object, and you can set its grounded state
				//		if (ball->IsGrounded()) return;
				//		// Set IsGrounded to true if collision with ground detected
				//		ENGINE_PRINT("Is grounded set to true", 10.0f, 40.0f);
				//		ball->SetGrounded(true);
				//	}
				//}
			}
		}
	}
}

