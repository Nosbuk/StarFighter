#include "Entity.hpp"

#pragma once

using namespace sf;

class Bullet : public Entity
{
public:
    Bullet(Texture *texture, Vector2f position)
    {
        this->shape.setTexture(*texture);
        this->shape.setScale(0.09f, 0.09f);
        this->shape.setPosition(position);
        this->velocity = 25.f;
    }

    // Bullet destructor
    ~Bullet(){

    };
};
