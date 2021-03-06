#pragma once

#include <stdint.h>
#include <string>
#include <fstream>

namespace MyTools 
{
   // color palette 0..15
   enum ConsoleColor
   {
      CC_Black = 0,
      CC_Blue,
      CC_Green,
      CC_Cyan,
      CC_Red,
      CC_Magenta,
      CC_Brown,
      CC_LightGray,
      CC_DarkGray,
      CC_LightBlue,
      CC_LightGreen,
      CC_LightCyan,
      CC_LightRed,
      CC_LightMagenta,
      CC_Yellow,
      CC_White
   };

   void ClrScr();
   void  GotoXY(double x, double y);
   uint16_t GetMaxX();
   uint16_t GetMaxY();
   void SetColor(ConsoleColor color);

   class ILogger
   {
   public:
      virtual ~ILogger() = default;
      virtual void WriteToLog(const std::string& str) = 0;
      virtual void WriteToLog(const std::string& str, int n) = 0;
      virtual void WriteToLog(const std::string& str, double d) = 0;
      virtual void OpenFile(const std::string& fileName) = 0;
   };

   class FileLoggerSingleton : public ILogger
   {
   public:
      static FileLoggerSingleton& getInstance();
      ~FileLoggerSingleton();

      void WriteToLog(const std::string& str) override;
      void WriteToLog(const std::string& str, int n) override;
      void WriteToLog(const std::string& str, double d) override;
      void OpenFile(const std::string& fileName) override;
   private:
      std::ofstream logOut;
   private:
      FileLoggerSingleton() = default;
      FileLoggerSingleton(const FileLoggerSingleton&) = delete;
      FileLoggerSingleton& operator = (const FileLoggerSingleton&) = delete;
   };

   class LoggerSingleton : public ILogger
   {
   public:
      static LoggerSingleton& getInstance(FileLoggerSingleton& logger);
      
      void WriteToLog(const std::string& str) override;
      void WriteToLog(const std::string& str, int n) override;
      void WriteToLog(const std::string& str, double d) override;
      void OpenFile(const std::string& fileName) override;
   private:
      LoggerSingleton(FileLoggerSingleton& logger);
      LoggerSingleton(const LoggerSingleton&) = delete;
      LoggerSingleton& operator = (const LoggerSingleton&) = delete;
   private:
      FileLoggerSingleton& logger;
      int64_t index;
   };
};