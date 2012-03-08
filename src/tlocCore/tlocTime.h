#ifndef TLOC_TIME_H
#define TLOC_TIME_H

#include "tlocBase.h"
#include "tlocTypes.h"
#include "tlocPlatform.h"

namespace tloc { namespace core {

  template <typename T_Real = f64, typename T_UInt = u64, bool T_Adjust = true>
  class Timer
  {
  public:
    typedef T_Real    sec_type;
    typedef T_UInt    value_type;

    Timer();
    ~Timer();

    ///-------------------------------------------------------------------------
    /// Calibrates the timer if T_Adjust = true.
    ///
    /// @param  aCalibrate (optional) default is true.
    ///
    /// ### remarks
    /// Use this function to re-calibrate a timer. This function is
    /// automatically called when the timer is first created.
    ///-------------------------------------------------------------------------
    TL_I void       Calibrate(bool aCalibrate = T_Adjust);
    TL_I void       Reset();
    TL_I sec_type   ElapsedSeconds();
    TL_I value_type ElapsedMilliSeconds();
    TL_I value_type ElapsedMicroSeconds();

  private:

    TL_I void       DoReset(Platform_win);
    TL_I void       DoReset(Platform_osx);
    TL_I void       DoReset(Platform_osx_iphone);
    TL_I void       DoReset(Platform_ps3);
    TL_I void       DoReset(Platform_linux);

    TL_I sec_type   DoGetElapsedSeconds(Platform_win);
    TL_I sec_type   DoGetElapsedSeconds(Platform_osx);
    TL_I sec_type   DoGetElapsedSeconds(Platform_osx_iphone);
    TL_I sec_type   DoGetElapsedSeconds(Platform_ps3);
    TL_I sec_type   DoGetElapsedSeconds(Platform_linux);

    TL_I value_type DoGetElapsedMilliSeconds(Platform_win);
    TL_I value_type DoGetElapsedMilliSeconds(Platform_osx);
    TL_I value_type DoGetElapsedMilliSeconds(Platform_osx_iphone);
    TL_I value_type DoGetElapsedMilliSeconds(Platform_ps3);
    TL_I value_type DoGetElapsedMilliSeconds(Platform_linux);

    TL_I value_type DoGetElapsedMicroSeconds(Platform_win);
    TL_I value_type DoGetElapsedMicroSeconds(Platform_osx);
    TL_I value_type DoGetElapsedMicroSeconds(Platform_osx_iphone);
    TL_I value_type DoGetElapsedMicroSeconds(Platform_ps3);
    TL_I value_type DoGetElapsedMicroSeconds(Platform_linux);

    value_type                              m_start;
    ConditionalType<sec_type, T_Adjust>     m_adjustInSeconds;

  };

};};

#endif