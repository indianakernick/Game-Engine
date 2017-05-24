# Game-Engine

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/dbaa9ac2d6694ed8bdbb0e6dee81d133)](https://www.codacy.com/app/kerndog73/Game-Engine?utm_source=github.com&utm_medium=referral&utm_content=Kerndog73/Game-Engine&utm_campaign=badger)

 
![Screenshot](https://preview.ibb.co/havsWQ/Demo.png)


This is a simple game engine written in C++ which currently doesn't have a name because I'm not all that creative. Does anyone have any ideas? I'm not building it so I can make a game. I'm building it to learn about Game Engines. I don't want any collaborators but ideas and suggestions are welcome.

## Dependencies

All of the dependencies (except for Ogre but thats included in the repo) can be installed with `brew`.

    brew install tinyxml2
    brew install boost
    brew install sdl2
    brew install glm

## Current progress

I recently dropped unicode support and decided that from now on I'm just going to use ASCII and English. ASCII is built right into C++ which is really convienient because I from Australia and English is my primary language. This project is just for learning. If it was any more than that then I might waste another month trying to get unicode and localized strings to work but I'd really like to move on. ASCII gets the job done!

## Plans

### UI
The UI system will be rendered using the Ogre3D overlay system.

There are a few more UI elements that need to be implemented. These include

| Name                     | HTML                     | Comment                                                   |
|--------------------------|--------------------------|-----------------------------------------------------------|
| Slider                   | `<input type="range" />` | Will require additional features in the `UI::Input` class |
| Text input box           | `<input type="text" />`  | Will require additional features in the `UI::Input` class |
| Multiline text input box | `<textarea></textarea>`  | I'm not sure if this will ever be needed in a game        |

and maybe a few more.

The layout will be represented as an XML document. I haven't thought about it much but it may resemble HTML with inline CSS. UI animations will be controlled by ChaiScript. The interface in which this is done may be similar to the JavaScript DOM but we'll see.

### Scripting
I plan to use the ChaiScript scripting language for scripting. I'll use ChaiScript for controlling animations in the UI system.

### Physics
I plan to use the Bullet Physics library for physics. I haven't really thought about Physics and I haven't looked at the Bullet documentation yet. I think I'll do this after I feel the UI system is stable. 
