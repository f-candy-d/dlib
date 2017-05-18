/**********************************************************************************
 *
 * node_cursor class declaration. this class is only used in forked_linked_list class.
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
	vh_iterator<T> to_vh_iterator() { return std::move(vh_iterator<T>(np, running_direction::kVertical)); }
	v_iterator<T> to_v_iterator() { return std::move(v_iterator<T>(np)); }
	h_iterator<T> to_h_iterator() { return std::move(h_iterator<T>(np)); }
	node_cursor& move_ver() { np = (np != nullptr) ? np->v_next : nullptr; return *this; }
	node_cursor& move_hor() { np = (np != nullptr) ? np->h_next : nullptr; return *this; }
	bool operator==(const node_cursor& other) { return (np == other.np); }
	bool operator!=(const node_cursor& other) { return !(*this == other); }

private:
	node<T>* np;

	node_cursor() :np(nullptr) {}
	node_cursor(node<T>* p) :np(p) {}
};

} /* namespace forked_linked_list_bits */
} /* namespace dlib */

#endif
