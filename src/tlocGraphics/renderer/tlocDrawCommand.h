#pragma once

#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>

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
    typedef gl::shader_program_sptr             shader_prog_ptr;
    typedef gl::vao_vptr                        vao_ptr;

    typedef core_conts::Array<shader_op_ptr>    shader_ops;

  public:
    DrawCommand();

  public:
    this_type&            AddShaderOperator(const shader_op_ptr& a_so);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(mode_type, Mode, m_mode);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(index_type, StartIndex, m_startIndex);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(size_type, Count, m_count);

    TLOC_DECL_AND_DEF_SETTER_CHAIN(vao_ptr, SetVAO, m_vao);

    TLOC_DECL_AND_DEF_GETTER(mode_type,       GetMode, m_mode);
    TLOC_DECL_AND_DEF_GETTER(index_type,      GetStartIndex, m_startIndex);
    TLOC_DECL_AND_DEF_GETTER(size_type,       GetCount, m_count);
    TLOC_DECL_AND_DEF_GETTER(vao_ptr,         GetVAO, m_vao);
    TLOC_DECL_AND_DEF_GETTER(shader_prog_ptr, GetShaderProgram, m_shaderProg);

  private:
    mode_type       m_mode;
    index_type      m_startIndex;
    size_type       m_count;
    shader_ops      m_shaderOps;
    vao_ptr         m_vao;
    shader_prog_ptr m_shaderProg;

  public:
    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(so, m_shaderOps);
  };

  // ///////////////////////////////////////////////////////////////////////
  // Draw

  class Draw
  {
  public:
    typedef Draw                                    this_type;
    typedef DrawCommand                             command_type;
    typedef core_conts::Array<command_type>         command_buffer;

    typedef command_type::shader_op_ptr             shader_op_ptr;
    typedef command_type::shader_prog_ptr           shader_prog_ptr;

  public:
    this_type&            AddCommand(const command_type& a_command);
    void                  Render();

  private:
    shader_prog_ptr       m_currShader;
    command_buffer        m_commands;

  public:
    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(commands, m_commands);
  };

};};};