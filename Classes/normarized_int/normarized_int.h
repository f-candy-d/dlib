/**
 * normarized_int class
 */
#ifndef DLIB_CLASSES_NORMARIZED_UINT_NORMARIZED_UINT_H
#define DLIB_CLASSES_NORMARIZED_UINT_NORMARIZED_UINT_H

#include <cstdio>
#include <cassert>

namespace dlib
{

class normarized_int
{
public:
	normarized_int()
	:normarized_int(0, 1, 0)
	{}

	normarized_int(int begin, size_t length)
	:normarized_int(begin, length, begin)
	{}

	normarized_int(int begin, size_t length, int position)
	:offset_(position - begin),begin_(begin),length_(length)
	{
		assert(length != 0);
		assert(begin <= position);
		assert(position < begin + static_cast<int>(length));
	}

	int operator*() const { return begin_ + offset_; }

	normarized_int& operator+=(int distance)
	{
		auto off_p_dis = offset_ + distance;
		if(off_p_dis < 0)
		{
			// backward
			offset_ = length_ - ((-off_p_dis) % length_);
		}
		else
		{
			// forward
			offset_ = off_p_dis % length_;
		}

		return *this;
	}

	normarized_int& operator-=(int distance) { return *this += -distance; }
	normarized_int& operator++() { return *this += 1; }
	normarized_int operator++(int) { auto nu = *this; ++*this; return nu; }
	normarized_int& operator--() { return *this -= 1; }
	normarized_int operator--(int) { auto nu = *this; --*this; return nu; }
	normarized_int operator+(int distance) & { auto nu = *this; nu += distance; return nu; }
	normarized_int operator-(int distance) & { auto nu = *this; nu -= distance; return nu; }
	normarized_int& advance(int distance) { return *this += distance; }

	void reset(int begin, size_t length) { reset(begin, length, begin); }

	void reset(int begin, size_t length, int position)
	{
		assert(length != 0);
		assert(begin <= position);
		assert(position < begin + static_cast<int>(length));

		offset_ = position - begin;
		begin_ = begin;
		length_ = length;
	}

	int begin() const { return begin_; }
	int end() const { return begin_ + length_ - 1;}
	size_t length() const { return length_; }

private:
	int offset_;
	int begin_;
	size_t length_;
};

} /* dlib */

#endif
