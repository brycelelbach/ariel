template<class Derived> struct base { };

template<class T> struct derived: base<derived<T> > { };

int main (void) {
  derived<int> instance;
}
