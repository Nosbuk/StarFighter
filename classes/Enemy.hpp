#include "Alive.hpp"

#pragma once

using namespace sf;

class Enemy : public Alive
{
private:
    using Alive::HP;

public:
    Enemy(Texture *texture, Vector2u windowSize)
    {
        // rand() returns from 0 to 99 so HPMax of each enemy varies from 1 to 3
        this->HPMax = rand() % 3 + 1;
        this->HP = this->HPMax;

        // dereference of pointer pointing to texture
        this->shape.setTexture(*texture);
        this->shape.setScale(0.3f, 0.3f);
        this->velocity = 2.f;
        this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % (windowSize.y - 150) + this->shape.getGlobalBounds().height);
    }

    ~Enemy()
    {
    }
};
