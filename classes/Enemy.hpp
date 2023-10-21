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
        this->HPMax = rand() % 3 + 1;
        this->HP = this->HPMax;

        this->shape.setTexture(*texture);
        this->shape.setScale(0.3f, 0.3f);
        this->velocity = 2.f;
        this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % (windowSize.y - 150) + this->shape.getGlobalBounds().height);
    }

    ~Enemy()
    {
    }
};
