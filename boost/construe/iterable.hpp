//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONSTRUE_ITERABLE_HPP
#define BOOST_CONSTRUE_ITERABLE_HPP

#include <boost/mpl/identity.hpp>
#include <boost/mpl/not.hpp>
#include <boost/optional.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <cstddef>
#include <cstring>
#include <cwchar>
#include <string>

namespace boost {

    namespace construe {

        namespace traits {

            struct not_iterable { };

            template <typename Type>
            struct iterable_impl
                : mpl::identity<not_iterable> { };

            template <>
            struct iterable_impl<char const *> {
                typedef char const * type;

                typedef char * iterator;
                typedef char const * const_iterator;

                iterable_impl(type const & value)
                    : value_(value) { }

                inline const_iterator const
                begin() {
                    return value_;
                }

                inline const_iterator const
                end() {
                    return value_ + size();
                }

                inline std::size_t const
                size() {
                    if (size_ == false)
                        size_ = strlen(value_);

                    return size_.get();
                }

                private:
                    type const value_;

                    optional<std::size_t> mutable size_;
            };

            template <>
            struct iterable_impl<char *>
                : iterable_impl<char const *> {
                typedef char * type;

                iterable_impl(type const & value)
                    : iterable_impl<char const *>(value) { }
            };

            template <>
            struct iterable_impl<wchar_t const *> {
                typedef wchar_t const * type;

                typedef wchar_t * iterator;
                typedef wchar_t const * const_iterator;

                iterable_impl(type const & value)
                    : value_(value) { }

                inline const_iterator const
                begin() {
                    return value_;
                }

                inline const_iterator const
                end() {
                    return value_ + size();
                }

                inline std::size_t const
                size() {
                    if (size_ == false)
                        size_ = wcslen(value_);

                    return size_.get();
                }

                private:
                    type const value_;

                    optional<std::size_t> mutable size_;
            };

            template <>
            struct iterable_impl<wchar_t *>
                : iterable_impl<wchar_t const *> {
                typedef wchar_t * type;

                iterable_impl(type const & value)
                    : iterable_impl<wchar_t const *>(value) { }
            };

            template <typename CharT, std::size_t N>
            struct iterable_impl_extent {
                typedef CharT const type[N];

                typedef CharT * iterator;
                typedef CharT const * const_iterator;

                iterable_impl_extent(CharT const (& value)[N])
                    : value_(value) { }

                inline const_iterator const
                begin() {
                    return &value_[0];
                }

                inline const_iterator const
                end() {
                    return &value_[0] + size();
                }

                inline std::size_t const
                size() {
                    return value_[N - 1] == 0 ? N - 1 : N;
                }

                private:
                    CharT const (& value_)[N];
            };

            template <std::size_t N>
            struct iterable_impl<char [N]>
                : iterable_impl_extent<char, N> {
                typedef char const type[N];

                iterable_impl(type const & value)
                    : iterable_impl_extent<char, N>(value) { }
            };

            template <std::size_t N>
            struct iterable_impl<wchar_t [N]>
                : iterable_impl_extent<wchar_t, N> {
                typedef wchar_t const type[N];

                iterable_impl(type const & value)
                    : iterable_impl_extent<wchar_t, N>(value) { }
            };

            template <typename CharT, typename Traits, typename Allocator>
            struct iterable_impl<std::basic_string<CharT, Traits, Allocator> > {
                typedef std::basic_string<CharT, Traits, Allocator> type;

                typedef typename type::iterator iterator;
                typedef typename type::const_iterator const_iterator;

                iterable_impl(type const & value)
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
                size() {
                    return value_.size();
                }

                private:
                    type const & value_;
            };

            template <typename Type, typename Enable = void>
            struct iterable
                : iterable_impl<
                    typename remove_const<
                        typename remove_reference<Type>::type
                    >::type> {
                iterable(Type const & value)
                    : iterable_impl<
                        typename remove_const<
                            typename remove_reference<Type>::type
                        >::type>(value) { }
            };

            template <typename Type>
            struct is_iterable
                : mpl::not_<is_same<
                    typename iterable<Type>::type,
                    not_iterable
                > > { };

        }  // namespace traits

    }  // namespace construe

}  // namespace boost

#endif  // BOOST_CONSTRUE_ITERABLE_HPP
