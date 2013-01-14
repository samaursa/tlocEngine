#ifndef TLOC_CHAR_BUFFER_H
#define TLOC_CHAR_BUFFER_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/data_structures/tlocProtectedBuffer.h>

namespace tloc { namespace core { namespace data_structs {

  template <tl_size T_Size>
  class CharBuffer : public ProtectedBuffer<char8, T_Size>
  { };

  template <tl_size T_Size>
  class CharBufferW : public ProtectedBuffer<char32, T_Size>
  { };

};};};

#endif