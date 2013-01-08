#ifndef _TLOC_GRAPHICS_GL_SHADER_VARIABLE_EXPLICIT_MACROS_H_
#define _TLOC_GRAPHICS_GL_SHADER_VARIABLE_EXPLICIT_MACROS_H_

#define TLOC_SHADER_VARIABLE_EXPLICIT(_derType_)\
  template class ShaderVariable_TI<_derType_>

#define TLOC_SHADER_VARIABLE_DO_SET_VALUE_AS(_type_, _derType_)\
  template ShaderVariable_TI<_derType_>::derived_type& \
  ShaderVariable_TI<_derType_>::DoSetValueAs(const _type_&);\
  \
  template ShaderVariable_TI<_derType_>::derived_type& \
  ShaderVariable_TI<_derType_>::DoSetValueAs(const Array<_type_>&,\
                                             p_shader_variable_ti::CopyArray);\
  \
  template ShaderVariable_TI<_derType_>::derived_type& \
  ShaderVariable_TI<_derType_>::DoSetValueAs(Array<_type_>&,\
                                             p_shader_variable_ti::SwapArray)

#endif