/**********************************************************************************
 *
 * Iterators of forked_linked_list class
 *
 **********************************************************************************/
#ifndef DLIB_CLASSES_FORKED_LINKED_LIST_ITERATORS_H
#define DLIB_CLASSES_FORKED_LINKED_LIST_ITERATORS_H

#include <iterator>
#include "node.h"

namespace dlib
{
namespace forked_linked_list_bits
{

// forward declaration
// set this class as friend of iterator class
template <typename T> class node_cursor;

// the running direction of an iterator (forward vertically or horizontally)
enum class running_direction
{
	kVertical, kHorizontal
};

// vh-iterator (movable vertically & horizontally)
template <typename T> struct vh_iterator : public std::iterator<
	std::forward_iterator_tag, T, std::ptrdiff_t, T*, T&>
{
	// enable to access to 'node<T>* np'
	friend node_cursor<T>;

	vh_iterator() :np(nullptr),r_dir(running_direction::kVertical) {}
	vh_iterator(node<T>* p) :np(p),r_dir(running_direction::kVertical) {}
	vh_iterator(node<T>* p, running_direction dir) :np(p),r_dir(dir) {}
	T& operator*() const { return np->value; }
	T* operator->() const { return &**this; }
	bool operator==(const vh_iterator& other) const { return (np == other.np); }
	bool operator!=(const vh_iterator& other) const { return !(*this == other); }
	vh_iterator& forward_ver() { np = (np != nullptr) ? np->v_next : nullptr; return *this; }
	vh_iterator& forward_hor() { np = (np != nullptr) ? np->h_next : nullptr; return *this; }
	void set_running_dir(running_direction dir) { r_dir = dir; }
	node<T>* nodep() { return np; }
	const node<T>* nodep() const { return np; }

	vh_iterator& operator++()
	{
		switch(r_dir)
		{
			case running_direction::kVertical :
				return forward_ver();

			case running_direction::kHorizontal :
				return forward_hor();
		}

		return *this;
	}

	vh_iterator& operator++(int)
	{
		auto old = *this;
		++*this;
		return old;
	}

private:
	node<T>* np;
	running_direction r_dir;

	node<T>* node_p() { return np; }
	const node<T>* node_p() const { return np; }
};

// const vh-iterator
template <typename T> struct const_vh_iterator : public vh_iterator<T>
{
	const_vh_iterator() :vh_iterator<T>() {}
	const_vh_iterator(node<T>* p, running_direction dir) :vh_iterator<T>(p, dir) {}
	const T& operator*() const { return vh_iterator<T>::operator*(); }
	const T* operator->() const { return vh_iterator<T>::operator->(); }

	const_vh_iterator& operator++()
	{
		vh_iterator<T>::operator++();
		return *this;
	}

	const_vh_iterator& operator++(int)
	{
		auto old = *this;
		++*this;
		return old;
	}
};

// v-iterator (movable only vertically)
template <typename T> struct v_iterator : public vh_iterator<T>
{
	v_iterator() :vh_iterator<T>(nullptr, running_direction::kVertical) {}
	v_iterator(node<T>* p) :vh_iterator<T>(p, running_direction::kVertical) {}

	v_iterator& operator++()
	{
		vh_iterator<T>::operator++();
		return *this;
	}

	v_iterator& operator++(int)
	{
		auto old = *this;
		++*this;
		return old;
	}

private:
	// disable the following methods
	v_iterator& forward_ver() {}
	v_iterator& forward_hor() {}
	void set_running_dir(running_direction dir) {}
};

// const v-iterator
template <typename T> struct const_v_iterator : public v_iterator<T>
{
	const_v_iterator() :v_iterator<T>() {}
	const_v_iterator(node<T>* p) :v_iterator<T>(p) {}
	const T& operator*() const { return v_iterator<T>::operator*(); }
	const T* operator->() const { return v_iterator<T>::operator->(); }

	const_v_iterator& operator++()
	{
		v_iterator<T>::operator++();
		return *this;
	}

	const_v_iterator& operator++(int)
	{
		auto old = *this;
		++*this;
		return old;
	}
};

// h-iterator (movable only horizontally)
template <typename T> struct h_iterator : public vh_iterator<T>
{
	h_iterator() :vh_iterator<T>(nullptr, running_direction::kHorizontal) {}
	h_iterator(node<T>* p) :vh_iterator<T>(p, running_direction::kHorizontal) {}

	h_iterator& operator++()
	{
		vh_iterator<T>::operator++();
		return *this;
	}

	h_iterator& operator++(int)
	{
		auto old = *this;
		++*this;
		return old;
	}

private:
	// disable the following methods
	h_iterator& forward_ver() {}
	h_iterator& forward_hor() {}
	void set_running_dir(running_direction dir) {}
};

// const h-iterator
template <typename T> struct const_h_iterator : public h_iterator<T>
{
	const_h_iterator() :v_iterator<T>() {}
	const_h_iterator(node<T>* p) :v_iterator<T>(p) {}
	const T& operator*() const { return v_iterator<T>::operator*(); }
	const T* operator->() const { return v_iterator<T>::operator->(); }

	const_h_iterator& operator++()
	{
		v_iterator<T>::operator++();
		return *this;
	}

	const_h_iterator& operator++(int)
	{
		auto old = *this;
		++*this;
		return old;
	}
};

} /* namespace forked_linked_list_bits */
} /* namespace dlib */

#endif
