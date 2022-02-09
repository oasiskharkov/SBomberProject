#pragma once

#include <vector>

#include "GameObject.h"

enum CraterSize
{
   SMALL_CRATER_SIZE = 9
};

class Crater : public GameObject
{
public:
   bool isInside(double xn) const;
   void Draw() const override;
private:
};

class Ground : public GameObject
{
public:
   Ground() = default;
   void Draw() const override;
   void AddCrater(double xn);
private:
   std::vector<Crater> vecCrates;
private:
   bool isInsideAnyCrater(double x) const;
};
