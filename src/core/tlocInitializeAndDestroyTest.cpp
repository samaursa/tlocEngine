#include "tlocTestCommon.h"

#include <tlocCore/base_classes/tlocInitializeAndDestroy.h>

namespace TestingInitializeAndDestroy
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
    TLOC_DECLARE_FRIEND_INITIALIZE_AND_DESTROY(this_type);
    
  public:
    TLOC_USING_INITIALIZE_AND_DESTROY_METHODS();
    
  protected:
    error_type DoInitialize()
    { return ErrorSuccess; }
    
    error_type DoDestroy()
    { return ErrorSuccess;}
  };

  //////////////////////////////////////////////////////////////////////////
  // SuccessOneParam

  struct SuccessOneParam
    : public InitializeAndDestroy_TI<SuccessOneParam, 
                core_bclass::p_initialize_and_destroy::OneParam>
  {
  public:
    typedef SuccessOneParam                             this_type;
    typedef InitializeAndDestroy_TI<this_type,
      core_bclass::p_initialize_and_destroy::OneParam>  base_type;
    
    typedef base_type::error_type                       error_type;
    
  public:
    TLOC_DECLARE_FRIEND_INITIALIZE_AND_DESTROY_ONE_PARAM(this_type);
    
  public:
    TLOC_USING_INITIALIZE_AND_DESTROY_METHODS();
    
  protected:
    error_type DoInitialize(int)
    { return ErrorSuccess; }
    
    error_type DoDestroy()
    { return ErrorSuccess;}
  };

  //////////////////////////////////////////////////////////////////////////
  // SuccessTwoParams

  struct SuccessTwoParams
    : public InitializeAndDestroy_TI<SuccessTwoParams,
                core_bclass::p_initialize_and_destroy::TwoParams>
  {
  public:
    typedef SuccessTwoParams                            this_type;
    typedef InitializeAndDestroy_TI<this_type,
      core_bclass::p_initialize_and_destroy::TwoParams>  base_type;
    typedef base_type::error_type                       error_type;
    
  public:
    TLOC_DECLARE_FRIEND_INITIALIZE_AND_DESTROY_TWO_PARAMS(this_type);
    
  public:
    TLOC_USING_INITIALIZE_AND_DESTROY_METHODS();
    
  protected:
    error_type DoInitialize(int, float)
    { return ErrorSuccess; }
    
    error_type DoDestroy()
    { return ErrorSuccess;}
  };

  //////////////////////////////////////////////////////////////////////////
  // SuccessTwoParams

  struct SuccessThreeParams
    : public InitializeAndDestroy_TI<SuccessThreeParams,
                core_bclass::p_initialize_and_destroy::ThreeParams>
  {
  public:
    typedef SuccessThreeParams                          this_type;
    typedef InitializeAndDestroy_TI<this_type,
      core_bclass::p_initialize_and_destroy::ThreeParams>  base_type;
    
    typedef base_type::error_type                       error_type;
    
  public:
    TLOC_DECLARE_FRIEND_INITIALIZE_AND_DESTROY_THREE_PARAMS(this_type);
    
  public:
    TLOC_USING_INITIALIZE_AND_DESTROY_METHODS();
    
  protected:
    error_type DoInitialize(int, float, double)
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

    SuccessOneParam s1;
    CHECK(s1.Initialize(10) == ErrorSuccess);
    CHECK(s1.Destroy() == ErrorSuccess);

    SuccessTwoParams s2;
    CHECK(s2.Initialize(10, 5.0f) == ErrorSuccess);
    CHECK(s2.Destroy() == ErrorSuccess);

    SuccessThreeParams s3;
    CHECK(s3.Initialize(10, 5.0f, 10.0) == ErrorSuccess);
    CHECK(s3.Destroy() == ErrorSuccess);

    //SECTION("Assert fired if Destroy() not called", "")
    {
      TLOC_TEST_ASSERT
      {
        Success s4;
        s4.Initialize();
      }
      TLOC_TEST_ASSERT_CHECK();
    }
  }
};