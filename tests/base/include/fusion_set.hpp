
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

#ifndef _yas_test__fusion_set_hpp__included_
#define _yas_test__fusion_set_hpp__included_

/***************************************************************************/

#if defined(YAS_HAS_BOOST_FUSION)

template<typename archive_traits>
bool fusion_set_test(const char* archive_type, const char* io_type) {
	((void)io_type);
	((void)archive_type);
#if 0

	typedef boost::fusion::set<int, int> set;
	set s1(33, 44), s2;

	std::cout << "size = " << boost::fusion::size(s1) << std::endl;
	std::cout << "0 = " << boost::fusion::at_key<int>(s1) << std::endl;
	std::cout << "1 = " << boost::fusion::at_key<int>(s1) << std::endl;

	OA oa;
	oa & s1;

	IA ia(oa.get_intrusive_buffer());
	ia & s2;

	if ( s1 != s2 ) {
		std::cout << "FUSION_SET deserialization error!" << std::endl;
		return false;
	}
#endif

	return true;
}

#endif // #if defined(YAS_HAS_BOOST_FUSION)

/***************************************************************************/

#endif // _yas_test__fusion_set_hpp__included_