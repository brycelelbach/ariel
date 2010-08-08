//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE qi

#include <boost/construe_cast.hpp>
#include <boost/test/unit_test.hpp>

#include <string>

BOOST_AUTO_TEST_CASE(qi_char_const_array) {
    char const string[1] = {'1'};
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(string), 1);
}

BOOST_AUTO_TEST_CASE(qi_char_array) {
    char string[1] = {'1'};
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(string), 1);
}

BOOST_AUTO_TEST_CASE(qi_char_const_pointer) {
    char const *string = "1";
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(string), 1);
}

BOOST_AUTO_TEST_CASE(qi_char_pointer) {
    char *string = const_cast<char *>("1");
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(string), 1);
}

BOOST_AUTO_TEST_CASE(qi_string_const) {
    std::string const string("1");
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(string), 1);
}

BOOST_AUTO_TEST_CASE(qi_string) {
    std::string string("1");
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(string), 1);
}

BOOST_AUTO_TEST_CASE(qi_wide_char_const_array) {
    wchar_t const string[1] = {L'1'};
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(string), 1);
}

BOOST_AUTO_TEST_CASE(qi_wide_char_array) {
    wchar_t string[1] = {L'1'};
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(string), 1);
}

BOOST_AUTO_TEST_CASE(qi_wide_char_const_pointer) {
    wchar_t const *string = L"1";
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(string), 1);
}

BOOST_AUTO_TEST_CASE(qi_wide_char_pointer) {
    wchar_t *string = const_cast<wchar_t *>(L"1");
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(string), 1);
}

BOOST_AUTO_TEST_CASE(qi_wide_string_const) {
    std::wstring const string(L"1");
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(string), 1);
}

BOOST_AUTO_TEST_CASE(qi_wide_string) {
    std::wstring string(L"1");
    BOOST_CHECK_EQUAL(boost::construe_cast<int>(string), 1);
}
