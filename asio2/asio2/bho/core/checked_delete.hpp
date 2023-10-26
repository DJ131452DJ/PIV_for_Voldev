#ifndef BHO_CORE_CHECKED_DELETE_HPP
#define BHO_CORE_CHECKED_DELETE_HPP

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <asio2/bho/config.hpp>

//
//  bho/checked_delete.hpp
//
//  Copyright (c) 2002, 2003 Peter Dimov
//  Copyright (c) 2003 Daniel Frey
//  Copyright (c) 2003 Howard Hinnant
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/core/doc/html/core/checked_delete.html for documentation.
//

namespace bho
{

// verify that types are complete for increased safety

template<class T> inline void checked_delete(T * x) BHO_NOEXCEPT
{
#if defined(__cpp_static_assert) && __cpp_static_assert >= 200410L

    static_assert( sizeof(T) != 0, "Type must be complete" );

#else

    typedef char type_must_be_complete[ sizeof(T) ];
    (void) sizeof(type_must_be_complete);

#endif

    delete x;
}

template<class T> inline void checked_array_delete(T * x) BHO_NOEXCEPT
{
#if defined(__cpp_static_assert) && __cpp_static_assert >= 200410L

    static_assert( sizeof(T) != 0, "Type must be complete" );

#else

    typedef char type_must_be_complete[ sizeof(T) ];
    (void) sizeof(type_must_be_complete);

#endif

    delete [] x;
}

template<class T> struct checked_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x) const BHO_NOEXCEPT
    {
        // bho:: disables ADL
        bho::checked_delete(x);
    }
};

template<class T> struct checked_array_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x) const BHO_NOEXCEPT
    {
        bho::checked_array_delete(x);
    }
};

} // namespace bho

#endif  // #ifndef BHO_CORE_CHECKED_DELETE_HPP
