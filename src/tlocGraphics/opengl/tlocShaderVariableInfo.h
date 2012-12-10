#pragma once

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocCore/containers/tlocProtectedBuffer.h>

namespace tloc { namespace graphics { namespace gl {

    struct ShaderVariableInfo
    {
      enum { g_buffSize = 40 };

      typedef core::ProtectedBuffer<char8, g_buffSize>  buff_type;

      GLsizei     m_nameLength;
      GLint       m_arraySize;
      GLint       m_location;
      GLenum      m_type;
      buff_type   m_name;
    };

};};};