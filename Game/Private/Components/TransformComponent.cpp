#include "Game/Public/Components/TransformComponent.h"

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
	mPosition = newPosition; // Updates the GameObject's position.
}

void TransformComponent::InitializeComponent()
{
}
