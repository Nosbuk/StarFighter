#include "Alive.hpp"
#include "Bullet.hpp"

#pragma once

using namespace sf;

class Player : public Alive
{
private:
    using Alive::HP;

public:
    std::vector<Bullet> bullets;
    // Player constructor
    Player()
    {
        // Player stats
        this->HPMax = 10;
        this->HP = this->HPMax;
        this->velocity = 25.f;
        // dereference of pointer pointing to texture
        this->shape.setScale(0.2f, 0.2f);
        this->shape.setRotation(90.f);
        this->shape.setPosition(90.f, 150.f);
    }
    void setTexture(Texture *texture)
    {
        this->shape.setTexture(*texture);
    }

    ~Player() {}
};
