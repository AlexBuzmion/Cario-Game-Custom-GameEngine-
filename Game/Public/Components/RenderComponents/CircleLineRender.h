#pragma once
#include "Game/Public/Components/RenderComponent.h"

class CircleLineRender : public RenderComponent
{
public:
	CircleLineRender() = delete; 
	~CircleLineRender();

	CircleLineRender(std::shared_ptr<GameObject> owner, float radius, exColor color, int layer);

protected: 
	virtual void Render(exEngineInterface* inEngineInterface);

private:
	float mRadius; 
};

