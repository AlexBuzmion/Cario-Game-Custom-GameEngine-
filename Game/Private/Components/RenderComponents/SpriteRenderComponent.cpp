#include "Game/Public/Components/RenderComponents/SpriteRenderComponent.h"
#include "Game/Public/GameObject.h"
#include "Game/Public/Components/TransformComponent.h"


extern SDL_Renderer* gRenderer;

SpriteRenderComponent::~SpriteRenderComponent()
{
    if (mTexture)
    {
        SDL_DestroyTexture(mTexture);  // Clean up the texture when the component is destroyed
        mTexture = nullptr;
    }
}

SpriteRenderComponent::SpriteRenderComponent(std::shared_ptr<GameObject> inOwner, const std::string& inFilePath) : RenderComponent(inOwner), mTexture(nullptr), mFilePath(inFilePath)
{
    // Load BMP image using SDL2's core functionality
    SDL_Surface* surface = SDL_LoadBMP(mFilePath.c_str());  // Load BMP image
    if (!surface)
    {
        // Handle error and log if image fails to load
        SDL_Log("Failed to load BMP: %s", SDL_GetError());
        return;
    }

    // Create a texture from the surface
    mTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface);  // Free the surface after creating the texture

    if (!mTexture)
    {
        // Handle error and log if texture creation fails
        SDL_Log("Failed to create texture from BMP: %s", SDL_GetError());
    }
}

void SpriteRenderComponent::Render(exEngineInterface* inEngineInterface)
{
    if (!mTexture)
    {
        // If no texture is available, don't render anything
        return;
    }

    // Get the transform component of the GameObject to get the position and scale
    auto transform = mOwner.lock()->FindComponentOfType<TransformComponent>();
    if (!transform)
    {
        return;
    }

    exVector2 position = transform->GetPosition();
    exVector2 scale = transform->GetScale();

    // Query the texture to get its width and height
    int textureWidth, textureHeight;
    SDL_QueryTexture(mTexture, nullptr, nullptr, &textureWidth, &textureHeight);

    // Define the destination rectangle for rendering
    SDL_Rect destRect;
    destRect.x = static_cast<int>(position.x);
    destRect.y = static_cast<int>(position.y);
    destRect.w = static_cast<int>(textureWidth * scale.x);  // Scale the width
    destRect.h = static_cast<int>(textureHeight * scale.y); // Scale the height

    // Render the texture onto the screen
    SDL_RenderCopy(gRenderer, mTexture, nullptr, &destRect);
}
