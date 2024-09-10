#include "Game/Public/Components/RenderComponents/BoxLineRender.h"
#include "Game/Public/GameObject.h"
BoxLineRender::~BoxLineRender()
{
}

BoxLineRender::BoxLineRender(std::shared_ptr<GameObject> owner, exVector2 point1, exVector2 point2, exColor color, int layer) : RenderComponent(owner, color, layer)
{
	mPoint1 = point1;
	mPoint2 = point2;
}

void BoxLineRender::Render(exEngineInterface* inEngineInterface)
{
	if (mOwner.expired()) return; // Early exit if the owning GameObject is no longer valid.

	std::shared_ptr<GameObject> owningGameObject = mOwner.lock(); // Lock the weak pointer to get a shared pointer.
	if (std::shared_ptr<TransformComponent> renderTransformComponent = owningGameObject->FindComponentOfType<TransformComponent>())
	{
		inEngineInterface->DrawLineBox(mPoint1, mPoint2, mColor, 0); // Draw the circle at the specified 
	}
}
