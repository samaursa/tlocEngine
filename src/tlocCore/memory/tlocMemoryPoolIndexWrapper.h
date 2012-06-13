///-------------------------------------------------------------------------
/// @brief WARNING: This class is NOT meant to be used on its own and thus is
///                 not meant to be included
///-------------------------------------------------------------------------

template <typename T_Elem, typename T_SizeType>
class Wrapper
{
public:
  typedef T_Elem                                      wrapper_value_type;
  typedef T_SizeType                                  index_type;
  typedef this_type                                   parent_type;
  typedef Wrapper<wrapper_value_type, index_type>             wrapper_type;

  template <class T_1, tl_uint T_2,
  class T_3, class T_4> friend class        MemoryPoolIndex;

  Wrapper();
  Wrapper(const wrapper_type& a_rhs);

  wrapper_value_type&       GetElement();
  const wrapper_value_type& GetElement() const;

  index_type        GetIndex() const;
  bool operator ==(wrapper_type& a_rhs);

private:
  void DoSwap(wrapper_type& a_rhs);

  wrapper_value_type  m_element;
  index_type          m_index;
};