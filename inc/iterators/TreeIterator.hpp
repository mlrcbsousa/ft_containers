#pragma once

#include "iterator.hpp"
#include "tree/Node.hpp"

namespace ft {

// ************************************************************************** //
//                      	TreeIterator template                         	  //
// ************************************************************************** //

template <typename T>
class TreeIterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {

	typedef TreeIterator							type;

public:

	/* Inherited from ft::iterator */
	typedef typename TreeIterator::pointer				pointer;
	typedef typename TreeIterator::reference			reference;
	typedef typename TreeIterator::value_type			value_type;
	typedef typename TreeIterator::difference_type		difference_type;
	typedef typename TreeIterator::iterator_category	iterator_category;

private:

	typedef Node<value_type>						node_type;
	typedef node_type *								node_pointer;

	node_pointer	_p;

public:

	explicit TreeIterator( node_pointer p ) : _p(p) { /* no-op */ }

	/* Getters */
	node_pointer	base( void ) const { return _p; }

	/*
	**	Based on https://cplusplus.com/reference/iterator/
	*/

	/* All iterators */
	TreeIterator( type const & src ) : _p(src._p) { /* no-op */ }
	~TreeIterator( void ) { /* no-op */ }
	type &	operator = ( type const & rhs ) { _p = rhs._p; return *this; }
	type &	operator ++ ( void ) { _p = increment(_p); return *this; }
  	type	operator ++ ( int ) { type tmp(*this); operator++(); return tmp; }

	/* Input iterators */
	inline bool		operator == ( type const & rhs ) const { return _p == rhs.base(); }
	inline bool		operator != ( type const & rhs ) const { return _p != rhs.base(); }
	reference		operator * ( void ) const { return _p->data; }
	pointer			operator -> ( void ) const { return &(_p->data); }

	/* Forward iterators */
	TreeIterator( void ) : _p(NULL) { /* no-op */ }

	/* Bidirectional iterators */
	type &	operator -- ( void ) { _p = decrement(_p); return *this; }
  	type	operator -- ( int ) { type tmp(*this); operator--(); return tmp; }

};


// ************************************************************************** //
//                      	TreeConstIterator template                        //
// ************************************************************************** //

template <typename T>
class TreeConstIterator : public ft::iterator<ft::bidirectional_iterator_tag, const T> {

	typedef TreeConstIterator		type;
	typedef TreeIterator<T>			non_const_type;

public:

	/* Inherited from ft::iterator */
	typedef typename TreeConstIterator::pointer				pointer;
	typedef typename TreeConstIterator::reference			reference;
	typedef typename TreeConstIterator::value_type			value_type;
	typedef typename TreeConstIterator::difference_type		difference_type;
	typedef typename TreeConstIterator::iterator_category	iterator_category;

private:

	typedef Node<T>						node_type;
	typedef node_type *					node_pointer;

	node_pointer	_p;

public:

	explicit TreeConstIterator( node_pointer p ) : _p(p) { /* no-op */ }

	/* Getters */
	node_pointer	base( void ) const { return _p; }

	/* All iterators */
	TreeConstIterator( non_const_type const & src ) : _p(src.base()) { /* no-op */ }
	TreeConstIterator( type const & src ) : _p(src.base()) { /* no-op */ }
	~TreeConstIterator( void ) { /* no-op */ }
	type &	operator = ( type const & rhs ) { _p = rhs._p; return *this; }
	type &	operator ++ ( void ) { _p = increment(_p); return *this; }
  	type	operator ++ ( int ) { type tmp(*this); operator++(); return tmp; }

	/* Input iterators */
	inline bool		operator == ( type const & rhs ) const { return _p == rhs.base(); }
	inline bool		operator != ( type const & rhs ) const { return _p != rhs.base(); }
	reference		operator * ( void ) const { return _p->data; }
	pointer			operator -> ( void ) const { return &(_p->data); }

	/* Forward iterators */
	TreeConstIterator( void ) : _p(NULL) { /* no-op */ }

	/* Bidirectional iterators */
	type &	operator -- ( void ) { _p = decrement(_p); return *this; }
  	type	operator -- ( int ) { type tmp(*this); operator--(); return tmp; }

};

template <typename T>
inline bool operator == ( const TreeIterator<T> & lhs, const TreeConstIterator<T> & rhs)
{ return lhs.base() == rhs.base(); }

template <typename T>
inline bool operator != ( const TreeIterator<T> & lhs, const TreeConstIterator<T> & rhs)
{ return lhs.base() != rhs.base(); }

template <typename T>
inline bool operator == ( const TreeConstIterator<T> & lhs, const TreeIterator<T> & rhs)
{ return lhs.base() == rhs.base(); }

template <typename T>
inline bool operator != ( const TreeConstIterator<T> & lhs, const TreeIterator<T> & rhs)
{ return lhs.base() != rhs.base(); }


// ************************************************************************** //
//                       TreeReverseIterator template    	                  //
// ************************************************************************** //

template <class Iterator>
class TreeReverseIterator {

	typedef TreeReverseIterator	type;

public:

	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;

	TreeReverseIterator( iterator_type it ) : current(it) { /* no-op */ }

	/* Getters */
	iterator_type base( void ) const { return current; }

	/* All iterators */
	template <typename U>
	TreeReverseIterator( TreeReverseIterator<U> const & src ): current(src.base()) { /* no-op */ }

	~TreeReverseIterator( void ) { /* no-op */ }
	type &	operator ++ ( void ) { --current; return *this; }
  	type	operator ++ ( int ) { type tmp(*this); --current; return tmp; }

	/* Input iterators */
	pointer		operator -> ( void ) const { return &(operator*()); }

	/* Output iterators */
	reference	operator * ( void ) const {
		iterator_type	tmp = current;
		tmp--;
		return *tmp;
	}

	/* Forward iterators */
	TreeReverseIterator( void ) : current() { /* no-op */ }

	/* Bidirectional iterators */
	type &	operator -- ( void ) { ++current; return *this; }
  	type	operator -- ( int ) { type tmp(*this); ++current; return tmp; }

protected:
	iterator_type	current;

};

template <typename Iterator1, typename Iterator2>
bool	operator == ( const TreeReverseIterator<Iterator1> & lhs, const TreeReverseIterator<Iterator2> & rhs )
{ return lhs.base() == rhs.base(); }

template <typename Iterator1, typename Iterator2>
bool	operator != ( const TreeReverseIterator<Iterator1> & lhs, const TreeReverseIterator<Iterator2> & rhs )
{ return lhs.base() != rhs.base(); }

template <typename Iterator>
bool	operator == ( const TreeReverseIterator<Iterator> & lhs, const TreeReverseIterator<Iterator> & rhs )
{ return lhs.base() == rhs.base(); }

template <typename Iterator>
bool	operator != ( const TreeReverseIterator<Iterator> & lhs, const TreeReverseIterator<Iterator> & rhs )
{ return lhs.base() != rhs.base(); }

}

