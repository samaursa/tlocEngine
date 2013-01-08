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
typedef Variadic<_type_, 10> Variadic10 ##_post_fix_; \
typedef Variadic<_type_, 11> Variadic11 ##_post_fix_; \
typedef Variadic<_type_, 12> Variadic12 ##_post_fix_; \
typedef Variadic<_type_, 13> Variadic13 ##_post_fix_; \
typedef Variadic<_type_, 14> Variadic14 ##_post_fix_; \
typedef Variadic<_type_, 15> Variadic15 ##_post_fix_; \
typedef Variadic<_type_, 16> Variadic16 ##_post_fix_;

#define TLOC_INSTANTIATE_VARIADIC(_type_, _size_)\
  template class Variadic<_type_, _size_>;\
  template Variadic<_type_, _size_>::Variadic(_type_ const (&)[_size_]);\
  template _type_& Tuple<_type_, _size_>::operator[] (tl_int);\
  template const _type_& Tuple<_type_, _size_>::operator[] (tl_int) const;\
  template Tuple<_type_, _size_>::size_type Tuple<_type_, _size_>::GetSize() const

#define TLOC_EXPLICITLY_INSTANTIATE_VARIADIC_TYPES(_type_) \
  TLOC_INSTANTIATE_VARIADIC(_type_, 1);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 2);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 3);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 4);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 5);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 6);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 7);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 8);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 9);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 10);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 11);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 12);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 13);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 14);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 15);\
  TLOC_INSTANTIATE_VARIADIC(_type_, 16)
  //template class Variadic<_type_, 1>;\
  //template Variadic<_type_, 1>::Variadic(_type_ const (&)[1]);\
  //template class Variadic<_type_, 2>;\
  //template Variadic<_type_, 2>::Variadic(_type_ const (&)[2]);\
  //template class Variadic<_type_, 3>;\
  //template Variadic<_type_, 3>::Variadic(_type_ const (&)[3]);\
  //template class Variadic<_type_, 4>;\
  //template Variadic<_type_, 4>::Variadic(_type_ const (&)[4]);\
  //template class Variadic<_type_, 5>;\
  //template Variadic<_type_, 5>::Variadic(_type_ const (&)[5]);\
  //template class Variadic<_type_, 6>;\
  //template Variadic<_type_, 6>::Variadic(_type_ const (&)[6]);\
  //template class Variadic<_type_, 7>;\
  //template Variadic<_type_, 7>::Variadic(_type_ const (&)[7]);\
  //template class Variadic<_type_, 8>;\
  //template Variadic<_type_, 8>::Variadic(_type_ const (&)[8]);\
  //template class Variadic<_type_, 9>;\
  //template Variadic<_type_, 9>::Variadic(_type_ const (&)[9]);\
  //template class Variadic<_type_, 10>;\
  //template Variadic<_type_, 10>::Variadic(_type_ const (&)[10]);\
  //template class Variadic<_type_, 11>;\
  //template Variadic<_type_, 11>::Variadic(_type_ const (&)[11]);\
  //template class Variadic<_type_, 12>;\
  //template Variadic<_type_, 12>::Variadic(_type_ const (&)[12]);\
  //template class Variadic<_type_, 13>;\
  //template Variadic<_type_, 13>::Variadic(_type_ const (&)[13]);\
  //template class Variadic<_type_, 14>;\
  //template Variadic<_type_, 14>::Variadic(_type_ const (&)[14]);\
  //template class Variadic<_type_, 15>;\
  //template Variadic<_type_, 15>::Variadic(_type_ const (&)[15]);\
  //template class Variadic<_type_, 16>;\
  //template Variadic<_type_, 16>::Variadic(_type_ const (&)[16]);\
  //template class Tuple<_type_, 1>;\

#endif