#pragma once
#include "Game/Public/Components/RenderComponent.h"

//-----------------------------------------------------------------
// CircleRenderComponent Class
// This class is responsible for rendering a circle for the GameObject
// it is attached to. It extends the base RenderComponent class and adds
// functionality specific to drawing circles on the screen. The circle's
// radius, color, and rendering layer can be customized.
//-----------------------------------------------------------------

class CircleRenderComponent : public RenderComponent
{
public:
	// deleting the default constructor to enforce that every CircleRenderComponent is associated with a GameObject and initialized with meaningful data
	CircleRenderComponent() = delete;

	// ensures proper cleanup of resources when the CircleRenderComponent is destroyed
	~CircleRenderComponent();

	// constructors to initialize the CircleRenderComponent with its owning GameObject, radius, and optional rendering properties like color and layer
	CircleRenderComponent(std::shared_ptr<GameObject> owner);
	CircleRenderComponent(std::shared_ptr<GameObject> owner, float radius);
	CircleRenderComponent(std::shared_ptr<GameObject> owner, float radius, exColor color);
	CircleRenderComponent(std::shared_ptr<GameObject> owner, float radius, exColor color, int layer);

	void SetRadius(float inRadiusChange);
protected:
	// overrides the abstract Render function from RenderComponent to provide the specific logic for rendering a circle
	virtual void Render(exEngineInterface* inEngineInterface);

private:
	// defines the radius of the circle to be rendered
	float mRadius;
};
