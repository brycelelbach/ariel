//              Copyright Jeroen Habraken 2010.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE pass_through

#include <boost/test/unit_test.hpp>
#include <boost/spirit_cast.hpp>

BOOST_AUTO_TEST_CASE(pass_through) {
    BOOST_CHECK_EQUAL(boost::spirit_cast<int>(1.0), 1);
}

BOOST_AUTO_TEST_CASE(pass_through_downcast) {
    BOOST_CHECK_EQUAL(boost::spirit_cast<double>(1), 1.0);
}
