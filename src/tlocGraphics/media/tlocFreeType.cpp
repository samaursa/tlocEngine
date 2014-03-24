#include "tlocFreeType.h"

#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace media { 

  FreeType::
    FreeType()
    : m_library(nullptr)
  { }

  FreeType::error_type 
    FreeType::
    DoInitialize(const data_type& a_data)
  {
    FT_Error error = FT_Init_FreeType( &m_library );
    if ( error )
    {
      TLOC_LOG_GFX_ERR() <<
        "Failed to initialize FreeType - FreeType error code: " << error;
      return TLOC_ERROR( gfx_err::Type::error_free_type_initialize );
    }

    const FT_Byte* rawData =
      reinterpret_cast<const FT_Byte*>( a_data.begin() );

    error = FT_New_Memory_Face( m_library, rawData, a_data.size(), 0, &m_face );

    if ( error )
    {
      TLOC_LOG_GFX_ERR() <<
        "Failed to load font from memory - FreeType error code: " << error;
      return TLOC_ERROR( gfx_err::Type::error_free_type_error_loading_font );
    }

    return ErrorSuccess;
  }

  FreeType::error_type
    FreeType::
    DoDestroy()
  { 
    AssertIsDestroyed();

    if (m_library)
    { FT_Done_FreeType(m_library); }

    return ErrorSuccess;
  }

};};};

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(tloc::char8);