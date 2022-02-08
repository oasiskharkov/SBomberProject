#include <iostream>

#include "Plane.h"
#include "MyTools.h"

void Plane::Draw() const
{
   MyTools::SetColor(MyTools::CC_LightBlue);
   MyTools::GotoXY(x, y);
   std::cout << "=========>";
   MyTools::GotoXY(x - 2, y - 1);
   std::cout << "===";
   MyTools::GotoXY(x + 3, y - 1);
   std::cout << "\\\\\\\\";
   MyTools::GotoXY(x + 3, y + 1);
   std::cout << "////";
}
