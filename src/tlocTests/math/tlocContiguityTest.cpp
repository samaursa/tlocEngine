#include "tlocTestCommon.h"

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl>

#include <tlocMath/vector/tlocVector2.h>
#include <tlocMath/vector/tlocVector3.h>
#include <tlocMath/vector/tlocVector4.h>

namespace TestingContiguity
{
  using namespace tloc;
  using namespace tloc::core;
  using namespace tloc::math;

  // The purpose of these tests is to test that certain classes are laid out
  // contiguously in memory without any padding. This is very important for
  // serializing tasks and some required casting code (such as an array for
  // math::vector being casted to an array of floats with defined results)

  // _numMembers_ is the number of members in _type_ where _type_ is the type
  // we are testing for contiguity in an array

  template <typename T_Type>
  void TestVec()
  {
    typedef T_Type                           test_type;
    typedef typename test_type::value_type   value_type;
    typedef Array<test_type>                 cont_type;

    cont_type v(32);
    value_type* first = static_cast<value_type*>(static_cast<void*>(&v[0]));
    bool testPassed = true;

    const tl_size numElements = typename T_Type::k_size;

    for (cont_type::size_type i = 0, size = v.size(); i != size; ++i)
    {
      for (tl_size j = 0; j < numElements; ++j)
      {
        if ( (first + ((i * numElements) + j) )   != (&(v[i][j])) )
        {
          testPassed = false; break;
        }
      }
    }

    CHECK(testPassed);
  }

  TEST_CASE("Math/Contiguity/Vector", "")
  {
    TestVec<Vec2f>();
    TestVec<Vec2f32>();
    TestVec<Vec2f64>();

    TestVec<Vec3f>();
    TestVec<Vec3f32>();
    TestVec<Vec3f64>();

    TestVec<Vec4f>();
    TestVec<Vec4f32>();
    TestVec<Vec4f64>();
  }
};