#include "DestroyableGroundObject.h"
#include "BombDecorator.h"

bool DestroyableGroundObject::HandleInsideCheck(BombDecorator* bombDecorator) const
{
   const double size = bombDecorator->GetWidth();
   const double size_2 = size / 2;
   const double x1 = bombDecorator->GetX() - size_2;
   const double x2 = x1 + size;

   return isInside(x1, x2);
}
