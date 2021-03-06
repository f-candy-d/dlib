/**********************************************************************************
 *
 * ring_buffer class implementation.
 *
 **********************************************************************************/
#ifndef DLIB_CLASSES_RING_BUFFER_IMPL_H
#define DLIB_CLASSES_RING_BUFFER_IMPL_H

#include <cassert>
#include <utility>
#include <algorithm>
#include "ring_buffer.h"

namespace dlib
{

// constant values
namespace
{
	static const size_t kCapacityBase = 2;
	static const size_t kNumDummyMemory = 1;
}

template <typename T>
ring_buffer<T>::ring_buffer()
:front_(0)
,back_(0)
,size_(0)
,gross_capacity_(0)
,data_(nullptr)
,allocator_()
{}

template <typename T>
ring_buffer<T>::ring_buffer(size_t size, T def_value)
:ring_buffer()
{
	// expand_capacity(size);
	init(size, size, def_value);
}

template <typename T>
ring_buffer<T>::ring_buffer(size_t size, size_t cap_request, T def_value)
:ring_buffer()
{
	// assert(size <= cap_request);
	// expand_capacity(cap_request);
	init(size, cap_request, def_value);
}

template <typename T>
ring_buffer<T>::ring_buffer(const ring_buffer& other)
{
	if(other.data_ != nullptr)
	{
		data_ = allocator_.allocate(other.gross_capacity_);
		std::uninitialized_copy(other.begin_strage(), other.end_strage(), data_);
	}
	else
	{
		data_ = nullptr;
	}

	front_ = other.front_;
	back_ = other.back_;
	size_ = other.size_;
	gross_capacity_ = other.gross_capacity_;
}

template <typename T>
ring_buffer<T>& ring_buffer<T>::operator=(const ring_buffer<T> &other)
{
	if(other.data_ != nullptr)
	{
		data_ = allocator_.allocate(other.gross_capacity_);
		std::uninitialized_copy(other.begin_strage(), other.end_strage(), data_);
	}
	else
	{
		data_ = nullptr;
	}

	front_ = other.front_;
	back_ = other.back_;
	size_ = other.size_;
	gross_capacity_ = other.gross_capacity_;

	return *this;
}

template <typename T>
void ring_buffer<T>::change_capacity(size_t cap_request)
{
	if(capacity() < cap_request)
	{
		expand_capacity(cap_request);
	}
	else if(cap_request < capacity())
	{
		shrink_capacity(cap_request);
	}
}

template <typename T>
void ring_buffer<T>::expand_capacity(size_t cap_request)
{
	auto capacity = confirm_capacity(cap_request);
	if(gross_capacity_ < capacity)
	{
		T* data = allocator_.allocate(capacity);
		std::uninitialized_copy_n(begin(), size_, data);

		gross_capacity_ = capacity;
		front_ = 0;
		back_ = (size_ == 0) ? 0 : size_ - 1;

		free_memory();
		data_ = data;
	}
}

template <typename T>
void ring_buffer<T>::shrink_capacity(size_t cap_request)
{
	// this is gross-capacity
	auto capacity = confirm_capacity(cap_request);

	if(capacity < kNumDummyMemory)
	{
		free_memory();
		front_ = 0;
		back_ = 0;
		size_ = 0;
		gross_capacity_ = 0;
	}
	else if(capacity < gross_capacity_)
	{
		gross_capacity_ = capacity;
		size_ = (size_ < this->capacity()) ? size_ : this->capacity();
		front_ = 0;
		back_ = this->capacity() - 1;

		T* data = allocator_.allocate(capacity);
		std::uninitialized_copy_n(begin(), size_, data);
		free_memory();
		data_ = data;
	}
}

template <typename T>
void ring_buffer<T>::push_back(T value)
{
	if(data_ == nullptr)
		return;

	if(size_ == 0)
	{
		// front == back
		data_[back_] = std::move(value);
		++size_;
	}
	else
	{
		// front != back
		back_ = normalize_index(back_ + 1);
		data_[back_] = std::move(value);
		front_ = (front_ == normalize_index(back_ + kNumDummyMemory)) ? normalize_index(front_ + 1) : front_;
		size_ = (size_ < capacity()) ? size_ + 1 : size_;
	}
}

template <typename T>
void ring_buffer<T>::push_front(T value)
{
	if(data_ == nullptr)
		return;

	if(size_ == 0)
	{
		// front == back
		data_[front_] = std::move(value);
		++size_;
	}
	else
	{
		// front != back
		// NOTE -> (front_ < 1) is equal to (front_ - 1 < 0), but (front_ - 1 < 0) is not working
		//         because front_ is size_t and it is not be a negative number.
		front_ = (front_ < 1) ? gross_capacity_ - 1 : front_ - 1;
		data_[front_] = std::move(value);
		back_ = (((front_ < 1) ? gross_capacity_ - 1 : front_ - 1) == back_)
				? ((back_ < 1) ? gross_capacity_ - 1 : back_ - 1)
				: back_;
		size_ = (size_ < capacity()) ? size_ + 1 : size_;
	}
}

template <typename T>
T ring_buffer<T>::pop_back()
{
	if(0 < size_)
	{
		auto data = data_[back_];
		allocator_.destroy(&data_[back_]);
		back_ = (back_ < 1) ? gross_capacity_ - 1 : back_ - 1;
		--size_;
		return data;
	}

	return T();
}

template <typename T>
T ring_buffer<T>::pop_front()
{
	if(0 < size_)
	{
		auto data = data_[front_];
		allocator_.destroy(&data_[front_]);
		front_ = normalize_index(front_ + 1);
		--size_;
		return data;
	}

	return T();
}

template <typename T>
T& ring_buffer<T>::operator[](size_t index)
{
	assert(data_ != nullptr);
	// NOTE -> (*this)[0] is always returns a reference to the front element in ring_buffer.
	return *(data_ + normalize_index(front_ + index));
}

template <typename T>
const T& ring_buffer<T>::operator[](size_t index)
const
{
	assert(data_ != nullptr);
	// NOTE -> (*this)[0] is always returns a reference to the front element in ring_buffer.
	return *(data_ + normalize_index(front_ + index));
}

template <typename T>
void ring_buffer<T>::clear()
{
	// clear() does not free memories
	for(size_t i = 0; i < size_; ++i)
	{
		allocator_.destroy(&(*this)[i]);
	}
	size_ = 0;
	front_ = 0;
	back_ = 0;
}

template <typename T>
size_t ring_buffer<T>::capacity()
const
{
	// return a net-capacity.
	return (gross_capacity_ < kNumDummyMemory) ? 0 : gross_capacity_ - kNumDummyMemory;
}

template <typename T>
void ring_buffer<T>::free_memory()
{
	// deallocate memory and reset parameters
	if(data_ != nullptr)
	{
		for(size_t i = 0; i < size_; ++i)
		{
			allocator_.destroy(&(*this)[i]);
		}

		allocator_.deallocate(data_, gross_capacity_);
		data_ = nullptr;
	}
}

template <typename T>
size_t ring_buffer<T>::normalize_index(size_t index)
const
{
	if(gross_capacity_ == 0)
	{
		return 0;
	}
	else
	{
		// NOTE -> gross_capacity_ must always be 2^n !!
		return index & (gross_capacity_ - 1);
	}
}

template <typename T>
size_t ring_buffer<T>::confirm_capacity(size_t cap_request)
{
	if(cap_request == 0)
	{
		return 0;
	}

	size_t capacity = 0;
	cap_request += kNumDummyMemory;
	// NOTE -> gross_capacity_ must always be 2^n !!
	for(; capacity < cap_request; capacity = (capacity == 0) ? 1 : capacity * kCapacityBase);

	return capacity;
}

template <typename T>
void ring_buffer<T>::init(size_t size, size_t cap_request, T def_value)
{
	assert(size <= cap_request);

	if(data_ == nullptr)
	{
		auto capacity = confirm_capacity(cap_request);
		if(capacity != 0)
		{
			data_ = allocator_.allocate(size);
			std::uninitialized_fill(data_, data_ + size, def_value);
		}

		gross_capacity_ = capacity;
		size_ = size;
		front_ = 0;
		back_ = (size == 0) ? 0 : size - 1;
	}
}

} /* namespace dlib */

#endif
