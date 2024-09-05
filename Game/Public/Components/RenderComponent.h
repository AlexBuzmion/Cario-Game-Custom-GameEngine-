#pragma once
#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"

class exEngineInterface;

//-----------------------------------------------------------------
// RenderComponent Class
// Base class for all components responsible for rendering a GameObject.
// This component handles color and layering properties and provides
// an interface for rendering the GameObject on the screen. It is an 
// abstract class, meaning that specific renderable components will 
// inherit from it and implement the Render function.
//-----------------------------------------------------------------

class RenderComponent : public Component, public std::enable_shared_from_this<RenderComponent>
{
	friend class RenderEngine;
public:
	// deleting the default constructor to enforce that every RenderComponent must be associated with a GameObject
	RenderComponent() = delete;

	// ensures proper cleanup of resources when the RenderComponent is destroyed
	~RenderComponent();

	// constructors to initialize the RenderComponent with its owning GameObject and optional rendering properties like color and layer
	RenderComponent(std::shared_ptr<GameObject> owner);
	RenderComponent(std::shared_ptr<GameObject> owner, exColor color);
	RenderComponent(std::shared_ptr<GameObject> owner, exColor color, int layer);

	// getter and setter for color
	exColor GetColor() const;               // retrieves the current color of the GameObject for rendering
	void SetColor(const exColor& newColor); // sets a new color for the GameObject's rendering

protected:
	// abstract render function that must be implemented by derived classes, defining how the GameObject is drawn on the screen
	virtual void Render(exEngineInterface* inEngineInterface) = 0;
	virtual void InitializeComponent() override;
	// color used for rendering the GameObject
	exColor mColor;

	// determines the rendering order; lower values are rendered first
	int mLayer;

private:
	// registers the RenderComponent with the render engine, ensuring it is included in the rendering process
	void RegisterSelfToRenderEngine();
};
