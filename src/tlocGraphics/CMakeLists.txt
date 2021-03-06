set(TLOC_GRAPHICS 
  tlocRtt.h
  tlocRtt.cpp
  tlocDepVersionCheck.cpp 
  tlocGraphicsBase.h 
  tlocGraphicsBase.cpp
  tloc_graphics.cpp 
  tloc_graphics.h 
  tloc_graphics.inl.h 
  )

set(3RD_PARTY_PATH ${SOLUTION_PATH}/src/3rdParty/Graphics/)
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

set(TLOC_GRAPHICS_3RD_PARTY_IMAGES_JPEG
    ${3RD_PARTY_PATH}/nanojpeg/ujpeg.h
    ${3RD_PARTY_PATH}/nanojpeg/ujpeg.c
    )

set(TLOC_GRAPHICS_APPLICATION 
  )

set(TLOC_GRAPHICS_COMPONENT_SYSTEM
  component_system/tlocArcBall.h
  component_system/tlocArcBall.cpp
  component_system/tlocArcBallSystem.h
  component_system/tlocArcBallSystem.cpp
  component_system/tlocBoundingBox.h
  component_system/tlocBoundingBox.cpp
  component_system/tlocBoundingBoxSystem.h
  component_system/tlocBoundingBoxSystem.cpp
  component_system/tlocBoundingBoxRenderSystem.h
  component_system/tlocBoundingBoxRenderSystem.cpp
  component_system/tlocCamera.h
  component_system/tlocCamera.cpp
  component_system/tlocCameraSystem.h
  component_system/tlocCameraSystem.cpp
  component_system/tlocComponentType.h 
  component_system/tlocDebugTransformRenderSystem.h 
  component_system/tlocDebugTransformRenderSystem.cpp
  component_system/tlocDynamicText.h
  component_system/tlocDynamicText.cpp
  component_system/tlocDynamicTextRenderSystem.h
  component_system/tlocDynamicTextRenderSystem.cpp
  component_system/tlocFan.cpp 
  component_system/tlocFan.h 
  component_system/tlocMaterial.cpp 
  component_system/tlocMaterial.h 
  component_system/tlocMaterialSystem.cpp 
  component_system/tlocMaterialSystem.h 
  component_system/tlocMesh.cpp 
  component_system/tlocMesh.h 
  component_system/tlocMeshRenderSystem.cpp 
  component_system/tlocMeshRenderSystem.h 
  component_system/tlocSceneNode.h
  component_system/tlocSceneNode.cpp
  component_system/tlocPrimitive.cpp 
  component_system/tlocPrimitive.h 
  component_system/tlocRaypick.h
  component_system/tlocRaypick.cpp
  component_system/tlocRaypickSystem.h
  component_system/tlocRaypickSystem.cpp
  component_system/tlocRenderSystem.h
  component_system/tlocRenderSystem.cpp
  component_system/tlocRenderSystem_I.h
  component_system/tlocRenderSystem_I.cpp
  component_system/tlocRenderable_TI.h
  component_system/tlocRenderable_TI.cpp
  component_system/tlocSceneGraphSystem.h
  component_system/tlocSceneGraphSystem.cpp
  component_system/tlocSkyBox.h
  component_system/tlocSkyBox.cpp
  component_system/tlocSkyBoxRenderSystem.h
  component_system/tlocSkyBoxRenderSystem.cpp
  component_system/tlocStaticText.h
  component_system/tlocStaticText.cpp
  component_system/tlocStaticTextRenderSystem.h
  component_system/tlocStaticTextRenderSystem.cpp
  component_system/tlocText_I.h
  component_system/tlocText_I.cpp
  component_system/tlocTextAlignment.h
  component_system/tlocTextRenderSystem_TI.h
  component_system/tlocTextRenderSystem_TI.cpp
  component_system/tlocTextureAnimator.h
  component_system/tlocTextureAnimator.cpp
  component_system/tlocTextureAnimatorSystem.h
  component_system/tlocTextureAnimatorSystem.cpp
  component_system/tlocTextureCoords.h
  component_system/tlocTextureCoords.cpp
  component_system/tlocQuad.cpp 
  component_system/tlocQuad.h 
  component_system/tloc_component_system.cpp 
  component_system/tloc_component_system.h 
  component_system/tloc_component_system.inl.h
  )

set(TLOC_GRAPHICS_ERROR 
  error/tlocErrorTypes.h 
  error/tloc_error.cpp 
  error/tloc_error.h 
  error/tloc_error.inl.h
  )

set(TLOC_GRAPHICS_MEDIA 
  media/tloc_media.cpp 
  media/tloc_media.h 
  media/tloc_media.inl.h
  media/tlocFont.h
  media/tlocFont.cpp
  media/tlocFontSize.h
  media/tlocFontSize.cpp
  media/tlocFreeType.h
  media/tlocFreeType.cpp
  media/tlocGlyph.h
  media/tlocGlyph.cpp
  media/tlocImage.cpp 
  media/tlocImage.h 
  media/tlocImageLoader.cpp 
  media/tlocImageLoader.h 
  media/tlocObjLoader.h
  media/tlocObjLoader.cpp
  media/tlocSprite.h
  media/tlocSprite.cpp
  media/tlocSpriteInfo.h
  media/tlocSpriteInfo.cpp
  media/tlocSpriteLoader.h
  media/tlocSpriteLoader.cpp
  )

set(TLOC_GRAPHICS_OPENGL 
  opengl/tlocAttributeVBO.cpp 
  opengl/tlocAttributeVBO.h 
  opengl/tlocError.cpp 
  opengl/tlocError.h 
  opengl/tlocFramebufferObject.h
  opengl/tlocFramebufferObject.cpp
  opengl/tlocGLTypes.h
  opengl/tlocGLTypes.cpp
  opengl/tlocObject.cpp 
  opengl/tlocObject.h 
  opengl/tlocOpenGL.cpp 
  opengl/tlocOpenGL.h 
  opengl/tlocOpenGLIncludes.h
  opengl/tlocRenderbufferObject.h
  opengl/tlocRenderbufferObject.cpp
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
  opengl/tlocVertexArrayObject.h
  opengl/tlocVertexArrayObject.cpp
  opengl/tlocVertexBufferObject.h
  opengl/tlocVertexBufferObject.cpp
  opengl/tloc_opengl.cpp 
  opengl/tloc_opengl.h 
  opengl/tloc_opengl.inl.h
  )

if(WIN32)
  set(TLOC_GRAPHICS_OPENGL
    ${TLOC_GRAPHICS_OPENGL} 
    opengl/tlocOpenGLExt.cpp 
    opengl/tlocOpenGLExt.h 
    )
endif()

set(TLOC_GRAPHICS_RENDERER 
  renderer/tlocRenderer.cpp 
  renderer/tlocRenderer.h 
  renderer/tlocDrawCommand.h
  renderer/tlocDrawCommand.cpp
  renderer/tloc_renderer.cpp 
  renderer/tloc_renderer.h 
  renderer/tloc_renderer.inl.h
  )

set(TLOC_GRAPHICS_TYPES 
  types/tlocColor.cpp 
  types/tlocColor.h 
  types/tlocDimension.h 
  types/tlocVertex.h 
  types/tlocVertex.cpp
  types/tloc_types.cpp 
  types/tloc_types.h 
  types/tloc_types.inl.h
  )

set(TLOC_GRAPHICS_VIEW_PROJECTION 
  )

set(TLOC_GRAPHICS_WINDOW 
  window/tlocContext.cpp 
  window/tlocContext.h 
  window/tlocGraphicsContext.h 
  window/tlocGraphicsModes.cpp 
  window/tlocGraphicsModes.h 
  window/tlocWindow.cpp 
  window/tlocWindow.h 
  window/tlocWindow.inl.h 
  window/tlocWindowHandle.h 
  window/tlocWindowImpl.h 
  window/tlocWindowSettings.h 
  window/tlocWindowSettings.cpp
  window/tloc_window.cpp 
  window/tloc_window.h 
  window/tloc_window.inl.h
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
  ${TLOC_DEP_INSTALL_PATH}/include/FreeType/
  ${TLOC_ENGINE_PATH}/src/3rdParty/Graphics/GLEW/
  ${TLOC_ENGINE_PATH}/src/3rdParty/Graphics/glext/
)

tloc_add_definitions_strict()
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
  ${TLOC_GRAPHICS_3RD_PARTY_IMAGES_JPEG}
  )

add_dependencies(tlocGraphics
  3rdParty
  tlocCore
  tlocMath
  )

set_platform_specific_properties(tlocGraphics)

# Filters to organize the source files
source_group(application      FILES ${TLOC_GRAPHICS_APPLICATION})
source_group(component_system FILES ${TLOC_GRAPHICS_COMPONENT_SYSTEM})
source_group(error            FILES ${TLOC_GRAPHICS_ERROR})
source_group(media            FILES ${TLOC_GRAPHICS_MEDIA})
source_group(opengl           FILES ${TLOC_GRAPHICS_OPENGL})
source_group(renderer         FILES ${TLOC_GRAPHICS_RENDERER})
source_group(types            FILES ${TLOC_GRAPHICS_TYPES})
source_group(view             FILES ${TLOC_GRAPHICS_VIEW_PROJECTION})
source_group(window           FILES ${TLOC_GRAPHICS_WINDOW})

source_group(3rd_party/compression      FILES ${TLOC_GRAPHICS_3RD_PARTY_COMPRESSION})
source_group(3rd_party/glew             FILES ${TLOC_GRAPHICS_3RD_PARTY_GLEW})
source_group(3rd_party/glext            FILES ${TLOC_GRAPHICS_3RD_PARTY_GLEXT})
source_group(3rd_party/images/lodepng   FILES ${TLOC_GRAPHICS_3RD_PARTY_IMAGES_PNG})
source_group(3rd_party/images/nanojpeg  FILES ${TLOC_GRAPHICS_3RD_PARTY_IMAGES_JPEG})

tloc_install_library(tlocGraphics "")
