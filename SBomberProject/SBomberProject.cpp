#include <conio.h>
#include <crtdbg.h>
#include <thread>
#include <chrono>
#include <iostream>

#include "SBomber.h"
#include "MyTools.h"

using namespace std::chrono_literals;


int main(void)
{
   // Check for memory leak if debug build
#if defined( DEBUG ) | defined( _DEBUG )
   _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

   try
   {
      SBomber game;

      do {
         game.TimeStart();

         if (_kbhit())
         {
            game.ProcessKBHit();
         }
         std::this_thread::sleep_for(500ms);
         MyTools::ClrScr();

         game.DrawFrame();
         game.MoveObjects();
         game.CheckObjects();

         game.TimeFinish();

      } while (!game.GetExitFlag());
   }
   catch (const std::exception& ex)
   {
      std::cerr << ex.what() << std::endl;
   }

   return 0;
}
