//                 Copyright Adam Merz 2010.
//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONSTRUE_RESERVE_HPP
#define BOOST_CONSTRUE_RESERVE_HPP

#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <cstddef>

namespace boost {

    namespace construe {

        namespace traits {

            template <typename Type, typename Tag>
            struct reserve_size_impl {
                BOOST_STATIC_CONSTANT(std::size_t, value = 0);
            };

            template <typename Tag>
            struct reserve_size_impl<char, Tag> {
                BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            };

            template <typename Tag>
            struct reserve_size_impl<wchar_t, Tag> {
                BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            };

            template <typename Tag>
            struct reserve_size_impl<bool, Tag> {
                BOOST_STATIC_CONSTANT(std::size_t, value = 5);
            };

            template <typename Type, typename Tag>
            struct reserve_size_impl_integral;

            template <typename Type>
            struct reserve_size_impl_integral<Type, boost::spirit::unused_type> {
                BOOST_STATIC_CONSTANT(std::size_t, value =
                    std::numeric_limits<Type>::is_signed +
                    1 +
                    std::numeric_limits<Type>::digits10);
            };

            template <typename Tag>
            struct reserve_size_impl<int, Tag>
                : reserve_size_impl_integral<int, Tag> { };

            template <typename Tag>
            struct reserve_size_impl<short, Tag>
                : reserve_size_impl_integral<short, Tag> { };

            template <typename Tag>
            struct reserve_size_impl<long, Tag>
                : reserve_size_impl_integral<long, Tag> { };

            template <typename Tag>
            struct reserve_size_impl<unsigned int, Tag>
                : reserve_size_impl_integral<unsigned int, Tag> { };

#ifndef BOOST_NO_INTRINSIC_WCHAR_T
            template <typename Tag>
            struct reserve_size_impl<unsigned short, Tag>
                : reserve_size_impl_integral<unsigned short, Tag> { };
#endif

            template <typename Tag>
            struct reserve_size_impl<unsigned long, Tag>
                : reserve_size_impl_integral<unsigned long, Tag> { };

#ifdef BOOST_HAS_LONG_LONG
            template <typename Tag>
            struct reserve_size_impl<boost::long_long_type, Tag>
                : reserve_size_impl_integral<boost::long_long_type, Tag> { };

            template <typename Tag>
            struct reserve_size_impl<boost::ulong_long_type, Tag>
                : reserve_size_impl_integral<boost::ulong_long_type, Tag> { };
#endif

            template <typename Type, typename Tag>
            struct reserve_size_impl_floating_point {
                BOOST_STATIC_CONSTANT(std::size_t, value =
                    std::numeric_limits<Type>::is_signed +
                    8 +
                    std::numeric_limits<Type>::digits10);
            };

            template <typename Tag>
            struct reserve_size_impl<float, Tag>
                : reserve_size_impl_floating_point<float, Tag> { };

            template <typename Tag>
            struct reserve_size_impl<double, Tag>
                : reserve_size_impl_floating_point<double, Tag> { };

            template <typename Tag>
            struct reserve_size_impl<long double, Tag>
                : reserve_size_impl_floating_point<long double, Tag> { };

            template <typename Type, typename Tag>
            struct reserve_size_impl<boost::optional<Type>, Tag>
                : reserve_size_impl<Type, Tag> { };

            template <typename Type, typename Tag, typename Enable = void>
            struct reserve_size {
                typedef std::size_t type;

                static inline type const
                call(Type const &) {
                    return reserve_size_impl<
                        typename remove_const<
                            typename remove_reference<Type>::type
                        >::type, Tag>::value;
                }
            };

        }  // namespace traits

        namespace detail {

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

            template <typename Sequence>
            inline void
            call_reserve(
                Sequence & sequence,
                typename Sequence::size_type const size
            ) {
                call_reserve_impl(
                    sequence, size, typename has_reserve<Sequence>::type());
            }

            template <typename Sequence>
            inline void
            call_reserve(
                Sequence const &,
                std::size_t const
            ) {
                // Missing size_type
            }

        }  // namespace detail

    }  // namespace construe

}  // namespace boost

#endif  // BOOST_CONSTRUE_RESERVE_HPP
