#pragma once

#include "macros.hpp"

#if defined(STL)
	# include <set>
	namespace ft = std;
#else
	# include "set.hpp"
#endif

template <typename T>
void	print_set(T& s) {
	LOG("{");
	for (typename T::iterator it = s.begin(); it != s.end(); it++) {
		typename T::iterator	temp = it;

		COUT("  " << *it);
		LOG((++temp != s.end() ? "," : ""));
	}
	LOG("}");
}

template <typename T>
void	print_metrics_set(T& v) {
	LOG("Size: " << v.size());
}

typedef std::string	Set_t;

typedef ft::set<Set_t>			Set;
typedef Set::iterator			Set_it;
typedef std::allocator<Set_t>	Set_allo;

void	set_tests( void );

