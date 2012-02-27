#ifndef TLOC_UTILS_H
#define TLOC_UTILS_H

namespace tloc { namespace core {

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


};};


#endif