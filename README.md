# Game-Engine
This is a simple game engine written in C++ which currently doesn't have a name because I'm not all that creative. Does anyone have any ideas? I'm not building it so I can make a game. I'm building it to learn about Game Engines. I don't want any collaborators but ideas and suggestions are welcome.

## Current progress

I replaced my rendering engine with Ogre3D 1.9!!!

A lot of code will need to be rewritten.

I'd just gotten the hang of OpenGL and it was all for nothing. Deleting all of that code was really emotional. But Ogre3D is better! 

## Plans

### UI
The UI system will be rendered using the Ogre3D overlay system.

There are a few more UI elements that need to be implemented. These include

| Name                     | HTML                     | Comment                                                   |
|--------------------------|--------------------------|-----------------------------------------------------------|
| Slider                   | `<input type="range" />` | Will require additional features in the `UI::Input` class |
| Text input box           | `<input type="text" />`  | Will require additional features in the `UI::Input` class |
| Multiline text input box | `<textarea></textarea>`  | I'm not sure if this will ever be needed in a game        |
| Caption                  | `<span></span>`          | Implemented but might need work                           |
| Paragraph                | `<p></p>`                | Like caption but multiple lines                           |

and maybe a few more.

The layout will be represented as an XML document. I haven't thought about it much but it may resemble HTML with inline CSS. UI animations will be controlled by ChaiScript. The interface in which this is done may be similar to the JavaScript DOM but we'll see.

### Scripting
I plan to use the ChaiScript scripting language for scripting. I'll use ChaiScript for controlling animations in the UI system.

### Physics
I plan to use the Bullet Physics library for physics. I haven't really thought about Physics and I haven't looked at the Bullet documentation yet. I think I'll do this after I feel the UI system is stable. 
