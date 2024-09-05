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

BoxRenderComponent::BoxRenderComponent(std::shared_ptr<GameObject> inOwner, exVector2 inPoint1, exVector2 inPoint2, exColor inColor) : RenderComponent(inOwner, inColor)
{
	point1 = inPoint1;
	point2 = inPoint2;
}

void BoxRenderComponent::Render(exEngineInterface* inEngineInterface)
{
	if (mOwner.expired()) return; // Early exit if the owning GameObject is no longer valid.

	std::shared_ptr<GameObject> owningGameObject = mOwner.lock(); // Lock the weak pointer to get a shared pointer.
	if (std::shared_ptr<TransformComponent> renderTransformComponent = owningGameObject->FindComponentOfType<TransformComponent>())
	{
		const exVector2 position = renderTransformComponent->GetPosition(); // Get the position from the TransformComponent.

		// adjsut the DrawBox positions to the spawn point location
		exVector2 adjustedPos1 = point1 + position;
		exVector2 adjustedPos2 = point2 + position;

		inEngineInterface->DrawBox(adjustedPos1, adjustedPos2, mColor, 0); // Draw the circle at the specified position, radius, and color.
	}
}
