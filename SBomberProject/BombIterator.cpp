#include "BombIterator.h"
#include <string>
#include <typeinfo>

BombIterator::BombIterator(const std::vector<std::shared_ptr<DynamicObject>>& vec) :
   dynamicObjects{ vec },
   index{ -1 }
{
   ++(*this);
}

void BombIterator::reset()
{
   index = -1;
}

BombIterator& BombIterator::operator ++ () // префиксный инкремент
{
   ++index;

   if (index == INT_MIN)
   {
      throw std::out_of_range("Incorrect Index: " + std::to_string(index));
   }

   for (; index < dynamicObjects.size(); ++index)
   {
      if(typeid(BombDecorator) == typeid(*dynamicObjects[index].get()))
      {
         DynamicObject* dObj = dynamicObjects[index].get();
         break;
      }
   }

   if (index == dynamicObjects.size())
   {
      index = -1;
   }

   return *this;
}

BombIterator& BombIterator::operator ++ (int) // постфиксный инкремент
{
   auto it = *this;
   ++(*this);
   return it;
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
   if (index == it.index && dynamicObjects == it.dynamicObjects)
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
