/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2009.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CPPCMS_BOOST_INTRUSIVE_RBTREE_NODE_HPP
#define CPPCMS_BOOST_INTRUSIVE_RBTREE_NODE_HPP

#include <cppcms_boost/intrusive/detail/config_begin.hpp>
#include <iterator>
#include <cppcms_boost/intrusive/detail/pointer_to_other.hpp>
#include <cppcms_boost/intrusive/rbtree_algorithms.hpp>
#include <cppcms_boost/intrusive/pointer_plus_bits.hpp>
#include <cppcms_boost/intrusive/detail/mpl.hpp>

namespace cppcms_boost {
namespace intrusive {

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                Generic node_traits for any pointer type                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

//This is the compact representation: 3 pointers
template<class VoidPointer>
struct compact_rbtree_node
{
   typedef typename pointer_to_other
      <VoidPointer
      ,compact_rbtree_node<VoidPointer> >::type node_ptr;
   enum color { red_t, black_t };
   node_ptr parent_, left_, right_;
};

//This is the normal representation: 3 pointers + enum
template<class VoidPointer>
struct rbtree_node
{
   typedef typename pointer_to_other
      <VoidPointer
      ,rbtree_node<VoidPointer> >::type   node_ptr;

   enum color { red_t, black_t };
   node_ptr parent_, left_, right_;
   color color_;
};

//This is the default node traits implementation
//using a node with 3 generic pointers plus an enum
template<class VoidPointer>
struct default_rbtree_node_traits_impl
{
   typedef rbtree_node<VoidPointer> node;

   typedef typename cppcms_boost::pointer_to_other
      <VoidPointer, node>::type          node_ptr;
   typedef typename cppcms_boost::pointer_to_other
      <VoidPointer, const node>::type    const_node_ptr;

   typedef typename node::color color;

   static node_ptr get_parent(const_node_ptr n)
   {  return n->parent_;  }

   static void set_parent(node_ptr n, node_ptr p)
   {  n->parent_ = p;  }

   static node_ptr get_left(const_node_ptr n)
   {  return n->left_;  }

   static void set_left(node_ptr n, node_ptr l)
   {  n->left_ = l;  }

   static node_ptr get_right(const_node_ptr n)
   {  return n->right_;  }

   static void set_right(node_ptr n, node_ptr r)
   {  n->right_ = r;  }

   static color get_color(const_node_ptr n)
   {  return n->color_;  }

   static void set_color(node_ptr n, color c)
   {  n->color_ = c;  }

   static color black()
   {  return node::black_t;  }

   static color red()
   {  return node::red_t;  }
};

//This is the compact node traits implementation
//using a node with 3 generic pointers
template<class VoidPointer>
struct compact_rbtree_node_traits_impl
{
   typedef compact_rbtree_node<VoidPointer> node;
   typedef typename cppcms_boost::pointer_to_other
      <VoidPointer, node>::type          node_ptr;
   typedef typename cppcms_boost::pointer_to_other
      <VoidPointer, const node>::type    const_node_ptr;

   typedef pointer_plus_bits<node_ptr, 1> ptr_bit;

   typedef typename node::color color;

   static node_ptr get_parent(const_node_ptr n)
   {  return ptr_bit::get_pointer(n->parent_);  }

   static void set_parent(node_ptr n, node_ptr p)
   {  ptr_bit::set_pointer(n->parent_, p);  }

   static node_ptr get_left(const_node_ptr n)
   {  return n->left_;  }

   static void set_left(node_ptr n, node_ptr l)
   {  n->left_ = l;  }

   static node_ptr get_right(const_node_ptr n)
   {  return n->right_;  }

   static void set_right(node_ptr n, node_ptr r)
   {  n->right_ = r;  }

   static color get_color(const_node_ptr n)
   {  return (color)ptr_bit::get_bits(n->parent_);  }

   static void set_color(node_ptr n, color c)
   {  ptr_bit::set_bits(n->parent_, c != 0);  }

   static color black()
   {  return node::black_t;  }

   static color red()
   {  return node::red_t;  }
};

//Dispatches the implementation based on the boolean
template<class VoidPointer, bool Compact>
struct rbtree_node_traits_dispatch
   :  public default_rbtree_node_traits_impl<VoidPointer>
{};

template<class VoidPointer>
struct rbtree_node_traits_dispatch<VoidPointer, true>
   :  public compact_rbtree_node_traits_impl<VoidPointer>
{};

//Inherit from the detail::link_dispatch depending on the embedding capabilities
template<class VoidPointer, bool OptimizeSize = false>
struct rbtree_node_traits
   :  public rbtree_node_traits_dispatch
         < VoidPointer
         ,  OptimizeSize &&
           (max_pointer_plus_bits
            < VoidPointer
            , detail::alignment_of<compact_rbtree_node<VoidPointer> >::value 
            >::value >= 1)
         >
{};

} //namespace intrusive 
} //namespace boost 

#include <cppcms_boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_RBTREE_NODE_HPP
