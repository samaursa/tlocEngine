#include "tlocDrawCommand.h"

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocGLTypes.h>

namespace tloc { namespace graphics { namespace renderer {

  namespace {

    auto 
      DoGetOpenGLModeType(const mode::value_type a_mode) -> mode::value_type
    {
      using namespace mode;

      switch(a_mode)
      {
      case k_points:          return GL_POINTS;
      case k_line_strip:      return GL_LINE_STRIP;
      case k_line_loop:       return GL_LINE_LOOP;
      case k_lines:           return GL_LINES;
      case k_triangle_strip:  return GL_TRIANGLE_STRIP;
      case k_triangle_fan:    return GL_TRIANGLE_FAN;
      case k_triangles:       return GL_TRIANGLES;
      default:
        TLOC_ASSERT_FALSE("Incorrect draw mode");
        return GL_POINTS;
      }
    }

  };

  // ///////////////////////////////////////////////////////////////////////
  // DrawCommands

  DrawCommand::
    DrawCommand()
    : m_mode(mode::k_points)
    , m_startIndex(0)
    , m_count(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    DrawCommand::
    AddShaderOperator(const shader_op_ptr& a_so) -> this_type&
  {
    m_shaderOps.push_back(a_so);
    return *this;
  }

  // ///////////////////////////////////////////////////////////////////////
  // Draw

  auto
    Draw::
    AddCommand(const command_type& a_command) -> this_type&
  { m_commands.push_back(a_command); return *this; }

  void
    Draw::
    Render()
  {
    for (auto& command : m_commands)
    {
      if (m_currShader != command.GetShaderProgram())
      {
        m_currShader = command.GetShaderProgram();
        m_currShader->Enable();
      }

      for (auto itr = command.begin_so(), itrEnd = command.end_so(); 
           itr != itrEnd; ++itr)
      {
        if ((*itr)->PrepareAllUniforms(*m_currShader).Succeeded())
        { (*itr)->EnableAllUniforms(*m_currShader); }
      }

      auto vao = command.GetVAO();

      if (vao)
      {
        gl::VertexArrayObject::Bind b(*vao);
        auto commandMode = DoGetOpenGLModeType(command.GetMode());

        glDrawArrays(commandMode, command.GetStartIndex(), command.GetCount());
      }
    }
  }

};};};
