#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>
#include <cstdlib>

using namespace sf;

int main()
{

    RenderWindow window(VideoMode(640, 400), "StarFighter", Style::Default);
    window.setFramerateLimit(60);

    // Main event loop
    while (window.isOpen())
    {
        // Create new instance of Event
        Event event;

        // User events handler - "event polling" - like event bubling in js but on window object
        while (window.pollEvent(event))
        {
            // Close window handler
            if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                window.close();
        }

        if (Mouse::isButtonPressed(Mouse::Left))
            window.close();

        window.clear();

        window.display();
    }

    return 0;
}
