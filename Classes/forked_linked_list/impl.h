/**********************************************************************************
 *
 * The implementation file of forked_linked_list class. May/19/2017
 *
 **********************************************************************************/
#include "forked_linked_list.h"
#include <cassert>

namespace dlib
{

template <typename T>
forked_linked_list<T>::forked_linked_list()
:head_()
,tail_ver_()
,tail_hor_()
,null_cursor_()
,width_(0)
,height_(0)
,capacity_width_(0)
,capacity_height_(0)
{}

template <typename T>
forked_linked_list<T>::forked_linked_list(size_t width, size_t height)
:forked_linked_list()
{
	set_size(width, height);
	if(size() != 0)
	{
		head_ = build(width, height);
		reset_tails();
	}
}

template <typename T>
forked_linked_list<T>::forked_linked_list(size_t width, size_t height, const T& def_val)
:forked_linked_list()
{
	set_size(width, height);
	if(size() != 0)
	{
		head_ = build(width, height, def_val);
		reset_tails();
	}
}

template <typename T>
void forked_linked_list<T>::push_back_ver_list(const T &def_val)
{
	// if (size = capacity = 0), do nothing
	if(size() != 0)
	{
		auto new_line = build_ver_list(height_, def_val);
		join_ver_list(tail_hor_, new_line);
		tail_hor_ = new_line;
		set_size(width_ + 1, height_);
	}
	else if(capaicty() != 0)
	{
		head_ = build_ver_list(capacity_height_, def_val);
		set_size(1, capacity_height_);
		reset_tails();
	}
}

template <typename T>
void forked_linked_list<T>::push_back_hor_list(const T &def_val)
{
	// if (size = capacity = 0), do nothing
	if(size() != 0)
	{
		auto new_line = build_hor_list(width_, def_val);
		join_hor_list(tail_ver_, new_line);
		tail_ver_ = new_line;
		set_size(width_, height_ + 1);
	}
	else if(capaicty() != 0)
	{
		head_ = build_hor_list(capacity_width_, def_val);
		set_size(capacity_width_, 1);
		reset_tails();
	}
}

template <typename T>
void forked_linked_list<T>::push_front_ver_list(const T &def_val)
{
	// if (size = capacity = 0), do nothing
	if(size() != 0)
	{
		head_ = join_ver_list(build_ver_list(height_, def_val), head_);
		set_size(width_ + 1, height_);
		reset_tail_ver();
	}
	else if(capaicty() != 0)
	{
		head_ = build_ver_list(capacity_height_, def_val);
		set_size(1, capacity_height_);
		reset_tails();
	}
}

template <typename T>
void forked_linked_list<T>::push_front_hor_list(const T &def_val)
{
	// if (size = capacity = 0), do nothing
	if(size() != 0)
	{
		head_ = join_hor_list(build_hor_list(width_, def_val), head_);
		set_size(width_, height_ + 1);
		reset_tail_hor();
	}
	else if(capaicty() != 0)
	{
		head_ = build_hor_list(capacity_width_, def_val);
		set_size(capacity_width_, 1);
		reset_tails();
	}
}

template <typename T>
typename forked_linked_list<T>::h_iterator
forked_linked_list<T>::insert_ver_list(h_iterator previous, const T &def_val)
{
	node_cursor prev_cursor(previous);

	if(prev_cursor == null_cursor_)
	{
		return std::move(previous);
	}

	if(prev_cursor == tail_hor_)
	{
		// push back
		push_back_ver_list(def_val);
		return std::move(tail_hor_.to_h_iterator());
	}
	else
	{
		auto new_ver_list = build_ver_list(height_, def_val);
		auto next_list = node_cursor(prev_cursor).forward_hor();
		join_ver_list(new_ver_list, next_list);
		join_ver_list(prev_cursor, new_ver_list);
		set_size(width_ + 1, height_);

		return std::move(new_ver_list.to_h_iterator());
	}
}

template <typename T>
typename forked_linked_list<T>::v_iterator
forked_linked_list<T>::insert_hor_list(v_iterator previous, const T &def_val)
{
	node_cursor prev_cursor(previous);

	if(prev_cursor == null_cursor_)
	{
		return std::move(previous);
	}

	if(prev_cursor == tail_ver_)
	{
		// push back
		push_back_hor_list(def_val);
		return std::move(tail_ver_.to_v_iterator());
	}
	else
	{
		auto new_hor_list = build_hor_list(width_, def_val);
		auto next_list = node_cursor(prev_cursor).forward_ver();
		join_hor_list(new_hor_list, next_list);
		join_hor_list(prev_cursor, new_hor_list);
		set_size(width_, height_ + 1);

		return std::move(new_hor_list.to_v_iterator());
	}
}

template <typename T>
void forked_linked_list<T>::pop_back_ver_list()
{
	if(size() != 0)
	{
		auto before_tail_hor = head_;
		for(; before_tail_hor->h_next != *tail_hor_; before_tail_hor.forward_hor());
		scrap_ver_list(tail_hor_);
		tail_hor_ = join_ver_list(before_tail_hor, node_cursor(nullptr));
		set_size(width_ - 1, height_);
	}
}

template <typename T>
void forked_linked_list<T>::pop_back_hor_list()
{
	if(size() != 0)
	{
		auto before_tail_ver = head_;
		for(; before_tail_ver->v_next != *tail_ver_; before_tail_ver.forward_ver());
		scrap_hor_list(tail_ver_);
		tail_ver_ = join_hor_list(before_tail_ver, node_cursor(nullptr));
		set_size(width_, height_ - 1);
	}
}

template <typename T>
void forked_linked_list<T>::pop_front_ver_list()
{
	if(size() != 0)
	{
		auto cursor = head_;
		head_.forward_hor();
		scrap_ver_list(cursor);
		set_size(width_ - 1, height_);
		reset_tail_ver();
	}
}

template <typename T>
void forked_linked_list<T>::pop_front_hor_list()
{
	if(size() != 0)
	{
		auto cursor = head_;
		head_.forward_ver();
		scrap_hor_list(cursor);
		set_size(width_, height_ - 1);
		reset_tail_hor();
	}
}

template <typename T>
typename forked_linked_list<T>::h_iterator
forked_linked_list<T>::erase_ver_list(h_iterator previous)
{
	node_cursor prev_cursor(previous);

	if(prev_cursor == null_cursor_ || prev_cursor == tail_hor_ || size() == 0)
	{
		return std::move(hend());
	}
	else
	{
		auto next = prev_cursor;
		auto after_next = prev_cursor;
		next.forward_hor();
		after_next.advance_hor(2);

		join_ver_list(prev_cursor, after_next);
		scrap_ver_list(next);

		set_size(width_ - 1, height_);
		reset_tail_hor();

		return std::move(after_next.to_h_iterator());
	}
}

template <typename T>
typename forked_linked_list<T>::v_iterator
forked_linked_list<T>::erase_hor_list(v_iterator previous)
{
	node_cursor prev_cursor(previous);

	if(prev_cursor == null_cursor_ || prev_cursor == tail_ver_ || size() == 0)
	{
		return std::move(vend());
	}
	else
	{
		auto next = prev_cursor;
		auto after_next = prev_cursor;
		next.forward_ver();
		after_next.advance_ver(2);

		join_hor_list(previous, after_next);
		scrap_hor_list(next);

		set_size(width_, height_ - 1);
		reset_tail_ver();

		return std::move(after_next.to_v_iterator());
	}
}

template <typename T>
void forked_linked_list<T>::clear()
{
		while(size() != 0)
		{
			pop_front_hor_list();
		}
}

template <typename T>
void forked_linked_list<T>::resize(size_t width, size_t height)
{
	resize(width, height, T());
}

template <typename T>
void forked_linked_list<T>::resize(size_t width, size_t height, const T& def_val)
{
	if(width * height == 0)
	{
		clear();
	}
	else if(size() == 0)
	{
		head_ = build(width, height, def_val);
		set_size(width, height);
		reset_tails();
	}
	else
	{
		// resize width
		auto diff_w = static_cast<int>(width) - static_cast<int>(width_);

		if(0 < diff_w)
		{
			for(int i = 0; i < diff_w; ++i)
			{
				push_back_ver_list(def_val);
			}
		}
		else if(diff_w < 0)
		{
			for(int i = 0; i < diff_w * -1; ++i)
			{
				pop_back_ver_list();
			}
		}

		// resize height
		auto diff_h = static_cast<int>(height) - static_cast<int>(height_);

		if(0 < diff_h)
		{
			for(int i = 0; i < diff_h; ++i)
			{
				push_back_hor_list(def_val);
			}
		}
		else if(diff_h < 0)
		{
			for(int i = 0; i < diff_h * -1; ++i)
			{
				pop_back_hor_list();
			}
		}
	}

	fit_capacity();
}

template <typename T>
void forked_linked_list<T>::swap_ver_list(h_iterator prev_left_itr, h_iterator prev_right_itr)
{
	node_cursor prev_left(prev_left_itr);
	node_cursor prev_right(prev_right_itr);

	if(prev_left == null_cursor_ || prev_right == null_cursor_ ||
		prev_left == tail_hor_ || prev_right == tail_hor_)
		return;

	node_cursor left(prev_left->h_next);
	node_cursor right(prev_right->h_next);
	node_cursor next_right(right->h_next);

	if(prev_left != right && prev_right != left)
	{
		join_ver_list(prev_right, left);
		join_ver_list(prev_left, right);
		join_ver_list(right, node_cursor(left->h_next));
		join_ver_list(left, next_right);
	}
	else
	{
		join_ver_list(left, next_right);
		join_ver_list(right, left);
		join_ver_list(prev_left, right);
	}

	reset_tails();
}

template <typename T>
void forked_linked_list<T>::swap_hor_list(v_iterator prev_below_itr, v_iterator prev_above_itr)
{
	node_cursor prev_below(prev_below_itr);
	node_cursor prev_above(prev_above_itr);

	if(prev_below == null_cursor_ || prev_above == null_cursor_ ||
		prev_below == tail_ver_ || prev_above == tail_ver_)
		return;

	node_cursor below(prev_below->v_next);
	node_cursor above(prev_above->v_next);
	node_cursor next_above(above->v_next);

	if(prev_below != above && prev_above != below)
	{
		join_hor_list(prev_above, below);
		join_hor_list(prev_below, above);
		join_hor_list(above, node_cursor(below->v_next));
		join_hor_list(below, next_above);
	}
	else
	{
		join_hor_list(below, next_above);
		join_hor_list(above, below);
		join_hor_list(prev_below, above);
	}

	reset_tails();
}

template <typename T>
void forked_linked_list<T>::swap_with_front_ver_list(h_iterator prev_itr)
{
	node_cursor prev(prev_itr);

	if(prev == null_cursor_ || prev == tail_hor_)
	{
		return;
	}

	node_cursor cursor(prev->h_next);
	node_cursor next(cursor->h_next);
	node_cursor old_head(head_);
	head_ = join_ver_list(cursor, node_cursor(head_->h_next));
	join_ver_list(prev, old_head);
	join_ver_list(old_head, next);

	reset_tails();
}

template <typename T>
void forked_linked_list<T>::swap_with_front_hor_list(v_iterator prev_itr)
{
	node_cursor prev(prev_itr);

	if(prev == null_cursor_ || prev == tail_ver_)
	{
		return;
	}

	node_cursor cursor(prev->v_next);
	node_cursor next(cursor->v_next);
	node_cursor old_head(head_);
	head_ = join_hor_list(cursor, node_cursor(head_->v_next));
	join_hor_list(prev, old_head);
	join_hor_list(old_head, next);

	reset_tails();
}

template <typename T>
void forked_linked_list<T>::value_swap_ver_list(vh_iterator tom, vh_iterator jerry)
{
	T cheese;

	for(; tom != vhend() && jerry != vhend(); tom.forward_ver(), jerry.forward_ver())
	{
		cheese = *tom;
		*tom = *jerry;
		*jerry = std::move(cheese);
	}
}

template <typename T>
void forked_linked_list<T>::value_swap_hor_list(vh_iterator tom, vh_iterator jerry)
{
	T cheese;

	for(; tom != vend() && jerry != vend(); tom.forward_hor(), jerry.forward_hor())
	{
		cheese = *tom;
		*tom = *jerry;
		*jerry = std::move(cheese);
	}
}

// template <typename T>
// void forked_linked_list<T>::to_front_ver_list(h_iterator prev_itr)
// {
// 	node_cursor prev(prev_itr);
//
// 	if(prev == null_cursor_ || prev == tail_hor_)
// 	{
// 		return;
// 	}
//
// 	node_cursor cursor(prev->h_next);
// 	join_ver_list(prev, node_cursor(cursor->h_next));
// 	head_ = join_ver_list(cursor, head_);
//
// 	reset_tails();
// }
//
// template <typename T>
// void forked_linked_list<T>::to_front_hor_list(v_iterator prev_itr)
// {
// 	node_cursor prev(prev_itr);
//
// 	if(prev == null_cursor_ || prev == tail_ver_)
// 	{
// 		return;
// 	}
//
// 	node_cursor cursor(prev->v_next);
// 	join_hor_list(prev, node_cursor(cursor->v_next));
// 	head_ = join_hor_list(cursor, head_);
//
// 	reset_tails();
// }

template <typename T>
typename forked_linked_list<T>::node_cursor
forked_linked_list<T>::build(size_t width, size_t height, const T &def_val)
{
	if(width * height == 0)
		return std::move(node_cursor(nullptr));

	// create a base list
	auto origin = build_hor_list(width, def_val);

	auto cursor = origin;
	for(size_t i = 1; i < height; ++i)
	{
		join_hor_list(cursor, build_hor_list(width, def_val));

		// move to the node above
		cursor.forward_ver();
	}

	return std::move(origin);
}

template <typename T>
typename forked_linked_list<T>::node_cursor
forked_linked_list<T>::build_ver_list(size_t height, const T &def_val)
{
	if(height == 0)
		return std::move(node_cursor(nullptr));

	node_cursor head(new node(def_val));
	auto cursor = head;
	for(size_t i = 1; i < height; ++i)
	{
		cursor->v_next = new node(def_val);
		cursor.forward_ver();
	}

	return std::move(head);
}

template <typename T>
typename forked_linked_list<T>::node_cursor
forked_linked_list<T>::build_hor_list(size_t width, const T &def_val)
{
	if(width == 0)
		return std::move(node_cursor(nullptr));

	node_cursor head(new node(def_val));
	auto cursor = head;
	for(size_t i = 1; i < width; ++i)
	{
		cursor->h_next = new node(def_val);
		cursor.forward_hor();
	}

	return std::move(head);
}

template <typename T>
void forked_linked_list<T>::set_size(size_t width, size_t height)
{
	if(width * height != 0)
	{
		width_ = width;
		height_ = height;
	}
	else
	{
		width_ = 0;
		height_ = 0;
		on_size_zero();
	}

	if(capaicty() < size())
	{
		fit_capacity();
	}
}

template <typename T>
typename forked_linked_list<T>::node_cursor
forked_linked_list<T>::join_ver_list(node_cursor left, node_cursor right)
{
	if(left == null_cursor_)
	{
		return std::move(left);
	}

	if(left == right)
	{
		return join_ver_list(left, node_cursor(nullptr));
	}

	auto l_cursor = left;
	for(; left != null_cursor_; left.forward_ver(), right.forward_ver())
	{
		left->h_next = *right;
	}

	return std::move(l_cursor);
}

template <typename T>
typename forked_linked_list<T>::node_cursor
forked_linked_list<T>::join_hor_list(node_cursor below, node_cursor above)
{
	if(below == null_cursor_)
	{
		return std::move(below);
	}

	if(below == above)
	{
		return join_hor_list(below, node_cursor(nullptr));
	}

	auto b_cursor = below;
	for(; below != null_cursor_; below.forward_hor(), above.forward_hor())
	{
		below->v_next = *above;
	}

	return std::move(b_cursor);
}

template <typename T>
void forked_linked_list<T>::scrap_ver_list(node_cursor head)
{
	for(auto cursor = head; cursor != null_cursor_; cursor = head)
	{
		head.forward_ver();
		delete *cursor;
	}
}

template <typename T>
void forked_linked_list<T>::scrap_hor_list(node_cursor head)
{
	for(auto cursor = head; cursor != null_cursor_; cursor = head)
	{
		head.forward_hor();
		delete *cursor;
	}
}

template <typename T>
void forked_linked_list<T>::on_size_zero()
{
	head_ = tail_hor_ = tail_ver_ = null_cursor_;
}

template <typename T>
void forked_linked_list<T>::reset_tails()
{
	reset_tail_ver();
	reset_tail_hor();
}

template <typename T>
void forked_linked_list<T>::reset_tail_ver()
{
	tail_ver_ = head_;

	if(head_ != null_cursor_)
	{
		// find vertical tail
		for(; tail_ver_->v_next != nullptr; tail_ver_.forward_ver());
	}
}

template <typename T>
void forked_linked_list<T>::reset_tail_hor()
{
	tail_hor_ = head_;

	if(head_ != null_cursor_)
	{
		// find horizontal tail
		for(; tail_hor_->h_next != nullptr; tail_hor_.forward_hor());
	}
}

} /* namespace dlib */
