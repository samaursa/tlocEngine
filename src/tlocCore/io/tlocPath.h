#ifndef TLOC_CORE_IO_PATH_H
#define TLOC_CORE_IO_PATH_H

#include <tlocCore/string/tlocString.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace core { namespace io {

  class Path
  {
  public:
    enum { ascii, binary, none }; typedef tl_int  file_type;
  public:
    Path(const char* a_path);

    void GetFileName(String& a_out) const;
    void GetFileNameWithoutExtension(String& a_out) const;
    void GetExtension(String& a_out) const;
    void GetPathWithoutFileName(String& a_out) const;

    ///-------------------------------------------------------------------------
    /// @brief Queries if the file in the path exists.
    ///
    /// @return ascii, binary or none if the file does not exist
    ///-------------------------------------------------------------------------
    file_type FileExists() const;

    ///-------------------------------------------------------------------------
    /// @brief
    /// Queries if the path folder exists
    ///
    /// @note False may be returned if the folder exists but is not
    /// accessible.
    ///
    /// @return true if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------
    bool FolderExists() const;
    bool HasFilename() const;

    TLOC_DECL_AND_DEF_GETTER(char*, GetPath, m_path.c_str());
    void SetPath(const char* a_path);

    //const char* GetPath() const;

  private:
    void DoFixPath();

    String m_path;
  };

};};};

#endif