#ifndef TLOC_UTILS_H
#define TLOC_UTILS_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypeTraits.h>

namespace tloc { namespace core { namespace utils {

  //------------------------------------------------------------------------
  // Nested functions

#define TL_NESTED_FUNC_BEGIN(funcName) struct funcName ## _nestedFunctionClass { static
#define TL_NESTED_FUNC_END() }
#define TL_NESTED_CALL(funcName) funcName ##  _nestedFunctionClass:: funcName

  ///-----------------------------------------------------------------------------
  /// Used to prevent a struct or class from being initialized by declaring a
  /// constructor with a static assert.
  ///
  /// @param  helper_name Name of the helper.
  ///-----------------------------------------------------------------------------
#define DECL_TYPEDEF_HELPER(helper_name) helper_name() { \
  TLOC_STATIC_ASSERT(false, \
  Cannot_instantiate_typedef_helper_USE_typedef_type_declared_in_helper); }

  ///-------------------------------------------------------------------------
  /// Used to avoid code duplication for operators. Requires definition of
  /// operators == and <
  ///
  /// @param object The type itself
  ///-------------------------------------------------------------------------
#define TLOC_DECLARE_OPERATORS(object) \
  bool operator !=(const object& a_other) const { return !(operator==(a_other)); }\
  bool operator > (const object& a_other) const { return a_other.operator<(*this); }\
  bool operator <=(const object& a_other) const { return !(operator>(a_other)); }\
  bool operator >=(const object& a_other) const { return !(operator<(a_other)); }


  ///-------------------------------------------------------------------------
  /// These macros allow you to declare getters and setters quickly. Note that in
  /// this engine member variables should not be accessed directly, even by the
  /// host class itself.
  /// Reason1: to maintain consistency
  /// Reason2: to allow devs to debug get/set operations
  ///
  /// The following macros make it easier/quicker to declare and define getters
  /// and setters. The problem ofcourse is that we cannot break into macros. This
  /// is why only declarations are also provided which can be defined immediately
  /// or later by the developer to allow breaking into the getter/setter.

  //------------------------------------------------------------------------
  // Getters

#define TLOC_DECL_GETTER(_type_, _name_)\
  _type_        _name_()
#define TLOC_DECL_GETTER_CONST(_type_, _name_)\
  const _type_  _name_() const
#define TLOC_DECL_GETTER_DIRECT(_type_, _name_)\
  _type_&       _name_()
#define TLOC_DECL_GETTER_CONST_DIRECT(_type_, _name_)\
  _type_ const & _name_() const

#define TLOC_DECL_AND_DEF_GETTER(_type_, _name_, _var_)\
  TLOC_DECL_GETTER(_type_, _name_) { return _var_; }
#define TLOC_DECL_AND_DEF_GETTER_CONST(_type_, _name_, _var_)\
  TLOC_DECL_GETTER_CONST(_type_, _name_) { return (_var_); }

#define TLOC_DECL_AND_DEF_GETTER_DIRECT(_type_, _name_, _var_)\
  TLOC_DECL_GETTER_DIRECT(_type_, _name_) { return _var_; }
#define TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(_type_, _name_, _var_)\
  TLOC_DECL_GETTER_CONST_DIRECT(_type_, _name_) { return (_var_); }

#define TLOC_DECL_AND_DEF_GETTERS(_type_, _name_, _var_)\
  TLOC_DECL_AND_DEF_GETTER(_type_, _name_, _var_)\
  TLOC_DECL_AND_DEF_GETTER_CONST(_type_, _name_, _var_)

  //------------------------------------------------------------------------
  // Setters

#define TLOC_DECL_SETTER(_type_, _name_)\
  void            _name_(_type_ const & a_in)

#define TLOC_DECL_AND_DEF_SETTER(_type_, _name_, _var_)\
  TLOC_DECL_SETTER(_type_, _name_) { _var_ = a_in; }

  //------------------------------------------------------------------------
  // Expansions

#define TLOC_DECL_AND_DEF_GET_SET(_type_, _var_, _name_)\
  TLOC_DECL_AND_DEF_GETTERS(_type_, _var_, _name_);\
  TLOC_DECL_AND_DEF_SETTER(_type_, _var_, _name_)

#define TLOC_DECL_AND_DEF_GETTERS_DIRECT(_type_, _name_, _var_)\
  TLOC_DECL_AND_DEF_GETTER_DIRECT(_type_, _name_, _var_)\
  TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(_type_, _name_, _var_)

  ///-------------------------------------------------------------------------
  /// Enum counter.
  ///
  /// This class is useful to count enums that are bit shifted, where a 'count'
  /// doesn't give us the correct answer (for full usage, see tests)
  ///-------------------------------------------------------------------------
  template <int T_CountInBits, bool T_CountZero = false>
  struct EnumCounter
  {
    enum { result = 1 + EnumCounter<T_CountInBits / 2, T_CountZero>::result };
  };

  template <>
  struct EnumCounter<1, false>
  {
    enum { result = 1 };
  };

  template <>
  struct EnumCounter<1, true>
  {
    enum { result = 2 };
  };

  //------------------------------------------------------------------------
  // Enum to Index converter

  template <int T_Enum, bool T_IncludeZero = false>
  struct EnumToIndex
  {
    enum { result = 0 + EnumCounter<T_Enum / 2, T_IncludeZero>::result };
  };

  template <>
  struct EnumToIndex<1, false>
  {
    enum { result = 0 };
  };

  template <>
  struct EnumToIndex<1, true>
  {
    enum { result = 1 };
  };

};};};


#endif