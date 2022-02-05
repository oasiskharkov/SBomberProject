
#include <conio.h>
#include <thread>
#include <chrono>

#include "SBomber.h"
#include "MyTools.h"

using namespace std;

//========================================================================================================================

int main(void)
{
    MyTools::OpenLogFile("log.txt");

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

    MyTools::CloseLogFile();

    return 0;
}
