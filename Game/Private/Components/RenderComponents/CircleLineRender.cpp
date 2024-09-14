#include "Game/Public/Components/RenderComponents/CircleLineRender.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/GameObject.h"

CircleLineRender::~CircleLineRender()
{
}

CircleLineRender::CircleLineRender(std::shared_ptr<GameObject> owner, float radius, exColor color, int layer) : RenderComponent(owner, color, layer)
{
	mRadius = radius;
}

void CircleLineRender::Render(exEngineInterface* inEngineInterface)
{
	if (mOwner.expired())
	{
		return; // Early exit if the owning GameObject is no longer valid.
	}

	std::shared_ptr<GameObject> owningGameObject = mOwner.lock(); // Lock the weak pointer to get a shared pointer.
	if (std::shared_ptr<TransformComponent> renderTransformComponent = owningGameObject->FindComponentOfType<TransformComponent>())
	{
		mRadius = mOwner.lock()->FindComponentOfType<CircleColliderComponent>()->GetColliderRadius();
		const exVector2 position = renderTransformComponent->GetPosition(); // Get the position from the TransformComponent.
		inEngineInterface->DrawLineCircle(position, mRadius, mColor, 0); // Draw the circle at the specified position, radius, and color.
	}
}
