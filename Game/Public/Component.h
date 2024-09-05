#pragma once
#include "Utils.h"

class GameObject;

//-----------------------------------------------------------------
// Component Class
// Base class for all components that can be attached to a GameObject.
// Components represent modular pieces of behavior or data that a GameObject
// can use to define its functionality.
//-----------------------------------------------------------------

class Component
{
	friend GameObject;
public:
	// delete the default constructor to enforce that every Component must be associated with a GameObject
	Component() = delete;

	// ensures proper cleanup of resources when a component is destroyed
	virtual ~Component();

	// constructor: initializes the component with its owning GameObject
	Component(std::shared_ptr<GameObject> inOwner);

	std::weak_ptr<GameObject> GetOwner() const;

protected:
	virtual void InitializeComponent() = 0;
	// weak pointer to the owning GameObject, used to avoid circular dependencies and manage the component's lifetime
	std::weak_ptr<GameObject> mOwner;
};

// typedef to define a list of components for easier management and readability
typedef std::vector<std::shared_ptr<Component>> ComponentList;
