#include "tests/vector_tests.hpp"

void	vector_test_constructor( void ) {
	CASE("Constructor - default");

	Vector	v;

	LOG(SPEC(v.size() == 0) << "Size is 0");
	LOG(SPEC(v.capacity() == 0) << "Capacity is 0");
	LOG(SPEC(v.get_allocator() == Vector_allo()) << "Allocator is Vector_allo");
	LOG("");
}

void	vector_test_constructor_copy( void ) {
	CASE("Constructor - copy");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		src(words, words + 4);

	Vector		v(src);
	print_vector(v);

	v = Vector(src); // test assignment clears the vector
	print_vector(v);

	LOG(SPEC(v.size() == 4) << "Size is 4");
	LOG(SPEC(v.capacity() == 4) << "Capacity is 4");
	LOG(SPEC(v.get_allocator() == Vector_allo()) << "Allocator is Vector_allo");
	LOG("");
}

void	vector_test_constructor_range( void ) {
	CASE("Constructor - range");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		src(words, words + 4);
	Vector		v(src.begin(), src.end());

	print_vector(v);

	LOG(SPEC(v.size() == 4) << "Size is 4");
	LOG(SPEC(v.capacity() == 4) << "Capacity is 4");
	LOG(SPEC(v.get_allocator() == Vector_allo()) << "Allocator is Vector_allo");
	LOG("");
}

void	vector_test_constructor_fill( void ) {
	CASE("Constructor - fill");

	Vector	v(4, "100");

	print_vector(v);

	LOG(SPEC(v.size() == 4) << "Size is 4");
	LOG(SPEC(v.capacity() == 4) << "Capacity is 4");
	LOG(SPEC(v.get_allocator() == Vector_allo()) << "Allocator is Vector_allo");

	try {
		Vector	big(v.max_size() + 1, "100");
	}
	catch(const std::length_error & e) {
		LOG(e.what());
#if defined(DARWIN)
		LOG(SPEC(std::string(e.what()) == "vector") << "std::string(e.what()) == vector");
#else
		LOG(
			SPEC(std::string(e.what()) == "cannot create std::vector larger than max_size()")
				<< "std::string(e.what()) == cannot create std::vector larger than max_size()"
		);
#endif
	}

	LOG("");
}

void	vector_test_iterator( void ) {
	CASE("Iterators");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		v(words, words + 4);

	int	i = 0;
	for (Vector_it it = v.begin() ; it != v.end(); ++it, i++) {
		LOG(SPEC(*it == words[i]) << "*it == " << words[i]);
	}
	LOG("");
}

void	vector_test_riterator( void ) {
	CASE("Iterators - reverse");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		v(words, words + 4);

	int	i = 3;
	for (Vector::reverse_iterator it = v.rbegin() ; it != v.rend(); ++it, i--) {
		LOG(SPEC(*it == words[i]) << "*it == " << words[i]);
	}
	LOG("");
}

void	vector_test_const_iterator( void ) {
	CASE("Iterators - const");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		v(words, words + 4);

	int	i = 0;
	for (Vector::const_iterator it = v.begin() ; it != v.end(); ++it, i++) {
		LOG(SPEC(*it == words[i]) << "*it == " << words[i]);
	}

	Vector::const_iterator	it_const = v.begin();
	Vector_it				it = v.begin();

	LOG(SPEC(it_const == it) << "it_const == it");
	LOG(SPEC(it_const != it) << "it_const != it");
	LOG(SPEC(it_const < it) << "it_const < it");
	LOG(SPEC(it_const > it) << "it_const > it");
	LOG(SPEC(it_const <= it) << "it_const <= it");
	LOG(SPEC(it_const >= it) << "it_const >= it");

	i = 3;
	for (Vector::const_reverse_iterator it = v.rbegin() ; it != v.rend(); ++it, i--) {
		LOG(SPEC(*it == words[i]) << "*it == " << words[i]);
	}

	Vector::const_iterator	rit_const = v.begin();
	Vector_it				rit = v.begin();

	LOG(SPEC(rit_const == rit) << "rit_const == rit");
	LOG(SPEC(rit_const != rit) << "rit_const != rit");
	LOG(SPEC(rit_const < rit) << "rit_const < rit");
	LOG(SPEC(rit_const > rit) << "rit_const > rit");
	LOG(SPEC(rit_const <= rit) << "rit_const <= rit");
	LOG(SPEC(rit_const >= rit) << "rit_const >= rit");

	LOG("");
}

void	vector_test_empty( void ) {
	CASE("Empty");

	Vector	v;

	LOG(SPEC(v.empty()) << "vector is empty");
	LOG("");
}

void	vector_test_max_size( void ) {
	CASE("Max Size");

	Vector	v;

	LOG(SPEC(v.max_size()) << "max_size is big number");
	LOG("");
}

void	vector_test_resize( void ) {
	CASE("Resize");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		v(words, words + 4);

	v.resize(2);
	v.resize(4, "100");
	v.resize(6);

	print_vector(v);
	print_metrics_vector(v);

	LOG("");
}

void	vector_test_reserve( void ) {
	CASE("Reserve");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		v(words, words + 4);

	v.reserve(13);

	LOG(SPEC(v.capacity() == 13) << "Capacity is 13");

	try {
		v.reserve(v.max_size() + 1);
	}
	catch(const std::length_error & e) {
		LOG(e.what());
#if defined(DARWIN)
		LOG(
			SPEC(std::string(e.what()) == "allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size")
				<< "std::string(e.what()) == allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"
		);
#else
		LOG(SPEC(std::string(e.what()) == "vector::reserve") << "std::string(e.what()) == vector::reserve");
#endif
	}

	LOG("");
}

void	vector_test_at( void ) {
	CASE("At");

	Vector	v(3);

	v.at(0) = "foo";
	v.at(1) = "bar";
	v.at(2) = "buzz";

	LOG(SPEC(v.at(0) == "foo") << "v.at(0) == foo");
	LOG(SPEC(v.at(1) == "bar") << "v.at(1) == bar");
	LOG(SPEC(v.at(2) == "buzz") << "v.at(2) == buzz");

	print_metrics_vector(v);

	try {
		Vector_t a = v.at(3);
	}
	catch(const std::out_of_range& e) {
		LOG(e.what());
#if defined(DARWIN)
		LOG(SPEC(std::string(e.what()) == "vector") << "std::string(e.what()) == vector");
#else
		LOG(
			SPEC(std::string(e.what()) == "vector::_M_range_check: __n (which is 3) >= this->size() (which is 3)")
				<< "std::string(e.what()) == vector::_M_range_check: __n (which is 3) >= this->size() (which is 3)"
		);
#endif
	}

	LOG("");
}

void	vector_test_index_operator( void ) {
	CASE("Operator []");

	Vector	v(3);

	v[0] = "foo";
	v[1] = "bar";
	v[2] = "buzz";

	LOG(SPEC(v[0] == "foo") << "v[0] == foo");
	LOG(SPEC(v[1] == "bar") << "v[1] == bar");
	LOG(SPEC(v[2] == "buzz") << "v[2] == buzz");

	print_metrics_vector(v);

	LOG("");
}

void	vector_test_front( void ) {
	CASE("Front");

	Vector_t	words[3] = {"foo", "bar", "bazz"};
	Vector		v(words, words + 3);

	v.front() = "buzz";

	LOG(SPEC(v.front() == "buzz") << "v.front() == buzz");
	LOG("");
}

void	vector_test_back( void ) {
	CASE("Back");

	Vector_t	words[3] = {"foo", "bar", "bazz"};
	Vector		v(words, words + 3);

	v.back() = "buzz";

	LOG(SPEC(v.back() == "buzz") << "v.back() == buzz");
	LOG("");
}

void	vector_test_data( void ) {
	CASE("Data");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		v(words, words + 4);

	Vector_t *	p = v.data();

	*p = "10";
	++p;
	*p = "20";
	p[2] = "100";

	print_vector(v);

	LOG("");
}

void	vector_test_erase_fill( void ) {
	CASE("Erase - single");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		v(words, words + 4);

	// erase the 3rd element
	v.erase(v.begin() + 2);

	print_vector(v);
	print_metrics_vector(v);

	LOG("");
}

void	vector_test_erase_range( void ) {
	CASE("Erase - range");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		v(words, words + 4);

	// erase the first 2 elements
	v.erase(v.begin(), v.begin() + 2);

	print_vector(v);
	print_metrics_vector(v);

	LOG("");
}

void	vector_test_pop_back( void ) {
	CASE("Pop back");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		v(words, words + 4);

	v.pop_back();

	print_vector(v);
	print_metrics_vector(v);

	LOG("");
}

void	vector_test_push_back( void ) {
	CASE("Push back");

	Vector		v;
	Vector_t	turns[5] = {"1", "2", "3", "4", "5"};

	for (size_t i = 0; i < 5; i++) {
		v.push_back(turns[i]);

		print_vector(v);
		print_metrics_vector(v);
	}

	LOG("");
}

void	vector_test_swap( void ) {
	CASE("Swap");

	Vector_t	numbers_1[3] = {"1", "2", "3"};
	Vector_t	numbers_2[2] = {"4", "5"};

	Vector	v_1(numbers_1, numbers_1 + 3);
	Vector	v_2(numbers_2, numbers_2 + 2);

	Vector_it	v_it1 = v_1.begin() + 1;
	Vector_it	v_it2 = v_2.begin() + 1;

	Vector_t &	v_ref1 = v_1.front();
	Vector_t &	v_ref2 = v_2.front();

	print_vector(v_1);
	print_vector(v_2);

	LOG(SPEC(*v_it1 == "2") << "*v_it1 == 2");
	LOG(SPEC(*v_it2 == "5") << "*v_it2 == 5");
	LOG(SPEC(v_ref1 == "1") << "v_ref1 == 1");
	LOG(SPEC(v_ref2 == "4") << "v_ref2 == 4");

	v_1.swap(v_2);

	print_vector(v_1);
	print_vector(v_2);

	LOG(SPEC(*v_it1 == "2") << "*v_it1 == 2");
	LOG(SPEC(*v_it2 == "5") << "*v_it2 == 5");
	LOG(SPEC(v_ref1 == "1") << "v_ref1 == 1");
	LOG(SPEC(v_ref2 == "4") << "v_ref2 == 4");

	ft::swap(v_1, v_2);

	print_vector(v_1);
	print_vector(v_2);

	LOG(SPEC(*v_it1 == "2") << "*v_it1 == 2");
	LOG(SPEC(*v_it2 == "5") << "*v_it2 == 5");
	LOG(SPEC(v_ref1 == "1") << "v_ref1 == 1");
	LOG(SPEC(v_ref2 == "4") << "v_ref2 == 4");
	LOG("");
}

void	vector_test_assign_range( void ) {
	CASE("Assign - range");

	Vector		v(2, "100");
	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};

	v.assign(words, words + 4);
	v.assign(words, words + 4);
	v.assign(words, words + 4);

	print_vector(v);
	print_metrics_vector(v);

	LOG("");
}

void	vector_test_assign_fill( void ) {
	CASE("Assign - fill");

	Vector	v(2, "100");

	v.assign(4, "300");
	v.assign(4, "300");
	v.assign(4, "300");

	print_vector(v);
	print_metrics_vector(v);

	LOG("");
}

void	vector_test_insert_single( void ) {
	CASE("Insert - single");

	Vector		v(2, "999");
	print_vector(v);
	print_metrics_vector(v);
	LOG("");

	LOG(">> insert at: begin + 0, 000");
	Vector_it	it_0 = v.insert(v.begin() + 0, "000");
	(void)it_0; // invalidated because had to reallocate memory
	print_vector(v);
	print_metrics_vector(v);
	LOG("");

	LOG(">> insert at: end - 1, 100");
	Vector_it	it_1 = v.insert(v.end() - 1, "100");
	print_vector(v);
	print_metrics_vector(v);
	LOG("");

	LOG(">> insert at: it - 1, 200");
	Vector_it	it_2 = v.insert(it_1 - 1, "200");
	(void)it_2; // invalidated because had to reallocate memory
	(void)it_1; // all previous ones too
	print_vector(v);
	print_metrics_vector(v);
	LOG("");

	LOG(">> insert at: end - 2 (it_3), 300");
	LOG(">> insert at: it_3 - 1 (it_4), 400");
	LOG(">> insert at: it_4 - 2 (it_5), 500");
	Vector_it	it_3 = v.insert(v.end() - 2, "300");
	Vector_it	it_4 = v.insert(it_3 - 1, "400");
	Vector_it	it_5 = v.insert(it_4 - 2, "500");
	(void)it_5; // invalidated because had to reallocate memory
	(void)it_4; // all previous ones too
	(void)it_3;
	print_vector(v);
	print_metrics_vector(v);
	LOG("");

	LOG(">> insert at: end - 4, 400");
	Vector_it	it_6 = v.insert(v.end() - 4, "400");
	(void)it_6;
	print_vector(v);
	print_metrics_vector(v);
	LOG("");
}

void	vector_test_insert_fill( void ) {
	CASE("Insert - fill");

	Vector		v(2, "000");
	print_vector(v);
	print_metrics_vector(v);
	LOG("");

	LOG(">> insert at: 1, 1x 100");
	v.insert(v.begin() + 1, 1, "100");
	print_vector(v);
	print_metrics_vector(v);
	LOG("");

	LOG(">> insert at: 2, 16x 160");
	v.insert(v.begin() + 2, 16, "160");
	print_vector(v);
	print_metrics_vector(v);
	LOG("");

	LOG(">> insert at: 4, 32x 320");
	v.insert(v.begin() + 4, 32, "320");
	print_vector(v);
	print_metrics_vector(v);
	LOG("");

	LOG(">> insert at: 8, 64x 640");
	v.insert(v.begin() + 8, 64, "640");
	print_vector(v);
	print_metrics_vector(v);
	LOG("");
}

void	vector_test_insert_range( void ) {
	CASE("Insert - range");

	Vector		v(2, "100");
	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};

	print_vector(v);
	print_metrics_vector(v);
	LOG("");

	LOG(">> insert at: 0 - foo");
	v.insert(v.begin(), words, words + 1);
	print_vector(v);
	print_metrics_vector(v);
	LOG("");

	LOG(">> insert at: 1 - foo, bar");
	v.insert(v.begin() + 1, words, words + 2);
	print_vector(v);
	print_metrics_vector(v);
	LOG("");

	Vector		a(11, "100");

	LOG(">> insert at: 3 - 11x 100"); // less then current v.size()
	v.insert(v.begin() + 3, a.begin(), a.end());
	print_vector(v);
	print_metrics_vector(v);
	LOG("");

	Vector		b(15, "100");

	LOG(">> insert at: 3 - 15x 100"); // more then current v.size()
	v.insert(v.begin() + 3, b.begin(), b.end());
	print_vector(v);
	print_metrics_vector(v);
	LOG("");
}

void	vector_test_clear( void ) {
	CASE("Clear");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		v(words, words + 4);

	v.clear();

	print_metrics_vector(v);

	LOG("");
}

void	vector_test_get_allocator( void ) {
	CASE("Get allocator");

	Vector	v;

	LOG(SPEC(v.get_allocator() == Vector_allo()) << "v.get_allocator() == Vector_allo()");
	LOG("");
}

void	vector_test_equality( void ) {
	CASE("Equality");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		v_1(words, words + 4);
	Vector		v_2(words, words + 4);

	LOG(SPEC(v_1 == v_2) << "v_1 == v_2");
	LOG("");
}

void	vector_test_inequality( void ) {
	CASE("Inequality");

	Vector_t	words[4] = {"foo", "bar", "bazz", "buzz"};
	Vector		v_1(words, words + 4);
	Vector		v_2;

	LOG(SPEC(v_1 != v_2) << "v_1 != v_2");
	LOG("");
}

void	vector_test_inequality_comparisons( void ) {
	CASE("Inequality - comparisons");

	Vector	v_1(3, "100");
	Vector	v_2(2, "200");

	LOG(SPEC(v_1 < v_2) << "v_1 < v_2");
	LOG(SPEC(v_1 <= v_2) << "v_1 <= v_2");

	v_1	= Vector(2, "200");
	v_2 = Vector(3, "100");

	LOG(SPEC(v_1 > v_2) << "v_1 > v_2");
	LOG(SPEC(v_1 >= v_2) << "v_1 >= v_2");
	LOG("");
}

void	vector_tests( void ) {
	LOG("");
	LOG(COLOR_LPURPLE("➤ Vector Tests"));
	LOG("");
    vector_test_constructor();
    vector_test_constructor_copy();
    vector_test_constructor_range();
    vector_test_constructor_fill();
    vector_test_iterator();
    vector_test_riterator();
    vector_test_const_iterator();
    vector_test_empty();
    vector_test_max_size();
    vector_test_resize();
    vector_test_reserve();
    vector_test_at();
    vector_test_index_operator();
    vector_test_front();
    vector_test_back();
    vector_test_data();
    vector_test_erase_fill();
    vector_test_erase_range();
    vector_test_pop_back();
    vector_test_push_back();
    vector_test_swap();
	vector_test_assign_range();
    vector_test_assign_fill();
	vector_test_insert_single();
	vector_test_insert_fill();
	vector_test_insert_range();
    vector_test_clear();
    vector_test_get_allocator();
    vector_test_equality();
    vector_test_inequality();
    vector_test_inequality_comparisons();
}
