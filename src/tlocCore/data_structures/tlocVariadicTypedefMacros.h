#ifndef TLOC_CORE_VARIADIC_TYPEDEF_MACROS_H
#define TLOC_CORE_VARIADIC_TYPEDEF_MACROS_H

#define TLOC_DECLARE_VARIADIC_TYPES(_type_, _post_fix_) \
typedef Variadic<_type_, 1>  Variadic1  ##_post_fix_; \
typedef Variadic<_type_, 2>  Variadic2  ##_post_fix_; \
typedef Variadic<_type_, 3>  Variadic3  ##_post_fix_; \
typedef Variadic<_type_, 4>  Variadic4  ##_post_fix_; \
typedef Variadic<_type_, 5>  Variadic5  ##_post_fix_; \
typedef Variadic<_type_, 6>  Variadic6  ##_post_fix_; \
typedef Variadic<_type_, 7>  Variadic7  ##_post_fix_; \
typedef Variadic<_type_, 8>  Variadic8  ##_post_fix_; \
typedef Variadic<_type_, 9>  Variadic9  ##_post_fix_; \
typedef Variadic<_type_, 10> Variadic10 ##_post_fix_  \

#define TLOC_EXPLICITLY_INSTANTIATE_VARIADIC_TYPES(_type_) \
  template class Variadic<_type_, 1>;\
  template class Variadic<_type_, 2>;\
  template class Variadic<_type_, 3>;\
  template class Variadic<_type_, 4>;\
  template class Variadic<_type_, 5>;\
  template class Variadic<_type_, 6>;\
  template class Variadic<_type_, 7>;\
  template class Variadic<_type_, 8>;\
  template class Variadic<_type_, 9>;\
  template class Variadic<_type_, 10>

#endif