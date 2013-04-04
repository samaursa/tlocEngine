#ifndef _TLOC_GRAPHICS_GL_SHADER_VARIABLE_INFO_H_
#define _TLOC_GRAPHICS_GL_SHADER_VARIABLE_INFO_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocCore/data_structures/tlocProtectedBuffer.h>

namespace tloc { namespace graphics { namespace gl {

    struct ShaderVariableInfo
    {
      enum { g_buffSize = 40 }; // try to keep it divisible by 4 and 8

      typedef core::data_structs::ProtectedBuffer<char8, g_buffSize>  buff_type;

      GLsizei     m_nameLength;
      GLint       m_arraySize;
      GLint       m_location;
      GLenum      m_type;
      buff_type   m_name;
    };

};};};

#endif