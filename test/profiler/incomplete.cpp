template<typename T> struct a;

template<typename T> struct b { };

int main (void) {
  b<a<int> > instance;
}
