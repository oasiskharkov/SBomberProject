#pragma once

#include <functional>
#include <vector>
#include <memory>

class Plane;
class LevelGUI;
class Ground;
class BombDecorator;
class DestroyableGroundObject;
class GameObject;

class CollisionImpl
{
public:
   virtual ~CollisionImpl() = default;
   virtual void CheckPlaneAndLevelGUI(std::function<Plane*()>&& findPlaneFunc, std::function<LevelGUI*()>&& findLevelGUIFunc, bool& exitFlag) = 0;
   virtual void CheckBombsAndGround(std::function<std::vector<BombDecorator*>()>&& findBombsFunc, std::function<Ground*()>&& findGroundFunc,
      std::function<void(BombDecorator*)>&& checkDestroyableObjectsFunc, std::function<void(BombDecorator*)>&& deleteDynamicObjFunc) = 0;
   virtual void CheckDestroyableObjects(std::function<std::vector<DestroyableGroundObject*>()>&& findDestroyableGroundObjectsFunc, 
      std::function<void(GameObject*)>&& deleteStaticObjFunc, int16_t& score, BombDecorator* pBomb) = 0;
};
   
class CollisionImplWin : public CollisionImpl
{
public:
   void CheckPlaneAndLevelGUI(std::function<Plane*()>&& findPlaneFunc, std::function<LevelGUI* ()>&& findLevelGUIFunc, bool& exitFlag) override;
   void CheckBombsAndGround(std::function<std::vector<BombDecorator*>()>&& findBombsFunc, std::function<Ground* ()>&& findGroundFunc,
      std::function<void(BombDecorator*)>&& checkDestroyableObjectsFunc, std::function<void(BombDecorator*)>&& deleteDynamicObjFunc) override;
   void CheckDestroyableObjects(std::function<std::vector<DestroyableGroundObject*>()>&& findDestroyableGroundObjectsFunc,
      std::function<void(GameObject*)>&& deleteStaticObjFunc, int16_t& score, BombDecorator* pBomb) override;
};

class CollisionDetector
{
public:
   CollisionDetector(std::unique_ptr<CollisionImpl> impl);
   void CheckPlaneAndLevelGUI(std::function<Plane*()>&& findPlaneFunc, std::function<LevelGUI*()>&& findLevelGUIFunc, bool& exitFlag);
   void CheckBombsAndGround(std::function<std::vector<BombDecorator*>()>&& findBombsFunc, std::function<Ground* ()>&& findGroundFunc,
      std::function<void(BombDecorator*)>&& checkDestroyableObjectsFunc, std::function<void(BombDecorator*)>&& deleteDynamicObjFunc);
   void CheckDestroyableObjects(std::function<std::vector<DestroyableGroundObject*>()>&& findDestroyableGroundObjectsFunc,
      std::function<void(GameObject*)>&& deleteStaticObjFunc, int16_t& score, BombDecorator* pBomb);
private:
   std::unique_ptr<CollisionImpl> impl;
};