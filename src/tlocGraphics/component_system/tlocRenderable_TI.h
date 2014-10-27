#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDERABLE_TI_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDERABLE_TI_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>

namespace tloc { namespace graphics { namespace component_system {

  template <typename T_Component, tl_int T_ComponentEnumType>
  class Renderable_TI
    : public core_cs::Component_T<T_Component, 
                                  core_cs::component_group::k_graphics, 
                                  T_ComponentEnumType>
  {
  public:
    typedef Renderable_TI<T_Component, k_component_type>    this_type;
    typedef core_cs::Component_T
      <T_Component, k_component_group, k_component_type>    base_type;

    typedef typename base_type::component_type              component_type;
    typedef gfx_gl::shader_operator_vso                     so_type;

  public:
    TLOC_DECL_AND_DEF_GETTER_DIRECT(so_type, GetShaderOperator, m_shaderOp);

  protected:
    Renderable_TI(BufferArg a_debugName);

  private:
    so_type         m_shaderOp;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_Component, tl_int T_ComponentEnumType>
  Renderable_TI<T_Component, T_ComponentEnumType>::
    Renderable_TI(BufferArg a_debugName)
    : base_type(a_debugName)
  { }

};};};

#endif