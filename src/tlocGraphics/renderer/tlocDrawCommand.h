#pragma once

#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>
#include <tlocCore/base_classes/tlocDebugName.h>

namespace tloc { namespace graphics { namespace renderer {

  namespace mode {
    enum {

      k_points = 0,
      k_line_strip,
      k_line_loop,
      k_lines,
      k_triangle_strip,
      k_triangle_fan,
      k_triangles,

    }; typedef tl_int               value_type;
  };

  // ///////////////////////////////////////////////////////////////////////
  // DrawCommand

  class DrawCommand
  {
  public:
    typedef DrawCommand                         this_type;
    typedef mode::value_type                    mode_type;
    typedef tl_int                              index_type;
    typedef tl_size                             size_type;
    typedef gl::shader_operator_vptr            shader_op_ptr;
    typedef gl::shader_program_vptr             shader_prog_ptr;
    typedef gl::vao_vptr                        vao_ptr;

    typedef core_conts::Array<shader_op_ptr>    shader_ops;

  public:
    DrawCommand(shader_prog_ptr a_shader, shader_op_ptr a_materialOp);

  public:
    this_type&            AddShaderOperator(const shader_op_ptr& a_so);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(mode_type, SetDrawMode, m_drawMode);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(index_type, SetStartIndex, m_startIndex);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(size_type, SetVertexCount, m_vertexCount);

    TLOC_DECL_AND_DEF_SETTER_CHAIN(vao_ptr, SetVAO, m_vao);

    TLOC_DECL_AND_DEF_GETTER(mode_type,       GetMode, m_drawMode);
    TLOC_DECL_AND_DEF_GETTER(index_type,      GetStartIndex, m_startIndex);
    TLOC_DECL_AND_DEF_GETTER(size_type,       GetCount, m_vertexCount);
    TLOC_DECL_AND_DEF_GETTER(vao_ptr,         GetVAO, m_vao);
    TLOC_DECL_AND_DEF_GETTER(shader_prog_ptr, GetShaderProgram, m_shaderProg);
    TLOC_DECL_AND_DEF_GETTER(shader_op_ptr,   GetMaterialSO, m_materialSO);

  private:
    shader_prog_ptr m_shaderProg;
    shader_op_ptr   m_materialSO;

    mode_type       m_drawMode;
    index_type      m_startIndex;
    size_type       m_vertexCount;
    shader_ops      m_shaderOps;

    vao_ptr         m_vao;

  public:
    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_so, m_shaderOps);
  };

  // ///////////////////////////////////////////////////////////////////////
  // Draw

  class RenderPass
  {
  public:
    typedef RenderPass                          this_type;
    typedef DrawCommand                         command_type;
    typedef core_conts::Array<command_type>     command_buffer;
    typedef tl_size                             size_type;

    typedef command_type::shader_op_ptr         shader_op_ptr;
    typedef command_type::shader_prog_ptr       shader_prog_ptr;

  public:
    RenderPass();

    this_type&            AddDrawCommand(const command_type& a_command);
    void                  Draw();

    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumDrawCalls, m_numDrawCalls);

  private:
    command_buffer        m_commands;
    size_type             m_numDrawCalls;

  public:
    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_commands, m_commands);
  };

};};};