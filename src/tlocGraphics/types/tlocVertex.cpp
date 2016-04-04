#include "tlocVertex.h"

namespace tloc { namespace graphics { namespace types {

  namespace f_vertex {

    // ///////////////////////////////////////////////////////////////////////
    // VertexAttribPointerInfo

    VertexAttribPointerInfo::
      VertexAttribPointerInfo()
      : m_size(0)
      , m_stride(0)
      , m_pointerIndex(0)
    { }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    VertexAttribPointerInfo::
      VertexAttribPointerInfo(gl_int a_size, gl_sizei a_stride, 
                              size_type a_pointerIndex) 
      : m_size(a_size)
      , m_stride(a_stride)
      , m_pointerIndex(a_pointerIndex)
    { }

    // -----------------------------------------------------------------------

    VertexAttribPointerInfo 
      GetCustomGLTypeInfo(tl_int a_customGlType, tl_size a_interleaveIndex)
    {
      TLOC_ASSERT(a_customGlType >= TLOC_GL_POSITION2F &&
                  a_customGlType <= TLOC_GL_POSITION3F_NORMAL3F_COLOR4F_TEXTURE2F,
                  "Invalid type specified");
      TLOC_ASSERT(a_interleaveIndex >= 0 && a_interleaveIndex <= 3, 
                  "Custom types have upto 4 interleaving types");

      switch(a_customGlType)
      {
        // -----------------------------------------------------------------------
        // POSITION2F

        case TLOC_GL_POSITION2F:
        {
          TLOC_ASSERT(a_interleaveIndex == 0, "Type has no interleaving");
          return VertexAttribPointerInfo(2, 0, 0);
        }
        case TLOC_GL_POSITION2F_NORMAL3F:
        {
          TLOC_ASSERT(a_interleaveIndex <= 1, "Type has 2 interleaving types");
          switch(a_interleaveIndex)
          {
            case 0: // POSITION2F
            { return VertexAttribPointerInfo(2, 5, 0); }
            case 1: // NORMAL3F
            { return VertexAttribPointerInfo(3, 5, 2); }
          }
        }
        case TLOC_GL_POSITION2F_TEXTURE2F:
        {
          TLOC_ASSERT(a_interleaveIndex <= 1, "Type has 2 interleaving types");
          switch(a_interleaveIndex)
          {
            case 0: // POSITION2F
            { return VertexAttribPointerInfo(2, 4, 0); }
            case 1: // TEXTURE2F
            { return VertexAttribPointerInfo(2, 4, 2); }
          }
        }
        case TLOC_GL_POSITION2F_COLOR4F:
        {
          TLOC_ASSERT(a_interleaveIndex <= 1, "Type has 2 interleaving types");
          switch(a_interleaveIndex)
          {
            case 0: // POSITION2F
            { return VertexAttribPointerInfo(2, 6, 0); }
            case 1: // COLOR4F
            { return VertexAttribPointerInfo(4, 6, 2); }
          }
        }
        case TLOC_GL_POSITION2F_NORMAL3F_COLOR4F:
        {
          TLOC_ASSERT(a_interleaveIndex <= 2, "Type has 3 interleaving types");
          switch(a_interleaveIndex)
          {
            case 0: // POSITION2F
            { return VertexAttribPointerInfo(2, 9, 0); }
            case 1: // NORMAL3F
            { return VertexAttribPointerInfo(3, 9, 2); }
            case 2: // COLOR4F
            { return VertexAttribPointerInfo(4, 9, 5); }
          }
        }
        case TLOC_GL_POSITION2F_NORMAL3F_TEXTURE2F:
        {
          TLOC_ASSERT(a_interleaveIndex <= 2, "Type has 3 interleaving types");
          switch(a_interleaveIndex)
          {
            case 0: // POSITION2F
            { return VertexAttribPointerInfo(2, 7, 0); }
            case 1: // NORMAL3F
            { return VertexAttribPointerInfo(3, 7, 2); }
            case 2: // TEXTURE2F
            { return VertexAttribPointerInfo(2, 7, 5); }
          }
        }
        case TLOC_GL_POSITION2F_NORMAL3F_COLOR4F_TEXTURE2F:
        {
          switch(a_interleaveIndex)
          {
            case 0: // POSITION2F
            { return VertexAttribPointerInfo(2, 11, 0); }
            case 1: // NORMAL3F
            { return VertexAttribPointerInfo(3, 11, 2); }
            case 2: // COLOR4F
            { return VertexAttribPointerInfo(4, 11, 5); }
            case 3: // TEXTURE2F
            { return VertexAttribPointerInfo(2, 11, 9); }
          }
        }

        // -----------------------------------------------------------------------
        // POSITION3F

        case TLOC_GL_POSITION3F:
        {
          TLOC_ASSERT(a_interleaveIndex == 0, "Type has no interleaving");
          return VertexAttribPointerInfo(3, 0, 0);
        }
        case TLOC_GL_POSITION3F_NORMAL3F:
        {
          TLOC_ASSERT(a_interleaveIndex <= 1, "Type has 2 interleaving types");
          switch(a_interleaveIndex)
          {
            case 0: // POSITION3F
            { return VertexAttribPointerInfo(3, 6, 0); }
            case 1: // NORMAL3F
            { return VertexAttribPointerInfo(3, 6, 3); }
          }
        }
        case TLOC_GL_POSITION3F_TEXTURE2F:
        {
          TLOC_ASSERT(a_interleaveIndex <= 1, "Type has 2 interleaving types");
          switch(a_interleaveIndex)
          {
            case 0: // POSITION3F
            { return VertexAttribPointerInfo(3, 5, 0); }
            case 1: // TEXTURE2F
            { return VertexAttribPointerInfo(2, 5, 3); }
          }
        }
        case TLOC_GL_POSITION3F_COLOR4F:
        {
          TLOC_ASSERT(a_interleaveIndex <= 1, "Type has 2 interleaving types");
          switch(a_interleaveIndex)
          {
            case 0: // POSITION3F
            { return VertexAttribPointerInfo(3, 7, 0); }
            case 1: // COLOR4F
            { return VertexAttribPointerInfo(4, 7, 3); }
          }
        }
        case TLOC_GL_POSITION3F_NORMAL3F_COLOR4F:
        {
          TLOC_ASSERT(a_interleaveIndex <= 2, "Type has 3 interleaving types");
          switch(a_interleaveIndex)
          {
            case 0: // POSITION3F
            { return VertexAttribPointerInfo(3, 10, 0); }
            case 1: // NORMAL3F
            { return VertexAttribPointerInfo(3, 10, 3); }
            case 2: // COLOR4F
            { return VertexAttribPointerInfo(4, 10, 6); }
          }
        }
        case TLOC_GL_POSITION3F_NORMAL3F_TEXTURE2F:
        {
          TLOC_ASSERT(a_interleaveIndex <= 2, "Type has 3 interleaving types");
          switch(a_interleaveIndex)
          {
            case 0: // POSITION3F
            { return VertexAttribPointerInfo(3, 8, 0); }
            case 1: // NORMAL3F
            { return VertexAttribPointerInfo(3, 8, 3); }
            case 2: // TEXTURE2F
            { return VertexAttribPointerInfo(2, 8, 6); }
          }
        }
        case TLOC_GL_POSITION3F_TEXTURE2F_TBN:
        {
          TLOC_ASSERT(a_interleaveIndex <= 2, "Type has 3 interleaving types");
          switch(a_interleaveIndex)
          {
            case 0: // POSITION3F
            { return VertexAttribPointerInfo(3, 14, 0); }
            case 1: // TEXTURE2F
            { return VertexAttribPointerInfo(2, 14, 3); }
            case 2: // MATRIX3F
            { return VertexAttribPointerInfo(3, 14, 5); }
          }
        }
        case TLOC_GL_POSITION3F_NORMAL3F_COLOR4F_TEXTURE2F:
        {
          switch(a_interleaveIndex)
          {
            case 0: // POSITION3F
            { return VertexAttribPointerInfo(3, 12, 0); }
            case 1: // NORMAL3F
            { return VertexAttribPointerInfo(3, 12, 3); }
            case 2: // COLOR4F
            { return VertexAttribPointerInfo(4, 12, 6); }
            case 3: // TEXTURE2F
            { return VertexAttribPointerInfo(2, 12, 10); }
          }
        }
        default:
        { return VertexAttribPointerInfo(); }
      }
    }
  };

};};};