#ifndef TLOC_STRING_H
#define TLOC_STRING_H

#include "tlocArray.h"

namespace tloc
{
  template <typename T>
  class StringBase : public Array<T>
  {
  public:
    StringBase();
    ~StringBase();

    //------------------------------------------------------------------------
    // Modifiers

  protected:

    //------------------------------------------------------------------------
    // Helper functions


  };
};

#endif