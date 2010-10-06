//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONSTRUE_HPP
#define BOOST_CONSTRUE_HPP

#include <boost/construe/iterable.hpp>
#include <boost/construe/reserve.hpp>
#include <boost/construe/tag.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/spirit/home/karma/auto.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/directive.hpp>
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
                    Target target = Target();

                    bool result = do_call(
                        target,
                        source,
                        traits::is_iterable<Source>(),
                        boost::spirit::traits::is_container<Target>());

                    if (!result)
                        throw boost::bad_construe_cast();

                    return target;
                }
 
                private:
                    static inline bool const
                    do_call(
                        Target & target,
                        Source const & source,
                        boost::mpl::true_ const,
                        bool const
                    ) {
                        typedef traits::iterable<Source> iterable_t;
                        typedef typename iterable_t::const_iterator iterator_t;

                        iterable_t iterable(source);

                        if (iterable.size() < 1)
                            return false;

                        call_reserve(target, iterable.size());

                        iterator_t begin = iterable.begin(), iterator = begin;
                        iterator_t end = iterable.end();

                        bool result = boost::spirit::qi::parse(
                            iterator, end, tag_type<Target, Tag>::call(target));

                        if (!result || !((iterator < end && *iterator == 0) || iterator == end))
                            return false;

                        return true;
                    }

                    static inline bool const
                    do_call(
                        Target & target,
                        Source const & source,
                        boost::mpl::false_ const,
                        boost::mpl::true_ const
                    ) {
                        call_reserve(target, traits::reserve_size<Source, Tag>::call(source));

                        std::back_insert_iterator<Target> iterator(target);
                        bool result = boost::spirit::karma::generate(
                            iterator,
#if SPIRIT_VERSION <= 0x2030
                            boost::spirit::karma::auto_,
#endif
                            tag_type<Source const, Tag>::call(source));

                        return result;
                    }

                    static inline Target const
                    do_call(
                        Target & target,
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

}  // namespace boost

#endif  // BOOST_CONSTRUE_HPP
