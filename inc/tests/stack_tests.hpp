#pragma once

#include "macros.hpp"

# include <deque>
# include <list>

#if defined(STL)
	# include <stack>
	# include <vector>
	namespace ft = std;
#else
	# include "stack.hpp"
#endif

typedef std::string	Stack_t;

typedef ft::stack< Stack_t >						StackVector;
typedef ft::stack< Stack_t, std::deque<Stack_t> >	StackDeque;
typedef ft::stack< Stack_t, std::list<Stack_t> >	StackList;

template <typename T, typename Container>
class IterableStack : public ft::stack<T, Container>
{
	typedef typename ft::stack<T, Container>	stack_type;
public:
	IterableStack() {}
	IterableStack(const IterableStack & src) { *this = src; }
	IterableStack(const stack_type & src): stack_type(src) {}
	IterableStack & operator=(const IterableStack & rhs)
	{
		this->c = rhs.c;
		return *this;
	}
	~IterableStack() {}

	typedef typename Container::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

// typedef IterableStack<Stack_t, StackVector_c>	IStackVector;
// typedef IterableStack<Stack_t, StackDeque_c>	IStackDeque;
// typedef IterableStack<Stack_t, StackList_c>		IStackList;

template <typename Stack>
void	print_stack(Stack & s) {
	typedef IterableStack<Stack_t, typename Stack::container_type>	IStack;
	typedef typename IStack::iterator	Iterator;

	IStack	is(s);

	COUT("[");
	if (is.size() <= MAX_PRINT) {
		for (Iterator it = is.begin(); it != --is.end(); it++) {
			COUT(*it << ", ");
		}
		LOG(is.top() << "]");
	} else {
		Iterator	end = is.begin();
		int			max = MAX_PRINT;
		while(--max) end++; // List has a Bidirectional Iterator
		for (Iterator it = is.begin(); it != end; it++) {
			COUT(*it << ", ");
		}
		LOG(" ... Stack longer then 50 elements");
	}
}

template <typename T>
void	print_metrics_stack(T& s) {
	LOG("Size: " << s.size());
}

template <typename Stack>
void	stack_test_constructor( void ) {
	CASE("Constructor - default");

	Stack	s;

	LOG(SPEC(s.size() == 0) << "Size is 0");
	LOG("");
}

template <typename Stack>
void	stack_test_constructor_copy( void ) {
	CASE("Constructor - copy");

	typedef typename Stack::container_type	Container;

	Stack_t		words[4] = {"foo", "bar", "bazz", "buzz"};
	Container	c(words, words + 4);
	Stack		src(c);
	Stack		s(src);

	print_stack(s);

	LOG(SPEC(s.size() == 4) << "Size is 4");
	LOG("");
}

template <typename Stack>
void	stack_test_constructor_assignment( void ) {
	CASE("Constructor - assignment");

	typedef typename Stack::container_type	Container;

	Stack_t		words[4] = {"foo", "bar", "bazz", "buzz"};
	Container	c(words, words + 4);
	Stack		src(c);
	Stack		s = src;

	print_stack(s);

	LOG(SPEC(s.size() == 4) << "Size is 4");
	LOG("");
}

template <typename Stack>
void	stack_test_constructor_container( void ) {
	CASE("Constructor - container");

	typedef typename Stack::container_type	Container;

	Stack_t		words[4] = {"foo", "bar", "bazz", "buzz"};
	Container	c(words, words + 4);
	Stack		s(c);

	print_stack(s);

	LOG(SPEC(s.size() == 4) << "Size is 4");
	LOG("");
}

template <typename Stack>
void	stack_test_empty( void ) {
	CASE("Empty");

	Stack	s;

	LOG(SPEC(s.empty()) << "sector is empty");
	LOG("");
}

template <typename Stack>
void	stack_test_top( void ) {
	CASE("Top");

	typedef typename Stack::container_type	Container;

	Stack_t		words[3] = {"foo", "bar", "bazz"};
	Container	src(words, words + 3);
	Stack		s(src);

	s.top() = "buzz";

	LOG(SPEC(s.top() == "buzz") << "s.top() == buzz");
	LOG("");
}

template <typename Stack>
void	stack_test_pop( void ) {
	CASE("Pop");

	typedef typename Stack::container_type	Container;

	Stack_t		words[4] = {"foo", "bar", "bazz", "buzz"};
	Container	src(words, words + 4);
	Stack		s(src);

	s.pop();

	print_stack(s);
	print_metrics_stack(s);

	LOG("");
}

template <typename Stack>
void	stack_test_push( void ) {
	CASE("Push");

	Stack	s;

	s.push("1");

	print_stack(s);
	print_metrics_stack(s);

	s.push("2");

	print_stack(s);
	print_metrics_stack(s);

	s.push("3");

	print_stack(s);
	print_metrics_stack(s);

	LOG("");
}

template <typename Stack>
void	stack_test_equality( void ) {
	CASE("Equality");

	typedef typename Stack::container_type	Container;

	Stack_t		words[4] = {"foo", "bar", "bazz", "buzz"};
	Container	src(words, words + 4);
	Stack		s_1(src);
	Stack		s_2(src);

	LOG(SPEC(s_1 == s_2) << "s_1 == s_2");
	LOG("");
}

template <typename Stack>
void	stack_test_inequality( void ) {
	CASE("Inequality");

	typedef typename Stack::container_type	Container;

	Stack_t		words[4] = {"foo", "bar", "bazz", "buzz"};
	Container	src(words, words + 4);
	Stack		s_1(src);
	Stack		s_2;

	LOG(SPEC(s_1 != s_2) << "s_1 != s_2");
	LOG("");
}

template <typename Stack>
void	stack_test_inequality_comparisons( void ) {
	CASE("Inequality - comparisons");

	typedef typename Stack::container_type	Container;

	Stack_t		words_1[3] = {"100", "100", "100"};
	Stack_t		words_2[2] = {"200", "200"};

	Container	src_1(words_1, words_1 + 3);
	Container	src_2(words_2, words_2 + 2);
	Stack		s_1(src_1);
	Stack		s_2(src_2);

	LOG(SPEC(s_1 < s_2) << "s_1 < s_2");
	LOG(SPEC(s_1 <= s_2) << "s_1 <= s_2");

	s_1	= Stack(Container(words_2, words_2 + 2));
	s_2 = Stack(Container(words_1, words_1 + 3));

	LOG(SPEC(s_1 > s_2) << "s_1 > s_2");
	LOG(SPEC(s_1 >= s_2) << "s_1 >= s_2");
	LOG("");
}

void	stack_tests( void );

