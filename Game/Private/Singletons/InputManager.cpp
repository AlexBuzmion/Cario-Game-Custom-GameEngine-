#include "Game/Public/Singletons/InputManager.h"
#include "Engine/Public/SDL.h"

// Constructor to initialize the state
InputState::InputState()
    : mButtonStates(0)  // Initialize the button states to 0 (no buttons pressed)
{
}

InputState::~InputState() {}

//==========================================================
//==========================================================

// Update function to capture and update button states using bitmasking
void InputManager::Update()
{
    mState.mButtonStates = 0;  // Clear the button states first

    // Set the bits for each button if the key is pressed
    if (IsButtonDown(SDL_SCANCODE_LCTRL)) {
        mState.mButtonStates |= ATTACK_BUTTON;
    }
    if (IsButtonDown(SDL_SCANCODE_SPACE)) {
        mState.mButtonStates |= JUMP_BUTTON;
    }
    if (IsButtonDown(SDL_SCANCODE_S)) {
        mState.mButtonStates |= DUCK_BUTTON;
    }
    if (IsButtonDown(SDL_SCANCODE_D)) {
        mState.mButtonStates |= FORWARD_BUTTON;
    }
    if (IsButtonDown(SDL_SCANCODE_A)) {
        mState.mButtonStates |= BACK_BUTTON;
    }
    if (IsButtonDown(SDL_SCANCODE_E)) {
        mState.mButtonStates |= USE_BUTTON;
    }
    if (IsButtonDown(SDL_SCANCODE_BACKSPACE)) {
        mState.mButtonStates |= CANCEL_BUTTON;
    }
}

// Helper function to check if a button is down using SDL
uint InputManager::IsButtonDown(int nScancode) const
{
    int nKeys = 0;
    const Uint8* pKeys = SDL_GetKeyboardState(&nKeys);

    if (pKeys == nullptr)
    {
        return 0;  // No keys pressed
    }

    if (nScancode >= nKeys)
    {
        return 0;  // Invalid scancode
    }

    return pKeys[nScancode];  // Return the state of the key
}
