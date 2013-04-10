#ifndef _TLOC_CORE_ERROR_H_
#define _TLOC_CORE_ERROR_H_

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/error/tlocErrorTypes.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocCore/configs/tlocBuildConfig.h>

namespace tloc { namespace core { namespace error {

  //////////////////////////////////////////////////////////////////////////
  // Error_I

  template <typename T_Derived>
  class Error_TI
  {
  public:
    typedef Error_TI               this_type;
    typedef T_Derived             derived_type;
    typedef error_code_type       code_type;

    Error_TI(code_type a_errorType);

    bool Succeeded() const;
    bool Failed() const;
    void Ignore() const;

    void operator=(const code_type& a_code);

    bool operator==(const this_type& a_other) const;
    bool operator==(const code_type& a_other) const;

    bool operator!=(const this_type& a_other) const;
    bool operator!=(const code_type& a_other) const;

    TLOC_DECL_AND_DEF_GETTER(code_type, GetErrorCode, m_error);

  private:
    code_type m_error;
  };

  //////////////////////////////////////////////////////////////////////////
  // Error_T<T_BuildConfig>

  template <typename T_BuildConfig>
  class Error_T
    : public Error_TI<Error_T<T_BuildConfig> >
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_BuildConfig,
                        configs::p_build_config::Debug>::value ||
      Loki::IsSameType<T_BuildConfig,
                       configs::p_build_config::Release>::value ||
      Loki::IsSameType<T_BuildConfig,
                       configs::p_build_config::Release_DebugInfo>::value
       ), Unsupported_template_argument);

  public:
    template <typename T_Derived> friend class Error_TI;

  public:
    typedef Error_T<T_BuildConfig>        this_type;
    typedef Error_TI<this_type>           base_type;
    typedef typename base_type::code_type code_type;

  public:
    Error_T(code_type a_errorType);
    Error_T(const this_type& a_other);
    ~Error_T();

    using base_type::Succeeded;
    using base_type::Failed;

    void operator=(const code_type& a_code);

    using base_type::operator ==;
    using base_type::operator !=;

    using base_type::GetErrorCode;

  private:
    void DoSucceeded() const;
    void DoFailed() const;
    void DoEqual() const;
    void DoNotEqual() const;
    void DoIgnore() const;

  private:
    mutable bool m_errorCheckedByUser;

  };

  //////////////////////////////////////////////////////////////////////////
  // Error_T<>

  template <>
  class Error_T<configs::p_build_config::Release>
    : public Error_TI<Error_T<configs::p_build_config::Release> >
  {
  public:
    template <typename T_Derived> friend class Error_TI;

  public:
    typedef configs::p_build_config::Release  build_config;
    typedef Error_T<build_config>             this_type;
    typedef Error_TI<this_type>                base_type;
    typedef base_type::code_type              code_type;

  public:
    Error_T(code_type a_errorType);
    Error_T(const this_type& a_other);
    ~Error_T();

    using base_type::Succeeded;
    using base_type::Failed;

    using base_type::operator =;
    using base_type::operator ==;
    using base_type::operator !=;

    using base_type::GetErrorCode;

  private:
    void DoSucceeded() const;
    void DoFailed() const;
    void DoEqual() const;
    void DoNotEqual() const;
    void DoIgnore() const;
  };

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef Error_T<configs::BuildConfig<>::build_config_type> Error;


};};};

///////////////////////////////////////////////////////////////////////////
// Macros for the basic error types

#define ErrorSuccess \
  tloc::core::error::Error(tloc::common_error_types::error_success)
#define ErrorFailure \
  tloc::core::error::Error(tloc::common_error_types::error_failure)

#endif