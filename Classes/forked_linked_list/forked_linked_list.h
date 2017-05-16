#ifndef DLIB_CLASSES_FORKED_LINKED_LIST_FORKED_LINKED_LIST_H
#define DLIB_CLASSES_FORKED_LINKED_LIST_FORKED_LINKED_LIST_H

#include <cstdio> // std::size_t

namespace dlib
{

template <typename T> class forked_linked_list
{
	// forward declaration
	struct node;

public:
	forked_linked_list();
	void push_back_ver_list(T def_val);
	void push_back_hor_list(T def_val);
	void push_front_ver_list(T def_val);
	void push_front_hor_list(T def_val);
	void insert_ver_list(T def_val);
	void insert_hor_list(T def_val);
	void pop_back_ver_list();
	void pop_back_hor_list();
	void pop_front_ver_list();
	void pop_front_hor_list();
	void erase_ver_list();
	void erase_hor_list();
	void clear();

	// inline methods
	size_t size() const { return width_ * height_; }
	size_t width() const { return width_; }
	size_t height() const { return height_; }

private:
	node* origin_;
	size_t width_;
	size_t height_;

	struct node
	{
		T value;
		struct node* v_next;
		struct node* h_next;

		node(const T& val, struct node* vnxt = nullptr, struct node* hnxt = nullptr)
		:value(val),v_next(vnxt),h_next(hnxt) {}
	};
};

// include the implementation file
#include "impl.h"

} /* namespace dlib */

#endif
