///-------------------------------------------------------------------------
/// @brief WARNING: This class is NOT meant to be used on its own and thus is
///                 not meant to be included
///-------------------------------------------------------------------------

// Try to catch illegal includes
#ifndef TLOC_MEMORY_POOL_H
  #error This class is meant to be used by MemoryPool only
#endif

template <typename T_Elem, typename T_SizeType>
class Wrapper
{
public:
  typedef T_Elem                                      wrapper_value_type;
  typedef T_SizeType                                  index_type;
  typedef this_type                                   parent_type;
  typedef Wrapper<wrapper_value_type, index_type>     wrapper_type;

  template <class T_1, tl_uint T_2,
            class T_3, class T_4> friend class        MemoryPoolIndexed;

  Wrapper();
  Wrapper(const wrapper_type& a_rhs);

  wrapper_value_type&       GetValue();
  const wrapper_value_type& GetValue() const;
  void                      SetValue(const wrapper_value_type& a_value);

  index_type        GetIndex() const;
  bool operator ==(wrapper_type& a_rhs);

private:
  void DoSwap(wrapper_type& a_rhs);

  wrapper_value_type  m_element;
  index_type          m_index;
};