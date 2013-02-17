#include "tlocTestCommon.h"

#include <tlocCore/containers/tlocContainerTraits.h>

namespace TestingContainerTraits
{
  using namespace tloc;

  TEST_CASE("core/containers/ContainerTraits", "")
  {
    using namespace core_conts;
    using core_conts::type_traits::IsContainer;

    CHECK(IsContainer<Array<int> >::value);
    CHECK( (IsContainer<Array<int, Array_Unordered> >::value) );

    CHECK(IsContainer<List<int> >::value);
    CHECK( (IsContainer<List<int, ListNode<int, core::singly_linked_tag> > >::value) );

    CHECK( (IsContainer<HashMap<int, int> >::value) );
  }
}
