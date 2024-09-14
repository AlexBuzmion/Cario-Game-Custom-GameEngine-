#pragma once

#include "Utils.h"
#include "Component.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/RenderComponent.h"
#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/Components/RenderComponents/CircleRenderComponent.h"
#include "Game/Public/Components/PhysicsComponents/CircleColliderComponent.h"
#include "Game/Public/Components/RenderComponents/BoxRenderComponent.h"
#include "Game/Public/Components/PhysicsComponents/BoxColliderComponent.h"
#include "Game/Public/Components/RenderComponents/SpriteRenderComponent.h"

// inherits from std::enable_shared_from_this<GameObject>
// this allows for safely creating shared pointers to the GameObject itself, ensuring proper memory management
class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	// initializes the GameObject, setting it up to manage components and interact with the engine
	GameObject();

	// ensures that all components are properly cleaned up when the GameObject is destroyed
	~GameObject();

	// called when the GameObject is first introduced into the game, essential for initializing components or setting up initial states
	virtual void BeginPlay();

	// called when the GameObject is removed from the game, necessary for handling any cleanup or final state saving
	virtual void EndPlay();

	// updates the GameObject every frame, allowing it to respond dynamically to changes in the game
	virtual void Tick(float deltaTime);

	virtual void SetIsGrounded(const bool& inGrounded);
	virtual bool GetGrounded() const; 
	// creates and adds a component of the specified type to the GameObject, following the Entity-Component-System (ECS) pattern for modular design
	template<class ComponentType, typename... Args>
	std::shared_ptr<ComponentType> AddComponentOfType(Args... arguments)
	{
		std::shared_ptr<ComponentType> componentToAdd = std::make_shared<ComponentType>
			(shared_from_this(), arguments...);

		if (std::shared_ptr<Component> castedComponent = std::dynamic_pointer_cast<Component>(componentToAdd)) {
			castedComponent->InitializeComponent();
		}
		
		mComponents.push_back(componentToAdd); // store the newly created component in the list for management
		return componentToAdd;
	}

	// searches for and returns a specific type of component attached to this GameObject
	template<class ComponentType>
	std::shared_ptr<ComponentType> FindComponentOfType()
	{
		// iterate over all components to find one that matches the requested type
		for (std::shared_ptr<Component> componentIter : mComponents)
		{
			if (std::shared_ptr<ComponentType> castedComponent = std::dynamic_pointer_cast<ComponentType>(componentIter))
			{
				return castedComponent; // return the component if found
			}
		}
		return nullptr; // return null if the component type isn't found
	}

protected:
	ComponentList mComponents; // holds all components attached to this GameObject, managing its behavior and state
	bool mIsGrounded;
};
