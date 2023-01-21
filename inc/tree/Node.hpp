#pragma once

// Enumeration for the color of a node
enum Color { RED, BLACK };

namespace ft {

// ************************************************************************** //
//                               Node template	                              //
// ************************************************************************** //

// Struct for a node in the tree
template <typename T>
struct Node {
	typedef	T					value_type;
	typedef	value_type &		value_reference;
	typedef	Node<value_type>	node_type;
	typedef	node_type *			node_pointer;

	value_type		data;
	Color 			color;
	node_pointer	left, right, parent;

	Node( value_type data )
		: data(data)
		, color(RED)
		, left(NULL)
		, right(NULL)
		, parent(NULL) { /* no-op */ };
};

template <typename T>
bool	is_leaf_node( Node<T> * node ) { return node && node->left == NULL; }

template <typename T>
bool	is_left_child( Node<T> * node ) { return node->parent->left == node; }

template <typename T>
bool	is_right_child( Node<T> * node ) { return !is_left_child(node); }

template <typename T>
bool	is_black( Node<T> * node ) { return !node || node->color == BLACK; }

template <typename T>
bool	is_red( Node<T> * node ) { return !is_black(node); }

template <typename T>
Node<T> *	leftmost_node( Node<T> * node ) {
	if (!node) {
		return NULL;
	}

	while (!is_leaf_node(node->left)) {
		node = node->left;
	}
	return node;
}

template <typename T>
Node<T> *	rightmost_node( Node<T> * node ) {
	if (!node) {
		return NULL;
	}

	while (!is_leaf_node(node->right)) {
		node = node->right;
	}
	return node;
}

template <typename T>
Node<T> *	upmost_node( Node<T> * node ) {
	while (node && node->parent) {
		node = node->parent;
	}
	return node;
}

template <typename T>
Node<T> *	upmost_right_node( Node<T> * node ) {
	if (!node) {
		return NULL;
	}

	while (node->parent && node->parent->right == node) {
		node = node->parent;
	}
	node = node->parent;
	return node;
}

template <typename T>
Node<T> *	upmost_left_node( Node<T> * node ) {
	if (!node) {
		return NULL;
	}

	while (node->parent && node->parent->left == node) {
		node = node->parent;
	}
	node = node->parent;
	return node;
}

template <typename T>
Node<T> *	increment( Node<T> * node ) {
	if (!node) {
		return NULL;
	}

	if (is_leaf_node(node)) {
		if (node->parent) {
			node = leftmost_node(upmost_node(node));
		}
	} else if (!is_leaf_node(node->right)) {
		node = leftmost_node(node->right);
	} else if (node->right->parent == node) {
		node = node->right;
	} else {
		node = upmost_right_node(node);
	}
	return node;
}

template <typename T>
Node<T> *	decrement( Node<T> * node ) {
	if (!node) {
		return NULL;
	}

	if (is_leaf_node(node)) {
		if (node->parent) {
			node = node->parent;
		}
	} else if (!is_leaf_node(node->left)) {
		node = rightmost_node(node->left);
	} else if (node == leftmost_node(upmost_node(node))) {
		node = node->left;
	} else {
		node = upmost_left_node(node);
	}
	return node;
}

}
