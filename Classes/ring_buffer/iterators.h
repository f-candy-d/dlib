/**********************************************************************************
 *
 * iterator classes for ring_buffer class.
 *
 **********************************************************************************/
#ifndef DLIB_CLASSES_RING_BUFFER_ITERATORS_H
#define DLIB_CLASSES_RING_BUFFER_ITERATORS_H

#include <iterator>
#include <cassert>

namespace dlib
{
// forward declaration
template <typename T> class ring_buffer;

namespace ring_buffer_bits
{

template <typename T> struct const_iterator : public std::iterator<
	std::forward_iterator_tag, T, std::ptrdiff_t, const T*, const T&>
{
	const_iterator(const ring_buffer<T>* p) :parent(p),index(0) { assert(p); }
	const_iterator(const ring_buffer<T>* p, size_t i) :parent(p),index(i) { assert(p); }
	const T& operator*() const { return (*parent)[index]; }
	const T* operator->() const { return &**this; }
	bool operator==(const const_iterator& other) const { return (index == other.index); }
	bool operator!=(const const_iterator& other) const { return !(*this == other); }
	const_iterator& operator++() { ++index; return *this; }
	const_iterator& operator++(int) { auto old = *this; ++*this; return std::move(old); }

private:
	const ring_buffer<T>* parent;
	// 'index' is the value that is not normarized
	size_t index;
};

template <typename T> struct iterator : public const_iterator<T>
{
	iterator(const ring_buffer<T>* p) :const_iterator<T>(p) {}
	iterator(const ring_buffer<T>* p, size_t i) :const_iterator<T>(p, i) {}
	T& operator*() { return const_cast<T&>(const_iterator<T>::operator*()); }
	T* operator->() { return &**this; }
	iterator& operator++() { const_iterator<T>::operator++(); return *this; }
	iterator& operator++(int) { auto old = *this; ++*this; return std::move(old); }
};

} /* namespace ring_buffer_bits */
} /* namespace dlib */

#endif
