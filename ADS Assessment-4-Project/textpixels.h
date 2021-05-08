
/** TextPixels.h, a bumpercar remix of olcConsoleGameEngine for new programmers.
 *
 *  @author Danny McGillick
 *  @author Javidx9
 *  Contact: dmac_makes#3457 (Discord)
 *
 *---- Original credits follow ------------------------
 *  OneLoneCoder.com - Command Line Game Engine
 *  "Who needs a frame buffer?" - @Javidx9
 *  The Original & Best :P
 *  One Lone Coder License
 *  Original Copyright (C) 2018 Javidx9
 */
#pragma once
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <chrono>
#include <functional>
#include <sstream>
#include <thread>
#include "textpixels_enums.h"
using namespace std::chrono_literals;

#ifndef __TEXT_PIXELS__
#define __TEXT_PIXELS__
using namespace std;
using namespace std::chrono;

namespace textpixels
{

  class TextPixels
  {
  public:
    int desiredFps = 30;
    float desiredFrameTime_ms = 33.3f;// = 33.3ms;
    int maxFrameTime = 33;
    int windowWidth;
    int windowHeight;
    int fontWidth = 12;
    int fontHeight = 12;
    time_point<system_clock> thisFrameStarted = system_clock::now();
    time_point<system_clock> lastFrameStarted = system_clock::now();
    time_point<system_clock> lastFrameEnded = system_clock::now();
    //time_point<system_clock> tp2 = system_clock::now();

    HANDLE console;
    HANDLE consoleIn;
    HANDLE originalConsole;
    SMALL_RECT rectWindow;
    CHAR_INFO* bufScreen;


    int Error(const wchar_t* msg)
    {
      wchar_t buf[256];
      FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
      SetConsoleActiveScreenBuffer(originalConsole);
      //wprintf(L"ERROR: %s\n\t%s\n", msg, buf); FIX
      return 0;
    }

    static BOOL CloseHandler(DWORD evt)
    {
      // Note this gets called in a seperate OS thread, so it must
      // only exit when the game has finished cleaning up, or else
      // the process will be killed before OnUserDestroy() has finished
      if (evt == CTRL_CLOSE_EVENT)
      {
        //m_bAtomActive = false;

        // Wait for thread to be exited
        //std::unique_lock<std::mutex> ul(m_muxGame);
        //m_cvGameFinished.wait(ul);
      }
      return true;
    }

    int setupConsole(int width = 20, int height = 20, int characterWidth = 12, int characterHeight = 12)
    {
      console = GetStdHandle(STD_OUTPUT_HANDLE);
      consoleIn = GetStdHandle(STD_INPUT_HANDLE);

      fontWidth = characterWidth;
      fontHeight = characterHeight;
      if (console == INVALID_HANDLE_VALUE)
        return Error(L"Bad Handle");

      windowWidth = width;
      windowHeight = height;

      // Update 13/09/2017 - It seems that the console behaves differently on some systems
      // and I'm unsure why this is. It could be to do with windows default settings, or
      // screen resolutions, or system languages. Unfortunately, MSDN does not offer much
      // by way of useful information, and so the resulting sequence is the reult of experiment
      // that seems to work in multiple cases.
      //
      // The problem seems to be that the SetConsoleXXX functions are somewhat circular and 
      // fail depending on the state of the current console properties, i.e. you can't set
      // the buffer size until you set the screen size, but you can't change the screen size
      // until the buffer size is correct. This coupled with a precise ordering of calls
      // makes this procedure seem a little mystical :-P. Thanks to wowLinh for helping - Jx9

      // Change console visual size to a minimum so ScreenBuffer can shrink
      // below the actual visual size
      rectWindow = { 0, 0, 1, 1 };
      SetConsoleWindowInfo(console, TRUE, &rectWindow);

      // Set the size of the screen buffer
      COORD coord = { (short)windowWidth, (short)windowHeight };
      if (!SetConsoleScreenBufferSize(console, coord))
        Error(L"SetConsoleScreenBufferSize");

      // Assign screen buffer to the console
      if (!SetConsoleActiveScreenBuffer(console))
        return Error(L"SetConsoleActiveScreenBuffer");

      // Set the font size now that the screen buffer has been assigned to the console
      CONSOLE_FONT_INFOEX cfi;
      cfi.cbSize = sizeof(cfi);
      cfi.nFont = 0;
      cfi.dwFontSize.X = fontWidth;
      cfi.dwFontSize.Y = fontHeight;
      cfi.FontFamily = FF_DONTCARE;
      cfi.FontWeight = FW_NORMAL;

      /*	DWORD version = GetVersion();
        DWORD major = (DWORD)(LOBYTE(LOWORD(version)));
        DWORD minor = (DWORD)(HIBYTE(LOWORD(version)));*/

        //if ((major > 6) || ((major == 6) && (minor >= 2) && (minor < 4)))		
        //	wcscpy_s(cfi.FaceName, L"Raster"); // Windows 8 :(
        //else
        //	wcscpy_s(cfi.FaceName, L"Lucida Console"); // Everything else :P

        //wcscpy_s(cfi.FaceName, L"Liberation Mono");
      wcscpy_s(cfi.FaceName, L"Consolas");
      if (!SetCurrentConsoleFontEx(console, false, &cfi))
        return Error(L"SetCurrentConsoleFontEx");

      // Get screen buffer info and check the maximum allowed window size. Return
      // error if exceeded, so user knows their dimensions/fontsize are too large
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      if (!GetConsoleScreenBufferInfo(console, &csbi))
        return Error(L"GetConsoleScreenBufferInfo");
      if (windowHeight > csbi.dwMaximumWindowSize.Y)
        return Error(L"Screen Height / Font Height Too Big");
      if (windowWidth > csbi.dwMaximumWindowSize.X)
        return Error(L"Screen Width / Font Width Too Big");

      // Set Physical Console Window Size
      rectWindow = { 0, 0, (short)windowWidth - 1, (short)windowHeight - 1 };
      if (!SetConsoleWindowInfo(console, TRUE, &rectWindow))
        return Error(L"SetConsoleWindowInfo");

      // Set flags to allow mouse input		
      if (!SetConsoleMode(consoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
        return Error(L"SetConsoleMode");

      // Allocate memory for screen buffer
      bufScreen = new CHAR_INFO[windowWidth * windowHeight];
      memset(bufScreen, 0, sizeof(CHAR_INFO) * windowWidth * windowHeight);

      SetConsoleCtrlHandler((PHANDLER_ROUTINE)CloseHandler, TRUE);
      return 1;
    }

    void drawBufferToConsole()
    {
      WriteConsoleOutput(console, bufScreen, { (short)windowWidth, (short)windowHeight }, { 0,0 }, &rectWindow);
    }

    void drawCharacter(int x, int y, short c = 0x2588, short col = 0x000F)
    {
      if (x >= 0 && x < windowWidth && y >= 0 && y < windowHeight)
      {
        bufScreen[y * windowWidth + x].Char.UnicodeChar = c;
        bufScreen[y * windowWidth + x].Attributes = col;
      }
    }

    void clip(int& x, int& y)
    {
      if (x < 0) x = 0;
      if (x >= windowWidth) x = windowWidth;
      if (y < 0) y = 0;
      if (y >= windowHeight) y = windowHeight;
    }

    void fillRect(int x1, int y1, int x2, int y2, short col = 0x000F, short c = 0x2588)
    {
      clip(x1, y1);
      clip(x2, y2);
      for (int x = x1; x < x2; x++)
        for (int y = y1; y < y2; y++)
          drawCharacter(x, y, c, col);
    }

    // Use foreground colour, this will use solid pixel
    void fillWindow(short colour)
    {
      fillRect(0, 0, windowWidth+1, windowHeight + 1, colour);
    }

    /**
     *  \brief Set the desired frames to be drawn per second.
     *  Accurate within 1-3 frames if performance allows.
     *  \param desiredFps Defaults to 30. Try 60 if you have faster animation, even 100.
     **/
    void setFps(int desiredFps = 30)
    {
      TextPixels::desiredFps = desiredFps;
      // Take the floor of this number, since we're stuck with millisecond resolution.
      // Better to set a shorter maxFrameTime than a long one and run slow because we 
      // are oversleeping. Casting to int will floor it by default. Would be great if
      // floor could return, you know, ints, whole numbers.
      maxFrameTime = static_cast<int>(1000.0f / (float)desiredFps);

      // next time use float for maxFrameTime and ditch chrono in favour 
      // of the MS QueryPerformanceCounter 
      // https://docs.microsoft.com/en-us/windows/win32/sysinfo/acquiring-high-resolution-time-stamps
    }

    void startFrame()
    {
      thisFrameStarted = std::chrono::system_clock::now();
    }

    float getLastFrameDuration_sec()
    {
      std::chrono::duration<float> elapsedTime = (lastFrameEnded - lastFrameStarted);
      return(elapsedTime.count());
    }

    int getLastFrameDuration_ms()
    {
      int elapsedTime = static_cast<int>(std::chrono::round<milliseconds>(lastFrameEnded - lastFrameStarted).count());
      return(elapsedTime);
    }

    void drawString(int x, int y, std::wstring c, short col = 0x000F)
    {
      for (size_t i = 0; i < c.size(); i++)
      {
        bufScreen[y * windowWidth + x + i].Char.UnicodeChar = c[i];
        bufScreen[y * windowWidth + x + i].Attributes = col;
      }
    }

    void endFrame()
    {
      drawBufferToConsole();

      // Round up time math: better to sleep too little than too long.
      int thisFrameLength = static_cast<int>(chrono::ceil<milliseconds>((system_clock::now() - thisFrameStarted)).count());
      this_thread::sleep_for(milliseconds((maxFrameTime - thisFrameLength)));

      // In our (frame's) time of dying, write our present and past to history.
      lastFrameStarted = thisFrameStarted;
      lastFrameEnded = system_clock::now();

      // next time use float for maxFrameTime and ditch chrono in favour 
      // of the MS QueryPerformanceCounter 
      // https://docs.microsoft.com/en-us/windows/win32/sysinfo/acquiring-high-resolution-time-stamps
    }

    void drawRow(int y, int colour = (int)Colour::FG_MAGENTA)
    {
      for (int x = 0; x < windowWidth; x++)
      {
        drawCharacter(x, y, 0x2588, colour);
      }
    }

    void drawPixel(int x, int y, short colour = 0x000F)
    {
      drawCharacter(x, y, 0x2588, colour);
    }

    short layerColours(short foreground, short background)
    {
      return (foreground | background);
    }

    int getFps()
    {
      return((int)(round(1.0f / getLastFrameDuration_sec())));
      //return((int)(ceil(1000.0f / float(getLastFrameDuration_ms()))));
    }

    std::string getFpsString()
    {
      return(to_string(getFps()));
    }
  };  // End class TextPixels

////////////// Functions providing no-knowledge access to object //////////////////////

  std::wstring strToWstr(std::string regularString)
  {
    std::wstringstream cls;
    cls << regularString.c_str();

    return(cls.str());
  }

  TextPixels txtPxls;

  // Checks the current state of the key. Takes a Virtual Key Code
  bool keyIsDown(int keyCode)
  {
    return (GetAsyncKeyState(keyCode) < 0);
  }
  
  
  int windowWidth()
  {
    return txtPxls.windowWidth;
  }

  int windowHeight()
  {
    return txtPxls.windowHeight;
  }
  
  int setupWindow(int width = 30, int height = 30, int pixelWidth = 16, int pixelHeight = 16)
  {
    int result = txtPxls.setupConsole(width, height, pixelWidth, pixelHeight);
    Sleep(100); // Fix tiny window problem?
    //windowWidth = txtPxls.windowWidth;
    //windowHeight = txtPxls.windowHeight;
    return(result);
  }

  // Draw a text character that looks like a full pixel to location x, y on the screen
  void drawPixel(int x, int y, short colour = FG_WHITE)
  {
    txtPxls.drawPixel(x, y, short(colour));
  }

  // Draw a unicode wide character to x,y on the screen. 
  // To supply a wide char literal, use L`a` (where a is a character)
  void drawWCharacter(int x, int y, short character, short colour = FG_WHITE)
  {
    txtPxls.drawCharacter(x, y, character, colour);
  }

  // Draw a filled rectangle with its top left corner at x,y.
  // @param colour is a short int: use an FG_ colour from the Colours enum.
  // @param character is a unicode wide char (as short integer). Default is a solid FG colour.
  void fillRect(int x, int y, int width=6, int height=4, short colour = FG_WHITE, short character = Pixel::PIXEL_SOLID )
  {
    txtPxls.fillRect(x, y, x+width, y+height, colour, character );
  }

  // Draw a filled rectangle with its top left corner at x,y, bottom right corner at x2,y2
 // @param colour is a short int: use an FG_ colour from the Colours enum.
 // @param character is a unicode wide char (as short integer). Default is a solid FG colour.
  void fillRectByCoords(int x, int y, int x2, int y2, short colour = FG_WHITE, short character = Pixel::PIXEL_SOLID)
  {
    txtPxls.fillRect(x, y, x2+1, y2+1, colour, character);
  }

  // Fill the window with colour. Use an FG_ colour as this uses solid pixel.
  void fillWindow(short colour)
  {
    txtPxls.fillWindow(colour);
  }

  // Create a single short int describing both foreground and background colours.
  // Colours are from textpixels_enums.h, eg FG_WHITE, BG_DARK_MAGENTA
  short layerColours(short foreground, short background)
  {
    return (txtPxls.layerColours(foreground, background));
  }

  // Anything drawn with drawPixel/drawString/etc this frame will now
  // be drawn to the screen in a single pass (from the screen buffer)
  void updateScreen()
  {
    txtPxls.drawBufferToConsole();
  }

  // Required at start of game loop when using textpixels.h
  void startFrame()
  {
    txtPxls.startFrame();
    return;
  }

  // Required at end of game loop when using textpixels.h
  void endFrame()
  {
    txtPxls.endFrame();
    return;
  }

  // How long was the time between the start of last frame and
  // the start of this one? In seconds.
  // Returns a float from 0 to 1. eg: 0.5 is half a second, 0.033 is 33 milliseconds.
  float getLastFrameDuration_sec()
  {
    return(txtPxls.getLastFrameDuration_sec());
  }

  // How long was the time between the start of last frame and
  // the start of this one? In milliseconds.
  // Returns an int: 500 is half a second, 33 is.. 33 milliseconds.
  int getLastFrameDuration_ms()
  {
    return (txtPxls.getLastFrameDuration_ms());
  }

//    std::function<void(int, int, std::wstring, short)> printWString = [=](int x, int y, std::wstring aWString, short colour = 0x000F) {
//    return txtPxls.drawString(x, y, aWString, colour);
//  };

  // Draw/print a string of characters to the screen at location x,y (in text pixels).
  // Use layerColour to supply both foreground and background colours.
  void drawString(int x, int y, std::string regularString, short colour = 0x000F)
  {
    wstring wideString = strToWstr(regularString);
    //wstring::
    txtPxls.drawString(x, y, wideString, colour);
  }

  // Draw/print a wstring of unicode characters to the screen at location x,y (in text pixels).
  // Use layerColour to supply both foreground and background colours.
  // To supply a wstring literal you can use L"whatever", rather than the regular string "example".
  void drawWString(int x, int y, std::wstring wideString, short colour = 0x000F)
  {
    txtPxls.drawString(x, y, wideString, colour);
  }

  //  Set the desired frames to be drawn per second.
  //  Accurate within 1-3 frames if performance allows.
  //  @param desiredFps Defaults to 30. Try 60 if you have faster animation, even 100.
  void setFps(int desiredFps = 30)
  {
    txtPxls.setFps(desiredFps);
    Sleep(100);   // Fix tiny window problem?
  }

  // The number of frames being  drawn per second. Highly changeable since it only 
  // checks the last frame.
  int getFps()
  {
    return(txtPxls.getFps());
  }

  // The number of frames being  drawn per second as a string. Highly changeable 
  // since it only checks the last frame.
  std::string getFpsString()
  {
    return(txtPxls.getFpsString());
  }

}

#endif