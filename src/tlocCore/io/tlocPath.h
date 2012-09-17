#ifndef TLOC_CORE_IO_PATH_H
#define TLOC_CORE_IO_PATH_H

#include <tlocCore/string/tlocString.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace core { namespace io {

  class Path
  {
  public:
    Path(const char* a_path);

    void GetFileName(String& a_out) const;
    void GetFileNameWithoutExtension(String& a_out) const;
    void GetExtension(String& a_out) const;
    void GetPathWithoutFileName(String& a_out) const;
    void GetAbsolutePath(String& a_out) const;

    bool        Exists() const;

    TLOC_DECL_AND_DEF_GETTER(char*, GetPath, m_path.c_str());
    void SetPath(const char* a_path);

    //const char* GetPath() const;

  private:
    void DoFixPath();

    String m_path;
  };

};};};

#endif