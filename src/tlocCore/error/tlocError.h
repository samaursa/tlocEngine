#ifndef TLOC_ERROR_H
#define TLOC_ERROR_H

#include <tlocCore/error/tlocErrorTypes.h>

namespace tloc { namespace core { namespace error {

  class Error
  {
  public:
    typedef error_code_type       code_type;

    Error(code_type a_errorType);

    bool Succeeded() const;
    bool Failed() const;

    code_type GetErrorCode() const;

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