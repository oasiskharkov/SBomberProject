#include "BombDecorator.h"
#include "MyTools.h"

#include <algorithm>

void BombDecorator::Draw() const
{
   bomb.Draw();
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

void BombDecorator::Accept(const Visitor& v)
{
   bomb.Accept(v);
}

void BombDecorator::AddObserver(DestroyableGroundObject* observer)
{
   if (observer)
   {
      observers.emplace_back(observer);
   }
}

std::vector<DestroyableGroundObject*> BombDecorator::CheckDestroyableObjects()
{
   std::vector<DestroyableGroundObject*> vecDestroyableObjects;
   
   for (size_t i = 0; i < observers.size(); ++i)
   {
      if (observers[i]->HandleInsideCheck(this))
      {
         vecDestroyableObjects.emplace_back(observers[i]);
      }
   }

   for (const auto& dgo : vecDestroyableObjects)
   {
      auto it = std::remove_if(observers.begin(), observers.end(), [&](const auto& ob) { return ob == dgo; });
      observers.erase(it, observers.end());
   }

   return vecDestroyableObjects;
}
