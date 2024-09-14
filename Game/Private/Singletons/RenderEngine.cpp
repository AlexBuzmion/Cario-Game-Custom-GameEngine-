#include "Game/Public/Singletons/RenderEngine.h"
#include "Game/Public/Components/RenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"


std::unique_ptr<RenderEngine> RenderEngine::sInstance = nullptr; // Initialize the static instance pointer to nullptr.

RenderEngine::RenderEngine()
{
}

RenderEngine::~RenderEngine()
{
}

RenderEngine& RenderEngine::GetInstance()
{
	if (!sInstance) {
		std::unique_ptr<RenderEngine> newInstance(new RenderEngine());
		sInstance = std::move(newInstance);
	}
	return *sInstance; // Return a reference to the singleton instance.
}

void RenderEngine::Render(exEngineInterface* renderEngine, bool RenderCollider)
{

	// Iterate through all registered render components.
	for (std::weak_ptr<RenderComponent> componentToRender : mRenderComponentList) {
		if (!componentToRender.expired()) {
			std::shared_ptr<RenderComponent> renderComponent = componentToRender.lock();
			// If RenderCollider is false, skip rendering collider-specific components.
			if (!RenderCollider) {
				if (std::dynamic_pointer_cast<CircleLineRender>(renderComponent) ||
					std::dynamic_pointer_cast<BoxLineRender>(renderComponent)) {
					continue; // Skip rendering the collider components
				}
			}

			componentToRender.lock()->Render(renderEngine); // Lock the weak pointer and call Render if the component is still valid.
		}
	}
}

void RenderEngine::AddRenderingComponent(std::shared_ptr<RenderComponent> renderingComponentToAdd)
{
	mRenderComponentList.push_back(renderingComponentToAdd); // Add the new rendering component to the list of components to be rendered.
}



