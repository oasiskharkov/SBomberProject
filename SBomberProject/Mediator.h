#pragma once

#include <queue>
#include <string>
#include <iostream>

namespace 
{
   constexpr float notifyTime = 3.f;
}

class LevelGUI;

class Mediator
{
public:
   Mediator();
   void SetReceiver(LevelGUI* gui_);
   void SendMessage(const std::string& mes);
   void Update(float dt);
private:
   LevelGUI* gui;
   float time;
   std::queue<std::string> messages;
};