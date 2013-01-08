#include "tlocTestCommon.h"

#if defined(TLOC_OS_WIN)
# include<Windows.h>
#elif defined(TLOC_OS_IPHONE)
# include<unistd.h>
#endif

#include<time.h>

#include <tlocCore/time/tlocTime.h>
#include <tlocCore/time/tlocTime.inl>

namespace TestingTime
{
  using namespace tloc;
  using namespace core;
  using namespace core::time;

  struct TimeFixture
  {
    // Timer<f64, u64, true>
    Timer_T<> timerOne, timerTwo, timerThree;

    typedef Timer_T<f64, u64, p_timer_t::Adjust>    accurate_adjust_timer;
    typedef Timer_T<f64, u64, p_timer_t::NoAdjust>  accurate_no_adjust_timer;

    typedef Timer_T<f32, u32, p_timer_t::Adjust>    no_accurate_adjust_timer;
    typedef Timer_T<f32, u32, p_timer_t::NoAdjust>  no_accurate_no_adjust_timer;
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
    return (T_UInt)(GetCurrentTimeS<T_Real, T_UInt>() * (T_Real)1000.0);
  }

  template <typename T_Real, typename T_UInt>
  T_UInt GetCurrentTimeMicroS()
  {
    return (T_UInt)(GetCurrentTimeS<T_Real, T_UInt>() * (T_Real)1000000.0);
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

  template <typename T_UInt>
  void TimeTestSleepCTimeS(T_UInt durationS)
  {
    T_UInt startTime = (T_UInt)::time(NULL);
    T_UInt currentTime = startTime;

    while (currentTime - startTime < durationS)
    {
      currentTime = (T_UInt)::time(NULL);
    }
  }

  template <typename T_TimerType>
  void TestTimerAgainstSelf()
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
    TimeTestSleepMS<real_type, UInt_type>(2);
    UInt_type timeTwoMS = timerTwo.ElapsedMilliSeconds();

    REQUIRE(timeOneMS < timeTwoMS);
    CHECK((timeTwoMS - timeOneMS) >= (UInt_type)1);

    timerTwo.Reset();

    timeOneMS = timerOne.ElapsedMilliSeconds();
    timeTwoMS = timerTwo.ElapsedMilliSeconds();

    CHECK(timeOneMS > timeTwoMS);

    //------------------------------------------------------------------------
    // Testing Microseconds
    timerOne.Reset();
    timerTwo.Reset();

    UInt_type timeOneMicroS = timerOne.ElapsedMicroSeconds();
    TimeTestSleepMicroS<real_type, UInt_type>(2);
    UInt_type timeTwoMicroS = timerTwo.ElapsedMicroSeconds();

    REQUIRE(timeOneMicroS < timeTwoMicroS);
    CHECK((timeTwoMicroS - timeOneMicroS) >= (UInt_type)1);

    timerTwo.Reset();

    timeOneMicroS = timerOne.ElapsedMicroSeconds();
    timeTwoMicroS = timerTwo.ElapsedMicroSeconds();

    CHECK(timeOneMicroS > timeTwoMicroS);
  }

  TEST_CASE_METHOD(TimeFixture, "Core/Containers/Time/TimerAgainstSelf", "")
  {
    TestTimerAgainstSelf<accurate_adjust_timer>();
    TestTimerAgainstSelf<accurate_no_adjust_timer>();
    TestTimerAgainstSelf<no_accurate_adjust_timer>();
    TestTimerAgainstSelf<no_accurate_no_adjust_timer>();
  }

  template <typename T_TimerType>
  void TestTimerAgainstCTime()
  {
    typedef typename T_TimerType::sec_type    real_type;

    T_TimerType timer;
    timer.Reset();

    real_type timeOne = timer.ElapsedSeconds();
    TimeTestSleepCTimeS(2);
    real_type timeTwo = timer.ElapsedSeconds();

    REQUIRE(timeTwo > timeOne);
    CHECK((timeTwo - timeOne) >= (real_type)1.0);
    CHECK((timeTwo - timeOne) <  (real_type)3.0);
  }

  // NOTE: Test NOT run normally, use asterisk in command line to run this test
  TEST_CASE_METHOD(TimeFixture, "./Core/Containers/Time/TimerAgainstCTime", "")
  {
    TestTimerAgainstCTime<accurate_adjust_timer>();
    TestTimerAgainstCTime<accurate_no_adjust_timer>();
    TestTimerAgainstSelf<no_accurate_adjust_timer>();
    TestTimerAgainstSelf<no_accurate_no_adjust_timer>();
  }
};