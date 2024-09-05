#pragma once
#include "Game/Public/Utils.h"

#define RENDER_ENGINE RenderEngine::GetInstance() // macro to easily access the singleton instance of the RenderEngine

class exEngineInterface;
class RenderComponent;

//-----------------------------------------------------------------
// RenderEngine Class
// Manages the rendering process for all renderable components in the game.
// This class follows the Singleton design pattern, ensuring that only one
// instance of the RenderEngine exists at any time. It handles the collection
// and rendering of all components that require drawing on the screen.
//-----------------------------------------------------------------

class RenderEngine
{
public:
	
	~RenderEngine();
	// returns the single instance of the RenderEngine, creating it if it doesn't exist
	static RenderEngine& GetInstance();

	// iterates over all registered rendering components and calls their Render function
	void Render(exEngineInterface* renderEngine);

	// adds a rendering component to the list of components managed by the RenderEngine
	void AddRenderingComponent(std::shared_ptr<RenderComponent> renderingComponentToAdd);


private:
	// needs to be a private constructor to enforce the Singleton pattern, preventing direct instantiation
	RenderEngine();

	// a list of weak pointers to rendering components, ensuring that the RenderEngine does not prevent components from being destroyed
	std::vector<std::weak_ptr<RenderComponent>> mRenderComponentList;

	// unique pointer to the single instance of the RenderEngine
	static std::unique_ptr<RenderEngine> sInstance;
};
