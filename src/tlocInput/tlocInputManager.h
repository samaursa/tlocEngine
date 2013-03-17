#ifndef TLOC_INPUT_H
#define TLOC_INPUT_H

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.h>

#include "tlocInputImpl.h"
#include "tlocInputTypes.h"

namespace tloc { namespace input {

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
    typedef T_Policy                                   policy_type;
    typedef T_Platform                                 platform_type;
    typedef InputManager<policy_type, platform_type>   this_type;

    typedef u32                                        input_type;
    typedef tl_size                                    size_type;

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
    T_InputObject*  CreateHID
      (parameter_options::Type a_params = parameter_options::TL_DEFAULT)
    {
      p_hid::IsInputTypeSupported<T_InputObject>();

      // Static assert: You are likely mixing immediate and buffered policies
      type_traits::AssertTypeIsSupported
        <typename T_InputObject::policy_type,
         policy_type>();

      return DoCreateHID<T_InputObject>(a_params);
    }

    ///-------------------------------------------------------------------------
    /// Updates the given a_inputType.
    ///
    /// @param  a_inputType Type of HID.
    ///-------------------------------------------------------------------------
    template <typename T_InputObject>
    void Update()
    {
      p_hid::IsInputTypeSupported<T_InputObject>();
      DoUpdate(T_InputObject::m_index);
    }

    ///-------------------------------------------------------------------------
    /// Updates all HIDs
    ///-------------------------------------------------------------------------
    void Update();

    template <typename T_InputObject>
    void Reset()
    {
      p_hid::IsInputTypeSupported<T_InputObject>();
    }

    void Reset();

    ///-------------------------------------------------------------------------
    /// Returns an HID with the given type at the given index
    ///
    /// @param  a_inputType Type of the input.
    /// @param  a_index     Zero-based index of a.
    ///
    /// @return The HID of type a_inputType at the specified index
    ///-------------------------------------------------------------------------
    template <typename T_InputObject>
    T_InputObject* GetHID(size_type a_index = 0)
    {
      p_hid::IsInputTypeSupported<T_InputObject>();
      return DoGetHID<T_InputObject>(a_index);
    }

    ///-------------------------------------------------------------------------
    /// Get the number of a given HID type.
    ///
    /// @param  a_inputType Type of the input.
    ///
    /// @return The total number of input types created.
    ///-------------------------------------------------------------------------
    template <typename T_InputObject>
    size_type GetTotalHID()
    {
      p_hid::IsInputTypeSupported<T_InputObject>();
      return DoGetTotalHID(T_InputObject::m_index);
    }

  private:
    void      DoUpdate(input_type a_inputType);
    void      DoReset(input_type a_inputType);
    size_type DoGetTotalHID(input_type a_inputType);

    template <typename T_InputObject>
    T_InputObject*  DoCreateHID(parameter_options::Type a_params);

    template <typename T_InputObject>
    T_InputObject* DoGetHID(size_type a_index);

  private:
    typedef priv::InputManagerImpl<this_type>       impl_type;
    typedef core::smart_ptr::UniquePtr<impl_type>   impl_ptr_type;

    impl_ptr_type  m_impl;
  };

  typedef InputManager<InputPolicy::Buffered>     InputManagerB;
  typedef InputManager<InputPolicy::Immediate>    InputManagerI;

  typedef core::smart_ptr::SharedPtr<InputManagerB> input_mgr_b_ptr;
  typedef core::smart_ptr::SharedPtr<InputManagerI> input_mgr_i_ptr;

};};

#endif