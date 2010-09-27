// (C) Copyright 2010 Bryce Lelbach
// Copyright (c) 2001-2010 Joel de Guzman
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /doc/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
#if !defined(ARIEL_TST_HPP)
#define ARIEL_TST_HPP

#include <boost/call_traits.hpp>
#include <boost/detail/iterator.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at_c.hpp>

namespace ariel {

template<class Key, class T>
class tst_node {
 public:
  typedef typename Key::value_type id_type;
  
  tst_node(id_type id): id(id), data(0), lt(0), eq(0), gt(0) { }

  template<class Owner>
  static void destruct (tst_node* p, Owner* owner) {
    if (p) {
      if (p->data)
        owner->delete_data(p->data);
      destruct(p->lt, owner);
      destruct(p->eq, owner);
      destruct(p->gt, owner);
      owner->delete_node(p);
    }
  }

  template<class Owner>
  static tst_node* clone (tst_node* p, Owner* owner) {
    if (p) {
      tst_node* clone = owner->new_node(p->id);
      if (p->data)
        clone->data = owner->new_data(*p->data);
      clone->lt = clone(p->lt, owner);
      clone->eq = clone(p->eq, owner);
      clone->gt = clone(p->gt, owner);
      return clone;
    }
    return 0;
  }

  template<class I, typename Filter>
  static T* find (tst_node*& start, I& first, I last, Filter filter) {
    if (first == last)
      return 0;

    I i = first;
    I latest = first;
    tst_node* p = start;
    T* found = 0;

    while (p && i != last) {
      id_type c = filter(*i); // filter only the input

      if (c == p->id) {
        if (p->data) {
          found = p->data;
          latest = i;
        }
        p = p->eq;
        i++;
      }
      else if (c < p->id) p = p->lt;
      else p = p->gt;
    }

    if (found)
      first = ++latest; // one past the last matching char

    return found;
  }

  template<class I, typename Owner>
  static std::pair<T*, bool> insert (
    tst_node*& start, I first, I last, T val, Owner* owner
  ) {
    if (first == last)
      return std::pair<T*, bool>(0, 0);

    for (tst_node** pp = &start; ; ) {
      id_type c = *first;

      if (*pp == 0)
        *pp = owner->new_node(c);
      tst_node* p = *pp;

      if (c == p->id) {
        if (++first == last) {
          // if the node doesn't exist, create it
          if (p->data == 0) {
            p->data = owner->new_data(val);   
            return std::pair<T*, bool>(p->data, true);
          }

          // the node already exists, so we return it
          return std::pair<T*, bool>(p->data, false);
        }
        pp = &p->eq;
      }

      else if (c < p->id) pp = &p->lt;
      else pp = &p->gt;
    }
  }

  template<class I, typename Owner>
  static void remove (tst_node*& p, I first, I last, Owner* owner) {
    if (p == 0 || first == last)
      return;

    id_type c = *first;

    if (c == p->id) {
      if (++first == last) {
        if (p->data) {
          owner->delete_data(p->data);
          p->data = 0;
        }
      }

      remove(p->eq, first, last, owner);
    }

    else if (c < p->id) remove(p->lt, first, last, owner);
    else remove(p->gt, first, last, owner);

    if (p->data == 0 && p->lt == 0 && p->eq == 0 && p->gt == 0) {
      owner->delete_node(p);
      p = 0;
    }
  }

  template<class F>
  static void for_each (tst_node* p, Key prefix, F f) {
    if (p) {
      for_each(p->lt, prefix, f);
      Key s = prefix + p->id;
      for_each(p->eq, s, f);
      if (p->data) f(s, *p->data);
      for_each(p->gt, prefix, f);
    }
  }

  class for_each_iterator {
   private:
    tst_node* element;
    tst_node* parent;
   
    for_each_iterator(tst_node* new_element, tst_node* new_parent):
      element(new_element), parent(new_parent) { }

   public:
  };

 private:
  id_type id;     // the node's identity character
  T* data;        // optional data
  tst_node* lt;   // left pointer
  tst_node* eq;   // middle pointer
  tst_node* gt;   // right pointer
};

struct tst_pass_through {
  template<class Char>
  Char operator() (Char i) const { return i; }
};

template<
  class Key, class T,
  template<class> class NodeAlloc = std::allocator, 
  class DataAlloc = std::allocator<T>
>
class tst {
 friend class tst_node<Key, T>;

 public:
  // implementation typedefs
  typedef tst_node<Key, T> node_type;
  typedef typename Key::value_type id_type;

  // STL typedefs
  typedef Key key_type;
  typedef typename DataAlloc::value_type mapped_type;

  typedef std::pair<key_type, mapped_type> value_type;
  
  typedef typename DataAlloc::difference_type difference_type;
  typedef typename DataAlloc::size_type size_type;

  tst (void): root(0) { }
  tst (tst const& rhs): root(node_type::clone(rhs.root, this)) { }
  
  ~tst (void) { clear(); }

  tst& operator= (tst const& rhs) {
    if (this != &rhs) {
      clear();
      root = node_type::clone(rhs.root, this);
    }
    return *this;
  }

  template<class I, typename Filter>
  mapped_type* find (I& first, I last, Filter filter) const {
    return node_type::find(root, first, last, filter);
  }

  template<class I>
  mapped_type* find (I& first, I last) const {
    return find(first, last, tst_pass_through());
  }

  std::pair<mapped_type*, bool> insert (value_type kv_pair) {
    return node_type::insert(
      root, kv_pair.first.begin(), kv_pair.first.end(), kv_pair.second, this
    );
  }
  
  template<class I>
  std::pair<mapped_type*, bool> insert (I first, I last, mapped_type val) {
    return node_type::insert(root, first, last, val, this);
  }

  template<class I>
  void remove (I first, I last) {
    node_type::remove(root, first, last, this);
  }

  void clear (void) {
    node_type::destruct(root, this);
    root = 0;
  }

  template<class F>
  void for_each (F f) const {
    node_type::for_each(root, key_type(), f);
  }

 private:
  node_type* root;

  // allocator interface 
  NodeAlloc<node_type> node_alloc;
  DataAlloc data_alloc;

  node_type* new_node (id_type id) {
    node_type* n = node_alloc.allocate(1);
    node_alloc.construct(n, id);
    return n;
  }

  mapped_type* new_data (mapped_type val) {
    mapped_type* d = data_alloc.allocate(1);
    data_alloc.construct(d, val);
    return d;
  }

  void delete_node (node_type* p) {
    if (!p) return;
    node_alloc.destroy(p);
    node_alloc.deallocate(p, 1);
  }

  void delete_data (mapped_type* p) {
    if (!p) return;
    data_alloc.destroy(p);
    data_alloc.deallocate(p, 1);
  }
};

} // ariel

#endif // ARIEL_TST_HPP

