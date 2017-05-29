/**
 * normarized_int_optimized_pow2 class declaration.
 * a child class of normarized_int class. this class is optimized for the case that its length is 2^n.
 * this class use a bitwise operator '&' instead of '%' when normarize a value.
 */
#ifndef DLIB_CLASSES_NORMARIZED_INT_NORMARIZED_INT_OPTIMIZED_POW2_H
#define DLIB_CLASSES_NORMARIZED_INT_NORMARIZED_INT_OPTIMIZED_POW2_H

#include "normarized_int.h"

namespace dlib
{

class normarized_int_optimized_pow2 : public normarized_int
{
public:
	normarized_int_optimized_pow2()
	:normarized_int()
	{}

	normarized_int_optimized_pow2(int begin, size_t length)
	:normarized_int(begin, length)
	{
		assert(is_power_of_2(length));
	}

	normarized_int_optimized_pow2(int begin, size_t length, int def_v)
	:normarized_int(begin, length, def_v)
	{
		assert(is_power_of_2(length));
	}

	normarized_int_optimized_pow2& operator+=(int distance)
	{
		auto off_p_dis = normarized_int::offset_ + distance;
		if(off_p_dis < 0)
		{
			// backward
			normarized_int::offset_ = normarized_int::length_ - ((-off_p_dis) & (normarized_int::length_ - 1));
		}
		else
		{
			// forward
			normarized_int::offset_ = off_p_dis & (normarized_int::length_ - 1);
		}

		return *this;
	}

	normarized_int_optimized_pow2& operator-=(int distance) { return *this += -distance; }
	normarized_int_optimized_pow2& operator++() { return *this += 1; }
	normarized_int_optimized_pow2 operator++(int) { auto nu = *this; ++*this; return nu; }
	normarized_int_optimized_pow2& operator--() { return *this -= 1; }
	normarized_int_optimized_pow2 operator--(int) { auto nu = *this; --*this; return nu; }
	normarized_int_optimized_pow2 operator+(int distance) & { auto nu = *this; return std::move(nu += distance); }
	normarized_int_optimized_pow2 operator-(int distance) & { auto nu = *this; return std::move(nu += distance); }
	normarized_int_optimized_pow2& advance(int distance) { return *this += distance; }

	normarized_int_optimized_pow2& forward(int distance) { normarized_int::offset_ = (normarized_int::offset_ + distance) & (normarized_int::length_ - 1); return *this; }
	void fforward() { normarized_int::offset_ = (normarized_int::offset_ + 1) & (normarized_int::length_ - 1); }

	void reset(int begin, size_t length) { reset(begin, length, begin); }

	void reset(int begin, size_t length, int def_v)
	{
		assert(is_power_of_2(length));
		normarized_int::reset(begin, length, def_v);
	}

private:
	bool is_power_of_2(size_t n)
	{
		if(0 < n)
		{
			return !(n & (n - 1));
		}

		return false;
	}
};

} /* dlib */

#endif
