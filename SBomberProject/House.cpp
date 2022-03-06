#include <iostream>

#include "House.h"
#include "MyTools.h"

House::House()
{
   memset((char*)look, ' ', houseWidth * houseHeight);
}

House::House(const House& house)
{
   SetPos(house.GetX(), house.GetY());
   SetWidth(house.GetWidth());
   memcpy(look, house.look, houseWidth * houseHeight);
}

House& House::operator = (const House& house)
{
   if (this != &house)
   {
      SetPos(house.GetX(), house.GetY());
      SetWidth(house.GetWidth());
      memcpy(look, house.look, houseWidth * houseHeight);
   }
   return *this;
}

bool House::isInside(double x1, double x2) const
{
   const double XBeg = x + 2;
   const double XEnd = x + width - 1;

   if (x1 < XBeg && x2 > XEnd)
   {
      return true;
   }

   if (x1 > XBeg && x1 < XEnd)
   {
      return true;
   }

   if (x2 > XBeg && x2 < XEnd)
   {
      return true;
   }

   return false;
}

void House::Draw() const
{
   MyTools::SetColor(MyTools::CC_Yellow);
   for (size_t i = 0; i < houseHeight; ++i)
   {
      MyTools::GotoXY(x, y - i);
      for (size_t j = 0; j < houseWidth; ++j)
      {
         std::cout << look[houseHeight - i - 1][j];
      }
   }
}

std::shared_ptr<DestroyableGroundObject> House::Clone() const
{
   return std::make_shared<House>(*this);
}
