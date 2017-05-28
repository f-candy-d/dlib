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
	using iterator = ring_buffer_bits::iterator<T>;
	using const_iterator = ring_buffer_bits::const_iterator<T>;

public:
	ring_buffer();
	ring_buffer(size_t size, T def_value = T());
	ring_buffer(size_t size, size_t cap_request, T def_value);
	ring_buffer(const ring_buffer& other);
	ring_buffer& operator=(const ring_buffer& other);
	void change_capacity(size_t cap_request);
	void expand_capacity(size_t cap_request);
	void shrink_capacity(size_t cap_request);
	void push_back(T value);
	void push_front(T value);
	T pop_back();
	T pop_front();
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	T front() const { return (size_ != 0) ? data_[front_] : T(); }
	T back() const { return (size_ != 0) ? data_[back_] : T(); }
	void clear();
	size_t capacity() const;
	size_t size() const { return size_; }

	// iterators
	// return an iterator pointing the front element
	iterator begin() { return std::move(iterator(this, 0)); }
	const_iterator begin() const { return std::move(const_iterator(this, 0)); }
	const_iterator cbegin() const { return std::move(begin()); }
	// return an iterator pointing the back element
	iterator end() { return std::move(iterator(this, size_)); }
	const_iterator end() const { return std::move(const_iterator(this, size_)); }
	const_iterator cend() const { return std::move(end()); }

private:
	size_t front_;
	size_t back_;
	size_t size_;
	// net-capacity + the number of dummy memory
	size_t gross_capacity_;
	T* data_;
	std::allocator<T> allocator_;

	void free_memory();
	size_t normalize_index(size_t index) const;
	size_t confirm_capacity(size_t cap_request);
	void init(size_t size, size_t cap_request, T def_value = T());

	// iterators (private)
	iterator begin_strage() { return std::move(iterator(this, gross_capacity_ - front_)); }
	const_iterator begin_strage() const { return std::move(const_iterator(this, gross_capacity_ - front_)); }
	const_iterator cbegin_strage() const { return std::move(begin()); }
	iterator end_strage() { return std::move(iterator(this, 2 * gross_capacity_ - front_)); }
	const_iterator end_strage() const { return std::move(const_iterator(this, 2 * gross_capacity_ - front_)); }
	const_iterator cend_strage() const { return std::move(end()); }
};

} /* namespace dlib */

// include the implementation file here...
#include "impl.h"

#endif
