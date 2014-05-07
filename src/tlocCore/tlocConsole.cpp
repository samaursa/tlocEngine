#include "tlocConsole.h"

#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/platform/tlocPlatformSpecificIncludes.h>

#include <stdio.h>

// -----------------------------------------------------------------------
// global helper functions
namespace {

  using namespace tloc;

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Platform>
  void DoSetConsoleColor(tl_int , tl_int, T_Platform)
  {  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Platform>
  bool DoWriteToIDEConsole(const char8* , T_Platform)
  { return false; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#if defined(TLOC_OS_WIN)

  void DoSetConsoleColor(tl_int a_textCol, tl_int a_bgCol, 
                         core_plat::p_platform_info::win)
  {  
    WORD col = 0;
    col |= a_textCol;
    col |= (a_bgCol << 4);

    static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, col);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Platform>
  void DoWriteToIDEConsole(const char8* a_text,
                           core_plat::p_platform_info::win)
  { 
    bool idp = IsDebuggerPresent() != 0;
    if (idp)
    { OutputDebugString(a_text); }
    else
    { return false; }
  }

#endif // TLOC_OS_WIN
};

namespace tloc { namespace console {

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    SetConsoleColor(tl_int a_textCol, tl_int a_bgColor)
  {
    DoSetConsoleColor(a_textCol, a_bgColor, 
                      core_plat::PlatformInfo::platform_type());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    WriteToConsole(const char8* a_formattedText)
  { printf(a_formattedText); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    WriteToIDEConsole(const char8* a_formattedText)
  { 
    return DoWriteToIDEConsole(a_formattedText, 
                               core_plat::PlatformInfo::platform_type());
  }

};};