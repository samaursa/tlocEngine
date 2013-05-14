#include "tlocString.h"
#include "tlocString.inl.h"

namespace tloc { namespace core { namespace string {

  template class StringBase<char8>;
  template class StringBase<char32>;

};};};

//TLOC_INTENTIONALLY_EMPTY_SOURCE_FILE();