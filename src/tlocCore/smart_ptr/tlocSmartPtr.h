#ifndef _TLOC_CORE_SMART_PTR_H_
#define _TLOC_CORE_SMART_PTR_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>

namespace tloc { namespace core { namespace smart_ptr {

  ///-------------------------------------------------------------------------
  /// @brief Used only for distinguishing a normal object from a SmartPtr
  ///-------------------------------------------------------------------------
  class SmartPtr
  {
  protected: // to disallow the user from doing anything with this base class
    SmartPtr();
    ~SmartPtr();
  };

  namespace p_smart_ptr_tracker
  {
    struct NoDebug {};
    struct Debug {};
  };

  ///-------------------------------------------------------------------------
  /// @brief
  /// Base class for all smart pointers that is capable of tracking
  /// pointers to ensure a pointer is not 're-tracked' by a new set of
  /// smart pointers leading to double deletions. The default policy
  /// selected here by all derived smart pointers should be NoDebug as
  /// Debug is very expensive at runtime.
  ///-------------------------------------------------------------------------
  template <typename T_DebugPolicy = p_smart_ptr_tracker::NoDebug>
  class SmartPtrTracker_T : public SmartPtr
  {
  public:
    typedef T_DebugPolicy       policy_type;

  protected:
    SmartPtrTracker_T(void* a_pointer);

    void DoStopTrackingPtr(void* a_pointer);
  };

  template <>
  class SmartPtrTracker_T<p_smart_ptr_tracker::NoDebug> : public SmartPtr
  {
  public:
    typedef p_smart_ptr_tracker::NoDebug    policy_type;

  protected:
    SmartPtrTracker_T(void*) {}
    void DoStopTrackingPtr(void*) {}
  };

  //------------------------------------------------------------------------
  // typedefs
  typedef SmartPtrTracker_T<>           SmartPtrTracker;

  //////////////////////////////////////////////////////////////////////////
  // Not to be used as a reliable method as with a NoDebug policy above this
  // method always returns false. Use for tests only.
  extern bool     Unsafe_IsPtrTracked(void* a_pointer);
  extern tl_size  Unsafe_GetPtrTrackedSize();

};};};

#endif