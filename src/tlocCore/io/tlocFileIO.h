#ifndef TLOC_FILE_IO_H
#define TLOC_FILE_IO_H

#include <cstdio>

#include <tlocCore/error/tlocError.h>
#include <tlocCore/string/tlocString.h>

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
  class FileIO
  {
  public:
    typedef T_AccessPolicy                  access_policy_type;
    typedef T_FileFormat                    file_format_type;
    typedef error::Error                    error_type;

    FileIO(const char* a_fileName);
    ~FileIO();

    error_type      Open();
    error_type      Close();
    error_type      GetContents(String& a_out) const;

  private:

    error_type DoClose();

    FILE*   m_file;
    String  m_fileName;
  };

  //------------------------------------------------------------------------
  // All typedefs for our FileIO template class

  typedef FileIO<p_file_io::Read,
                 p_file_io::Ascii>                  FileIO_ReadA;
  typedef FileIO<p_file_io::Append,
                 p_file_io::Ascii>                  FileIO_AppendA;
  typedef FileIO<p_file_io::Write,
                 p_file_io::Ascii>                  FileIO_WriteA;
  typedef FileIO<p_file_io::Read_And_Write,
                 p_file_io::Ascii>                  FileIO_ReadAndWriteA;
  typedef FileIO<p_file_io::Read_And_Write_Empty,
                 p_file_io::Ascii>                  FileIO_ReadAndWriteEmptyA;
  typedef FileIO<p_file_io::Read_And_Append,
                 p_file_io::Ascii>                  FileIO_ReadAndAppendA;

  typedef FileIO<p_file_io::Read,
                 p_file_io::Binary>                  FileIO_ReadB;
  typedef FileIO<p_file_io::Append,
                 p_file_io::Binary>                  FileIO_AppendB;
  typedef FileIO<p_file_io::Write,
                 p_file_io::Binary>                  FileIO_WriteB;
  typedef FileIO<p_file_io::Read_And_Write,
                 p_file_io::Binary>                  FileIO_ReadAndWriteB;
  typedef FileIO<p_file_io::Read_And_Write_Empty,
                 p_file_io::Binary>                  FileIO_ReadAndWriteEmptyB;
  typedef FileIO<p_file_io::Read_And_Append,
                 p_file_io::Binary>                  FileIO_ReadAndAppendB;

};};};

#endif