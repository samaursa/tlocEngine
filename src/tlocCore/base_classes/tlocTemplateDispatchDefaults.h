#ifndef TLOC_TEMPLATE_DISPATCH_DEFAULTS_H
#define TLOC_TEMPLATE_DISPATCH_DEFAULTS_H

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocList.h>
#include <tlocCore/containers/tlocArray.inl>
#include <tlocCore/containers/tlocList.inl>
#include <tlocCore/utilities/tlocUtils.h>

#include "tlocTemplateDispatch.h"

namespace tloc { namespace core {

  //------------------------------------------------------------------------
  // Helpers for the base group

  template <typename T, typename T_CallbackMethods>
  struct CallbackGroupTArray
  {
    DECL_TYPEDEF_HELPER(CallbackGroupTArray);
    typedef CallbackGroupT<T_CallbackMethods, Array<T*> > type;
  };

  template <typename T, typename T_CallbackMethods>
  struct CallbackGroupTList
  {
    DECL_TYPEDEF_HELPER(CallbackGroupTList);
    typedef CallbackGroupT<T_CallbackMethods, List<T*> > type;
  };

  //------------------------------------------------------------------------
  // Helpers for the dispatcher base

  template <typename T_Callbacks, template <typename T> class T_CallbackGroupT>
  struct DispatcherBaseArray
  {
    DECL_TYPEDEF_HELPER(DispatcherBaseArray);
    typedef DispatcherBase<T_Callbacks, T_CallbackGroupT, ArrayOrderedTemp> type;
  };

  //template <typename T_Callbacks, template <typename T> class T_CallbackGroupT>
  //struct DispatcherBaseList
  //{
  //  DECL_TYPEDEF_HELPER(DispatcherBaseList);
  //  typedef DispatcherBase<T_Callbacks, T_CallbackGroupT, List> type;
  //};

};};

#endif