#include "tlocImageLoader.h"

#include <tlocCore/io/tlocFileIO.h>

namespace tloc { namespace graphics { namespace media {

  ImageLoader::ImageLoader()
  {
  }

  ImageLoader::error_type ImageLoader::Load(const path_type& a_path)
  {
    if (a_path.HasFilename() == false)
    { return common_error_types::error_path_incorrect; }

    if (a_path.FileExists() == false)
    { return common_error_types::error_file_not_found; }

    core::io::FileIO_ReadB imgFile(a_path);

    error_type res = imgFile.Open();
    if (res != common_error_types::error_success)
    { return res; }

    core::String imgCont;
    imgFile.GetContents(imgCont);

    res = m_image.LoadFromMemory(imgCont.c_str(), imgCont.length());
    if (res != common_error_types::error_success)
    { return res; }

    return common_error_types::error_success;
  }

};};};