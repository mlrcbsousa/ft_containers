#pragma once

#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {

// ************************************************************************** //
//                      RandomAccessIterator template                         //
// ************************************************************************** //

template <typename T>
class RandomAccessIterator : public ft::iterator<ft::random_access_iterator_tag, T> {

	typedef RandomAccessIterator	type;

public:

	/* Inherited from ft::iterator */
	typedef typename RandomAccessIterator::pointer				pointer;
	typedef typename RandomAccessIterator::reference			reference;
	typedef typename RandomAccessIterator::value_type			value_type;
	typedef typename RandomAccessIterator::difference_type		difference_type;
	typedef typename RandomAccessIterator::iterator_category	iterator_category;

	RandomAccessIterator( pointer p ) : _p(p) { /* no-op */ }

	/* Getters */
	pointer	base( void ) const { return _p; }

	/*
	**	Based on https://cplusplus.com/reference/iterator/
	*/

	/* All iterators */

	template <typename Iterator>
	RandomAccessIterator( const RandomAccessIterator<Iterator> & src ) : _p(src.base()) { /* no-op */ }
	RandomAccessIterator( type const & src ) : _p(src._p) {  }
	~RandomAccessIterator( void ) { /* no-op */ }
	type &	operator = ( type const & rhs ) { _p = rhs._p; return *this; }
	type &	operator ++ ( void ) { ++_p; return *this; }
  	type	operator ++ ( int ) { type tmp(*this); operator++(); return tmp; }

	/* Input iterators */
	bool		operator == ( type const & rhs ) const { return _p == rhs._p; }
	bool		operator != ( type const & rhs ) const { return _p != rhs._p; }
	pointer		operator -> ( void ) const { return _p; }

	/* Output iterators */
	reference	operator * ( void ) const { return *_p; }

	/* Forward iterators */
	RandomAccessIterator( void ) : _p(NULL) { /* no-op */ }

	/* Bidirectional iterators */
	type &	operator -- ( void ) { --_p; return *this; }
  	type	operator -- ( int ) { type tmp(*this); operator--(); return tmp; }

	/* Random Access iterators */
	type			operator + ( difference_type n ) const { return type(_p + n); }
	difference_type	operator + ( type const & rhs ) const { return _p + rhs._p; }
	type			operator - ( difference_type n ) const { return type(_p - n); }
	difference_type operator - ( type const & rhs ) const { return _p - rhs._p; }

	bool	operator < ( const type & rhs ) const { return _p < rhs._p; }
	bool	operator > ( const type & rhs ) const { return _p > rhs._p; }
	bool	operator <= ( const type & rhs ) const { return _p <= rhs._p; }
	bool	operator >= ( const type & rhs ) const { return _p >= rhs._p; }

	type &	operator += ( difference_type n ) { _p += n; return *this; }
	type &	operator -= ( difference_type n ) { _p -= n; return *this; }

	reference	operator [] ( difference_type n ) const { return _p[n]; }

private:

	pointer _p;

};

// Non-member comparison overloads
template <typename T, typename U>
bool operator == ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<U> & rhs ) {
	return lhs.base() == rhs.base();
}

template <typename T, typename U>
bool operator != ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<U> & rhs ) {
	return lhs.base() != rhs.base();
}

template <typename T, typename U>
bool operator < ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<U> & rhs ) {
	return lhs.base() < rhs.base();
}

template <typename T, typename U>
bool operator <= ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<U> & rhs ) {
	return lhs.base() <= rhs.base();
}

template <typename T, typename U>
bool operator > ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<U> & rhs ) {
	return lhs.base() > rhs.base();
}

template <typename T, typename U>
bool operator >= ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<U> & rhs ) {
	return lhs.base() >= rhs.base();
}

template <typename T, typename U>
inline typename RandomAccessIterator<T>::difference_type
operator - ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<U> & rhs) {
	return lhs.base() - rhs.base(); }


template <typename T>
bool operator == ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<T> & rhs ) {
	return lhs.base() == rhs.base();
}

template <typename T>
bool operator != ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<T> & rhs ) {
	return lhs.base() != rhs.base();
}

template <typename T>
bool operator < ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<T> & rhs ) {
	return lhs.base() < rhs.base();
}

template <typename T>
bool operator > ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<T> & rhs ) {
	return lhs.base() > rhs.base();
}

template <typename T>
bool operator <= ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<T> & rhs ) {
	return lhs.base() <= rhs.base();
}

template <typename T>
bool operator >= ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<T> & rhs ) {
	return lhs.base() >= rhs.base();
}

template <typename T>
inline typename RandomAccessIterator<T>::difference_type
operator - ( const RandomAccessIterator<T> & lhs, const RandomAccessIterator<T> & rhs) {
	return lhs.base() - rhs.base();
}

template <typename T>
RandomAccessIterator<T>	operator + ( const typename RandomAccessIterator<T>::difference_type & lhs,
					 				 const RandomAccessIterator<T> & rhs )
{ return rhs + lhs; }

}
