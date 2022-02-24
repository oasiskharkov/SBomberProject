#include <iostream>

#include "Plane.h"
#include "MyTools.h"

void Plane::Draw() const
{
   DrawTail();
   DrawWing();
   DrawBody();
}

void Plane::Accept(const Visitor& v)
{
   v.log(*this);
}

void ColorPlane::DrawTail() const
{
   MyTools::SetColor(MyTools::CC_Yellow);
   MyTools::GotoXY(x - 2, y - 1);
   std::cout << "===";
}

void ColorPlane::DrawWing() const
{
   MyTools::SetColor(MyTools::CC_Green);
   MyTools::GotoXY(x + 3, y - 1);
   std::cout << "\\\\\\\\";
   MyTools::GotoXY(x + 3, y + 1);
   std::cout << "////";
}

void ColorPlane::DrawBody() const
{
   MyTools::SetColor(MyTools::CC_Red);
   MyTools::GotoXY(x, y);
   std::cout << "=========>";
}

void BigPlane::DrawTail() const
{
   MyTools::SetColor(MyTools::CC_LightBlue);
   MyTools::GotoXY(x - 1, y - 1);
   std::cout << "===";
   MyTools::GotoXY(x - 2, y - 2);
   std::cout << "==";
}

void BigPlane::DrawWing() const
{
   MyTools::GotoXY(x + 3, y - 3);
   std::cout << "\\\\";
   MyTools::GotoXY(x + 4, y - 2);
   std::cout << "\\\\\\";
   MyTools::GotoXY(x + 5, y - 1);
   std::cout << "\\\\\\\\";
   MyTools::GotoXY(x + 5, y + 1);
   std::cout << "////";
   MyTools::GotoXY(x + 4, y + 2);
   std::cout << "///";
   MyTools::GotoXY(x + 3, y + 3);
   std::cout << "//";
}

void BigPlane::DrawBody() const
{
   MyTools::GotoXY(x, y);
   std::cout << "DDDDDDDDDDDDDD>";
}
