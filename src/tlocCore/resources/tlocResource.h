#ifndef _TLOC_CORE_RESOURCES_RESOURCE_H_
#define _TLOC_CORE_RESOURCES_RESOURCE_H_

#include <tlocCore/tlocFunctional.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/io/tlocPath.h>
#include <tlocCore/tlocUCID.h>

namespace tloc { namespace core { namespace resources {

  // ///////////////////////////////////////////////////////////////////////
  // Resource_I

  class Resource_I
  {
  public:
    typedef Resource_I                          this_type;
    typedef tl_size                             hash_type;
    typedef core_io::Path                       path_type;
    typedef core::UCID<this_type>::id_type      ucid_type;

  protected:

    bool operator==(const this_type& a_other) const;

    TLOC_DECL_AND_DEF_GETTER(ucid_type, GetUCID, m_ucid);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(path_type, GetPath, m_path);

  protected:
    template <typename T>
    Resource_I(path_type a_path);

    ~Resource_I();

  private:
    ucid_type               m_ucid;
    path_type               m_path;

  };

};};};

#endif