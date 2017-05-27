/**********************************************************************************
 *
 * ring_buffer class implementation.
 *
 **********************************************************************************/
#ifndef DLIB_CLASSES_RING_BUFFER_IMPL_H
#define DLIB_CLASSES_RING_BUFFER_IMPL_H

#include <cassert>
#include <utility>
#include "ring_buffer.h"

namespace dlib
{

// constant values
namespace
{
	static const size_t kCapacityBase = 2;
}

template <typename T>
ring_buffer<T>::ring_buffer()
:front_(0)
,back_(0)
,size_(0)
,capacity_(0)
,data_(nullptr)
{}

template <typename T>
ring_buffer<T>::ring_buffer(size_type size, T def_value)
:ring_buffer()
{
	change_capacity(size, def_value);
}

template <typename T>
ring_buffer<T>::ring_buffer(size_type size, size_type cap_request, T def_value)
:ring_buffer()
{
	assert(size <= cap_request);
	change_capacity(cap_request, def_value);
}

template <typename T>
ring_buffer<T>::ring_buffer(const ring_buffer& other)
{
	if(other.data_ != nullptr)
	{
		data_ = new T[other.capacity()];
		for(index_type i = 0; i < other.capacity(); ++i)
		{
			data_[i] = other.data_[i];
		}
	}

	front_ = other.front_;
	back_ = other.back_;
	size_ = other.size_;
	capacity_ = other.capacity_;
}

template <typename T>
ring_buffer<T>& ring_buffer<T>::operator=(const ring_buffer<T> &other)
{
	if(other.data_ != nullptr)
	{
		data_ = new T[other.capacity()];
		for(index_type i = 0; i < other.capacity(); ++i)
		{
			data_[i] = other.data_[i];
		}
	}

	front_ = other.front_;
	back_ = other.back_;
	size_ = other.size_;
	capacity_ = other.capacity_;

	return *this;
}

template <typename T>
void ring_buffer<T>::change_capacity(size_type cap_request, T def_value)
{
	if(capacity_ < cap_request)
	{
		expand_capacity(cap_request, def_value);
	}
	else if(cap_request < capacity_)
	{
		shrink_capacity(cap_request, def_value);
	}
}

template <typename T>
void ring_buffer<T>::expand_capacity(size_type cap_request, T def_value)
{
	auto capacity = confirm_capacity(cap_request);
	if(capacity_ < capacity)
	{
		T* data = new T[capacity];
		for(index_type i = 0; i < capacity; ++i)
		{
			data[i] = (i < size_) ? (*this)[i] : def_value;
		}

		capacity_ = capacity;
		front_ = 0;
		back_ = (size_ == 0) ? 0 : size_ - 1;

		if(data_ != nullptr)
		{
			delete [] data_;
		}
		data_ = data;
	}
}

template <typename T>
void ring_buffer<T>::shrink_capacity(size_type cap_request, T def_value)
{
	auto capacity = confirm_capacity(cap_request);

	if(capacity == 0)
	{
		free_memory();
	}
	else if(capacity < capacity_)
	{
		T* data = new T[capacity];
		for(index_type i = 0; i < capacity; ++i)
		{
			data[i] = (*this)[i];
		}

		capacity_ = capacity;
		size_ = capacity;
		front_ = 0;
		back_ = capacity - 1;

		if(data_ != nullptr)
		{
			delete [] data_;
		}
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
		front_ = (front_ == back_) ? normalize_index(front_ + 1) : front_;
		size_ = (size_ < capacity_) ? size_ + 1 : size_;
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
		front_ = (front_ < 1) ? capacity_ - 1 : front_ - 1;
		data_[front_] = std::move(value);
		back_ = (front_ == back_) ? ((back_ < 1) ? capacity_ - 1 : back_ - 1) : back_;
		size_ = (size_ < capacity_) ? size_ + 1 : size_;
	}
}

template <typename T>
T ring_buffer<T>::pop_back()
{
	if(0 < size_)
	{
		auto data = data_[back_];
		data_[back_] = 0;
		back_ = (back_ < 1) ? capacity_ - 1 : back_ - 1;
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
		data_[front_] = 0;
		front_ = normalize_index(front_ + 1);
		--size_;
		return data;
	}

	return T();
}

template <typename T>
T& ring_buffer<T>::operator[](index_type index)
{
	assert(data_ != nullptr);
	// NOTE -> (*this)[0] is always returns a reference to the front element in ring_buffer.
	return *(data_ + normalize_index(front_ + index));
}

template <typename T>
const T& ring_buffer<T>::operator[](index_type index)
const
{
	assert(data_ != nullptr);
	// NOTE -> (*this)[0] is always returns a reference to the front element in ring_buffer.
	return *(data_ + normalize_index(front_ + index));
}

template <typename T>
void ring_buffer<T>::clear()
{
	// clear() does not free memory
	size_ = 0;
	front_ = 0;
	back_ = 0;
}

template <typename T>
void ring_buffer<T>::free_memory()
{
	// deallocate memory and reset parameters
	if(data_ != nullptr)
	{
		delete [] data_;
		data_ = nullptr;
	}

	capacity_ = 0;
	clear();
}

template <typename T>
typename ring_buffer<T>::index_type ring_buffer<T>::normalize_index(index_type index)
const
{
	if(capacity_ == 0)
	{
		return 0;
	}
	else
	{
		// NOTE -> capacity_ must always be 2^n !!
		return index & (capacity_ - 1);
	}
}

template <typename T>
typename ring_buffer<T>::size_type ring_buffer<T>::confirm_capacity(size_type cap_request)
{
	size_type capacity = 0;
	// NOTE -> capacity_ must always be 2^n !!
	for(; capacity < cap_request; capacity = (capacity == 0) ? 1 : capacity * kCapacityBase);

	return capacity;
}

} /* namespace dlib */

#endif
