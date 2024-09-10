#include "Game/Public/Components/RenderComponents/BoxRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/GameObject.h"

BoxRenderComponent::~BoxRenderComponent() 
{
}

BoxRenderComponent::BoxRenderComponent(std::shared_ptr<GameObject> inOwner) : RenderComponent(inOwner)
{
	point1 = exVector2{100.0f, 100.0f};
	point2 = exVector2{400.0f, 200.0f};
}

BoxRenderComponent::BoxRenderComponent(std::shared_ptr<GameObject> inOwner, exVector2 inSpawnLoc, exVector2 inPoint1, exVector2 inPoint2, exColor inColor, int layer) : RenderComponent(inOwner, inColor, layer)
{
	// Store input parameters
	point1 = inPoint1;
	point2 = inPoint2;

	
}

void BoxRenderComponent::Render(exEngineInterface* inEngineInterface)
{
	if (mOwner.expired()) return; // Early exit if the owning GameObject is no longer valid.

	std::shared_ptr<GameObject> owningGameObject = mOwner.lock(); // Lock the weak pointer to get a shared pointer.
	if (std::shared_ptr<TransformComponent> renderTransformComponent = owningGameObject->FindComponentOfType<TransformComponent>())
	{
		// Get the current position from the TransformComponent
		exVector2 position = renderTransformComponent->GetPosition();

		// Calculate half-width and half-height of the box
		exVector2 halfDimensions = (point2 - point1) * 0.5f;

		// Calculate the top-left and bottom-right corner relative to the current position (spawnPoint)
		exVector2 adjustedPoint1 = position - halfDimensions;
		exVector2 adjustedPoint2 = position + halfDimensions;

		inEngineInterface->DrawBox(adjustedPoint1, adjustedPoint2, mColor, 0);
	}
}
