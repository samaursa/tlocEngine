#include "tlocSmartPtrTracker.h"

#include <tlocCore/containers/tlocHashmap.h>
#include <tlocCore/containers/tlocHashmap.inl.h>
#include <tlocCore/configs/tlocBuildConfig.h>

namespace tloc { namespace core { namespace smart_ptr { namespace priv {

  namespace {

    // ///////////////////////////////////////////////////////////////////////
    // PointerMap_T<>

    template <typename T_BuildConfig = core_cfg::BuildConfig::build_config_type>
    class PointerMap_T
    {
    public:
      typedef containers::HashMap<void*, void*>     map_type;
      typedef containers::HashMap<void*, tl_size>   virtual_map_type;

    public:
      bool Exists(void* a_pointer)
      {
        if (m_mapIsDestroyed) { return false; }

        if (a_pointer != nullptr)
        { return m_ptrMap.find(a_pointer) != m_ptrMap.end(); }

        return false;
      }

      bool ExistsVirtual(void* a_pointer)
      {
        if (m_mapIsDestroyed) { return false; }

        if (a_pointer != nullptr)
        {
          virtual_map_type::iterator itr = m_virtualPtrMap.find(a_pointer);
          if (itr != m_virtualPtrMap.end())
          {
            return true;
          }
          return m_virtualPtrMap.find(a_pointer) != m_virtualPtrMap.end();
        }

        return false;
      }

      void StartTracking(void* a_pointer)
      {
        TLOC_ASSERT(!m_mapIsDestroyed, "Are you calling Add() at program exit?");

        if (a_pointer != nullptr)
        { m_ptrMap[a_pointer] = a_pointer; }
      }

      tl_size StartTrackingVirtual(void* a_pointer)
      {
        TLOC_ASSERT(!m_mapIsDestroyed, "Are you callind Add() at program exit?");

        if (a_pointer != nullptr)
        {
          virtual_map_type::iterator itr = m_virtualPtrMap.find(a_pointer);

          if (itr != m_virtualPtrMap.end())
          { ++itr->second; }
          else
          {
            m_virtualPtrMap[a_pointer] = 1;
            return 1;
          }

          return itr->second;
        }

        return 0;
      }

      void StopTracking(void* a_pointer)
      {
        TLOC_ASSERT(!m_mapIsDestroyed, "Are you calling Add() at program exit?");

        if (a_pointer != nullptr)
        { m_ptrMap.erase(a_pointer); }
      }

      tl_size StopTrackingVirtual(void* a_pointer)
      {
        TLOC_ASSERT(!m_mapIsDestroyed, "Are you calling Add() at program exit?");

        if (a_pointer != nullptr)
        {
          virtual_map_type::iterator itr = m_virtualPtrMap.find(a_pointer);

          TLOC_ASSERT(itr != m_virtualPtrMap.end(),
            "Pointer never tracked virtually OR too many calls to this function");

          TLOC_ASSERT(itr->second >= 1, "Logical error");
          --itr->second;

          if (itr->second == 0)
          {
            m_virtualPtrMap.erase(itr);
            return 0;
          }

          return itr->second;
        }

        return 0;
      }

      tl_size GetNumTrackedPointers()
      { return m_ptrMap.size(); }

      tl_size GetNumTrackedVirtualPointers()
      { return m_virtualPtrMap.size(); }

      tl_size GetVirtualRefCount(void* a_pointer)
      {
        virtual_map_type::iterator itr = m_virtualPtrMap.find(a_pointer);

        if (itr != m_virtualPtrMap.end())
        {
          return itr->second;
        }

        return 0;
      }

      static PointerMap_T& Get()
      { return sm_inst; }

    private:
      PointerMap_T()
      { m_mapIsDestroyed = false; }

      ~PointerMap_T()
      { m_mapIsDestroyed = true; }

    private:
      map_type            m_ptrMap;
      virtual_map_type    m_virtualPtrMap;
      static bool         m_mapIsDestroyed;
      static PointerMap_T sm_inst;
    };

    // ///////////////////////////////////////////////////////////////////////
    // PointerMap_T<Release>

    template <>
    class PointerMap_T<core_cfg::p_build_config::Release>
    {
    public:
      typedef containers::HashMap<void*, void*>   map_type;

    public:
      bool Exists(void* )
      { return false; }

      bool ExistsVirtual(void* )
      { return false; }

      void StartTracking(void* )
      { }

      tl_size StartTrackingVirtual(void* )
      { return 0; }

      void StopTracking(void* )
      { }

      tl_size StopTrackingVirtual(void* )
      { return 0; }

      tl_size GetNumTrackedPointers()
      { return 0; }

      tl_size GetNumTrackedVirtualPointers()
      { return 0; }

      tl_size GetVirtualRefCount(void* )
      { return 0; }

      static PointerMap_T& Get()
      {
        return sm_inst;
      }

    private:
      PointerMap_T() {}
      ~PointerMap_T() {}

    private:
      static PointerMap_T sm_inst;
    };

    // ------------------------------------------------------------------------
    // typedefs

    typedef PointerMap_T<>            PointerMap;

    // ------------------------------------------------------------------------
    // static var definitions

    template <typename T_BuildConfig>
    bool              PointerMap_T<T_BuildConfig>::m_mapIsDestroyed = true;

    template<typename T>
    PointerMap_T<T> PointerMap_T<T>::sm_inst;

    PointerMap_T<core_cfg::p_build_config::Release>
      PointerMap_T<core_cfg::p_build_config::Release>::sm_inst;
  }

  void DoStartTrackingPtr(void* a_pointer)
  {
    TLOC_ASSERT_LOW_LEVEL(PointerMap::Get().Exists(a_pointer) == false,
      "a_pointer is already managed by another (set of) smart pointers");
    PointerMap::Get().StartTracking(a_pointer);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void DoStopTrackingPtr(void* a_pointer)
  {
    TLOC_ASSERT_LOW_LEVEL(PointerMap::Get().Exists(a_pointer),
      "a_pointer has already been removed by another (set of) smart pointers");
    PointerMap::Get().StopTracking(a_pointer);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    DoIsPointerTracked(void* a_pointer)
  {
    return PointerMap::Get().Exists(a_pointer);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  tl_size
    DoAddVirtualPtrRef(void* a_pointer)
  {
    return PointerMap::Get().StartTrackingVirtual(a_pointer);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  tl_size
    DoRemoveVirtualPtrRef(void* a_pointer)
  {
    return PointerMap::Get().StopTrackingVirtual(a_pointer);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  tl_size
    DoGetVirtualRefCount(void* a_pointer)
  {
    return PointerMap::Get().GetVirtualRefCount(a_pointer);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    DoIsPointerTrackedVirtually(void* a_pointer)
  {
    return PointerMap::Get().ExistsVirtual(a_pointer);
  }

  //////////////////////////////////////////////////////////////////////////

  bool Unsafe_IsPtrTracked(void* a_pointer)
  {
    return PointerMap::Get().Exists(a_pointer);
  }

  tl_size Unsafe_GetPtrTrackedSize()
  {
    return PointerMap::Get().GetNumTrackedPointers();
  }

};};};};