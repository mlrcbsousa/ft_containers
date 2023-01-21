#pragma once

#include "macros.hpp"

#if defined(STL)
	# include <map>
	namespace ft = std;
#else
	# include "map.hpp"
#endif

template <typename T>
void	print_map(T& m) {
	LOG("{");
	for (typename T::iterator it = m.begin(); it != m.end(); it++) {
		typename T::iterator	temp = it;

		COUT("  " << it->first << ": " << it->second);
		LOG((++temp != m.end() ? "," : ""));
	}
	LOG("}");
}

template <typename T>
void	print_metrics_map(T& v) {
	LOG("Size: " << v.size());
}

typedef std::string	Map_t;

typedef ft::map<Map_t, Map_t>	Map;
typedef Map::iterator			Map_it;
typedef Map::value_type			Pair;
typedef std::allocator<Pair>	Map_allo;

void	map_tests( void );

