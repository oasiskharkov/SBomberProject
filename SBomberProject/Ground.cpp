#include <iostream>
#include <memory>

#include "MyTools.h"
#include "Ground.h"

//==================================================================================================

void Crater::Draw() const
{
   if (width == SMALL_CRATER_SIZE) // Рисование воронки в 9 символов шириной
   {
      MyTools::GotoXY(x - 4, y + 1);
      std::cout << "==     ==";
      MyTools::GotoXY(x - 2, y + 2);
      std::cout << "=====";
   }
}

bool Crater::isInside(double xn) const
{
   const double size_2 = width / 2.0;
   if (int(xn) > int(x - size_2) && xn <= int(x + size_2))
   {
      return true;
   }

   return false;
}

//==================================================================================================

void Ground::Draw() const
{
   MyTools::SetColor(MyTools::CC_Green);

   const size_t bufSize = width + 1;
   auto deleter = [](char* p) { delete[] p; };
   std::unique_ptr<char, decltype(deleter)> buf{ new (std::nothrow) char[bufSize], deleter };

   *(buf.get() + bufSize - 1) = '\0';
   if (buf == nullptr)
   {
      return;
   }

   if (vecCrates.size() == 0)
   {
      MyTools::GotoXY(x, y);
      memset(buf.get(), '=', bufSize);
      *(buf.get() + bufSize - 1) = '\0';
      std::cout << buf;
   }
   else
   {
      const size_t X = size_t(x);
      char c;
      for (size_t i = X; i < width + X; i++)
      {
         c = (isInsideAnyCrater((double)i)) ? ' ' : '=';
         *(buf.get() + i - X) = c;
      }

      MyTools::GotoXY((double)X, y);
      *(buf.get() + bufSize - 1) = '\0';
      std::cout << buf;

      for (size_t i = 0; i < vecCrates.size(); i++)
      {
         vecCrates[i].Draw();
      }
   }
}

bool Ground::isInsideAnyCrater(double x) const
{
   bool isInside = false;
   for (size_t i = 0; i < vecCrates.size(); i++)
   {
      if (vecCrates[i].isInside(x))
      {
         isInside = true;
         break;
      }
   }

   return isInside;
}

void Ground::AddCrater(double xn)
{
   Crater cr;
   cr.SetPos(int(xn), y);
   cr.SetWidth(SMALL_CRATER_SIZE);
   vecCrates.emplace_back(cr);
}