#ifndef BHO_CORE_DETAIL_SP_WIN32_SLEEP_HPP_INCLUDED
#define BHO_CORE_DETAIL_SP_WIN32_SLEEP_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// bho/core/detail/sp_win32_sleep.hpp
//
// Declares the Win32 Sleep() function.
//
// Copyright 2008, 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0
// https://www.boost.org/LICENSE_1_0.txt

#if defined( BHO_USE_WINDOWS_H )
# include <windows.h>
#endif

namespace bho
{
namespace core
{
namespace detail
{

#if !defined( BHO_USE_WINDOWS_H )

#if defined(__clang__) && defined(__x86_64__)
// clang x64 warns that __stdcall is ignored
# define BHO_CORE_SP_STDCALL
#else
# define BHO_CORE_SP_STDCALL __stdcall
#endif

#if defined(__LP64__) // Cygwin 64
  extern "C" __declspec(dllimport) void BHO_CORE_SP_STDCALL Sleep( unsigned int ms );
#else
  extern "C" __declspec(dllimport) void BHO_CORE_SP_STDCALL Sleep( unsigned long ms );
#endif

extern "C" __declspec(dllimport) int BHO_CORE_SP_STDCALL SwitchToThread();

#undef BHO_CORE_SP_STDCALL

#endif // !defined( BHO_USE_WINDOWS_H )

} // namespace detail
} // namespace core
} // namespace bho

#endif // #ifndef BHO_CORE_DETAIL_SP_WIN32_SLEEP_HPP_INCLUDED
