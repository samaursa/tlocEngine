#include "tlocTestCommon.h"

#define private public
#include <tlocCore/containers/tlocCharBuffer.h>
#include <tlocCore/containers/tlocCharBuffer.inl>

namespace ProtectedBufferTest
{
  using namespace tloc::core;

  template <typename T_BuildConfig>
  struct CheckBufferStatusForInvalidBuffer
  {
    void operator()(bool a_isValid)
    {
      CHECK(a_isValid == false);
    }
  };

  template <>
  struct CheckBufferStatusForInvalidBuffer<p_build_config::Release>
  {
    void operator()(bool)
    {
    }
  };

  TEST_CASE("Core/containers/ProtectedBuffers", "")
  {
    typedef CharBuffer<5>                     char5;
    typedef BuildConfig<>::build_config_type  build_config_type;

    {
      const char* word = "1234";
      char5 p;
      for (int i = 0; i < 5; ++i)
      {
        p.Get()[i] = word[i];
      }
      REQUIRE(p.DoIsBufferValid(build_config_type()) == true);
    }

    {
      char5 p;
      sprintf(p.Get(), "This ");

      bool isBufferValid = p.DoIsBufferValid(build_config_type());

      CheckBufferStatusForInvalidBuffer<BuildConfig<>::build_config_type>()(isBufferValid);
      //CHECK(isBufferValid == false);

      p.DoInit(build_config_type()); // To avoid the assertion in the destructor
    }
  }
}
