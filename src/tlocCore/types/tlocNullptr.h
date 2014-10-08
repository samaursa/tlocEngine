#ifndef _TLOC_CORE_NULL_PTR_H_
#define _TLOC_CORE_NULL_PTR_H_

  #ifdef TLOC_CXX03
namespace std {
    //////////////////////////////////////////////////////////////////////////
    // C++11 NULL define (this will be removed when compiling as C++11)

    // Copied from http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/nullptr#Solution_and_Sample_Code
    // Note that this class should NOT be in tloc namespace to facilitate easy
    // transition to C++11
    class nullptr_t
    {
    public:
      template<class T>
      inline operator T*() const // convertible to any type of null non-member pointer...
      { return 0; }

      template<class C, class T>
      inline operator T C::*() const   // or any type of null member pointer...
      { return 0; }

    private:
      void operator&() const;  // Can't take address of nullptr

    };

    extern nullptr_t nullptr;
};
  #else
    #include <cstddef>
    using std::nullptr_t;
  #endif

#endif

