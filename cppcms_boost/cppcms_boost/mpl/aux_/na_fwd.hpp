
#ifndef CPPCMS_BOOST_MPL_AUX_NA_FWD_HPP_INCLUDED
#define CPPCMS_BOOST_MPL_AUX_NA_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: na_fwd.hpp 49267 2008-10-11 06:19:02Z agurtovoy $
// $Date: 2008-10-11 02:19:02 -0400 (Sat, 11 Oct 2008) $
// $Revision: 49267 $

#include <cppcms_boost/mpl/aux_/adl_barrier.hpp>

CPPCMS_BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

// n.a. == not available
struct na
{
    typedef na type;
    enum { value = 0 };
};

CPPCMS_BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE
CPPCMS_BOOST_MPL_AUX_ADL_BARRIER_DECL(na)

#endif // BOOST_MPL_AUX_NA_FWD_HPP_INCLUDED
