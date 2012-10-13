#ifndef TLOC_GL_OBJECT_H
#define TLOC_GL_OBJECT_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/string/tlocString.h>

#include <tlocCore/base_classes/tlocNonCopyable.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_object
  {
    struct OnlyID{};
    struct WithError{};
  };

  class ObjectBase : public core::NonCopyable
  {
  public:
    typedef u32 object_handle;

    ObjectBase();

    bool IsValid();

    TLOC_DECL_AND_DEF_GETTER(object_handle, GetHandle, m_handle);
    TLOC_DECL_AND_DEF_SETTER(object_handle, SetHandle, m_handle);

  private:

    object_handle m_handle;
  };

  template <typename T_Policy = p_object::OnlyID >
  class Object_T : public ObjectBase
  {
  public:
    typedef ObjectBase                  base_type;
    typedef base_type::object_handle    object_handle;
  };

  template<>
  class Object_T<p_object::WithError> : public ObjectBase
  {
  public:
    typedef ObjectBase                  base_type;
    typedef base_type::object_handle    object_handle;
    typedef core::String                string_type;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetError, m_error);

  protected:
    TLOC_DECL_AND_DEF_GETTER_DIRECT(string_type, DoGetError, m_error);

  private:
    string_type m_error;
  };

  //------------------------------------------------------------------------
  // Typedefs

  typedef Object_T<>        Object;

};};};

#endif