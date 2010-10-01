template<class T> struct foo { typedef T type; };

extern template struct foo<int>;

