#include "tlocFileIO.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/memory/tlocMemory.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/string/tlocString.inl.h>

#include <stdio.h>
#include <cstdio>

namespace tloc { namespace core { namespace io {

  using string::String;

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
#define FILE_IO_TYPE    typename FileIO_T<FILE_IO_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FileIO_T<FILE_IO_PARAMS>::
    FileIO_T(const Path& a_path)
    : m_file(nullptr), m_filePath(a_path)
  {
    TLOC_ASSERT(m_filePath.HasFilename(), "Path does not contain a filename!");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FileIO_T<FILE_IO_PARAMS>::
    FileIO_T(const this_type& a_other)
    : m_file(nullptr)
    , m_filePath(a_other.m_filePath)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FileIO_T<FILE_IO_PARAMS>::
    ~FileIO_T()
  {
    DoClose();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::this_type&
    FileIO_T<FILE_IO_PARAMS>::
    operator=(this_type a_other)
  {
    swap(a_other);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // NOTE: This function could be a 'const' but is deliberately not so to
  //       be more consistent with usage. Close() cannot be const and
  //       intuitively so shouldn't be Open(). Moreover, we would like to
  //       pass a FileIO_T<> as a const reference and ensure that the receiver
  //       cannot open/close the file

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    FileIO_T<FILE_IO_PARAMS>::
    Open() /* const */
  {
    if (m_filePath.HasFilename() == false)
    { return TLOC_ERROR(common_error_types::error_path_incorrect); }

    m_file = detail::DoOpen(m_filePath.GetPath(), access_policy_type(),
                            file_format_type());
    if (m_file)
    {
      return ErrorSuccess;
    }

    return ErrorFailure;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  bool
    FileIO_T<FILE_IO_PARAMS>::
    IsOpen() const
  {
    return m_file != nullptr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    FileIO_T<FILE_IO_PARAMS>::
    Close()
  {
    return DoClose();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // NOTE: See explanation in Open() for why this is not const

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    FileIO_T<FILE_IO_PARAMS>::
    Delete() /* const */
  {
    if (::remove(m_filePath.GetPath()) == 0)
    { return ErrorSuccess; }
    else
    { return ErrorFailure; }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    FileIO_T<FILE_IO_PARAMS>::
    Write(BufferArg a_string) const
  {
    TLOC_ASSERT(IsOpen(), "Attempting to write/append to a file that is not open");

    if (fprintf(m_file, "%s", a_string.GetPtr()) >= 0)
    { return ErrorSuccess; }
    else
    { return TLOC_ERROR(common_error_types::error_file_write); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    FileIO_T<FILE_IO_PARAMS>::
    Write(BufferArg a_string, tl_size a_buffSize) const
  {
    TLOC_ASSERT(IsOpen(), "Attempting to write/append to a file that is not open");

    if (fwrite((char*)a_string.GetPtr(), 1, a_buffSize, m_file) != a_buffSize)
    {
      return TLOC_ERROR(common_error_types::error_file_write);
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    FileIO_T<FILE_IO_PARAMS>::
    GetContents(String& a_out) const
  {
    TLOC_ASSERT(m_file, "No file to read - did you forget to call Open()?");

    if (fseek(m_file, 0, SEEK_END) != 0)
    { return ErrorFailure; }

    tl_long fileSize = ftell(m_file);
    if (fileSize < 0)
    { return ErrorFailure; }

    rewind(m_file);

    const tl_size fileSizeInclNull = fileSize + 1;
    char* buffer = (char*)TL_MALLOC(sizeof(char) * fileSizeInclNull);

    tl_size result = fread(buffer, 1, fileSizeInclNull, m_file);
    if (result == 0) { return ErrorFailure; }

    buffer[result] = '\0';
    a_out.assign(buffer, buffer + result);

    TL_FREE(buffer);

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    FileIO_T<FILE_IO_PARAMS>::
    GetContents(FileContents& a_out) const
  {
    string_type contents;
    auto err = GetContents(contents);

    a_out = FileContents(m_filePath, contents);
    return err;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  void
    FileIO_T<FILE_IO_PARAMS>::
    swap(this_type& a_other)
  {
    using core::swap;
    swap(m_file, a_other.m_file);
    swap(m_filePath, a_other.m_filePath);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    FileIO_T<FILE_IO_PARAMS>::
    DoClose()
  {
    if (m_file)
    {
      if (fclose(m_file) == EOF)
      {
        return ErrorFailure;
      }
    }

    m_file = nullptr;
    return ErrorSuccess;
  }

  //------------------------------------------------------------------------
  // Force Instantiate

  template class FileIO_T<p_file_io::Read, p_file_io::Ascii>;
  template class FileIO_T<p_file_io::Append, p_file_io::Ascii>;
  template class FileIO_T<p_file_io::Write, p_file_io::Ascii>;
  template class FileIO_T<p_file_io::Read_And_Write, p_file_io::Ascii>;
  template class FileIO_T<p_file_io::Read_And_Write_Empty, p_file_io::Ascii>;
  template class FileIO_T<p_file_io::Read_And_Append, p_file_io::Ascii>;

  template class FileIO_T<p_file_io::Read, p_file_io::Binary>;
  template class FileIO_T<p_file_io::Append, p_file_io::Binary>;
  template class FileIO_T<p_file_io::Write, p_file_io::Binary>;
  template class FileIO_T<p_file_io::Read_And_Write, p_file_io::Binary>;
  template class FileIO_T<p_file_io::Read_And_Write_Empty, p_file_io::Binary>;
  template class FileIO_T<p_file_io::Read_And_Append, p_file_io::Binary>;

  // ///////////////////////////////////////////////////////////////////////

  namespace f_file_io {

    template <typename T_FileFormat>
    typename FileIO_T<p_file_io::Read, T_FileFormat>::error_type
      OpenAndGetContents(const core_io::Path& a_filePath, 
                         core_str::String& a_contentOut)
    {
      typedef FileIO_T<p_file_io::Read, T_FileFormat>       file_io_type;

      file_io_type f(a_filePath);

      core_err::Error err = ErrorSuccess;
      err = f.Open();

      if (err.Failed())
      { return TLOC_ERROR(common_error_types::error_file_not_found); }

      f.GetContents(a_contentOut);
      f.Close();

      return err;
    }

    // -----------------------------------------------------------------------
    // explicit instantiate OpenAndGetContents

#define TLOC_EXPLICITLY_INSTANTIATE_FILE_IO_OPEN_AND_GET_CONTENTS(_fileFormat_)\
  template FileIO_T<p_file_io::Read, _fileFormat_>::error_type\
  OpenAndGetContents<_fileFormat_>(const core_io::Path&, core_str::String&)

    TLOC_EXPLICITLY_INSTANTIATE_FILE_IO_OPEN_AND_GET_CONTENTS(p_file_io::Ascii);
    TLOC_EXPLICITLY_INSTANTIATE_FILE_IO_OPEN_AND_GET_CONTENTS(p_file_io::Binary);

  };

};};};