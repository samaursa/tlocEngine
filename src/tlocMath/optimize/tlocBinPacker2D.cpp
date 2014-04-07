#include "tlocBinPacker2D.h"

namespace tloc { namespace math { namespace optimize {

  BinPacker2D::dim_type
    BinPacker2D::s_maxDimensions = core_ds::MakeTuple(8192, 8192);

  // ///////////////////////////////////////////////////////////////////////
  // BinPacker2D

  BinPacker2D::
    BinPacker2D()
    : m_bimDimensions(core_ds::MakeTuple(32, 32))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BinPacker2D::
    BinPacker2D(dim_type a_startingDimension)
    : m_bimDimensions(a_startingDimension)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    BinPacker2D::
    Add(const rect_user_pair& a_pair)
  {
    m_bin.push_back(a_pair);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    BinPacker2D::
    SetBin(const rect_user_cont& a_pairs)
  {
    m_bin = a_pairs;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BinPacker2D::error_type
    BinPacker2D::
    Process()
  {
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BinPacker2D::error_type
    BinPacker2D::
    Process(dim_type )
  {
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BinPacker2D::const_iterator 
    BinPacker2D::
    begin() const
  { return m_bin.begin(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BinPacker2D::const_iterator 
    BinPacker2D::
    end() const
  { return m_bin.end(); }

};};};

using namespace tloc::math::optimize;

#include <tlocCore/containers/tlocArray.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(BinPacker2D::rect_user_pair);