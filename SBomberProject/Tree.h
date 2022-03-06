#pragma once

#include "DestroyableGroundObject.h"

namespace
{
   constexpr float growTime = 5.f;
}

class Tree;

class TreeState
{
public:
   virtual void Grow(Tree* tree) = 0;
   virtual void Draw(double x, double y) const = 0;
};

class Tree : public DestroyableGroundObject
{
public:
   Tree(TreeState* state);
   ~Tree();
   bool isInside(double x1, double x2) const override;
   inline uint16_t GetScore() const override { return score; }
   void Draw() const override;
   void Update(float dt);
   void SetState(TreeState* s);
   std::shared_ptr<DestroyableGroundObject> Clone() const override;
   static int* i;
private:
   const uint16_t score = 10;
   float time;
   TreeState* state;
};

class SmallState : public TreeState
{
public:
   void Grow(Tree* tree) override;
   void Draw(double x, double y) const override;
};

class MidState : public TreeState
{
public:
   void Grow(Tree* tree) override;
   void Draw(double x, double y) const override;
};

class BigState : public TreeState
{
public:
   void Grow(Tree* tree) override;
   void Draw(double x, double y) const override;
};
