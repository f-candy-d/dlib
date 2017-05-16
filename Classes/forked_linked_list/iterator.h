/**********************************************************************************
 *
 * Iterators of forked_linked_list class
 *
 **********************************************************************************/
#ifndef DLIB_CLASSES_FORKED_LINKED_LIST_ITERATOR_H
#define DLIB_CLASSES_FORKED_LINKED_LIST_ITERATOR_H

#include <iterator>
#include "node.h"

namespace dlib
{
namespace forked_linked_list_bits
{

// the running direction of an iterator (forward vertically or horizontally)
enum class iterator_direction
{
	kVertical, kHorizontal
};

// normal iterator
template <typename T> struct iterator : public std::iterator<
	std::forward_iterator_tag, T, std::ptrdiff_t, T*, T&>
{
	iterator() :np(nullptr),i_dir(iterator_direction::kVertical) {}
	iterator(node<T>* p, iterator_direction dir) :np(p),i_dir(dir) {}
	T& operator*() const { return np->value; }
	T* operator->() const { return &**this; }
	bool operator==(const iterator& other) const { return (np == other.np); }
	bool operator!=(const iterator& other) const { return !(*this == other); }
	iterator& forward_var() { np = (np != nullptr) ? np->v_next : nullptr; return *this; }
	iterator& forward_hor() { np = (np != nullptr) ? np->h_next : nullptr; return *this; }

	iterator& operator++()
	{
		switch(i_dir)
		{
			case iterator_direction::kVertical :
			{
				np = (np != nullptr) ? np->v_next : nullptr;
				break;
			}

			case iterator_direction::kHorizontal :
			{
				np = (np != nullptr) ? np->h_next : nullptr;
				break;
			}
		}

		return *this;
	}

	iterator& operator++(int)
	{
		auto old = *this;
		++*this;
		return old;
	}

private:
	node<T>* np;
	iterator_direction i_dir;
};

// const iterator
template <typename T> struct const_iterator : public iterator<T>
{
	const_iterator() :iterator<T>() {}
	const_iterator(node<T>* p, iterator_direction dir) :iterator<T>(p, dir) {}
	const T& operator*() const { return iterator<T>::operator*(); }
	const T* operator->() const { return iterator<T>::operator->(); }

	const_iterator& operator++()
	{
		iterator<T>::operator++();
		return *this;
	}

	const_iterator& operator++(int)
	{
		auto old = *this;
		++*this;
		return old;
	}
};

} /* namespace forked_linked_list_bits */
} /* namespace dlib */

#endif
