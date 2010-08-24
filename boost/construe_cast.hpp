//              Copyright Jeroen Habraken 2010.
// 
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONSTRUE_CAST_HPP
#define BOOST_CONSTRUE_CAST_HPP

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/home/karma/auto.hpp>
#include <boost/spirit/home/karma/numeric.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/directive.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <cstddef>
#include <cstring>
#include <cwchar>
#include <limits>
#include <string>
#include <typeinfo>

namespace boost {

    class bad_construe_cast
        : public std::bad_cast { };

    namespace construe {

        namespace detail {

            template <typename String>
            struct string_wrapper;

            template <typename String>
            struct string_wrapper<String const>
                : string_wrapper<String> {
                template <typename T>
                string_wrapper(T value)
                    : string_wrapper<String>(value) { }
            };

            template <>
            struct string_wrapper<char const *> {
                typedef char * iterator;
                typedef char const * const_iterator;

                string_wrapper(char const * value)
                    : value_(value) { }

                inline const_iterator const
                begin() {
                    return value_;
                }

                inline const_iterator const
                end() {
                    return value_ + length();
                }

                inline std::size_t const
                length() {
                    if (length_ == false)
                        length_ = strlen(value_);

                    return length_.get();
                }

                private:
                    char const * value_;

                    boost::optional<std::size_t> mutable length_;
            };

            template <>
            struct string_wrapper<wchar_t const *> {
                typedef wchar_t * iterator;
                typedef wchar_t const * const_iterator;

                string_wrapper(wchar_t const * value)
                    : value_(value) { }

                inline const_iterator const
                begin() {
                    return value_;
                }

                inline const_iterator const
                end() {
                    return value_ + length();
                }

                inline std::size_t const
                length() {
                    if (length_ == false)
                        length_ = wcslen(value_);

                    return length_.get();
                }

                private:
                    wchar_t const * value_;

                    boost::optional<std::size_t> mutable length_;
            };

            template <>
            struct string_wrapper<char *>
                : string_wrapper<char const *> {
                template <typename T>
                string_wrapper(T value)
                    : string_wrapper<char const *>(value) { }
            };

            template <>
            struct string_wrapper<wchar_t *>
                : string_wrapper<wchar_t const *> {
                template <typename T>
                string_wrapper(T value)
                    : string_wrapper<wchar_t const *>(value) { }
            };

            template <typename CharT, std::size_t N>
            struct string_wrapper<CharT [N]> {
                typedef CharT * iterator;
                typedef CharT const * const_iterator;

                string_wrapper(CharT const (&value)[N])
                    : value_(value) { }

                inline const_iterator const
                begin() {
                    return &value_[0];
                }

                inline const_iterator const
                end() {
                    return &value_[0] + N;
                }

                inline std::size_t const
                length() {
                    return N;
                }

                private:
                    CharT const (&value_)[N];
            };

            template <typename CharT, std::size_t N>
            struct string_wrapper<CharT const [N]>
                : string_wrapper<CharT [N]> {
                string_wrapper(CharT const (&value)[N])
                    : string_wrapper<CharT [N]>(value) { }
            };

            template <typename CharT, std::size_t N>
            struct string_wrapper<CharT (&)[N]>
                : string_wrapper<CharT [N]> {
                string_wrapper(CharT const (&value)[N])
                    : string_wrapper<CharT [N]>(value) { }
            };

            template <typename CharT, std::size_t N>
            struct string_wrapper<CharT const (&)[N]>
                : string_wrapper<CharT [N]> {
                string_wrapper(CharT const (&value)[N])
                    : string_wrapper<CharT [N]>(value) { }
            };

            template <typename CharT, typename Traits, typename Allocator>
            struct string_wrapper<std::basic_string<CharT, Traits, Allocator> > {
                private:
                    typedef std::basic_string<CharT, Traits, Allocator> string_t;

                public:
                    typedef typename string_t::iterator iterator;
                    typedef typename string_t::const_iterator const_iterator;

                    string_wrapper(string_t const & value)
                        : value_(value) { }

                    inline const_iterator const
                    begin() {
                        return value_.begin();
                    }

                    inline const_iterator const
                    end() {
                        return value_.end();
                    }

                    inline std::size_t const
                    length() {
                        return value_.length();
                    }

                private:
                    string_t const & value_;
            };

        }  // namespace detail

        namespace traits {

            template <typename Source>
            struct reserve_size {
                BOOST_STATIC_CONSTANT(std::size_t, value = 0);
            };

            template <typename Source>
            struct reserve_size<Source const>
                : reserve_size<Source> { };

            template <>
            struct reserve_size<char> {
                BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            };

            template <>
            struct reserve_size<wchar_t> {
                BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            };

            template <>
            struct reserve_size<bool> {
                BOOST_STATIC_CONSTANT(std::size_t, value = 5);
            };

            template <typename Source>
            struct reserve_size_integral {
                BOOST_STATIC_CONSTANT(std::size_t, value =
                    std::numeric_limits<Source>::is_signed +
                    1 +
                    std::numeric_limits<Source>::digits10);
            };

            template <>
            struct reserve_size<int>
                : reserve_size_integral<int> { };

            template <>
            struct reserve_size<short>
                : reserve_size_integral<short> { };

            template <>
            struct reserve_size<long>
                : reserve_size_integral<long> { };

            template <>
            struct reserve_size<unsigned int>
                : reserve_size_integral<unsigned int> { };

#ifndef BOOST_NO_INTRINSIC_WCHAR_T
            template <>
            struct reserve_size<unsigned short>
                : reserve_size_integral<unsigned short> { };
#endif

            template <>
            struct reserve_size<unsigned long>
                : reserve_size_integral<unsigned long> { };

#ifdef BOOST_HAS_LONG_LONG
            template <>
            struct reserve_size<boost::long_long_type>
                : reserve_size_integral<boost::long_long_type> { };

            template <>
            struct reserve_size<boost::ulong_long_type>
                : reserve_size_integral<boost::ulong_long_type> { };
#endif

            template <typename Source>
            struct reserve_size_floating_point {
                BOOST_STATIC_CONSTANT(std::size_t, value =
                    std::numeric_limits<Source>::is_signed +
                    8 +
                    std::numeric_limits<Source>::digits10);
            };

            template <>
            struct reserve_size<float>
                : reserve_size_floating_point<float> { };

            template <>
            struct reserve_size<double>
                : reserve_size_floating_point<double> { };

            template <>
            struct reserve_size<long double>
                : reserve_size_floating_point<long double> { };

            template <typename Source>
            struct reserve_size<boost::optional<Source> >
                : reserve_size<Source> { };

        }  // namespace traits

        namespace traits {

            template <typename Sequence>
            class has_reserve {
                template <typename U, void (U::*)(typename U::size_type) = &U::reserve>
                struct impl { };

                template <typename U>
                static boost::type_traits::yes_type test(U*, impl<U>* = 0);

                template <typename U>
                static boost::type_traits::no_type test(...);

            public:
                BOOST_STATIC_CONSTANT(bool, value =
                    sizeof(test<Sequence>(0)) == sizeof(boost::type_traits::yes_type));
                typedef boost::mpl::bool_<value> type;
            };

        }  // namespace traits

        namespace detail {

            template <typename Sequence>
            inline void
            call_reserve(
                Sequence & sequence,
                typename Sequence::size_type const size
            ) {
                call_reserve_impl(
                    sequence, size, typename boost::construe::traits::has_reserve<Sequence>::type());
            }

            template <typename Sequence>
            inline void
            call_reserve(
                Sequence const &,
                std::size_t const
            ) {
                // Missing size_type
            }

            template <typename Sequence>
            inline void
            call_reserve_impl(
                Sequence & sequence,
                typename Sequence::size_type const size,
                boost::mpl::true_ const
            ) {
                sequence.reserve(size);
            }

            template <typename Sequence>
            inline void
            call_reserve_impl(
                Sequence const &,
                typename Sequence::size_type const,
                boost::mpl::false_ const
            ) {
                // Missing .reserve()
            }

        }  // namespace detail

        namespace detail {

            template <typename Target, typename Source>
            struct construe_cast;

            template <typename Target>
            struct construe_cast<Target, Target> {
                static inline Target const &
                call(Target const & source) {
                    return source;
                }
            };

            template <typename Target, typename Source>
            struct construe_cast {
                static inline Target const
                call(Source const & source) {
                    return do_call(
                        source,
                        boost::is_convertible<Target, Source>(),
                        boost::spirit::traits::is_string<Source>(),
                        boost::spirit::traits::is_container<Target>());
                }
 
                private:
                    static inline Target const
                    do_call(
                        Source const & source,
                        boost::mpl::true_ const,
                        bool const,
                        bool const
                    ) {
                        return static_cast<Target>(source);
                    }

                    static inline Target const
                    do_call(
                        Source const & source,
                        boost::mpl::false_ const,
                        boost::mpl::true_ const,
                        boost::mpl::false_ const
                    ) {
                        typedef boost::construe::detail::string_wrapper<Source> string_t;
                        typedef typename string_t::const_iterator iterator_t;

                        Target target;

                        string_t string(source);

                        if (string.length() < 1)
                            throw boost::bad_construe_cast();

                        iterator_t begin = string.begin(), iterator = begin;
                        iterator_t end = string.end();

                        bool result = boost::spirit::qi::parse(
                            iterator, end, target);

                        if (!result || !((iterator < end && *iterator == 0) || iterator == end))
                            throw boost::bad_construe_cast();

                        return target;
                    }

                    static inline Target const
                    do_call(
                        Source const & source,
                        boost::mpl::false_ const,
                        boost::mpl::false_ const,
                        boost::mpl::true_ const
                    ) {
                        Target target;

                        call_reserve(target, boost::construe::traits::reserve_size<Source>::value);

                        std::back_insert_iterator<Target> iterator(target);
                        bool result = boost::spirit::karma::generate(
                            iterator,
#if SPIRIT_VERSION <= 0x2030
                            boost::spirit::karma::auto_,
#endif
                            source);

                        if (!result)
                            throw boost::bad_construe_cast();

                        return target;
                    }

                    static inline Target const
                    do_call(
                        Source const & source,
                        boost::mpl::false_ const,
                        boost::mpl::true_ const,
                        boost::mpl::true_ const
                    ) {
                        typedef boost::construe::detail::string_wrapper<Source> string_t;
                        typedef typename string_t::const_iterator iterator_t;

                        Target target;

                        string_t string(source);

                        call_reserve(target, string.length());

                        iterator_t iterator = string.begin();
                        iterator_t end = string.end();

                        bool result = boost::spirit::qi::parse(
                            iterator, end, target);

                        if (!result || iterator != end)
                            throw boost::bad_construe_cast();

                        return target;
                    }

                    static inline Target const
                    do_call(
                        Source const & source,
                        boost::mpl::false_ const,
                        boost::mpl::false_ const,
                        boost::mpl::false_ const
                    ) {
                        BOOST_STATIC_ASSERT(sizeof(Source) == 0);
                    }
            };

        }  // namespace detail

    }  // namespace construe

    namespace traits {
        template <typename Target, typename Source, typename Enable = void>
        struct construe_cast
            : boost::construe::detail::construe_cast<Target, Source> { };
    }  // traits

    template <typename Target, typename Source>
    inline Target const
    construe_cast(Source const & source) {
        return boost::traits::construe_cast<Target, Source>::call(source);
    }

}  // namespace boost

#endif  // BOOST_CONSTRUE_CAST_HPP
