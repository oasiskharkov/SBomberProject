#include "Bomb.h"
#include "MyTools.h"

void Bomb::Draw() const
{
   MyTools::SetColor(MyTools::CC_LightMagenta);
   MyTools::GotoXY(x, y);
   std::cout << "*";
}

void Bomb::Accept(const Visitor& v)
{
   v.log(*this);
}
