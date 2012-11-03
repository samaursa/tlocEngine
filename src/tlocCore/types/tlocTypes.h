#pragma once
#ifndef TLOC_TYPES_H
#define TLOC_TYPES_H

// 2LoC engine types
#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/types/tlocConditionalType.h>

//------------------------------------------------------------------------
// Global functions, no namespace
//
// These are the rare few functions that are globally defined without under
// the tloc namespace. This is so that types in other namespaces can
// successfully call TLOC_DEF_TYPE.

//////////////////////////////////////////////////////////////////////////
// Compile time type to string functions.
// USAGE: A type that you want (or is required) to have its own specialized
//        type_to_string<> function should simply call TLOC_DEF_TYPE(type)
//        after the type declaration in the header

// We do not allow unregistered types to be queried. If the compiler sent you
// here, trace back to the type that originated the error and register it.
template <typename>
struct tl_type_to_string
{
  static const char* value()
  {
    TLOC_STATIC_ASSERT(false, Using_an_unregistered_type_Call_TLOC_DEF_TYPE_to_register_the_type);
  }
};

#ifdef TLOC_DEF_TYPE
#error "TLOC_DEF_TYPE is already defined somewhere else!"
#else
#define TLOC_DEF_TYPE(_type_)\
  template <>\
  struct tl_type_to_string<_type_>\
  {\
    static const char* value()\
    {\
      return #_type_;\
    }\
  }
#endif // TLOC_DEF_TYPE

namespace tloc
{
  class EmptyType
  {
    typedef EmptyType   value_type;
  };

  // Useful for inheriting from several empty types
  template <tl_size ID>
  class EmptyType_T
  {
    typedef EmptyType_T<ID> value_type;
  };
};

#endif // header guard
