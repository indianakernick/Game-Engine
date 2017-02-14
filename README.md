# Game-Engine
This is a simple game engine written in C++ which currently doesn't have a name because I'm not all that creative. Does anyone have any ideas? I'm not building it so I can make a game. I'm building it to learn about Game Engines. I don't want any collaborators but ideas and suggestions are welcome.

The 3D engine uses OpenGL and supports skeletal animation. I'm still yet to create a good UI system. I've lost count of how many times I've deleted the whole thing and started again (I think it's about 6). The resource cache is at its 2nd iteration and still going strong. If you look a few commits back you can see some demos of the system.

This is engine is not ready for a game yet. I still need to integrate the physics engine. I plan to use Bullet. The 3D engine still needs work and I need to implement a few shaders.

I might be able to start making a game in about 6 months but even that seems ambitious because when I started this thing (Feb 2016) I thought it would be a year and its been a year (as of Feb 2017).

The input system hasn't really been used much so it might need a rewrite. The next iteration would be its 3rd (I think). I still need to build the animation system because at the moment, the skeletan animation only works because I have a global variable and an interface used by the Game View is used by the Renderer. Basically I hacked it together just to see something on the screen.

There's also the scripting language that needs to be integrated. I plan to use ChaiScript simply because it's really easy to use with C++. 

The design is lossly based on the one described in Game Coding Complete (4th edition) by Mike McShaffry and David "Rez" Graham but not so similar as I copy directly from the book.
