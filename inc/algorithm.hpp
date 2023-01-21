#pragma once

namespace ft {

template <typename Iterator1, typename Iterator2>
bool	equal( Iterator1 first1, Iterator1 last1, Iterator2 first2 ) {
	for (; first1 != last1; ++first1, ++first2) {
		if (!(*first1 == *first2)) {
			return false;
		}
	}
	return true;
}

template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
bool	equal( Iterator1 first1, Iterator1 last1, Iterator2 first2, BinaryPredicate predicate ) {
	for (; first1 != last1; ++first1, ++first2) {
		if (!predicate(*first1, *first2)) {
			return false;
		}
	}
	return true;
}

template <typename Iterator1, typename Iterator2>
bool	lexicographical_compare( Iterator1 first1, Iterator1 last1,
                                 Iterator2 first2, Iterator2 last2 ) {
	for (; first1 != last1; ++first1, ++first2) {
		if (first2 == last2 || *first2 < *first1) {
			return false;
		}
		else if (*first1 < *first2) {
			return true;
		}
	}
	return (first2 != last2);
}

template <typename Iterator1, typename Iterator2, typename Compare>
bool	lexicographical_compare( Iterator1 first1, Iterator1 last1,
                                 Iterator2 first2, Iterator2 last2,
								 Compare compare ) {
	for (; first1 != last1; ++first1, ++first2) {
		if (first2 == last2 || compare(*first2, *first1)) {
			return false;
		}
		else if (compare(*first1, *first2)) {
			return true;
		}
	}
	return (first2 != last2);
}

}
