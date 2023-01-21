#include "tests/stack_tests.hpp"

void	stack_tests( void ) {
	LOG("");
	LOG(COLOR_LPURPLE("➤ Stack (vector) Tests"));
	LOG("");
    stack_test_constructor<StackVector>();
    stack_test_constructor_copy<StackVector>();
    stack_test_constructor_assignment<StackVector>();
    stack_test_constructor_container<StackVector>();
    stack_test_empty<StackVector>();
    stack_test_top<StackVector>();
    stack_test_pop<StackVector>();
    stack_test_push<StackVector>();
    stack_test_equality<StackVector>();
    stack_test_inequality<StackVector>();
    stack_test_inequality_comparisons<StackVector>();
	LOG("");
	LOG(COLOR_LPURPLE("➤ Stack (deque) Tests"));
	LOG("");
    stack_test_constructor<StackDeque>();
    stack_test_constructor_copy<StackDeque>();
    stack_test_constructor_assignment<StackDeque>();
    stack_test_constructor_container<StackDeque>();
    stack_test_empty<StackDeque>();
    stack_test_top<StackDeque>();
    stack_test_pop<StackDeque>();
    stack_test_push<StackDeque>();
    stack_test_equality<StackDeque>();
    stack_test_inequality<StackDeque>();
    stack_test_inequality_comparisons<StackDeque>();
	LOG("");
	LOG(COLOR_LPURPLE("➤ Stack (list) Tests"));
	LOG("");
    stack_test_constructor<StackList>();
    stack_test_constructor_copy<StackList>();
    stack_test_constructor_assignment<StackList>();
    stack_test_constructor_container<StackList>();
    stack_test_empty<StackList>();
    stack_test_top<StackList>();
    stack_test_pop<StackList>();
    stack_test_push<StackList>();
    stack_test_equality<StackList>();
    stack_test_inequality<StackList>();
    stack_test_inequality_comparisons<StackList>();
}
