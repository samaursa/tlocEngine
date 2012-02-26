#ifndef TLOC_TEMPLATE_DISPATCH_DEFAULTS_H
#define TLOC_TEMPLATE_DISPATCH_DEFAULTS_H

#include "tlocTemplateDispatch.h"
#include "tlocArray.h"
#include "tlocList.h"
#include "tlocArray.inl"
#include "tlocList.inl"

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
    typedef DispatcherBase<T_Callbacks, T_CallbackGroupT, Array> type;
  };

  //template <typename T_Callbacks, template <typename T> class T_CallbackGroupT>
  //struct DispatcherBaseList
  //{
  //  DECL_TYPEDEF_HELPER(DispatcherBaseList);
  //  typedef DispatcherBase<T_Callbacks, T_CallbackGroupT, List> type;
  //};

};};

#endif