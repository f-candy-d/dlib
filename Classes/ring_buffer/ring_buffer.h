/**********************************************************************************
 *
 * ring_buffer class declaration.
 *
 **********************************************************************************/
#ifndef DLIB_CLASSES_RING_BUFFER_RING_BUFFER_H
#define DLIB_CLASSES_RING_BUFFER_RING_BUFFER_H

#include <cstdlib>

namespace dlib
{

template <typename T> class ring_buffer
{
	using index_type = size_t;
	using size_type = size_t;

public:
	ring_buffer();
	ring_buffer(size_type size, T def_value = T());
	ring_buffer(size_type size, size_type cap_request, T def_value);
	void change_capacity(size_type cap_request, T def_value = T());
	void expand_capacity(size_type cap_request, T def_value = T());
	void shrink_capacity(size_type cap_request, T def_value = T());
	void push_back(T value);
	void push_front(T value);
	T pop_back();
	T pop_front();
	T& operator[](index_type index);
	const T& operator[](index_type index) const;
	T front() const { return (data_ != nullptr) ? data_[front_] : T(); }
	T back() const { return (data_ != nullptr) ? data_[back_] : T(); }

	size_type size() const { return size_; }
	size_type capacity() const { return capacity_; }
	const T* data() const { return data_; }

private:
	index_type front_;
	index_type back_;
	size_type size_;
	size_type capacity_;
	T* data_;

	index_type normalize_index(index_type index) const;
	size_type confirm_capacity(size_type cap_request);
};

} /* namespace dlib */

// include the implementation file here...
#include "impl.h"

#endif