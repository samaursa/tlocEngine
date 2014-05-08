#ifndef _TLOC_CORE_ERROR_H_
#define _TLOC_CORE_ERROR_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/tlocAlgorithms.h>

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
    typedef Error_TI              this_type;
    typedef T_Derived             derived_type;
    typedef error_code_type       code_type;

    bool Succeeded() const;
    bool Failed() const;

    void Ignore() const;
    void Check() const;

    tl_int      GetLineNumber() const;
    const char* GetFileName() const;

    void        swap(this_type& a_other);

    bool operator==(const this_type& a_other) const;
    bool operator==(const code_type& a_other) const;

    bool operator!=(const this_type& a_other) const;
    bool operator!=(const code_type& a_other) const;

    TLOC_DECL_AND_DEF_GETTER(code_type, GetErrorCode, m_error);

  protected:
    Error_TI(const this_type& a_errorType);
    Error_TI(code_type a_errorType);

    TLOC_DECL_AND_DEF_SETTER(code_type, DoSetErrorCode, m_error);

  private:
    void operator =(const this_type& a_other);

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
    Error_T(code_type a_errorType, tl_int a_line, const char* a_file);
    Error_T(const this_type& a_other);
    ~Error_T() TLOC_DTOR_ASSERT;

    this_type& operator=(const this_type& a_other);

    void swap(this_type& a_other);

    using base_type::operator ==;
    using base_type::operator !=;

    using base_type::Succeeded;
    using base_type::Failed;
    using base_type::Ignore;

    using base_type::GetLineNumber;
    using base_type::GetFileName;

    using base_type::GetErrorCode;

  private:
    void DoSucceeded() const;
    void DoFailed() const;
    void DoEqual() const;
    void DoNotEqual() const;
    void DoIgnore() const;

    tl_int      DoGetLineNumber() const;
    const char* DoGetFileName() const;

    using base_type::DoSetErrorCode;

  private:
    mutable bool          m_errorCheckedByUser;
    mutable tl_int        m_line;
    mutable const char*   m_file;

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
    Error_T(code_type a_errorType, tl_int a_line, const char* a_file);
    Error_T(const this_type& a_other);
    ~Error_T();

    void operator=(const this_type& a_other);

    void swap(this_type& a_other);

    using base_type::operator ==;
    using base_type::operator !=;

    using base_type::Succeeded;
    using base_type::Failed;
    using base_type::Ignore;

    using base_type::GetLineNumber;
    using base_type::GetFileName;

    using base_type::GetErrorCode;

  private:
    void DoSucceeded() const;
    void DoFailed() const;
    void DoEqual() const;
    void DoNotEqual() const;
    void DoIgnore() const;

    tl_int      DoGetLineNumber() const;
    const char* DoGetFileName() const;

    using base_type::DoSetErrorCode;
  };

  //------------------------------------------------------------------------
  // swap

  TL_I void swap(Error_TI<configs::p_build_config::Release>& a,
                 Error_TI<configs::p_build_config::Release>& b)
  { a.swap(b); }

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef Error_T<configs::BuildConfig::build_config_type> Error;


};};};

namespace tloc { namespace core {

  //------------------------------------------------------------------------
  // swap

  template <typename T_Derived>
  TL_I void swap(core_err::Error_TI<T_Derived>& a,
                 core_err::Error_TI<T_Derived>& b)
  { a.swap(b); }

  //------------------------------------------------------------------------
  // swap

  template <typename T_BuildConfig>
  TL_I void swap(core_err::Error_T<T_BuildConfig>& a,
                 core_err::Error_T<T_BuildConfig>& b)
  { a.swap(b); }

};};

///////////////////////////////////////////////////////////////////////////
// Macros for the basic error types

#define ErrorSuccess \
  tloc::core::error::Error(tloc::common_error_types::error_success, __LINE__, __FILE__)
#define ErrorFailure \
  tloc::core::error::Error(tloc::common_error_types::error_failure, __LINE__, __FILE__)

#define TLOC_ERROR(_errorCode_)\
  tloc::core::error::Error(_errorCode_, __LINE__, __FILE__)

// ///////////////////////////////////////////////////////////////////////
// Helper macro for common error reporting tasks

// if the user expression returns an error, then that error is returned
#define TLOC_ERROR_RETURN_IF_FAILED(_expr_)\
  do {\
    tloc::core_err::Error errToReturn = (_expr_);\
    if (errToReturn.Failed())\
    { return errToReturn; }\
  } while((void)0, 0)

#endif