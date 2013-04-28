#include "tlocError.h"

namespace tloc { namespace core { namespace error {

  //////////////////////////////////////////////////////////////////////////
  // Error_I

#define ERROR_TI_TEMP    typename T_Derived
#define ERROR_TI_PARAMS  T_Derived
#define ERROR_TI_TYPE    typename Error_TI<ERROR_TI_PARAMS>

  template <ERROR_TI_TEMP>
  Error_TI<ERROR_TI_PARAMS>::
    Error_TI(const this_type& a_other)
    : m_error(a_other.m_error)
  {
    a_other.Ignore();
  }

  template <ERROR_TI_TEMP>
  Error_TI<ERROR_TI_PARAMS>::
    Error_TI(code_type a_errorType)
    : m_error(a_errorType)
  { }

  template <ERROR_TI_TEMP>
  bool Error_TI<ERROR_TI_PARAMS>::
    Succeeded() const
  {
    static_cast<const derived_type*>(this)->DoSucceeded();
    return m_error == common_error_types::error_success;
  }

  template <ERROR_TI_TEMP>
  bool Error_TI<ERROR_TI_PARAMS>::
    Failed() const
  {
    static_cast<const derived_type*>(this)->DoFailed();
    return !Succeeded();
  }

  template <ERROR_TI_TEMP>
  void Error_TI<ERROR_TI_PARAMS>::
    Ignore() const
  {
    static_cast<const derived_type*>(this)->DoIgnore();
  }

  template <ERROR_TI_TEMP>
  void Error_TI<ERROR_TI_PARAMS>::
    operator =(const code_type& a_other)
  {
    m_error = a_other;
  }

  template <ERROR_TI_TEMP>
  bool Error_TI<ERROR_TI_PARAMS>::
    operator ==(const this_type& a_other) const
  {
    static_cast<const derived_type*>(this)->DoEqual();
    static_cast<const derived_type*>(&a_other)->DoEqual();
    return operator==(a_other.m_error);
  }

  template <ERROR_TI_TEMP>
  bool Error_TI<ERROR_TI_PARAMS>::
    operator ==(const code_type& a_other) const
  {
    static_cast<const derived_type*>(this)->DoEqual();
    return m_error == a_other;
  }

  template <ERROR_TI_TEMP>
  bool Error_TI<ERROR_TI_PARAMS>::
    operator !=(const this_type& a_other) const
  {
    static_cast<const derived_type*>(this)->DoNotEqual();
    static_cast<const derived_type*>(&a_other)->DoNotEqual();
    return operator!=(a_other.m_error);
  }

  template <ERROR_TI_TEMP>
  bool Error_TI<ERROR_TI_PARAMS>::
    operator !=(const code_type& a_other) const
  {
    static_cast<const derived_type*>(this)->DoNotEqual();
    return m_error != a_other;
  }

  //////////////////////////////////////////////////////////////////////////
  // Error_T<T_BuildConfig>

#define ERROR_T_TEMP    typename T_BuildConfig
#define ERROR_T_PARAMS  T_BuildConfig
#define ERROR_T_TYPE    typename Error_T<ERROR_TI_PARAMS>

  template <ERROR_T_TEMP>
  Error_T<ERROR_T_PARAMS>::
    Error_T(code_type a_errorType)
    : base_type(a_errorType)
    , m_errorCheckedByUser(false)
  { }

  template <ERROR_T_TEMP>
  Error_T<ERROR_T_PARAMS>::
    Error_T(const this_type& a_other)
    : base_type(a_other.GetErrorCode())
    , m_errorCheckedByUser(false)
  {
    a_other.Ignore();
  }

  template <ERROR_T_TEMP>
  Error_T<ERROR_T_PARAMS>::
    ~Error_T()
  {
    if (GetErrorCode() == common_error_types::error_success)
    { m_errorCheckedByUser = true; }

    TLOC_ASSERT(m_errorCheckedByUser, "Ignored an error!");
  }

  template <ERROR_T_TEMP>
  void Error_T<ERROR_T_PARAMS>::
    operator =(const this_type& a_other)
  {
    base_type::operator=(a_other.GetErrorCode() );
    a_other.Ignore();
  }

  template <ERROR_T_TEMP>
  void Error_T<ERROR_T_PARAMS>::
    operator =(const code_type& a_code)
  {
    base_type::operator=(a_code);
    m_errorCheckedByUser = false;
  }

  template <ERROR_T_TEMP>
  void Error_T<ERROR_T_PARAMS>::
    DoSucceeded() const
  { m_errorCheckedByUser = true; }

  template <ERROR_T_TEMP>
  void Error_T<ERROR_T_PARAMS>::
    DoFailed() const
  { m_errorCheckedByUser = true; }

  template <ERROR_T_TEMP>
  void Error_T<ERROR_T_PARAMS>::
    DoEqual() const
  { m_errorCheckedByUser = true; }

  template <ERROR_T_TEMP>
  void Error_T<ERROR_T_PARAMS>::
    DoNotEqual() const
  { m_errorCheckedByUser = true; }

  template <ERROR_T_TEMP>
  void Error_T<ERROR_T_PARAMS>::
    DoIgnore() const
  { m_errorCheckedByUser = true; }

  //////////////////////////////////////////////////////////////////////////
  // Error_T<>

#define ERROR_T_RELEASE_TEMP
#define ERROR_T_RELEASE_PARAMS core_cfg::p_build_config::Release

  Error_T<ERROR_T_RELEASE_PARAMS>::
    Error_T(code_type a_errorType)
    : base_type(a_errorType)
  { }

  Error_T<ERROR_T_RELEASE_PARAMS>::
    Error_T(const this_type& a_other)
    : base_type(a_other.GetErrorCode())
  { }

  Error_T<ERROR_T_RELEASE_PARAMS>::
    ~Error_T()
  { }

  void Error_T<ERROR_T_RELEASE_PARAMS>::
    DoSucceeded() const
  { }

  void Error_T<ERROR_T_RELEASE_PARAMS>::
    DoFailed() const
  { }

  void Error_T<ERROR_T_RELEASE_PARAMS>::
    DoEqual() const
  { }

  void Error_T<ERROR_T_RELEASE_PARAMS>::
    DoNotEqual() const
  { }

  void Error_T<ERROR_T_RELEASE_PARAMS>::
    DoIgnore() const
  { }

  //////////////////////////////////////////////////////////////////////////
  // Explicit specializations

  template class Error_TI<Error_T<configs::p_build_config::Debug> >;
  template class Error_TI<Error_T<configs::p_build_config::Release> >;
  template class Error_TI<Error_T<configs::p_build_config::Release_DebugInfo> >;

  template class Error_T<configs::p_build_config::Debug>;
  template class Error_T<configs::p_build_config::Release_DebugInfo>;

};};};