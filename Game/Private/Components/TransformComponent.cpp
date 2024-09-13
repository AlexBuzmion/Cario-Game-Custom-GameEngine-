#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Singletons/CameraManager.h"

TransformComponent::~TransformComponent()
{
	// Destructor: Ensures any necessary cleanup when a TransformComponent is destroyed.
}

TransformComponent::TransformComponent(std::shared_ptr<GameObject> owner, exVector2 position, exVector2 scale, exVector2 rotation)
	: Component(owner), mPosition(position), mScale(scale), mRotation(rotation)
{
	// Constructor: Initializes the TransformComponent with specified position, scale, and rotation.
	// The component is associated with the owning GameObject.
}

TransformComponent::TransformComponent(std::shared_ptr<GameObject> owner, exVector2 position)
	: Component(owner), mPosition(position), mRotation({ 0.0f, 0.0f }), mScale({ 1.0f, 1.0f })
{
	// Constructor: Initializes the TransformComponent with a specified position.
	// Default values are used for scale (1.0, 1.0) and rotation (0.0, 0.0).
}

TransformComponent::TransformComponent(std::shared_ptr<GameObject> owner, exVector2&& position)
	: Component(owner), mPosition(position), mRotation({ 0.0f, 0.0f }), mScale({ 1.0f, 1.0f })
{
	// Constructor: Initializes the TransformComponent with a movable position.
	// Default values are used for scale (1.0, 1.0) and rotation (0.0, 0.0).
}

exVector2 TransformComponent::GetPosition() const
{
	return mPosition; // Returns the current position of the GameObject.
}

void TransformComponent::SetPosition(const exVector2& newPosition)
{
	// Only broadcast if the position actually changed
	if (mPosition.x != newPosition.x || mPosition.y != newPosition.y) {
		mPosition = newPosition;
	}
}

exVector2 TransformComponent::GetScale() const
{
	return mScale;
}

void TransformComponent::SetScale(const exVector2& newScale)
{
	mScale = newScale; 
}

void TransformComponent::RegisterMovementListener(OnMovementEvent listenerToAdd)
{
	mMovementEvents.push_back(listenerToAdd);
}

void TransformComponent::BroadcastMovement(exVector2 inNewPos)
{
	for (OnMovementEvent& event : mMovementEvents) {
		event(mPosition); 
	}
}

void TransformComponent::InitializeComponent()
{
	CAMERA_MANAGER.AddTransformComponent(shared_from_this());
}
