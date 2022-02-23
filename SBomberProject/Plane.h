#pragma once

#include "DynamicObject.h"

class Plane : public DynamicObject
{
public:
    void Draw() const override;
    void ChangePlaneY(double dy) { yDirection += dy; }
    void Accept(const Visitor& v) override;

    virtual void DrawTail() const = 0;
    virtual void DrawWing() const = 0;
    virtual void DrawBody() const = 0;
};

class ColorPlane final : public Plane
{
public:
   void DrawTail() const override;
   void DrawWing() const override;
   void DrawBody() const override;
};

class BigPlane final : public Plane
{
public:
   void DrawTail() const override;
   void DrawWing() const override;
   void DrawBody() const override;
};
