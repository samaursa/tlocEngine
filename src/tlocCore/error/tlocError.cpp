#include "tlocError.h"

namespace tloc { namespace core { namespace error {

  Error::Error(code_type a_errorType)
    : m_error(a_errorType)
  {
  }

  bool Error::Succeeded() const
  {
    return m_error == common_error_types::error_success;
  }

  bool Error::Failed() const
  {
    return !Succeeded();
  }

  bool Error::operator ==(const this_type& a_other)
  {
    return operator==(a_other.m_error);
  }

  bool Error::operator ==(const code_type& a_other)
  {
    return m_error == a_other;
  }

  bool Error::operator !=(const this_type& a_other)
  {
    return operator!=(a_other.m_error);
  }

  bool Error::operator !=(const code_type& a_other)
  {
    return m_error != a_other;
  }

};};};