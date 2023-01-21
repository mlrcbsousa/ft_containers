#pragma once

#include "macros.hpp"

#if defined(STL)
	# include <vector>
	namespace ft = std;
#else
	# include "vector.hpp"
#endif

template <typename T>
void	print_vector(T& v) {
	COUT("[");
	if (v.size() <= MAX_PRINT) {
		for (typename T::iterator it = v.begin(); it != v.end() - 1; it++) {
			COUT(*it << ", ");
		}
		LOG(v.back() << "]");
	} else {
		typename T::iterator	end = v.begin() + MAX_PRINT;
		for (typename T::iterator it = v.begin(); it != end; it++) {
			COUT(*it << ", ");
		}
		LOG(" ... Vector longer then 50 elements");
	}
}

template <typename T>
void	print_metrics_vector(T& v) {
	LOG("Size: " << v.size());
	LOG("Capacity: " << v.capacity());
	if (v.capacity() < v.size()) {
		throw("Capacity smaller then Size!");
	}
}

typedef std::string	Vector_t;

typedef ft::vector<Vector_t>			Vector;
typedef ft::vector<Vector_t>::iterator	Vector_it;
typedef std::allocator<Vector_t>		Vector_allo;

void	vector_tests( void );
