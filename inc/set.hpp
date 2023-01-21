#pragma once

#include <memory>
#include <string>

#include "tree/Tree.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"

namespace ft {

// ************************************************************************** //
//                               set template	                              //
// ************************************************************************** //

template <
    typename T,
    typename Compare = std::less<T>,
    typename Allocator = std::allocator<T>
>
class set {

public:
	/* Member types */
	typedef T													key_type;
	typedef T													value_type;
	typedef Compare												key_compare;
	typedef Compare												value_compare;
	typedef Allocator											allocator_type;

	typedef typename allocator_type::pointer        			pointer;
	typedef typename allocator_type::const_pointer  			const_pointer;
	typedef typename allocator_type::reference      			reference;
	typedef typename allocator_type::const_reference			const_reference;

	typedef TreeIterator<value_type>							iterator;
	typedef TreeConstIterator<value_type>						const_iterator;
	typedef TreeReverseIterator<iterator>						reverse_iterator;
	typedef TreeReverseIterator<const_iterator>					const_reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t												size_type;

private:
	typedef Tree<value_type, value_compare, allocator_type>		tree_type;

	/* Member variables */
	tree_type		tree;
	allocator_type	allocator;
	key_compare		compare;

public:
	/* Constructors */
	explicit set( const key_compare & comp = key_compare(),
				  const allocator_type & alloc = allocator_type() )
		: tree(value_compare(comp), alloc), allocator(alloc), compare(comp) { /* no-op */ } // empty

	template <class InputIterator>
	set( InputIterator first,
		 InputIterator last,
		 const key_compare & comp = key_compare(),
		 const allocator_type & alloc = allocator_type() )
		: tree(value_compare(comp), alloc), allocator(alloc), compare(comp)
		{ insert(first, last); } // range

	set( set const & s ): tree(s.tree), allocator(s.allocator), compare(s.compare) { /* no-op */ } // copy

	/* Assignment operator */
	set &	operator = ( set const & s ) {
		if (this != &s) {
			tree = s.tree;
			allocator = s.allocator;
			compare = s.compare;
		}
		return *this;
	}

	/* Destructor */
	~set( void ) { /* no-op */ }

	/* Iterators */
	iterator			begin( void ) { return iterator(tree.begin()); }
	const_iterator		begin( void ) const { return const_iterator(tree.begin()); }
	iterator			end( void ) { return iterator(tree.end()); }
	const_iterator		end( void ) const { return const_iterator(tree.end()); }
	reverse_iterator		rbegin( void ) { return reverse_iterator(iterator(tree.end())); }
	const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator(const_iterator(tree.end())); }
	reverse_iterator		rend( void ) { return reverse_iterator(tree.begin()); }
	const_reverse_iterator	rend( void ) const { return const_reverse_iterator(const_iterator(tree.begin())); }

	/* Capacity */
	bool		empty( void ) const { return tree.empty(); }
	size_type	size( void ) const { return tree.size(); }
	size_type	max_size( void ) const { return tree.max_size(); }
	allocator_type	get_allocator( void ) const { return tree.get_allocator(); }

	/* Modifiers */
	void	clear( void ) { tree.clear(); }

	pair<iterator, bool>	insert( const_reference val ) {
		if (has_key(val)) {
			return ft::make_pair(--upper_bound(val), false);
		}
		return tree.insert(val);
	} // single element

	template <typename InputIterator>
	void		insert( InputIterator first, InputIterator last ) { while (first != last) insert(*first++); } // range

	iterator	insert( iterator position, const_reference val ) {
		if (has_key(val)) {
			return --upper_bound(val);
		}
		return tree.insert(position, val);
	} // with hint

	void		erase( iterator position ) { tree.erase(position); }
	size_type	erase( const_reference key ) { return tree.erase(key); }
	void		erase( iterator first, iterator last ) { tree.erase(first, last); }

	void	swap( set & s ) {
		if (this == &s) {
			return ;
		}
		tree.swap(s.tree);
	}

	/* Lookup */
	size_type		count( const_reference key ) const { return has_key(key); }
	iterator		find( const_reference key ) { return tree.find(key); }
	const_iterator	find( const_reference key ) const { return tree.find(key); }

	pair<iterator, iterator>				equal_range( const_reference key ) { return tree.equal_range(key); }
	pair<const_iterator, const_iterator>	equal_range( const_reference key ) const { return tree.equal_range(key); }
	iterator		lower_bound( const_reference key ) { return tree.lower_bound(key); }
	iterator		upper_bound( const_reference key ) { return tree.upper_bound(key); }
	const_iterator	lower_bound( const_reference key ) const { return tree.lower_bound(key); }
	const_iterator	upper_bound( const_reference key ) const { return tree.upper_bound(key); }

	/* Observers */
	key_compare		key_comp( void ) const { return compare; }
	value_compare	value_comp( void ) const { return value_compare(key_comp()); }

private:

	bool	has_key( const_reference key ) const { return find(key) != end(); }

};

/* Non-member functions */
template <typename T, typename Compare, typename Alloc>
bool	operator == ( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs ) {
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, typename Compare, typename Alloc>
bool	operator != ( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs ) {
	return !(lhs == rhs);
}

template <typename T, typename Compare, typename Alloc>
bool	operator < ( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs ) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, typename Compare, typename Alloc>
bool	operator <= ( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs ) {
	return !(rhs < lhs);
}

template <typename T, typename Compare, typename Alloc>
bool	operator > ( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs ) {
	return rhs < lhs;
}

template <typename T, typename Compare, typename Alloc>
bool	operator >= ( const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs ) {
	return !(lhs < rhs);
}

// swap
template <typename T, typename Compare, typename Alloc>
void	swap( set<T, Compare, Alloc> & lhs, set<T, Compare, Alloc> & rhs ) { lhs.swap(rhs); }

}

