#include "tlocVector.h"
#include "tlocVector.opt.inl.h"

#include <tlocMath/tlocMath.inl.h>

using namespace tloc;

TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f32, 1, DummyStruct);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f64, 1, DummyStruct);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f128, 1, DummyStruct);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f32, 2, DummyStruct);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f64, 2, DummyStruct);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f128, 2, DummyStruct);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f32, 3, DummyStruct);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f64, 3, DummyStruct);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f128, 3, DummyStruct);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR_ALL_ACCURACIES(f32, 4, DummyStruct);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f64, 4, DummyStruct);
TLOC_EXPLICITLY_INSTANTIATE_VECTOR(f128, 4, DummyStruct);