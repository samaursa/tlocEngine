#include "tlocSmartPtrTracker.h"

#include <tlocCore/containers/tlocHashmap.h>
#include <tlocCore/containers/tlocHashmap.inl.h>

namespace tloc { namespace core { namespace smart_ptr { namespace priv {

  namespace {
    class PointerMap
    {
    public:
      typedef containers::HashMap<void*, void*>   map_type;

    public:
      static bool Exists(void* a_pointer)
      {
        if (a_pointer != nullptr)
        { return m_ptrMap.find(a_pointer) != m_ptrMap.end(); }

        return false;
      }

      static void Add(void* a_pointer)
      {
        if (a_pointer != nullptr)
        { m_ptrMap[a_pointer] = a_pointer; }
      }

      static void Remove(void* a_pointer)
      {
        if (a_pointer != nullptr)
        { m_ptrMap.erase(a_pointer); }
      }

      static tl_size size()
      {
        return m_ptrMap.size();
      }

    private:
      static map_type m_ptrMap;
    };

    PointerMap::map_type  PointerMap::m_ptrMap;
  }

  void DoStartTrackingPtr(void* a_pointer)
  {
    TLOC_ASSERT_LOW_LEVEL(PointerMap::Exists(a_pointer) == false,
      "a_pointer is already managed by another (set of) smart pointers");
    PointerMap::Add(a_pointer);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void DoStopTrackingPtr(void* a_pointer)
  {
    TLOC_ASSERT_LOW_LEVEL(PointerMap::Exists(a_pointer),
      "a_pointer has already been removed by another (set of) smart pointers");
    PointerMap::Remove(a_pointer);
  }

  //////////////////////////////////////////////////////////////////////////

  bool Unsafe_IsPtrTracked(void* a_pointer)
  {
    return PointerMap::Exists(a_pointer);
  }

  tl_size Unsafe_GetPtrTrackedSize()
  {
    return PointerMap::size();
  }

};};};};