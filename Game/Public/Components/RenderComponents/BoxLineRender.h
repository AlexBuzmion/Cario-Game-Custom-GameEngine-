#pragma once
#include "Game/Public/Components/RenderComponent.h"

class BoxLineRender : public RenderComponent
{
public:
	BoxLineRender() = delete;
	~BoxLineRender();

	BoxLineRender(std::shared_ptr<GameObject> owner, exVector2 point1, exVector2 point2, exColor color, int layer);

protected:
	virtual void Render(exEngineInterface* inEngineInterface);

private:
	exVector2 mPoint1; 
	exVector2 mPoint2; 	
};

