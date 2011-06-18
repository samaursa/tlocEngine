// This file is for mostly for internal use, however, you may want to take
// advantage of it. This file allows you to instantiate your template classes
// without code repitition. For example:
// 
// #define CLASS_NAME tloc::Table
// #define TYPE tloc::f32
// #include "tlocTypes.h"
// #undef TYPE
// 
// The above lines will instantiate the tloc::Table<> template class with
// the following instantiations. No need for code repetition.

#define ROW_NUM 1
#include "tlocTemplateTypesNxM.helper.h"
#undef ROW_NUM