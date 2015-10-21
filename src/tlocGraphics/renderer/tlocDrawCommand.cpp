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
    DrawCommand(shader_prog_ptr a_shader, shader_op_ptr a_materialOp, 
                mem_address a_matPtrAddress)
    : m_shaderProg(a_shader)
    , m_materialSO(a_materialOp)
    , m_matPtrAddress(a_matPtrAddress)
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
  // RenderPass

  RenderPass::
    RenderPass()
    : m_numDrawCalls(0)
  { }

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
    size_type numShaderSwitches = 0, numDrawCalls = 0;

    shader_prog_ptr   currShader;
    mem_address       currMatAddress(nullptr);

    for (auto itr = m_commands.begin(), itrEnd = m_commands.end(); 
         itr != itrEnd; ++itr)
    {
      auto& command = *itr;
      auto newShader = command.GetShaderProgram();

      // set or switch shader
      if (!currShader || currShader->GetHandle() != newShader->GetHandle())
      {
        currShader = newShader;
        numShaderSwitches++;
        if (currShader->Enable().Failed())
        {
          TLOC_LOG_GFX_WARN_FILENAME_ONLY() << "ShaderProgram #"
            << currShader->GetHandle() << " could not be enabled";
        }
      }

      if (currMatAddress != command.GetMaterialAddress())
      {
        currMatAddress = command.GetMaterialAddress();

        DoPrepAndEnableUniforms(command.GetMaterialSO(), *currShader);
      }

      // prepare and enable uniforms/attributes
      auto vao = command.GetVAO();

      for (auto itr2 = command.begin_so(), itrEnd2 = command.end_so(); 
           itr2 != itrEnd2; ++itr2)
      {
        DoPrepAndEnableUniforms(*itr2, *currShader);
        DoPrepAndEnableAttributeVBOs(*itr2, *currShader, *vao);
      }

      if (vao)
      {
        gl::VertexArrayObject::Bind b(*vao);
        auto commandMode = DoGetOpenGLModeType(command.GetMode());

        numDrawCalls++;
        glDrawArrays(commandMode, command.GetStartIndex(), command.GetCount());
      }
    }

    m_numDrawCalls = numDrawCalls;
    m_numShaderSwitches = numShaderSwitches;
    m_commands.clear();
  }

};};};
