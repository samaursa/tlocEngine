#ifndef TLOC_ERROR_H
#define TLOC_ERROR_H

#include <tlocCore/error/tlocErrorTypes.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace core { namespace error {

  class Error
  {
  public:
    typedef Error                 this_type;
    typedef error_code_type       code_type;

    Error(code_type a_errorType);

    bool Succeeded() const;
    bool Failed() const;

    bool operator==(const this_type& a_other);
    bool operator==(const code_type& a_other);

    TLOC_DECL_AND_DEF_GETTER_CONST(code_type, GetErrorCode, m_error);

  private:
    code_type m_error;
  };

  class ErrorSuccess : public Error
  {
  public:
    ErrorSuccess() : Error(common_error_types::error_success) {}
  };

  class ErrorFailure : public Error
  {
  public:
    ErrorFailure() : Error(common_error_types::error_failure) {}
  };

};};};

#endif