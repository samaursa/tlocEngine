set(TLOC_INPUT 
  tlocDepVersionCheck.cpp 
  tlocInputBase.h 
  tlocInputImpl.h 
  tlocInputManager.cpp 
  tlocInputManager.h 
  tlocInputTypes.h 
  tloc_input.cpp 
  tloc_input.h 
  tloc_input.inl.h
  )

set(TLOC_INPUT_HID 
  hid/tlocJoystick.cpp 
  hid/tlocJoystick.h 
  hid/tlocJoystickImpl.h 
  hid/tlocKeyboard.cpp 
  hid/tlocKeyboard.h 
  hid/tlocKeyboardImpl.h 
  hid/tlocMouse.cpp 
  hid/tlocMouse.h 
  hid/tlocMouseImpl.h 
  hid/tlocTouchSurface.cpp 
  hid/tlocTouchSurface.h 
  hid/tlocTouchSurfaceDevice.cpp 
  hid/tlocTouchSurfaceDevice.h 
  hid/tlocTouchSurfaceImpl.h 
  hid/tloc_hid.cpp 
  hid/tloc_hid.h 
  hid/tloc_hid.inl.h
  )

#-------------------------------------------
# Platform specific files

# IOS
if(APPLE)
  set(TLOC_INPUT
    ${TLOC_INPUT}
    tlocInputImplIphone.h 
    tlocInputImplIphone.mm 
    )

  set(TLOC_INPUT_HID
    ${TLOC_INPUT_HID}
    hid/tlocJoystickImplIphone.h 
    hid/tlocJoystickImplIphone.mm
    hid/tlocTouchSurfaceImplIphone.h 
    hid/tlocTouchSurfaceImplIphone.mm 
    hid/tlocMouseImplIphone.h 
    hid/tlocKeyboardImplIphone.h 
    hid/tlocKeyboardImplIphone.mm 
    )
endif()

# Windows
if(WIN32)
  set(TLOC_INPUT
    ${TLOC_INPUT}
    tlocInputImplWin.cpp 
    tlocInputImplWin.h 
    )

  set(TLOC_INPUT_HID
    ${TLOC_INPUT_HID}
    hid/tlocTouchSurfaceImplWin.h 
    hid/tlocMouseImplWin.cpp 
    hid/tlocMouseImplWin.h 
    hid/tlocKeyboardImplWin.cpp 
    hid/tlocKeyboardImplWin.h 
    hid/tlocJoystickImplWin.cpp 
    hid/tlocJoystickImplWin.h 
    )
endif()

#-------------------------------------------
# Project setup

add_library(tlocInput STATIC
  ${TLOC_INPUT}
  ${TLOC_INPUT_HID}
  )

add_dependencies(tlocInput
  tlocCore
  tlocGraphics
  tlocMath
  )

# Filters to organize the source files
source_group(hid FILES ${TLOC_INPUT_HID})
