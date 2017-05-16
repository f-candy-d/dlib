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
	using const_iterator = forked_linked_list_bits::const_iterator<T>;
	using node = forked_linked_list_bits::node<T>;
	using itr_dir = forked_linked_list_bits::iterator_direction;

	forked_linked_list();
	forked_linked_list(size_t width, size_t height);
	forked_linked_list(size_t width, size_t height, const T& def_val);
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
	void resize(size_t width, size_t height, const T& def_val);

	// inline methods
	size_t size() const { return width_ * height_; }
	size_t width() const { return width_; }
	size_t height() const { return height_; }
	iterator begin() { return iterator(origin_, itr_dir::kVertical); }
	const_iterator begin() const { return const_iterator(origin_, itr_dir::kVertical); }
	const_iterator cbegin() const { return const_iterator(origin_, itr_dir::kVertical); }
	iterator end() { return iterator(nullptr, itr_dir::kVertical); }
	const_iterator end() const { return const_iterator(nullptr, itr_dir::kVertical); }
	const_iterator cend() const { return const_iterator(nullptr, itr_dir::kVertical); }
	iterator vbegin() { return std::move(begin()); }
	const_iterator vbegin() const { return std::move(begin()); }
	const_iterator cvbegin() const { return std::move(cbegin()); }
	iterator vend() { return std::move(end()); }
	const_iterator vend() const { return std::move(end()); }
	const_iterator cvend() const { return std::move(cend()); }
	iterator hbegin() { return iterator(origin_, itr_dir::kHorizontal); }
	const_iterator hbegin() const { return const_iterator(origin_, itr_dir::kHorizontal); }
	const_iterator chbegin() const { return const_iterator(origin_, itr_dir::kHorizontal); }
	iterator hend() { return iterator(nullptr, itr_dir::kHorizontal); }
	const_iterator hend() const { return const_iterator(nullptr, itr_dir::kHorizontal); }
	const_iterator chend() const { return const_iterator(nullptr, itr_dir::kHorizontal); }

private:
	node* origin_;
	size_t width_;
	size_t height_;

	node* build(size_t width, size_t height, const T& def_val = T());
	node* build_ver_list(size_t height, const T& def_val = T());
	node* build_hor_list(size_t width, const T& def_val = T());
	void set_size(size_t width, size_t height);
};

} /* namespace dlib */

// include the implementation file
#include "impl.h"

#endif
