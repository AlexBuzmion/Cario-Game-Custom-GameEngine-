#pragma once
#include "Game/Public/Components/RenderComponent.h"

class BoxRenderComponent : public RenderComponent
{
public:
	BoxRenderComponent() = delete;
	~BoxRenderComponent(); 
	BoxRenderComponent(std::shared_ptr<GameObject> inOwner);
	BoxRenderComponent(std::shared_ptr<GameObject> inOwner, exVector2 inPoint1, exVector2 inPoint2, exColor inColor);

protected:
	virtual void Render(exEngineInterface* inEngineInterface);

private:
	exVector2 point1;
	exVector2 point2;

};

