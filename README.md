# Game-Engine

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/dbaa9ac2d6694ed8bdbb0e6dee81d133)](https://www.codacy.com/app/kerndog73/Game-Engine?utm_source=github.com&utm_medium=referral&utm_content=Kerndog73/Game-Engine&utm_campaign=badger)

 
![Screenshot](https://preview.ibb.co/havsWQ/Demo.png)


This is a simple game engine written in C++ which currently doesn't have a name because I'm not all that creative. Does anyone have any ideas? 

Collaborators are absolutly welcome! I'd really like to learn from other programmers and see what sort of solutions they have. Also feel free to critique the code, make suggestions, etc.

## Dependencies

All of the dependencies (except for Ogre but thats included in the repo) can be installed with `brew`.

    brew install yaml-cpp
    brew install tinyxml2
    brew install boost
    brew install sdl2
    brew install glm

## Current progress

At the moment I'm working on a simple game using the engine. The `GameLogic` is already implemented. Now I'm starting on the `GameView` which is a little bit trickier.

## Plans

Once I finish implementing the game, I might see what happens when I move some of the `GameLogic` into scripts. I'll use ChaiScript because it has a really nice C++ interface.
