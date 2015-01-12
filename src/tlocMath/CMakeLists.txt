set(TLOC_MATH
  tlocDepVersionCheck.cpp 
  tlocMath.cpp 
  tlocMath.h 
  tlocMath.inl.h 
  tlocMathBase.h 
  tlocMathBase.cpp
  tlocMathExplicitMacros.h 
  tloc_math.cpp 
  tloc_math.h 
  tloc_math.inl.h
  tloc_math.opt.inl.h
  tlocRange.h
  tlocRange.inl.h
  tlocRange.cpp
  tlocBounds.h
  tlocBounds.cpp
  )

set(TLOC_MATH_STATISTICS
  statistics/tloc_statistics.h
  statistics/tloc_statistics.inl.h
  statistics/tloc_statistics.cpp
  statistics/tlocStatFunction.h
  statistics/tlocStatFunction.inl.h
  statistics/tlocStatFunction.cpp
)

set(TLOC_MATH_COMPONENT_SYSTEM 
  component_system/tlocComponentType.h 
  component_system/tlocProjectionComponent.cpp 
  component_system/tlocProjectionComponent.h 
  component_system/tlocTransform.cpp 
  component_system/tlocTransform.h 
  component_system/tloc_component_system.cpp 
  component_system/tloc_component_system.h 
  component_system/tloc_component_system.inl.h
  )

set(TLOC_MATH_OPTIMIZE
  optimize/tloc_optimize.h
  optimize/tloc_optimize.inl.h
  optimize/tloc_optimize.cpp
  optimize/tlocBinPacker2D.h
  optimize/tlocBinPacker2D.cpp
)

set(TLOC_MATH_TYPES 
  types/tlocAngle.cpp 
  types/tlocAngle.h 
  types/tlocAngle.opt.inl.h 
  types/tlocAspectRatio.cpp 
  types/tlocAspectRatio.h 
  types/tlocCircle.cpp 
  types/tlocCircle.h
  types/tlocCuboid.h
  types/tlocCuboid.cpp
  types/tlocFOV.h
  types/tlocFOV.cpp
  types/tlocMatrix.cpp 
  types/tlocMatrix.h 
  types/tlocMatrix.opt.inl.h 
  types/tlocMatrix2.cpp 
  types/tlocMatrix2.h 
  types/tlocMatrix2.opt.inl.h 
  types/tlocMatrix3.cpp 
  types/tlocMatrix3.h 
  types/tlocMatrix3.opt.inl.h 
  types/tlocMatrix4.cpp 
  types/tlocMatrix4.h 
  types/tlocMatrix4.opt.inl.h 
  types/tlocRay.h
  types/tlocRay.cpp
  types/tlocRectangle.cpp 
  types/tlocRectangle.h 
  types/tlocVector.cpp 
  types/tlocVector.h 
  types/tlocVector.opt.inl.h 
  types/tlocVector2.cpp 
  types/tlocVector2.h 
  types/tlocVector2.opt.inl.h 
  types/tlocVector3.cpp 
  types/tlocVector3.h 
  types/tlocVector3.opt.inl.h 
  types/tlocVector4.cpp 
  types/tlocVector4.h 
  types/tlocVector4.opt.inl.h 
  types/tloc_matrix.cpp 
  types/tloc_matrix.h 
  types/tloc_matrix.inl.h 
  types/tloc_matrix.opt.inl.h 
  types/tloc_types.cpp 
  types/tloc_types.h 
  types/tloc_types.inl.h 
  types/tloc_types.opt.inl.h 
  types/tloc_vector.cpp 
  types/tloc_vector.h 
  types/tloc_vector.inl.h 
  types/tloc_vector.opt.inl.h 
  )

set(TLOC_MATH_UTILITIES 
  utilities/tlocPythagoras.cpp 
  utilities/tlocPythagoras.h 
  utilities/tlocScale.h
  utilities/tlocScale.cpp
  utilities/tloc_utilities.cpp 
  utilities/tloc_utilities.h 
  utilities/tloc_utilities.inl.h
  )

set(TLOC_MATH_PROJECTION
  projection/tloc_projection.h
  projection/tloc_projection.inl.h
  projection/tloc_projection.cpp
  projection/tlocFrustum.h
  projection/tlocFrustum.cpp
  )


#-------------------------------------------
# Project setup

add_library(tlocMath STATIC
  ${TLOC_MATH}
  ${TLOC_MATH_COMPONENT_SYSTEM}
  ${TLOC_MATH_STATISTICS}
  ${TLOC_MATH_OPTIMIZE}
  ${TLOC_MATH_TYPES}
  ${TLOC_MATH_UTILITIES}
  ${TLOC_MATH_PROJECTION}
  )

add_dependencies(tlocMath
  tlocCore
  )

set_platform_specific_properties(tlocMath)

# Filters to organize the source files
source_group(component_system FILES ${TLOC_MATH_COMPONENT_SYSTEM})
source_group(statistics       FILES ${TLOC_MATH_STATISTICS})
source_group(optimize         FILES ${TLOC_MATH_OPTIMIZE})
source_group(types            FILES ${TLOC_MATH_TYPES})
source_group(utilities        FILES ${TLOC_MATH_UTILITIES})
source_group(projection       FILES ${TLOC_MATH_PROJECTION})

tloc_install_library(tlocMath "")
