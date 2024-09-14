// + Main.cpp
// entry point
//

#include "Game/Private/Game.h"
#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"
#include <windows.h>

Cario gGame;
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

int InitializeSDL()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return -1;
    }

    // Create window
    gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!gWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        return -1;
    }

    return 0;
}

void CleanupSDL()
{
    if (gRenderer)
    {
        SDL_DestroyRenderer(gRenderer);
    }
    if (gWindow)
    {
        SDL_DestroyWindow(gWindow);
    }
    SDL_Quit();
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Ensure only one instance
    if (hPrevInstance)
    {
        return 0;
    }

    // Initialize SDL and check for success
    if (InitializeSDL() != 0)
    {
        return 0;
    }

    // Engine version check
    if (AccessEngineVersion() != kEngineVersion)
    {
        CleanupSDL();
        return 0;
    }

    // Get the engine instance
    exEngineInterface* pEngine = AccessEngine();
    if (pEngine == nullptr)
    {
        CleanupSDL();
        return 0;
    }

    // Run the game through the engine
    pEngine->Run(&gGame);

    // Cleanup SDL resources
    CleanupSDL();

    return 0;
}
//-----------------------------------------------------------------
//-----------------------------------------------------------------

//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
//{
//	// never allow two instances
//	if ( hPrevInstance )
//	{
//		return 0;
//	}
//
//	// check version
//	if ( AccessEngineVersion() != kEngineVersion )
//	{
//		return 0;
//	}
//
//	// find the engine
//	exEngineInterface* pEngine = AccessEngine();
//
//	if ( pEngine == nullptr )
//	{
//		return 0;
//	}
//
//	// tell it to run
//	pEngine->Run( &gGame );
//
//	return 0;
//}
