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
  template Variadic<_type_, 1>::Variadic(_type_ const (&)[1]);\
  template class Variadic<_type_, 2>;\
  template Variadic<_type_, 2>::Variadic(_type_ const (&)[2]);\
  template class Variadic<_type_, 3>;\
  template Variadic<_type_, 3>::Variadic(_type_ const (&)[3]);\
  template class Variadic<_type_, 4>;\
  template Variadic<_type_, 4>::Variadic(_type_ const (&)[4]);\
  template class Variadic<_type_, 5>;\
  template Variadic<_type_, 5>::Variadic(_type_ const (&)[5]);\
  template class Variadic<_type_, 6>;\
  template Variadic<_type_, 6>::Variadic(_type_ const (&)[6]);\
  template class Variadic<_type_, 7>;\
  template Variadic<_type_, 7>::Variadic(_type_ const (&)[7]);\
  template class Variadic<_type_, 8>;\
  template Variadic<_type_, 8>::Variadic(_type_ const (&)[8]);\
  template class Variadic<_type_, 9>;\
  template Variadic<_type_, 9>::Variadic(_type_ const (&)[9]);\
  template class Variadic<_type_, 10>;\
  template Variadic<_type_, 10>::Variadic(_type_ const (&)[10])

#endif