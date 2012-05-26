
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

#ifndef _yas__text__boost_unordered_multiset_hpp__included_
#define _yas__text__boost_unordered_multiset_hpp__included_

#include <yas/config/config.hpp>

#if defined(YAS_HAS_BOOST_UNORDERED)
#include <yas/mpl/type_traits.hpp>
#include <yas/serializers/detail/properties.hpp>
#include <yas/serializers/detail/serializer_fwd.hpp>

#include <boost/unordered_set.hpp>

namespace yas {
namespace detail {

/***************************************************************************/

template<typename K>
struct serializer<
   e_type_type::e_type_type::not_a_pod,
   e_ser_method::use_internal_serializer,
   e_archive_type::text,
   e_direction::out,
   boost::unordered_multiset<K>
>
{
   template<typename Archive>
   static void apply(Archive& ar, const boost::unordered_multiset<K>& set) {
   }
};

template<typename K>
struct serializer<
   e_type_type::e_type_type::not_a_pod,
   e_ser_method::use_internal_serializer,
   e_archive_type::text,
   e_direction::in,
   boost::unordered_multiset<K>
>
{
   template<typename Archive>
   static void apply(Archive& ar, boost::unordered_multiset<K>& set) {
   }
};

/***************************************************************************/

} // namespace detail
} // namespace yas

#endif // defined(YAS_HAS_BOOST_UNORDERED)

#endif // _yas__text__boost_unordered_multiset_hpp__included_