#ifndef TLOC_NESTED_FUNCTION_H
#define TLOC_NESTED_FUNCTION_H

#define TL_NESTED_FUNC_BEGIN(funcName) struct funcName ## _nestedFunctionClass { static
#define TL_NESTED_FUNC_END() }
#define TL_NESTED_CALL(funcName) funcName ## _nestedFunctionClass:: ##funcName

#endif