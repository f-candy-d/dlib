/**********************************************************************************
 *
 * node_cursor class. May/19/2017
 * this class is only used in forked_linked_list class.
 *
 **********************************************************************************/
#ifndef DLIB_CLASSES_FORKED_LINKED_LIST_NODE_CURSOR_H
#define DLIB_CLASSES_FORKED_LINKED_LIST_NODE_CURSOR_H

#include "node.h"
#include "iterators.h"

namespace dlib
{
	// forward declaration
	template <typename T> class forked_linked_list;

namespace forked_linked_list_bits
{

template <typename T> class node_cursor
{
	friend forked_linked_list<T>;

public:
	node<T>*& operator*() { return np; }
	node<T>* operator->() { return &*np; }
	vh_iterator<T> to_vh_iterator() { return std::move(vh_iterator<T>(np)); }
	v_iterator<T> to_v_iterator() { return std::move(v_iterator<T>(np)); }
	h_iterator<T> to_h_iterator() { return std::move(h_iterator<T>(np)); }
	node_cursor& forward_ver() { np = (np != nullptr) ? np->v_next : nullptr; return *this; }
	node_cursor& forward_hor() { np = (np != nullptr) ? np->h_next : nullptr; return *this; }
	bool operator==(const node_cursor& other) { return (np == other.np); }
	bool operator!=(const node_cursor& other) { return !(*this == other); }

	node_cursor& advance_ver(size_t delta)
	{
		for(size_t i = 0; i < delta; ++i)
		{
			forward_ver();
		}

		return *this;
	}

	node_cursor& advance_hor(size_t delta)
	{
		for(size_t i = 0; i < delta; ++i)
		{
			forward_hor();
		}

		return *this;
	}

private:
	node<T>* np;

	// ONLY dlib::forked_linked_list class is able to create the object of this class
	node_cursor() :np(nullptr) {}
	node_cursor(node<T>* p) :np(p) {}
	node_cursor(vh_iterator<T>& itr) :np(itr.node_p()) {}
};

} /* namespace forked_linked_list_bits */
} /* namespace dlib */

#endif
