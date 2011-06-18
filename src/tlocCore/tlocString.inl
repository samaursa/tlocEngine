#ifndef TLOC_STRING_H
#define TLOC_STRING_H

#include <string>

namespace tloc
{
  template <typename T>
  class String
  {
  public:
    String()
    {

    }

    ~String()
    {

    }



  private:
    T* m_string;
  };
};

#endif