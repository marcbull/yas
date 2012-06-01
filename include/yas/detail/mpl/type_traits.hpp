
// Copyright (c) 2010-2012 niXman (i dot nixman dog gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef _yas__type_traits_hpp__included_
#define _yas__type_traits_hpp__included_

#include <yas/detail/mpl/bool.hpp>
#include <yas/detail/boost_preprocessor/preprocessor.hpp>

#include <cstddef>

namespace yas {
namespace detail {

/***************************************************************************/

template<typename T>
struct is_pointer: false_ {};

template<typename T>
struct is_pointer<T*>: true_ {};

template<typename T>
struct is_pointer<T const*>: true_ {};

template<typename T>
struct is_pointer<T volatile*>: true_ {};

template<typename T>
struct is_pointer<T const volatile*>: true_ {};

/***************************************************************************/

template<typename T>
struct is_const: false_ {};

template<typename T>
struct is_const<T const>: true_ {};

template<typename T>
struct is_void: false_ {};

template<typename T0, typename T1>
struct is_same: false_ {};

template<typename T0>
struct is_same<T0, T0>: true_ {};

template<typename T>
struct is_array: false_ {};

template<typename T, std::size_t N>
struct is_array<T [N]>: true_ {};

template<typename T, std::size_t N>
struct is_array<T const [N]>: true_ {};

template<typename T, std::size_t N>
struct is_array<T volatile [N]>: true_ {};

template<typename T, std::size_t N>
struct is_array<T const volatile [N]>: true_ {};

/***************************************************************************/

template<typename T>
struct remove_all_extents {typedef T type;};

template<typename T, size_t N>
struct remove_all_extents<T[N]>
{typedef typename remove_all_extents<T>::type type;};

template<typename T, size_t N>
struct remove_all_extents<T const[N]>
{typedef typename remove_all_extents<T const>::type type;};

template<typename T, size_t N>
struct remove_all_extents<T volatile[N]>
{typedef typename remove_all_extents<T volatile>::type type;};

template<typename T, size_t N>
struct remove_all_extents<T const volatile[N]>
{typedef typename remove_all_extents<T const volatile>::type type;};

template<typename T>
struct remove_all_extents<T[]>
{typedef typename remove_all_extents<T>::type type;};

template<typename T>
struct remove_all_extents<T const[]>
{typedef typename remove_all_extents<T const>::type type;};

template<typename T>
struct remove_all_extents<T volatile[]>
{typedef typename remove_all_extents<T volatile>::type type;};

template<typename T>
struct remove_all_extents<T const volatile[]>
{typedef typename remove_all_extents<T const volatile>::type type;};

/***************************************************************************/

template<typename T, typename A1, typename A2, typename A3 = void, typename A4 = void>
struct is_any_of: bool_
<
		is_same<T, A1>::value
	|| is_same<T, A2>::value
	|| is_same<T, A3>::value
	|| is_same<T, A4>::value
>
{};

/***************************************************************************/

#define YAS_WRITE_ONE_SPECIALIZATION(unused, idx, seq) \
	template<> \
	struct YAS_PP_TUPLE_ELEM(2, 0, YAS_PP_SEQ_ELEM(idx, seq)) \
		<YAS_PP_TUPLE_ELEM(2, 1, YAS_PP_SEQ_ELEM(idx, seq))> {static const bool value = true;}; \
	\
	template<> \
	struct YAS_PP_TUPLE_ELEM(2, 0, YAS_PP_SEQ_ELEM(idx, seq)) \
		<YAS_PP_TUPLE_ELEM(2, 1, YAS_PP_SEQ_ELEM(idx, seq)) const> {static const bool value = true;}; \
	\
	template<> \
	struct YAS_PP_TUPLE_ELEM(2, 0, YAS_PP_SEQ_ELEM(idx, seq)) \
		<YAS_PP_TUPLE_ELEM(2, 1, YAS_PP_SEQ_ELEM(idx, seq)) volatile> {static const bool value = true;}; \
	\
	template<> \
	struct YAS_PP_TUPLE_ELEM(2, 0, YAS_PP_SEQ_ELEM(idx, seq)) \
		<YAS_PP_TUPLE_ELEM(2, 1, YAS_PP_SEQ_ELEM(idx, seq)) const volatile> {static const bool value = true;};

#define YAS_WRITE_POD_SPECIALIZATIONS(seq) \
	YAS_PP_REPEAT(YAS_PP_SEQ_SIZE(seq), YAS_WRITE_ONE_SPECIALIZATION, seq)

/***************************************************************************/

template<typename T>
struct is_pod: false_ {};

YAS_WRITE_POD_SPECIALIZATIONS(
	((is_void,void))
	((is_pod, char))
	((is_pod, wchar_t))
	((is_pod, signed char))
	((is_pod, unsigned char))
	((is_pod, short))
	((is_pod, unsigned short))
	((is_pod, int))
	((is_pod, unsigned int))
	((is_pod, long))
	((is_pod, unsigned long))
	((is_pod, long long))
	((is_pod, unsigned long long))
	((is_pod, long double))
	((is_pod, double))
	((is_pod, float))
);

/***************************************************************************/

template<typename T>
struct is_array_of_pods: bool_<
	is_array<T>::value && is_pod<typename remove_all_extents<T>::type>::value
>
{};

/***************************************************************************/

template<typename T>
struct is_enum: bool_<__is_enum(T)>
{};

/***************************************************************************/

} // namespace detail
} // namespace yas

#endif // _yas__type_traits_hpp__included_
