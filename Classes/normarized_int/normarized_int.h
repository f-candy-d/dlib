/**
 * normarized_int class
 */
#ifndef DLIB_CLASSES_NORMARIZED_INT_NORMARIZED_INT_H
#define DLIB_CLASSES_NORMARIZED_INT_NORMARIZED_INT_H

#include <cstdio>
#include <cassert>
#include <utility>

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

	normarized_int(int begin, size_t length, int def_v)
	:offset_(def_v - begin),begin_(begin),length_(length)
	{
		assert(length != 0);
		assert(begin <= def_v);
		assert(def_v < begin + static_cast<int>(length));
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
	normarized_int operator+(int distance) & { auto nu = *this; return std::move(nu += distance); }
	normarized_int operator-(int distance) & { auto nu = *this; return std::move(nu += distance); }
	normarized_int& advance(int distance) { return *this += distance; }

	void reset(int begin, size_t length) { reset(begin, length, begin); }

	void reset(int begin, size_t length, int def_v)
	{
		assert(length != 0);
		assert(begin <= def_v);
		assert(def_v < begin + static_cast<int>(length));

		offset_ = def_v - begin;
		begin_ = begin;
		length_ = length;
	}

	int begin() const { return begin_; }
	int end() const { return begin_ + length_ - 1;}
	size_t length() const { return length_; }

protected:
	int offset_;
	int begin_;
	size_t length_;
};

} /* dlib */

#endif
