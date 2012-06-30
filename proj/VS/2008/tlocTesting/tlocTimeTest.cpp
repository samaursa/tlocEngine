#include "tlocTestCommon.h"

#if defined(TLOC_OS_WIN)
# include<Windows.h>
#elif defined(TLOC_OS_IPHONE)
# include<unistd.h>
#endif

#include <tlocCore/time/tlocTime.h>
#include <tlocCore/time/tlocTime.inl>

namespace TestingTime
{
  USING_TLOC;
  using namespace core;

  struct TimeFixture
  {
    // Timer<f64, u64, true>
    Timer<> timerOne, timerTwo, timerThree;
    
    typedef Timer<f64, u64, true>   accurate_adjust_timer;
    typedef Timer<f64, u64, false>  accurate_no_adjust_timer;
    
    typedef Timer<f32, u32, true>   no_accurate_adjust_timer;
    typedef Timer<f32, u32, false>  no_accurate_no_adjust_timer;
  };

#if defined(TLOC_OS_WIN)
  template <typename T_Real, typename T_UInt>
  T_Real GetCurrentTimeS()
  {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);

    return (T_UInt)currentTime.QuadPart / (T_Real)frequency.QuadPart;
  }

  template <typename T_Real, typename T_UInt>
  T_UInt GetCurrentTimeMS()
  {
    return (u64)(GetCurrentTimeS() * (T_Real)1000.0);
  }

  template <typename T_Real, typename T_UInt>
  T_UInt GetCurrentTimeMicroS()
  {
    return (u64)(GetCurrentTimeS() * (T_Real)1000000.0);
  }

#elif defined (TLOC_OS_IPHONE)
  template <typename T_Real, typename T_UInt>
  T_Real GetCurrentTimeS()
  {
    static T_Real ticksToSeconds = 0;
    if (ticksToSeconds == (T_Real)0.0)
    {
      mach_timebase_info_data_t timebase;
      mach_timebase_info(&timebase);
      ticksToSeconds = 
        (T_Real)timebase.numer / timebase.denom * (T_Real)0.000000001;
    }
    
    return mach_absolute_time() * ticksToSeconds;
  }

  template <typename T_Real, typename T_UInt>
  T_UInt GetCurrentTimeMS()
  {
    return (T_UInt)(GetCurrentTimeS<T_Real, T_UInt>() * (T_Real)1000.0);
  }
  
  template <typename T_Real, typename T_UInt>
  T_UInt GetCurrentTimeMicroS()
  {
    return (T_UInt)(GetCurrentTimeS<T_Real, T_UInt>() * (T_Real)1000000.0);
  }
#endif

  template <typename T_Real, typename T_UInt>
  void TimeTestSleepS(T_Real durationS)
  {
    T_Real startTime = GetCurrentTimeS<T_Real, T_UInt>();
    T_Real currentTime = startTime;

    while(currentTime - startTime < durationS)
    {
      currentTime = GetCurrentTimeS<T_Real, T_UInt>();
    }
  }

  template <typename T_Real, typename T_UInt>
  void TimeTestSleepMS(T_UInt durationMS)
  {
    TimeTestSleepS<T_Real, T_UInt>(durationMS * (T_Real)0.001);
  }

  template <typename T_Real, typename T_UInt>
  void TimeTestSleepMicroS(T_UInt durationMicroS)
  {
    TimeTestSleepS<T_Real, T_UInt>(durationMicroS * (T_Real)0.000001);
  }
  
  
  template <typename T_TimerType>
  void TestTimer()
  {
    typedef typename T_TimerType::sec_type    real_type;
    typedef typename T_TimerType::value_type  UInt_type;
    
    T_TimerType timerOne, timerTwo;
    
    //------------------------------------------------------------------------
    // Testing seconds
    timerOne.Reset ();
    timerTwo.Reset();
    
    real_type timeOneS = timerOne.ElapsedSeconds();
    TimeTestSleepMicroS<real_type, UInt_type>(1);
    real_type timeTwoS = timerTwo.ElapsedSeconds();
    
    CHECK(timeOneS < timeTwoS);
    
    timerTwo.Reset();
    
    timeOneS = timerOne.ElapsedSeconds();
    timeTwoS = timerTwo.ElapsedSeconds();
    
    CHECK(timeOneS > timeTwoS);
    
    //------------------------------------------------------------------------
    // Testing Milliseconds
    timerOne.Reset();
    timerTwo.Reset();
    
    UInt_type timeOneMS = timerOne.ElapsedMilliSeconds();
    TimeTestSleepMS<real_type, UInt_type>(1);
    UInt_type timeTwoMS = timerTwo.ElapsedMilliSeconds();
    
    CHECK(timeOneMS < timeTwoMS);
    
    timerTwo.Reset();
    
    timeOneMS = timerOne.ElapsedMilliSeconds();
    timeTwoMS = timerTwo.ElapsedMilliSeconds();
    
    CHECK(timeOneMS > timeTwoMS);
    
    //------------------------------------------------------------------------
    // Testing Microseconds
    timerOne.Reset();
    timerTwo.Reset();
    
    UInt_type timeOneMicroS = timerOne.ElapsedMicroSeconds();
    TimeTestSleepMicroS<real_type, UInt_type>(1);
    UInt_type timeTwoMicroS = timerTwo.ElapsedMicroSeconds();
    
    CHECK(timeOneMicroS < timeTwoMicroS);
    
    timerTwo.Reset();
    
    timeOneMicroS = timerOne.ElapsedMicroSeconds();
    timeTwoMicroS = timerTwo.ElapsedMicroSeconds();
    
    CHECK(timeOneMicroS > timeTwoMicroS);
  }

  TEST_CASE_METHOD(TimeFixture, "Core/Containers/Time/Timer", "")
  {
    TestTimer<accurate_adjust_timer>();
    TestTimer<accurate_no_adjust_timer>();
    TestTimer<no_accurate_adjust_timer>();
    TestTimer<no_accurate_no_adjust_timer>();
  }
};