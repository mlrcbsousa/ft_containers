#include "tests/set_tests.hpp"

// Seed data
Set_t	s_aaa("s_aaa");
Set_t	s_bbb("s_bbb");
Set_t	s_ccc("s_ccc");
Set_t	s_ddd("s_ddd");
Set_t	s_eee("s_eee");
Set_t	s_fff("s_fff");

void	set_test_constructor( void ) {
	CASE("Constructor - default");

	Set	s;

	LOG(SPEC(s.size() == 0) << "Size is 0");
	LOG(SPEC(s.get_allocator() == Set_allo()) << "Allocator is Set_allo");
	LOG("");
}

void	set_test_constructor_copy( void ) {
	CASE("Constructor - copy");

	Set	src;

	src.insert(s_aaa);
	src.insert(s_bbb);
	src.insert(s_ccc);
	src.insert(s_ddd);
	src.insert(s_eee);
	src.insert(s_fff);

	Set	s(src);

	print_set(s);

	LOG(SPEC(s.size() == 6) << "Size is 6");
	LOG(SPEC(s.get_allocator() == Set_allo()) << "Allocator is Set_allo");
	LOG("");
}

void	set_test_constructor_range( void ) {
	CASE("Constructor - range");

	Set	src;

	src.insert(s_aaa);
	src.insert(s_bbb);
	src.insert(s_ccc);
	src.insert(s_ddd);
	src.insert(s_eee);
	src.insert(s_fff);

	Set	s(src.begin(), src.end());

	print_set(s);

	LOG(SPEC(s.size() == 6) << "Size is 6");
	LOG(SPEC(s.get_allocator() == Set_allo()) << "Allocator is Set_allo");
	LOG("");
}

void	set_test_iterator( void ) {
	CASE("Iterators");

	Set_t	words[6] = { s_aaa, s_bbb, s_ccc, s_ddd, s_eee, s_fff };
	Set		s;

	s.insert(s_aaa);
	s.insert(s_bbb);
	s.insert(s_ccc);
	s.insert(s_ddd);
	s.insert(s_eee);
	s.insert(s_fff);

	int	i = 0;
	for (Set_it it = s.begin() ; it != s.end(); it++, i++) {
		LOG(SPEC(*it == words[i]) << "*it == " << words[i]);
	}
	LOG("");
}

void	set_test_riterator( void ) {
	CASE("Iterators - reverse");

	Set_t	words[6] = { s_aaa, s_bbb, s_ccc, s_ddd, s_eee, s_fff };
	Set		s;

	s.insert(s_aaa);
	s.insert(s_bbb);
	s.insert(s_ccc);
	s.insert(s_ddd);
	s.insert(s_eee);
	s.insert(s_fff);

	int	i = 5;

	for (Set::reverse_iterator it = s.rbegin() ; it != s.rend(); it++, i--) {
		LOG(SPEC(*it == words[i]) << "*it == " << words[i]);
	}
	LOG("");
}

void	set_test_const_iterator( void ) {
	CASE("Iterators - const");

	Set_t	words[6] = { s_aaa, s_bbb, s_ccc, s_ddd, s_eee, s_fff };
	Set		s;

	s.insert(s_aaa);
	s.insert(s_bbb);
	s.insert(s_ccc);
	s.insert(s_ddd);
	s.insert(s_eee);
	s.insert(s_fff);

	int	i = 0;
	for (Set::const_iterator it = s.begin() ; it != s.end(); it++, i++) {
		LOG(SPEC(*it == words[i]) << "*it == " << words[i]);
	}

	Set::const_iterator	it_const = s.begin();
	Set_it				it = s.begin();

	LOG(SPEC(it_const == it) << "it_const == it");
	LOG(SPEC(it_const != it) << "it_const != it");

	i = 5;
	for (Set::const_reverse_iterator it = s.rbegin() ; it != s.rend(); ++it, i--) {
		LOG(SPEC(*it == words[i]) << "*it == " << words[i]);
	}

	Set::const_iterator	rit_const = s.begin();
	Set_it				rit = s.begin();

	LOG(SPEC(rit_const == rit) << "rit_const == rit");
	LOG(SPEC(rit_const != rit) << "rit_const != rit");

	LOG("");
}

void	set_test_empty( void ) {
	CASE("Empty");

	Set	s;

	LOG(SPEC(s.empty()) << "map is empty");
	LOG("");
}

void	set_test_max_size( void ) {
	CASE("Max Size");

	Set	s;

	LOG(SPEC(s.max_size()) << "max_size is big number");
	LOG("");
}

void	set_test_erase_single( void ) {
	CASE("Erase - single");

	Set	s;

	s.insert(s_aaa);
	s.insert(s_bbb);
	s.insert(s_ccc);
	s.insert(s_ddd);
	s.insert(s_eee);
	s.insert(s_fff);

	// erase with position
	s.erase(s.begin());

	// erase with key
	s.erase(s_bbb);

	print_set(s);
	print_metrics_set(s);

	LOG("");
}

void	set_test_erase_range( void ) {
	CASE("Erase - range");

	Set	s;

	s.insert(s_aaa);
	s.insert(s_bbb);
	s.insert(s_ccc);
	s.insert(s_ddd);
	s.insert(s_eee);
	s.insert(s_fff);

	// erase the first 2 elements
	s.erase(s.begin(), ++(++s.begin()));

	print_set(s);
	print_metrics_set(s);

	LOG("");
}

void	set_test_swap( void ) {
	CASE("Swap");

	Set	s_1;
	Set	s_2;

	s_1.insert(s_aaa);
	s_1.insert(s_bbb);
	s_1.insert(s_ccc);

	s_2.insert(s_ddd);
	s_2.insert(s_eee);

	Set_it	s_it1 = ++s_1.begin();
	Set_it	s_it2 = ++s_2.begin();

	Set_t const &	s_ref1 = *s_1.begin();
	Set_t const &	s_ref2 = *s_2.begin();

	print_set(s_1);
	print_set(s_2);

	LOG(SPEC(*s_it1 == "s_bbb") << "*s_it1 == s_bbb");
	LOG(SPEC(*s_it2 == "s_eee") << "*s_it2 == s_eee");
	LOG(SPEC(s_ref1 == "s_aaa") << "s_ref1 == s_aaa");
	LOG(SPEC(s_ref2 == "s_ddd") << "s_ref2 == s_ddd");

	s_1.swap(s_2);

	print_set(s_1);
	print_set(s_2);

	LOG(SPEC(*s_it1 == "s_bbb") << "*s_it1 == s_bbb");
	LOG(SPEC(*s_it2 == "s_eee") << "*s_it2 == s_eee");
	LOG(SPEC(s_ref1 == "s_aaa") << "s_ref1 == s_aaa");
	LOG(SPEC(s_ref2 == "s_ddd") << "s_ref2 == s_ddd");

	ft::swap(s_1, s_2);

	print_set(s_1);
	print_set(s_2);

	LOG(SPEC(*s_it1 == "s_bbb") << "*s_it1 == s_bbb");
	LOG(SPEC(*s_it2 == "s_eee") << "*s_it2 == s_eee");
	LOG(SPEC(s_ref1 == "s_aaa") << "s_ref1 == s_aaa");
	LOG(SPEC(s_ref2 == "s_ddd") << "s_ref2 == s_ddd");
	LOG("");
}

void	set_test_insert_range( void ) {
	CASE("Insert - range");

	Set	s_src;
	Set	s;

	s_src.insert(s_aaa);
	s_src.insert(s_bbb);
	s_src.insert(s_ccc);
	s_src.insert(s_ddd);
	s_src.insert(s_eee);
	s_src.insert(s_fff);

	s.insert(s_src.begin(), s_src.end());

	print_set(s);
	print_metrics_set(s);

	LOG("");
}

void	set_test_insert_single( void ) {
	CASE("Insert - single & hint");

	Set	s;

	s.insert(s_aaa);
	s.insert(s_bbb);
	s.insert(s_ccc);

	// single
	ft::pair<Set_it, bool>		result = s.insert(s_ddd);

	print_set(s);
	print_metrics_set(s);

	LOG(SPEC(*result.first == s_ddd) << "*result.first == s_ddd");
	LOG(SPEC(result.second == true) << "result.second == true");

	// with hint
	Set_it	s_it = s.insert(s.begin(), s_eee);

	print_set(s);
	print_metrics_set(s);

	LOG(SPEC(*s_it == s_eee) << "*s_it == s_eee");

	LOG("");
}

void	set_test_clear( void ) {
	CASE("Clear");

	Set	s;

	s.insert(s_aaa);
	s.insert(s_bbb);
	s.insert(s_ccc);
	s.insert(s_ddd);
	s.insert(s_eee);
	s.insert(s_fff);

	s.clear();

	print_set(s);
	print_metrics_set(s);

	LOG("");
}

void	set_test_get_allocator( void ) {
	CASE("Get allocator");

	Set	s;

	LOG(SPEC(s.get_allocator() == Set_allo()) << "s.get_allocator() == Set_allo()");
	LOG("");
}

void	set_test_count( void ) {
	CASE("Count");

	Set	s;

	s.insert(s_aaa);

	LOG(SPEC(s.count(s_aaa) == 1) << "s.count(s_aaa) == 1");
	LOG(SPEC(s.count(s_bbb) == 0) << "s.count(s_bbb) == 0");

	LOG("");
}

void	set_test_bounds( void ) {
	CASE("Bounds");

	Set	s;

	s.insert(s_aaa);
	s.insert(s_bbb);
	s.insert(s_ccc);
	s.insert(s_ddd);
	s.insert(s_eee);
	s.insert(s_fff);

	// upper
	Set_it	s_up = s.upper_bound(s_ccc);

	LOG(SPEC(*s_up == s_ddd) << "*s_up == s_ddd");

	// lower
	Set_it	s_low = s.lower_bound(s_ccc);

	LOG(SPEC(*s_low == s_ccc) << "*s_low == s_ccc");

	// equal
	ft::pair<Set_it, Set_it>	s_eq = s.equal_range(s_ccc);

	LOG(SPEC(*s_eq.first == s_ccc) << "*s_eq.first == s_ccc");
	LOG(SPEC(*s_eq.second == s_ddd) << "*s_eq.second == s_ddd");

	LOG("");
}

void	set_test_equality( void ) {
	CASE("Equality");

	Set	s_1;
	Set	s_2;

	s_1.insert(s_aaa);
	s_2.insert(s_aaa);
	s_1.insert(s_bbb);
	s_2.insert(s_bbb);
	s_1.insert(s_ccc);
	s_2.insert(s_ccc);
	s_1.insert(s_ddd);
	s_2.insert(s_ddd);
	s_1.insert(s_eee);
	s_2.insert(s_eee);
	s_1.insert(s_fff);
	s_2.insert(s_fff);

	LOG(SPEC(s_1 == s_2) << "s_1 == s_2");

	LOG("");
}

void	set_test_inequality( void ) {
	CASE("Inequality");

	Set	s_1;
	Set	s_2;

	s_1.insert(s_aaa);
	s_1.insert(s_bbb);
	s_1.insert(s_ccc);
	s_1.insert(s_ddd);
	s_1.insert(s_eee);
	s_1.insert(s_fff);

	LOG(SPEC(s_1 != s_2) << "s_1 != s_2");

	LOG("");
}

void	set_test_inequality_comparisons( void ) {
	CASE("Inequality - comparisons");

	Set	s_1;
	Set	s_2;

	s_1.insert(s_aaa);
	s_1.insert(s_bbb);
	s_1.insert(s_ccc);

	s_2.insert(s_ddd);
	s_2.insert(s_eee);
	s_2.insert(s_fff);

	LOG(SPEC(s_1 < s_2) << "s_1 < s_2");
	LOG(SPEC(s_1 <= s_2) << "s_1 <= s_2");

	s_1.clear();
	s_2.clear();

	s_2.insert(s_aaa);
	s_2.insert(s_bbb);
	s_2.insert(s_ccc);

	s_1.insert(s_ddd);
	s_1.insert(s_eee);
	s_1.insert(s_fff);

	LOG(SPEC(s_1 > s_2) << "s_1 > s_2");
	LOG(SPEC(s_1 >= s_2) << "s_1 >= s_2");

	LOG("");
}

void	set_tests( void ) {
	LOG("");
	LOG(COLOR_LPURPLE("➤ Set Tests"));
	LOG("");
    set_test_constructor();
    set_test_constructor_copy();
    set_test_constructor_range();
    set_test_iterator();
    set_test_riterator();
    set_test_const_iterator();
    set_test_empty();
    set_test_max_size();
    set_test_erase_single();
    set_test_erase_range();
    set_test_swap();
    set_test_insert_range();
    set_test_insert_single();
    set_test_clear();
    set_test_get_allocator();
    set_test_count();
    set_test_bounds();
    set_test_equality();
    set_test_inequality();
    set_test_inequality_comparisons();
}
