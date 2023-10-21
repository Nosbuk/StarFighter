#include "Entity.hpp"

#pragma once

class Alive : public Entity
{
public:
    int HP;
    int HPMax;

    void setHP(int hp)
    {
        HP = hp;
    }
    int getHP()
    {
        return HP;
    }
    int getHPMax()
    {
        return HPMax;
    }
    void takeHit()
    {
        HP--;
    }
};
