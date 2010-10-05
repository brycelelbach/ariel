//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONSTRUE_TAG_HPP
#define BOOST_CONSTRUE_TAG_HPP

#include <boost/spirit/home/karma/auto.hpp>
#include <boost/spirit/home/karma/numeric.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/static_assert.hpp>

namespace boost {

    namespace construe {

        namespace tag {

            using boost::spirit::tag::bin;

            using boost::spirit::tag::oct;

            using boost::spirit::tag::hex;

        }  // namespace tag

        namespace detail {

            template <typename Type, typename Tag>
            struct tagged_type {
                tagged_type(Type & value)
                    : value_(value) { }

                inline Type const &
                get() const {
                    return value_;
                }

                void
                set(Type const & value) {
                    value_ = value;
                }

                private:
                    Type & value_;
            };

            template <typename Type, typename Tag>
            struct tag_type {
                typedef tagged_type<Type, Tag> type;

                static inline type const
                call(Type & value) {
                    return type(value);
                }
            };

            template <typename Type>
            struct tag_type<Type, boost::spirit::unused_type> {
                typedef Type type;

                static inline type &
                call(Type & value) {
                    return value;
                }
            };

        }  // namespace detail 

    }  // namespace construe

    namespace spirit {

        namespace traits {

            template <typename Target>
            struct create_parser<construe::detail::tagged_type<Target, construe::tag::bin> > {
                typedef spirit::bin_type type;

                static inline type const &
                call() {
                    return spirit::bin;
                }
            };

            template <typename Target>
            struct create_parser<construe::detail::tagged_type<Target, construe::tag::oct> > {
                typedef spirit::oct_type type;

                static inline type const &
                call() {
                    return spirit::oct;
                }
            };

            template <typename Target>
            struct create_parser<construe::detail::tagged_type<Target, construe::tag::hex> > {
                typedef spirit::hex_type type;

                static inline type const &
                call() {
                    return spirit::hex;
                }
            };

            template <typename Target, typename Tag, typename Enable>
            struct assign_to_attribute_from_value<construe::detail::tagged_type<Target, Tag>, Target, Enable> {
                static inline void
                call(Target const & val, construe::detail::tagged_type<Target, Tag> & attr) {
                    attr.set(val);
                }
            };

            template <typename Target, typename Tag, typename Attrib, typename Enable>
            struct assign_to_attribute_from_value<construe::detail::tagged_type<Target, Tag>, Attrib, Enable> {
                BOOST_STATIC_ASSERT(sizeof(Target) == 0);
            };

            template <typename Source>
            struct create_generator<construe::detail::tagged_type<Source, construe::tag::bin> > {
                typedef spirit::bin_type type;

                static inline type const &
                call() {
                    return spirit::bin;
                }
            };

            template <typename Source>
            struct create_generator<construe::detail::tagged_type<Source, construe::tag::oct> > {
                typedef spirit::oct_type type;

                static inline type const &
                call() {
                    return spirit::oct;
                }
            };

            template <typename Source>
            struct create_generator<construe::detail::tagged_type<Source, construe::tag::hex> > {
                typedef spirit::hex_type type;

                static inline type const &
                call() {
                    return spirit::hex;
                }
            };

            template <typename Source, typename Tag, typename Enable>
#if SPIRIT_VERSION < 2040
            struct extract_from_attribute<construe::detail::tagged_type<Source, Tag>, Enable> {
#else
            struct extract_from_attribute<construe::detail::tagged_type<Source, Tag>, Source, Enable> {
#endif
                typedef Source type;

                template <typename Context>
                static inline type const &
                call(construe::detail::tagged_type<Source, Tag> const & attr, Context & context) {
                    return attr.get();
                }
            };

#if SPIRIT_VERSION >= 2040
            template <typename Source, typename Tag, typename Attrib, typename Enable>
            struct extract_from_attribute<construe::detail::tagged_type<Source, Tag>, Attrib, Enable> {
                BOOST_STATIC_ASSERT(sizeof(Source) == 0);
            };
#endif

        }  // namespace traits

    }  // namespace spirit

}  // namespace boost

#endif  // BOOST_CONSTRUE_TAG_HPP
