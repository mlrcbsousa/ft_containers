#include <map>
#include <time.h>
#include <iomanip>

#include "convert.hpp"
#include "tests/vector_tests.hpp"
#include "tests/stack_tests.hpp"
#include "tests/map_tests.hpp"
#include "tests/set_tests.hpp"

# define VECTOR  "vector"
# define STACK   "stack"
# define MAP     "map"
# define SET     "set"

typedef std::map<String, bool>	Tests;

int	print_usage(char *name) {
    ERROR("Usage: " << name << " [cycles = 1] [containers = all]");
    ERROR("  cycles:      number of test runs");
    ERROR("  containers:  " << VECTOR << " / " << STACK << " / " << MAP << " / " << SET);
	return 1;
}

double	get_total(clock_t start, clock_t end) {
	return static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

int	main( int argc, char **argv ) {
	LOG("");

	Tests	tests;

	tests[VECTOR]	= false;
	tests[STACK] 	= false;
	tests[MAP] 		= false;
	tests[SET] 		= false;

	// cycles
	int cycles = argc > 1 ? to_i(argv[1]) : 1;
    if (cycles < 1) {
        return print_usage(*argv);
    }

	// tests
	if (argc > 2) {
		for (int i = 2; i < argc; i++) {
			std::string	test(argv[i]);

			if (tests.count(test)) {
				tests[test] = true;
			} else {
				return print_usage(*argv);
			}
		}
	} else {
		tests[VECTOR]	= true;
		tests[STACK] 	= true;
		tests[MAP] 		= true;
		tests[SET] 		= true;
	}

	// timer
	clock_t	start_time = clock();
    for (int i = 0; i < cycles; i++) {
        if (tests[VECTOR])	vector_tests();
        if (tests[STACK])	stack_tests();
        if (tests[MAP])		map_tests();
        if (tests[SET])		set_tests();
    }
    clock_t	end_time = clock();

	// result
	double	total = get_total(start_time, end_time) * 1000;
    double	avg = total / cycles;

    COUT(std::setw(16) << std::left << argv[0] << " -> ");
    COUT("cycles: "	<< cycles << ", ");
    COUT("total: " << total << " ms, ");
    LOG("avg: "	<< avg << " ms");

	return 0;
}
