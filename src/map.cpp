#include "tests/map_tests.hpp"

// Seed data
Map_t	k_aaa("k_aaa");
Map_t	k_bbb("k_bbb");
Map_t	k_ccc("k_ccc");
Map_t	k_ddd("k_ddd");
Map_t	k_eee("k_eee");
Map_t	k_fff("k_fff");

Map_t	zzz("zzz");

Map_t	v_aaa("v_aaa");
Map_t	v_bbb("v_bbb");
Map_t	v_ccc("v_ccc");
Map_t	v_ddd("v_ddd");
Map_t	v_eee("v_eee");
Map_t	v_fff("v_fff");

void	map_test_constructor( void ) {
	CASE("Constructor - default");

	Map	m;

	LOG(SPEC(m.size() == 0) << "Size is 0");
	LOG(SPEC(m.get_allocator() == Map_allo()) << "Allocator is Map_allo");
	LOG("");
}

void	map_test_constructor_copy( void ) {
	CASE("Constructor - copy");

	Map	src;

	src[k_aaa] = v_aaa;
	src[k_bbb] = v_bbb;
	src[k_ccc] = v_ccc;
	src[k_ddd] = v_ddd;
	src[k_eee] = v_eee;
	src[k_fff] = v_fff;

	Map	m(src);

	print_map(m);

	LOG(SPEC(m.size() == 6) << "Size is 6");
	LOG(SPEC(m.get_allocator() == Map_allo()) << "Allocator is Map_allo");
	LOG("");
}

void	map_test_constructor_range( void ) {
	CASE("Constructor - range");

	Map	src;

	src[k_aaa] = v_aaa;
	src[k_bbb] = v_bbb;
	src[k_ccc] = v_ccc;
	src[k_ddd] = v_ddd;
	src[k_eee] = v_eee;
	src[k_fff] = v_fff;

	Map	m(src.begin(), src.end());

	print_map(m);

	LOG(SPEC(m.size() == 6) << "Size is 6");
	LOG(SPEC(m.get_allocator() == Map_allo()) << "Allocator is Map_allo");
	LOG("");
}

void	map_test_iterator( void ) {
	CASE("Iterators");

	Map_t	words[6] = { k_aaa, k_bbb, k_ccc, k_ddd, k_eee, k_fff };
	Map		m;

	m[k_aaa] = v_aaa;
	m[k_bbb] = v_bbb;
	m[k_ccc] = v_ccc;
	m[k_ddd] = v_ddd;
	m[k_eee] = v_eee;
	m[k_fff] = v_fff;

	int	i = 0;
	for (Map_it it = m.begin() ; it != m.end(); it++, i++) {
		LOG(SPEC(it->second == m[words[i]]) << "it->second == " << m[words[i]]);
	}
	LOG("");
}

void	map_test_riterator( void ) {
	CASE("Iterators - reverse");

	Map_t	words[6] = { k_aaa, k_bbb, k_ccc, k_ddd, k_eee, k_fff };
	Map		m;

	m[k_aaa] = v_aaa;
	m[k_bbb] = v_bbb;
	m[k_ccc] = v_ccc;
	m[k_ddd] = v_ddd;
	m[k_eee] = v_eee;
	m[k_fff] = v_fff;

	int	i = 5;

	for (Map::reverse_iterator it = m.rbegin() ; it != m.rend(); it++, i--) {
		LOG(SPEC(it->second == m[words[i]]) << "it->second == " << m[words[i]]);
	}
	LOG("");
}

void	map_test_const_iterator( void ) {
	CASE("Iterators - const");

	Map_t	words[6] = { k_aaa, k_bbb, k_ccc, k_ddd, k_eee, k_fff };
	Map		m;

	m[k_aaa] = v_aaa;
	m[k_bbb] = v_bbb;
	m[k_ccc] = v_ccc;
	m[k_ddd] = v_ddd;
	m[k_eee] = v_eee;
	m[k_fff] = v_fff;

	int	i = 0;
	for (Map::const_iterator it = m.begin() ; it != m.end(); it++, i++) {
		LOG(SPEC(it->second == m[words[i]]) << "it->second == " << m[words[i]]);
	}

	Map::const_iterator	it_const = m.begin();
	Map_it				it = m.begin();

	LOG(SPEC(it_const == it) << "it_const == it");
	LOG(SPEC(it_const != it) << "it_const != it");

	i = 5;
	for (Map::const_reverse_iterator it = m.rbegin() ; it != m.rend(); ++it, i--) {
		LOG(SPEC(it->second == m[words[i]]) << "it->second == " << m[words[i]]);
	}

	Map::const_iterator	rit_const = m.begin();
	Map_it				rit = m.begin();

	LOG(SPEC(rit_const == rit) << "rit_const == rit");
	LOG(SPEC(rit_const != rit) << "rit_const != rit");

	LOG("");
}

void	map_test_empty( void ) {
	CASE("Empty");

	Map	m;

	LOG(SPEC(m.empty()) << "map is empty");
	LOG("");
}

void	map_test_max_size( void ) {
	CASE("Max Size");

	Map	m;

	LOG(SPEC(m.max_size()) << "max_size is big number");
	LOG("");
}

void	map_test_at( void ) {
	CASE("At");

	Map	m;

	m[k_aaa] = "_";
	m[k_bbb] = "_";
	m[k_ccc] = "_";
	m[k_ddd] = "_";
	m[k_eee] = "_";
	m[k_fff] = "_";

	m.at(k_aaa) = v_aaa;
	m.at(k_bbb) = v_bbb;
	m.at(k_ccc) = v_ccc;
	m.at(k_ddd) = v_ddd;
	m.at(k_eee) = v_eee;
	m.at(k_fff) = v_fff;

	LOG(SPEC(m.at(k_aaa) == "v_aaa") << "m.at(k_aaa) == v_aaa");
	LOG(SPEC(m.at(k_bbb) == "v_bbb") << "m.at(k_bbb) == v_bbb");
	LOG(SPEC(m.at(k_ccc) == "v_ccc") << "m.at(k_ccc) == v_ccc");
	LOG(SPEC(m.at(k_ddd) == "v_ddd") << "m.at(k_ddd) == v_ddd");
	LOG(SPEC(m.at(k_eee) == "v_eee") << "m.at(k_eee) == v_eee");
	LOG(SPEC(m.at(k_fff) == "v_fff") << "m.at(k_fff) == v_fff");

	print_metrics_map(m);

	try {
		Map_t	a = m.at(zzz);
	}
	catch(const std::out_of_range& e) {
		LOG(e.what());
		LOG(SPEC(std::string(e.what()) == "map::at") << "std::string(e.what()) == map::at");
	}

	LOG("");
}

void	map_test_index_operator( void ) {
	CASE("Operator []");

	Map	m;

	m[k_aaa] = v_aaa;
	m[k_bbb] = v_bbb;
	m[k_ccc] = v_ccc;
	m[k_ddd] = v_ddd;
	m[k_eee] = v_eee;
	m[k_fff] = v_fff;

	LOG(SPEC(m[k_aaa] == "v_aaa") << "m[k_aaa] == v_aaa");
	LOG(SPEC(m[k_bbb] == "v_bbb") << "m[k_bbb] == v_bbb");
	LOG(SPEC(m[k_ccc] == "v_ccc") << "m[k_ccc] == v_ccc");
	LOG(SPEC(m[k_ddd] == "v_ddd") << "m[k_ddd] == v_ddd");
	LOG(SPEC(m[k_eee] == "v_eee") << "m[k_eee] == v_eee");
	LOG(SPEC(m[k_fff] == "v_fff") << "m[k_fff] == v_fff");

	print_metrics_map(m);

	LOG("");
}

void	map_test_erase_single( void ) {
	CASE("Erase - single");

	Map	m;

	m[k_aaa] = v_aaa;
	m[k_bbb] = v_bbb;
	m[k_ccc] = v_ccc;
	m[k_ddd] = v_ddd;
	m[k_eee] = v_eee;
	m[k_fff] = v_fff;

	// erase with position
	m.erase(m.begin());

	// erase with key
	m.erase(k_bbb);

	print_map(m);
	print_metrics_map(m);

	LOG("");
}

void	map_test_erase_range( void ) {
	CASE("Erase - range");

	Map	m;

	m[k_aaa] = v_aaa;
	m[k_bbb] = v_bbb;
	m[k_ccc] = v_ccc;
	m[k_ddd] = v_ddd;
	m[k_eee] = v_eee;
	m[k_fff] = v_fff;

	// erase the first 2 elements
	m.erase(m.begin(), ++(++m.begin()));

	print_map(m);
	print_metrics_map(m);

	LOG("");
}

void	map_test_swap( void ) {
	CASE("Swap");

	Map	m_1;
	Map	m_2;

	m_1[k_aaa] = v_aaa;
	m_1[k_bbb] = v_bbb;
	m_1[k_ccc] = v_ccc;

	m_2[k_ddd] = v_ddd;
	m_2[k_eee] = v_eee;

	Map_it	m_it1 = ++m_1.begin();
	Map_it	m_it2 = ++m_2.begin();

	Map_t &	m_ref1 = m_1.begin()->second;
	Map_t &	m_ref2 = m_2.begin()->second;

	print_map(m_1);
	print_map(m_2);

	LOG(SPEC(m_it1->second == "v_bbb") << "m_it1->second == v_bbb");
	LOG(SPEC(m_it2->second == "v_eee") << "m_it2->second == v_eee");
	LOG(SPEC(m_ref1 == "v_aaa") << "m_ref1 == v_aaa");
	LOG(SPEC(m_ref2 == "v_ddd") << "m_ref2 == v_ddd");

	m_1.swap(m_2);

	print_map(m_1);
	print_map(m_2);

	LOG(SPEC(m_it1->second == "v_bbb") << "m_it1->second == v_bbb");
	LOG(SPEC(m_it2->second == "v_eee") << "m_it2->second == v_eee");
	LOG(SPEC(m_ref1 == "v_aaa") << "m_ref1 == v_aaa");
	LOG(SPEC(m_ref2 == "v_ddd") << "m_ref2 == v_ddd");

	ft::swap(m_1, m_2);

	print_map(m_1);
	print_map(m_2);

	LOG(SPEC(m_it1->second == "v_bbb") << "m_it1->second == v_bbb");
	LOG(SPEC(m_it2->second == "v_eee") << "m_it2->second == v_eee");
	LOG(SPEC(m_ref1 == "v_aaa") << "m_ref1 == v_aaa");
	LOG(SPEC(m_ref2 == "v_ddd") << "m_ref2 == v_ddd");
	LOG("");
}

void	map_test_insert_range( void ) {
	CASE("Insert - range");

	Map	m_src;
	Map	m;

	m_src[k_aaa] = v_aaa;
	m_src[k_bbb] = v_bbb;
	m_src[k_ccc] = v_ccc;
	m_src[k_ddd] = v_ddd;
	m_src[k_eee] = v_eee;
	m_src[k_fff] = v_fff;

	m.insert(m_src.begin(), m_src.end());

	print_map(m);
	print_metrics_map(m);

	LOG("");
}

void	map_test_insert_single( void ) {
	CASE("Insert - single & hint");

	Map	m;

	m[k_aaa] = v_aaa;
	m[k_bbb] = v_bbb;
	m[k_ccc] = v_ccc;

	// single
	ft::pair<Map_it, bool>		result = m.insert(Pair(k_ddd, v_ddd));

	print_map(m);
	print_metrics_map(m);

	LOG(SPEC(result.first->first == k_ddd) << "result.first->first == k_ddd");
	LOG(SPEC(result.first->second == v_ddd) << "result.first->second == v_ddd");
	LOG(SPEC(result.second == true) << "result.second == true");

	// with hint
	Map_it	m_it = m.insert(m.begin(), Pair(k_eee, v_eee));

	print_map(m);
	print_metrics_map(m);

	LOG(SPEC(m_it->first == k_eee) << "m_it->first == k_eee");
	LOG(SPEC(m_it->second == v_eee) << "m_it->second == v_eee");

	LOG("");
}

void	map_test_clear( void ) {
	CASE("Clear");

	Map	m;

	m[k_aaa] = v_aaa;
	m[k_bbb] = v_bbb;
	m[k_ccc] = v_ccc;
	m[k_ddd] = v_ddd;
	m[k_eee] = v_eee;
	m[k_fff] = v_fff;

	m.clear();

	print_map(m);
	print_metrics_map(m);

	LOG("");
}

void	map_test_get_allocator( void ) {
	CASE("Get allocator");

	Map	m;

	LOG(SPEC(m.get_allocator() == Map_allo()) << "m.get_allocator() == Map_allo()");
	LOG("");
}

void	map_test_count( void ) {
	CASE("Count");

	Map	m;

	m[k_aaa] = v_aaa;

	LOG(SPEC(m.count(k_aaa) == 1) << "m.count(k_aaa) == 1");
	LOG(SPEC(m.count(k_bbb) == 0) << "m.count(k_bbb) == 0");

	LOG("");
}

void	map_test_bounds( void ) {
	CASE("Bounds");

	Map	m;

	m[k_aaa] = v_aaa;
	m[k_bbb] = v_bbb;
	m[k_ccc] = v_ccc;
	m[k_ddd] = v_ddd;
	m[k_eee] = v_eee;
	m[k_fff] = v_fff;

	// upper
	Map_it	m_up = m.upper_bound(k_ccc);

	LOG(SPEC(m_up->first == k_ddd) << "m_up->first == k_ddd");
	LOG(SPEC(m_up->second == v_ddd) << "m_up->second == v_ddd");

	// lower
	Map_it	m_low = m.lower_bound(k_ccc);

	LOG(SPEC(m_low->first == k_ccc) << "m_low->first == k_ccc");
	LOG(SPEC(m_low->second == v_ccc) << "m_low->second == v_ccc");

	// equal
	ft::pair<Map_it, Map_it>	m_eq = m.equal_range(k_ccc);

	LOG(SPEC(m_eq.first->first == k_ccc) << "m_eq.first->first == k_ccc");
	LOG(SPEC(m_eq.first->second == v_ccc) << "m_eq.first->second == v_ccc");
	LOG(SPEC(m_eq.second->first == k_ddd) << "m_eq.second->first == k_ddd");
	LOG(SPEC(m_eq.second->second == v_ddd) << "m_eq.second->second == v_ddd");

	LOG("");
}

void	map_test_equality( void ) {
	CASE("Equality");

	Map	m_1;
	Map	m_2;

	m_1[k_aaa] = m_2[k_aaa] = v_aaa;
	m_1[k_bbb] = m_2[k_bbb] = v_bbb;
	m_1[k_ccc] = m_2[k_ccc] = v_ccc;
	m_1[k_ddd] = m_2[k_ddd] = v_ddd;
	m_1[k_eee] = m_2[k_eee] = v_eee;
	m_1[k_fff] = m_2[k_fff] = v_fff;

	LOG(SPEC(m_1 == m_2) << "m_1 == m_2");

	LOG("");
}

void	map_test_inequality( void ) {
	CASE("Inequality");

	Map	m_1;
	Map	m_2;

	m_1[k_aaa] = v_aaa;
	m_1[k_bbb] = v_bbb;
	m_1[k_ccc] = v_ccc;
	m_1[k_ddd] = v_ddd;
	m_1[k_eee] = v_eee;
	m_1[k_fff] = v_fff;

	LOG(SPEC(m_1 != m_2) << "m_1 != m_2");

	LOG("");
}

void	map_test_inequality_comparisons( void ) {
	CASE("Inequality - comparisons");

	Map	m_1;
	Map	m_2;

	m_1[k_aaa] = v_aaa;
	m_1[k_bbb] = v_bbb;
	m_1[k_ccc] = v_ccc;

	m_2[k_ddd] = v_ddd;
	m_2[k_eee] = v_eee;
	m_2[k_fff] = v_fff;

	LOG(SPEC(m_1 < m_2) << "m_1 < m_2");
	LOG(SPEC(m_1 <= m_2) << "m_1 <= m_2");

	m_1.clear();
	m_2.clear();

	m_2[k_aaa] = v_aaa;
	m_2[k_bbb] = v_bbb;
	m_2[k_ccc] = v_ccc;

	m_1[k_ddd] = v_ddd;
	m_1[k_eee] = v_eee;
	m_1[k_fff] = v_fff;

	LOG(SPEC(m_1 > m_2) << "m_1 > m_2");
	LOG(SPEC(m_1 >= m_2) << "m_1 >= m_2");

	LOG("");
}

void	map_tests( void ) {
	LOG("");
	LOG(COLOR_LPURPLE("➤ Map Tests"));
	LOG("");
    map_test_constructor();
    map_test_constructor_copy();
    map_test_constructor_range();
    map_test_iterator();
    map_test_riterator();
    map_test_const_iterator();
    map_test_empty();
    map_test_max_size();
    map_test_at();
    map_test_index_operator();
    map_test_erase_single();
    map_test_erase_range();
    map_test_swap();
    map_test_insert_range();
    map_test_insert_single();
    map_test_clear();
    map_test_get_allocator();
    map_test_count();
    map_test_bounds();
    map_test_equality();
    map_test_inequality();
    map_test_inequality_comparisons();
}
