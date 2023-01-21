#pragma once

#include <cstddef> // ptrdiff_t

namespace ft {

// ************************************************************************** //
//                               iterator template                            //
// ************************************************************************** //

template <typename Category,
		  typename T,
		  typename Distance = ptrdiff_t,
		  typename Pointer = T*,
		  typename Reference = T& >
struct iterator {
	typedef Pointer   pointer;
	typedef Reference reference;
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Category  iterator_category;
};

struct bidirectional_iterator_tag { /* no-op */ };
struct random_access_iterator_tag { /* no-op */ };


// ************************************************************************** //
//                         iterator_traits template                           //
// ************************************************************************** //

template <typename Iterator>
struct	iterator_traits {

	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;

};

template <typename T>
struct	iterator_traits<T*> {

	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef random_access_iterator_tag		iterator_category;

};

template <typename T>
struct	iterator_traits<const T*> {

	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef random_access_iterator_tag		iterator_category;

};


// ************************************************************************** //
//                          reverse_iterator template                         //
// ************************************************************************** //

template <class Iterator>
class reverse_iterator {

	typedef reverse_iterator	type;

public:

	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;

	explicit reverse_iterator( iterator_type it ) : current(it) { /* no-op */ }

	/* Getters */
	iterator_type base( void ) const { return current; }

	/*
	**	Based on https://cplusplus.com/reference/iterator/reverse_iterator/
	*/

	/* All iterators */
	template <typename U>
	reverse_iterator( reverse_iterator<U> const & src ) { *this = src; }
	template <typename U>
	type &	operator = ( reverse_iterator<U> const & rhs ) { current = rhs.base(); return *this; }

	~reverse_iterator( void ) { /* no-op */ }
	type &	operator ++ ( void ) { --current; return *this; }
  	type	operator ++ ( int ) { type tmp(*this); operator++(); return tmp; }

	/* Input iterators */
	pointer		operator -> ( void ) const { return &(operator*()); }

	/* Output iterators */
	reference	operator * ( void ) const { iterator_type tmp = current; return *--tmp; }

	/* Forward iterators */
	reverse_iterator( void ) : current(iterator_type()) { /* no-op */ }

	/* Bidirectional iterators */
	type &	operator -- ( void ) { ++current; return *this; }
  	type	operator -- ( int ) { type tmp(*this); operator--(); return tmp; }

	/* Random Access iterators */
	type			operator + ( difference_type n ) const { return type(current - n); }
	type			operator - ( difference_type n ) const { return type(current + n); }

	type &	operator += ( difference_type n ) { current -= n; return *this; }
	type &	operator -= ( difference_type n ) { current += n; return *this; }

	reference	operator [] ( difference_type n ) const { return current[-n - 1]; }

protected:
	iterator_type	current;

};

template< typename Iterator1, typename Iterator2 >
bool	operator == ( const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs )
{ return lhs.base() == rhs.base(); }

template< typename Iterator1, typename Iterator2 >
bool	operator != ( const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs )
{ return lhs.base() != rhs.base(); }

template< typename Iterator1, typename Iterator2 >
bool	operator < ( const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs )
{ return lhs.base() > rhs.base(); }

template< typename Iterator1, typename Iterator2 >
bool	operator <= ( const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs )
{ return lhs.base() >= rhs.base(); }

template< typename Iterator1, typename Iterator2 >
bool	operator > ( const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs )
{ return lhs.base() < rhs.base(); }

template< typename Iterator1, typename Iterator2 >
bool	operator >= ( const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs )
{ return lhs.base() <= rhs.base(); }

template< typename Iterator >
reverse_iterator<Iterator>
    operator + ( typename reverse_iterator<Iterator>::difference_type n,
               	 const reverse_iterator<Iterator>& it )
	{ return reverse_iterator<Iterator>(it.base() - n); }

template< typename Iterator >
typename reverse_iterator<Iterator>::difference_type
    operator - ( const reverse_iterator<Iterator>& lhs,
               	 const reverse_iterator<Iterator>& rhs )
	{ return rhs.base() - lhs.base(); }

}
