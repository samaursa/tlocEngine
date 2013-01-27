#ifndef _TLOC_GRAPHICS_GL_UNIFORM_EXPLICIT_MACROS_H_
#define _TLOC_GRAPHICS_GL_UNIFORM_EXPLICIT_MACROS_H_

#define TLOC_INSTANTIATE_DO_SET_VALUES(_type_)\
  template Uniform& Uniform::DoSetValueAs(const _type_&)

#endif