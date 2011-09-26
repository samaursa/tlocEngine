#include "catch_with_main.hpp"
#include "catch.hpp"

#define TLOC_ENABLE_ASSERT_LOW_LEVEL

using namespace Catch::Detail;

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocMemory.h"
#include "tlocCore/tlocLinkMe.cpp"

//------------------------------------------------------------------------
// Core
#include "tlocCore/tlocAlgorithms.h"
#include "tlocCore/tlocArray.h"
#include "tlocCore/tlocString.h"
#include "tlocCore/tlocTuple.h"
#include "tlocCore/tlocTable.h"

#include "tlocAlgorithmsTest.h"
#include "tlocMemoryTest.h"
#include "tlocTupleTest.h"
#include "tlocTableTest.h"
#include "tlocArrayTest.h"
#include "tlocStringTest.h"

//------------------------------------------------------------------------
// Math
#include "tlocMath/tlocMath.h"
#include "tlocMath/tlocVector.h"
#include "tlocMath/tlocMatrix.h"

#include "tlocMathTest.h"
#include "tlocVector3Test.h"
#include "tlocVector2Test.h"
#include "tlocMatrixTest.h"
#include "tlocMatrix2Test.h"
#include "tlocMatrix3Test.h"