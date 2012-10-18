#include "tlocObject.h"

TLOC_INTENTIONALLY_EMPTY_SOURCE_FILE();

namespace tloc { namespace graphics { namespace gl {

  ObjectBase::ObjectBase()
  { }

  bool ObjectBase::IsValid()
  {
    return m_handle != 0;
  }

};};};