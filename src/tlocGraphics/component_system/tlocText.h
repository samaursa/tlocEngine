#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_STATIC_TEXT_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_STATIC_TEXT_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/memory/tlocBufferArg.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace graphics { namespace component_system {

  //class StaticText
  //  : public core_cs::Component_T<StaticText, components::static_text>
  //{
  //public:
  //  typedef StaticText                                      this_type;
  //  typedef Component_T<this_type, components::static_text> base_type;
  //  typedef f32                                             real_type;
  //  typedef core_str::String                                str_type;

  //  typedef char8                                       symbol_type;
  //  typedef core::Pair<symbol_type, math_t::Rectf32_c>  symbol_tcoord_pair_type;
  //  typedef core_conts::Array<symbol_tcoord_pair_type>  text_cont;

  //public:
  //  StaticText();
  //  explicit StaticText(BufferArg a_text);

  //  TLOC_DECL_AND_DEF_SETTER_BY_VALUE(BufferArg, Set, m_text);
  //  TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(str_type, Get, m_text);

  //private:
  //  str_type              m_text;
  //  text_cont             m_symbols;

  //};

};};};

#endif