//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE construe_cast

#include <boost/construe_cast.hpp>
#include <boost/test/unit_test.hpp>

#include <string>

using namespace boost;

BOOST_AUTO_TEST_CASE(to_bool) {
    BOOST_CHECK_EQUAL(construe_cast<bool>("false"), false);
    BOOST_CHECK_EQUAL(construe_cast<bool>("true"), true);
    BOOST_CHECK_THROW(construe_cast<bool>(""), bad_construe_cast);
    BOOST_CHECK_THROW(construe_cast<bool>("XXX"), bad_construe_cast);

    BOOST_CHECK_EQUAL(construe_cast<bool>(std::string("false")), false);
    BOOST_CHECK_EQUAL(construe_cast<bool>(std::string("true")), true);
    BOOST_CHECK_THROW(construe_cast<bool>(std::string("")), bad_construe_cast);
    BOOST_CHECK_THROW(construe_cast<bool>(std::string("XXX")), bad_construe_cast);
}

BOOST_AUTO_TEST_CASE(to_char) {
    BOOST_CHECK_EQUAL(construe_cast<char>("\0"), '\0');
    BOOST_CHECK_EQUAL(construe_cast<char>("\x17"), '\x17');
    BOOST_CHECK_THROW(construe_cast<char>(""), bad_construe_cast);
    BOOST_CHECK_THROW(construe_cast<char>("XXX"), bad_construe_cast);

    BOOST_CHECK_EQUAL(construe_cast<char>(std::string("\0", 1)), '\0');
    BOOST_CHECK_EQUAL(construe_cast<char>(std::string("\x17")), '\x17');
    BOOST_CHECK_THROW(construe_cast<char>(std::string("")), bad_construe_cast);
    BOOST_CHECK_THROW(construe_cast<char>(std::string("XXX")), bad_construe_cast);
}

BOOST_AUTO_TEST_CASE(to_short) {
    BOOST_CHECK_EQUAL(construe_cast<short>("0"), static_cast<short>(0));
    BOOST_CHECK_EQUAL(construe_cast<short>("23"), static_cast<short>(23));
    BOOST_CHECK_EQUAL(construe_cast<short>("-23"), static_cast<short>(-23));
    BOOST_CHECK_THROW(construe_cast<short>(""), bad_construe_cast);
    BOOST_CHECK_THROW(construe_cast<short>("XXX"), bad_construe_cast);

    BOOST_CHECK_EQUAL(construe_cast<short>(std::string("0")), static_cast<short>(0));
    BOOST_CHECK_EQUAL(construe_cast<short>(std::string("23")), static_cast<short>(23));
    BOOST_CHECK_EQUAL(construe_cast<short>(std::string("-23")), static_cast<short>(-23));
    BOOST_CHECK_THROW(construe_cast<short>(std::string("")), bad_construe_cast);
    BOOST_CHECK_THROW(construe_cast<short>(std::string("XXX")), bad_construe_cast);
}
