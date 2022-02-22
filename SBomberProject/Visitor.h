#pragma once

class Plane;
class Bomb;

#include "MyTools.h"

using namespace MyTools;

class Visitor
{
public:
   virtual ~Visitor() = default;
   virtual void log(const Plane& plane) const = 0;
   virtual void log(const Bomb& bomb) const = 0;
};

class LogVisitor : public Visitor
{
public:
   LogVisitor();
   void log(const Plane& plane) const override;
   void log(const Bomb& bomb) const override;
private:
   MyTools::LoggerSingleton& logger;
};