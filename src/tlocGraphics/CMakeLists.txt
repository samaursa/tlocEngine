set(TLOC_GRAPHICS 
  tlocDepVersionCheck.cpp 
  tlocGraphicsBase.h 
  tloc_graphics.cpp 
  tloc_graphics.h 
  tloc_graphics.inl 
  )

set(3RD_PARTY_PATH ${TLOC_PATH}/src/3rdParty/Graphics/)
set(TLOC_GRAPHICS_3RD_PARTY_COMPRESSION
  ${3RD_PARTY_PATH}/miniz/miniz.c
  )

if(WIN32)
  set(TLOC_GRAPHICS_3RD_PARTY_GLEW
    ${3RD_PARTY_PATH}/GLEW/GLEW.C
    ${3RD_PARTY_PATH}/GLEW/GLEW.H
    ${3RD_PARTY_PATH}/GLEW/glewinfo.c
    ${3RD_PARTY_PATH}/GLEW/GLXEW.H
    ${3RD_PARTY_PATH}/GLEW/wglew.h
    )
  set(TLOC_GRAPHICS_3RD_PARTY_GLEXT
    ${3RD_PARTY_PATH}/glext/glext.h
    ${3RD_PARTY_PATH}/glext/glxext.h
    ${3RD_PARTY_PATH}/glext/wglext.h
    )
else()
  set(TLOC_GRAPHICS_3RD_PARTY_GLEW
    )
  set(TLOC_GRAPHICS_3RD_PARTY_GLEXT
    )
endif()

set(TLOC_GRAPHICS_3RD_PARTY_IMAGES_PNG
    ${3RD_PARTY_PATH}/lodepng/lodepng.h
    ${3RD_PARTY_PATH}/lodepng/lodepng.c
    )

set(TLOC_GRAPHICS_APPLICATION 
  )

set(TLOC_GRAPHICS_COMPONENT_SYSTEM
  component_system/tlocComponentType.h 
  component_system/tlocFan.cpp 
  component_system/tlocFan.h 
  component_system/tlocFanRenderSystem.cpp 
  component_system/tlocFanRenderSystem.h 
  component_system/tlocMaterial.cpp 
  component_system/tlocMaterial.h 
  component_system/tlocMaterialSystem.cpp 
  component_system/tlocMaterialSystem.h 
  component_system/tlocMesh.cpp 
  component_system/tlocMesh.h 
  component_system/tlocMeshRenderSystem.cpp 
  component_system/tlocMeshRenderSystem.h 
  component_system/tlocPrefabMaterial.h 
  component_system/tlocPrimitive.cpp 
  component_system/tlocPrimitive.h 
  component_system/tlocProjectionComponent.cpp 
  component_system/tlocProjectionComponent.h 
  component_system/tlocQuad.cpp 
  component_system/tlocQuad.h 
  component_system/tlocQuadRenderSystem.cpp 
  component_system/tlocQuadRenderSystem.h 
  component_system/tloc_component_system.cpp 
  component_system/tloc_component_system.h 
  component_system/tloc_component_system.inl
  )

set(TLOC_GRAPHICS_ERROR 
  error/tlocErrorTypes.h 
  error/tloc_error.cpp 
  error/tloc_error.h 
  error/tloc_error.inl
  )

set(TLOC_GRAPHICS_MEDIA 
  media/tlocImage.cpp 
  media/tlocImage.h 
  media/tlocImageLoader.cpp 
  media/tlocImageLoader.h 
  media/tloc_media.cpp 
  media/tloc_media.h 
  media/tloc_media.inl
  )

set(TLOC_GRAPHICS_OPENGL 
  opengl/tlocAttribute.cpp 
  opengl/tlocAttribute.h 
  opengl/tlocError.cpp 
  opengl/tlocError.h 
  opengl/tlocObject.cpp 
  opengl/tlocObject.h 
  opengl/tlocOpenGL.cpp 
  opengl/tlocOpenGL.h 
  opengl/tlocOpenGLExt.cpp 
  opengl/tlocOpenGLExt.h 
  opengl/tlocShader.cpp 
  opengl/tlocShader.h 
  opengl/tlocShaderOperator.cpp 
  opengl/tlocShaderOperator.h 
  opengl/tlocShaderProgram.cpp 
  opengl/tlocShaderProgram.h 
  opengl/tlocShaderVariable.cpp 
  opengl/tlocShaderVariable.h 
  opengl/tlocShaderVariableExplicitMacros.h 
  opengl/tlocShaderVariableInfo.cpp 
  opengl/tlocShaderVariableInfo.h 
  opengl/tlocTextureObject.cpp 
  opengl/tlocTextureObject.h 
  opengl/tlocUniform.cpp 
  opengl/tlocUniform.h 
  opengl/tlocUniformExplicitMacros.h 
  opengl/tloc_opengl.cpp 
  opengl/tloc_opengl.h 
  opengl/tloc_opengl.inl
  )

set(TLOC_GRAPHICS_RENDERER 
  renderer/tlocRenderer.cpp 
  renderer/tlocRenderer.h 
  renderer/tloc_renderer.cpp 
  renderer/tloc_renderer.h 
  renderer/tloc_renderer.inl
  )

set(TLOC_GRAPHICS_TYPES 
  types/tlocAspectRatio.cpp 
  types/tlocAspectRatio.h 
  types/tlocColor.cpp 
  types/tlocColor.h 
  types/tlocDimension.h 
  types/tlocFOV.cpp 
  types/tlocFOV.h 
  types/tlocVertex.h 
  types/tloc_types.cpp 
  types/tloc_types.h 
  types/tloc_types.inl
  )

set(TLOC_GRAPHICS_VIEW_PROJECTION 
  view_projection/tlocCamera.cpp 
  view_projection/tlocCamera.h 
  view_projection/tlocFrustum.cpp 
  view_projection/tlocFrustum.h 
  view_projection/tloc_view_projection.cpp 
  view_projection/tloc_view_projection.h 
  view_projection/tloc_view_projection.inl
  )

set(TLOC_GRAPHICS_WINDOW 
  window/tlocContext.cpp 
  window/tlocContext.h 
  window/tlocGraphicsContext.h 
  window/tlocGraphicsModes.cpp 
  window/tlocGraphicsModes.h 
  window/tlocWindow.cpp 
  window/tlocWindow.h 
  window/tlocWindow.inl 
  window/tlocWindowHandle.h 
  window/tlocWindowImpl.h 
  window/tlocWindowSettings.h 
  window/tloc_window.cpp 
  window/tloc_window.h 
  window/tloc_window.inl
  )

#-------------------------------------------
# Platform specific files

# IOS
if(APPLE)
  set(TLOC_GRAPHICS_APPLICATION 
    ${TLOC_GRAPHICS_APPLICATION}
    application/tlocAppDelegateIphone.h 
    application/tlocAppDelegateIphone.mm 
    )

  set(TLOC_GRAPHICS_WINDOW
    ${TLOC_GRAPHICS_WINDOW}
    window/tlocOpenGLViewControllerIphone.h 
    window/tlocOpenGLViewControllerIphone.mm 
    window/tlocOpenGLViewIphone.h 
    window/tlocOpenGLViewIphone.mm 
    window/tlocWindowImplIphone.h 
    window/tlocWindowImplIphone.mm 
    )
endif()

# Windows
if(WIN32)
  set(TLOC_GRAPHICS_WINDOW
    ${TLOC_GRAPHICS_WINDOW}
    window/tlocWindowImplWin.cpp 
    window/tlocWindowImplWin.h 
    )
endif()

#-------------------------------------------
# Project setup

add_definitions(-DGLEW_STATIC)

include_directories(
  ${TLOC_PATH}/src/3rdParty/Graphics/GLEW/
  ${TLOC_PATH}/src/3rdParty/Graphics/glext/
)

add_library(tlocGraphics STATIC
  ${TLOC_GRAPHICS}
  ${TLOC_GRAPHICS_APPLICATION}
  ${TLOC_GRAPHICS_COMPONENT_SYSTEM}
  ${TLOC_GRAPHICS_ERROR}
  ${TLOC_GRAPHICS_MEDIA}
  ${TLOC_GRAPHICS_OPENGL}
  ${TLOC_GRAPHICS_RENDERER}
  ${TLOC_GRAPHICS_TYPES}
  ${TLOC_GRAPHICS_VIEW_PROJECTION}
  ${TLOC_GRAPHICS_WINDOW}
  ${TLOC_GRAPHICS_3RD_PARTY_COMPRESSION}
  ${TLOC_GRAPHICS_3RD_PARTY_GLEW}
  ${TLOC_GRAPHICS_3RD_PARTY_GLEXT}
  ${TLOC_GRAPHICS_3RD_PARTY_IMAGES_PNG}
  )

# Filters to organize the source files
source_group(application      FILES ${TLOC_GRAPHICS_APPLICATION})
source_group(component_system FILES ${TLOC_GRAPHICS_COMPONENT_SYSTEM})
source_group(error            FILES ${TLOC_GRAPHICS_ERROR})
source_group(media            FILES ${TLOC_GRAPHICS_MEDIA})
source_group(opengl           FILES ${TLOC_GRAPHICS_OPENGL})
source_group(renderer         FILES ${TLOC_GRAPHICS_RENDERER})
source_group(types            FILES ${TLOC_GRAPHICS_TYPES})
source_group(view_projection  FILES ${TLOC_GRAPHICS_VIEW_PROJECTION})
source_group(window           FILES ${TLOC_GRAPHICS_WINDOW})

source_group(3rd_party/compression    FILES ${TLOC_GRAPHICS_3RD_PARTY_COMPRESSION})
source_group(3rd_party/glew           FILES ${TLOC_GRAPHICS_3RD_PARTY_GLEW})
source_group(3rd_party/glext          FILES ${TLOC_GRAPHICS_3RD_PARTY_GLEXT})
source_group(3rd_party/images/lodepng FILES ${TLOC_GRAPHICS_3RD_PARTY_IMAGES_PNG})

