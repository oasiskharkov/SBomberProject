#include "Mediator.h"
#include "LevelGUI.h"

Mediator::Mediator() :
   gui{ nullptr },
   time{ 0.f }
{}

void Mediator::SetReceiver(LevelGUI* gui_)
{
   gui = gui_;
}

void Mediator::SendMessage(const std::string& mes)
{
   messages.push(mes);
}

void Mediator::Update(float dt)
{
   time += dt;
   
   if (!gui)
   {
      throw std::logic_error("GUI was not initialized in Mediator!");
   }

   if (time > notifyTime && !messages.empty())
   {
      gui->BeNotified(messages.front());
      messages.pop();
      time = 0.f;
   }
}
