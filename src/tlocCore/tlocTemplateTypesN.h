// This file is for mostly for internal use, however, you may want to take
// advantage of it. This file allows you to instantiate your template classes
// without code repitition. For example:
// 
// #define CLASS_NAME tloc::Vector
// #define TYPE tloc::f32
// #include "tlocTypes.h"
// #undef TYPE
// 
// The above lines will instantiate the tloc::Vector<> template class with
// the following instantiations. No need for code repetition.

template CLASS_NAME<TYPE, 1>;
template CLASS_NAME<TYPE, 2>;
template CLASS_NAME<TYPE, 3>;
template CLASS_NAME<TYPE, 4>;
template CLASS_NAME<TYPE, 5>;
template CLASS_NAME<TYPE, 6>;
template CLASS_NAME<TYPE, 7>;
template CLASS_NAME<TYPE, 8>;
template CLASS_NAME<TYPE, 9>;

#ifdef TLOC_TEMPLATE_TYPES_SIZE_15
  template CLASS_NAME<TYPE, 10>;
  template CLASS_NAME<TYPE, 11>;
  template CLASS_NAME<TYPE, 12>;
  template CLASS_NAME<TYPE, 13>;
  template CLASS_NAME<TYPE, 14>;
  template CLASS_NAME<TYPE, 15>;
    #ifdef TLOC_TEMPLATE_TYPES_SIZE_20
      template CLASS_NAME<TYPE, 16>;
      template CLASS_NAME<TYPE, 17>;
      template CLASS_NAME<TYPE, 18>;
      template CLASS_NAME<TYPE, 19>;
      template CLASS_NAME<TYPE, 20>;
    #endif // TLOC_TEMPLATE_TYPES_SIZE_20
#endif // TLOC_TEMPLATE_TYPES_SIZE_15