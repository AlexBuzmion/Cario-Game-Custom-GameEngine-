#include "Game/Private/Game.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/GameObjects/Ball.h"
#include "Game/Public/GameObjects/Cube.h"
#include "Engine/Public/SDL.h"
#include "Game/Public/Singletons/RenderEngine.h"
#include "Game/Public/Singletons/PhysicsEngine.h"

//-----------------------------------------------------------------
// defining the window name globally for easy reference across the game
//-----------------------------------------------------------------

const char* gWindowName = "Cario";

//-----------------------------------------------------------------
// initializing member variables to their default states
// - mEngine: initially set to nullptr, will be assigned in Initialize.
// - mFontID: set to -1, indicating that the font has not been loaded yet.
// - mUp and mDown: flags to track key presses, initially set to false.
//-----------------------------------------------------------------

Cario::Cario()
	: mEngine(nullptr)  // no engine reference at the start; it will be set in Initialize
	, mFontID(-1)       // -1 indicates that no font is loaded yet
	, mUp(false)        // flags for key presses are initially false
	, mDown(false)
{
}

//-----------------------------------------------------------------
// destructor handles any necessary cleanup.
// currently, no dynamic memory allocation or resources need to be explicitly released.
//-----------------------------------------------------------------

Cario::~Cario()
{
}

//-----------------------------------------------------------------
// Initialize: sets up the game environment
// - Assigns the engine reference for future operations.
// - Loads the font for rendering text.
// - Sets the initial position for text rendering.
// - Creates and initializes the Ball object, ensuring it is ready to be used in the game.
//-----------------------------------------------------------------

void Cario::Initialize(exEngineInterface* pEngine)
{
	mEngine = pEngine; // linking the game with the engine for future operations

	mFontID = mEngine->LoadFont("resources/play-regular.ttf", 32); // loading the font to render text

	// setting initial position for text display; can be adjusted based on game needs
	mTextPosition.x = 50.0f;
	mTextPosition.y = 50.0f;

	mBall = std::make_shared<Ball>(exVector2{ 0.0f,0.0f }, exVector2{ 200.0f,400.0f }, 25.0f, exColor{ 180, 10, 10,255 }, false);
	mBall->BeginPlay();

	//exVector2 inSpawnLoc, exColor inColor, bool inHasGravity, bool inIsStatic, exVector2 inPoint1, exVector2 inPoint2
	mFloor1 = std::make_shared<Cube>(exVector2 {0.0f, 550.0f}, exColor{ 125, 10, 10, 255 }, false, true, exVector2 {50.0f, 10.0f}, exVector2 {750.0f, 50.0f});
	mFloor1->BeginPlay();

	mWall1 = std::make_shared<Cube>(exVector2{ 0.0f, 460.0f }, exColor{ 125, 125, 125, 255 }, false, true, exVector2{ 50.0f, 50.0f }, exVector2{ 100.0f, 100.0f });
	mWall1->BeginPlay();
	mWall2 = std::make_shared<Cube>(exVector2{ 650.0f, 460.0f }, exColor{ 125, 125, 125, 255 }, false, true, exVector2{ 50.0f, 50.0f }, exVector2{ 100.0f, 100.0f });
	mWall2->BeginPlay();
	mBreakable1 = std::make_shared<Cube>(exVector2{ 200.0f, 300.0f }, exColor{ 125, 10, 10, 255 }, false, true, exVector2{ 50.0f, 50.0f }, exVector2{ 100.0f, 100.0f });
	mBreakable1->BeginPlay();
	mBreakable2 = std::make_shared<Cube>(exVector2{ 250.0f, 300.0f }, exColor{ 125, 10, 10, 255 }, false, true, exVector2{ 50.0f, 50.0f }, exVector2{ 100.0f, 100.0f });
	mBreakable2->BeginPlay();	
	mBreakable3 = std::make_shared<Cube>(exVector2{ 300.0f, 300.0f }, exColor{ 200, 200, 0, 255 }, false, true, exVector2{ 50.0f, 50.0f }, exVector2{ 100.0f, 100.0f });
	mBreakable3->BeginPlay();
	mBreakable4 = std::make_shared<Cube>(exVector2{ 350.0f, 300.0f }, exColor{ 125, 10, 10, 255 }, false, true, exVector2{ 50.0f, 50.0f }, exVector2{ 100.0f, 100.0f });
	mBreakable4->BeginPlay();

}

//-----------------------------------------------------------------
// GetWindowName: returns the window name used by the game
// This name is used by the engine to title the window and can be used 
// throughout the game for display purposes.
//-----------------------------------------------------------------

const char* Cario::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
// GetClearColor: sets the background color for the game window
// - The color is set to a neutral grey using RGB values of 128.
// - This color is used to clear the screen before rendering each frame, 
//   ensuring a consistent background.
//-----------------------------------------------------------------

void Cario::GetClearColor(exColor& color) const
{
	color.mColor[0] = 74; // setting the clear color to a neutral grey
	color.mColor[1] = 118;
	color.mColor[2] = 202;
	color.mColor[3] = 100;
}

//-----------------------------------------------------------------
// OnEvent: processes incoming SDL events
// - Currently a placeholder for handling events like key presses or mouse movements.
// - This method can be extended to include specific event handling logic.
//-----------------------------------------------------------------

void Cario::OnEvent(SDL_Event* pEvent)
{
	// currently empty, but can be extended to handle specific events
}

//-----------------------------------------------------------------
// OnEventsConsumed: processes the state of keys after all events are handled
// - This method checks the current state of the keyboard and updates the flags
//   (mUp, mDown) based on whether specific keys are pressed.
//-----------------------------------------------------------------

void Cario::OnEventsConsumed()
{
	mInputManager.Update();
	int nKeys = 0;
	const Uint8* pState = SDL_GetKeyboardState(&nKeys); // getting the current state of the keyboard

	// updating movement flags based on the current key state
	mUp = pState[SDL_SCANCODE_UP];
	mDown = pState[SDL_SCANCODE_DOWN];
}

//-----------------------------------------------------------------
// Run: main game loop logic
// - Updates the position of text on the screen based on user input.
// - Renders the text at the new position with a specific color.
// - Checks if the Ball object has a render component and, if so, 
//   delegates the rendering responsibility to that component.
//-----------------------------------------------------------------

void Cario::Run(float fDeltaT)
{
	// store all of the characters components for easy access later on 
	std::shared_ptr<TransformComponent> charTransform = mBall->FindComponentOfType<TransformComponent>(); 
	std::shared_ptr<CircleColliderComponent> charPhysics = mBall->FindComponentOfType<CircleColliderComponent>();
	exVector2 charVelocity = charPhysics->GetVelocity();
	
	exVector2 accumulatedVelocity = {0.0f, 0.0f}; 

	charPhysics->SetVelocity(charVelocity);
	// drawing the text at the current position with a specific color
	exColor c;
	c.mColor[0] = 25;   // green color for text
	c.mColor[1] = 255;
	c.mColor[2] = 0;
	c.mColor[3] = 255;
	
	// updating text position based on input flags
	if (mInputManager.GetState().IsAttack())
	{
		
	}

	if (mInputManager.GetState().IsJump() )
	{
		// Mark the ball as no longer grounded
		mBall->SetGrounded(false);


		// Set an upward velocity to initiate the jump
		accumulatedVelocity.y = -mBall->GetJumpHeight(); // Negative to move upward in most 2D coordinate systems
		

	}

	if (mInputManager.GetState().IsDuck())
	{
		accumulatedVelocity.y += 8;
	}

	if (mInputManager.GetState().IsForward())
	{
		accumulatedVelocity.x += 4;
	}

	if (mInputManager.GetState().IsBack())
	{
		accumulatedVelocity.x -= 4;
	}

	charPhysics->SetVelocity(accumulatedVelocity); // Apply all velocity accumulated here

	if (mInputManager.GetState().IsUse())
	{
		mEngine->DrawText(mFontID, exVector2(10, 185), "Use", c, 0);
	}

	if (mInputManager.GetState().IsCancel())
	{
		mEngine->DrawText(mFontID, exVector2(10, 220), "Cancel", c, 0);
	}


	//mEngine->DrawText(mFontID, mTextPosition, "Super", c, 0); // rendering the text with the font and position
	//mEngine->DrawText(mFontID, (mTextPosition + exVector2 {0.0f, 30.0f}), "Cario", c, 0); // rendering the text with the font and position
	
	RENDER_ENGINE.Render(mEngine);
	PHYSICS_ENGINE.SimulatePhysics();
}
