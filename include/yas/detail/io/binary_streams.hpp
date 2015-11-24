
// Copyright (c) 2010-2015 niXman (i dot nixman dog gmail dot com). All
// rights reserved.
//
// This file is part of YAS(https://github.com/niXman/yas) project.
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

#ifndef _yas__detail__io__binary_streams_hpp
#define _yas__detail__io__binary_streams_hpp

#include <yas/detail/config/config.hpp>

#include <yas/detail/io/io_exceptions.hpp>
#include <yas/detail/io/endian_conv.hpp>

#include <yas/detail/preprocessor/cat.hpp>

namespace yas {
namespace detail {

/***************************************************************************/

#define YAS_ENDIAN_TEST(et) \
	(et == big_endian && !YAS_BIG_ENDIAN()) || (et == little_endian && !YAS_LITTLE_ENDIAN())

#define YAS_SAVE_ENDIAN_SWITCH(et, var, bits) \
	enum { _need_bswap = YAS_ENDIAN_TEST(et) }; \
	var = _need_bswap ? YAS_PP_CAT(YAS_LOCAL_TO_NETWORK, bits)(var) : var

#define YAS_LOAD_ENDIAN_SWITCH(et, var, bits) \
	enum { _need_bswap = YAS_ENDIAN_TEST(et) }; \
	var = _need_bswap ? YAS_PP_CAT(YAS_NETWORK_TO_LOCAL, bits)(var) : var

/***************************************************************************/

template<typename IS, endian_t ET>
struct binary_istream {
	binary_istream(IS &is)
		:is(is)
	{}

	// for arrays
	void read(void *ptr, std::size_t size) {
		YAS_THROW_ON_READ_ERROR(size, !=, is.read(ptr, size));
	}

	// for chars & bools
	template<typename T>
	void read(T &v, YAS_ENABLE_IF_IS_ANY_OF(T, char, signed char, unsigned char, bool)) {
		YAS_THROW_ON_READ_ERROR(sizeof(v), !=, is.read(&v, sizeof(v)));
	}

	// for shorts
	template<typename T>
	void read(T &v, YAS_ENABLE_IF_IS_ANY_OF(T, std::int16_t, std::uint16_t)) {
		YAS_THROW_ON_READ_ERROR(sizeof(v), !=, is.read(&v, sizeof(v)));
		YAS_LOAD_ENDIAN_SWITCH(ET, v, 16);
	}

	// for 32-bit ints
	template<typename T>
	void read(T &v, YAS_ENABLE_IF_IS_ANY_OF(T, std::int32_t, std::uint32_t)) {
		YAS_THROW_ON_READ_ERROR(sizeof(v), !=, is.read(&v, sizeof(v)));
		YAS_LOAD_ENDIAN_SWITCH(ET, v, 32);
	}

	// for 64-bit ints
	template<typename T>
	void read(T &v, YAS_ENABLE_IF_IS_ANY_OF(T, std::int64_t, std::uint64_t)) {
		YAS_THROW_ON_READ_ERROR(sizeof(v), !=, is.read(&v, sizeof(v)));
		YAS_LOAD_ENDIAN_SWITCH(ET, v, 64);
	}

	// for floats and doubles
	template<typename T>
	void read(T &v, YAS_ENABLE_IF_IS_ANY_OF(T, float, double)) {
		std::uint8_t buf[sizeof(T)];
		YAS_THROW_ON_READ_ERROR(sizeof(T), !=, is.read(buf, sizeof(buf)));
		endian_convertor<YAS_ENDIAN_TEST(ET)>::from_network(v, buf);
	}

private:
	IS &is;
};

template<typename OS, endian_t ET>
struct binary_ostream {
	binary_ostream(OS &os)
		:os(os)
	{}

	// for arrays
	void write(const void *ptr, std::size_t size) {
		YAS_THROW_ON_WRITE_ERROR(size, !=, os.write(ptr, size));
	}

	// for chars & bools
	template<typename T>
	void write(T v, YAS_ENABLE_IF_IS_ANY_OF(T, char, signed char, unsigned char, bool)) {
		YAS_THROW_ON_WRITE_ERROR(sizeof(v), !=, os.write(&v, sizeof(v)));
	}

	// for shorts
	template<typename T>
	void write(T v, YAS_ENABLE_IF_IS_ANY_OF(T, std::int16_t, std::uint16_t)) {
		YAS_SAVE_ENDIAN_SWITCH(ET, v, 16);
		YAS_THROW_ON_WRITE_ERROR(sizeof(v), !=, os.write(&v, sizeof(v)));
	}

	// for 32-bit ints
	template<typename T>
	void write(T v, YAS_ENABLE_IF_IS_ANY_OF(T, std::int32_t, std::uint32_t)) {
		YAS_SAVE_ENDIAN_SWITCH(ET, v, 32);
		YAS_THROW_ON_WRITE_ERROR(sizeof(v), !=, os.write(&v, sizeof(v)));
	}

	// for 64-bit ibts
	template<typename T>
	void write(T v, YAS_ENABLE_IF_IS_ANY_OF(T, std::int64_t, std::uint64_t)) {
		YAS_SAVE_ENDIAN_SWITCH(ET, v, 64);
		YAS_THROW_ON_WRITE_ERROR(sizeof(v), !=, os.write(&v, sizeof(v)));
	}

	// for floats and doubles
	template<typename T>
	void write(const T &v, YAS_ENABLE_IF_IS_ANY_OF(T, float, double)) {
		std::uint8_t buf[sizeof(T)];
		endian_convertor<YAS_ENDIAN_TEST(ET)>::to_network(buf, v);
		YAS_THROW_ON_WRITE_ERROR(sizeof(buf), !=, os.write(buf, sizeof(buf)));
	}

private:
	OS &os;
};

/***************************************************************************/

} // ns detail
} // ns yas

#endif // _yas__detail__io__binary_streams_hpp
