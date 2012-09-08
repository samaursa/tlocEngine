#include "tlocFileIO.h"

#include <tlocCore/memory/tlocMemory.h>

namespace tloc { namespace core { namespace io {

  //------------------------------------------------------------------------
  // Policy details

  namespace detail
  {
    // Yes, this is a lot of repetition but this is done only once and in
    // return we get type safety (that is, we will never have to find out at
    // run-time that we used incorrect file access parameters)

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::Read, p_file_io::Ascii)
    { return fopen(a_fileName, "r"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::Read, p_file_io::Binary)
    { return fopen(a_fileName, "rb"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::Write, p_file_io::Ascii)
    { return fopen(a_fileName, "w"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::Write, p_file_io::Binary)
    { return fopen(a_fileName, "wb"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::Append, p_file_io::Ascii)
    { return fopen(a_fileName, "a"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::Append, p_file_io::Binary)
    { return fopen(a_fileName, "ab"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::Read_And_Write, p_file_io::Ascii)
    { return fopen(a_fileName, "r+"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::Read_And_Write, p_file_io::Binary)
    { return fopen(a_fileName, "r+b"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::Read_And_Write_Empty, p_file_io::Ascii)
    { return fopen(a_fileName, "w+"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::Read_And_Write_Empty, p_file_io::Binary)
    { return fopen(a_fileName, "w+b"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::Read_And_Append, p_file_io::Ascii)
    { return fopen(a_fileName, "a+"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::Read_And_Append, p_file_io::Binary)
    { return fopen(a_fileName, "a+b"); }
  };

  //------------------------------------------------------------------------
  // FileFromDisk

#define FILE_IO_TEMP    typename T_AccessPolicy, typename T_FileFormat
#define FILE_IO_PARAMS  T_AccessPolicy, T_FileFormat
#define FILE_IO_TYPE    typename FileIO<FILE_IO_PARAMS>

  template <FILE_IO_TEMP>
  FileIO<FILE_IO_PARAMS>::FileIO(const char* a_fileName)
    : m_fileName(a_fileName)
  {
  }

  template <FILE_IO_TEMP>
  FileIO<FILE_IO_PARAMS>::~FileIO()
  {
    DoClose();
  }

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type FileIO<FILE_IO_PARAMS>::Open()
  {
    m_file = detail::DoOpen(m_fileName.c_str(), access_policy_type(),
                            file_format_type());
    if (m_file)
    {
      return core::error::ErrorSuccess();
    }

    return core::error::ErrorFailure();
  }

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type FileIO<FILE_IO_PARAMS>::Close()
  {
    return DoClose();
  }

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    FileIO<FILE_IO_PARAMS>::GetContents(String& a_out) const
  {
    TLOC_ASSERT(m_file, "No file to read - did you forget to call Open()?");
    fseek(m_file, 0, SEEK_END);

    tl_size fileSize = ftell(m_file);
    rewind(m_file);

    char* buffer = (char*)TL_MALLOC(sizeof(char) * fileSize);

    tl_size result = fread(buffer, 1, fileSize, m_file);
    if (result != fileSize) { return core::error::ErrorFailure(); }

    buffer[fileSize - 1] = '\0';
    a_out = buffer;

    TL_FREE(buffer);

    return core::error::ErrorSuccess();
  }

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type FileIO<FILE_IO_PARAMS>::DoClose()
  {
    if (m_file)
    {
      if (fclose(m_file) == EOF)
      {
        return core::error::ErrorFailure();
      }
    }

    return core::error::ErrorSuccess();
  }

  //------------------------------------------------------------------------
  // Force Instantiate

  template class FileIO<p_file_io::Read, p_file_io::Ascii>;
  template class FileIO<p_file_io::Append, p_file_io::Ascii>;
  template class FileIO<p_file_io::Write, p_file_io::Ascii>;
  template class FileIO<p_file_io::Read_And_Write, p_file_io::Ascii>;
  template class FileIO<p_file_io::Read_And_Write_Empty, p_file_io::Ascii>;
  template class FileIO<p_file_io::Read_And_Append, p_file_io::Ascii>;

  template class FileIO<p_file_io::Read, p_file_io::Binary>;
  template class FileIO<p_file_io::Append, p_file_io::Binary>;
  template class FileIO<p_file_io::Write, p_file_io::Binary>;
  template class FileIO<p_file_io::Read_And_Write, p_file_io::Binary>;
  template class FileIO<p_file_io::Read_And_Write_Empty, p_file_io::Binary>;
  template class FileIO<p_file_io::Read_And_Append, p_file_io::Binary>;

};};};