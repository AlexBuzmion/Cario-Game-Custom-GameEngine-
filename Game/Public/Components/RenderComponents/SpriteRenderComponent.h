#pragma once
#include "Game/Public/Components/RenderComponent.h"
#include "Engine/Public/SDL.h"

class SpriteRenderComponent : public RenderComponent
{
public:
	SpriteRenderComponent() = delete; 
	~SpriteRenderComponent();
	SpriteRenderComponent(std::shared_ptr<GameObject> inOwner, const std::string& inFilePath);


protected: 
	virtual void Render(exEngineInterface* inEngineInterface) override; 

private:
	std::string mFilePath; 
	SDL_Texture* mTexture;
};

