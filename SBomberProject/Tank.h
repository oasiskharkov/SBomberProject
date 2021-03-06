#pragma once

#include "DestroyableGroundObject.h"

#include <array>

class Mediator;

namespace 
{
   std::array<std::string, 5> messages 
   {
      "Stinky",
      "Dummbas",
      "Asshole",
      "Stupid",
      "Motherfucker"
   };

   constexpr float sendMessageTime = 2.f;
}

class Tank : public DestroyableGroundObject
{
public:
   Tank(Mediator* med);
   Tank(const Tank& tank);
   Tank& operator = (const Tank& tank);
   bool isInside(double x1, double x2) const override;
   inline uint16_t GetScore() const override { return score; }
   void Draw() const override;
   void Update(float dt);
   std::shared_ptr<DestroyableGroundObject> Clone() const override;
private:
   const uint16_t score = 30;
   float time;
   Mediator* mediator;
};

