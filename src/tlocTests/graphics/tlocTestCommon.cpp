#include "tlocTestCommon.h"
#include <tlocCore/platform/tlocPlatform.h>

#include <cstring>

#if defined(TLOC_OS_WIN)

const char* GetResourcePath()
{
  static const char* resourcePath = "../../../../../resources/";
  return resourcePath;
}
#elif defined(TLOC_OS_IPHONE)
const char* GetResourcePath()
{
  static char resourcePath[1024];
  strcpy(resourcePath, [[[NSBundle mainBundle] resourcePath]
                        cStringUsingEncoding:[NSString defaultCStringEncoding]]);
  strcat(resourcePath, "/resources/");

  return resourcePath;
}
#endif