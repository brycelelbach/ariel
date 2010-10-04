//===-----------------------------------------------------------*- C++ -*-===//
// Copyright 2010 Bryce Lelbach
// Copyright 2001-2010 Joel de Guzman 
//
// Use, modification and distribution of this software is subject to the Boost
// Software License, Version 1.0.
//
// Relative to repository root: /credit/BOOST_LICENSE_1_0.rst
// Online: http://www.boost.org/LICENSE_1_0.txt
//===----------------------------------------------------------------------===//

#if !defined(ARIEL_ADT_TST_HXX)
#define ARIEL_ADT_TST_HXX

#include <memory>
#include <list>

#include <boost/swap.hpp>
#include <boost/call_traits.hpp>
#include <boost/detail/iterator.hpp>

namespace ariel {

template<
  typename Key,
  typename T,
  template<typename> class Alloc = std::allocator
>
class tst;

template<typename Key, typename T>
struct tst_node {
 public:
  typedef typename Key::value_type char_type;
  typedef typename boost::call_traits<T>::param_type param_type;

  tst_node (char_type id): id(id), data(0), lt(0), eq(0), gt(0) { }

  template<typename Alloc>
  static void destruct_node (tst_node* p, Alloc* alloc) {
    if (p) {
      destruct_node(p->lt, alloc);
      destruct_node(p->eq, alloc);
      destruct_node(p->gt, alloc);
      if (p->data) alloc->delete_data(p->data);
      alloc->delete_node(p);
    }
  }

  template<typename Alloc>
  static tst_node* clone_node(tst_node* p, Alloc* alloc) {
    if (p) {
      tst_node* clone = alloc->new_node(p->id);
      if (p->data) clone->data = alloc->new_data(*p->data);
      clone->lt = clone_node(p->lt, alloc);
      clone->eq = clone_node(p->eq, alloc);
      clone->gt = clone_node(p->gt, alloc);
      return clone;
    }
    return 0;
  }

  template<typename Iter, typename Filter>
  static tst_node* find (tst_node* start, Iter& first, Iter last, Filter filter) {
    if (first == last) return 0;

    for (tst_node* p = start; p;) {
      typename boost::detail::iterator_traits<Iter>::value_type
        c = filter(*first); 

      if (c == p->id) {
        if (++first == last) return p; 
        p = p->eq;
      }
      else if (c < p->id) p = p->lt;
      else p = p->gt;
    }

    return 0;
  }

  // faster version of find that does not apply any filter at all
  template<typename Iter>
  static tst_node* fast_find (tst_node* start, Iter& first, Iter last) {
    if (first == last) return 0;

    for (tst_node* p = start; p;) {
      typename boost::detail::iterator_traits<Iter>::value_type
        c = *first; 

      if (c == p->id) {
        if (++first == last) return p; 
        p = p->eq;
      }
      else if (c < p->id) p = p->lt;
      else p = p->gt;
    }

    return 0;
  }

  template<typename Iter, typename Alloc>
  static tst_node* add (
    tst_node*& start, Iter first, Iter last, param_type val, Alloc* alloc
  ) {
    if (first == last) return 0;

    for (tst_node** pp = &start;;) {
      typename boost::detail::iterator_traits<Iter>::value_type
        c = *first;

      if (*pp == 0) *pp = alloc->new_node(c);
      tst_node* p = *pp;

      if (c == p->id) {
        if (++first == last) {
          if (p->data == 0) p->data = alloc->new_data(val);
          return p;
        }
        pp = &p->eq;
      }
      else if (c < p->id) pp = &p->lt;
      else pp = &p->gt;
    }
  }

  template<typename Iter, typename Alloc>
  static void remove (tst_node*& p, Iter first, Iter last, Alloc* alloc) {
    if (p == 0 || first == last) return;

    typename boost::detail::iterator_traits<Iter>::value_type
      c = *first;

    if (c == p->id) {
      if ((++first == last) && p->data) {
        alloc->delete_data(p->data);
        p->data = 0;
      }
      remove(p->eq, first, last, alloc);
    }
    else if (c < p->id) remove(p->lt, first, last, alloc);
    else remove(p->gt, first, last, alloc);

    if (p->data == 0 && p->lt == 0 && p->eq == 0 && p->gt == 0) {
      alloc->delete_node(p);
      p = 0;
    }

    return;
  }

  template<typename F>
  static void for_each (tst_node* p, Key prefix, F f) {
    if (p) {
      for_each(p->lt, prefix, f);
      Key s = prefix + p->id;
      for_each(p->eq, s, f);
      if (p->data) f(s, *p->data);
      for_each(p->gt, prefix, f);
    }
  }

  char_type                        id;   // the node's identity character
  typename std::list<T>::iterator* data; // optional data
  tst_node*                        lt;   // left pointer
  tst_node*                        eq;   // middle pointer
  tst_node*                        gt;   // right pointer
};

template<typename Key, typename T, template<typename> class Alloc>
class tst {
 friend struct tst_node<Key, T>;

 public:
  // implementation typedefs
  typedef typename std::list<T>::iterator data_iterator;
  typedef typename boost::call_traits<T>::param_type param_type;
  typedef tst_node<Key, T> node_type;
 
  // STL Container 
  typedef T value_type;
  typedef typename std::list<value_type>::const_iterator iterator; 
  typedef typename std::list<value_type>::const_iterator const_iterator; 
  typedef typename Alloc<value_type>::reference reference;
  typedef typename Alloc<value_type>::const_reference const_reference;
  typedef typename Alloc<value_type>::pointer pointer;
  typedef typename Alloc<value_type>::difference_type difference_type;
  typedef typename Alloc<value_type>::size_type size_type;
 
  // STL AssociativeContainer 
  typedef Key key_type;

  // STL DefaultConstructible 
  tst (void): root(0) { }

  // dtor
  ~tst (void) { clear(); }

  // STL Assignable
  tst (tst const& rhs): root(0) { copy(rhs); }
  tst& operator= (tst const& rhs) { return assign(rhs); }
  void swap (tst& rhs) { boost::swap(*this, rhs); }

  // implementation for Assignable
  tst& assign (tst const& rhs) {
    if (this != &rhs) {
      clear();
      copy(rhs);
    }
    return *this;
  }

  // iterator-based lookup implementation
  template<typename Iter, typename Filter>
  iterator find (Iter& first, Iter last, Filter filter) const {
    node_type* r = node_type::find(root, first, last, filter);
    if (r && r->data) return *r->data;
    return data_list.end();
  }

  // we use a seperate find function here because the compiler
  // doesn't seem to want to optimize out an identity filter 
  template<typename Iter>
  iterator find (Iter& first, Iter last) const {
    node_type* r = node_type::fast_find(root, first, last);
    if (r && r->data) return *r->data;
    return data_list.end();
  }

  // STL AssociativeContainer
  iterator find (key_type const& key) const {
    typename key_type::const_iterator first = key.begin();
    return find(first, key.end());
  }

  // STL style lookup interface with filters
  template<typename Filter>
  iterator find (key_type const& key, Filter filter) const {
    typename key_type::const_iterator first = key.begin();
    return find(first, key.end(), filter);
  }
  
  // STL AssociativeContainer
  std::pair<iterator, iterator> equal_range (key_type const& key) const {
    typename key_type::const_iterator first = key.begin();
    iterator it = find(first, key.end());
    return std::make_pair(it, it);
  }

  // STL AssociativeContainer
  size_type count (key_type const& key) const {
    typename key_type::const_iterator first = key.begin();
    iterator it = find(first, key.end());
    return (it == end() ? 0 : 1);
  }

  // iterator-based insertation
  template<typename Iter>
  iterator add (Iter first, Iter last, param_type val) {
    node_type* r = node_type::add(root, first, last, val, this);
    if (r && r->data) return *r->data;
    return data_list.end();
  }

  // alias for add  
  template<typename Iter>
  iterator insert (Iter first, Iter last, param_type val) {
    return add(first, last, val);
  }

  // STL style insertation 
  iterator insert (key_type const& key, param_type val) {
    return add(key.begin(), key.end(), val);
  }
  
  // std::map style insertation 
  iterator insert (std::pair<key_type, param_type> kv_pair) {
    return add(kv_pair.first.begin(), kv_pair.first.end(), kv_pair.second);
  }
  
  // iterator-based removal
  template<typename Iter>
  void remove (Iter first, Iter last) {
    node_type::remove(root, first, last, this);
  }

  // alias for remove
  template<typename Iter>
  void erase (Iter first, Iter last) {
    remove(first, last);
  }
  
  // STL AssociativeContainer
  void erase (key_type const& key) {
    remove(key.begin(), key.end());
  }

  // STL AssociativeContainer 
  void clear (void) {
    node_type::destruct_node(root, this);
    root = 0;
    data_list.clear();
  }

  // recursive functor interface
  template<typename F>
  void for_each (F f) const {
    node_type::for_each(root, key_type(), f);
  }

  // STL Container 
  size_type size (void) const { return data_list.size(); }

  // STL Container (this value is dependent on key sizes in reality)
  size_type max_size (void) const { return data_list.max_size(); }
  
  // STL Container 
  iterator begin (void) const { return data_list.begin(); }
  
  // STL Container
  iterator end (void) const { return data_list.end(); }
  
  // STL Container
  bool empty (void) const { return data_list.empty(); }

 private:
  node_type* root;
  static Alloc<data_iterator> data_alloc;
  static Alloc<node_type> node_alloc;
  std::list<value_type> data_list;
 
  // shared implementation details for Assignable and DefaultConstructible 
  void copy (tst const& rhs) {
    root = node_type::clone_node(rhs.root, this);
  }

  // node creation internal interface 
  node_type* new_node (typename key_type::value_type id) {
    node_type* r = node_alloc.allocate(1);
    node_alloc.construct(r, id);
    return r;
  }

  // data creation internal interface
  data_iterator* new_data (value_type val) {
    data_iterator* r = data_alloc.allocate(1);
    data_alloc.construct(r, data_list.insert(data_list.begin(), val));
    return r;
  }

  // node deletion interface
  void delete_node (node_type* p) {
    if (p) {
      node_alloc.destroy(p);
      node_alloc.deallocate(p, 1);
    }
  }

  // data deletion interface
  void delete_data (data_iterator* p) {
    if (p) {
      data_list.erase(*p);
      data_alloc.destroy(p);
      data_alloc.deallocate(p, 1);
    }
  }
};

template<typename Key, typename T, template<typename> class Alloc>
Alloc<typename tst<Key, T, Alloc>::data_iterator> tst<Key, T, Alloc>::data_alloc;

template<typename Key, typename T, template<typename> class Alloc>
Alloc<typename tst<Key, T, Alloc>::node_type> tst<Key, T, Alloc>::node_alloc;

} // ariel

#endif // ARIEL_ADT_TST_HXX
