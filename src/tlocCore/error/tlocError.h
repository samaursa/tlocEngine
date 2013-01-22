#ifndef _TLOC_CORE_ERROR_H_
#define _TLOC_CORE_ERROR_H_

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/error/tlocErrorTypes.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace core { namespace error {

  class Error
  {
  public:
    typedef Error                 this_type;
    typedef error_code_type       code_type;

    Error();
    Error(code_type a_errorType);

    bool Succeeded() const;
    bool Failed() const;

    bool operator==(const this_type& a_other);
    bool operator==(const code_type& a_other);

    bool operator!=(const this_type& a_other);
    bool operator!=(const code_type& a_other);

    TLOC_DECL_AND_DEF_GETTER(code_type, GetErrorCode, m_error);

  private:
    code_type m_error;
  };

};};};

namespace tloc
{
  class ErrorSuccess : public core::error::Error
  {
  public:
    ErrorSuccess() : Error(common_error_types::error_success) {}
  };

  class ErrorFailure : public core::error::Error
  {
  public:
    ErrorFailure() : Error(common_error_types::error_failure) {}
  };
};

#endif