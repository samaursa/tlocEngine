#ifndef TLOC_INPUT_WIN_H
#define TLOC_INPUT_WIN_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocArray.h"
#include "tlocCore/tlocString.h"

#include "tlocInput.h"
#include "tlocInputImpl.h"
#include "tlocInputTypes.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <InitGuid.h> // Required to circumvent linking errors for dxguid.lib
#define DIRECTINPUT_VERSION 0x0800 // removes the default warning
#include <dinput.h>

namespace tloc { namespace input {

  typedef InputParameterList<HWND> input_param_type;

};};

namespace tloc { namespace input { namespace priv {

  struct InputDeviceInfo
  {
    GUID          m_productGuid;
    GUID          m_deviceGuid;
    core::String  m_deviceName;
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

    typedef typename parent_type::platform_type       platform_type;
    typedef typename parent_type::policy_type         policy_type;
    typedef typename parent_type::size_type           size_type;
    typedef typename parent_type::input_type          input_type;

    InputManagerImpl(parent_type* a_parent,
                     param_type a_params);

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
    T_InputObject*  CreateHID(input_type a_inputType,
                              parameter_options::Type a_params);

    ///-------------------------------------------------------------------------
    /// Updates the given a_inputType. Pass only one type.
    ///
    /// @param  a_inputType Type of HID.
    ///-------------------------------------------------------------------------
    void Update(input_type a_inputType);

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

    HWND      GetWindowHandle();

  private:

    static BOOL CALLBACK DoEnumerateCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
    void                 DoEnumerateDevices();

    IDirectInput8*                m_directInput;

    typedef core::Array<core::Array
      <core::Pair<bool, InputDeviceInfo> > >  win_HID_array;
    win_HID_array m_winHIDs;

  };

};};};

#endif