#include <conio.h>
#include <thread>
#include <chrono>

#include "SBomber.h"
#include "MyTools.h"
#include <crtdbg.h>

using namespace std;

//========================================================================================================================

int main(void)
{
   // Check for memory leak if debug build
#if defined( DEBUG ) | defined( _DEBUG )
   _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

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

    return 0;
}
