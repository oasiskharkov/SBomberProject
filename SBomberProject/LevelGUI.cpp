#include <iostream>

#include "LevelGUI.h"
#include "MyTools.h"

LevelGUI::LevelGUI() :
   height{ 0 },
   passedTime{ 0 },
   fps{ 0 },
   bombsNumber{ 0 },
   score{ 0 } 
{
}

void LevelGUI::Draw() const
{
   MyTools::SetColor(MyTools::CC_White);

   MyTools::GotoXY(x, y);
   char* buf = new (std::nothrow) char[width + 1];
   if (buf == nullptr)
   {
      return;
   }
   memset(buf, '+', width);
   buf[width] = '\0';
   std::cout << buf;
   MyTools::GotoXY(x, y + height);
   std::cout << buf;
   delete[] buf;
   buf = nullptr;

   for (size_t i = size_t(y); i < height + y; i++)
   {
      MyTools::GotoXY(x, (double)i);
      std::cout << "+";
      MyTools::GotoXY(x + width - 1, (double)i);
      std::cout << "+";
   }

   MyTools::GotoXY(3, 1);
   std::cout << "FramePerSecond: " << static_cast<int>(fps / (passedTime / 1000.0));
   MyTools::GotoXY(25, 1);
   std::cout << "PassedTime: " << static_cast<int>(passedTime / 1000.0) << " sec";
   MyTools::GotoXY(46, 1);
   std::cout << "BombsNum: " << bombsNumber;
   MyTools::GotoXY(62, 1);
   std::cout << "Score: " << score;
}

void  LevelGUI::SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew)
{
   passedTime = passedTimeNew;
   fps = fpsNew;
   bombsNumber = bombsNumberNew;
   score = scoreNew;
}
