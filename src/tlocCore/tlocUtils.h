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

};};


#endif