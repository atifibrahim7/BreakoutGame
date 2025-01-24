# Overview

Attached is a small utility framework based on SFML 2.6 for drawing sprites to a window (the `sdk` folder)

Your task is to use this framework to implement a [Breakout](https://en.wikipedia.org/wiki/Breakout_(video_game))/[Arkanoid](https://en.wikipedia.org/wiki/Arkanoid)-like game
with a paddle bouncing a ball onto bricks to remove them. 

Do not use libraries not provided with the project.

Only the included graphical assets may be used, and only the provided
interface to rendering may be used - do not access SFML functions directly.


# Tech

It is recommended to build using CMake. SFML 2.6.1, dependency is bootstrapped to be downloaded to your project folder. See the _Getting Started_ section for bootstrapping you development environment.


# Specification

The window contains a score bar at the top and a game area below. The score
bar contains a score display and the player lives display. The game area
contains a paddle, a ball and a number of bricks that start out in a
rectangular layout near the top.

The paddle is confined to horizontal movements between the window edges along
the lower portion of the window, and is controlled by keyboard input on the A
and D keys.

The ball starts on the top of the paddle, and shoots upwards at the press of
the space bar. If the ball hits the side or top of the window, it bounces
against the surface it hit.

If the ball hits a brick, the brick disappears and the player is granted
points. If the ball hits the bottom of the screen, a player life is deducted
and the ball is reset to the paddle. If the player is out of lives, the
game area is replaced by a "Game Over" text, and the game can be restarted
by pressing the space bar.

If the ball hits the paddle, it bounces in a direction that depends on the
normal from the center of the paddle to the point of impact.


# Keep in mind

Try to design your implementation as if it was the base of a game, to be
extended further. Think about how you structure your code and what trade-offs
you are making.

# Testing
This project is set up to run unit tests with Catch2, a standard c++ testing framework.
You are welcome to add more tests for your code if you would like.
To run the test suite, either invoke the tests.exe (`.\build\test\Debug\tests.exe`) on your
terminal, or use the Cmake interpreted runner directly in VS Code.

You can _debug_ your tests (and the supplied test for the SDK) in VS Code using the included
_Run Catch2 test suite_ project.

# Getting started
This project has been tested on Windows, MacOS and Linux with Microsoft Visual Studio Code and some useful plugins. You don't have to work in VS Code, but it is the recommended way to not waste time on setting up your environment.

All platforms support [Visual Studio Code](https://code.visualstudio.com/) once installed, making sure you exposed `code` to you command line PATH, run this command for _Recommended and required VS Code extensions_:
```
code --install-extension ms-vscode.cmake-tools ms-vscode.cpptools
```

## Windows
On Windows, the recommended C++ compiler is MSVC included with [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/?cid=learn-onpage-download-cta)

[VS Code C++ development Readme for Windows](https://code.visualstudio.com/docs/cpp/config-msvc) 

To install **CMake** on Windows 10 or Windows 11, you likely want to use winget:

```
winget install kitware.cmake
```

Now:
1. Open the Project in VS Code
2. Go to the CMake pane in the left hand side toolbar
3. In the "Project Outline" view, Click _Configure all projects_, then _Build all projects_
4. Run the game, from the *Run and Debug* pane (Ctrl-Shift-D) using the supplied launch.json configuration for your platform - `Craftout - Windows`

> Note: you will be asked to select a compiler when running _CMake Configure_. The executable is expected to end up as linked in the `.vscode/launch.json` file

# Requirements / Software
CMake 3.8+
[Visual Studio Code](https://code.visualstudio.com/)

