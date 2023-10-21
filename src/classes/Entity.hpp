#pragma once

using namespace sf;

class Entity
{
public:
    Sprite shape;
    float velocity;

    void moveUp()
    {
        this->shape.move(0.f, -velocity);
    }
    void moveDown()
    {
        this->shape.move(0.f, velocity);
    }
    void moveLeft()
    {
        this->shape.move(-velocity, 0.f);
    }
    void moveRight()
    {
        this->shape.move(velocity, 0.f);
    }
    Vector2f getPosition()
    {
        return this->shape.getPosition();
    }
    FloatRect getGlobalBounds()
    {
        return this->shape.getGlobalBounds();
    }
};
