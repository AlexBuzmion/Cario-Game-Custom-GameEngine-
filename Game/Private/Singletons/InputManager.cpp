#include "Game/Public/Singletons/InputManager.h"
#include "Engine/Public/SDL.h"

InputState::InputState()
	: mAttack(false)
	, mJump(false)
	, mDuck(false)
	, mForward(false)
	, mBack(false)
	, mUse(false)
	, mCancel(false)
{
}

InputState::~InputState()
{
}

uint InputState::IsAttack() const
{
	return mAttack;
}

uint InputState::IsJump() const
{
	return mJump;
}

uint InputState::IsDuck() const
{
	return mDuck;
}

uint InputState::IsForward() const
{
	return mForward;
}

uint InputState::IsBack() const
{
	return mBack;
}

uint InputState::IsUse() const
{
	return mUse;
}

uint InputState::IsCancel() const
{
	return mCancel;
}

//==========================================================
//==========================================================

void InputManager::Update()
{
	mState.mAttack = IsButtonDown(SDL_SCANCODE_LCTRL);
	mState.mJump = IsButtonDown(SDL_SCANCODE_SPACE);
	mState.mDuck = IsButtonDown(SDL_SCANCODE_S);
	mState.mForward = IsButtonDown(SDL_SCANCODE_D);
	mState.mBack = IsButtonDown(SDL_SCANCODE_A);
	mState.mUse = IsButtonDown(SDL_SCANCODE_E);
	mState.mCancel = IsButtonDown(SDL_SCANCODE_BACKSPACE);
}

uint InputManager::IsButtonDown(int nScancode) const
{
	int nKeys = 0;
	const Uint8* pKeys = SDL_GetKeyboardState(&nKeys);

	if (pKeys == nullptr)
	{
		return 0;
	}

	if (nScancode >= nKeys)
	{
		return 0;
	}

	return pKeys[nScancode];
}

