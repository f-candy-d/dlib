/**
 * normarized_uint class
 */
#ifndef DLIB_CLASSES_NORMARIZED_UINT_NORMARIZED_UINT_H
#define DLIB_CLASSES_NORMARIZED_UINT_NORMARIZED_UINT_H

#include <cstdio>
#include <cassert>

namespace dlib
{

class normarized_uint
{
	using uint = unsigned int;

public:
	normarized_uint()
	:normarized_uint(0, 0, 0)
	{}

	normarized_uint(uint begin, size_t length)
	:normarized_uint(begin, length, begin)
	{}

	normarized_uint(uint begin, size_t length, uint position)
	:offset_(position - begin),begin_(begin),length_(length)
	{
		assert(length != 0);
		assert(begin <= position);
		assert(position < begin + length);
	}

	uint operator*() const { return begin_ + offset_; }
	normarized_uint& operator+=(size_t distance) { offset_ = (offset_ + distance) % length_; return *this; }
	normarized_uint& operator++() { return *this += 1; }
	normarized_uint operator++(int) { auto nu = *this; ++*this; return nu; }
	normarized_uint operator+(size_t distance) & { auto nu = *this; nu += distance; return nu; }
	normarized_uint& forward(size_t distance) { return *this += distance; }

	void reset(uint begin, size_t length) { reset(begin, length, begin); }

	void reset(uint begin, size_t length, uint position)
	{
		assert(length != 0);
		assert(begin <= position);
		assert(position < begin + length);

		offset_ = position - begin;
		begin_ = begin;
		length_ = length;
	}

	uint begin() const { return begin_; }
	uint end() const { return begin_ + length_ - 1;}
	size_t length() const { return length_; }

private:
	uint offset_;
	uint begin_;
	size_t length_;
};

} /* dlib */

#endif
