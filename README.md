<p align="center"> 
    <img src="./ReadMeAssets/GameEngineHeader.gif" alt="Custom Game Engine Logo" width="200"> 
</p> 
<h1 align="center">Custom 2D Game Engine</h1> 
<p align="center"> A 2D game engine built from scratch in C++ and SDL, aimed at mimicking the core architecture of popular engines like Unity and Unreal Engine but specifically tailored for 2D games. </p> 
<h2>Installation</h2>
<p>To set up the project locally, follow these steps:</p> 
<pre> <code> 
  # git clone https://github.com/AlexBuzmion/Game-Custom-GameEngine-.git 
  # cd CustomGameEngine 
  # Build the project using your C++ IDE (Visual Studio, etc.) 
  # Make sure to have SDL2 installed 
</code> </pre> 
<h2>Overview of the Engine</h2> 
<p> This custom 2D game engine demonstrates my proficiency in C++ and SDL, designed to provide full control over the game loop, inputs, rendering, and physics. It's still a work in progress, with future plans to incorporate more complex systems and sprite-based rendering. </p>
<p> The engine follows an Entity-Component-System (ECS) architecture, allowing modularity and flexibility. Each game object (or entity) contains multiple components that define its behavior, making it easier to scale and extend the engine. </p>
<p> The current features include: </p> 
<ul> 
  <li><strong>GameObject and Component System:</strong> Each GameObject can have various components (e.g., Physics, Rendering, Transform) that determine its behavior.</li>
  <li><strong>Custom Physics Engine:</strong> Includes collision detection for circles and boxes, leveraging math-based algorithms to handle interactions and broadcasting collision events to registered objects.</li> 
  <li><strong>Input System:</strong> Captures and handles keyboard inputs for controlling player movement and interactions.</li>
  <li><strong>Render Engine:</strong> Draws shapes like circles and boxes directly to the screen, with plans to support sprites and more complex visuals in future updates.</li> 
</ul> 

<h2>About the Project</h2> 
<p> This game engine is a solo project aimed at replicating the foundational structure of major game engines like Unity and Unreal Engine. The main goal is to gain an in-depth understanding of game development concepts by building all core components from scratch using C++ and SDL. </p> 
<ul> 
  <li><strong>GameObject Framework:</strong> The engine's core revolves around GameObjects, each containing components that dictate their behavior, similar to actors in Unity/Unreal.</li>
  <li><strong>Physics Engine:</strong> Includes circle-circle and box-circle collision detection, with plans to expand to polygonal collision handling.</li> 
  <li><strong>Input Management:</strong> Allows for real-time keyboard input, mapped to player actions and future game elements.</li> 
  <li><strong>Rendering System:</strong> Currently rendering basic 2D shapes (circles, boxes) with future plans for sprite integration.</li> 
</ul> 

<p> As the project evolves, I plan to implement additional components like animation systems, sound management, and sprite handling for visual assets. </p> 

<!-- PROJECT FILES DESCRIPTION --> 
<h2 id="project-files-description"> :floppy_disk: Project Files Description</h2>

###Core Systems
|File	| Description|
|-----|------------|
|GameObject.h	|Defines GameObjects and their component management.|
|Component.h	|Base class for all components (Physics, Render, etc.).|
|PhysicsEngine.cpp	|Handles all physics calculations and collision detection.|
|RenderEngine.cpp	|Manages rendering objects on screen using SDL.|
|InputManager.cpp	|Manages input handling from the user (e.g., keyboard).|

<h2>Usage</h2> 
<p>Build the project, and test the example game loop included to see the engine in action. Control your character using the arrow keys, and experiment with the physics and collision systems already implemented.</p> 

<h2>Future Plans</h2> 
<p>In the near future, I plan to expand the engine's capabilities with the following features:</p> 
<ul> 
  <li><strong>Sprite Rendering:</strong> Implement a system for rendering sprites, allowing for more complex and visually appealing game assets.</li> 
  <li><strong>Animation System:</strong> Build an animation component to handle sprite-based animations and smooth transitions between frames.</li> 
  <li><strong>Expanded Physics:</strong> Add support for more complex collision shapes like polygons, and optimize the physics system for performance.</li> 
  <li><strong>Audio Engine:</strong> Introduce sound effects and background music through SDL's audio features.</li> 
  <li><strong>Level Editor:</strong> Create a simple in-engine level editor for easier testing and game design.</li> 
</ul>
<h2>Contributing</h2> 
<p>Fork the repository and submit a pull request if you would like to contribute or suggest improvements.</p> 

<h2>License</h2> 
<p>This project is licensed under the <a href="LICENSE">MIT License</a>.</p> 

<h2>Screenshots</h2> 
