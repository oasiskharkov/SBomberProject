#pragma once

#include <vector>
#include <memory>

#include "BombDecorator.h"

class BombIterator
{
public:
   BombIterator(const std::vector<std::shared_ptr<DynamicObject>>& vec);
   void reset();

   BombIterator& operator ++ ();
   BombIterator& operator ++ (int);
   BombDecorator*& operator * ();

   bool operator == (const BombIterator& it) const;
   bool operator != (BombIterator it) const;
   
   BombIterator begin();
   BombIterator end();
private:
   std::vector<std::shared_ptr<DynamicObject>> dynamicObjects;
   int index;
};