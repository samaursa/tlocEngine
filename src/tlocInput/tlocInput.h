#ifndef TLOC_INPUT_H
#define TLOC_INPUT_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>

#include "tlocInputImpl.h"
#include "tlocInputTypes.h"

namespace tloc { namespace input {

  // TODO: Create parameter list header file in core with lists up to 50
  ///-------------------------------------------------------------------------
  /// Platform independent list of parameters.
  ///
  /// Incorrect parameter types will result in linking errors.
  ///-------------------------------------------------------------------------
  template <typename T1,
            typename T2 = TLOC_DUMMY_PARAM,
            typename T3 = TLOC_DUMMY_PARAM,
            typename T4 = TLOC_DUMMY_PARAM>
  struct InputParameterList
  {
    T1  m_param1;
    T2  m_param2;
    T3  m_param3;
    T4  m_param4;
  };


  ///-------------------------------------------------------------------------
  /// Manager for all inputs. You can create as many of them as you want. A
  /// manager may handle buffered or unbuffered inputs but not both. If you
  /// want a buffered keyboard and an unbuffered mouse, you will need to create
  /// two managers.
  ///
  /// This manager follows the RAII principle.
  ///-------------------------------------------------------------------------
  template <typename T_Policy = InputPolicy::Buffered,
            typename T_Platform = typename core::PlatformInfo<>::platform_type>
  class InputManager
  {
  public:
    typedef T_Policy                      policy_type;
    typedef T_Platform                    platform_type;
    typedef InputManager<policy_type, platform_type>   this_type;

    typedef u32                           input_type;
    typedef tl_size                       size_type;

  public:
    template <typename T_ParamList>
    InputManager(T_ParamList a_paramList);

    ///-------------------------------------------------------------------------
    /// Destroys all HIDs that were created by this manager
    ///-------------------------------------------------------------------------
    ~InputManager();

    ///-------------------------------------------------------------------------
    /// Creates the correct input type. An unsupported or mismatched input type
    /// will result in assertion failure.
    ///
    /// @return The new input type
    ///-------------------------------------------------------------------------
    template <typename T_InputObject>
    T_InputObject*  CreateHID(input_type a_inputType,
      parameter_options::Type a_params = parameter_options::TL_DEFAULT);

    ///-------------------------------------------------------------------------
    /// Updates the given a_inputType. Pass only one type.
    ///
    /// @param  a_inputType Type of HID.
    ///-------------------------------------------------------------------------
    void Update(input_type a_inputType);

    ///-------------------------------------------------------------------------
    /// Updates all HIDs
    ///-------------------------------------------------------------------------
    void Update();

    ///-------------------------------------------------------------------------
    /// Returns an HID with the given type at the given index
    ///
    /// @param  a_inputType Type of the input.
    /// @param  a_index     Zero-based index of a.
    ///
    /// @return The HID of type a_inputType at the specified index
    ///-------------------------------------------------------------------------
    template <typename T_InputObject>
    T_InputObject* GetHID(input_type a_inputType, size_type a_index = 0);

    ///-------------------------------------------------------------------------
    /// Get the number of a given HID type.
    ///
    /// @param  a_inputType Type of the input.
    ///
    /// @return The total number of input types created.
    ///-------------------------------------------------------------------------
    size_type GetTotalHID(input_type a_inputType);

  private:

    typedef priv::InputManagerImpl<this_type> impl_type;
    impl_type*  m_impl;
  };

  typedef InputManager<InputPolicy::Buffered>     InputManagerB;
  typedef InputManager<InputPolicy::Immediate>    InputManagerI;

  typedef core::smart_ptr::SharedPtr<InputManagerB> input_mgr_b_ptr;
  typedef core::smart_ptr::SharedPtr<InputManagerI> input_mgr_i_ptr;

};};

#endif