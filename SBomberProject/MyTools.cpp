#include <conio.h>
#include <windows.h>
#include <stdint.h>
#include <time.h> 

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

#include "MyTools.h"

namespace MyTools {
   //=============================================================================================

   void ClrScr()
   {
      system("cls");
   }

   void __fastcall GotoXY(double x, double y)
   {
      const COORD cc = { short(x), short(y) };
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
   }

   uint16_t GetMaxX()
   {
      HANDLE hWndConsole;
      if (hWndConsole = GetStdHandle(-12))
      {
         CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
         if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
         {
            return consoleInfo.srWindow.Right;
            int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
         }
      }

      return 0;
   }

   uint16_t GetMaxY()
   {
      HANDLE hWndConsole;
      if (hWndConsole = GetStdHandle(-12))
      {
         CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
         if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
         {
            return consoleInfo.srWindow.Bottom;
         }
      }

      return 0;
   }

   void SetColor(ConsoleColor color)
   {
      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(hConsole, color); // color =  (WORD)((BackgroundColor << 4) | TextColor))
   }

   //=============================================================================================

   std::string GetCurDateTime()
   {
      auto cur = std::chrono::system_clock::now();
      time_t time = std::chrono::system_clock::to_time_t(cur);
      char buf[64] = { 0 };
      ctime_s(buf, 64, &time);
      buf[strlen(buf) - 1] = '\0';
      return std::string(buf);
   }

   FileLoggerSingleton& FileLoggerSingleton::getInstance(const std::string& FN)
   {
      static FileLoggerSingleton instance(FN);
      return instance;
   }

   FileLoggerSingleton::FileLoggerSingleton(const std::string& FN)
   {
      logOut.open(FN, std::ios_base::out);
      if (!logOut.is_open())
      {
         throw std::ios_base::failure("Can't open file " + FN);
      }
   }

   FileLoggerSingleton::~FileLoggerSingleton()
   {
      if (logOut.is_open())
      {
         logOut.close();
      }
   }

   void __fastcall FileLoggerSingleton::WriteToLog(const std::string& str)
   {
      if (logOut.is_open())
      {
         logOut << GetCurDateTime() << " - " << str << std::endl;
      }
   }

   void __fastcall FileLoggerSingleton::WriteToLog(const std::string& str, int n)
   {
      if (logOut.is_open())
      {
         logOut << GetCurDateTime() << " - " << str << n << std::endl;
      }
   }

   void __fastcall FileLoggerSingleton::WriteToLog(const std::string& str, double d)
   {
      if (logOut.is_open())
      {
         logOut << GetCurDateTime() << " - " << str << d << std::endl;
      }
   }

   void FileLoggerSingleton::WriteIndexToLog(int64_t index)
   {
      if (logOut.is_open())
      {
         logOut << index << ". ";
      }
   }

   int64_t LoggerSingleton::index = 1;

   LoggerSingleton& LoggerSingleton::getInstance(FileLoggerSingleton& logger)
   {
      static LoggerSingleton instance(logger);
      return instance;
   }

   LoggerSingleton::LoggerSingleton(FileLoggerSingleton& logger) : logger{logger}
   {
      
   }

   void LoggerSingleton::WriteToLog(const std::string& str)
   {
      logger.WriteIndexToLog(index);
      logger.WriteToLog(str);
      ++index;
   }

   void LoggerSingleton::WriteToLog(const std::string& str, int n)
   {
      logger.WriteIndexToLog(index);
      logger.WriteToLog(str, n);
      ++index;
   }

   void LoggerSingleton::WriteToLog(const std::string& str, double d)
   {
      logger.WriteIndexToLog(index);
      logger.WriteToLog(str, d);
      ++index;
   }

   //=============================================================================================

} // namespace MyTools