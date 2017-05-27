/**********************************************************************************
 *
 * ring_buffer class declaration.
 *
 **********************************************************************************/
#ifndef DLIB_CLASSES_RING_BUFFER_RING_BUFFER_H
#define DLIB_CLASSES_RING_BUFFER_RING_BUFFER_H

#include <cstdlib>
#include "iterators.h"

namespace dlib
{

template <typename T> class ring_buffer
{
	using index_type = size_t;
	using size_type = size_t;
	using iterator = ring_buffer_bits::iterator<T>;
	using const_iterator = ring_buffer_bits::const_iterator<T>;

public:
	ring_buffer();
	ring_buffer(size_type size, T def_value = T());
	ring_buffer(size_type size, size_type cap_request, T def_value);
	ring_buffer(const ring_buffer& other);
	ring_buffer& operator=(const ring_buffer& other);
	void change_capacity(size_type cap_request, T def_value = T());
	void expand_capacity(size_type cap_request, T def_value = T());
	void shrink_capacity(size_type cap_request, T def_value = T());
	void push_back(T value);
	void push_front(T value);
	T pop_back();
	T pop_front();
	T& operator[](index_type index);
	const T& operator[](index_type index) const;
	T front() const { return (size_ != 0) ? data_[front_] : T(); }
	T back() const { return (size_ != 0) ? data_[back_] : T(); }
	void clear();
	void free_memory();
	size_type capacity() const;

	size_type size() const { return size_; }
	const T* data() const { return data_; }

	// iterators
	iterator begin() { return std::move(iterator(this, 0)); }
	const_iterator begin() const { return std::move(const_iterator(this, 0)); }
	const_iterator cbegin() const { return std::move(begin()); }
	iterator end() { return std::move(iterator(this, size_)); }
	const_iterator end() const { return std::move(const_iterator(this, size_)); }
	const_iterator cend() const { return std::move(end()); }
	iterator begin_strage() { return std::move(iterator(this, gross_capacity_ - front_)); }
	const_iterator begin_strage() const { return std::move(const_iterator(this, gross_capacity_ - front_)); }
	const_iterator cbegin_strage() const { return std::move(begin()); }
	iterator end_strage() { return std::move(iterator(this, 2 * gross_capacity_ - front_)); }
	const_iterator end_strage() const { return std::move(const_iterator(this, 2 * gross_capacity_ - front_)); }
	const_iterator cend_strage() const { return std::move(end()); }

// private:
	index_type front_;
	index_type back_;
	size_type size_;
	// net-capacity + the number of dummy memory
	size_type gross_capacity_;
	T* data_;
	std::allocator<T> allocator_;

	index_type normalize_index(index_type index) const;
	size_type confirm_capacity(size_type cap_request);
};

} /* namespace dlib */

// include the implementation file here...
#include "impl.h"

#endif
