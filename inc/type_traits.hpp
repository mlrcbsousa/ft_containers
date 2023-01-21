#pragma once

namespace ft {

// ************************************************************************** //
//                          type_traits templates                             //
// ************************************************************************** //

/*
**	https://en.cppreference.com/w/cpp/types/integral_constant
*/

template <typename T, T v>
struct integral_constant {
	static const T	                    value = v;
	typedef T                           value_type;
	typedef integral_constant<T, v>		type;
	operator value_type() const { return value; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <typename T>
struct is_integral : false_type { /* no-op */ };

template <>
struct is_integral<bool> : true_type { /* no-op */ };

template <>
struct is_integral<char> : true_type { /* no-op */ };

template <>
struct is_integral<signed char> : true_type { /* no-op */ };

template <>
struct is_integral<unsigned char> : true_type { /* no-op */ };

template <>
struct is_integral<wchar_t> : true_type { /* no-op */ };

template <>
struct is_integral<short> : true_type { /* no-op */ };

template <>
struct is_integral<unsigned short> : true_type { /* no-op */ };

template <>
struct is_integral<int> : true_type { /* no-op */ };

template <>
struct is_integral<unsigned int> : true_type { /* no-op */ };

template <>
struct is_integral<long> : true_type { /* no-op */ };

template <>
struct is_integral<long long> : true_type { /* no-op */ };

template <>
struct is_integral<unsigned long> : true_type { /* no-op */ };

template <>
struct is_integral<unsigned long long> : true_type { /* no-op */ };


// ************************************************************************** //
//                            enable_if template                              //
// ************************************************************************** //

/*
**	https://en.cppreference.com/w/cpp/types/enable_if
*/

template<bool B, typename T = void>
struct enable_if {};

template<typename T>
struct enable_if<true, T> { typedef T type; };


// ************************************************************************** //
//                            is_same template                                //
// ************************************************************************** //

/*
**	https://en.cppreference.com/w/cpp/types/is_same
*/

template<typename T, typename U>
struct is_same : false_type { /* no-op */ };

template<typename T>
struct is_same<T, T> : true_type { /* no-op */ };

}

