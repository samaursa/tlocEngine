#include "catch_with_main.hpp"
#include "catch.hpp"

#define TLOC_ENABLE_ASSERT_LOW_LEVEL

using namespace Catch::Detail;

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocMemory.h"
#include "tlocCore/tlocLinkMe.cpp"

//------------------------------------------------------------------------
// Core

#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocTypes.inl"

#include "tlocCore/tlocAlgorithms.h"
#include "tlocCore/tlocAlgorithms.inl"

#include "tlocCore/tlocArray.h"
#include "tlocCore/tlocArray.inl"

#include "tlocCore/tlocList.h"
#include "tlocCore/tlocList.inl"

#include "tlocCore/tlocString.h"
#include "tlocCore/tlocString.inl"

#include "tlocCore/tlocTuple.h"
#include "tlocCore/tlocTuple.inl"

#include "tlocCore/tlocTable.h"
#include "tlocCore/tlocTable.inl"

#include "tlocCore/tlocIterator.h"
#include "tlocCore/tlocIterator.inl"

#include "tlocTypesTest.h"
#include "tlocAlgorithmsTest.h"
#include "tlocMemoryTest.h"
#include "tlocTupleTest.h"
#include "tlocTableTest.h"
#include "tlocArrayTest.h"
#include "tlocListTest.h"
#include "tlocStringTest.h"
#include "tlocIteratorTest.h"

//------------------------------------------------------------------------
// Math
#include "tlocMath/tlocMath.h"
#include "tlocMath/tlocMath.inl"

#include "tlocMath/tlocVector.h"
#include "tlocMath/tlocVector.inl"

#include "tlocMath/tlocMatrix.h"
#include "tlocMath/tlocMatrix.inl"

#include "tlocMathTest.h"
#include "tlocVector3Test.h"
#include "tlocVector2Test.h"
#include "tlocMatrixTest.h"
#include "tlocMatrix2Test.h"
#include "tlocMatrix3Test.h"