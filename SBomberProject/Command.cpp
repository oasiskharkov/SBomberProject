#include "Command.h"
#include "Plane.h"
#include "BombDecorator.h"
#include "Ground.h"

DeleteDynamicObjectCommand::DeleteDynamicObjectCommand(std::vector<std::shared_ptr<DynamicObject>>& dObjects, DynamicObject* dObject) :
   dynamicObjects{ dObjects },
   dynamicObject{ dObject }
{
}

void DeleteDynamicObjectCommand::Execute()
{
   if (!dynamicObject)
   {
      return;
   }

   for (auto it = dynamicObjects.begin(); it != dynamicObjects.end(); ++it)
   {
      if ((*it).get() == dynamicObject)
      {
         dynamicObjects.erase(it);
         break;
      }
   }
}

DeleteStaticObjectCommand::DeleteStaticObjectCommand(std::vector<std::shared_ptr<GameObject>>& gObjects, GameObject* gObject) :
   gameObjects{ gObjects},
   gameObject{ gObject }
{
}

void DeleteStaticObjectCommand::Execute()
{
   if (!gameObject)
   {
      return;
   }

   for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
   {
      if ((*it).get() == gameObject)
      {
         gameObjects.erase(it);
         break;
      }
   }
}

DropBombCommand::DropBombCommand(std::vector<std::shared_ptr<DynamicObject>>& dObjects, const std::vector<DestroyableGroundObject*>& dgos_, 
   const Plane* plane, uint16_t& bombsNumber, int16_t& score) :
   dynamicObjects{ dObjects },
   dgos{ dgos_ },
   plane{ plane },
   bombsNumber{ bombsNumber},
   score{score}
{
}

void DropBombCommand::Execute()
{
   if (!plane)
   {
      return;
   }

   double x = plane->GetX() + 4;
   double y = plane->GetY() + 2;

   std::shared_ptr<BombDecorator> bomb = std::make_shared<BombDecorator>();
   if (!bomb)
   {
      return;
   }

   bomb->SetDirection(0.3, 1);
   bomb->SetSpeed(2);
   bomb->SetPos(x, y);
   bomb->SetWidth(SMALL_CRATER_SIZE);

   dynamicObjects.emplace_back(bomb);
   for (const auto& dgo : dgos)
   {
      bomb->AddObserver(dgo);
   }

   bombsNumber--;
}
