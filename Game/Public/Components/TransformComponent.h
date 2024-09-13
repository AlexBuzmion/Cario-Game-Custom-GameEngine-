#pragma once
#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"

//-----------------------------------------------------------------
// TransformComponent Class
// This component handles the position, scale, and rotation of a GameObject.
// It is responsible for defining where a GameObject is located in the game world,
// its size, and its orientation. This is a fundamental component for any GameObject
// that requires spatial manipulation.
//-----------------------------------------------------------------

typedef std::function<void(exVector2)> OnMovementEvent;

class TransformComponent : public Component, public std::enable_shared_from_this<TransformComponent> 
{
	friend class CameraManager;
public:
	// deleting the default constructor to ensure that every TransformComponent is associated with a specific GameObject and initialized with meaningful data
	TransformComponent() = delete;

	// destructor to ensure proper cleanup of the component when it is no longer needed
	~TransformComponent();

	// constructors to initialize the TransformComponent with its owning GameObject and necessary transformation data
	TransformComponent(std::shared_ptr<GameObject> owner, exVector2 position, exVector2 scale, exVector2 rotation);
	TransformComponent(std::shared_ptr<GameObject> owner, exVector2 position);
	TransformComponent(std::shared_ptr<GameObject> owner, exVector2&& position);

	// getter and setter for position
	exVector2 GetPosition() const;          // retrieves the current position of the GameObject
	void SetPosition(const exVector2& newPosition); // sets a new position for the GameObject

	exVector2 GetScale() const; 
	void SetScale(const exVector2& newScale);

	void RegisterMovementListener(OnMovementEvent listenerToAdd);

	void BroadcastMovement(exVector2 inNewPos);

	// add a function update transform based on camera offset 
protected: 
	virtual void InitializeComponent() override; 

private:
	// holds the position of the GameObject in the game world
	exVector2 mPosition;

	// determining its size relative to its original size
	exVector2 mScale;

	// defines the rotation of the GameObject in the game world
	exVector2 mRotation;

	std::vector<OnMovementEvent> mMovementEvents; 
};
