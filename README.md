# Game-Engine
This is a simple game engine written in C++ which currently doesn't have a name because I'm not all that creative. Does anyone have any ideas? I'm not building it so I can make a game. I'm building it to learn about Game Engines. I don't want any collaborators but ideas and suggestions are welcome.

## Current progress

The current UI system is my best yet. I'm very proud of it. Previous systems have had multiple inheritance and circular dependancies in an effort to remove duplicate code. Radio and Checkbox are very similar. Button and Checkbox are very similar. If I try to remove the duplication I end of with crappy code. In previous systems I tried to remove the duplicate code before I even wrote it so I could never got anything on the screen.

I very recently re-designed the way that the platform is encapculated in the Platform module. I'll still yet to move all of the `#ifdef USE_OPENGL` and `#ifdef USE_SDL` into the platform module. It's a big job and I'll have to do it in pieces so I don't break anything.

## Plans

### Typography
I've written a FreeType/OpenGL font loader and I plan to create a very simple renderer and text layout engine. As these are dependant on OpenGL, they'll be put into the Platform module as will the font loader.

### UI
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
