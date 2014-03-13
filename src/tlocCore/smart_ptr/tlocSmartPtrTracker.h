#ifndef _TLOC_CORE_SMART_PTR_TRACKER_H_
#define _TLOC_CORE_SMART_PTR_TRACKER_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypes.h>

namespace tloc { namespace core { namespace smart_ptr { namespace priv {

  namespace p_smart_ptr_tracker
  {
    struct NoDebug {};
    struct Debug {};
  };

  //------------------------------------------------------------------------
  // typedefs
  typedef p_smart_ptr_tracker::NoDebug        current_smart_ptr_tracking_policy;

  ///-------------------------------------------------------------------------
  /// @brief
  /// All smart pointers should call this function when their
  /// constructor takes in a raw pointer directly.
  ///-------------------------------------------------------------------------
  void DoStartTrackingPtr(void* a_pointer);

  ///-------------------------------------------------------------------------
  /// @brief
  /// All smart pointers should call this function when they delete the
  /// pointer they are tracking.
  /// @note
  /// Do NOT call this function in your smart pointers destructor. Only
  /// call it when you are actually deleting the raw pointer.
  ///-------------------------------------------------------------------------
  void DoStopTrackingPtr(void* a_pointer);

  ///-------------------------------------------------------------------------
  /// @brief
  /// Checks whether the pointer is already tracked by a smart_ptr
  ///-------------------------------------------------------------------------
  bool DoIsPointerTracked(void* a_pointer);

  ///-------------------------------------------------------------------------
  /// @brief
  /// Internal use only by VirtualPointer
  ///-------------------------------------------------------------------------
  tl_size DoAddVirtualPtrRef(void* a_pointer);

  ///-------------------------------------------------------------------------
  /// @brief
  /// Internal use only by VirtualPointer. Same as above, but this time the
  /// incoming pointer is connected to this pointer. This case can happen with
  /// some instances of multiple inheritance where a Base* will have a diff.
  /// address than the Derived*
  ///-------------------------------------------------------------------------
  tl_size DoAddVirtualPtrRef(void* a_pointer, void* a_connectedPointer);

  ///-------------------------------------------------------------------------
  /// @brief
  /// Internal use only by VirtualPointer
  ///-------------------------------------------------------------------------
  tl_size DoRemoveVirtualPtrRef(void* a_pointer);

  ///-------------------------------------------------------------------------
  /// @brief
  /// Internal use only by VirtualPointer
  ///-------------------------------------------------------------------------
  tl_size DoGetVirtualRefCount(void* a_pointer);

  bool    DoIsPointerTrackedVirtually(void* a_pointer);

  //////////////////////////////////////////////////////////////////////////
  // Not to be used as a reliable method as with a NoDebug policy above this
  // method always returns false. Use for tests only.
  bool     Unsafe_IsPtrTracked(void* a_pointer);
  tl_size  Unsafe_GetPtrTrackedSize();
  tl_size  Unsafe_GetVirtualPtrTrackedSize();

};};};};

#endif