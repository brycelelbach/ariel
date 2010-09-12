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
    BOOST_CHECK_EQUAL(construe_cast<bool>(false), false);
    BOOST_CHECK_EQUAL(construe_cast<bool>(true), true);

    BOOST_CHECK_EQUAL(construe_cast<bool>(0), false);
    BOOST_CHECK_EQUAL(construe_cast<bool>(1), true);
    BOOST_CHECK_EQUAL(construe_cast<bool>(23), true);
    BOOST_CHECK_EQUAL(construe_cast<bool>(-23), true);

    BOOST_CHECK_EQUAL(construe_cast<bool>(0.0f), false);
    BOOST_CHECK_EQUAL(construe_cast<bool>(std::numeric_limits<float>::epsilon()), false);
    BOOST_CHECK_EQUAL(construe_cast<bool>(-std::numeric_limits<float>::epsilon()), false);
    BOOST_CHECK_EQUAL(construe_cast<bool>(1.0f), true);
    BOOST_CHECK_EQUAL(construe_cast<bool>(23.0f), true);
    BOOST_CHECK_EQUAL(construe_cast<bool>(23.0f + std::numeric_limits<float>::epsilon()), true);
    BOOST_CHECK_EQUAL(construe_cast<bool>(23.8f), true);
    BOOST_CHECK_EQUAL(construe_cast<bool>(-23.0f), true);

    BOOST_CHECK_EQUAL(construe_cast<bool>(0.0), false);
    BOOST_CHECK_EQUAL(construe_cast<bool>(std::numeric_limits<double>::epsilon()), false);
    BOOST_CHECK_EQUAL(construe_cast<bool>(-std::numeric_limits<double>::epsilon()), false);
    BOOST_CHECK_EQUAL(construe_cast<bool>(1.0), true);
    BOOST_CHECK_EQUAL(construe_cast<bool>(23.0), true);
    BOOST_CHECK_EQUAL(construe_cast<bool>(23.0 + std::numeric_limits<double>::epsilon()), true);
    BOOST_CHECK_EQUAL(construe_cast<bool>(23.8), true);
    BOOST_CHECK_EQUAL(construe_cast<bool>(-23.0), true);

    BOOST_CHECK_EQUAL(construe_cast<bool>('\0'), false);
    BOOST_CHECK_EQUAL(construe_cast<bool>('\1'), true);
    BOOST_CHECK_EQUAL(construe_cast<bool>('\x17'), true);

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
    BOOST_CHECK_EQUAL(construe_cast<char>(false), '\0');
    BOOST_CHECK_EQUAL(construe_cast<char>(true), '\1');

    BOOST_CHECK_EQUAL(construe_cast<char>(0), '\0');
    BOOST_CHECK_EQUAL(construe_cast<char>(23), '\x17');
    BOOST_CHECK_EQUAL(construe_cast<char>(-23), '\xe9');
    BOOST_CHECK_THROW(construe_cast<char>(std::numeric_limits<char>::min() - 1), bad_construe_cast);
    BOOST_CHECK_THROW(construe_cast<char>(std::numeric_limits<char>::max() + 1), bad_construe_cast);

    BOOST_CHECK_EQUAL(construe_cast<char>(0.0f), '\0');
    BOOST_CHECK_EQUAL(construe_cast<char>(23.0f), '\x17');
    BOOST_CHECK_EQUAL(construe_cast<char>(23.0f + std::numeric_limits<float>::epsilon()), '\x17');
    BOOST_CHECK_EQUAL(construe_cast<char>(23.8f), '\x17');
    BOOST_CHECK_EQUAL(construe_cast<char>(-23.0f), '\xe9');
    BOOST_CHECK_THROW(construe_cast<char>(std::numeric_limits<char>::min() - 1.0f), bad_construe_cast);
    BOOST_CHECK_THROW(construe_cast<char>(std::numeric_limits<char>::max() + 1.0f), bad_construe_cast);

    BOOST_CHECK_EQUAL(construe_cast<char>(0.0), '\0');
    BOOST_CHECK_EQUAL(construe_cast<char>(23.0), '\x17');
    BOOST_CHECK_EQUAL(construe_cast<char>(23.0 + std::numeric_limits<double>::epsilon()), '\x17');
    BOOST_CHECK_EQUAL(construe_cast<char>(23.8), '\x17');
    BOOST_CHECK_EQUAL(construe_cast<char>(-23.0), '\xe9');
    BOOST_CHECK_THROW(construe_cast<char>(std::numeric_limits<char>::min() - 1.0), bad_construe_cast);
    BOOST_CHECK_THROW(construe_cast<char>(std::numeric_limits<char>::max() + 1.0), bad_construe_cast);

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
    BOOST_CHECK_EQUAL(construe_cast<short>(false), static_cast<short>(0));
    BOOST_CHECK_EQUAL(construe_cast<short>(true), static_cast<short>(1));

    BOOST_CHECK_EQUAL(construe_cast<short>(0), static_cast<short>(0));
    BOOST_CHECK_EQUAL(construe_cast<short>(23), static_cast<short>(23));
    BOOST_CHECK_EQUAL(construe_cast<short>(-23), static_cast<short>(-23));
    BOOST_CHECK_THROW(construe_cast<short>(std::numeric_limits<short>::min() - 1), bad_construe_cast);
    BOOST_CHECK_THROW(construe_cast<short>(std::numeric_limits<short>::max() + 1), bad_construe_cast);

    BOOST_CHECK_EQUAL(construe_cast<short>(0.0f), static_cast<short>(0));
    BOOST_CHECK_EQUAL(construe_cast<short>(23.0f), static_cast<short>(23));
    BOOST_CHECK_EQUAL(construe_cast<short>(23.0f + std::numeric_limits<float>::epsilon()), static_cast<short>(23));
    BOOST_CHECK_EQUAL(construe_cast<short>(23.8f), static_cast<short>(23));
    BOOST_CHECK_EQUAL(construe_cast<short>(-23.0f), static_cast<short>(-23));
    BOOST_CHECK_THROW(construe_cast<short>(std::numeric_limits<short>::min() - 1.0f), bad_construe_cast);
    BOOST_CHECK_THROW(construe_cast<short>(std::numeric_limits<short>::max() + 1.0f), bad_construe_cast);

    BOOST_CHECK_EQUAL(construe_cast<short>(0.0), static_cast<short>(0));
    BOOST_CHECK_EQUAL(construe_cast<short>(23.0), static_cast<short>(23));
    BOOST_CHECK_EQUAL(construe_cast<short>(23.0 + std::numeric_limits<double>::epsilon()), static_cast<short>(23));
    BOOST_CHECK_EQUAL(construe_cast<short>(23.8), static_cast<short>(23));
    BOOST_CHECK_EQUAL(construe_cast<short>(-23.0), static_cast<short>(-23));
    BOOST_CHECK_THROW(construe_cast<short>(std::numeric_limits<short>::min() - 1.0), bad_construe_cast);
    BOOST_CHECK_THROW(construe_cast<short>(std::numeric_limits<short>::max() + 1.0), bad_construe_cast);

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
