#include <iostream>

#include "House.h"
#include "MyTools.h"

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
   MyTools::GotoXY(x, y - 5);
   std::cout << "  ########  ";
   MyTools::GotoXY(x, y - 4);
   std::cout << "##        ##";
   MyTools::GotoXY(x, y - 3);
   std::cout << "############";
   MyTools::GotoXY(x, y - 2);
   std::cout << "#          #";
   MyTools::GotoXY(x, y - 1);
   std::cout << "#          #";
   MyTools::GotoXY(x, y);
   std::cout << "############";
}