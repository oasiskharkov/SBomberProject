#include <iostream>

#include "Tank.h"
#include "MyTools.h"
#include "Mediator.h"

Tank::Tank(Mediator* med) :
   time{ 0.f },
   mediator{ med }
{

}

bool Tank::isInside(double x1, double x2) const
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

void Tank::Draw() const
{
   MyTools::SetColor(MyTools::CC_Brown);
   MyTools::GotoXY(x, y - 3);
   std::cout << "    #####";
   MyTools::GotoXY(x - 2, y - 2);
   std::cout << "#######   #";
   MyTools::GotoXY(x, y - 1);
   std::cout << "    #####";
   MyTools::GotoXY(x, y);
   std::cout << " ###########";
}

void Tank::Update(float dt)
{
   time += dt;
   if (time > sendMessageTime)
   {
      size_t choice = rand() % messages.size();
      mediator->SendMessage(messages[choice]);
      time = 0.f;
   }
}