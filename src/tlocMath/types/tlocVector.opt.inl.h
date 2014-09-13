#ifndef TLOC_VECTOR_N_OPT_INL
#define TLOC_VECTOR_N_OPT_INL

#ifndef TLOC_VECTOR_N_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocAssert.h>
#include <tlocCore/data_structures/tlocTuple.inl.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocMath/tlocMath.inl.h>

namespace tloc {
  namespace math {
    namespace types {

      namespace
      {
        template <typename T>
        TL_FI T GetInvSqrt(T a_value, p_vector::accurate)
        {
          return math::InvSqrt(a_value);
        }

        template <typename T>
        TL_FI T GetInvSqrt(T a_value, p_vector::fast)
        {
          return math::FastInvSqrt(a_value);
        }

        template <typename T>
        TL_FI T GetSqrt(T a_value, p_vector::accurate)
        {
          return math::Sqrt(a_value);
        }

        template <typename T>
        TL_FI T GetSqrt(T a_value, p_vector::fast)
        {
          return math::InvSqrt(a_value);
        }
      }

      //////////////////////////////////////////////////////////////////////////
      // Vector_T<N>

      ////////////////////////////////////////////////////////////////////////
      // Template Macros

#define VECTOR_TEMP typename T, tl_size T_Size
#define VECTOR_PARAMS T, T_Size
#define VECTOR_TYPE typename Vector_TI<T, T_Size>

      //////////////////////////////////////////////////////////////////////////
      // Misc Macros

      // Note that we have tl_int and not tl_size for the iteration. This is because
      // the [] operator only accepts integers, so we have no choice (either that
      // or we cast the tl_size to tl_int, which defeats the purpose anyway)
#define ITERATE_VECTOR for (tl_int i = 0; i < T_Size; ++i)

      //------------------------------------------------------------------------
      // Constructors

      template <VECTOR_TEMP>
      Vector_TI<VECTOR_PARAMS>::
        Vector_TI()
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      Vector_TI<VECTOR_PARAMS>::
        Vector_TI(value_type a_value)
        : base_type(a_value)
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      template <typename T_ArrayType>
      Vector_TI<VECTOR_PARAMS>::
        Vector_TI(const T_ArrayType(&aArray)[T_Size])
        : base_type(aArray)
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      Vector_TI<VECTOR_PARAMS>::
        Vector_TI(const core::data_structs::Variadic<T, T_Size>& a_vars)
        : base_type(a_vars)
      { }

      //------------------------------------------------------------------------
      // Modifiers

      template <VECTOR_TEMP>
      void
        Vector_TI<VECTOR_PARAMS>::
        MakeZero()
      {
        Set(0);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        Inverse() const
      {
        this_type inv(*this);
        ITERATE_VECTOR
        {
          inv.m_values[i] = -inv.m_values[i];
        }

        return inv;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      void
        Vector_TI<VECTOR_PARAMS>::
        Inverse(const this_type& a_vector)
      {
        base_type::operator=( a_vector.Inverse() );
      }

      //------------------------------------------------------------------------
      // Math Operations

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        Add(const this_type& a_vector) const
      {
        this_type temp(*this);

        ITERATE_VECTOR
        {
          temp.m_values[i] += a_vector[i];
        }

        return temp;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      void
        Vector_TI<VECTOR_PARAMS>::
        Add(const this_type& a_vector1, const this_type& a_vector2)
      {
        *this = a_vector1.Add(a_vector2);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        Sub(const this_type& a_vector) const
      {
        this_type temp(*this);

        ITERATE_VECTOR
        {
          temp.m_values[i] -= a_vector[i];
        }

        return temp;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      void
        Vector_TI<VECTOR_PARAMS>::
        Sub(const this_type& a_vector1, const this_type& a_vector2)
      {
        *this = a_vector1.Sub(a_vector2);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        Mul(const this_type& a_vector) const
      {
        this_type temp(*this);

        ITERATE_VECTOR
        {
          temp.m_values[i] *= a_vector[i];
        }

        return temp;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      void Vector_TI<VECTOR_PARAMS>::
        Mul(const this_type& a_vector1, const this_type& a_vector2)
      {
        *this = a_vector1.Mul(a_vector2);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        Mul(const value_type a_real) const
      {
        this_type temp(*this);

        ITERATE_VECTOR
        {
          temp.m_values[i] *= a_real;
        }

        return temp;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      void
        Vector_TI<VECTOR_PARAMS>::
        Mul(const this_type& a_vector, const value_type a_real)
      {
        ITERATE_VECTOR
        {
          this->m_values[i] = a_vector.m_values[i] * a_real;
        }
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        Div(const this_type& a_vector) const
      {
        this_type temp(*this);

        ITERATE_VECTOR
        {
          temp.m_values[i] /= a_vector[i];
        }

        return temp;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      void
        Vector_TI<VECTOR_PARAMS>::
        Div(const this_type& a_vector1, const this_type& a_vector2)
      {
        *this = a_vector1.Div(a_vector2);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        Div(const value_type a_real) const
      {
        this_type temp(*this);

        ITERATE_VECTOR
        {
          temp.m_values[i] /= a_real;
        }

        return temp;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      void
        Vector_TI<VECTOR_PARAMS>::
        Div(const this_type& a_vector, const value_type a_real)
      {
        *this = a_vector.Div(a_real);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::value_type
        Vector_TI<VECTOR_PARAMS>::
        LengthSquared() const
      {
        T lengthSq = 0;

        ITERATE_VECTOR
        {
          lengthSq += ( this->m_values[i] * this->m_values[i] );
        }

        return lengthSq;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::value_type
        Vector_TI<VECTOR_PARAMS>::
        Length() const
      {
        return DoLength<p_vector::accurate>(*this);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      template <typename T_Accuracy>
      VECTOR_TYPE::value_type
        Vector_TI<VECTOR_PARAMS>::
        DoLength(const this_type& a_vector) const
      {
        value_type length = a_vector.LengthSquared();
        return GetSqrt(length, T_Accuracy());
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::value_type
        Vector_TI<VECTOR_PARAMS>::
        Normalize()
      {
        return Normalize<p_vector::accurate>(*this);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::value_type
        Vector_TI<VECTOR_PARAMS>::
        Normalize(const this_type& a_vector)
      {
        return Normalize<p_vector::accurate>(a_vector);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      template <typename T_Accuracy>
      VECTOR_TYPE::value_type
        Vector_TI<VECTOR_PARAMS>::
        DoNorm(const this_type& a_vector)
      {
        value_type dblLength = a_vector.LengthSquared();

        TLOC_ASSERT_LOW_LEVEL(math::IsEqual<value_type>(dblLength, 0) == false,
                              "Divide by zero!");

        value_type invLength = GetInvSqrt(dblLength, T_Accuracy());
        ITERATE_VECTOR
        {
          this->m_values[i] = a_vector[i] * invLength;
        }

        return (T) 1 / invLength;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::value_type
        Vector_TI<VECTOR_PARAMS>::
        Distance(const this_type& a_vector) const
      {
        return DoDistance<p_vector::accurate>(a_vector);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      template <typename T_Accuracy>
      VECTOR_TYPE::value_type
        Vector_TI<VECTOR_PARAMS>::
        DoDistance(const this_type& a_vector) const
      {
        this_type lTemp = *this;
        lTemp = lTemp.Sub(a_vector);

        value_type length = lTemp.DoLength<T_Accuracy>(lTemp);
        return length;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::value_type
        Vector_TI<VECTOR_PARAMS>::
        DistanceSquared(const this_type& a_vector) const
      {
        this_type lTemp = Sub(a_vector);

        value_type lengthSq = lTemp.LengthSquared();
        return lengthSq;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::value_type
        Vector_TI<VECTOR_PARAMS>::
        Dot(const this_type& a_vector) const
      {
        value_type dotProd = 0;

        ITERATE_VECTOR
        {
          dotProd += this->m_values[i] * a_vector[i];
        }

        return dotProd;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::value_type
        Vector_TI<VECTOR_PARAMS>::
        DotAbs(const this_type& a_vector) const
      {
        value_type dotProd = Dot(a_vector);
        return math::Abs(dotProd);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      bool
        Vector_TI<VECTOR_PARAMS>::
        IsParallel(const this_type& a_vector) const
      { return IsEqual<value_type>(math::Abs(Dot(a_vector)), 1.0f); }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        Midpoint(const this_type& a_vector) const
      {
        this_type temp(*this);

        ITERATE_VECTOR
        {
          temp.m_values[i] = ( temp.m_values[i] + a_vector[i] ) * ( value_type )0.5;
        }

        return temp;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      void
        Vector_TI<VECTOR_PARAMS>::
        Midpoint(const this_type& a_vector1, const this_type& a_vector2)
      {
        *this = a_vector1.Midpoint(a_vector2);
      }

      //------------------------------------------------------------------------
      // Operators

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        operator+ ( const this_type& a_vector ) const
      {
        return Add(a_vector);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        operator- ( const this_type& a_vector ) const
      {
        return Sub(a_vector);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        operator* ( value_type a_value ) const
      {
        return Mul(a_value);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        operator* ( const this_type& a_vector ) const
      {
        return Mul(a_vector);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        operator/ ( value_type a_value ) const
      {
        return Div(a_value);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type
        Vector_TI<VECTOR_PARAMS>::
        operator/ ( const this_type& a_vector ) const
      {
        return Div(a_vector);
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type&
        Vector_TI<VECTOR_PARAMS>::
        operator+= ( const this_type& a_vector )
      {
        Add(*this, a_vector);
        return ( *this );
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type&
        Vector_TI<VECTOR_PARAMS>::
        operator-= ( const this_type& a_vector )
      {
        Sub(*this, a_vector);
        return ( *this );;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type&
        Vector_TI<VECTOR_PARAMS>::
        operator*= ( value_type a_value )
      {
        Mul(*this, a_value);
        return *this;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type&
        Vector_TI<VECTOR_PARAMS>::
        operator*= ( const this_type& a_vector )
      {
        Mul(*this, a_vector);
        return *this;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type&
        Vector_TI<VECTOR_PARAMS>::
        operator/= ( value_type a_value )
      {
        Div(*this, a_value);
        return ( *this );
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      VECTOR_TYPE::this_type&
        Vector_TI<VECTOR_PARAMS>::
        operator/=( const this_type& a_vector )
      {
        Div(*this, a_vector);
        return ( *this );
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      bool
        Vector_TI<VECTOR_PARAMS>::
        operator==( const this_type& a_vector ) const
      {
        ITERATE_VECTOR
        {
          if (!math::IsEqual(this->m_values[i], a_vector[i])) return false;
        }

        return true;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      bool
        Vector_TI<VECTOR_PARAMS>::
        operator!=( const this_type& a_vector ) const
      {
        return !operator==( a_vector );
      }

      //------------------------------------------------------------------------
      // Checks

      template <VECTOR_TEMP>
      bool
        Vector_TI<VECTOR_PARAMS>::
        IsValid()
      {
        ITERATE_VECTOR
        {
          if (math::IsNaN(this->m_values[i])) { return false; }
        }

        return true;
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      template <VECTOR_TEMP>
      bool
        Vector_TI<VECTOR_PARAMS>::
        IsZero()
      {
        ITERATE_VECTOR
        {
          if (!math::IsEqual<value_type>(this->m_values[i], 0)) { return false; }
        }

        return true;
      }

    };
  };
};

#endif