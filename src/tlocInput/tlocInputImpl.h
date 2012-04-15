#ifndef TLOC_INPUT_IMPL_H
#define TLOC_INPUT_IMPL_H

#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocPlatformImplBase.h"

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
  class InputManagerImplBase: public core::ImplBase<T_ParentInputManager>
  {
  public:
    typedef ImplBase<T_ParentInputManager>                base_type;
    using   base_type::parent_type;
    using   base_type::platform_type;

    typedef T_ParamList                                   param_list_type;
    typedef u32                                           index_type;

    InputManagerImplBase(parent_type* a_parent, param_list_type a_params)
      : ImplBase(a_parent), m_params(a_params)
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