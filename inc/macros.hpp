#pragma once

#include <iostream>
#include <sstream>
#include <string>

#define LOG(x) std::cout << x << std::endl
#define ERROR(x) std::cerr << x << std::endl
#define COUT(x) std::cout << x

#define CALL(object, member_pointer) ((object).*(member_pointer))

// Colors
#define COLOR_RESET			"\033[0m"
#define COLOR_RED(x)		"\033[0;31m" << x << COLOR_RESET
#define COLOR_GREEN(x) 		"\033[0;32m" << x << COLOR_RESET
#define COLOR_LGREEN(x)		"\033[1;32m" << x << COLOR_RESET
#define COLOR_ORANGE(x)		"\033[0;33m" << x << COLOR_RESET
#define COLOR_YELLOW(x) 	"\033[1;33m" << x << COLOR_RESET
#define COLOR_BLUE(x)		"\033[0;34m" << x << COLOR_RESET
#define COLOR_PURPLE(x) 	"\033[0;35m" << x << COLOR_RESET
#define COLOR_LPURPLE(x) 	"\033[1;35m" << x << COLOR_RESET

// Test
#define MAX_PRINT 50
#define CASE(x) LOG(COLOR_BLUE("➤➤ " << x))
#define SPEC(x) ((x) ? "✔️ " : "❌ ")

typedef std::string				String;
