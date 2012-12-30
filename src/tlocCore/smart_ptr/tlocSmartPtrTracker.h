#ifndef _TLOC_CORE_SMART_PTR_TRACKER_H_
#define _TLOC_CORE_SMART_PTR_TRACKER_H_

#include <tlocCore/tlocBase.h>
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
  extern void DoStartTrackingPtr(void* a_pointer);

  ///-------------------------------------------------------------------------
  /// @brief
  /// All smart pointers should call this function when they delete the
  /// pointer they are tracking.
  /// @note
  /// Do NOT call this function in your smart pointers destructor. Only
  /// call it when you are actually deleting the raw pointer.
  ///-------------------------------------------------------------------------
  extern void DoStopTrackingPtr(void* a_pointer);

  //////////////////////////////////////////////////////////////////////////
  // Not to be used as a reliable method as with a NoDebug policy above this
  // method always returns false. Use for tests only.
  extern bool     Unsafe_IsPtrTracked(void* a_pointer);
  extern tl_size  Unsafe_GetPtrTrackedSize();

};};};};

#endif