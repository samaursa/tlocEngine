#ifndef TLOC_INPUT_IMPL_H
#define TLOC_INPUT_IMPL_H

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/base_classes/tlocPlatformImplBase.h>

namespace tloc { namespace input { namespace priv {

  ///-------------------------------------------------------------------------
  /// Input implementation that must be specialized for each platform
  ///
  /// \tparam T_ParentKeyboard Platform-independant keyboard implementation that
  ///                          will eventually create platform-specific
  ///                          implementations
  ///-------------------------------------------------------------------------
  template <class T_ParentInputManager> class InputManagerImpl;

  template <class T_ParentInputManager, class T_ParamList>
  class InputManagerImplBase
    : public core::base_classes::ImplBase<T_ParentInputManager>
  {
  public:
    typedef core::base_classes::ImplBase<T_ParentInputManager>  base_type;
    typedef typename base_type::parent_type                     parent_type;
    typedef typename base_type::platform_type                   platform_type;

    typedef T_ParamList                                   param_list_type;
    typedef u32                                           index_type;

    InputManagerImplBase(parent_type* a_parent, param_list_type a_params)
    : base_type(a_parent), m_params(a_params)
    {
    }

    const param_list_type& GetParams() const
    {
      return m_params;
    }

  protected:

    param_list_type       m_params;
  };

};};};

#endif