#ifndef TLOC_MEMORY_H
#define TLOC_MEMORY_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocCore/memory/tlocAllocators.h>

#ifndef TLOC_BASE_H
# error "Must include tlocBase.h before including tlocMemory.h"
#endif

namespace tloc { namespace core {

  namespace memory
  {
    extern bool IsValidHeapPointer(const void * a_userData);
  };

};};

namespace tloc { namespace core { namespace memory {

  // ///////////////////////////////////////////////////////////////////////
  // Slightly safer version of memcpy where you don't have to worry about
  // complex types being copied incorrectly

  namespace priv {

    typedef std::true_type    simple_type;
    typedef std::false_type   complex_type;

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T>
    T* 
      DoMemCopy(T* a_destination, const T* a_source, tl_size a_elementsToCopy, 
                simple_type)
    { return (T*)memcpy(a_destination, a_source, a_elementsToCopy * sizeof(T)); }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T>
    T* 
      DoMemCopy(T* a_destination, const T* a_source, tl_size a_elementsToCopy, 
                complex_type)
    { 
      T* dest = a_destination;
      for (tl_size i = 0; i < a_elementsToCopy; ++i)
      {
        *dest = *a_source;
        ++dest; ++a_source;
      }

      return a_destination;
    }
  };

  template <typename T>
  T* MemCopy(T* a_destination, const T* a_source, tl_size a_elementsToCopy)
  {
    return priv::DoMemCopy(a_destination, a_source, a_elementsToCopy, 
                           std::is_fundamental<T>::type());
  }

};};}

#endif  // TLOC_MEMORY_H
