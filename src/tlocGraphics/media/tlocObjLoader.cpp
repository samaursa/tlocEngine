#include "tlocObjLoader.h"

#include <tlocGraphics/error/tlocErrorTypes.h>

#include <tlocCore/string/tlocString.inl.h>

namespace tloc { namespace graphics { namespace media {

  enum {
    k_initialized,
    k_count
  };

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::ObjLoader()
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    ObjLoader::
    IsSupported(const string_type&)
  {
    return true;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::error_type
    ObjLoader::
    Init(const string_type& a_fileContents)
  {
    m_objects.clear();

    typedef core_conts::Array<core_str::String>     string_array;

    string_array  allLines;
    core_str::Tokenize(a_fileContents.c_str(), '\n', allLines);

    string_array::iterator itr = allLines.begin();
    string_array::iterator itrEnd = allLines.end();

    string_array eachLine;

    // NOTES: (info: http://people.cs.clemson.edu/~dhouse/courses/405/docs/brief-obj-file-format.html)
    // We ignore: Point, Line
    // We support: Groups, Vertices, texture vertices, vertex normals, face
    while (itr != itrEnd)
    {
      eachLine.clear();
      core_str::Tokenize(itr->c_str(), ' ', eachLine);

      if (eachLine.size() == 0) { continue; }

      string_array::iterator begin = eachLine.begin();
      string_array::iterator end = eachLine.end();

      // Begin at a non-empty word
      while (begin->size() == 0)
      { ++begin; }

      m_objects.push_back(ObjGroup());
      ObjGroup& currGroup = m_objects.back();

      switch((*begin)[0])
      {
      case 'g':
        {
          if (currGroup.m_pos.size() != 0)
          {
            m_objects.push_back(ObjGroup());
            currGroup = m_objects.back();
          }
          break;
        }
      case 'v':
        {
          ++begin;

          // We should have only 3 floats
          if (core::distance(begin, end) != 3)
          { goto RETURN_ERROR; }

          math_t::Vec3f32 pos;
          for (int i = 0; begin != end; ++i, ++begin)
          {
            if (core_str::IsRealNumber(begin->c_str()) == false)
            { goto RETURN_ERROR; }

            pos[i] = core_utils::CastNumber<f32>( atof(begin->c_str()) );
          }

          currGroup.m_pos.push_back(pos);

          break;
        }
      case 'vt':
        {
          ++begin;

          // We should have at least 2 floats
          if (core::distance(begin, end) < 2)
          { goto RETURN_ERROR; }

          math_t::Vec2f32 tcoord;
          for (int i = 0; begin != end && i < 2; ++i, ++begin)
          {
            if (core_str::IsRealNumber(begin->c_str()) == false)
            { goto RETURN_ERROR; }

            tcoord[i] = core_utils::CastNumber<f32>( atof(begin->c_str()) );
          }

          currGroup.m_tcoords.push_back(tcoord);

          break;
        }
      case 'vn':
        {
          ++begin;

          // We should have only 3 floats
          if (core::distance(begin, end) != 3)
          { goto RETURN_ERROR; }

          math_t::Vec3f32 norm;
          for (int i = 0; begin != end; ++i, ++begin)
          {
            if (core_str::IsRealNumber(begin->c_str()) == false)
            { goto RETURN_ERROR; }

            norm[i] = core_utils::CastNumber<f32>( atof(begin->c_str()) );
          }

          currGroup.m_norms.push_back(norm);

          break;
        }
      case 'f':
        {
          ++begin;

          string_array wordTokens;

          while (begin != end)
          {
            wordTokens.clear();
            core_str::Tokenize(begin->c_str(), '/', wordTokens);

            // face can be: 559/3055/549 i.e. no more than 3 numbers
            if (wordTokens.size() > 3)
            { goto RETURN_ERROR; }

            string_array::iterator wordTokenBegin = wordTokens.begin();
            string_array::iterator wordTokenEnd = wordTokens.end();

            bool onlyVertexNormals = (begin->find("//") != core_str::String::npos);

            for (int i = 0; i < 3 && wordTokenBegin != wordTokenEnd;
                 ++i, ++wordTokenBegin)
            {
              if (core_str::IsNumber(begin->c_str()) == false)
              { goto RETURN_ERROR; }

              if (i == 0)
              {
                currGroup.m_posIndices.push_back(atoi(begin->c_str()) );
              }
              else if (i == 1)
              {
                if (onlyVertexNormals)
                {
                  goto PUSH_NORM_INDEX;
                }
                else
                {
                  currGroup.m_tcoordIndices.push_back(atoi(begin->c_str()) );
                }
              }
              else
              {
PUSH_NORM_INDEX:
                currGroup.m_normIndices.push_back(atoi(begin->c_str()) );
              }
            }

            ++begin;
          }

          break;
        }
      default:
        {
          // Log: Unsupported Obj tag
        }
      }
    }

    return ErrorSuccess;

RETURN_ERROR:
    return TLOC_ERROR(error::error_obj_file_parse_error);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const ObjLoader::ObjGroup&
    ObjLoader::
    GetGroup(size_type a_groupIndex) const
  {
    return m_objects[a_groupIndex];
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::const_iterator
    ObjLoader::
    begin() const
  {
    return m_objects.begin();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::const_iterator
    ObjLoader::
    end() const
  {
    return m_objects.end();
  }



};};};