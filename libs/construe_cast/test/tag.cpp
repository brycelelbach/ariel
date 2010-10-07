//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE tag

#include <boost/construe_cast.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost;

BOOST_AUTO_TEST_CASE(bin) {
    BOOST_CHECK_EQUAL(
        (construe_cast<unsigned int, construe::tag::bin>(std::string("10111"))),
        23U);

    BOOST_CHECK_THROW(
        (construe_cast<unsigned int, construe::tag::bin>(std::string("XXX"))),
        bad_construe_cast);

    BOOST_CHECK_EQUAL(
        (construe_cast<std::string, construe::tag::bin>(23)),
        std::string("10111"));
}

BOOST_AUTO_TEST_CASE(oct) {
    BOOST_CHECK_EQUAL(
        (construe_cast<unsigned int, construe::tag::oct>(std::string("27"))),
        23U);

    BOOST_CHECK_THROW(
        (construe_cast<unsigned int, construe::tag::oct>(std::string("XXX"))),
        bad_construe_cast);

    BOOST_CHECK_EQUAL(
        (construe_cast<std::string, construe::tag::oct>(23)),
        std::string("27"));
}

BOOST_AUTO_TEST_CASE(hex) {
    BOOST_CHECK_EQUAL(
        (construe_cast<unsigned int, construe::tag::hex>(std::string("17"))),
        23U);

    BOOST_CHECK_THROW(
        (construe_cast<unsigned int, construe::tag::hex>(std::string("XXX"))),
        bad_construe_cast);

    BOOST_CHECK_EQUAL(
        (construe_cast<std::string, construe::tag::hex>(23)),
        std::string("17"));
}
