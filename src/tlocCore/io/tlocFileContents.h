#ifndef _TLOC_CORE_IO_FILE_CONTENTS_H_
#define _TLOC_CORE_IO_FILE_CONTENTS_H_

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/io/tlocPath.h>
#include <tlocCore/string/tlocString.h>

namespace tloc { namespace core { namespace io {

  class FileContents
  {
  public:
    typedef core_str::String                        string_type;
    typedef core_io::Path                           path_type;
    typedef FileContents                            this_type;

  public:
    FileContents();
    FileContents(const path_type& a_path, const string_type& a_string);
    FileContents(this_type&& a_temp);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(path_type, GetPath, m_path);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetContents, m_fileContents);

  private:
    path_type     m_path;
    string_type   m_fileContents;
  };

};};};

#endif