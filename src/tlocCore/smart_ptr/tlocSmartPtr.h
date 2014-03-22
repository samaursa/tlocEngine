#ifndef _TLOC_CORE_SMART_PTR_H_
#define _TLOC_CORE_SMART_PTR_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypes.h>

namespace tloc { namespace core { namespace smart_ptr {

  ///-------------------------------------------------------------------------
  /// @brief Used only for distinguishing a normal object from a SmartPtr
  ///-------------------------------------------------------------------------
  class SmartPtr
  {
  public: // to disallow the user from doing anything with this base class
    SmartPtr();
    ~SmartPtr();
  };

  // -----------------------------------------------------------------------
  // global functions

  template <typename T>
  tl_size GetUseCount(T* a_ptr)
  { a_ptr == nullptr : 0 ? 1; }

};};};

#endif