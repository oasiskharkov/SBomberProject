#pragma once

#include "DynamicObject.h"

class Plane : public DynamicObject
{
public:
    void Draw() const override;
    void ChangePlaneY(double dy) { yDirection += dy; }
private:
};

