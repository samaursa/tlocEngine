#include "tlocDrawCommand.h"

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocGLTypes.h>

#include <tlocCore/logging/tlocLogger.h>

TLOC_DEFINE_THIS_FILE_NAME();

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
    DrawCommand(shader_prog_ptr a_shader, shader_op_ptr a_materialOp)
    : m_shaderProg(a_shader)
    , m_materialSO(a_materialOp)
    , m_drawMode(mode::k_points) // points is least likely to fail if set incorrectly
    , m_startIndex(0)
    , m_vertexCount(0)
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
    RenderPass::
    AddDrawCommand(const command_type& a_command) -> this_type&
  { m_commands.push_back(a_command); return *this; }

  void
    DoPrepAndEnableUniforms(DrawCommand::shader_op_ptr a_so, 
                            const gfx_gl::ShaderProgram& a_sp)
  {
    auto err = a_so->PrepareAllUniforms(a_sp);
    if (err.Succeeded())
    { a_so->EnableAllUniforms(a_sp); }
    else
    {
      TLOC_LOG_GFX_WARN_FILENAME_ONLY() << "Shader ID#" << a_sp.GetHandle() 
        << " encountered problems preparing uniforms.";
    }
  }

  void
    DoPrepAndEnableAttributeVBOs(DrawCommand::shader_op_ptr a_so, 
                                 const gfx_gl::ShaderProgram& a_sp, 
                                 const gfx_gl::VertexArrayObject& a_vao)
  {
    auto err = a_so->PrepareAllAttributeVBOs(a_sp, a_vao);
    if (err.Failed())
    {
      TLOC_LOG_GFX_WARN_FILENAME_ONLY() << "Shader ID#" << a_sp.GetHandle() 
        << " encountered problems preparing attributes.";
    }
  }

  void
    RenderPass::
    Draw()
  {
    shader_prog_ptr   currShader;

    for (auto itr = m_commands.begin(), itrEnd = m_commands.end(); 
         itr != itrEnd; ++itr)
    {
      auto& command = *itr;
      auto newShader = command.GetShaderProgram();

      // set or switch shader
      if (currShader != newShader)
      {
        currShader = newShader;
        if (currShader->Enable().Failed())
        {
          TLOC_LOG_GFX_WARN_FILENAME_ONLY() << "ShaderProgram #"
            << currShader->GetHandle() << " could not be enabled";
        }

        DoPrepAndEnableUniforms(command.GetMaterialSO(), *currShader);
      }

      // prepare and enable uniforms/attributes
      auto vao = command.GetVAO();

      for (auto itr = command.begin_so(), itrEnd = command.end_so(); 
           itr != itrEnd; ++itr)
      {
        DoPrepAndEnableUniforms(*itr, *currShader);
        DoPrepAndEnableAttributeVBOs(*itr, *currShader, *vao);
      }

      if (vao)
      {
        gl::VertexArrayObject::Bind b(*vao);
        auto commandMode = DoGetOpenGLModeType(command.GetMode());

        glDrawArrays(commandMode, command.GetStartIndex(), command.GetCount());
      }
    }

    m_commands.clear();
  }

};};};
