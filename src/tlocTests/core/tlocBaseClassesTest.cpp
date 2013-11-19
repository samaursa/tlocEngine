#include "tlocTestCommon.h"

#include <tlocCore/base_classes/tlocInitializeAndDestroy.h>

namespace TestingBaseClasses
{
  using namespace tloc;
  using namespace core_bclass;

    
  struct Success
    : public InitializeAndDestroy_TI<Success>
  {
  public:
    typedef InitializeAndDestroy_TI<Success>            base_type;
    typedef Success                                     this_type;
    
    typedef base_type::error_type                       error_type;
    
  public:
    friend class InitializeAndDestroy_TI<Success>;
    
  public:
    TLOC_USING_INITIALIZE_AND_DESTROY_METHODS();
    
  protected:
    error_type DoInitialize()
    { return ErrorSuccess; }
    
    error_type DoDestroy()
    { return ErrorSuccess;}
  };
  
  TEST_CASE("core/base_classes/InitializeAndDestroy_TI", "")
  {
    // ```````````````````````````````````````````````````````````````````````
    // class declaration

    Success s;
    CHECK(s.Initialize() == ErrorSuccess);
    CHECK(s.Destroy() == ErrorSuccess);
  }
};