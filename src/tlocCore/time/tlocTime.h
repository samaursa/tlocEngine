#ifndef TLOC_TIME_H
#define TLOC_TIME_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/platform/tlocPlatform.h>

namespace tloc { namespace core { namespace time {

  namespace p_timer_t
  {
    // Timer_T adjusts the final time by the amount of time it takes to call
    // Reset() - this (theoretically) increases accuracy
    struct Adjust   {};
    struct NoAdjust {};
  };

  template <typename T_Real = f64, typename T_UInt = u64,
            typename T_Adjust = p_timer_t::Adjust>
  class Timer_T
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T_Real);
    TLOC_STATIC_ASSERT_IS_INTEGRAL(T_UInt);
  public:
    typedef T_Real                    sec_type;
    typedef T_UInt                    value_type;
    typedef T_Adjust                  adjust_policy;

  public:
    Timer_T();
    ~Timer_T();

    ///-------------------------------------------------------------------------
    /// Calibrates the timer if T_Adjust = p_timer_t::Adjust
    ///
    /// @remarks
    /// Use this function to re-calibrate a timer. This function is
    /// automatically called when the timer is first created.
    ///-------------------------------------------------------------------------
    void              Calibrate();
    void              Reset();
    sec_type          ElapsedSeconds() const;
    value_type        ElapsedMilliSeconds() const;
    value_type        ElapsedMicroSeconds() const;

  private:
    typedef Loki::IsSameType<adjust_policy,
                             p_timer_t::Adjust>  is_adjust_selected;

  private:
    void              DoAdjust(p_timer_t::Adjust);
    void              DoAdjust(p_timer_t::NoAdjust);

    void              DoInit();
    void              DoReset();
    sec_type          DoGetElapsedSeconds() const;
    value_type        DoGetElapsedMilliSeconds() const;
    value_type        DoGetElapsedMicroSeconds() const;

#ifdef TLOC_OS_IPHONE
    static sec_type   DoGetTicksToSeconds() ;
#endif

  private:
    value_type                                  m_start;
    ConditionalType<sec_type,
                    is_adjust_selected::value>  m_adjustInSeconds;

#ifdef TLOC_OS_IPHONE
    static const sec_type                       sm_ticksToSeconds;
#endif

  };

  //------------------------------------------------------------------------
  // Typedefs

  typedef Timer_T<>                   Timer;
  typedef Timer_T<tl_float, tl_uint>  Timerf;
  typedef Timer_T<f32, u32>           Timer32;
  typedef Timer_T<f64, u64>           Timer64;

  // -----------------------------------------------------------------------
  // global functions

  const Timer&  GetProgramTime();

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Timer_T<>);
  TLOC_EXTERN_TEMPLATE_CLASS(Timer_T<f128>);
  TLOC_EXTERN_TEMPLATE_CLASS(Timer_T<f64 TLOC_COMMA u64 TLOC_COMMA p_timer_t::NoAdjust>);
  TLOC_EXTERN_TEMPLATE_CLASS(Timer_T<f128 TLOC_COMMA u64 TLOC_COMMA p_timer_t::NoAdjust>);

  TLOC_EXTERN_TEMPLATE_CLASS(Timer_T<f32 TLOC_COMMA u32 TLOC_COMMA p_timer_t::Adjust>);
  TLOC_EXTERN_TEMPLATE_CLASS(Timer_T<f32 TLOC_COMMA u32 TLOC_COMMA p_timer_t::NoAdjust>);

};};};

#endif