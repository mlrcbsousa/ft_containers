#pragma once

#include <iostream>
#include <sstream>

template <typename T>
std::string	to_s(T in) {
	std::ostringstream	ss;

	ss << in;
	return ss.str();
}

template <typename T>
int	to_i(T in) {
	std::stringstream	ss;
	int					n;

	ss << in;
	ss >> n;
	return n;
}