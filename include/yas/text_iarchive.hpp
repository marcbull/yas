
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

#ifndef _yas__text_iarchive_hpp__included_
#define _yas__text_iarchive_hpp__included_

#include <yas/detail/properties.hpp>
#include <yas/detail/has_method_serialize.hpp>
#include <yas/detail/has_function_serialize.hpp>

#include <yas/detail/selector.hpp>
#include <yas/detail/memstream.hpp>

#include <yas/serializers/text/utility/pod_serializers.hpp>
#include <yas/serializers/text/utility/usertype_serializers.hpp>
#include <yas/serializers/text/utility/autoarray_serializers.hpp>
#include <yas/serializers/text/utility/buffer_serializers.hpp>

#include <yas/detail/tools/buffer.hpp>
#include <yas/detail/tools/noncopyable.hpp>

namespace yas {

/***************************************************************************/

struct text_mem_iarchive
	:detail::imemstream<text_mem_iarchive>
	,detail::archive_information<e_archive_type::text, e_direction::in, text_mem_iarchive>
	,private detail::noncopyable
{
	text_mem_iarchive(const intrusive_buffer& o, header_t::type op = header_t::with_header)
		:detail::imemstream<text_mem_iarchive>(o)
		,detail::archive_information<e_archive_type::text, e_direction::in, text_mem_iarchive>(this, op)
	{}
	text_mem_iarchive(const shared_buffer& o, header_t::type op = header_t::with_header)
		:detail::imemstream<text_mem_iarchive>(o)
		,detail::archive_information<e_archive_type::text, e_direction::in, text_mem_iarchive>(this, op)
	{}
	text_mem_iarchive(const std::string& o, header_t::type op = header_t::with_header)
		:detail::imemstream<text_mem_iarchive>(o.c_str(), o.size())
		,detail::archive_information<e_archive_type::text, e_direction::in, text_mem_iarchive>(this, op)
	{}
	text_mem_iarchive(const char* ptr, size_t size, header_t::type op = header_t::with_header)
		:detail::imemstream<text_mem_iarchive>(ptr, size)
		,detail::archive_information<e_archive_type::text, e_direction::in, text_mem_iarchive>(this, op)
	{}

	template<typename T>
	text_mem_iarchive& operator& (T& v) {
		using namespace detail;
		serializer<
			type_propertyes<T>::value,
			serialization_method<T, text_mem_iarchive>::value,
			e_archive_type::text,
			e_direction::in,
			T
		>::apply(*this, v);

		return *this;
	}
};

/***************************************************************************/

} // namespace yas

#endif // _yas__text_iarchive_hpp__included_
