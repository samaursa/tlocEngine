#ifndef TLOC_TEMPLATE_DISPATCH_DEFAULTS_H
#define TLOC_TEMPLATE_DISPATCH_DEFAULTS_H

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocList.h>
#include <tlocCore/containers/tlocArray.inl>
#include <tlocCore/containers/tlocList.inl>
#include <tlocCore/utilities/tlocUtils.h>

#include "tlocTemplateDispatch.h"

namespace tloc { namespace core { namespace base_classes {

  //------------------------------------------------------------------------
  // Helpers for the base group

  template <typename T, typename T_CallbackMethods>
  struct CallbackGroupTArray : public utils::TypedefHelperBase<T>
  {
    typedef CallbackGroupT<T_CallbackMethods, containers::Array<T*> > type;
  };

  template <typename T, typename T_CallbackMethods>
  struct CallbackGroupTList : public utils::TypedefHelperBase<T>
  {
    typedef CallbackGroupT<T_CallbackMethods, containers::List<T*> > type;
  };

  //------------------------------------------------------------------------
  // Helpers for the dispatcher base

  template <typename T_Callbacks, template <typename T> class T_CallbackGroupT>
  struct DispatcherBaseArray : public utils::TypedefHelperBase<T_Callbacks>
  {
    typedef DispatcherBase<T_Callbacks, T_CallbackGroupT,
                           containers::ArrayOrderedTemp> type;
  };

  //template <typename T_Callbacks, template <typename T> class T_CallbackGroupT>
  //struct DispatcherBaseList
  //{
  //  DECL_TYPEDEF_HELPER(DispatcherBaseList);
  //  typedef DispatcherBase<T_Callbacks, T_CallbackGroupT, List> type;
  //};

};};};

#endif