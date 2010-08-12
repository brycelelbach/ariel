//              Copyright Jeroen Habraken 2010.
// 
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONSTRUE_CAST_HPP
#define BOOST_CONSTRUE_CAST_HPP

#include <boost/mpl/bool.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_container.hpp>
#include <boost/spirit/include/support_string_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <cstddef>
#include <string>
#include <typeinfo>

namespace boost {

    class bad_construe_cast
        : std::bad_cast { };

    namespace construe {

        namespace detail {

            template <typename String>
            struct string_iterators;

            template <typename String>
            struct string_iterators<String const>
                : string_iterators<String> {
                template <typename T>
                string_iterators(T value)
                    : string_iterators<String>(value) { }
            };

            template <>
            struct string_iterators<char const *> {
                typedef char * iterator;
                typedef char const * const_iterator;

                string_iterators(char const * value)
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
            struct string_iterators<wchar_t const *> {
                typedef wchar_t * iterator;
                typedef wchar_t const * const_iterator;

                string_iterators(wchar_t const * value)
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
            struct string_iterators<char *>
                : string_iterators<char const *> {
                template <typename T>
                string_iterators(T value)
                    : string_iterators<char const *>(value) { }
            };

            template <>
            struct string_iterators<wchar_t *>
                : string_iterators<wchar_t const *> {
                template <typename T>
                string_iterators(T value)
                    : string_iterators<wchar_t const *>(value) { }
            };

            template <typename CharT, std::size_t N>
            struct string_iterators<CharT [N]> {
                typedef CharT * iterator;
                typedef CharT const * const_iterator;

                string_iterators(CharT const (&value)[N])
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

            template <typename CharT, std::size_t N>
            struct string_iterators<CharT const [N]>
                : string_iterators<CharT [N]> {
                string_iterators(CharT const (&value)[N])
                    : string_iterators<CharT [N]>(value) { }
            };

            template <typename CharT, std::size_t N>
            struct string_iterators<CharT (&)[N]>
                : string_iterators<CharT [N]> {
                string_iterators(CharT const (&value)[N])
                    : string_iterators<CharT [N]>(value) { }
            };

            template <typename CharT, std::size_t N>
            struct string_iterators<CharT const (&)[N]>
                : string_iterators<CharT [N]> {
                string_iterators(CharT const (&value)[N])
                    : string_iterators<CharT [N]>(value) { }
            };

            template <typename CharT, typename Traits, typename Allocator>
            struct string_iterators<std::basic_string<CharT, Traits, Allocator> > {
                private:
                    typedef std::basic_string<CharT, Traits, Allocator> string_t;

                public:
                    typedef typename string_t::iterator iterator;
                    typedef typename string_t::const_iterator const_iterator;

                    string_iterators(string_t const & value)
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
                static bool const value = sizeof(test<Sequence>(0)) == sizeof(boost::type_traits::yes_type);
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
                        typedef string_iterators<Source> iterators_t;
                        typedef typename iterators_t::const_iterator iterator_t;

                        Target target;

                        string_iterators<Source> iterators(source);

                        iterator_t iterator = iterators.begin();
                        iterator_t end = iterators.end();

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

                        call_reserve(target, 32);

                        std::back_insert_iterator<Target> iterator(target);
                        bool result = boost::spirit::karma::generate(
                            iterator, source);

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
                        // TODO
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
