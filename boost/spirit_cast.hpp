//              Copyright Jeroen Habraken 2010.
// 
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_CAST_HPP
#define BOOST_SPIRIT_CAST_HPP

#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_string_traits.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

#include <string>
#include <typeinfo>

namespace boost {

    class bad_spirit_cast
        : std::bad_cast { };

    namespace detail {

        template <typename String>
        struct spirit_cast_string;

        template <typename CharT, std::size_t N>
        struct spirit_cast_string<CharT [N]> {
            typedef CharT * iterator;
            typedef CharT const * const_iterator;

            spirit_cast_string(CharT const (&value)[N])
                : value_(value) { }

            inline const_iterator const
            begin() {
                return &value_[0];
            }

            inline const_iterator const
            end() {
                return &value_[0] + N;
            }

            private:
                CharT const (&value_)[N];
        };

        template <>
        struct spirit_cast_string<char const *> {
            typedef char * iterator;
            typedef char const * const_iterator;

            spirit_cast_string(char const * value)
                : value_(value) { }

            inline const_iterator const
            begin() {
                return value_;
            }

            inline const_iterator const
            end() {
                return value_ + strlen(value_);
            }

            private:
                char const * value_;
        };

        template <>
        struct spirit_cast_string<char *>
            : spirit_cast_string<char const *> {
            spirit_cast_string(char * value)
                : spirit_cast_string<char const *>(value) { }
        };

        template <>
        struct spirit_cast_string<wchar_t const *> {
            typedef wchar_t * iterator;
            typedef wchar_t const * const_iterator;

            spirit_cast_string(wchar_t const * value)
                : value_(value) { }

            inline const_iterator const
            begin() {
                return value_;
            }

            inline const_iterator const
            end() {
                return value_ + wcslen(value_);
            }

            private:
                wchar_t const * value_;
        };

        template <>
        struct spirit_cast_string<wchar_t *>
            : spirit_cast_string<wchar_t const *> {
            spirit_cast_string(wchar_t * value)
                : spirit_cast_string<wchar_t const *>(value) { }
        };

        template <typename CharT, typename Traits, typename Allocator>
        struct spirit_cast_string<std::basic_string<CharT, Traits, Allocator> > {
            private:
                typedef std::basic_string<CharT, Traits, Allocator> string_t;

            public:
                typedef typename string_t::iterator iterator;
                typedef typename string_t::const_iterator const_iterator;

                spirit_cast_string(string_t const & value)
                    : value_(value) { }

                inline const_iterator const
                begin() {
                    return value_.begin();
                }

                inline const_iterator const
                end() {
                    return value_.end();
                }

            private:
                string_t const & value_;
        };

    }  // namespace detail

    namespace detail {

        template <typename Target, typename Source, typename Enable = void>
        struct spirit_cast;

        // pass-through when the source type is convertible to target type
        template <typename Target, typename Source>
        struct spirit_cast<Target, Source, typename boost::enable_if<
            boost::is_convertible<Target, Source>
                >::type> {
            static inline Target const
            call(Source const & source) {
                return static_cast<Target>(source);
            }
        };

        // boost::spirit::qi based conversion from a string to target type
        template <typename Target, typename Source>
        struct spirit_cast<Target, Source, typename boost::enable_if<
            boost::mpl::and_<
                boost::spirit::traits::is_string<Source>,
                boost::mpl::not_<
                    boost::is_same<Target, Source>
                >
            >
                >::type> {
            static inline Target const
            call(Source const & source) {
                Target target;

                spirit_cast_string<Source> expression(source);

                typedef typename spirit_cast_string<Source>::const_iterator iterator_t;
                iterator_t iterator = expression.begin(), end = expression.end();

                bool result = boost::spirit::qi::parse(
                    iterator, end, target);

                if (!result)
                    std::cout << "False" << std::endl;

                if (!result || !((iterator < end && *iterator == 0) || iterator == end))
                    throw boost::bad_spirit_cast();

                return target;
            }
        };

    }  // namespace detail

    template <typename Target, typename Source>
    inline Target const
    spirit_cast(Source const & source) {
        return boost::detail::spirit_cast<Target, Source>::call(source);
    }

}  // namespace boost

#endif  // BOOST_SPIRIT_CAST_HPP
