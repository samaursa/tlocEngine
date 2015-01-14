#ifndef TLOC_CORE_IO_PATH_H
#define TLOC_CORE_IO_PATH_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/memory/tlocBufferArg.h>

namespace tloc { namespace core { namespace io {

  class Path
  {
  public:
    typedef Path                  this_type;
    typedef string::String        string_type;

  public:
    Path(const BufferArg& a_path);

    const this_type& GetFileName(string_type& a_out) const;
    const this_type& GetFileNameWithoutExtension(string_type& a_out) const;
    const this_type& GetExtension(string_type& a_out) const;
    const this_type& GetPathWithoutFileName(string_type& a_out) const;

    string_type GetFileName() const;
    string_type GetFileNameWithoutExtension() const;
    string_type GetExtension() const;
    string_type GetPathWithoutFileName() const;

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

    TLOC_DECL_AND_DEF_GETTER(const char*, GetPath, m_path.c_str());
    this_type& SetPath(const BufferArg& a_path);

    bool operator==(const this_type& a_other) const;
    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

  private:
    void DoFixPath();

    string_type m_path;
  };

};};};

#include <tlocCore/logging/tlocLog.h>

namespace tloc { namespace core { 

  namespace logging {

    template <typename T_Logger, typename T_BuildConfig>
    Log_T<T_Logger, T_BuildConfig>&
      operator << (Log_T<T_Logger, T_BuildConfig>& a_log,
                   const core_io::Path& a_path)
    {
      if (a_path.HasFilename())
      {
        a_log << a_path.GetFileName() << "(" 
          << a_path.GetPathWithoutFileName() << ")";
      }
      else
      {
        a_log << a_path.GetPath();
      }
      return a_log;
    }

  };

};};

#endif