#include <tlocCore/types/tlocTypes.inl>
#include <tlocCore/platform/tlocPlatform.h>

#ifndef TLOC_TIME_H
#error "Must include header before including the inline file"
#endif
#include <tlocCore/time/tlocTime.h>

#if defined(TLOC_OS_WIN)
# include <Windows.h>
#elif defined(TLOC_OS_IPHONE)
# import <mach/mach_time.h>
#endif

namespace tloc { namespace core {

  //////////////////////////////////////////////////////////////////////////
  // Macros

#define TIMER_TYPES typename T_Real, typename T_UInt, bool T_Adjust
#define TIMER_PARAMS T_Real, T_UInt, T_Adjust
  
  //////////////////////////////////////////////////////////////////////////
  // Constants
  
#if defined (TLOC_OS_IPHONE)
  template<TIMER_TYPES>
  typename Timer<TIMER_PARAMS>::sec_type Timer<TIMER_PARAMS>
    ::sm_ticksToSeconds = (typename Timer<TIMER_PARAMS>::sec_type)0;
#endif

  //////////////////////////////////////////////////////////////////////////
  // Timer

  //------------------------------------------------------------------------
  // Main Functions

  template <TIMER_TYPES>
  Timer<TIMER_PARAMS>::Timer()
  {
    DoInit();
    Calibrate();
  }

  template <TIMER_TYPES>
  Timer<TIMER_PARAMS>::~Timer()
  {
  }

  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::Calibrate(bool aCalibrate)
  {
    if (aCalibrate)
    {
      m_adjustInSeconds = 0;
      Reset();
      m_adjustInSeconds = ElapsedSeconds();
    }

    Reset();
  }

  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::Reset()
  {
    DoReset();
  }

  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::sec_type 
    Timer<TIMER_PARAMS>::ElapsedSeconds()
  {
    return DoGetElapsedSeconds();
  }

  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::value_type 
    Timer<TIMER_PARAMS>::ElapsedMilliSeconds()
  {
    return DoGetElapsedMilliSeconds();
  }

  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::value_type 
    Timer<TIMER_PARAMS>::ElapsedMicroSeconds()
  {
    return DoGetElapsedMicroSeconds();
  }

  //------------------------------------------------------------------------
  // Helper functions

  //------------------------------------------------------------------------
  // WINDOWS OS
#if defined (TLOC_OS_WIN)
  
  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::DoInit()
  {
  }

  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::DoReset()
  {
    QueryPerformanceCounter( (LARGE_INTEGER*) &m_start);
  }

  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::sec_type 
    Timer<TIMER_PARAMS>::DoGetElapsedSeconds()
  {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    LARGE_INTEGER end;
    QueryPerformanceCounter( &end);

    value_type delta = (value_type)end.QuadPart - m_start;

    return (delta / (sec_type)freq.QuadPart) + m_adjustInSeconds;
  }
  
  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::value_type 
    Timer<TIMER_PARAMS>::DoGetElapsedMilliSeconds()
  {
    return (value_type)(ElapsedSeconds() * (sec_type)1000.0);
  }
  
  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::value_type 
    Timer<TIMER_PARAMS>::DoGetElapsedMicroSeconds()
  {
    return (value_type)(ElapsedSeconds() * (sec_type)1000000.0);
  }

  //------------------------------------------------------------------------
  // MAC OS
#elif defined (TLOC_OS_MAC) 
  
  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::DoInit()
  {
  }
  
  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::DoReset()
  {
    TLOC_ASSERT_WIP();
  }

  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::sec_type 
    Timer<TIMER_PARAMS>::DoGetElapsedSeconds()
  {
    TLOC_ASSERT_WIP();
    return 0;
  }
  
  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::value_type 
    Timer<TIMER_PARAMS>::DoGetElapsedMilliSeconds()
  {
    TLOC_ASSERT_WIP();
    return 0;
  }
  
  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::value_type 
    Timer<TIMER_PARAMS>::DoGetElapsedMicroSeconds()
  {
    TLOC_ASSERT_WIP();
    return 0;
  }
  
  //------------------------------------------------------------------------
  // IPHONE OS
#elif defined (TLOC_OS_IPHONE) 
  
  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::DoInit()
  {
    if (sm_ticksToSeconds == (sec_type)0)
    {
      mach_timebase_info_data_t timebase;
      mach_timebase_info(&timebase);
      sm_ticksToSeconds = 
        (sec_type)timebase.numer / timebase.denom * (sec_type)0.000000001;
    }
  }

  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::DoReset()
  {
    m_start = (value_type)mach_absolute_time();
  }

  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::sec_type 
    Timer<TIMER_PARAMS>::DoGetElapsedSeconds()
  {
    value_type end = (value_type)mach_absolute_time();
    value_type delta = end - m_start;
    
    return (delta * sm_ticksToSeconds) + m_adjustInSeconds;
  }
  
  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::value_type 
    Timer<TIMER_PARAMS>::DoGetElapsedMilliSeconds()
  {
    return (value_type)(ElapsedSeconds() * (sec_type)1000.0);
  }
  
  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::value_type 
    Timer<TIMER_PARAMS>::DoGetElapsedMicroSeconds()
  {
    return (value_type)(ElapsedSeconds() * (sec_type)1000000.0);
  }
  
  //------------------------------------------------------------------------
  // LINUX OS
#elif defined (TLOC_OS_LINUX)
  
  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::DoInit()
  {
  }

  template <TIMER_TYPES>
  TL_I void Timer<TIMER_PARAMS>::DoReset()
  {
    TLOC_ASSERT_WIP();
  }

  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::sec_type 
    Timer<TIMER_PARAMS>::DoGetElapsedSeconds()
  {
    TLOC_ASSERT_WIP();
    return 0;
  }
  
  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::value_type 
    Timer<TIMER_PARAMS>::DoGetElapsedMilliSeconds()
  {
    TLOC_ASSERT_WIP();
    return 0;
  }
  
  template <TIMER_TYPES>
  TL_I typename Timer<TIMER_PARAMS>::value_type 
    Timer<TIMER_PARAMS>::DoGetElapsedMicroSeconds()
  {
    TLOC_ASSERT_WIP();
    return 0;
  }
  
#endif 

};};
