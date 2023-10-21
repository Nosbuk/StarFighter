# Technical Documentation: Project "StarFighter"

## Project Description

"StarFighter" is a 2D computer game developed in C++ and published on GitHub. This documentation aims to present the structure of the source code, its key components, and the main project objectives.

## Project Structure

1. **Source Code**: The main source code of the project is located in the `src/` directory. It is divided into classes responsible for all the objects appearing on the screen.

2. **External Libraries**: The project utilizes the following components of the SFML library: `-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network`. Some are redundant but are included for future development.

3. **Resources**: All game resources, such as textures and fonts, are stored in the `assets/` directory.

## Main Components

1. **Game**: The main object responsible for executing the `run()` method, in which the main loop for rendering successive frames is executed.

2. **Entity**: An object containing the logic of geometry and movement. All other objects, except for `Game`, inherit all methods and properties from this class.

3. **Alive**: An object containing the logic of health points (`HP`) and methods to manipulate this value. The `Enemy` and `Player` classes inherit from it.

4. **Player**: An object containing the logic and properties of the player's character, as well as a vector storing all bullets fired by the player.

5. **Enemy**: An object containing the logic and properties of enemy characters.

6. **Bullet**: An object containing the logic and properties of bullets fired by the player.

## Compilation and Execution Instructions

1. Download HomeBrew: [https://brew.sh/](https://brew.sh/)

2. In the terminal, type: `brew install sfml` (or `apt get sfml` for the Linux system).

3. To compile and run the game (requires g++, which is available in the Xcode SDK), use the following command:

```bash
g++ ./src/main.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include -o StarFighter -L/usr/local/Cellar/sfml/2.5.1_2/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network && ./StarFighter
```
