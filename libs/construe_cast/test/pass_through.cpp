//              Copyright Jeroen Habraken 2010.
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE pass_through

#include <boost/construe_cast.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(pass_through) {
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(1), 1);
}

BOOST_AUTO_TEST_CASE(pass_through_convertible) {
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(1.0), 1);
}

BOOST_AUTO_TEST_CASE(pass_through_downcast) {
    BOOST_CHECK_EQUAL(boost::construe_cast<double>(1), 1.0);
}
