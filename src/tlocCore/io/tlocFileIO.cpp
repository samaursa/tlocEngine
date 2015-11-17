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
                 p_file_io::read, p_file_io::ascii)
    { return fopen(a_fileName, "r"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::read, p_file_io::binary)
    { return fopen(a_fileName, "rb"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::write, p_file_io::ascii)
    { return fopen(a_fileName, "w"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::write, p_file_io::binary)
    { return fopen(a_fileName, "wb"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::append, p_file_io::ascii)
    { return fopen(a_fileName, "a"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::append, p_file_io::binary)
    { return fopen(a_fileName, "ab"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::read_and_write, p_file_io::ascii)
    { return fopen(a_fileName, "r+"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::read_and_write, p_file_io::binary)
    { return fopen(a_fileName, "r+b"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::read_and_write_empty, p_file_io::ascii)
    { return fopen(a_fileName, "w+"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::read_and_write_empty, p_file_io::binary)
    { return fopen(a_fileName, "w+b"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::read_and_append, p_file_io::ascii)
    { return fopen(a_fileName, "a+"); }

    FILE* DoOpen(const char* a_fileName,
                 p_file_io::read_and_append, p_file_io::binary)
    { return fopen(a_fileName, "a+b"); }
  };

  //------------------------------------------------------------------------
  // FileFromDisk

#define FILE_IO_TEMP    typename T_AccessPolicy, typename T_FileFormat
#define FILE_IO_PARAMS  T_AccessPolicy, T_FileFormat
#define FILE_IO_TYPE    typename FileIO_T<FILE_IO_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  file_io_t<FILE_IO_PARAMS>::
    file_io_t(const path& a_path)
    : m_file(nullptr), m_filePath(a_path)
  {
    TLOC_ASSERT(m_filePath.has_file_name(), "Path does not contain a filename!");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  file_io_t<FILE_IO_PARAMS>::
    file_io_t(const this_type& a_other)
    : m_file(nullptr)
    , m_filePath(a_other.m_filePath)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  file_io_t<FILE_IO_PARAMS>::
    ~file_io_t()
  {
    DoClose();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::this_type&
    file_io_t<FILE_IO_PARAMS>::
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
    file_io_t<FILE_IO_PARAMS>::
    open() /* const */
  {
    if (m_filePath.has_file_name() == false)
    { return TLOC_ERROR(common_error_types::error_path_incorrect); }

    m_file = detail::DoOpen(m_filePath.get_path(), access_policy_type(),
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
    file_io_t<FILE_IO_PARAMS>::
    is_open() const
  {
    return m_file != nullptr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    file_io_t<FILE_IO_PARAMS>::
    close()
  {
    return DoClose();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // NOTE: See explanation in Open() for why this is not const

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    file_io_t<FILE_IO_PARAMS>::
    delete() /* const */
  {
    if (::remove(m_filePath.get_path()) == 0)
    { return ErrorSuccess; }
    else
    { return ErrorFailure; }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    file_io_t<FILE_IO_PARAMS>::
    write(buffer_arg a_string) const
  {
    TLOC_ASSERT(is_open(), "Attempting to write/append to a file that is not open");

    if (fprintf(m_file, "%s", a_string.GetPtr()) >= 0)
    { return ErrorSuccess; }
    else
    { return TLOC_ERROR(common_error_types::error_file_write); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    file_io_t<FILE_IO_PARAMS>::
    write(buffer_arg a_string, tl_size a_buffSize) const
  {
    TLOC_ASSERT(is_open(), "Attempting to write/append to a file that is not open");

    if (fwrite((char*)a_string.GetPtr(), 1, a_buffSize, m_file) != a_buffSize)
    {
      return TLOC_ERROR(common_error_types::error_file_write);
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    file_io_t<FILE_IO_PARAMS>::
    get_contents(String& a_out) const
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
    file_io_t<FILE_IO_PARAMS>::
    get_contents(FileContents& a_out) const
  {
    string_type contents;
    auto err = get_contents(contents);

    a_out = FileContents(m_filePath, contents);
    return err;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  void
    file_io_t<FILE_IO_PARAMS>::
    swap(this_type& a_other)
  {
    using core::swap;
    swap(m_file, a_other.m_file);
    swap(m_filePath, a_other.m_filePath);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <FILE_IO_TEMP>
  FILE_IO_TYPE::error_type
    file_io_t<FILE_IO_PARAMS>::
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

  template class file_io_t<p_file_io::read, p_file_io::ascii>;
  template class file_io_t<p_file_io::append, p_file_io::ascii>;
  template class file_io_t<p_file_io::write, p_file_io::ascii>;
  template class file_io_t<p_file_io::read_and_write, p_file_io::ascii>;
  template class file_io_t<p_file_io::read_and_write_empty, p_file_io::ascii>;
  template class file_io_t<p_file_io::read_and_append, p_file_io::ascii>;

  template class file_io_t<p_file_io::read, p_file_io::binary>;
  template class file_io_t<p_file_io::append, p_file_io::binary>;
  template class file_io_t<p_file_io::write, p_file_io::binary>;
  template class file_io_t<p_file_io::read_and_write, p_file_io::binary>;
  template class file_io_t<p_file_io::read_and_write_empty, p_file_io::binary>;
  template class file_io_t<p_file_io::read_and_append, p_file_io::binary>;

  // ///////////////////////////////////////////////////////////////////////

  namespace f_file_io {

    template <typename T_FileFormat>
    typename file_io_t<p_file_io::read, T_FileFormat>::error_type
      OpenAndGetContents(const core_io::path& a_filePath, 
                         core_io::FileContents& a_contentOut)
    {
      typedef file_io_t<p_file_io::read, T_FileFormat>       file_io_type;

      file_io_type f(a_filePath);

      core_err::Error err = ErrorSuccess;
      err = f.open();

      if (err.Failed())
      { return TLOC_ERROR(common_error_types::error_file_not_found); }

      err = f.get_contents(a_contentOut);
      if (err.Failed())
      { return TLOC_ERROR(common_error_types::error_file_read); }

      f.close();

      return err;
    }

    // -----------------------------------------------------------------------
    // explicit instantiate OpenAndGetContents

#define TLOC_EXPLICITLY_INSTANTIATE_FILE_IO_OPEN_AND_GET_CONTENTS(_fileFormat_)\
  template FileIO_T<p_file_io::Read, _fileFormat_>::error_type\
  OpenAndGetContents<_fileFormat_>(const core_io::Path&, core_io::FileContents&)

    TLOC_EXPLICITLY_INSTANTIATE_FILE_IO_OPEN_AND_GET_CONTENTS(p_file_io::ascii);
    TLOC_EXPLICITLY_INSTANTIATE_FILE_IO_OPEN_AND_GET_CONTENTS(p_file_io::binary);

  };

};};};