#pragma once

#include "House.h"

class HouseBuilder
{
public:
   virtual ~HouseBuilder() = default;
   virtual void buildWalls(House& house) {};
   virtual void buildFloor(House& house) {};
   virtual void buildCeil(House& house) {};
   virtual void buildRoof(House& house) {};
   virtual void buildWindow(House& house) {};
   virtual void buildDoor(House& house) {};
   virtual void buildPipe(House& house) {};
};

// a house with pipe and with window 
class HouseBuilderA final : public HouseBuilder
{
public:
   void buildWalls(House& house) override;
   void buildFloor(House& house) override;
   void buildCeil(House& house) override;
   void buildRoof(House& house) override;
   void buildWindow(House& house) override;
   void buildDoor(House& house) override;
   void buildPipe(House& house) override;
};

/// a house without pipe and without window
class HouseBuilderB final : public HouseBuilder
{
public:
   void buildWalls(House& house) override;
   void buildFloor(House& house) override;
   void buildCeil(House& house) override;
   void buildRoof(House& house) override;
   void buildDoor(House& house) override;
};

class Director
{
public:
   static void createHouse(HouseBuilder& builder, House& house)
   {
      builder.buildCeil(house);
      builder.buildDoor(house);
      builder.buildWalls(house);
      builder.buildRoof(house);
      builder.buildPipe(house);
      builder.buildWindow(house);
      builder.buildFloor(house);
   }
};