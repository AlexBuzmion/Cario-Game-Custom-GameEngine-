#pragma once
#include "Game/Public/Utils.h"

typedef unsigned int uint; 
 
class InputState
{
public:

	// the "friend" keyword allows you to bypass encapsulation
	// in this case, it allows InputManager to reach into my private variables
	friend class InputManager;

	InputState();
	~InputState();

	uint IsAttack() const;
	uint IsJump() const;
	uint IsDuck() const;
	uint IsForward() const;
	uint IsBack() const;
	uint IsUse() const;
	uint IsCancel() const;
	
private:

	uint mAttack;
	uint mJump;
	uint mDuck;
	uint mForward;
	uint mBack;
	uint mUse;
	uint mCancel;

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

