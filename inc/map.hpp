#pragma once

#include <memory>
#include <string>
#include <functional>

#include "tree/Tree.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"

namespace ft {

// ************************************************************************** //
//                               map template	                              //
// ************************************************************************** //

template <
    typename Key,
    typename T,
    typename Compare = std::less<Key>,
    typename Allocator = std::allocator< ft::pair<const Key, T> >
>
class map {

public:
	/* Member types */
	typedef Key													key_type;
	typedef T													mapped_type;
	typedef Compare												key_compare;
	typedef Allocator											allocator_type;

	typedef pair<const key_type, mapped_type>					value_type;
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

	class value_compare : std::binary_function<value_type, value_type, bool> {
		friend class map;
		public:
			bool operator () ( const value_type & lhs, const value_type & rhs ) const {
				return compare(lhs.first, rhs.first);
			}
		protected:
			key_compare compare;
			value_compare( key_compare comp ) : compare(comp) { /* no-op */ }
	};

private:
	typedef Tree<value_type, value_compare, allocator_type>		tree_type;
	typedef mapped_type &										mapped_reference;
	typedef key_type const &									const_key_reference;
	typedef mapped_type const &									const_mapped_reference;

	/* Member variables */
	tree_type		tree;
	allocator_type	allocator;
	key_compare		compare;

public:
	/* Constructors */
	explicit map( const key_compare & comp = key_compare(),
				  const allocator_type & alloc = allocator_type() )
		: tree(value_compare(comp), alloc), allocator(alloc), compare(comp) { /* no-op */ } // empty

	template <class InputIterator>
	map( InputIterator first,
		 InputIterator last,
		 const key_compare & comp = key_compare(),
		 const allocator_type & alloc = allocator_type() )
		: tree(value_compare(comp), alloc), allocator(alloc), compare(comp)
		{ insert(first, last); } // range

	map( map const & m ): tree(m.tree), allocator(m.allocator), compare(m.compare) { /* no-op */ } // copy

	/* Assignment operator */
	map &	operator = ( map const & m ) {
		if (this != &m) {
			tree = m.tree;
			allocator = m.allocator;
			compare = m.compare;
		}
		return *this;
	}

	/* Destructor */
	~map( void ) { /* no-op */ }

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

	/* Element access */
	mapped_reference	at( const key_type & key ) {
		iterator	it = find(key);

		if (it == end()) {
			throw std::out_of_range("map::at");
		}
		return it->second;
	}

	const_mapped_reference	at( const_key_reference key ) const { return at(key); }

	mapped_reference	operator [] ( const_key_reference key ) {
		iterator	it = find(key);
		if (it != end()) {
			return it->second;
		}

		pair<iterator, bool>	result = insert(ft::make_pair(key, mapped_type()));
		return result.first->second;
	}

	/* Modifiers */
	void	clear( void ) { tree.clear(); }

	pair<iterator, bool>	insert( const_reference val ) {
		if (has_key(val.first)) {
			return ft::make_pair(--upper_bound(val.first), false);
		}
		return tree.insert(val);
	} // single element

	template <typename InputIterator>
	void		insert( InputIterator first, InputIterator last ) { while (first != last) insert(*first++); } // range

	iterator	insert( iterator position, const_reference val ) {
		if (has_key(val.first)) {
			return --upper_bound(val.first);
		}
		return tree.insert(position, val);
	} // with hint

	void		erase( iterator position ) { tree.erase(position); }
	size_type	erase( const_key_reference key ) { return tree.erase(ft::make_pair(key, mapped_type())); }
	void		erase( iterator first, iterator last ) { tree.erase(first, last); }

	void	swap( map & m ) {
		if (this == &m) {
			return ;
		}
		tree.swap(m.tree);
	}

	/* Lookup */
	size_type		count( const_key_reference key ) const { return tree.count(ft::make_pair(key, mapped_type())); }
	iterator		find( const_key_reference key ) { return iterator(tree.find(ft::make_pair(key, mapped_type()))); }
	const_iterator	find( const_key_reference key ) const { return const_iterator(tree.find(ft::make_pair(key, mapped_type()))); }

	pair<iterator, iterator>				equal_range( const_key_reference key ) { return tree.equal_range(ft::make_pair(key, mapped_type())); }
	pair<const_iterator, const_iterator>	equal_range( const_key_reference key ) const { return tree.equal_range(ft::make_pair(key, mapped_type())); }
	iterator		lower_bound( const_key_reference key ) { return tree.lower_bound(ft::make_pair(key, mapped_type())); }
	iterator		upper_bound( const_key_reference key ) { return tree.upper_bound(ft::make_pair(key, mapped_type())); }
	const_iterator	lower_bound( const_key_reference key ) const { return tree.lower_bound(ft::make_pair(key, mapped_type())); }
	const_iterator	upper_bound( const_key_reference key ) const { return tree.upper_bound(ft::make_pair(key, mapped_type())); }

	/* Observers */
	key_compare		key_comp( void ) const { return compare; }
	value_compare	value_comp( void ) const { return value_compare(key_comp()); }

private:

	bool	has_key( const_key_reference key ) const { return find(key) != end(); }

};

/* Non-member functions */
template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator == ( const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs ) {
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator != ( const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs ) {
	return !(lhs == rhs);
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator < ( const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs ) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator <= ( const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs ) {
	return !(rhs < lhs);
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator > ( const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs ) {
	return rhs < lhs;
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator >= ( const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs ) {
	return !(lhs < rhs);
}

// swap
template <typename Key, typename T, typename Compare, typename Alloc>
void	swap( map<Key, T, Compare, Alloc> & lhs, map<Key, T, Compare, Alloc> & rhs ) { lhs.swap(rhs); }

}

