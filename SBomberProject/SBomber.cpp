#include <conio.h>
#include <windows.h>

#include "SBomber.h"

SBomber::SBomber() :
   impl{ std::make_unique<SBomberImpl>() }
{
   
}

void SBomber::MoveObjects()
{
   impl->logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");

   for (size_t i = 0; i < impl->vecDynamicObj.size(); ++i)
   {
      if (impl->vecDynamicObj[i] != nullptr)
      {
         impl->vecDynamicObj[i]->Move(impl->deltaTime);
         impl->vecDynamicObj[i]->Accept(impl->logVisitor);
      }
   }
};

void SBomber::CheckObjects()
{
   impl->logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");

   impl->CheckPlaneAndLevelGUI();
   impl->CheckBombsAndGround();
};

bool SBomber::GetExitFlag() const
{
   return impl->exitFlag;
}

void SBomber::ProcessKBHit()
{
   int c = _getch();

   if (c == 224)
   {
      c = _getch();
   }

   impl->logger.WriteToLog(std::string(__FUNCTION__) + " was invoked. key = ", c);

   switch (c) {

   case 27: // esc
      impl->exitFlag = true;
      break;

   case 72: // up
      impl->FindPlane()->ChangePlaneY(-0.25);
      break;

   case 80: // down
      impl->FindPlane()->ChangePlaneY(0.25);
      break;

   case 'b':
      impl->DropBomb();
      break;

   case 'B':
      impl->DropBomb();
      break;

   default:
      break;
   }
}

void SBomber::DrawFrame()
{
   impl->logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");

   for (size_t i = 0; i < impl->vecDynamicObj.size(); ++i)
   {
      if (impl->vecDynamicObj[i] != nullptr)
      {
         impl->vecDynamicObj[i]->Draw();
      }
   }

   for (size_t i = 0; i < impl->vecStaticObj.size(); ++i)
   {
      if (impl->vecStaticObj[i] != nullptr)
      {
         impl->vecStaticObj[i]->Draw();
      }
   }

   GotoXY(0, 0);
   impl->fps++;

   impl->FindLevelGUI()->SetParam(impl->passedTime, impl->fps, impl->bombsNumber, impl->score);
}

void SBomber::TimeStart()
{
   impl->logger.WriteToLog(std::string(__FUNCTION__) + " was invoked");
   impl->startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
   impl->finishTime = GetTickCount64();
   impl->deltaTime = uint16_t(impl->finishTime - impl->startTime);
   impl->passedTime += impl->deltaTime;

   for (size_t i = 0; i < impl->vecStaticObj.size(); ++i)
   {
      if (typeid(Tank) == typeid(*impl->vecStaticObj[i].get()))
      {
         if (Tank* pTank = dynamic_cast<Tank*>(impl->vecStaticObj[i].get()))
         {
            pTank->Update(impl->deltaTime / 1000.f);
         }
      }
   }

   impl->mediator.Update(impl->deltaTime / 1000.f);

   impl->logger.WriteToLog(std::string(__FUNCTION__) + " deltaTime = ", (int)impl->deltaTime);
}
