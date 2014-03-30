#include "tlocSharedPtr.h"
#include "tlocSharedPtr.inl.h"

#include <tlocCore/tlocAssert.h>

namespace tloc { namespace core { namespace smart_ptr {

  namespace p_shared_ptr
  {
    namespace null_copy
    {
      void 
        Allow::
        CheckNullBeforeCopy( void* )
      { /* Intentionally Empty */ }

      void 
        Disallow::
        CheckNullBeforeCopy(void* a_rawPtr)
      {
        TLOC_ASSERT_LOW_LEVEL( a_rawPtr != nullptr,
                               "Copy of NULL SharedPtr is disabled" );
        TLOC_UNUSED( a_rawPtr );
      }
    };
  };

};};};