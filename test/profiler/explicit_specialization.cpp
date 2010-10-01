template<class T> struct foo { typedef T type; };

template<> struct foo<int> { typedef int type; };

