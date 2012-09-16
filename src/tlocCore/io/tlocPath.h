#ifndef TLOC_CORE_IO_PATH_H
#define TLOC_CORE_IO_PATH_H

#include <tlocCore/string/tlocString.h>

namespace tloc { namespace core { namespace io {

  class Path
  {
  public:
    Path(const char* a_path);

    void GetFileName(String& a_out) const;
    void GetFileNameWithoutExtension(String& a_out) const;
    void GetExtension(String& a_out) const;
    void GetAbsolutePath(String& a_out) const;

    bool        Exists() const;
    const char* GetPath() const;

  private:
    void DoFixPath();

    String m_path;
  };

};};};

#endif