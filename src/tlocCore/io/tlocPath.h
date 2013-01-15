#ifndef TLOC_CORE_IO_PATH_H
#define TLOC_CORE_IO_PATH_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace core { namespace io {

  class Path
  {
  public:
    typedef string::String        string_type;

  public:
    Path(const char* a_path);

    void GetFileName(string_type& a_out) const;
    void GetFileNameWithoutExtension(string_type& a_out) const;
    void GetExtension(string_type& a_out) const;
    void GetPathWithoutFileName(string_type& a_out) const;

    ///-------------------------------------------------------------------------
    /// @brief Queries if the file in the path exists.
    ///
    /// @return ascii, binary or none if the file does not exist
    ///-------------------------------------------------------------------------
    bool FileExists() const;

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

  private:
    void DoFixPath();

    string_type m_path;
  };

};};};

#endif