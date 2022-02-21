#include "HouseBuilder.h"
#include "House.h"

void HouseBuilderA::buildWalls(House& house)
{
   for (int i = 4; i < house.getHeight() - 1; ++i)
   {
      house.look[i][0] = '#';
      house.look[i][house.getWidth() - 1] = '#';
   }
}

void HouseBuilderA::buildFloor(House& house)
{
   for (int i = 0; i < house.getWidth(); ++i)
   {
      house.look[house.getHeight() - 1][i] = '#';
   }
}

void HouseBuilderA::buildCeil(House& house)
{
   for (int i = 0; i < house.getWidth(); ++i)
   {
      house.look[3][i] = '#';
   }
}

void HouseBuilderA::buildRoof(House& house)
{
   int j = 1;
   for (int i = 2; i > 0; --i)
   {
      house.look[i][j] = '#';
      house.look[i][house.getWidth() - j - 1] = '#';
      j++;
   }
   for (int j = 3; j < house.GetWidth() - 3; j++)
   {
      house.look[1][j] = '#';
   }
}

void HouseBuilderA::buildWindow(House& house)
{
   for (int j = 2; j < 5; ++j)
   {
      house.look[5][j] = '#';
      house.look[7][j] = '#';
   }
   house.look[6][2] = '#';
   house.look[6][4] = '#';
}

void HouseBuilderA::buildDoor(House& house)
{
   for (int i = 5; i < 9; ++i)
   {
      house.look[i][7] = '#';
      house.look[i][9] = '#';
   }
   house.look[5][8] = '#';
}

void HouseBuilderA::buildPipe(House& house)
{
   house.look[0][7] = '#';
}

void HouseBuilderB::buildWalls(House& house)
{
   for (int i = 4; i < house.getHeight() - 1; ++i)
   {
      house.look[i][0] = '#';
      house.look[i][house.getWidth() - 1] = '#';
   }
}

void HouseBuilderB::buildFloor(House& house)
{
   for (int i = 0; i < house.getWidth(); ++i)
   {
      house.look[house.getHeight() - 1][i] = '#';
   }
}

void HouseBuilderB::buildCeil(House& house)
{
   for (int i = 0; i < house.getWidth(); ++i)
   {
      house.look[3][i] = '#';
   }
}

void HouseBuilderB::buildRoof(House& house)
{
   int j = 1;
   for (int i = 2; i > 0; --i)
   {
      house.look[i][j] = '#';
      house.look[i][house.getWidth() - j - 1] = '#';
      j++;
   }
   for (int j = 3; j < house.GetWidth() - 3; j++)
   {
      house.look[1][j] = '#';
   }
}

void HouseBuilderB::buildDoor(House& house)
{
   for (int i = 5; i < 9; ++i)
   {
      house.look[i][4] = '#';
      house.look[i][7] = '#';
   }
   house.look[5][5] = '#';
   house.look[5][6] = '#';
}