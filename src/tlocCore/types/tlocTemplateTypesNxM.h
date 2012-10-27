// This file is for mostly for internal use, however, you may want to take
// advantage of it. This file allows you to instantiate your template classes
// without code repitition. For example:
//
// #define CLASS_NAME tloc::Table
// #define TYPE tloc::f32
// #include <tlocCore/types/tlocTypes.h>
// #undef TYPE
//
// The above lines will instantiate the tloc::Table<> template class with
// the following instantiations. No need for code repetition.

#define ROW_NUM 1
#include "tlocTemplateTypesNxM.helper.h"
#undef ROW_NUM

#define ROW_NUM 2
#include "tlocTemplateTypesNxM.helper.h"
#undef ROW_NUM

#define ROW_NUM 3
#include "tlocTemplateTypesNxM.helper.h"
#undef ROW_NUM

#define ROW_NUM 4
#include "tlocTemplateTypesNxM.helper.h"
#undef ROW_NUM

#define ROW_NUM 5
#include "tlocTemplateTypesNxM.helper.h"
#undef ROW_NUM

#define ROW_NUM 6
#include "tlocTemplateTypesNxM.helper.h"
#undef ROW_NUM

#define ROW_NUM 7
#include "tlocTemplateTypesNxM.helper.h"
#undef ROW_NUM

#define ROW_NUM 8
#include "tlocTemplateTypesNxM.helper.h"
#undef ROW_NUM

#define ROW_NUM 9
#include "tlocTemplateTypesNxM.helper.h"
#undef ROW_NUM

//////////////////////////////////////////////////////////////////////////
#ifdef TLOC_TEMPLATE_TYPES_SIZE_15

  #define ROW_NUM 10
  #include "tlocTemplateTypesNxM.helper.h"
  #undef ROW_NUM

  #define ROW_NUM 11
  #include "tlocTemplateTypesNxM.helper.h"
  #undef ROW_NUM

  #define ROW_NUM 12
  #include "tlocTemplateTypesNxM.helper.h"
  #undef ROW_NUM

  #define ROW_NUM 13
  #include "tlocTemplateTypesNxM.helper.h"
  #undef ROW_NUM

  #define ROW_NUM 14
  #include "tlocTemplateTypesNxM.helper.h"
  #undef ROW_NUM

  #define ROW_NUM 15
  #include "tlocTemplateTypesNxM.helper.h"
  #undef ROW_NUM

  //////////////////////////////////////////////////////////////////////////
    #ifdef TLOC_TEMPLATE_TYPES_SIZE_20

    #define ROW_NUM 16
    #include "tlocTemplateTypesNxM.helper.h"
    #undef ROW_NUM

    #define ROW_NUM 17
    #include "tlocTemplateTypesNxM.helper.h"
    #undef ROW_NUM

    #define ROW_NUM 18
    #include "tlocTemplateTypesNxM.helper.h"
    #undef ROW_NUM

    #define ROW_NUM 19
    #include "tlocTemplateTypesNxM.helper.h"
    #undef ROW_NUM

    #define ROW_NUM 20
    #include "tlocTemplateTypesNxM.helper.h"
    #undef ROW_NUM

#endif // TLOC_TEMPLATE_TYPES_SIZE_20
#endif // TLOC_TEMPLATE_TYPES_SIZE_15