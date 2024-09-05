//
// * BrickBrinBall 
// * Brick Breaker meets Pinball
//
// + Game.h
// definition of BrickBrinBall, an implementation of exGameInterface
//

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/Singletons/InputManager.h"
#include <memory>
#include "Game/Public/Components/PhysicsComponents/CircleColliderComponent.h"

class Ball;
class Cube;
//-----------------------------------------------------------------
// BrickBrinBall Class
// This class implements the core game logic by interfacing with the engine.
// It handles initialization, event processing, and the game loop, ensuring
// that all game elements are updated and rendered each frame.
// The game combines mechanics from brick breaker and pinball, providing
// a dynamic and engaging gameplay experience.
//-----------------------------------------------------------------

class Cario : public exGameInterface
{
public:

    // sets up initial game state and loads necessary resources.
    Cario();

    // ensures proper cleanup of resources when the game ends.
    virtual ~Cario();

    // links the game with the engine, loads resources like fonts, and sets initial game states.
    virtual void Initialize(exEngineInterface* pEngine);

    // provides the window title for display.
    virtual const char* GetWindowName() const;

    // defines the background color used to clear the screen each frame.
    virtual void GetClearColor(exColor& color) const;

    // processes player inputs for responding to user actions.
    virtual void OnEvent(SDL_Event* pEvent);

    // consolidates input handling after events are processed, ensuring game state is updated based on inputs.
    virtual void OnEventsConsumed();

    // core game logic: updates game entities, checks conditions, and renders the frame.
    virtual void Run(float fDeltaT);

private:

    exEngineInterface* mEngine; // reference to the engine for game-engine interactions.

    int mFontID;                // font ID used for rendering text.

    InputManager mInputManager;
    bool mUp;                   // flags to track the state of key presses for movement.
    bool mDown;

    exVector2 mTextPosition;    // current position of the text, used for dynamic on-screen placement.

    std::shared_ptr<Ball> mBall;// shared pointer to a Ball object, representing a game entity.
    std::shared_ptr<Cube> mFloor1;
    std::shared_ptr<Cube> mWall1;
    std::shared_ptr<Cube> mWall2;
    std::shared_ptr<Cube> mBreakable1;
    std::shared_ptr<Cube> mBreakable2;
    std::shared_ptr<Cube> mBreakable3;
    std::shared_ptr<Cube> mBreakable4;

};
