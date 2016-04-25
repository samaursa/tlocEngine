#include "tlocObjLoader.h"

#include <tlocGraphics/error/tlocErrorTypes.h>

#include <tlocCore/string/tlocString.inl.h>
#include <tlocCore/logging/tlocLogger.h>

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
    m_vertices.m_tbn.clear();
    m_vertices.m_tcoords.clear();

    typedef core_conts::Array<core_str::String>     string_array;

    string_array  allLines;
    core_str::Tokenize(a_fileContents.c_str(), core_str::g_newline, allLines);

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

    error_type retErr = TLOC_ERROR(error::error_obj_file_parse_error);

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

      // treating groups and objects as the same
      if (begin->compare("g") == 0 || begin->compare("o") == 0)
      {
        ++begin;

        if (verticesRecorded && currGroup->m_posIndices.size() != 0)
        {
          m_objects.push_back(ObjGroup());
          currGroup = m_objects.begin();
          core::advance(currGroup, m_objects.size() - 1);
        }

        // the group may be nameless
        if (begin != end)
        { currGroup->m_name = *begin; }
      }
      else if (begin->compare("v") == 0)
      {
        ++begin;

        // We should have only 3 floats
        if (core::distance(begin, end) != 3)
        { 
          retErr = TLOC_ERROR(error::error_obj_file_invalid_vertex);
          goto RETURN_ERROR;
        }

        math_t::Vec3f32 pos;
        for (int i = 0; begin != end; ++i, ++begin)
        {
          if (core_str::IsRealNumber(begin->c_str()) == false)
          { 
            retErr = TLOC_ERROR(error::error_obj_file_expecting_real_number_encountered_NAN);
            goto RETURN_ERROR;
          }

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
        { 
          retErr = TLOC_ERROR(error::error_obj_file_invalid_vertex_texcoord);
          goto RETURN_ERROR;
        }

        math_t::Vec2f32 tcoord;
        for (int i = 0; begin != end && i < 2; ++i, ++begin)
        {
          if (core_str::IsRealNumber(begin->c_str()) == false)
          { 
            retErr = TLOC_ERROR(error::error_obj_file_expecting_real_number_encountered_NAN);
            goto RETURN_ERROR;
          }

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
        { 
          retErr = TLOC_ERROR(error::error_obj_file_invalid_vertex_normal);
          goto RETURN_ERROR;
        }

        norm_type norm;
        for (int i = 0; begin != end; ++i, ++begin)
        {
          if (core_str::IsRealNumber(begin->c_str()) == false)
          { 
            retErr = TLOC_ERROR(error::error_obj_file_expecting_real_number_encountered_NAN);
            goto RETURN_ERROR;
          }

          norm[i] = core_utils::CastNumber<f32>( atof(begin->c_str()) );
        }

        tbn_type tbn; tbn.SetCol(2, norm);
        m_vertices.m_tbn.push_back(tbn);
        normalsRecorded = true;
      }
      else if (begin->compare("f") == 0)
      {
        // If no vertices have been recorded, the obj file is not supported
        if (verticesRecorded == false)
        { 
          retErr = TLOC_ERROR(error::error_obj_file_has_no_vertices);
          goto RETURN_ERROR;
        }

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
          { 
            retErr = TLOC_ERROR(error::error_obj_file_face_vertex_has_more_than_three_indices);
            goto RETURN_ERROR; 
          }

          string_array::const_iterator wordTokenBegin = wordTokens.begin();
          string_array::const_iterator wordTokenEnd = wordTokens.end();

          bool onlyVertexNormals = (begin->find("//") != core_str::String::npos);

          for (int i = 0; i < 3 && wordTokenBegin != wordTokenEnd;
            ++i, ++wordTokenBegin)
          {
            if (core_str::IsNumber(wordTokenBegin->c_str()) == false)
            { 
              retErr = TLOC_ERROR(error::error_obj_file_expecting_real_number_encountered_NAN);
              goto RETURN_ERROR;
            }

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
                { 
                  retErr = TLOC_ERROR(error::error_obj_file_face_indexing_non_existent_tex_coord);
                  goto RETURN_ERROR; 
                }

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

      ++itr;
    }

    m_flags.Mark(k_valid);
    retErr = ErrorSuccess;
    return retErr;

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
    return m_vertices.m_tbn.begin();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::const_iterator_norm
    ObjLoader::
    end_norms() const
  {
    return m_vertices.m_tbn.end();
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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ObjLoader::error_type
    ObjLoader::
    GetUnpacked(vert_cont_type& a_vertsOut, size_type a_groupIndex) const
  {
    const ObjGroup& currGroup = m_objects[a_groupIndex];

    if (currGroup.m_posIndices.empty())
    { return TLOC_ERROR(error::error_obj_corrupt_or_invalid); }

    const size_type posIndexSize = currGroup.m_posIndices.size();

    const bool normIndexEmpty = currGroup.m_normIndices.empty();
    const bool tcoordIndexEmpty = currGroup.m_tcoordIndices.empty();

    if (normIndexEmpty == false)
    {
      if (currGroup.m_normIndices.size() != posIndexSize)
      { return TLOC_ERROR(error::error_obj_corrupt_or_invalid); }
    }

    if (tcoordIndexEmpty == false)
    {
      if (currGroup.m_tcoordIndices.size() != posIndexSize)
      { return TLOC_ERROR(error::error_obj_corrupt_or_invalid); }
    }

    for (size_type i = 0; i < posIndexSize; ++i)
    {
      vert_type newVert;
      pos_type  pos = m_vertices.m_pos[currGroup.m_posIndices[i] - 1];

      tbn_type tbn;
      tcoord_type tcoord;

      if (normIndexEmpty == false)
      { tbn = m_vertices.m_tbn[currGroup.m_normIndices[i] - 1]; }

      if (tcoordIndexEmpty == false)
      { tcoord = m_vertices.m_tcoords[currGroup.m_tcoordIndices[i] - 1]; }

      newVert.SetPosition(pos);
      newVert.SetTexCoord(tcoord);
      newVert.SetTBN(tbn);

      a_vertsOut.push_back(newVert);
    }

    typedef vert_type::attrib_3_type::vec_type  vec_type;

    // TODO: should be calculating this when we first parse the OBJ file
    // breakdown of the formula taken from http://gamedev.stackexchange.com/a/68617
    for (size_type i = 0; i < a_vertsOut.size(); i = i+3)
    {
        auto i1 = i, i2 = i+1, i3 = i+2;

        const auto& v1 = a_vertsOut[i1].GetPosition();
        const auto& v2 = a_vertsOut[i2].GetPosition();
        const auto& v3 = a_vertsOut[i3].GetPosition();

        const auto& w1 = a_vertsOut[i1].GetTexCoord();
        const auto& w2 = a_vertsOut[i2].GetTexCoord();
        const auto& w3 = a_vertsOut[i3].GetTexCoord();

        float x1 = v2[0] - v1[0];
        float x2 = v3[0] - v1[0];
        float y1 = v2[1] - v1[1];
        float y2 = v3[1] - v1[1];
        float z1 = v2[2] - v1[2];
        float z2 = v3[2] - v1[2];

        float s1 = w2[0] - w1[0];
        float s2 = w3[0] - w1[0];
        float t1 = w2[1] - w1[1];
        float t2 = w3[1] - w1[1];

        float r = 1.0f / ( s1 * t2 - s2 * t1 );
        vec_type sdir(( t2 * x1 - t1 * x2 ) * r, ( t2 * y1 - t1 * y2 ) * r,
                      ( t2 * z1 - t1 * z2 ) * r);
        vec_type tdir(( s1 * x2 - s2 * x1 ) * r, ( s1 * y2 - s2 * y1 ) * r,
                      ( s1 * z2 - s2 * z1 ) * r);

        for (int j = 0; j < 3; ++j)
        {
          int ij = i + j;
          a_vertsOut[ij].SetTangent(a_vertsOut[ij].GetTangent() + sdir);
          a_vertsOut[ij].SetBiNormal(a_vertsOut[ij].GetBiNormal() + tdir);
        }
    }

    for (size_type i = 0; i < a_vertsOut.size(); i++)
    {
      auto t = a_vertsOut[i].GetTangent();
      auto b = a_vertsOut[i].GetBiNormal();
      auto n = a_vertsOut[i].GetNormal();

      // Gram-Schmidt orthogonalize
      auto newT = ( t - n * n.Dot(t) );
      newT.Normalize();

      // Calculate handedness
      auto handedness = ( n.Cross(newT).Dot(b) < 0.0f ) ? -1.0f : 1.0f;

      auto newB = n.Cross(newT) * handedness;

      a_vertsOut[i].SetTangent(newT);
      a_vertsOut[i].SetBiNormal(newB);
    }

    return ErrorSuccess;
  }

  namespace f_obj_loader {

    obj_loader_sptr
      LoadObjFile (const core_io::Path& a_filePath)
    {
      core_io::FileIO_ReadA objFile(a_filePath);
      if (objFile.Open() != ErrorSuccess)
      { TLOC_LOG_GFX_ERR() << "Unable to open the .obj file."; return nullptr; }

      core_str::String objFileContents;
      objFile.GetContents(objFileContents);

      auto objLoader = core_sptr::MakeShared<ObjLoader>();
      if (objLoader->Init(objFileContents) != ErrorSuccess)
      { TLOC_LOG_GFX_ERR() << "Parsing errors in .obj file."; return nullptr; }

      if (objLoader->GetNumGroups() == 0)
      { TLOC_LOG_GFX_ERR() << "Obj file does not have any objects."; return nullptr; }

      return objLoader;
    }

  };

};};};

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(tl_gfx_med::ObjLoader);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(tl_gfx_med::ObjLoader);