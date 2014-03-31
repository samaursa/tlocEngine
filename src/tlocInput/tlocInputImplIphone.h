#ifndef TLOC_INPUT_IPHONE_H
#define TLOC_INPUT_IPHONE_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocAny.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTemplateParams.h>

#include "tlocInputManager.h"
#include "tlocInputImpl.h"
#include "tlocInputTypes.h"

namespace tloc { namespace input {

  typedef ParamList<core_t::Any> input_param_type;

};};

namespace tloc { namespace input { namespace priv {

  // TODO: Make InputDeviceInfo NOT use void*
  struct InputDeviceInfo
  {
    bool  m_available;
    void* m_devicePtr;
  };

  template <typename T_ParentInputManager>
  class InputManagerImpl
    : public InputManagerImplBase<T_ParentInputManager, input_param_type>
  {
  public:
    typedef T_ParentInputManager                    parent_type;
    typedef input_param_type                        param_type;
    typedef InputManagerImpl<parent_type>           this_type;
    typedef InputManagerImplBase
      <parent_type, param_type>                     base_type;

    typedef core_t::Any /* (UIWindow*) */           window_handle_type;
    typedef core_t::Any /* (OpenGLView*) */         view_handle_type;

    typedef typename parent_type::platform_type       platform_type;
    typedef typename parent_type::policy_type         policy_type;
    typedef typename parent_type::size_type           size_type;
    typedef typename parent_type::input_type          input_type;
    
    //------------------------------------------------------------------------
    // using declarations for access to base class
    using base_type::m_params;

    InputManagerImpl(parent_type& a_parent, param_type a_params);

    ~InputManagerImpl();

    ///-------------------------------------------------------------------------
    /// Initializes the input manager for the windows platform
    ///
    /// @param  a_key The key.
    ///-------------------------------------------------------------------------
    size_type Initialize();

    ///-------------------------------------------------------------------------
    /// Creates the correct input type. An unsupported or mismatched input type
    /// will result in assertion failure.
    ///
    /// @return The new input type
    ///-------------------------------------------------------------------------
    template <typename T_InputObject>
    T_InputObject*  CreateHID(param_options::value_type a_params);

    ///-------------------------------------------------------------------------
    /// Updates the given a_inputType. Pass only one type.
    ///
    /// @param  a_inputType Type of HID.
    ///-------------------------------------------------------------------------
    void Update(input_type a_inputType);

    void Reset(input_type a_inputType);

    ///-------------------------------------------------------------------------
    /// Returns an HID with the given type at the given index
    ///
    /// @param  a_inputType Type of the input.
    /// @param  a_index     Zero-based index of a.
    ///
    /// @return The HID of type a_inputType at the specified index
    ///-------------------------------------------------------------------------
    template <typename T_InputObject>
    T_InputObject* GetHID(size_type a_index);

    ///-------------------------------------------------------------------------
    /// Get the number of a given HID type.
    ///
    /// @param  a_inputType Type of the input.
    ///
    /// @return The total number of input types created.
    ///-------------------------------------------------------------------------
    size_type GetTotalHID(input_type a_inputType);

  public:
    //------------------------------------------------------------------------
    // Platform specific methods
    
    window_handle_type GetWindowHandle();
    
  private:
    
    view_handle_type DoGetOpenGLViewHandle();

    InputDeviceInfo m_iphoneHIDs[p_hid::Count::m_index];

  };

};};};

#endif