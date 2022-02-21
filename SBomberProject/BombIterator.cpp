#include "BombIterator.h"
#include <string>

BombIterator::BombIterator(const std::vector<std::shared_ptr<DynamicObject>>& vec) :
   dynamicObjects{ vec },
   index{ -1 },
   ptr{ nullptr }
{
   ++(*this);
}

void BombIterator::reset()
{
   index = -1;
   ptr = nullptr;
}

BombIterator& BombIterator::operator++ () // префиксный инкремент
{
   ++index;

   if (index == INT_MIN)
   {
      throw std::out_of_range("Incorrect Index: " + std::to_string(index));
   }

   for (; index < dynamicObjects.size(); ++index)
   {
      BombDecorator* pBomb = dynamic_cast<BombDecorator*>(dynamicObjects[index].get());
      if (pBomb != nullptr)
      {
         DynamicObject* dObj = dynamicObjects[index].get();
         ptr = &dObj;
         break;
      }
   }

   if (index == dynamicObjects.size())
   {
      index = -1;
      ptr = nullptr;
   }

   return *this;
}

BombDecorator*& BombIterator::operator * ()
{
   auto bomb = dynamic_cast<BombDecorator*>(dynamicObjects.at(index).get());
   if (bomb != nullptr)
   {
      return bomb;
   }
   throw std::logic_error("Incorrect object type");
}

bool BombIterator::operator == (const BombIterator& it) const
{
   if (index == it.index && ptr == it.ptr && dynamicObjects == it.dynamicObjects)
   {
      return true;
   }
   return false;
}

bool BombIterator::operator != (const BombIterator it) const
{
   return !(*this == it);
}

BombIterator BombIterator::begin()
{
   BombIterator it(dynamicObjects);
   return it;
}

BombIterator BombIterator::end()
{
   BombIterator it(dynamicObjects); 
   it.reset(); 
   return it;
}
