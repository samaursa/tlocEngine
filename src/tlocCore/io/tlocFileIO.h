#ifndef TLOC_FILE_IO_H
#define TLOC_FILE_IO_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/error/tlocError.h>
#include <tlocCore/io/tlocPath.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/io/tlocFileContents.h>

namespace tloc { namespace core { namespace io {

  namespace p_file_io
  {
    // Access policies
    struct read{};
    struct write{};
    struct append{};
    struct read_and_write{};
    struct read_and_write_empty{};
    struct read_and_append{};

    // File type policies
    struct ascii{};
    struct binary{};
  };

  template <typename T_AccessPolicy, typename T_FileFormat>
  class file_io_t
  {
  public:
    typedef string::String                  string_type;

    typedef T_AccessPolicy                  access_policy_type;
    typedef T_FileFormat                    file_format_type;
    typedef error::Error                    error_type;

    typedef file_io_t<access_policy_type, file_format_type>  this_type;

  public:
    file_io_t(const path& a_path);
    file_io_t(const this_type& a_other);
    ~file_io_t();

    this_type& operator=(this_type a_other);

    error_type      open();
    error_type      close();
    error_type      delete();
    error_type      write(buffer_arg a_string) const;
    error_type      write(buffer_arg a_string, tl_size a_buffSize) const;
    error_type      get_contents(string_type& a_out) const;
    error_type      get_contents(FileContents& a_out) const;
    void            swap(this_type& a_other);

    bool            is_open() const;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(path, GetPath, m_filePath);

  private:

    error_type      DoClose();

    FILE*   m_file;
    path    m_filePath;
  };

  // -----------------------------------------------------------------------
  // swap

  template <typename T_AccessPolicy, typename T_FileFormat>
  void swap(file_io_t<T_AccessPolicy, T_FileFormat>& a,
            file_io_t<T_AccessPolicy, T_FileFormat>& b)
  { a.swap(b); }

  //------------------------------------------------------------------------
  // All typedefs for our FileIO template class

  typedef file_io_t<p_file_io::read,
                 p_file_io::ascii>                  FileIO_ReadA;
  typedef file_io_t<p_file_io::append,
                 p_file_io::ascii>                  FileIO_AppendA;
  typedef file_io_t<p_file_io::write,
                 p_file_io::ascii>                  FileIO_WriteA;
  typedef file_io_t<p_file_io::read_and_write,
                 p_file_io::ascii>                  FileIO_ReadAndWriteA;
  typedef file_io_t<p_file_io::read_and_write_empty,
                 p_file_io::ascii>                  FileIO_ReadAndWriteEmptyA;
  typedef file_io_t<p_file_io::read_and_append,
                 p_file_io::ascii>                  FileIO_ReadAndAppendA;

  typedef file_io_t<p_file_io::read,
                 p_file_io::binary>                  FileIO_ReadB;
  typedef file_io_t<p_file_io::append,
                 p_file_io::binary>                  FileIO_AppendB;
  typedef file_io_t<p_file_io::write,
                 p_file_io::binary>                  FileIO_WriteB;
  typedef file_io_t<p_file_io::read_and_write,
                 p_file_io::binary>                  FileIO_ReadAndWriteB;
  typedef file_io_t<p_file_io::read_and_write_empty,
                 p_file_io::binary>                  FileIO_ReadAndWriteEmptyB;
  typedef file_io_t<p_file_io::read_and_append,
                 p_file_io::binary>                  FileIO_ReadAndAppendB;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(file_io_t<p_file_io::read TLOC_COMMA p_file_io::ascii>);
  TLOC_EXTERN_TEMPLATE_CLASS(file_io_t<p_file_io::append TLOC_COMMA p_file_io::ascii>);
  TLOC_EXTERN_TEMPLATE_CLASS(file_io_t<p_file_io::write TLOC_COMMA p_file_io::ascii>);
  TLOC_EXTERN_TEMPLATE_CLASS(file_io_t<p_file_io::read_and_write TLOC_COMMA p_file_io::ascii>);
  TLOC_EXTERN_TEMPLATE_CLASS(file_io_t<p_file_io::read_and_write_empty TLOC_COMMA p_file_io::ascii>);
  TLOC_EXTERN_TEMPLATE_CLASS(file_io_t<p_file_io::read_and_append TLOC_COMMA p_file_io::ascii>);

  TLOC_EXTERN_TEMPLATE_CLASS(file_io_t<p_file_io::read TLOC_COMMA p_file_io::binary>);
  TLOC_EXTERN_TEMPLATE_CLASS(file_io_t<p_file_io::append TLOC_COMMA p_file_io::binary>);
  TLOC_EXTERN_TEMPLATE_CLASS(file_io_t<p_file_io::write TLOC_COMMA p_file_io::binary>);
  TLOC_EXTERN_TEMPLATE_CLASS(file_io_t<p_file_io::read_and_write TLOC_COMMA p_file_io::binary>);
  TLOC_EXTERN_TEMPLATE_CLASS(file_io_t<p_file_io::read_and_write_empty TLOC_COMMA p_file_io::binary>);
  TLOC_EXTERN_TEMPLATE_CLASS(file_io_t<p_file_io::read_and_append TLOC_COMMA p_file_io::binary>);

  // ///////////////////////////////////////////////////////////////////////

  namespace f_file_io {

    template <typename T_FileFormat>
    typename file_io_t<p_file_io::read, T_FileFormat>::error_type
      OpenAndGetContents(const core_io::path& a_filePath, 
                         core_io::FileContents& a_contentOut);

  };

};};};

#endif