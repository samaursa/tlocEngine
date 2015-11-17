#ifndef TLOC_CORE_IO_PATH_H
#define TLOC_CORE_IO_PATH_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/memory/tlocBufferArg.h>

namespace tloc { namespace core { namespace io {

  class path
  {
  public:
    typedef path                  this_type;
    typedef std::string           string_type;

  public:
    path(const buffer_arg& a_path);

    const this_type& get_file_name(string_type& a_out) const;
    const this_type& get_file_name_without_extension(string_type& a_out) const;
    const this_type& get_extension(string_type& a_out) const;
    const this_type& get_path_without_file_name(string_type& a_out) const;

    string_type get_file_name() const;
    string_type get_file_name_without_extension() const;
    string_type get_extension() const;
    string_type get_path_without_file_name() const;

    bool file_exists() const;
    bool folder_exists() const;
    bool has_file_name() const;

    TLOC_DECL_AND_DEF_GETTER(const char*, get_path, m_path.c_str());
    this_type& set_path(const buffer_arg& a_path);

    bool operator==(const this_type& a_other) const;
    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

  private:
    void do_fix_path();

    string_type m_path;
  };

};};};

#include <tlocCore/logging/tlocLog.h>

namespace tloc { namespace core { 

  namespace logging {

    template <typename T_Logger, typename T_BuildConfig>
    const Log_T<T_Logger, T_BuildConfig>&
      operator << (const Log_T<T_Logger, T_BuildConfig>& a_log,
                   const core_io::path& a_path)
    {
      if (a_path.has_file_name())
      {
        a_log << a_path.get_file_name() << "(" 
          << a_path.get_path_without_file_name() << ")";
      }
      else
      {
        a_log << a_path.get_path();
      }
      return a_log;
    }

  };

};};

#endif