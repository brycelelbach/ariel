#include <cstdio>
#include <boost/mpl/set.hpp>
#include <boost/mpl/has_key.hpp>

int main()
{
  typedef boost::mpl::set<double,float>    reals;
  typedef boost::mpl::set<char,short,int>  ints;

  printf("Is int    in reals: %d\n",boost::mpl::has_key<reals,int>::value);
  printf("Is int    in ints : %d\n",boost::mpl::has_key<ints ,int>::value);
  printf("Is double in reals: %d\n",boost::mpl::has_key<reals,double>::value);
  printf("Is double in ints : %d\n",boost::mpl::has_key<ints ,double>::value);
}
