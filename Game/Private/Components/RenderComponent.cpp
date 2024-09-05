#include "Game/Public/Components/RenderComponent.h"
#include "Game/Public/Singletons/RenderEngine.h"

// Destructor: Ensures any necessary cleanup when a RenderComponent is destroyed.
RenderComponent::~RenderComponent()
{
}

// Constructor: Initializes the RenderComponent with a default grey color and layer 0.
// The component is associated with the owning GameObject.
RenderComponent::RenderComponent(std::shared_ptr<GameObject> owner) : Component(owner)
{
	mColor = { 125, 125, 125, 1 }; 
	mLayer = 0;
}

// Constructor: Initializes the RenderComponent with a specified color and default layer 0.
RenderComponent::RenderComponent(std::shared_ptr<GameObject> owner, exColor color) : Component(owner)
{
	mColor = color;
	mLayer = 0;
}

// Constructor: Initializes the RenderComponent with specified color and layer.
RenderComponent::RenderComponent(std::shared_ptr<GameObject> owner, exColor color, int layer) : Component(owner)
{
	mColor = color; 
	mLayer = layer;
}

// Returns the current color used for rendering the GameObject.
exColor RenderComponent::GetColor() const
{
	return mColor; 
}

// Updates the color used for rendering the GameObject.
void RenderComponent::SetColor(const exColor& newColor)
{
	mColor = newColor; 
}

void RenderComponent::InitializeComponent()
{
	RegisterSelfToRenderEngine();
}

// Registers this RenderComponent with the RenderEngine, allowing it to be included in the rendering process.
void RenderComponent::RegisterSelfToRenderEngine()
{
	RENDER_ENGINE.AddRenderingComponent(shared_from_this());
}

