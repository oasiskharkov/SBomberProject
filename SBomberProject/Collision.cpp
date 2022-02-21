#include "Collision.h"
#include "Plane.h"
#include "LevelGUI.h"
#include "Ground.h"
#include "BombDecorator.h"
#include "DestroyableGroundObject.h"

void CollisionImplWin::CheckPlaneAndLevelGUI(std::function<Plane*()>&& findPlaneFunc, std::function<LevelGUI*()>&& findLevelGUIFunc, bool& exitFlag)
{
   if (findPlaneFunc()->GetX() > findLevelGUIFunc()->GetFinishX())
   {
      exitFlag = true;
   }
}

void CollisionImplWin::CheckBombsAndGround(std::function<std::vector<BombDecorator*>()>&& findBombsFunc, std::function<Ground* ()>&& findGroundFunc, 
   std::function<void(BombDecorator*)>&& checkDestroyableObjectsFunc, std::function<void(BombDecorator*)>&& deleteDynamicObjFunc)
{
   std::vector<BombDecorator*> vecBombs = findBombsFunc();
   Ground* pGround = findGroundFunc();
   const double y = pGround->GetY();
   for (size_t i = 0; i < vecBombs.size(); ++i)
   {
      if (vecBombs[i]->GetY() >= y)
      {
         pGround->AddCrater(vecBombs[i]->GetX());
         checkDestroyableObjectsFunc(vecBombs[i]);
         deleteDynamicObjFunc(vecBombs[i]);
      }
   }
}

void CollisionImplWin::CheckDestroyableObjects(std::function<std::vector<DestroyableGroundObject*>()>&& findDestroyableGroundObjectsFunc, 
   std::function<void(GameObject*)>&& deleteStaticObjFunc, int16_t& score, BombDecorator* pBomb)
{
   std::vector<DestroyableGroundObject*> vecDestroyableObjects = findDestroyableGroundObjectsFunc();
   const double size = pBomb->GetWidth();
   const double size_2 = size / 2;
   for (size_t i = 0; i < vecDestroyableObjects.size(); ++i)
   {
      const double x1 = pBomb->GetX() - size_2;
      const double x2 = x1 + size;
      if (vecDestroyableObjects[i]->isInside(x1, x2))
      {
         score += vecDestroyableObjects[i]->GetScore();
         deleteStaticObjFunc(vecDestroyableObjects[i]);
      }
   }
}

CollisionDetector::CollisionDetector(std::unique_ptr<CollisionImpl> impl) :
   impl{std::move(impl)}
{

}

void CollisionDetector::CheckPlaneAndLevelGUI(std::function<Plane*()>&& findPlaneFunc, std::function<LevelGUI*()>&& findLevelGUIFunc, bool& exitFlag)
{
   if (impl)
   {
      impl->CheckPlaneAndLevelGUI(std::move(findPlaneFunc), std::move(findLevelGUIFunc), exitFlag);
   }
}

void CollisionDetector::CheckBombsAndGround(std::function<std::vector<BombDecorator*>()>&& findBombsFunc, std::function<Ground*()>&& findGroundFunc, 
   std::function<void(BombDecorator*)>&& checkDestroyableObjectsFunc, std::function<void(BombDecorator*)>&& deleteDynamicObjFunc)
{
   if (impl)
   {
      impl->CheckBombsAndGround(std::move(findBombsFunc), std::move(findGroundFunc), std::move(checkDestroyableObjectsFunc), std::move(deleteDynamicObjFunc));
   }
}

void CollisionDetector::CheckDestroyableObjects(std::function<std::vector<DestroyableGroundObject*>()>&& findDestroyableGroundObjectsFunc,
   std::function<void(GameObject*)>&& deleteStaticObjFunc, int16_t& score, BombDecorator* pBomb)
{
   if (impl)
   {
      impl->CheckDestroyableObjects(std::move(findDestroyableGroundObjectsFunc), std::move(deleteStaticObjFunc), score, pBomb);
   }
}