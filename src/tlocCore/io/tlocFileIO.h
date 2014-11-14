#ifndef TLOC_FILE_IO_H
#define TLOC_FILE_IO_H

#include <tlocCore/tlocCoreBase.h>

#include <cstdio>

#include <tlocCore/error/tlocError.h>
#include <tlocCore/io/tlocPath.h>
#include <tlocCore/memory/tlocBufferArg.h>

namespace tloc { namespace core { namespace io {

  namespace p_file_io
  {
    // Access policies
    struct Read{};
    struct Write{};
    struct Append{};
    struct Read_And_Write{};
    struct Read_And_Write_Empty{};
    struct Read_And_Append{};

    // File type policies
    struct Ascii{};
    struct Binary{};
  };

  template <typename T_AccessPolicy, typename T_FileFormat>
  class FileIO_T
  {
  public:
    typedef string::String                  string_type;

    typedef T_AccessPolicy                  access_policy_type;
    typedef T_FileFormat                    file_format_type;
    typedef error::Error                    error_type;

    typedef FileIO_T<access_policy_type, file_format_type>  this_type;

  public:
    FileIO_T(const Path& a_path);
    FileIO_T(const this_type& a_other);
    ~FileIO_T();

    this_type& operator=(this_type a_other);

    error_type      Open();
    error_type      Close();
    error_type      Delete();
    error_type      Write(BufferArg a_string) const;
    error_type      GetContents(string_type& a_out) const;
    void            swap(this_type& a_other);

    bool            IsOpen() const;

  private:

    error_type      DoClose();

    FILE*   m_file;
    Path    m_fileName;
  };

  // -----------------------------------------------------------------------
  // swap

  template <typename T_AccessPolicy, typename T_FileFormat>
  void swap(FileIO_T<T_AccessPolicy, T_FileFormat>& a,
            FileIO_T<T_AccessPolicy, T_FileFormat>& b)
  { a.swap(b); }

  //------------------------------------------------------------------------
  // All typedefs for our FileIO template class

  typedef FileIO_T<p_file_io::Read,
                 p_file_io::Ascii>                  FileIO_ReadA;
  typedef FileIO_T<p_file_io::Append,
                 p_file_io::Ascii>                  FileIO_AppendA;
  typedef FileIO_T<p_file_io::Write,
                 p_file_io::Ascii>                  FileIO_WriteA;
  typedef FileIO_T<p_file_io::Read_And_Write,
                 p_file_io::Ascii>                  FileIO_ReadAndWriteA;
  typedef FileIO_T<p_file_io::Read_And_Write_Empty,
                 p_file_io::Ascii>                  FileIO_ReadAndWriteEmptyA;
  typedef FileIO_T<p_file_io::Read_And_Append,
                 p_file_io::Ascii>                  FileIO_ReadAndAppendA;

  typedef FileIO_T<p_file_io::Read,
                 p_file_io::Binary>                  FileIO_ReadB;
  typedef FileIO_T<p_file_io::Append,
                 p_file_io::Binary>                  FileIO_AppendB;
  typedef FileIO_T<p_file_io::Write,
                 p_file_io::Binary>                  FileIO_WriteB;
  typedef FileIO_T<p_file_io::Read_And_Write,
                 p_file_io::Binary>                  FileIO_ReadAndWriteB;
  typedef FileIO_T<p_file_io::Read_And_Write_Empty,
                 p_file_io::Binary>                  FileIO_ReadAndWriteEmptyB;
  typedef FileIO_T<p_file_io::Read_And_Append,
                 p_file_io::Binary>                  FileIO_ReadAndAppendB;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(FileIO_T<p_file_io::Read TLOC_COMMA p_file_io::Ascii>);
  TLOC_EXTERN_TEMPLATE_CLASS(FileIO_T<p_file_io::Append TLOC_COMMA p_file_io::Ascii>);
  TLOC_EXTERN_TEMPLATE_CLASS(FileIO_T<p_file_io::Write TLOC_COMMA p_file_io::Ascii>);
  TLOC_EXTERN_TEMPLATE_CLASS(FileIO_T<p_file_io::Read_And_Write TLOC_COMMA p_file_io::Ascii>);
  TLOC_EXTERN_TEMPLATE_CLASS(FileIO_T<p_file_io::Read_And_Write_Empty TLOC_COMMA p_file_io::Ascii>);
  TLOC_EXTERN_TEMPLATE_CLASS(FileIO_T<p_file_io::Read_And_Append TLOC_COMMA p_file_io::Ascii>);

  TLOC_EXTERN_TEMPLATE_CLASS(FileIO_T<p_file_io::Read TLOC_COMMA p_file_io::Binary>);
  TLOC_EXTERN_TEMPLATE_CLASS(FileIO_T<p_file_io::Append TLOC_COMMA p_file_io::Binary>);
  TLOC_EXTERN_TEMPLATE_CLASS(FileIO_T<p_file_io::Write TLOC_COMMA p_file_io::Binary>);
  TLOC_EXTERN_TEMPLATE_CLASS(FileIO_T<p_file_io::Read_And_Write TLOC_COMMA p_file_io::Binary>);
  TLOC_EXTERN_TEMPLATE_CLASS(FileIO_T<p_file_io::Read_And_Write_Empty TLOC_COMMA p_file_io::Binary>);
  TLOC_EXTERN_TEMPLATE_CLASS(FileIO_T<p_file_io::Read_And_Append TLOC_COMMA p_file_io::Binary>);

  // ///////////////////////////////////////////////////////////////////////

  namespace f_file_io {

    template <typename T_FileFormat>
    typename FileIO_T<p_file_io::Read, T_FileFormat>::error_type
      OpenAndGetContents(const core_io::Path& a_filePath, 
                         core_str::String& a_contentOut);

  };

};};};

#endif