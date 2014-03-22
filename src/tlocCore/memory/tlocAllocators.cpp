#include "tlocAllocators.h"

#ifdef TLOC_USE_CUSTOM_NEW_DELETE

# if defined (_MSC_VER)
#   define ALLOCATOR_DECL_THROW(type)
#   define ALLOCATOR_DECL_NO_THROW()
# else
#   define ALLOCATOR_DECL_THROW(type) throw(type)
#   define ALLOCATOR_DECL_NO_THROW()  throw()
# endif

void* operator new (std::size_t size)
ALLOCATOR_DECL_THROW(std::bad_alloc)
{
  void *ptr = TL_MALLOC(size);
  return ptr; // Not throwing on purpose
}

void operator delete (void* ptr)
ALLOCATOR_DECL_NO_THROW()
{
  using namespace tloc;

  if (ptr)
  {
    if (core_mem::priv::DoIsMemoryAddressTracked(ptr))
    { core_mem::priv::DoUntrackMemoryAddress(ptr); }

    TL_FREE(ptr);
  }
}

void* operator new (std::size_t size, const std::nothrow_t&)
ALLOCATOR_DECL_NO_THROW()
{
  void *ptr = TL_MALLOC(size);
  return ptr; // Not throwing on purpose
}

void operator delete (void* ptr, const std::nothrow_t&)
ALLOCATOR_DECL_NO_THROW()
{
  using namespace tloc;

  if (ptr)
  {
    if (core_mem::priv::DoIsMemoryAddressTracked(ptr))
    { core_mem::priv::DoUntrackMemoryAddress(ptr); }

    TL_FREE(ptr);
  }
}

#include <tlocCore/containers/tlocHashmap.h>
#include <tlocCore/containers/tlocHashmap.inl.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/configs/tlocBuildConfig.h>
#include <tlocCore/utilities/tlocPointerUtils.h>
#include <tlocCore/logging/tlocLogger.h>

namespace tloc { namespace core { namespace memory { namespace priv {

  namespace {

    template<typename T_BuildConfig = core_cfg::BuildConfig::build_config_type>
    class MemoryTracker_T
    {
    public:
      typedef void*                             mem_info_type;
      typedef void*                             ptr_info_type;

      typedef T_BuildConfig                     build_config;
      typedef MemoryTracker_T<build_config>     this_type;

      typedef core_conts::Array<mem_info_type>  mem_array;
      typedef core_conts::Array<ptr_info_type>  ptr_array;

      typedef core_conts::HashMap
        <mem_info_type, ptr_array>              memAddress_map_type;

      typedef core_conts::HashMap
        <mem_info_type, mem_array>              mem_to_mem_map;

      typedef core_conts::HashMap
        <ptr_info_type, mem_info_type>          pointer_map_type;

      typedef tl_size                           size_type;

    public:
      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void TrackMemoryAddress(void* a_memAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(IsTrackerAvail(), "Tracker Unavailable");

        DoAssertAddressIsNotTracked(a_memAddress);

        m_memAddresses[a_memAddress] = ptr_array();
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void TrackConnectedMemoryAddress(void* a_memAddress,
                                       void* a_connectedAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(a_memAddress != a_connectedAddress,
          "The connected memory address cannot be the same as a_memAddress");

        // Here we are adding another memory address to an already tracked
        // address (a_memAddress) which may happen in certain cases

        TLOC_ASSERT_LOW_LEVEL(IsTrackerAvail(), "Tracker Unavailable");

        DoAssertAddressIsTracked(a_memAddress);
        DoAssertAddressIsNotTracked(a_connectedAddress);

        m_memAddresses[a_connectedAddress] = ptr_array();

        mem_to_mem_map::iterator itrMemToMem = m_memToMemMap.find(a_memAddress);

        if (itrMemToMem == m_memToMemMap.end())
        {
          m_memToMemMap[a_memAddress] = ptr_array();
          itrMemToMem = m_memToMemMap.find(a_memAddress);
        }

        TLOC_ASSERT_LOW_LEVEL
          (core::find_all(itrMemToMem->second, a_connectedAddress)
          == itrMemToMem->second.end(), "Additional memory address is already "
          "added to a_memAddress. Too many calls to TrackConnectedMemoryAddress()");

        itrMemToMem->second.push_back(a_connectedAddress);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void UntrackMemoryAddress(void* a_memAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(IsTrackerAvail(), "Tracker Unavailable");

        DoAssertAddressIsTracked(a_memAddress);

        memAddress_map_type::iterator itrMemAddress =
          m_memAddresses.find(a_memAddress);

        ptr_array& ptrArray = itrMemAddress->second;

        for (ptr_array::iterator itr = ptrArray.begin(), itrEnd = ptrArray.end();
             itr != itrEnd; ++itr)
        {
          DoAssertPtrIsTracked(*itr);

          // invalidate the pointer to address - this address may actually be
          // different than a_memAddress because of multiple inheritance (in
          // most cases it will be the same however)
          m_pointerToAddresses[*itr] = nullptr;
        }

        // untrack connected addresses as well
        mem_to_mem_map::iterator itrMemToMem = m_memToMemMap.find(a_memAddress);

        if (itrMemToMem != m_memToMemMap.end())
        {
          mem_array::iterator itrMem = itrMemToMem->second.begin();
          mem_array::iterator itrMemEnd = itrMemToMem->second.end();

          for (; itrMem != itrMemEnd; ++itrMem)
          {
            UntrackMemoryAddress(*itrMem);
          }
        }

        m_memAddresses.erase(itrMemAddress);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void TrackPointerToMemoryAddress(void* a_memAddress, void* a_ptrAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(IsTrackerAvail(), "Tracker Unavailable");

        DoAssertPtrIsNotTracked(a_ptrAddress);

        m_pointerToAddresses[a_ptrAddress] = a_memAddress;

        memAddress_map_type::iterator itrMemAddress =
          m_memAddresses.find(a_memAddress);

        // this should only happen when a 'naked new' is used
        if (itrMemAddress == m_memAddresses.end())
        {
          TrackMemoryAddress(a_memAddress);
          itrMemAddress = m_memAddresses.find(a_memAddress);
        }

        TLOC_ASSERT_LOW_LEVEL(itrMemAddress != m_memAddresses.end(),
          "The memory address must be tracked");

        TLOC_ASSERT(core::find_all(itrMemAddress->second, a_ptrAddress) ==
          itrMemAddress->second.end(), "a_ptrAddress already exists");

        itrMemAddress->second.push_back(a_ptrAddress);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void UntrackPointerToMemoryAddress(void* a_memAddress, void* a_ptrAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(IsTrackerAvail(), "Tracker Unavailable");

        DoAssertPtrIsTracked(a_ptrAddress);

        pointer_map_type::iterator itrPtr =
          m_pointerToAddresses.find(a_ptrAddress);

        if (itrPtr->second != nullptr)
        {
          TLOC_ASSERT_LOW_LEVEL(itrPtr->second == a_memAddress,
            "Pointer is tracking a different memory address than previously "
            "recorded. Possible reason is calling TrackPointerToMemoryAddress "
            "with a different memory address.");

          memAddress_map_type::iterator itrMemAddress =
            m_memAddresses.find(itrPtr->second);

          ptr_array::iterator itr =
            core::find_all(itrMemAddress->second, a_ptrAddress);

          TLOC_ASSERT(itr != itrMemAddress->second.end(),
            "Unable to find a_ptrAddress assigned to memAddress it is tracking");

          itrMemAddress->second.erase(itr);
        }

        m_pointerToAddresses.erase(a_ptrAddress);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      bool IsMemoryAddressTracked(void* a_memAddress)
      {
        if (IsTrackerAvail() == false)
        { return false; }

        return m_memAddresses.find(a_memAddress) != m_memAddresses.end();
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      bool IsPointerTracked(void* a_ptrAddress)
      {
        if (IsTrackerAvail() == false)
        { return false; }

        return m_pointerToAddresses.find(a_ptrAddress) != m_pointerToAddresses.end();
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      bool IsPointerToValidMemoryAddress(void* a_ptrAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(IsTrackerAvail(), "Tracker Unavailable");

        DoAssertPtrIsTracked(a_ptrAddress);
        return m_pointerToAddresses[a_ptrAddress] != nullptr;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      size_type GetNumberOfPointersToMemAddresses(void* a_memAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(IsTrackerAvail(), "Tracker Unavailable");

        memAddress_map_type::iterator itrMemAddress =
          m_memAddresses.find(a_memAddress);

        size_type total = 0;

        if (itrMemAddress != m_memAddresses.end())
        {
          total += itrMemAddress->second.size();
        }

        mem_to_mem_map::iterator itrMemToMem = m_memToMemMap.find(a_memAddress);
        if (itrMemToMem != m_memToMemMap.end())
        {
          mem_array::iterator itrMem    = itrMemToMem->second.begin();
          mem_array::iterator itrMemEnd = itrMemToMem->second.end();

          for (; itrMem != itrMemEnd; ++itrMem)
          {
            total += GetNumberOfPointersToMemAddresses(*itrMem);
          }
        }

        return total;
      }

    private:

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void DoAssertAddressIsTracked(void* a_memAddress)
      {
        TLOC_ASSERT(IsMemoryAddressTracked(a_memAddress) == true,
          "Memory address is not tracked. Possibly cause includes no calls "
          "to TrackAddress() OR trying to remove memory address of an upcasted "
          "pointer.");
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void DoAssertAddressIsNotTracked(void* a_memAddress)
      {
        TLOC_ASSERT(IsMemoryAddressTracked(a_memAddress) == false,
          "Memory address is already tracked. Possibly causes include delete "
          "not calling UntrackAddress() properly OR multiple calls to "
          "TrackAddress");
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void DoAssertPtrIsTracked(void* a_ptrAddress)
      {
        TLOC_ASSERT(IsPointerTracked(a_ptrAddress) == true,
          "Memory address is already tracked. Possibly causes include no calls "
          "to TrackPointerToAddress()");
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void DoAssertPtrIsNotTracked(void* a_ptrAddress)
      {
        TLOC_ASSERT(IsPointerTracked(a_ptrAddress) == false,
          "Pointer address is already tracked. Possibly causes include dtor "
          "of tracking class not calling UntrackPointerToAddress OR multiple "
          "calls to TrackPointerToAddress");
      }

    public:
      MemoryTracker_T()
      { s_trackerAvailable = true; }

      ~MemoryTracker_T()
      { s_trackerAvailable = false; }

      static this_type& Get()
      { return s_tracker; }

      static bool
        IsTrackerAvail()
      { return s_trackerAvailable; }

    private:
      memAddress_map_type           m_memAddresses;
      mem_to_mem_map                m_memToMemMap;
      pointer_map_type              m_pointerToAddresses;

      static bool                   s_trackerAvailable;
      static this_type              s_tracker;
    };

    template <typename T_BuildConfig>
    bool MemoryTracker_T<T_BuildConfig>::s_trackerAvailable = false;

    template <typename T_BuildConfig>
    MemoryTracker_T<T_BuildConfig>
      MemoryTracker_T<T_BuildConfig>::s_tracker;

    // ///////////////////////////////////////////////////////////////////////
    // Relase build

    template <>
    class MemoryTracker_T<core_cfg::p_build_config::Release>
    {
    public:
      typedef void*                             mem_info_type;
      typedef void*                             ptr_info_type;

      typedef core_cfg::p_build_config::Release build_config;
      typedef MemoryTracker_T<build_config>     this_type;

      typedef core_conts::Array<mem_info_type>  mem_array;
      typedef core_conts::Array<ptr_info_type>  ptr_array;

      typedef core_conts::HashMap
        <mem_info_type, ptr_array>              memAddress_map_type;

      typedef core_conts::HashMap
        <mem_info_type, mem_array>              mem_to_mem_map;

      typedef core_conts::HashMap
        <ptr_info_type, mem_info_type>          pointer_map_type;

      typedef tl_size                           size_type;

    public:
      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void TrackMemoryAddress(void* )
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void TrackConnectedMemoryAddress(void* , void* )
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void UntrackMemoryAddress(void* )
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void TrackPointerToMemoryAddress(void* , void* )
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void UntrackPointerToMemoryAddress(void* , void* )
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      bool IsMemoryAddressTracked(void* )
      { return true; }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      bool IsPointerTracked(void* )
      { return false; }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      bool IsPointerToValidMemoryAddress(void* )
      { return true; }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      size_type GetNumberOfPointersToMemAddresses(void* )
      { return 0; }

    public:

      static this_type& Get()
      { return s_tracker; }

      static bool
        IsTrackerAvail()
      { return false; }

    private:
      static this_type              s_tracker;
    };

    MemoryTracker_T<core_cfg::p_build_config::Release>
      MemoryTracker_T<core_cfg::p_build_config::Release>::s_tracker;

    // -----------------------------------------------------------------------
    // typedefs

    typedef MemoryTracker_T<>               MemoryTracker;

  }; // priv

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoTrackMemoryAddress(void* a_memAddress)
  {
    if (a_memAddress == nullptr)
    { return; }

    if (MemoryTracker::IsTrackerAvail())
    { MemoryTracker::Get().TrackMemoryAddress(a_memAddress); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoTrackConnectedMemoryAddress(void* a_memAddress,
                                  void* a_connectedAddress)
  {
    if (a_memAddress == nullptr)
    { return; }

    if (a_memAddress == a_connectedAddress)
    { return; }

    if (MemoryTracker::IsTrackerAvail())
    {
      MemoryTracker::Get().
        TrackConnectedMemoryAddress(a_memAddress, a_connectedAddress);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoUntrackMemoryAddress(void* a_memAddress)
  {
    if (MemoryTracker::IsTrackerAvail())
    { MemoryTracker::Get().UntrackMemoryAddress(a_memAddress); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoTrackPointerToMemoryAddress(void* a_memAddress, void* a_ptr)
  {
    MemoryTracker::Get().TrackPointerToMemoryAddress(a_memAddress, a_ptr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoUntrackPointerToMemoryAddress(void* a_memAddress, void* a_ptr)
  {
    MemoryTracker::Get().UntrackPointerToMemoryAddress(a_memAddress, a_ptr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    DoIsPointerToValidMemoryAddress(void* a_ptr)
  {
    if (a_ptr == nullptr)
    { return false; }

     return MemoryTracker::Get().IsPointerToValidMemoryAddress(a_ptr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    DoIsMemoryAddressTracked(void* a_memAddress)
  {
    if (a_memAddress == nullptr)
    { return false; }

    return MemoryTracker::Get().IsMemoryAddressTracked(a_memAddress);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoAssertPointerToValidMemoryAddress(void* a_memAddress, void* a_ptr)
  {
    if (a_memAddress == nullptr)
    { return; }

    bool isPointerToValidMemAddress = DoIsPointerToValidMemoryAddress(a_ptr);

    TLOC_LOG_CORE_ERR_IF(isPointerToValidMemAddress == false)
      << "Pointer (" << core_utils::GetMemoryAddress(a_ptr)
      << ") is pointing to a invalid/deleted "
      << "memory address (" << core_utils::GetMemoryAddress(a_memAddress)
      << ").";

    TLOC_ASSERT_LOW_LEVEL(isPointerToValidMemAddress,
      "Pointer is pointing to invalid/deleted memory address");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  size_t
    DoGetNumberOfPointersToMemoryAddress(void* a_memAddress)
  {
    return MemoryTracker::Get().GetNumberOfPointersToMemAddresses(a_memAddress);
  }

};};};};

#endif