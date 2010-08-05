//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE karma

#include <boost/construe_cast.hpp>
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>

BOOST_AUTO_TEST_CASE(karma_string) {
    std::string string("1");
    BOOST_CHECK_EQUAL(boost::spirit_cast<std::string>(1), string);
}

BOOST_AUTO_TEST_CASE(karma_wide_string) {
    std::wstring string(L"1");
    BOOST_CHECK(boost::spirit_cast<std::wstring>(1) == string);
}

BOOST_AUTO_TEST_CASE(karma_char_vector) {
    std::vector<char> string(1, '1');
    BOOST_CHECK(boost::spirit_cast<std::vector<char> >(1) == string);
}

BOOST_AUTO_TEST_CASE(karma_wide_char_vector) {
    std::vector<wchar_t> string(1, L'1');
    BOOST_CHECK(boost::spirit_cast<std::vector<wchar_t> >(1) == string);
}
