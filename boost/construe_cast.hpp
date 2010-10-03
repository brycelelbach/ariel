//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONSTRUE_HPP
#define BOOST_CONSTRUE_HPP

#include <boost/construe/iterable.hpp>
#include <boost/construe/reserve.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/spirit/home/karma/auto.hpp>
#include <boost/spirit/home/karma/numeric.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/directive.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/static_assert.hpp>

#include <cstddef>
#include <typeinfo>

namespace boost {

    class bad_construe_cast
        : public std::bad_cast { };

    namespace construe {

        namespace detail {

            template <typename Type, typename Tag>
            struct tagged_type {
                tagged_type(Type & value)
                    : value_(value) { }

                inline Type const &
                get_value() const {
                    return value_;
                }

                void
                set_value(Type const & value) {
                    value_ = value;
                }

                private:
                    Type & value_;
            };

            template <typename Type, typename Tag>
            struct tag_type {
                typedef boost::construe::detail::tagged_type<Type, Tag> type;

                static inline type const
                call(Type & value) {
                    return type(value);
                }
            };

            template <typename Type>
            struct tag_type<Type, boost::spirit::unused_type> {
                static inline Type &
                call(Type & value) {
                    return value;
                }
            };

        }  // namespace detail

        namespace tag {

            using boost::spirit::tag::hex;

        }  // namespace tag

        namespace detail {

            template <typename Target, typename Tag, typename Source>
            struct construe_cast;

            template <typename Target>
            struct construe_cast<Target, boost::spirit::unused_type, Target> {
                static inline Target const &
                call(Target const & source) {
                    return source;
                }
            };

            template <typename Target, typename Tag, typename Source>
            struct construe_cast {
                static inline Target const
                call(Source const & source) {
                    return do_call(
                        source,
                        traits::is_iterable<Source>(),
                        boost::spirit::traits::is_container<Target>());
                }
 
                private:
                    static inline Target const
                    do_call(
                        Source const & source,
                        boost::mpl::true_ const,
                        bool const
                    ) {
                        typedef traits::iterable<Source> iterable_t;
                        typedef typename iterable_t::const_iterator iterator_t;

                        iterable_t iterable(source);

                        if (iterable.size() < 1)
                            throw boost::bad_construe_cast();

                        Target target = Target();

                        call_reserve(target, iterable.size());

                        iterator_t begin = iterable.begin(), iterator = begin;
                        iterator_t end = iterable.end();

                        bool result = boost::spirit::qi::parse(
                            iterator, end, boost::construe::detail::tag_type<Target, Tag>::call(target));

                        if (!result || !((iterator < end && *iterator == 0) || iterator == end))
                            throw boost::bad_construe_cast();

                        return target;
                    }

                    static inline Target const
                    do_call(
                        Source const & source,
                        boost::mpl::false_ const,
                        boost::mpl::true_ const
                    ) {
                        Target target = Target();

                        call_reserve(target, traits::reserve_size<Source, Tag>::call(source));

                        std::back_insert_iterator<Target> iterator(target);
                        bool result = boost::spirit::karma::generate(
                            iterator,
#if SPIRIT_VERSION <= 0x2030
                            boost::spirit::karma::auto_,
#endif
                            boost::construe::detail::tag_type<Source const, Tag>::call(source));

                        if (!result)
                            throw boost::bad_construe_cast();

                        return target;
                    }

                    static inline Target const
                    do_call(
                        Source const & source,
                        boost::mpl::false_ const,
                        boost::mpl::false_ const
                    ) {
                        BOOST_STATIC_ASSERT(sizeof(Source) == 0);
                    }
            };

        }  // namespace detail

    }  // namespace construe

    namespace traits {

        template <typename Target, typename Tag, typename Source, typename Enable = void>
        struct construe_cast
            : boost::construe::detail::construe_cast<Target, Tag, Source> { };

    }  // traits

    template <typename Target, typename Source>
    inline Target const
    construe_cast(Source const & source) {
        return boost::traits::construe_cast<Target, boost::spirit::unused_type, Source>::call(source);
    }

    template <typename Target, typename Tag, typename Source>
    inline Target const
    construe_cast(Source const & source) {
        return boost::traits::construe_cast<Target, Tag, Source>::call(source);
    }

    namespace spirit {

        namespace traits {

            template <typename Target>
            struct create_parser<boost::construe::detail::tagged_type<Target, boost::construe::tag::hex> > {
                typedef spirit::hex_type type;

                static inline type const &
                call() {
                    return spirit::hex;
                }
            };

            template <typename Target, typename Tag, typename Enable>
            struct assign_to_attribute_from_value<boost::construe::detail::tagged_type<Target, Tag>, Target, Enable> {
                static inline void
                call(Target const & val, boost::construe::detail::tagged_type<Target, Tag> & attr) {
                    attr.set_value(val);
                }
            };

            template <typename Source>
            struct create_generator<boost::construe::detail::tagged_type<Source, boost::construe::tag::hex> > {
                typedef spirit::hex_type type;

                static inline type const &
                call() {
                    return spirit::hex;
                }
            };

            template <typename Source, typename Tag, typename Enable>
#if SPIRIT_VERSION < 2040
            struct extract_from_attribute<boost::construe::detail::tagged_type<Source, Tag>, Enable> {
#else
            struct extract_from_attribute<boost::construe::detail::tagged_type<Source, Tag>, Source, Enable> {
#endif
                typedef Source type;

                template <typename Context>
                static inline type
                call(boost::construe::detail::tagged_type<Source, Tag> const & attr, Context & context) {
                    return attr.get_value();
                }
            };

#if SPIRIT_VERSION >= 2040
            template <typename Source, typename Tag, typename Attrib, typename Enable>
            struct extract_from_attribute<boost::construe::detail::tagged_type<Source, Tag>, Attrib, Enable> {
                BOOST_STATIC_ASSERT(sizeof(Source) == 0);
            };
#endif

        }  // namespace traits

    }  // namespace spirit

}  // namespace boost

#endif  // BOOST_CONSTRUE_HPP
