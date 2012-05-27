#ifndef TLOC_CONTAINER_UTILS_H
#define TLOC_CONTAINER_UTILS_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypeTraits.h>

namespace tloc { namespace core { namespace utils {

  //------------------------------------------------------------------------
  // Array size counter (raw and complex)

  template <typename T, tl_size T_Size>
  tl_size ArraySize(T (&)[T_Size]) { return T_Size; }

  template <typename T, tl_size T_Size>
  tl_size ArraySize(const T (&)[T_Size]) { return T_Size; }

  template <typename T_Container>
  typename T_Container::size_type ArraySize(T_Container& a_container)
  { return a_container.size(); }

  template <typename T_Container>
  typename T_Container::size_type ArraySize(const T_Container& a_container)
  { return a_container.size(); }

};};};


#endif