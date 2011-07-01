#include "catch_with_main.hpp"
#include "catch.hpp"

#define TLOC_ENABLE_ASSERT_LOW_LEVEL

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTuple.h"
#include "tlocCore/tlocTable.h"
#include "tlocMath/tlocMath.h"
#include "tlocMath/tlocVector.h"
#include "tlocMath/tlocMatrix.h"

using namespace Catch::Detail;
using namespace tloc;

#include "tlocCore/tlocMemory.h"
#include "tlocCore/tlocLinkMe.cpp"

//------------------------------------------------------------------------
// Core
#include "tlocMemoryTest.h"
#include "tlocTupleTest.h"
#include "tlocTableTest.h"

//------------------------------------------------------------------------
// Math
#include "tlocMathTest.h"
#include "tlocVector3Test.h"
#include "tlocVector2Test.h"
#include "tlocMatrixTest.h"
#include "tlocMatrix2Test.h"
#include "tlocMatrix3Test.h"