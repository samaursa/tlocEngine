#ifndef _TLOC_CORE_CONSOLE_H_
#define _TLOC_CORE_CONSOLE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocBasicTypes.h>

namespace tloc { namespace console {

  // -----------------------------------------------------------------------
  // write to console helper function
  // the console color code referenced from: http://www.cplusplus.com/articles/2ywTURfi/ 

  namespace p_color
  {
    enum 
    {
      black=0,
      dark_blue=1,
      dark_green=2,
      dark_aqua,dark_cyan=3,
      dark_red=4,
      dark_purple=5,dark_pink=5,dark_magenta=5,
      dark_yellow=6,
      dark_white=7,
      gray=8,
      blue=9,
      green=10,
      aqua=11,cyan=11,
      red=12,
      purple=13,pink=13,magenta=13,
      yellow=14,
      white=15
    };
  };

  void SetConsoleColor(tl_int a_textCol, tl_int a_bgColor);
  void WriteToConsole(const char8* a_formattedText);
  bool WriteToIDEConsole(const char8* a_formattedText);

};};

#endif