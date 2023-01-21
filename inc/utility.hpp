#pragma once

namespace ft {

// ************************************************************************** //
//                               pair template	                              //
// ************************************************************************** //

template <typename T1, typename T2>
struct pair {

	typedef T1	first_type;
	typedef T2	second_type;

	first_type	first;
	second_type	second;

	pair( void ): first(), second() { /* no-op */ }
	pair( const first_type & first, const second_type & second ): first(first), second(second) { /* no-op */ }
	~pair( void ) { /* no-op */ }

	template <typename U1, typename U2>
	pair( const pair<U1, U2> & p): first(p.first), second(p.second) { /* no-op */ }

	pair &	operator = ( const pair & other ) {
		if (this != &other) {
			first = other.first;
			second = other.second;
		}
		return *this;
	}
};

template <typename T1, typename T2>
bool	operator == ( const pair<T1, T2> & lhs, const pair<T1, T2> & rhs ) {
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename T1, typename T2>
bool	operator < ( const pair<T1, T2> & lhs, const pair<T1, T2> & rhs ) {
	return (lhs.first < rhs.first) || (lhs.first == rhs.first && lhs.second < rhs.second);
}

template <typename T1, typename T2>
bool	operator != ( const pair<T1, T2> & lhs, const pair<T1, T2> & rhs ) { return !(lhs == rhs); }

template <typename T1, typename T2>
bool	operator > ( const pair<T1, T2> & lhs, const pair<T1, T2> & rhs ) { return rhs < lhs; }

template <typename T1, typename T2>
bool	operator <= ( const pair<T1, T2> & lhs, const pair<T1, T2> & rhs ) { return !(rhs < lhs); }

template <typename T1, typename T2>
bool	operator >= ( const pair<T1, T2> & lhs, const pair<T1, T2> & rhs ) { return !(lhs < rhs); }

template <typename T1, typename T2>
pair<T1, T2>	make_pair( T1 first, T2 second ) { return pair<T1, T2>(first, second); }

}

