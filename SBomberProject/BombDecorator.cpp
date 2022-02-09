#include "BombDecorator.h"
#include "MyTools.h"

void BombDecorator::Draw() const
{
   bomb.Draw();
   // Некоторое изменение внешнего вида бомбы
   MyTools::GotoXY(bomb.GetX(), bomb.GetY() - 1);
   std::cout << "|";
}

void BombDecorator::Move(uint64_t time)
{
   time *= 2;
   bomb.Move(time);
}

void BombDecorator::SetPos(double nx, double ny)
{
   bomb.SetPos(nx, ny);
}

double BombDecorator::GetY() const
{
   return bomb.GetY();
}

double BombDecorator::GetX() const
{
   return bomb.GetX();
}

void BombDecorator::SetWidth(uint16_t width)
{
   bomb.SetWidth(width);
}

uint16_t BombDecorator::GetWidth() const
{
   return bomb.GetWidth();
}

void BombDecorator::SetSpeed(double sp)
{
   bomb.SetSpeed(sp);
}

void BombDecorator::SetDirection(double dx, double dy)
{
   bomb.SetDirection(dx, dy);
}
