/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_CORE_DEFINITION
#define CHECKHEADER_SLIB_CORE_DEFINITION

#include "option.h"

#if defined(SLIB_COMPILER_IS_VC)

#	if defined (_DEBUG)
#		define SLIB_DEBUG
#	endif

#	define SLIB_STDCALL		__stdcall
#	define SLIB_INLINE		__forceinline
#	define SLIB_THREAD_OLD	__declspec(thread)
#	define SLIB_THREAD		thread_local
#	define SLIB_INT64(v)	(v##i64)
#	define SLIB_UINT64(v)	(v##ui64)
typedef __int64				sl_int64;
typedef unsigned __int64	sl_uint64;
typedef size_t				sl_size_t;

#	define SLIB_ALIGN(n)	__declspec(align(n))

#	define SLIB_EXPORT
#	define SLIB_VISIBLE_LOCAL

#elif defined(SLIB_COMPILER_IS_GCC)

#	if ! defined (__OPTIMIZE__)
#		define SLIB_DEBUG
#	endif

#	define SLIB_STDCALL		__attribute__((stdcall))
#	define SLIB_INLINE		inline __attribute__((always_inline))
#	define SLIB_INT64(v)	(v##LL)
#	define SLIB_UINT64(v)	(v##ULL)
#	define SLIB_THREAD_OLD	__thread
#	define SLIB_THREAD		thread_local
typedef long long			sl_int64;
typedef unsigned long long	sl_uint64;
typedef __SIZE_TYPE__		sl_size_t;

#	define SLIB_ALIGN(n)		__attribute__((aligned(n)))

#	if __GNUC__ >= 4
#		define SLIB_EXPORT			__attribute__((visibility("default")))
#		define SLIB_VISIBLE_LOCAL	__attribute__((visibility("hidden")))
#	else
#		define SLIB_EXPORT
#		define SLIB_VISIBLE_LOCAL
#	endif

#endif

// Basic Type Definition
typedef int					sl_int;
typedef unsigned int		sl_uint;
typedef signed char			sl_int8;
typedef unsigned char		sl_uint8;
typedef short				sl_int16;
typedef unsigned short		sl_uint16;
#if defined(__SIZEOF_INT__)
#	if __SIZEOF_INT__ == 4
typedef int					sl_int32;
typedef unsigned int		sl_uint32;
#	else
typedef long				sl_int32;
typedef unsigned long		sl_uint32;
#	endif
#else
typedef int					sl_int32;
typedef unsigned int		sl_uint32;
#endif
typedef float				sl_real;

typedef void*				sl_ptr;
typedef const void*			sl_cptr;

#define sl_null				nullptr
typedef decltype(nullptr)	sl_null_t;

typedef bool				sl_bool;
#define sl_true				true
#define sl_false			false

#ifdef SLIB_ARCH_IS_64BIT
typedef sl_uint64			sl_size;
typedef sl_int64			sl_reg;
#else
typedef sl_uint32			sl_size;
typedef sl_int32			sl_reg;
#endif

typedef char				sl_char8;
typedef char16_t			sl_char16;
typedef char32_t			sl_char32;

#define SLIB_UNICODE(quote)	u##quote

#if defined(SLIB_COMPILER_IS_VC)
#	define SLIB_WCHAR_SIZE(quote)		2
#else
#	if defined(__SIZEOF_WCHAR_T__)
#		define SLIB_WCHAR_SIZE			__SIZEOF_WCHAR_T__
#	else
#		define SLIB_WCHAR_SIZE			0
#	endif
#endif

namespace slib
{
	SLIB_INLINE void _blank_proc(const void*) {}
	void _abort(const char* msg, const char* file, sl_uint32 line);
}

#define SLIB_UNUSED(x)					slib::_blank_proc(&x);

#if defined(SLIB_DEBUG)
#	define SLIB_ASSERT(_Expression)		( (!!(_Expression)) || (slib::_abort(#_Expression, __FILE__, __LINE__), 0) )
#	define SLIB_ABORT(MESSAGE)			(slib::_abort(MESSAGE, __FILE__, __LINE__))
#else
#	define SLIB_ASSERT(_Expression)
#	define SLIB_ABORT(MESSAGE)
#endif

/************************************************************************/
/* Operating System Related Difinitions                                 */
/************************************************************************/
#if (SLIB_PLATFORM==SLIB_PLATFORM_WIN32)
#	ifndef _WIN32_WINNT
#		define _WIN32_WINNT 0x0501
#	endif
#endif

#endif
