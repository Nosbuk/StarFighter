#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(640, 400), "StarFighter", Style::Default);
    window.setFramerateLimit(60);

    // Vector with two floats | .f used for faster compilation
    RectangleShape rectangle(Vector2f(50.f, 50.f));
    rectangle.setPosition(Vector2f(400.f, 200.f));
    rectangle.setFillColor(Color(100, 200, 150, 200));

    CircleShape circle(50);
    circle.setPosition(Vector2f(0.f, 0.f));
    circle.setFillColor(Color::Green);

    CircleShape triangle;
    triangle.setRadius(50.f);
    triangle.setPointCount(3);
    triangle.setFillColor(Color::Cyan);
    triangle.setOutlineThickness(5.f);
    triangle.setOutlineColor(Color::Blue);

    Vertex line[] = {Vertex(Vector2f(100.f, 400.f)),
                     Vertex(Vector2f(50.f, 100.f))};

    ConvexShape convex;
    convex.setPosition(Vector2f(400.f, 100.f));
    convex.setPointCount(5);
    convex.setPoint(0, Vector2f(0.f, 0.f));
    convex.setPoint(1, Vector2f(150.f, 10.f));
    convex.setPoint(2, Vector2f(120.f, 90.f));
    convex.setPoint(3, Vector2f(30.f, 100.f));
    convex.setPoint(4, Vector2f(0.f, 50.f));

    // Main event loop
    while (window.isOpen())
    {
        // Create new instance of Event
        Event event;

        // User events handler - "event polling" - like event bubling in js but on window object
        while (window.pollEvent(event))
        {
            // Close window handler
            if (event.type == Event::Closed)
                window.close();
        }

        // Update states
        circle.move(0.5f, 0.1f);
        rectangle.move(0.1f, 0.3f);

        circle.rotate(5.f);
        rectangle.rotate(5.f);

        // Clear current frame
        window.clear();

        // Draw new frame - from updated states
        window.draw(circle);
        window.draw(rectangle);

        window.draw(line, 2, Lines);
        window.draw(triangle);
        window.draw(convex);

        // Render next frame
        window.display();
    }

    return 0;
}
