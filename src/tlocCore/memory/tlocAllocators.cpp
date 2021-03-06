#include "tlocAllocators.h"

#include <stdlib.h>

#ifdef TLOC_USE_CUSTOM_NEW_DELETE

# if defined (TLOC_COMPILER_VISUAL_CPP)
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

void* operator new[] (std::size_t size)
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
    if (core_mem::tracking::priv::DoIsMemoryAddressTracked(ptr))
    { core_mem::tracking::priv::DoUntrackMemoryAddress(ptr); }

    TL_FREE(ptr);
  }
}

void operator delete[] (void* ptr)
ALLOCATOR_DECL_NO_THROW()
{
  using namespace tloc;

  if (ptr)
  {
    if (core_mem::tracking::priv::DoIsMemoryAddressTracked(ptr))
    { core_mem::tracking::priv::DoUntrackMemoryAddress(ptr); }

    TL_FREE(ptr);
  }
}

void* operator new (std::size_t size, const std::nothrow_t&)
ALLOCATOR_DECL_NO_THROW()
{
  void *ptr = TL_MALLOC(size);
  return ptr; // Not throwing on purpose
}

void* operator new[] (std::size_t size, const std::nothrow_t&)
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
    if (core_mem::tracking::priv::DoIsMemoryAddressTracked(ptr))
    { core_mem::tracking::priv::DoUntrackMemoryAddress(ptr); }

    TL_FREE(ptr);
  }
}

void operator delete[] (void* ptr, const std::nothrow_t&)
ALLOCATOR_DECL_NO_THROW()
{
  using namespace tloc;

  if (ptr)
  {
    if (core_mem::tracking::priv::DoIsMemoryAddressTracked(ptr))
    { core_mem::tracking::priv::DoUntrackMemoryAddress(ptr); }

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
#include <tlocCore/tlocAssert.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace core { namespace memory {

  namespace tracking { namespace priv {

  namespace {

    namespace p_memory_tracker
    {
      class EnableTracker   {};
      class DisableTracker  {};
    };

#if defined(TLOC_ENABLE_MEMORY_TRACKING) && !defined(TLOC_RELEASE) && !defined(TLOC_RELEASE_DLL)
#define TLOC_MEMORY_TRACKING_SELECTION p_memory_tracker::EnableTracker
#else
#define TLOC_MEMORY_TRACKING_SELECTION p_memory_tracker::DisableTracker
#endif

    using core_utils::MemoryAddress;

    template<typename T_BuildConfig = TLOC_MEMORY_TRACKING_SELECTION>
    class MemoryTracker_T
    {
    public:
      typedef const void*                       mem_info_type;
      typedef const void*                       ptr_info_type;

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

      void TrackMemoryAddress(const void* a_memAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(IsTrackerAvail(), "Tracker Unavailable");

        TLOC_LOG_CORE_INFO_FILENAME_ONLY_IF(m_loggingEnabled)
          << "Tracking memory address (" << MemoryAddress(a_memAddress) << ")";

        memAddress_map_type::iterator itr = m_memAddresses.find(a_memAddress);
        if (itr != m_memAddresses.end())
        {
          // is it a memory address that was tracked directly by VirtualPtrs?
          if (itr->second.size() > 0 && itr->second[0] == nullptr)
          {
            UntrackMemoryAddress(a_memAddress);
          }
        }

        DoAssertAddressIsNotTracked(a_memAddress);
        m_memAddresses[a_memAddress] = ptr_array();
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void TrackConnectedMemoryAddress(const void* a_memAddress,
                                       const void* a_connectedAddress)
      {
        TLOC_LOG_CORE_INFO_FILENAME_ONLY_IF(m_loggingEnabled)
          << "Tracking connected memory address (" << MemoryAddress(a_memAddress)
          << ") to (" << MemoryAddress(a_memAddress) << ")";
        TLOC_ASSERT_LOW_LEVEL(a_memAddress != a_connectedAddress,
          "The connected memory address cannot be the same as a_memAddress");

        // Here we are adding another memory address to an already tracked
        // address (a_memAddress) which may happen in certain cases

        TLOC_ASSERT_LOW_LEVEL(IsTrackerAvail(), "Tracker Unavailable");

        DoAssertAddressIsTracked(a_memAddress);
        DoAssertAddressIsNotTracked(a_connectedAddress);

        TrackMemoryAddress(a_connectedAddress);

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

      void UntrackMemoryAddress(const void* a_memAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(IsTrackerAvail(), "Tracker Unavailable");

        TLOC_LOG_CORE_INFO_FILENAME_ONLY_IF(m_loggingEnabled)
          << "Untracking memory address (" << MemoryAddress(a_memAddress) << ")";
        DoAssertAddressIsTracked(a_memAddress);

        memAddress_map_type::iterator itrMemAddress =
          m_memAddresses.find(a_memAddress);

        ptr_array& ptrArray = itrMemAddress->second;

        for (ptr_array::iterator itr = ptrArray.begin(), itrEnd = ptrArray.end();
             itr != itrEnd; ++itr)
        {
          if (*itr != nullptr)
          { DoAssertPtrIsTracked(*itr); }

          TLOC_LOG_CORE_INFO_FILENAME_ONLY_IF( m_loggingEnabled )
            << "Invalidating vptr (" << MemoryAddress(*itr) << ")";

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
            TLOC_LOG_CORE_INFO_IF( m_loggingEnabled ) <<
              "Attempting to untrack connected address ("
              << MemoryAddress(*itrMem) << ")...";

            UntrackMemoryAddress(*itrMem);
          }

          m_memToMemMap.erase(a_memAddress);
        }

        m_memAddresses.erase(itrMemAddress);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void TrackPointerToMemoryAddress(const void* a_memAddress, 
                                       const void* a_ptrAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(IsTrackerAvail(), "Tracker Unavailable");

        TLOC_LOG_CORE_INFO_FILENAME_ONLY_IF( m_loggingEnabled )
          << "Tracking pointer (" << MemoryAddress(a_ptrAddress) << ") to "
          << "memory address (" << MemoryAddress(a_memAddress) << ")";
        DoAssertPtrIsNotTracked(a_ptrAddress);

        m_pointerToAddresses[a_ptrAddress] = a_memAddress;

        memAddress_map_type::iterator itrMemAddress =
          m_memAddresses.find(a_memAddress);

        // this should only happen when a 'naked new' is used or vptr is
        // pointing to an object allocated on the stack without using a VSO
        if (itrMemAddress == m_memAddresses.end())
        {
          TrackMemoryAddress(a_memAddress);
          itrMemAddress = m_memAddresses.find(a_memAddress);

          // mark this memory address as a non-tracked address (i.e. this is
          // tracked here only because our vptrs are pointing to it)
          itrMemAddress->second.push_back(nullptr);
        }

        TLOC_ASSERT_LOW_LEVEL(itrMemAddress != m_memAddresses.end(),
          "The memory address must be tracked");

        TLOC_ASSERT(core::find_all(itrMemAddress->second, a_ptrAddress) ==
          itrMemAddress->second.end(), "a_ptrAddress already exists");

        itrMemAddress->second.push_back(a_ptrAddress);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void UntrackPointerToMemoryAddress(const void* a_memAddress, 
                                         const void* a_ptrAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(IsTrackerAvail(), "Tracker Unavailable");

        TLOC_LOG_CORE_INFO_FILENAME_ONLY_IF( m_loggingEnabled )
          << "Untracking pointer (" << MemoryAddress(a_ptrAddress) << ") to "
          << "memory address (" << MemoryAddress(a_memAddress) << ")";
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

          TLOC_ASSERT_LOW_LEVEL(itr != itrMemAddress->second.end(),
            "Unable to find a_ptrAddress assigned to memAddress it is tracking");

          itrMemAddress->second.erase(itr);
          
          // is this the marked memory address which was only tracked because
          // a VirtualPtr began tracking a raw pointer? If yes, untrack
          // see TrackPointerToMemoryAddress() for push_back of nullptr
          if (itrMemAddress->second.size() == 1 && 
              *itrMemAddress->second.begin() == nullptr)
          {
            UntrackMemoryAddress(a_memAddress);
          }
        }

        m_pointerToAddresses.erase(a_ptrAddress);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      bool IsMemoryAddressTracked(const void* a_memAddress)
      {
        if (IsTrackerAvail() == false)
        { return false; }

        return m_memAddresses.find(a_memAddress) != m_memAddresses.end();
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      bool IsPointerTracked(const void* a_ptrAddress)
      {
        if (IsTrackerAvail() == false)
        { return false; }

        return m_pointerToAddresses.find(a_ptrAddress) != m_pointerToAddresses.end();
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      bool IsPointerToValidMemoryAddress(const void* a_ptrAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(IsTrackerAvail(), "Tracker Unavailable");

        DoAssertPtrIsTracked(a_ptrAddress);
        return m_pointerToAddresses[a_ptrAddress] != nullptr;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      size_type GetNumberOfPointersToMemAddresses(const void* a_memAddress)
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

      TLOC_DECL_AND_DEF_SETTER(bool, EnableLogging, m_loggingEnabled);
      TLOC_DECL_AND_DEF_GETTER(bool, IsLoggingEnabled, m_loggingEnabled);

    private:

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void DoAssertAddressIsTracked(const void* a_memAddress)
      {
        bool isAddressTracked = IsMemoryAddressTracked(a_memAddress);

        TLOC_LOG_CORE_ERR_FILENAME_ONLY_IF(isAddressTracked == false)
          << "Pointer (" << MemoryAddress(a_memAddress)
          << ") is not tracked. Possible causes include no calls to "
          << "TrackAddress() OR trying to remove memory address of an upcasted "
          << "pointer.";

        TLOC_ASSERT_LOW_LEVEL(isAddressTracked,
          "Memory address is not tracked. Possibly cause includes no calls "
          "to TrackAddress() OR trying to remove memory address of an upcasted "
          "pointer.");
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void DoAssertAddressIsNotTracked(const void* a_memAddress)
      {
        bool isAddressTracked = IsMemoryAddressTracked(a_memAddress);

        TLOC_LOG_CORE_ERR_FILENAME_ONLY_IF(isAddressTracked)
          << "Pointer (" << MemoryAddress(a_memAddress)
          << ") is already tracked. Possible causes include delete not calling "
          << "UntrackAddress() OR multiple calls to TrackAddress()";

        TLOC_ASSERT_LOW_LEVEL(isAddressTracked == false,
          "Memory address is already tracked. Possibly causes include delete "
          "not calling UntrackAddress() properly OR multiple calls to "
          "TrackAddress()");
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void DoAssertPtrIsTracked(const void* a_ptrAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(IsPointerTracked(a_ptrAddress) == true,
          "Memory address is NOT tracked. Possibly causes include no calls to "
          "TrackPointerToAddress()");
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void DoAssertPtrIsNotTracked(const void* a_ptrAddress)
      {
        TLOC_ASSERT_LOW_LEVEL(IsPointerTracked(a_ptrAddress) == false,
          "Pointer address is already tracked. Possibly causes include dtor "
          "of tracking class not calling UntrackPointerToAddress OR multiple "
          "calls to TrackPointerToAddress");
      }

    public:
      MemoryTracker_T()
        : m_loggingEnabled(false)
      { s_trackerAvailable = true; }

      ~MemoryTracker_T()
      { s_trackerAvailable = false; }

      static this_type& Get()
      { return s_tracker; }

      static bool
        IsTrackerAvail()
      { return s_trackerAvailable && (s_trackerDisabled == false); }

      static void
        Disable()
      { s_trackerDisabled = true; }

    private:
      memAddress_map_type           m_memAddresses;
      mem_to_mem_map                m_memToMemMap;
      pointer_map_type              m_pointerToAddresses;
      bool                          m_loggingEnabled;

      static bool                   s_trackerAvailable;
      static bool                   s_trackerDisabled;
      static this_type              s_tracker;
    };

    template <typename T_BuildConfig>
    bool MemoryTracker_T<T_BuildConfig>::s_trackerAvailable = false;

    template <typename T_BuildConfig>
    bool MemoryTracker_T<T_BuildConfig>::s_trackerDisabled = false;

    template <typename T_BuildConfig>
    MemoryTracker_T<T_BuildConfig>
      MemoryTracker_T<T_BuildConfig>::s_tracker;

    // ///////////////////////////////////////////////////////////////////////
    // Relase build

    template <>
    class MemoryTracker_T<p_memory_tracker::DisableTracker>
    {
    public:
      typedef const void*                       mem_info_type;
      typedef const void*                       ptr_info_type;

      typedef p_memory_tracker::DisableTracker  build_config;
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

      void TrackMemoryAddress(const void* )
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void TrackConnectedMemoryAddress(const void* , const void* )
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void UntrackMemoryAddress(const void* )
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void TrackPointerToMemoryAddress(const void* , const void* )
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void UntrackPointerToMemoryAddress(const void* , const void* )
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      bool IsMemoryAddressTracked(const void* )
      { return true; }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      bool IsPointerTracked(const void* )
      { return false; }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      bool IsPointerToValidMemoryAddress(const void* )
      { return true; }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      size_type GetNumberOfPointersToMemAddresses(const void* )
      { return 0; }

      void EnableLogging(bool)
      { }

      bool IsLoggingEnabled()
      { return false; }

    public:

      static this_type& Get()
      { return s_tracker; }

      static bool
        IsTrackerAvail()
      { return false; }

      static void
        Disable()
      { }

    private:
      static this_type              s_tracker;
    };

    MemoryTracker_T<p_memory_tracker::DisableTracker>
      MemoryTracker_T<p_memory_tracker::DisableTracker>::s_tracker;

    // -----------------------------------------------------------------------
    // typedefs

    typedef MemoryTracker_T<>               MemoryTracker;

  }; // priv

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoTrackMemoryAddress(const void* a_memAddress)
  {
    if (a_memAddress == nullptr)
    { return; }

    if (MemoryTracker::IsTrackerAvail())
    { MemoryTracker::Get().TrackMemoryAddress(a_memAddress); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoTrackConnectedMemoryAddress(const void* a_memAddress,
                                  const void* a_connectedAddress)
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
    DoUntrackMemoryAddress(const void* a_memAddress)
  {
    if (MemoryTracker::IsTrackerAvail())
    { MemoryTracker::Get().UntrackMemoryAddress(a_memAddress); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoTrackPointerToMemoryAddress(const void* a_memAddress, const void* a_ptr)
  {
    if (MemoryTracker::IsTrackerAvail())
    {
      MemoryTracker::Get().TrackPointerToMemoryAddress(a_memAddress, a_ptr);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoUntrackPointerToMemoryAddress(const void* a_memAddress, const void* a_ptr)
  {
    if (MemoryTracker::IsTrackerAvail())
    {
      MemoryTracker::Get().UntrackPointerToMemoryAddress(a_memAddress, a_ptr);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    DoIsPointerToValidMemoryAddress(const void* a_ptr)
  {
    if (a_ptr == nullptr)
    { return false; }

    if (MemoryTracker::IsTrackerAvail())
    {
      return MemoryTracker::Get().IsPointerToValidMemoryAddress(a_ptr);
    }

    return true;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    DoIsMemoryAddressTracked(const void* a_memAddress)
  {
    if (a_memAddress == nullptr)
    { return false; }

    if (MemoryTracker::IsTrackerAvail())
    {
      return MemoryTracker::Get().IsMemoryAddressTracked(a_memAddress);
    }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoAssertPointerToValidMemoryAddress(const void* a_memAddress, const void* a_ptr)
  {
    if (a_memAddress == nullptr)
    { return; }

    bool isPointerToValidMemAddress = DoIsPointerToValidMemoryAddress(a_ptr);

    TLOC_LOG_CORE_ERR_FILENAME_ONLY_IF(isPointerToValidMemAddress == false)
      << "Pointer (" << MemoryAddress(a_ptr) << ") is pointing to a invalid/deleted "
      << "memory address (" << MemoryAddress(a_memAddress) << ").";

    TLOC_ASSERT_LOW_LEVEL(isPointerToValidMemAddress,
      "Pointer is pointing to invalid/deleted memory address");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  size_t
    DoGetNumberOfPointersToMemoryAddress(const void* a_memAddress)
  {
    return MemoryTracker::Get().GetNumberOfPointersToMemAddresses(a_memAddress);
  }

};};};};};

namespace tloc { namespace core { namespace memory { namespace tracking {

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoEnableLogging()
  {
    priv::MemoryTracker::Get().EnableLogging(true);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoDisableLogging()
  {
    priv::MemoryTracker::Get().EnableLogging( true );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DoDisableTracking()
  {
    priv::MemoryTracker::Get().Disable();
    TLOC_LOG_CORE_WARN() << "Memory tracking has been disabled";
  }

};};};};

#endif