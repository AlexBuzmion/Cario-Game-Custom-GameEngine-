#include "Game/Public/Components/RenderComponents/CircleRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/GameObject.h"

CircleRenderComponent::~CircleRenderComponent()
{
	// Destructor: Ensures any necessary cleanup when a CircleRenderComponent is destroyed.
}

CircleRenderComponent::CircleRenderComponent(std::shared_ptr<GameObject> owner)
	: RenderComponent(owner), mRadius(20.0f)
{
	// Constructor: Initializes the CircleRenderComponent with a default radius of 20.0f.
}

CircleRenderComponent::CircleRenderComponent(std::shared_ptr<GameObject> owner, float radius)
	: RenderComponent(owner), mRadius(radius)
{
	// Constructor: Initializes the CircleRenderComponent with a specified radius.
}

CircleRenderComponent::CircleRenderComponent(std::shared_ptr<GameObject> owner, float radius, exColor color)
	: RenderComponent(owner, color), mRadius(radius)
{
	// Constructor: Initializes the CircleRenderComponent with a specified radius and color.
}

CircleRenderComponent::CircleRenderComponent(std::shared_ptr<GameObject> owner, float radius, exColor color, int layer)
	: RenderComponent(owner, color, layer), mRadius(radius)
{
	// Constructor: Initializes the CircleRenderComponent with a specified radius, color, and layer.
}

void CircleRenderComponent::SetRadius(float inRadiusChange)
{
	mOwner.lock()->FindComponentOfType<TransformComponent>()->SetScale({inRadiusChange, inRadiusChange});
}

void CircleRenderComponent::Render(exEngineInterface* inEngineInterface)
{
	if (mOwner.expired())
	{
		return; // Early exit if the owning GameObject is no longer valid.
	}

	std::shared_ptr<GameObject> owningGameObject = mOwner.lock(); // Lock the weak pointer to get a shared pointer.
	if (std::shared_ptr<TransformComponent> renderTransformComponent = owningGameObject->FindComponentOfType<TransformComponent>())
	{
		const exVector2 position = renderTransformComponent->GetPosition(); // Get the position from the TransformComponent.
		float scaledRadius = mRadius * (renderTransformComponent->GetScale().x + renderTransformComponent->GetScale().y) * 0.5f;
		inEngineInterface->DrawCircle(position, scaledRadius, mColor, 0); // Draw the circle at the specified position, radius, and color.
	}
}
