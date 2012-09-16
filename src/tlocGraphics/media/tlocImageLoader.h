#ifndef TLOC_IMAGE_LOADER_H
#define TLOC_IMAGE_LOADER_H

#include <tlocCore/string/tlocString.h>
#include <tlocCore/error/tlocError.h>

namespace tloc { namespace graphics { namespace media {

  class ImageLoader
  {
  public:
    typedef core::error::Error    error_type;

  public:
    ImageLoader();

    error_type    Load(const char* a_fileName);

  private:
  };

};};};

#endif