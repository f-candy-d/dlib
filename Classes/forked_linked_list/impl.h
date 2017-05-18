/**********************************************************************************
 *
 * The implementation file of forked_linked_list class.
 *
 **********************************************************************************/
#include "forked_linked_list.h"
#include <cassert>
#include <iostream>

namespace dlib
{

template <typename T>
forked_linked_list<T>::forked_linked_list()
:head_()
,tail_var_()
,tail_hor_()
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
		join_hor_list(tail_var_, new_line);
		tail_var_ = new_line;
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
	if(previous.nodep() == nullptr)
	{
		return std::move(previous);
	}

	// if(previous == tail_hor_)
	if(previous == h_iterator(*tail_hor_))
	{
		// push back
		push_back_ver_list(def_val);
		// return std::move(h_iterator(*tail_hor_));
		return std::move(h_iterator(*tail_hor_));
	}
	else
	{
		// auto new_ver_list = build_ver_list(height_, def_val);
		auto new_ver_list = build_ver_list(height_, def_val).to_v_iterator();
		auto next_list = previous;
		++next_list;
		// join_ver_list(new_ver_list, next_list);
		join_ver_list(node_cursor(new_ver_list.nodep()), node_cursor(next_list.nodep()));
		// join_ver_list(previous, new_ver_list);
		join_ver_list(node_cursor(previous.nodep()), node_cursor(new_ver_list.nodep()));
		set_size(width_ + 1, height_);

		return std::move(h_iterator(new_ver_list.nodep()));
	}
}

template <typename T>
typename forked_linked_list<T>::v_iterator
forked_linked_list<T>::insert_hor_list(v_iterator previous, const T &def_val)
{
	if(previous.nodep() == nullptr)
	{
		return std::move(previous);
	}

	// if(previous == tail_hor_)
	if(previous == v_iterator(*tail_hor_))
	{
		// push back
		push_back_hor_list(def_val);
		// return std::move(v_iterator(*tail_var_));
		return std::move(v_iterator(*tail_var_));
	}
	else
	{
		// auto new_hor_list = build_hor_list(width_, def_val);
		auto new_hor_list = build_hor_list(width_, def_val).to_h_iterator();
		auto next_list = previous;
		++next_list;
		// join_hor_list(new_hor_list, next_list);
		join_hor_list(node_cursor(new_hor_list.nodep()), node_cursor(next_list.nodep()));
		// join_hor_list(previous, new_hor_list);
		join_hor_list(node_cursor(previous.nodep()), node_cursor(new_hor_list.nodep()));
		set_size(width_, height_ + 1);

		return std::move(v_iterator(new_hor_list.nodep()));
	}
}

template <typename T>
void forked_linked_list<T>::pop_back_ver_list()
{
	if(size() != 0)
	{
		auto before_tail_hor = head_;
		for(; before_tail_hor->h_next != *tail_hor_; before_tail_hor.move_hor());
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
		// auto before_tail_ver = head_;
		auto before_tail_ver = head_.to_vh_iterator();
		for(; before_tail_ver.nodep()->v_next != *tail_var_; before_tail_ver.forward_var());
		scrap_hor_list(tail_var_);
		// tail_var_ = join_hor_list(before_tail_ver, vh_iterator());
		tail_var_ = join_hor_list(node_cursor(before_tail_ver.nodep()), node_cursor(vh_iterator().nodep()));
		set_size(width_, height_ - 1);
	}
}

template <typename T>
void forked_linked_list<T>::pop_front_ver_list()
{
	if(size() != 0)
	{
		auto cursor = head_;
		// head_.forward_hor();
		head_.move_hor();
		scrap_ver_list(cursor);
		// scrap_ver_list(node_cursor(itr.nodep()));
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
		// head_.forward_var();
		head_.move_ver();
		scrap_hor_list(cursor);
		// scrap_hor_list(node_cursor(itr.nodep()));
		set_size(width_, height_ - 1);
		reset_tail_hor();
	}
}

template <typename T>
typename forked_linked_list<T>::h_iterator
forked_linked_list<T>::erase_ver_list(h_iterator previous)
{
	// if(previous.nodep() == nullptr || previous == tail_hor_ || size() == 0)
	if(previous.nodep() == nullptr || previous == h_iterator(*tail_hor_) || size() == 0)
	{
		return std::move(hend());
	}
	else
	{
		auto next = previous;
		auto after_next = previous;
		++next;
		++after_next;
		++after_next;

		// join_ver_list(previous, after_next);
		join_ver_list(node_cursor(previous.nodep()), node_cursor(after_next.nodep()));
		// scrap_ver_list(next);
		scrap_ver_list(node_cursor(next.nodep()));

		set_size(width_ - 1, height_);
		reset_tail_hor();

		return std::move(after_next);
	}
}

template <typename T>
typename forked_linked_list<T>::v_iterator
forked_linked_list<T>::erase_hor_list(v_iterator previous)
{
	// if(previous.nodep() == nullptr || previous == tail_var_ || size() == 0)
	if(previous.nodep() == nullptr || previous == v_iterator(*tail_var_) || size() == 0)
	{
		return std::move(vend());
	}
	else
	{
		auto next = previous;
		auto after_next = previous;
		++next;
		++after_next;
		++after_next;

		// join_hor_list(previous, after_next);
		join_hor_list(node_cursor(previous.nodep()), node_cursor(after_next.nodep()));
		// scrap_hor_list(next);
		scrap_hor_list(node_cursor(next.nodep()));

		set_size(width_, height_ - 1);
		reset_tail_ver();

		return std::move(after_next);
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
		// head_ = build(width, height, def_val).to_vh_iterator();
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
		// join_hor_list(cursor, build_hor_list(width, def_val));
		join_hor_list(cursor, build_hor_list(width, def_val));

		// move to the node above
		cursor.move_ver();
	}

	return std::move(origin);
}

template <typename T>
typename forked_linked_list<T>::node_cursor
forked_linked_list<T>::build_ver_list(size_t height, const T &def_val)
{
	if(height == 0)
		return std::move(node_cursor(nullptr));

	// auto head = vh_iterator(new node(def_val), run_dir::kVertical);
	node_cursor head(new node(def_val));
	auto cursor = head;
	for(size_t i = 1; i < height; ++i)
	{
		// itr.nodep()->v_next = new node(def_val);
		cursor->v_next = new node(def_val);
		// ++itr;
		cursor.move_ver();
	}

	return std::move(head);
}

template <typename T>
typename forked_linked_list<T>::node_cursor
forked_linked_list<T>::build_hor_list(size_t width, const T &def_val)
{
	if(width == 0)
		return std::move(node_cursor(nullptr));
		// return std::move(vh_iterator(nullptr, run_dir::kHorizontal));

	// auto head = vh_iterator(new node(def_val), run_dir::kHorizontal);
	node_cursor head(new node(def_val));
	auto cursor = head;
	for(size_t i = 1; i < width; ++i)
	{
		// itr.nodep()->h_next = new node(def_val);
		cursor->h_next = new node(def_val);
		// ++itr;
		cursor.move_hor();
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
	if(*left == nullptr)
	{
		return std::move(left);
	}

	auto l_cursor = left;
	for(; *left != nullptr; left.move_ver(), right.move_ver())
	{
		left->h_next = *right;
	}

	return std::move(l_cursor);
}

template <typename T>
typename forked_linked_list<T>::node_cursor
forked_linked_list<T>::join_hor_list(node_cursor below, node_cursor above)
{
	if(*below == nullptr)
	{
		return std::move(below);
	}

	auto b_cursor = below;
	for(; below != nullptr; below.move_hor(), above.move_hor())
	{
		below->v_next = *above;
	}

	return std::move(b_cursor);
}

template <typename T>
void forked_linked_list<T>::scrap_ver_list(node_cursor head)
{
	for(auto cursor = head; *cursor != nullptr; cursor = head)
	{
		head.move_ver();
		delete *cursor;
	}
}

template <typename T>
void forked_linked_list<T>::scrap_hor_list(node_cursor head)
{
	for(auto cursor = head; *cursor != nullptr; cursor = head)
	{
		head.move_hor();
		delete *cursor;
	}
}

template <typename T>
void forked_linked_list<T>::on_size_zero()
{
	// head_ = tail_hor_ = tail_var_ = vhend();
	*head_ = *tail_hor_ = *tail_var_ = vhend().nodep();
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
	if(*head_ == vhend().nodep())
	{
		// tail_var_ = vhend();
		*tail_var_ = vhend().nodep();
	}
	else
	{
		// find vertical tail
		tail_var_ = head_;
		// for(; *tail_var_->v_next != nullptr; tail_var_.forward_var());
		for(; tail_var_->v_next != nullptr; tail_var_.move_ver());
	}
}

template <typename T>
void forked_linked_list<T>::reset_tail_hor()
{
	if(*head_ == vhend().nodep())
	{
		tail_hor_ = vhend().nodep();
	}
	else
	{
		// find horizontal tail
		tail_hor_ = head_;
		for(; tail_hor_->h_next != nullptr; tail_hor_.move_hor());
	}
}

} /* namespace dlib */
