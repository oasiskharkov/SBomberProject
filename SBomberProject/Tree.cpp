#include <typeinfo>
#include <iostream>

#include "Tree.h"
#include "MyTools.h"

using namespace MyTools;

Tree::Tree(TreeState* state) : 
   time{ 0.f },
   state{ state }
{
   if (!state)
   {
      throw std::logic_error("Incorrect tree initialization.");
   }
}

Tree::~Tree()
{
   if (state)
   {
      delete state;
   }
}

bool Tree::isInside(double x1, double x2) const
{
   return false;
}

void Tree::Draw() const
{
   if (typeid(SmallState) == typeid(*state))
   {
      MyTools::SetColor(MyTools::CC_Green);
      MyTools::GotoXY(x, y);
      std::cout << " | ";
      MyTools::GotoXY(x, y - 1);
      std::cout << "\\|/";
   }
   else if (typeid(MidState) == typeid(*state))
   {
      MyTools::SetColor(MyTools::CC_Green);
      MyTools::GotoXY(x - 1, y);
      std::cout << "  |  ";
      MyTools::GotoXY(x - 1, y - 1);
      std::cout << " \\|/ ";
      MyTools::GotoXY(x - 1, y - 2);
      std::cout << "\\\\|//";
   }
   else if (typeid(BigState) == typeid(*state))
   {
      MyTools::SetColor(MyTools::CC_Green);
      MyTools::GotoXY(x - 2, y);
      std::cout << "   |   ";
      MyTools::GotoXY(x - 2, y - 1);
      std::cout << "  \\|/  ";
      MyTools::GotoXY(x - 2, y - 2);
      std::cout << " \\\\|// ";
      MyTools::GotoXY(x - 2, y - 3);
      std::cout << "\\\\\\|///";
   }
}

void Tree::Update(float dt)
{
   time += dt;
   if (time > growTime && state)
   {
      state->Grow(this);
      time = 0.f;
   }
}

void Tree::SetState(TreeState* s)
{
   if (state)
   {
      delete state;
      state = s;
   }
}

std::shared_ptr<DestroyableGroundObject> Tree::Clone() const
{
   return nullptr;
}

void SmallState::Grow(Tree* tree)
{
   if (tree)
   {
      tree->SetState(new MidState);
   }
}

void MidState::Grow(Tree* tree)
{
   if (tree)
   {
      tree->SetState(new BigState);
   }
}

void BigState::Grow(Tree* tree)
{
   // dummy
}
