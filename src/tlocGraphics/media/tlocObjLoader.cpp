#include "tlocObjLoader.h"

#include <tlocGraphics/error/tlocErrorTypes.h>

#include <tlocCore/string/tlocString.inl.h>

namespace tloc { namespace graphics { namespace media {

  enum {
    k_initialized,
    k_valid,
    k_count
  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::
    ObjLoader()
    : m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    ObjLoader::
    IsSupported(const string_type&)
  {
    return true;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::error_type
    ObjLoader::
    Init(const string_type& a_fileContents)
  {
    m_objects.clear();
    m_vertices.m_pos.clear();
    m_vertices.m_norms.clear();
    m_vertices.m_tcoords.clear();

    typedef core_conts::Array<core_str::String>     string_array;

    string_array  allLines;
    core_str::Tokenize(a_fileContents.c_str(), '\n', allLines);

    string_array::iterator itr = allLines.begin();
    string_array::iterator itrEnd = allLines.end();

    string_array eachLine;


    // We only support obj files where the vertexes, normals and tcoords i.e.
    // we do NOT support negative face index
    // are defined first
    bool verticesRecorded = false;
    bool normalsRecorded  = false;
    bool tcoordsRecorded  = false;

    m_objects.push_back(ObjGroup());
    iterator currGroup = m_objects.begin();
    core::advance(currGroup, m_objects.size() - 1);

    // NOTES: (info: http://people.cs.clemson.edu/~dhouse/courses/405/docs/brief-obj-file-format.html)
    // We ignore: Point, Line and negative face values
    // We support: Groups, Vertices, texture vertices, vertex normals, face
    while (itr != itrEnd)
    {
      eachLine.clear();
      core_str::Tokenize(itr->c_str(), core_str::g_space, eachLine);

      if (eachLine.size() == 0) { ++itr; continue; }

      string_array::iterator begin = eachLine.begin();
      string_array::iterator end = eachLine.end();

      // Begin at a non-empty word
      while (begin->size() == 0)
      { ++begin; }

      if (begin->compare("g") == 0)
      {
        if (verticesRecorded && currGroup->m_posIndices.size() != 0)
        {
          m_objects.push_back(ObjGroup());
          currGroup = m_objects.begin();
          core::advance(currGroup, m_objects.size() - 1);
        }
      }
      else if (begin->compare("v") == 0)
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

        m_vertices.m_pos.push_back(pos);
        verticesRecorded = true;

      }
      else if (begin->compare("vt") == 0)
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

        m_vertices.m_tcoords.push_back(tcoord);
        tcoordsRecorded = true;
      }
      else if (begin->compare("vn") == 0)
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

        m_vertices.m_norms.push_back(norm);
        normalsRecorded = true;
      }
      else if (begin->compare("f") == 0)
      {
        // If no vertices have been recorded, the obj file is not supported
        if (verticesRecorded == false)
        { goto RETURN_ERROR; }

        string_array::const_iterator firstNum = ++begin;

        string_array wordTokens;
        string_array::iterator beforeBegin = begin;

        tl_int vertexCount = 0;

        while (begin != end)
        {
          // If we are at a vertex count of 3, then start a new face with
          // the first vertex/normal/tcoord index as the first element of the
          // new face
          bool newFace = false;
          ++vertexCount;
          if (vertexCount > 3)
          {
            newFace = true;
            vertexCount = 1;

            // we need to take one step back for correctly indexing the polygon
            begin = beforeBegin;
          }

          wordTokens.clear();
          core_str::Tokenize(begin->c_str(), '/', wordTokens);

          // face can be: 559/3055/549 i.e. no more than 3 numbers
          if (wordTokens.size() > 3)
          { goto RETURN_ERROR; }

          string_array::const_iterator wordTokenBegin = wordTokens.begin();
          string_array::const_iterator wordTokenEnd = wordTokens.end();

          bool onlyVertexNormals = (begin->find("//") != core_str::String::npos);

          for (int i = 0; i < 3 && wordTokenBegin != wordTokenEnd;
            ++i, ++wordTokenBegin)
          {
            if (core_str::IsNumber(wordTokenBegin->c_str()) == false)
            { goto RETURN_ERROR; }

            if (i == 0)
            {
              if (newFace)
              {
                index_type newIndex = atoi(firstNum->c_str());
                currGroup->m_posIndices.push_back(newIndex);
              }
              index_type newIndex = atoi(wordTokenBegin->c_str());
              currGroup->m_posIndices.push_back(newIndex);
            }
            else if (i == 1)
            {
              if (onlyVertexNormals)
              { goto PUSH_NORM_INDEX; }
              else
              {
                if (tcoordsRecorded == false)
                { goto RETURN_ERROR; }

                if (newFace)
                {
                  index_type newIndex = atoi(firstNum->c_str());
                  currGroup->m_tcoordIndices.push_back(newIndex);
                }
                currGroup->m_tcoordIndices.push_back(atoi(wordTokenBegin->c_str()) );
              }
            }
            else
            {
PUSH_NORM_INDEX:
              if (normalsRecorded == false)
              { goto RETURN_ERROR; }

              if (newFace)
              {
                index_type newIndex = atoi(firstNum->c_str());
                currGroup->m_normIndices.push_back(newIndex);
              }
              currGroup->m_normIndices.push_back(atoi(wordTokenBegin->c_str()) );
            }
          }
          beforeBegin = begin;
          ++begin;
        }
      }
      else
      {
        // Log: Unsupported Obj tag
      }

      ++itr;
    }

    m_flags.Mark(k_valid);
    return ErrorSuccess;

RETURN_ERROR:
    m_flags.Unmark(k_valid);
    return TLOC_ERROR(error::error_obj_file_parse_error);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    ObjLoader::
    IsInitialized() const
  {
    return m_flags.IsMarked(k_initialized);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    ObjLoader::
    IsValid() const
  {
    return m_flags.IsMarked(k_valid);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const ObjLoader::ObjGroup&
    ObjLoader::
    GetGroup(size_type a_groupIndex) const
  {
    return m_objects[a_groupIndex];
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::const_iterator
    ObjLoader::
    begin() const
  {
    return m_objects.begin();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::const_iterator
    ObjLoader::
    end() const
  {
    return m_objects.end();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::const_iterator_pos
    ObjLoader::
    begin_pos() const
  {
    return m_vertices.m_pos.begin();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::const_iterator_pos
    ObjLoader::
    end_pos() const
  {
    return m_vertices.m_pos.end();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::const_iterator_norm
    ObjLoader::
    begin_norms() const
  {
    return m_vertices.m_norms.begin();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::const_iterator_norm
    ObjLoader::
    end_norms() const
  {
    return m_vertices.m_norms.end();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::const_iterator_tcoord
    ObjLoader::
    begin_tcoords() const
  {
    return m_vertices.m_tcoords.begin();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::const_iterator_tcoord
    ObjLoader::
    end_tcoords() const
  {
    return m_vertices.m_tcoords.end();
  }


};};};