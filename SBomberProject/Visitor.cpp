#include "Visitor.h"
#include "BombDecorator.h"
#include "Plane.h"
#include "MyTools.h"

#include <string>

LogVisitor::LogVisitor() :
   logger{ LoggerSingleton::getInstance(FileLoggerSingleton::getInstance()) }
{
}

void LogVisitor::log(const Plane& plane) const
{
   const auto& dir = plane.GetDirection();
   logger.WriteToLog(std::string(__FUNCTION__) + " plane direction = x:" + std::to_string(dir.first) + " y:" + std::to_string(dir.second));
   logger.WriteToLog(std::string(__FUNCTION__) + " plane speed = ", plane.GetSpeed());
}

void LogVisitor::log(const Bomb& bomb) const
{
   const auto& dir = bomb.GetDirection();
   logger.WriteToLog(std::string(__FUNCTION__) + " bomb direction = x:" + std::to_string(dir.first) + " y:" + std::to_string(dir.second));
   logger.WriteToLog(std::string(__FUNCTION__) + " bomb speed = ", bomb.GetSpeed());
}
