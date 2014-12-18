# -----------------------------------------------------------------------------
# CACHE variables added to any project that includes this file
# INACTIVE for now

#set(TLOCLIBRARY_CORE      ON CACHE BOOL "Core library")
#set(TLOCLIBRARY_MATH      ON CACHE BOOL "Math library")
#set(TLOCLIBRARY_GRAPHICS  ON CACHE BOOL "Graphics library")
#set(TLOCLIBRARY_INPUT     ON CACHE BOOL "Input library")
#set(TLOCLIBRARY_ANIMATION ON CACHE BOOL "Animation library")
#set(TLOCLIBRARY_PHYSICS   ON CACHE BOOL "Physics library")
#set(TLOCLIBRARY_PREFAB    ON CACHE BOOL "Physics library")

set(TLOC_LIBRARIES
  3rdParty
  tlocCore
  tlocMath
  tlocGraphics
  tlocInput
  tlocPhysics
  tlocAnimation
  tlocPrefab
  )

set(TLOC_DEP_INCLUDE_DIRECTORIES
  ${TLOC_DEP_INSTALL_PATH}/include/
  ${TLOC_DEP_INSTALL_PATH}/include/Box2D/
  ${TLOC_DEP_INSTALL_PATH}/include/CATCH/
  )

set(TLOC_ENGINE_INCLUDE_DIRECTORIES
  ${TLOC_ENGINE_INSTALL_PATH}/include/
  )

set(TLOC_INCLUDE_DIRECTORIES
  ${TLOC_DEP_INCLUDE_DIRECTORIES}
  ${TLOC_ENGINE_INCLUDE_DIRECTORIES}
  )

set(TLOC_DEP_LINK_DIRECTORIES
  ${TLOC_DEP_INSTALL_PATH}/lib/
  )

set(TLOC_ENGINE_LINK_DIRECTORIES
  ${TLOC_ENGINE_INSTALL_PATH}/lib/
  )

set(TLOC_LINK_DIRECTORIES
  ${TLOC_DEP_LINK_DIRECTORIES}
  ${TLOC_ENGINE_LINK_DIRECTORIES}
  )
