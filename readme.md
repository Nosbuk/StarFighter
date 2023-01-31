Author: Jakub Matwis

License: MIT

Mac instructions:

Donwload HomeBrew: https://brew.sh/

In terminal "run: brew install sfml" ("apt get sfml" for linux)

Run to compile & start the game (requires clang++, included in xcode sdk):

g++ main.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include -o StarFighter -L/usr/local/Cellar/sfml/2.5.1_2/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network && ./StarFighter

\*-I/ & -L flags may have different paths depending on user settings

To check your sfml paths run in terminal: "brew info sfml" ("dpkg -L sfml" for linux)

Assets downloaded from google images - no rights
