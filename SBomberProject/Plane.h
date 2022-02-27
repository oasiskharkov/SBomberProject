#pragma once

#include "DynamicObject.h"

class Plane : public DynamicObject
{
public:
    void Draw() const override;
    void ChangePlaneY(double dy) { yDirection += dy; }
    void Accept(const Visitor& v) override;

    virtual void DrawTail() const;
    virtual void DrawWing() const;
    virtual void DrawBody() const;
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
