/**********************************************************************************
 *
 * forked_linked_list class. May/19/2017
 *
 **********************************************************************************/
#ifndef DLIB_CLASSES_FORKED_LINKED_LIST_FORKED_LINKED_LIST_H
#define DLIB_CLASSES_FORKED_LINKED_LIST_FORKED_LINKED_LIST_H

#include "iterators.h"
#include "node.h"
#include "node_cursor.h"

namespace dlib
{

template <typename T> class forked_linked_list
{
public:
	using vh_iterator = forked_linked_list_bits::vh_iterator<T>;
	using const_vh_iterator = forked_linked_list_bits::const_vh_iterator<T>;
	using v_iterator = forked_linked_list_bits::v_iterator<T>;
	using const_v_iterator = forked_linked_list_bits::const_v_iterator<T>;
	using h_iterator = forked_linked_list_bits::h_iterator<T>;
	using const_h_iterator = forked_linked_list_bits::const_h_iterator<T>;
	using run_dir = forked_linked_list_bits::running_direction;
	using node = forked_linked_list_bits::node<T>;
	using node_cursor = forked_linked_list_bits::node_cursor<T>;

	forked_linked_list();
	forked_linked_list(size_t width, size_t height);
	forked_linked_list(size_t width, size_t height, const T& def_val);
	void push_back_ver_list(const T& def_val);
	void push_back_hor_list(const T& def_val);
	void push_front_ver_list(const T& def_val);
	void push_front_hor_list(const T& def_val);
	h_iterator insert_ver_list(h_iterator previous, const T& def_val);
	v_iterator insert_hor_list(v_iterator previous, const T& def_val);
	void pop_back_ver_list();
	void pop_back_hor_list();
	void pop_front_ver_list();
	void pop_front_hor_list();
	h_iterator erase_ver_list(h_iterator previous);
	v_iterator erase_hor_list(v_iterator previous);
	void clear();
	void resize(size_t width, size_t height);
	void resize(size_t width, size_t height, const T& def_val);
	void swap_ver_list(h_iterator prev_left_itr, h_iterator prev_right_itr);
	void swap_hor_list(v_iterator prev_below_itr, v_iterator prev_above_itr);
	void value_swap_ver_list(vh_iterator tom, vh_iterator jerry);
	void value_swap_hor_list(vh_iterator tom, vh_iterator jerry);

	// inline methods
	size_t size() const { return width_ * height_; }
	size_t width() const { return width_; }
	size_t height() const { return height_; }
	size_t capaicty() const { return capacity_width_ * capacity_height_; }
	size_t capacity_width() const { return capacity_width_; }
	size_t capacity_height() const { return capacity_height_; }
	void fit_capacity() { capacity_width_ = width_; capacity_height_ = height_; }
	// vh-iterator
	vh_iterator vhbegin() { return std::move(vh_iterator(*head_)); }
	const_vh_iterator vhbegin() const { return const_vh_iterator(*head_); }
	const_vh_iterator cvhbegin() const { return const_vh_iterator(*head_); }
	vh_iterator vhend() { return vh_iterator(nullptr); }
	const_vh_iterator vhend() const { return const_vh_iterator(nullptr); }
	const_vh_iterator cvhend() const { return const_vh_iterator(nullptr); }
	// v-iterator
	v_iterator vbegin() { return v_iterator(*head_); }
	const_v_iterator vbegin() const { return const_v_iterator(*head_); }
	const_v_iterator cvbegin() const { return const_v_iterator(*head_); }
	v_iterator vend() { return v_iterator(nullptr); }
	const_v_iterator vend() const { return const_v_iterator(nullptr); }
	const_v_iterator cvend() const { return const_v_iterator(nullptr); }
	// h-iterator
	h_iterator hbegin() { return h_iterator(*head_); }
	const_h_iterator hbegin() const { return const_h_iterator(*head_); }
	const_h_iterator chbegin() const { return const_h_iterator(*head_); }
	h_iterator hend() { return h_iterator(nullptr); }
	const_h_iterator hend() const { return const_h_iterator(nullptr); }
	const_h_iterator chend() const { return const_h_iterator(nullptr); }

private:
	node_cursor head_;
	node_cursor tail_ver_;
	node_cursor tail_hor_;
	const node_cursor null_cursor_;
	size_t width_;
	size_t height_;
	size_t capacity_width_;
	size_t capacity_height_;

	node_cursor build(size_t width, size_t height, const T& def_val = T());
	node_cursor build_ver_list(size_t height, const T& def_val = T());
	node_cursor build_hor_list(size_t width, const T& def_val = T());
	void set_size(size_t width, size_t height);
	node_cursor join_ver_list(node_cursor left, node_cursor right);
	node_cursor join_hor_list(node_cursor below, node_cursor above);
	void scrap_ver_list(node_cursor head);
	void scrap_hor_list(node_cursor head);
	void on_size_zero();
	void reset_tails();
	void reset_tail_ver();
	void reset_tail_hor();
};

} /* namespace dlib */

// include the implementation file
#include "impl.h"

#endif
