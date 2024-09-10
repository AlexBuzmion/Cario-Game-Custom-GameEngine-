#pragma once
#include "Game/Public/Components/PhysicsComponent.h"

#define PHYSICS_ENGINE PhysicsEngine::GetInstance() // macro to easily access the singleton instance of the RenderEngine

class exEngineInterface;
class PhysicsComponent;

class PhysicsEngine
{
public:
	~PhysicsEngine();
	// returns the single instance of the RenderEngine, creating it if it doesn't exist
	static PhysicsEngine& GetInstance();

	// iterates over all registered rendering components and calls their Render function
	void SimulatePhysics(float deltaTime);

	// adds a rendering component to the list of components managed by the RenderEngine
	void AddPhysicsComponent(std::shared_ptr<PhysicsComponent> physicsComponentToAdd);
	void RemovePhysicsComponent(std::shared_ptr<PhysicsComponent> componentToRemove);
private:
	// needs to be a private constructor to enforce the Singleton pattern, preventing direct instantiation
	PhysicsEngine();
	
	void Move(float deltaTime);
	void Collide(float deltaTime);

	// unique pointer to the single instance of the RenderEngine
	static std::unique_ptr<PhysicsEngine> sInstance;

	// a list of weak pointers to rendering components, ensuring that the RenderEngine does not prevent components from being destroyed
	std::vector<std::weak_ptr<PhysicsComponent>> mPhysicsComponentList;

};


