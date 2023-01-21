#pragma once

#include "vector.hpp"

namespace ft {

// ************************************************************************** //
//                               stack template                            	  //
// ************************************************************************** //

template< typename T, typename Container = ft::vector<T> >
class stack {

public:
	typedef Container							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef typename Container::reference		reference;
	typedef typename Container::const_reference	const_reference;

	explicit stack( const container_type & cont = container_type() ) : c(cont) { /* no-op */ }
	stack( const stack & other ) : c(other.c) { /* no-op */ }
	~stack( void ) { /* no-op */ }
	stack &	operator = ( const stack & other ) { c = other.c; return *this; }

	// Element access
	reference 		top( void ) { return c.back(); }
	const_reference	top( void ) const { return c.back(); }

	// Capacity
	bool		empty( void ) const { return c.size() == 0; }
	size_type	size( void ) const { return c.size(); }

	// Modifiers
	void	push( const_reference value ) { c.push_back(value); }
	void	pop( void ) { c.pop_back(); }

private:
	// Operators (non-member)
	template <typename U, typename C>
	friend bool	operator == ( const stack<U, C> & lhs, const stack<U, C> & rhs );
	// template <typename U, typename C>
	// friend bool	operator != ( const stack<U, C> & lhs, const stack<U> & rhs );
	template <typename U, typename C>
	friend bool	operator < ( const stack<U, C> & lhs, const stack<U, C> & rhs );
	// template <typename U, typename C>
	// friend bool	operator <= ( const stack<U, C> & lhs, const stack<U> & rhs );
	// template <typename U, typename C>
	// friend bool	operator > ( const stack<U, C> & lhs, const stack<U> & rhs );
	// template <typename U, typename C>
	// friend bool	operator >= ( const stack<U, C> & lhs, const stack<U> & rhs );
	/* 	https://en.cppreference.com/w/cpp/language/friend

		The friend declaration appears in a class body and grants a function or
		another class access to private and protected members of the class where
		the friend declaration appears.
	*/
protected:
	container_type	c;

};

// Operators (non-member)
template <typename T, typename Container>
bool	operator == ( const stack<T, Container> & lhs, const stack<T, Container> & rhs ) { return lhs.c == rhs.c; }

template <typename T, typename Container>
bool	operator < ( const stack<T, Container> & lhs, const stack<T, Container> & rhs ) { return lhs.c < rhs.c; }

template <typename T, typename Container>
bool	operator != ( const stack<T, Container> & lhs, const stack<T, Container> & rhs ) { return !(lhs == rhs); }

template <typename T, typename Container>
bool	operator <= ( const stack<T, Container> & lhs, const stack<T, Container> & rhs ) { return !(rhs < lhs); }

template <typename T, typename Container>
bool	operator > ( const stack<T, Container> & lhs, const stack<T, Container> & rhs ) { return rhs < lhs; }

template <typename T, typename Container>
bool	operator >= ( const stack<T, Container> & lhs, const stack<T, Container> & rhs ) { return !(lhs < rhs); }

}
