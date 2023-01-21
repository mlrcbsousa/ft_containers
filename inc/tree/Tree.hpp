#pragma once

#include <memory>

#include "macros.hpp"
#include "tree/Node.hpp"
#include "iterators/TreeIterator.hpp"
#include "utility.hpp" // pair

namespace ft {

// ************************************************************************** //
//                               Tree template	                              //
// ************************************************************************** //

template <
	typename T,
	typename Compare = std::less<T>,
	typename Allocator = std::allocator<T>
>
class Tree {

public:
	/* Member types */
	typedef T												value_type;
	typedef Compare											value_compare;
	typedef Allocator										allocator_type;
	typedef size_t 											size_type;
	typedef ptrdiff_t 										difference_type;

	typedef Tree<value_type, value_compare, Allocator>		tree_type;
	typedef Node<value_type>								node_type;
	typedef node_type *										node_pointer;
	typedef const node_pointer								const_node_pointer;
	typedef node_type &										node_reference;

	typedef value_type &									reference;
	typedef value_type *									pointer;
	typedef const pointer									const_pointer;
	typedef value_type const &								const_reference;

	typedef TreeIterator<value_type>						iterator;
	typedef TreeConstIterator<value_type>					const_iterator;
	typedef TreeReverseIterator<iterator>					reverse_iterator;
	typedef TreeReverseIterator<const_iterator>				const_reverse_iterator;

	typedef typename Allocator::template rebind<node_type>::other		node_allocator_type;

private:

	/* Member variables */
	node_pointer		_root, nil;
	/*
		The `nil` node is used as the leaf nodes in the tree and it helps simplify some of the tree
		operations by eliminating the need to check for null pointers.

		It's important to note that the `nil` node should be created once and it should be used throughout
		the lifetime of the tree.

		A sentinel node serves as a placeholder for null pointers in the tree. Instead of using null
		pointers, the tree uses the sentinel node as the leaf nodes.

		The use of a sentinel node eliminates the need to check for null pointers in many of the tree
		operations, such as insertions and deletions. This makes the code simpler and more efficient, by
		avoiding the need to check for null pointers in many cases.

		It also helps to simplify the implementation of some of the methods of the Red-Black Tree, such as
		the minimum and maximum methods, because the tree is guaranteed to have a certain structure, and the
		nil node is guaranteed to be a leaf node, the implementation of these methods can be simplified by
		assuming that the tree has this structure.

		In addition, using a sentinel node also makes it easy to implement the successor and predecessor
		methods, as you don't need to check for the end of the tree, because you know that the nil is always
		the leaf node.

		It's also worth mentioning that it makes it easier to implement the tree traversals, because it
		eliminates the need to check for null pointers during the traversal.
	*/
	size_type			_size;
	value_compare		compare;
	node_allocator_type	allocator;

public:
	/* Constructors */
	explicit Tree( const value_compare & comp = value_compare(),
				   const node_allocator_type & alloc = node_allocator_type() )
	: _root(NULL), nil(NULL), _size(0), compare(comp), allocator(alloc) { nil_create(); } // default

	template <class InputIterator>
	Tree( InputIterator first,
		  InputIterator last,
		  const value_compare & comp = value_compare(),
		  const node_allocator_type & alloc = node_allocator_type() ) : compare(comp), allocator(alloc) {
		nil_create();
		while (first != last) {
			insert(*first);
			first++;
		}
	} // range

	Tree( tree_type const & tree )
		: _root(NULL), nil(NULL), _size(0), compare(tree.compare), allocator(tree.allocator) {
		nil_create();
		insert(tree.begin(), tree.end());
	} // copy

	/* Assignment operator */
	Tree &	operator = ( tree_type const & tree ) {
		if (this != &tree) {
			clear();
			nil_destroy();
			compare = tree.compare;
			allocator = tree.allocator;
			nil_create();
			insert(tree.begin(), tree.end());
		}
		return *this;
	}

	/* Destructor */
	~Tree( void ) { clear(); nil_destroy(); }

	/* Iterators */
	iterator			begin( void ) { return _root ? iterator(leftmost_node(_root)) : end(); }
	const_iterator		begin( void ) const { return _root ? const_iterator(leftmost_node(_root)) : end(); }
	iterator			end( void ) { return iterator(nil); }
	const_iterator		end( void ) const { return const_iterator(nil); }
	reverse_iterator		rbegin( void ) { return reverse_iterator(--end()); }
	const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator(--end()); }
	reverse_iterator		rend( void ) { return reverse_iterator(end()); }
	const_reverse_iterator	rend( void ) const { return const_reverse_iterator(end()); }

	/* Getters */
	const_iterator	root( void ) const { return const_iterator(_root); }
	size_type		size( void ) const { return _size; }
	size_type		max_size( void ) const { return allocator.max_size(); }
	node_allocator_type	get_allocator( void ) const { return allocator; }

	/* Modifier */
	template<class InputIterator>
	void	insert( InputIterator first, InputIterator last ) {
		while (first != last) {
			insert(*first);
			first++;
		}
	} // range

	pair<iterator, bool>	insert( const_reference data ) {
		node_pointer	node = NULL;

		try {
			node = node_create(data);
		} catch (std::bad_alloc &e) {
			return ft::make_pair(lower_bound(data), false);
		}

		insert(node);

		return ft::make_pair(iterator(node), true);
	} // single element

	iterator	insert( iterator hint, const_reference data ) {
		(void)hint;
		pair<iterator, bool>	p = insert(data);
		return p.first;
	} // with hint

	size_type	erase( const_reference data ) {
		iterator	it = find(data);
		if (it != end()) {
			erase(it.base());
			return 1;
		}
		return 0;
	} // data

	void	erase( iterator position ) { erase(position.base()); } // iterator

	void	erase( iterator first, iterator last ) {
		while (first != last) {
			erase(first++);
		}
	} // range

	bool		empty( void ) const { return !_size; }

	void		clear( void ) {
		destroy(_root);
		_root = NULL;
		if (nil) {
			nil->parent = NULL;
		}
		_size = 0;
	}

	void	swap( Tree & t ) {
		if (this == &t) {
			return ;
		}

		node_allocator_type	tmp_allocator = allocator;
		value_compare		tmp_compare = compare;
		node_type *			tmp_root = _root;
		node_type *			tmp_nil = nil;
		size_type			tmp_size = _size;

		allocator = t.allocator;
		compare = t.compare;
		_root = t._root;
		nil = t.nil;
		_size = t._size;

		t.allocator = tmp_allocator;
		t.compare = tmp_compare;
		t._root = tmp_root;
		t.nil = tmp_nil;
		t._size = tmp_size;
	}

	/* Lookup */
	iterator		find( const_reference data ) { return iterator(find(_root, data)); }
	const_iterator	find( const_reference data ) const { return const_iterator(find(_root, data)); }
	size_type	height( void ) const { return height(_root); }

	size_type	count( const_reference data ) const {
		size_type	count = 0;

		for (node_pointer tmp = _root; tmp && tmp != nil; ) {
			if (!compare(data, tmp->data)) {
				if (!compare(tmp->data, data)) {
					count++;
				}
				tmp = tmp->right;
			} else {
				tmp = tmp->left;
			}
		}
		return count;
	}

	pair<iterator, iterator>	equal_range( const_reference key ) { return ft::make_pair(lower_bound(key), upper_bound(key)); }
	pair<const_iterator, const_iterator>	equal_range( const_reference key ) const { return ft::make_pair(lower_bound(key), upper_bound(key)); }

	iterator	lower_bound( const_reference key ) {
		node_pointer	tmp = _root;
		node_pointer	closest = NULL;

		while (tmp && tmp != nil) {
			if (!compare(tmp->data, key)) {
				closest = tmp;
				tmp = tmp->left;
			} else {
				tmp = tmp->right;
			}
		}
		if (!closest) {
			return end();
		}
		return iterator(closest);
	}

	const_iterator	lower_bound( const_reference key ) const {
		return const_iterator(lower_bound(key));
	}

	iterator	upper_bound( const_reference key ) {
		node_pointer	tmp = _root;
		node_pointer	closest = NULL;

		while (tmp && tmp != nil) {
			if (compare(key, tmp->data)) {
				closest = tmp;
				tmp = tmp->left;
			} else {
				tmp = tmp->right;
			}
		}
		if (!closest) {
			return end();
		}
		return iterator(closest);
	}

	const_iterator	upper_bound( const_reference key ) const { return const_iterator(upper_bound(key)); }

	/* Traversal */
	void	in_order( void (*function)(iterator) ) { in_order(_root, function); }
	void	pre_order( void (*function)(iterator) ) { pre_order(_root, function); }
	void	post_order( void (*function)(iterator) ) { post_order(_root, function); }
	void	breadth_order( void (*function)(iterator) ) {
		const size_t	h = height();

		for (size_t i = 1; i <= h; i++) {
			breadth_order(_root, i, function);
		}
	}

	/* Print */
	std::string		to_str( void ) const { return to_str("", _root, false); }

private:
	/* Nodes */
	node_pointer	node_create( const_reference data ) {
		node_pointer	node = allocator.allocate(1);

		allocator.construct(node, data);
		node->right = nil;
		node->left = nil;
		return node;
	}

	void	node_destroy( node_pointer node ) {
		if (!node) {
			return;
		}
		node->right = NULL;
		node->left = NULL;
		node->parent = NULL;
		allocator.destroy(node);
		allocator.deallocate(node, 1);
	}

	void	nil_create( void ) {
		nil = allocator.allocate(1);
		allocator.construct(nil, value_type());
		nil->color = BLACK;
		nil->left = NULL;
		nil->right = NULL;
		nil->parent = NULL;
	}

	void	nil_destroy( void ) { node_destroy(nil); nil = NULL; }

	void	destroy( node_pointer node ) {
		if (node && node != nil) {
			destroy(node->left);
			destroy(node->right);
			node_destroy(node);
		}
	}

	/* Modifier */
	void	insert( node_pointer node ) {
		for (node_pointer tmp = _root; tmp && tmp != nil; ) {
			node->parent = tmp;
			tmp = !compare(node->data, tmp->data) ? tmp->right : tmp->left;
		}

		if (!node->parent) {
			_root = node;
		} else if (!compare(node->data, node->parent->data)) {
			node->parent->right = node;
		} else {
			node->parent->left = node;
		}
		insert_fixup(node);
		_size++;
		nil->parent = rightmost_node(_root);
	}

	void	insert_fixup( node_pointer node ) {
		while (node != _root) {
			if (is_black(node->parent)) {
				break ;
			}

			node_pointer	parent = node->parent;
			node_pointer	grandpa = parent->parent;
			node_pointer	uncle = nil;

			if (is_left_child(parent)) {
				uncle = grandpa->right;
				if (is_black(uncle)) {
					if (is_right_child(node)) {
						rotate_left(parent);
						parent = node;
					}
					rotate_right(grandpa);
					parent->color = BLACK;
					grandpa->color = RED;
				} else {
					// RED uncle so swap uncle & parent's and grandparent's colors
					node = grandpa;
					uncle->color = BLACK;
					parent->color = BLACK;
					grandpa->color = RED;
				}
			} else {
				uncle = grandpa->left;
				if (is_black(uncle)) {
					if (is_left_child(node)) {
						rotate_right(parent);
						parent = node;
					}
					rotate_left(grandpa);
					parent->color = BLACK;
					grandpa->color = RED;

				} else {
					// RED uncle so swap uncle & parent's and grandparent's colors
					node = grandpa;
					uncle->color = BLACK;
					parent->color = BLACK;
					grandpa->color = RED;
				}
			}
		}
		_root->color = BLACK;
	}

	void	erase( node_pointer node ) {
		if (node == nil) {
			return;
		}

		if (node->left != nil && node->right != nil) {
			// 2 childs
			node_pointer	successor = leftmost_node(node->right);
			nodes_swap(node, successor);
		}

		// 0 or 1 child
		node_pointer	child = (node->left == nil) ? node->right : node->left;
		if (!node->parent) {
			_root = child;
		} else if (is_left_child(node)) {
			node->parent->left = child;
		} else {
			node->parent->right = child;
		}
		if (child != nil) {
			child->parent = node->parent;
		}
		if (is_black(node)) {
			erase_fixup(child, node->parent);
		}
		if (nil->parent == node) {
			nil->parent = rightmost_node(_root);
		}
		if (node != nil) {
			node_destroy(node);
		}
		_size--;
	}

	void	erase_fixup( node_pointer node, node_pointer parent ) {
		while (node != nil && is_black(node) && node != _root) {
			if (node == parent->left) {
				node_pointer	uncle = parent->right;

				if (is_red(uncle)) {
					// Case 1: node is left child, and right child (uncle) is red
					parent->color = RED;
					uncle->color = BLACK;
					rotate_left(parent);
				} else {
					// Case 2: node is left child, and right child (uncle) is black
					if (is_black(uncle->right)) {
						uncle->color = RED;
						uncle->left->color = BLACK;
						rotate_right(uncle);
						uncle = parent->right;
					}
					uncle->color = parent->color;
					uncle->right->color = BLACK;
					parent->color = BLACK;
					rotate_left(parent);
					node = _root;
				}
			} else {
				node_pointer	uncle = parent->left;

				// Case 3: node is right child, and left child (uncle) is red
				if (is_red(uncle)) {
					parent->color = RED;
					uncle->color = BLACK;
					rotate_right(parent);
					uncle = parent->left;
				}

				if (is_black(uncle->left) && is_black(uncle->right)) {
					// Case 4: uncle has two childs
					uncle->color = RED;
					node = parent;
					parent = node->parent;
				} else {
					// Case 5: uncle has one child or hasn't any
					if (is_black(uncle->left)) {
						uncle->right->color = BLACK;
						uncle->color = RED;
						rotate_left(uncle);
						uncle = parent->left;
					}
					uncle->color = parent->color;
					parent->color = BLACK;
					uncle->left->color = BLACK;
					rotate_right(parent);
					node = _root;
				}
			}
		}
		if (node && node != nil) {
			node->color = BLACK;
		}
	}

	void	nodes_swap( node_pointer first, node_pointer second ) {
		bool	is_left_child_first = first->parent && is_left_child(first);
		bool	is_left_child_second = second->parent && is_left_child(second);
		bool	direct_child = (second->parent == first);

		node_pointer	tmp_parent = first->parent;
		node_pointer	tmp_left = first->left;
		node_pointer	tmp_right = first->right;
		Color			tmp_color = first->color;

		// Changing first node
		first->color = second->color;
		first->left = second->left;
		first->right = second->right;
		if (first->left != nil) {
			first->left->parent = first;
		}
		if (first->right != nil) {
			first->right->parent = first;
		}
		first->parent = (direct_child) ? second : second->parent;

		if (direct_child) {
			first->parent = second;
		} else {
			first->parent = second->parent;
			if (!second->parent) {
				_root = first;
			} else if (is_left_child_second) {
				second->parent->left = first;
			} else {
				second->parent->right = first;
			}
		}

		// Changing second node
		second->color = tmp_color;
		second->parent = tmp_parent;
		if (!tmp_parent) {
			_root = second;
		} else if (is_left_child_first) {
			tmp_parent->left = second;
		} else {
			tmp_parent->right = second;
		}

		if (direct_child) {
			if (is_left_child_second) {
				second->right = tmp_right;
				second->left = first;
			} else {
				second->right = first;
				second->left = tmp_left;
			}
		} else {
			second->left = tmp_left;
			second->right = tmp_right;
		}

		if (second->left != nil) {
			second->left->parent = second;
		}
		if (second->right != nil) {
			second->right->parent = second;
		}
	}

	void	rotate_right( node_pointer node ) {
		node_pointer	left = node->left;

		node->left = left->right;
		if (left != nil) {
			left->parent = node->parent;
			if (left->right != nil) {
				left->right->parent = node;
			}
			left->right = node;
		}

		if (!node->parent) {
			_root = left;
		} else if (node == node->parent->right) {
			node->parent->right = left;
		} else {
			node->parent->left = left;
		}
		node->parent = left;
	}

	void	rotate_left( node_pointer node ) {
		node_pointer	right = node->right;

		node->right = right->left;
		if (right != nil) {
			right->parent = node->parent;
			if (right->left != nil) {
				right->left->parent = node;
			}
			right->left = node;
		}

		if (!node->parent) {
			_root = right;
		} else if (node == node->parent->left) {
			node->parent->left = right;
		} else {
			node->parent->right = right;
		}
		node->parent = right;
	}

	/* Helpers */
	size_type		height( node_pointer node ) const {
		if (node == nil) {
			return 0;
		}
		size_t	left_height = height(node->left);
		size_t	right_height = height(node->right);
		return left_height > right_height ? left_height + 1 : right_height + 1;
	}

	/* Access */
	node_pointer	find( node_pointer node, const_reference data ) const {
		if (!node || node == nil) {
			return nil;
		}

		if (!compare(data, node->data) && !compare(node->data, data)) {
			return node;
		} else if (!compare(data, node->data)) {
			return find(node->right, data);
		} else {
			return find(node->left, data);
		}
	}

	/* Traversal */
	void	breadth_order( node_pointer node, int lvl, void (*function)(iterator) ) const {
		if (node != nil) {
			if (lvl == 1) {
				function(node);
			} else if (lvl > 1) {
				breadth_order(node->left, lvl - 1, function);
				breadth_order(node->right, lvl - 1, function);
			}
		}
	}

	void	pre_order( node_pointer node, void (*function)(iterator) ) const {
		if (node != nil) {
			function(node);
			pre_order(node->left, function);
			pre_order(node->right, function);
		}
	}

	void	in_order( node_pointer node, void (*function)(iterator) ) const {
		if (node != nil) {
			in_order(node->left, function);
			function(node);
			in_order(node->right, function);
		}
	}

	void	post_order( node_pointer node, void (*function)(iterator) ) const {
		if (node != nil) {
			post_order(node->left, function);
			post_order(node->right, function);
			function(node);
		}
	}

	/* Print */
	std::string		to_str( std::string const & prefix, const_node_pointer node, bool is_left ) const {
		if (!node) {
			return "";
		}

		std::stringstream	stream;

		stream << prefix;
		stream << (is_left ? "├──" : "└──");

		stream << node->data << std::endl;

		stream << to_str(prefix + (is_left ? "│   " : "    "), node->left, true);
		stream << to_str(prefix + (is_left ? "│   " : "    "), node->right, false);

		return stream.str();
	}
};

template <typename T, typename Compare, typename Allocator>
std::ostream &	operator << ( std::ostream & o, Tree<T, Compare, Allocator> const & tree ) {
	o << tree.to_str();
	return o;
}

}
