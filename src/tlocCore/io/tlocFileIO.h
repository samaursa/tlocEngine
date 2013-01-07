#ifndef TLOC_FILE_IO_H
#define TLOC_FILE_IO_H

#include <cstdio>

#include <tlocCore/error/tlocError.h>
#include <tlocCore/io/tlocPath.h>

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

  public:
    typedef T_AccessPolicy                  access_policy_type;
    typedef T_FileFormat                    file_format_type;
    typedef error::Error                    error_type;

    FileIO_T(const Path& a_path);
    ~FileIO_T();

    error_type      Open();
    error_type      Close();
    error_type      Delete();
    error_type      GetContents(string_type& a_out) const;

    bool            IsOpen();

  private:

    error_type DoClose();

    FILE*   m_file;
    Path    m_fileName;
  };

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

};};};

#endif