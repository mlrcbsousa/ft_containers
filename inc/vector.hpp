#pragma once

#include <memory>
#include <algorithm>

#include "convert.hpp"
#include "iterators/RandomAccessIterator.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"

namespace ft {

// ************************************************************************** //
//                               vector template                           	  //
// ************************************************************************** //

template< typename T, typename Allocator = std::allocator<T> >
class vector {

public:
	/* Member types */
	typedef T													value_type;
	typedef Allocator											allocator_type;
	typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;
	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;
	typedef RandomAccessIterator<value_type>					iterator;
	typedef RandomAccessIterator<const value_type>				const_iterator;
	typedef ft::reverse_iterator<iterator>						reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t												size_type;

protected:
	pointer	c;

private:
	/* Member variables */
	size_type		_size;
	size_type		_capacity;
	allocator_type	_allocator;

public:
	/* Constructors */
	explicit vector ( const allocator_type & alloc = allocator_type() )
		: c(NULL), _size(0), _capacity(0), _allocator(alloc) { /* no-op */ } // default

	explicit vector ( size_type n,
					  const value_type & val = value_type(),
					  const allocator_type & alloc = allocator_type() )
		: c(NULL), _size(n), _capacity(n), _allocator(alloc) {
			if (n == 0) {
				return ;
			}
			if (n > max_size()){
#if defined(DARWIN)
				throw std::length_error("vector");
#else
				throw std::length_error("cannot create std::vector larger than max_size()");
#endif
			}

			c = _allocate(n);
			for (size_type i = 0; i < n; i++) {
				_construct(c + i, val);
			}
		} // fill

	template <typename InputIterator>
	vector ( typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			 InputIterator last,
			 const allocator_type & alloc = allocator_type() )
		: c(NULL), _size(0), _capacity(0), _allocator(alloc) {
		/*
		** Attention: the operations available on these iterators are restricted to InputIterators
		** https://cplusplus.com/reference/iterator/InputIterator/
		*/
		for (InputIterator it = first; it != last; it++) {
			_size++;
		}

		size_type	capacity = _next_capacity(_capacity, _size);

		c = _allocate(capacity);
		_capacity = capacity;

		size_type	i = 0;
		for (InputIterator it = first; it != last; it++) {
			_construct(c + i, *it);
			i++;
		}
	} // range

	vector ( const vector & v ) : c(NULL), _size(0), _capacity(0), _allocator(v._allocator) { *this = v; } // copy

	/* Assignment operator */
	vector &	operator = ( const vector & v ) {
		if (this != &v) {
			if (c) {
				clear();
				_deallocate();
			}
			_allocator = v._allocator;
			c = _allocate(v._capacity);
			_capacity = v._capacity;
			_copy(v);
			_size = v._size;
		}
		return *this;
	}

	/* Destructor */
	~vector( void ) { if (!c) return ; clear(); _deallocate(); }

	/* Iterators */
	iterator			begin( void ) { return iterator(c); }
	const_iterator		begin( void ) const { return const_iterator(c); }
	iterator			end( void ) { return iterator(c + _size); }
	const_iterator		end( void ) const { return const_iterator(c + _size); }
	reverse_iterator		rbegin( void ) { return reverse_iterator(end()); }
	const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator(end()); }
	reverse_iterator		rend( void ) { return reverse_iterator(begin()); }
	const_reverse_iterator	rend( void ) const { return const_reverse_iterator(begin()); }

	/* Capacity */
	size_type	size( void ) const { return _size; }
	size_type	max_size( void ) const { return _allocator.max_size(); }

	void	resize( size_type n, value_type val = value_type() ) {
		if (n == _size) {
			return ;
		}

		if (n > _size) {
			if (_size * 2 < n) {
				reserve(n);
			}
			for (size_type i = n - _size; i > 0; i--) {
				push_back(val);
			}
		} else {
			erase(begin() + n, end());
		}
	}

	size_type	capacity( void ) const { return _capacity; }
	bool		empty( void ) const { return !_size; }

	void	reserve( size_type n ) {
		if (n > max_size()){
#if defined(DARWIN)
			throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
#else
			throw std::length_error("vector::reserve");
#endif
		}
		if (n > _capacity) {
			pointer		tmp = _allocate(n);
			for (size_type i = 0; i < _size; i++) {
				_construct(tmp + i, c[i]);
			}
			size_type	tmp_size = _size;
			clear();
			_deallocate();
			c = tmp;
			_size = tmp_size;
			_capacity = n;
		}
	}

	/* Element access */
	reference			operator [] ( size_type n ) { return c[n]; }
	const_reference		operator [] ( size_type n ) const { return c[n]; }
	reference			at( size_type n ) { if (n >= _size) throw std::out_of_range(range_error(n)); return c[n]; }
	const_reference		at( size_type n ) const { return at(n); }
	reference			front( void ) { return c[0]; }
	const_reference		front( void ) const { return c[0]; }
	reference			back( void ) { return c[_size - 1]; }
	const_reference		back( void ) const { return c[_size - 1]; }
	value_type *		data( void ) { return c; }
	const value_type *	data( void ) const { return c; }

	/* Modifiers */
	template <typename InputIterator>
	void	assign( typename ft::enable_if<!ft::is_integral<InputIterator>::value,
					InputIterator>::type first,
					InputIterator last ) {
		size_type	n = 0;
		for (InputIterator it = first; it != last; it++) {
			n++;
		}

		if (n >= _capacity) {
			vector tmp(first, last, _allocator);
			swap(tmp);
		} else {
			clear();
			insert(begin(), first, last);
		}
	} // range

	void	assign( size_type n, const value_type & val ) {
		if (n >= _capacity) {
			vector tmp(n, val, _allocator);
			swap(tmp);
		} else {
			clear();
			insert(begin(), n, val);
		}
	} // fill

	void	push_back( const value_type & val ) {
		if (_capacity < _size + 1) {
			reserve(_next_capacity(_size, _size + 1));
		}
		_construct(c + _size, val);
		_size++;
	};

	void	pop_back( void ) { if (_size > 0) erase(end() - 1); }

	// single element
	iterator	insert( iterator position, const value_type & val ) {
		size_type	j = position - begin();

		insert(position, size_type(1), val);
		return iterator(c + j);
	}

	// fill
    void	insert( iterator position, size_type n, const value_type & val ) {
		if (n == 0) {
			return;
		}
		size_type	j = position - begin();

		if (_capacity < _size + n) {
			reserve(std::max(2 * _size, _size + n));
		}
		// Move previous values
		if (_size) {
			for (size_type i = _size - 1; i >= j; i--) {
				_construct(c + i + n, c[i]);
				_destroy(c + i);
				if (i == 0) { // unsigned can't go below 0
					break;
				}
			}
		}
		// Insert new values
		while (n--) {
			_construct(c + j + n, val);
			_size++;
		}
	}

	// range
	template <typename InputIterator>
	void	insert( iterator position,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
					InputIterator last ) {
		/*
		** Attention: the operations available on these iterators are restricted to InputIterators
		** https://cplusplus.com/reference/iterator/InputIterator/
		*/
		size_type	j = position - begin(); // has to be before because can grow, invalidating iterators

		size_type	n = 0;
		for (InputIterator it = first; it != last; it++) {
			n++;
		}
		if (n == 0) {
			return;
		}

		if (_capacity < _size + n) {
			reserve(std::max(2 * _size, _size + n));
		}

		// Move previous values
		if (_size) {
			for (size_type i = _size - 1; i >= j; i--) {
				_construct(c + i + n, c[i]);
				_destroy(c + i);
				if (i == 0) { // unsigned can't go below 0
					break;
				}
			}
		}
		// Insert new values
		for (InputIterator it = first; it != last; it++) {
			_construct(c + j, *it);
			j++;
		}
		_size += n;
	}

	iterator	erase( iterator position ) { return erase(position, position + 1); } // single element

	iterator	erase( iterator first, iterator last ) {
		size_type	j = last - begin();

		for (size_type i = first - begin(); i != j; i++) {
			_destroy(c + i);
		}

		size_type	n = last - first;

		_size = _size - n;
		for (size_type i = first - begin(); i != _size; i++) {
			_construct(c + i, c[i + n]);
			_destroy(c + i + n);
		}

		return first;
	} // range

	void	swap( vector & v ) {
		if (this == &v) {
			return ;
		}

		pointer			tmp_c = c;
		size_type		tmp_size = _size;
		size_type		tmp_capacity = _capacity;
		allocator_type	tmp_allocator = _allocator;

		c = v.c;
		_size = v._size;
		_capacity = v._capacity;
		_allocator = v._allocator;

		v.c = tmp_c;
		v._size = tmp_size;
		v._capacity = tmp_capacity;
		v._allocator = tmp_allocator;
	};

	void	clear( void ) { erase(begin(), end()); }

	/* Allocator */
	allocator_type	get_allocator( void ) const { return _allocator; }

private:

	void	_copy( vector const & v ) {
		if (v._size > _capacity || !c) {
			return ;
		}
		for (size_type i = 0; i < v._size; i++) {
			_construct(c + i, v[i]);
		}
	}

	size_type	_next_capacity( size_type start, size_type end ) {
		size_type	capacity = start ? start : 1;

		while (capacity < end) {
			capacity *= 2;
		}
		return capacity;
	}

	std::string	range_error( size_type n ) {
#if defined(DARWIN)
		std::string		error("vector");

		(void)n;
#else
		std::string		error("vector::_M_range_check: __n (which is ");

		error += to_s(n) + std::string(") >= this->size() (which is ");
		error += to_s(_size) + std::string(")");
#endif

		return error;
	}

	/* Allocator wrappers */
	pointer			_allocate( size_type capacity ) { return _allocator.allocate(capacity); }
	void			_deallocate( void ) { if (c) _allocator.deallocate(c, _capacity); }
	void			_destroy( pointer p ) { if (p) _allocator.destroy(p); }
	void			_construct( pointer p, value_type val ) { if (p) _allocator.construct(p, val); }

};

/* Non-member functions */

// relational operators
template <typename T, typename Alloc>
inline bool	operator == ( const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs ) {
	if (lhs.size() == rhs.size()) {
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	return false;
}

template <typename T, typename Alloc>
bool	operator != ( const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs ) { return !(lhs == rhs); }

template <typename T, typename Alloc>
bool	operator < ( const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs ) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, typename Alloc>
bool	operator <= ( const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs ) { return !(rhs < lhs); }

template <typename T, typename Alloc>
bool	operator > ( const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs ) { return rhs < lhs; }

template <typename T, typename Alloc>
bool	operator >= ( const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs ) { return !(lhs < rhs); }

// swap
template <typename T, typename Alloc>
void	swap( vector<T, Alloc> & lhs, vector<T, Alloc> & rhs ) { lhs.swap(rhs); }

}

