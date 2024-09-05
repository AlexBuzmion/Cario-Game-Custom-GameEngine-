#pragma once
#include "Game/Public/Utils.h"

typedef unsigned int uint;

// Define bitmask values representing each button's state
#define ATTACK_BUTTON   (1 << 0)  // 00000001
#define JUMP_BUTTON     (1 << 1)  // 00000010
#define DUCK_BUTTON     (1 << 2)  // 00000100
#define FORWARD_BUTTON  (1 << 3)  // 00001000
#define BACK_BUTTON     (1 << 4)  // 00010000
#define USE_BUTTON      (1 << 5)  // 00100000
#define CANCEL_BUTTON   (1 << 6)  // 01000000

class InputState
{
public:

	// the "friend" keyword allows you to bypass encapsulation
	// in this case, it allows InputManager to reach into my private variables
	friend class InputManager;

	InputState();
	~InputState();

	// Functions to check the state of each button
	uint IsAttack() const { return (mButtonStates & ATTACK_BUTTON) != 0; }
	uint IsJumpPressed() const { return (mButtonStates & JUMP_BUTTON) != 0; }
	uint IsDownPressed() const { return (mButtonStates & DUCK_BUTTON) != 0; }
	uint IsForwardPressed() const { return (mButtonStates & FORWARD_BUTTON) != 0; }
	uint IsBackwardPressed() const { return (mButtonStates & BACK_BUTTON) != 0; }
	uint IsUse() const { return (mButtonStates & USE_BUTTON) != 0; }
	uint IsCancel() const { return (mButtonStates & CANCEL_BUTTON) != 0; }
	
private:

	uint mButtonStates;  // This will hold the bitmask of all button states
};


//=============================================================
//=============================================================

class InputManager
{
public:

	// this gets called each frame to query the system for the button states
	void Update();

	uint IsButtonDown(int nScancode) const;

	const InputState& GetState() const { return mState; }

private:

	InputState mState;

};

