set(TLOC_MATH
  tlocDepVersionCheck.cpp 
  tlocMath.cpp 
  tlocMath.h 
  tlocMath.inl 
  tlocMathBase.h 
  tlocMathExplicitMacros.h 
  tloc_math.cpp 
  tloc_math.h 
  tloc_math.inl
  )

set(TLOC_MATH_COMPONENT_SYSTEM 
  component_system/tlocComponentType.h 
  component_system/tlocTransform.cpp 
  component_system/tlocTransform.h 
  component_system/tloc_component_system.cpp 
  component_system/tloc_component_system.h 
  component_system/tloc_component_system.inl
  )

set(TLOC_MATH_TYPES 
  types/tlocAngle.cpp 
  types/tlocAngle.h 
  types/tlocAngle.inl 
  types/tlocAngleExplicitMacros.h 
  types/tlocCircle.cpp 
  types/tlocCircle.h 
  types/tlocMatrix.cpp 
  types/tlocMatrix.h 
  types/tlocMatrix.inl 
  types/tlocMatrix2.cpp 
  types/tlocMatrix2.h 
  types/tlocMatrix2.inl 
  types/tlocMatrix3.cpp 
  types/tlocMatrix3.h 
  types/tlocMatrix3.inl 
  types/tlocMatrix4.cpp 
  types/tlocMatrix4.h 
  types/tlocMatrix4.inl 
  types/tlocMatrixExplicitMacros.h 
  types/tlocRectangle.cpp 
  types/tlocRectangle.h 
  types/tlocVector.cpp 
  types/tlocVector.h 
  types/tlocVector.inl 
  types/tlocVector2.cpp 
  types/tlocVector2.h 
  types/tlocVector2.inl 
  types/tlocVector3.cpp 
  types/tlocVector3.h 
  types/tlocVector3.inl 
  types/tlocVector4.cpp 
  types/tlocVector4.h 
  types/tlocVector4.inl 
  types/tlocVectorExplicitMacros.h 
  types/tloc_matrix.cpp 
  types/tloc_matrix.h 
  types/tloc_matrix.inl 
  types/tloc_types.cpp 
  types/tloc_types.h 
  types/tloc_types.inl 
  types/tloc_vector.cpp 
  types/tloc_vector.h 
  types/tloc_vector.inl 
  )

set(TLOC_MATH_UTILITIES 
  utilities/tlocPythagoras.cpp 
  utilities/tlocPythagoras.h 
  utilities/tloc_utilities.cpp 
  utilities/tloc_utilities.h 
  utilities/tloc_utilities.inl
  )

#-------------------------------------------
# Project setup

add_library(tlocMath STATIC
  ${TLOC_MATH}
  ${TLOC_MATH_COMPONENT_SYSTEM}
  ${TLOC_MATH_TYPES}
  ${TLOC_MATH_UTILITIES}
  )

# Add to the list of all libraries
list(APPEND tlocAllLibraries tlocMath)

# Filters to organize the source files
source_group(component_system FILES ${TLOC_MATH_COMPONENT_SYSTEM})
source_group(types            FILES ${TLOC_MATH_TYPES})
source_group(utilities        FILES ${TLOC_MATH_UTILITIES})
