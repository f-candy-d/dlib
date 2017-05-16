/**********************************************************************************
 *
 * forked_linked_list class
 *
 **********************************************************************************/
#ifndef DLIB_CLASSES_FORKED_LINKED_LIST_FORKED_LINKED_LIST_H
#define DLIB_CLASSES_FORKED_LINKED_LIST_FORKED_LINKED_LIST_H

#include "iterator.h"
#include "node.h"

namespace dlib
{

template <typename T> class forked_linked_list
{
public:
	using iterator = forked_linked_list_bits::iterator<T>;
	using node = forked_linked_list_bits::node<T>;

	forked_linked_list();
	forked_linked_list(size_t width, size_t height);
	void push_back_ver_list(const T& def_val);
	void push_back_hor_list(const T& def_val);
	void push_front_ver_list(const T& def_val);
	void push_front_hor_list(const T& def_val);
	iterator insert_ver_list(iterator previous, const T& def_val);
	iterator insert_hor_list(iterator previous, const T& def_val);
	void pop_back_ver_list();
	void pop_back_hor_list();
	void pop_front_ver_list();
	void pop_front_hor_list();
	iterator erase_ver_list(iterator previous);
	iterator erase_hor_list(iterator previous);
	void clear();
	void resize(size_t width, size_t height);

	// inline methods
	size_t size() const { return width_ * height_; }
	size_t width() const { return width_; }
	size_t height() const { return height_; }

private:
	node* origin_;
	size_t width_;
	size_t height_;
};

} /* namespace dlib */

// include the implementation file
#include "impl.h"

#endif
