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


};};};};

#endif