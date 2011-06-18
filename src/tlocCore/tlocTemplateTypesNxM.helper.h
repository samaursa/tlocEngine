// Used only by tlocTemplateTypesNxM.h

template CLASS_NAME<TYPE, ROW_NUM, 1>;
template CLASS_NAME<TYPE, ROW_NUM, 2>;
template CLASS_NAME<TYPE, ROW_NUM, 3>;
template CLASS_NAME<TYPE, ROW_NUM, 4>;
template CLASS_NAME<TYPE, ROW_NUM, 5>;
template CLASS_NAME<TYPE, ROW_NUM, 6>;
template CLASS_NAME<TYPE, ROW_NUM, 7>;
template CLASS_NAME<TYPE, ROW_NUM, 8>;
template CLASS_NAME<TYPE, ROW_NUM, 9>;

#ifdef TLOC_TEMPLATE_TYPES_SIZE_15
template CLASS_NAME<TYPE, ROW_NUM, 10>;
template CLASS_NAME<TYPE, ROW_NUM, 11>;
template CLASS_NAME<TYPE, ROW_NUM, 12>;
template CLASS_NAME<TYPE, ROW_NUM, 13>;
template CLASS_NAME<TYPE, ROW_NUM, 14>;
template CLASS_NAME<TYPE, ROW_NUM, 15>;

  #ifdef TLOC_TEMPLATE_TYPES_SIZE_20
    template CLASS_NAME<TYPE, ROW_NUM, 16>;
    template CLASS_NAME<TYPE, ROW_NUM, 17>;
    template CLASS_NAME<TYPE, ROW_NUM, 18>;
    template CLASS_NAME<TYPE, ROW_NUM, 19>;
    template CLASS_NAME<TYPE, ROW_NUM, 20>;

  #endif // TLOC_TEMPLATE_TYPES_SIZE_20
#endif // TLOC_TEMPLATE_TYPES_SIZE_15