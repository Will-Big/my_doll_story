#pragma once
#include "Object.h"


class Wall :
    public Object
{
public:
    void update() override;
    void render(HDC _dc) override;
   
public:
    Wall();
    ~Wall();
};

