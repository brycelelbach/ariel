//              Copyright Jeroen Habraken 2010.
// 
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_CAST_HPP
#define BOOST_SPIRIT_CAST_HPP

#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <typeinfo>

namespace boost {

    class bad_spirit_cast
        : std::bad_cast { };

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

    }  // namespace detail

    template <typename Target, typename Source>
    inline Target const
    spirit_cast(Source const & source) {
        return boost::detail::spirit_cast<Target, Source>::call(source);
    }

}  // namespace boost

#endif  // BOOST_SPIRIT_CAST_HPP
