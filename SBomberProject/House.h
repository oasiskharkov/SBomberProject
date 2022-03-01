#pragma once

#include "DestroyableGroundObject.h"

namespace
{
   constexpr size_t houseHeight = 10;
   constexpr size_t houseWidth = 12;
}

class House : public DestroyableGroundObject
{
public:
   House();
   House(const House& house);
   House& operator = (const House& house);
   bool isInside(double x1, double x2) const override;
   inline uint16_t GetScore() const override { return score; }
   friend class HouseBuilderA;
   friend class HouseBuilderB;
   size_t getHeight() const { return houseHeight; }
   size_t getWidth() const { return houseWidth; }
   void Draw() const override;
   std::shared_ptr<DestroyableGroundObject> Clone() const override;
private:
   const uint16_t score = 40;
   char look[houseHeight][houseWidth];
};

