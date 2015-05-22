#ifndef TLOC_CONTAINER_UTILS_H
#define TLOC_CONTAINER_UTILS_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/tlocAssert.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/utilities/tlocType.h>

namespace tloc { namespace core { namespace utils {

  // -----------------------------------------------------------------------
  // macros for quickly exposing begin/end/size/empty of containers

#define TLOC_DECL_AND_DEF_CONTAINER_BEGIN_CONST(_suffix_, _container_)\
  auto begin ## _suffix_(int = 0) const -> decltype(_container_.begin()) \
  { return _container_.begin(); }

#define TLOC_DECL_AND_DEF_CONTAINER_END_CONST(_suffix_, _container_)\
  auto  end ## _suffix_(int = 0) const -> decltype(_container_.end()) \
  { return _container_.end(); }

#define TLOC_DECL_AND_DEF_CONTAINER_BEGIN(_suffix_, _container_)\
  auto begin ## _suffix_(int = 0) -> decltype(_container_.begin()) \
  { return _container_.begin(); }

#define TLOC_DECL_AND_DEF_CONTAINER_END(_suffix_, _container_)\
  auto end ## _suffix_(int = 0) -> decltype(_container_.end()) \
  { return _container_.end(); }

#define TLOC_DECL_AND_DEF_CONTAINER_SIZE(_suffix_, _container_)\
  auto size ## _suffix_(int = 0) const -> decltype(_container_.size()) \
  { return _container_.size(); }

#define TLOC_DECL_AND_DEF_CONTAINER_EMPTY(_suffix_, _container_)\
  bool empty ## _suffix_(int = 0) const { return _container_.empty(); }

#define TLOC_DECL_AND_DEF_CONTAINER_BEGIN_END_CONST(_suffix_, _container_)\
  TLOC_DECL_AND_DEF_CONTAINER_BEGIN_CONST(_suffix_, _container_);\
  TLOC_DECL_AND_DEF_CONTAINER_END_CONST(_suffix_, _container_)

#define TLOC_DECL_AND_DEF_CONTAINER_BEGIN_END(_suffix_, _container_)\
  TLOC_DECL_AND_DEF_CONTAINER_BEGIN(_suffix_, _container_);\
  TLOC_DECL_AND_DEF_CONTAINER_END(_suffix_, _container_)

#define TLOC_DECL_AND_DEF_CONTAINER_BEGIN_END_ALL(_suffix_, _container_)\
  TLOC_DECL_AND_DEF_CONTAINER_BEGIN_END_CONST(_suffix_, _container_);\
  TLOC_DECL_AND_DEF_CONTAINER_BEGIN_END(_suffix_, _container_)

#define TLOC_DECL_AND_DEF_CONTAINER_SIZE_AND_EMPTY(_suffix_, _container_)\
  TLOC_DECL_AND_DEF_CONTAINER_EMPTY(_suffix_, _container_);\
  TLOC_DECL_AND_DEF_CONTAINER_SIZE(_suffix_, _container_)

#define TLOC_DECL_AND_DEF_CONTAINER_CONST_METHODS(_suffix_, _container_)\
  TLOC_DECL_AND_DEF_CONTAINER_BEGIN_END_CONST(_suffix_, _container_);\
  TLOC_DECL_AND_DEF_CONTAINER_SIZE_AND_EMPTY(_suffix_, _container_)

#define TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_suffix_, _container_)\
  TLOC_DECL_AND_DEF_CONTAINER_BEGIN_END(_suffix_, _container_);\
  TLOC_DECL_AND_DEF_CONTAINER_BEGIN_END_CONST(_suffix_, _container_);\
  TLOC_DECL_AND_DEF_CONTAINER_SIZE_AND_EMPTY(_suffix_, _container_)

  //------------------------------------------------------------------------
  // Array size counter (raw and complex)

  template <typename T, tl_size T_Size>
  tl_size ArraySize(T (&)[T_Size]) { return T_Size; }

  template <typename T, tl_size T_Size>
  tl_size ArraySize(const T (&)[T_Size]) { return T_Size; }

  template <typename T_Container>
  typename T_Container::size_type ArraySize(T_Container& a_container)
  { return a_container.size(); }

  template <typename T_Container>
  typename T_Container::size_type ArraySize(const T_Container& a_container)
  { return a_container.size(); }

  // -----------------------------------------------------------------------
  // Compile time index and coord calculator

  // ///////////////////////////////////////////////////////////////////////
  // Index2D

  template <tl_int T_SizeX  , tl_int T_SizeY,
            tl_int T_CoordX = -1, tl_int T_CoordY = -1>
  struct Index2D
  {
    TLOC_STATIC_ASSERT(T_CoordX < T_SizeX, Index_is_out_of_bounds);
    TLOC_STATIC_ASSERT(T_CoordY < T_SizeY, Index_is_out_of_bounds);

    enum { k_value = T_CoordX + T_SizeX * T_CoordY };
  };

  template <tl_int T_SizeX, tl_int T_SizeY>
  struct Index2D<T_SizeX, T_SizeY, -1, -1>
  {
    static tl_int Get(tl_int x, tl_int y)
    {
      TLOC_ASSERT(x < T_SizeX, "Index x is out of bounds");
      TLOC_ASSERT(y < T_SizeY, "Index y is out of bounds");

      return x + T_SizeX * y;
    }
  };

  template <typename T>
  tl_int
    GetIndex(core_ds::Tuple<T, 2> a_gridSize,
             core_ds::Tuple<T, 2> a_coord)
  {
    TLOC_ASSERT(a_coord[0] < a_gridSize[0], "Index x is out of bounds");
    TLOC_ASSERT(a_coord[1] < a_gridSize[1], "Index y is out of bounds");

    return core_utils::CastNumber<tl_int>
      (a_coord[0] + a_gridSize[0] * a_coord[1]);
  }

  // ///////////////////////////////////////////////////////////////////////
  // Index3D

  template <tl_int T_SizeX  , tl_int T_SizeY  , tl_int T_SizeZ,
            tl_int T_CoordX = -1, tl_int T_CoordY = -1, tl_int T_CoordZ = -1>
  struct Index3D
  {
    TLOC_STATIC_ASSERT(T_CoordX < T_SizeX, Index_is_out_of_bounds);
    TLOC_STATIC_ASSERT(T_CoordY < T_SizeY, Index_is_out_of_bounds);
    TLOC_STATIC_ASSERT(T_CoordZ < T_SizeZ, Index_is_out_of_bounds);

    enum { k_value = T_CoordX + T_SizeX * T_CoordY + T_SizeX * T_SizeY * T_CoordZ };
  };

  template <tl_int T_SizeX, tl_int T_SizeY, tl_int T_SizeZ>
  struct Index3D<T_SizeX, T_SizeY, T_SizeZ, -1, -1, -1>
  {
    static tl_int Get(tl_int x, tl_int y, tl_int z)
    {
      TLOC_ASSERT(x < T_SizeX, "Index x is out of bounds");
      TLOC_ASSERT(y < T_SizeY, "Index y is out of bounds");
      TLOC_ASSERT(z < T_SizeZ, "Index y is out of bounds");

      return x + T_SizeX * y + T_SizeX * T_SizeY * z;
    }
  };

  template <typename T>
  tl_int
    GetIndex(core_ds::Tuple<T, 3> a_gridSize,
             core_ds::Tuple<T, 3> a_coord)
  {
    TLOC_ASSERT(a_coord[0] < a_gridSize[0], "Index x is out of bounds");
    TLOC_ASSERT(a_coord[1] < a_gridSize[1], "Index y is out of bounds");
    TLOC_ASSERT(a_coord[2] < a_gridSize[2], "Index y is out of bounds");

    return core_utils::
      CastNumber<tl_int>(a_coord[0] +
                         a_gridSize[0] * a_coord[1] +
                         a_gridSize[0] * a_gridSize[1] * a_coord[2]);
  }

  // ///////////////////////////////////////////////////////////////////////
  // Coord2D

  template <tl_int T_SizeX, tl_int T_SizeY, tl_int T_Index = -1>
  struct Coord2D
  {
    TLOC_STATIC_ASSERT(T_Index < T_SizeX * T_SizeY, Index_out_of_bounds);

    enum { k_x = T_Index % T_SizeX };
    enum { k_y = (T_Index / T_SizeX) % T_SizeY};
  };

  template <tl_int T_SizeX, tl_int T_SizeY>
  struct Coord2D<T_SizeX, T_SizeY, -1>
  {
    static core_ds::Tuple2s Get(tl_int a_index)
    {
      TLOC_ASSERT(a_index < T_SizeX * T_SizeY, "Index out of bounds");
      return core_ds::MakeTuple(a_index % T_SizeX,
                                (a_index / T_SizeX) % T_SizeY);
    }

    template <typename T>
    static core_ds::Tuple<T, 2> Get(T a_index)
    {
      TLOC_ASSERT(a_index < T_SizeX * T_SizeY, "Index out of bounds");
      return core_ds::MakeTuple<T>(a_index % T_SizeX,
                                   (a_index / T_SizeX) % T_SizeY);
    }
  };

  template <typename T>
  core_ds::Tuple<T, 2>
    GetCoord(core_ds::Tuple<T, 2> a_gridSize,
             T a_index)
  {
    TLOC_ASSERT(a_index < a_gridSize[0] * a_gridSize[1], "Index out of bounds");
    return core_ds::MakeTuple(a_index % a_gridSize[0],
                              (a_index / a_gridSize[0]) % a_gridSize[1]);
  }

  // ///////////////////////////////////////////////////////////////////////
  // Coord3D

  template <tl_int T_SizeX, tl_int T_SizeY, tl_int T_SizeZ, tl_int T_Index = -1>
  struct Coord3D
  {
    TLOC_STATIC_ASSERT(T_Index < T_SizeX * T_SizeY * T_SizeZ, Index_out_of_bounds);

    enum { k_x = T_Index % T_SizeX };
    enum { k_y = ( T_Index / T_SizeX ) % T_SizeY };
    enum { k_z = ( ( T_Index / T_SizeX) / T_SizeY ) % T_SizeZ };
  };

  template <tl_int T_SizeX, tl_int T_SizeY, tl_int T_SizeZ>
  struct Coord3D<T_SizeX, T_SizeY, T_SizeZ, -1>
  {
    static core_ds::Tuple3s Get(tl_int a_index)
    {
      TLOC_ASSERT(a_index < T_SizeX * T_SizeY * T_SizeZ, "Index out of bounds");
      return core_ds::MakeTuple(a_index % T_SizeX,
                                (a_index / T_SizeX) % T_SizeY,
                                ((a_index / T_SizeX) / T_SizeY) % T_SizeZ);
    }

    template <typename T>
    static core_ds::Tuple<T, 3> Get(T a_index)
    {
      TLOC_ASSERT(a_index < T_SizeX * T_SizeY * T_SizeZ, "Index out of bounds");
      return core_ds::MakeTuple<T>(a_index % T_SizeX,
                                   (a_index / T_SizeX) % T_SizeY,
                                   ((a_index / T_SizeX) / T_SizeY) % T_SizeZ);
    }
  };

  template <typename T>
  core_ds::Tuple<T, 3>
    GetCoord(core_ds::Tuple<T, 3> a_gridSize,
             T a_index)
  {
      TLOC_ASSERT(a_index < a_gridSize[0] * a_gridSize[1] * a_gridSize[2],
                  "Index out of bounds");
      return core_ds::MakeTuple<T>
        (a_index % a_gridSize[0],
         (a_index / a_gridSize[0]) % a_gridSize[1],
         ((a_index / a_gridSize[0]) / a_gridSize[1]) % a_gridSize[2]);
  }

  // -----------------------------------------------------------------------
  // Runtime index calculator



};};};


#endif