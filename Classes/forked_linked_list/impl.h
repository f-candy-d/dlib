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
		set_tails();
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
		set_tails();
	}
}

template <typename T>
void forked_linked_list<T>::push_back_ver_list(const T &def_val)
{
	// auto new_tail_hor = build_ver_list(height_, def_val);
	// join_ver_list(tail_hor_, new_tail_hor);
	// tail_hor_ = new_tail_hor;
	//
	// if(tail_hor_.nodep() != nullptr)
	// {
	// 	set_size(width_ + 1, height_);
	// }

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
		set_tails();
	}
}

template <typename T>
void forked_linked_list<T>::push_back_hor_list(const T &def_val)
{
	// auto new_tail_ver = build_ver_list(width_, def_val);
	// join_ver_list(tail_var_, new_tail_ver);
	// tail_var_ = new_tail_ver;
	//
	// if(tail_var_.nodep() != nullptr)
	// {
	// 	set_size(width_, height_ + 1);
	// }

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
		set_tails();
	}
}

template <typename T>
void forked_linked_list<T>::push_front_ver_list(const T &def_val)
{
	// head_ = join_ver_list(build_ver_list(height_, def_val), head_);
	// if(head_.nodep() != nullptr)
	// {
	// 	set_size(width_ + 1, height_);
	// }

	// if (size = capacity = 0), do nothing
	if(size() != 0)
	{
		head_ = join_ver_list(build_ver_list(height_, def_val), head_);
		set_size(width_ + 1, height_);
	}
	else if(capaicty() != 0)
	{
		head_ = build_ver_list(capacity_height_, def_val);
		set_size(1, capacity_height_);
		set_tails();
	}
}

template <typename T>
void forked_linked_list<T>::push_front_hor_list(const T &def_val)
{
	// head_ = join_hor_list(build_hor_list(width_, def_val), head_);
	// if(head_.nodep() != nullptr)
	// {
	// 	set_size(width_, height_ + 1);
	// }

	// if (size = capacity = 0), do nothing
	if(size() != 0)
	{
		head_ = join_hor_list(build_hor_list(width_, def_val), head_);
		set_size(width_, height_ + 1);
	}
	else if(capaicty() != 0)
	{
		head_ = build_hor_list(capacity_width_, def_val);
		set_size(capacity_width_, 1);
		set_tails();
	}
}

template <typename T>
typename forked_linked_list<T>::h_iterator
forked_linked_list<T>::insert_ver_list(h_iterator previous, const T &def_val)
{
	// if(previous.nodep() == nullptr)
	// 	return previous;
	//
	// if(previous == tail_hor_)
	// {
	// 	// push back
	// 	push_back_ver_list(def_val);
	// 	return std::move(h_iterator(tail_hor_.nodep()));
	// }
	// else
	// {
	// 	auto new_ver_list = build_ver_list(height_, def_val);
	// 	auto next_list = previous;
	// 	++next_list;
	// 	join_ver_list(new_ver_list, next_list);
	// 	join_ver_list(previous, new_ver_list);
	// 	set_size(width_ + 1, height_);
	//
	// 	return std::move(h_iterator(new_ver_list.nodep()));
	// }

	if(previous.nodep() == nullptr)
	{
		return std::move(previous);
	}

	if(previous == tail_hor_)
	{
		// push back
		push_back_ver_list(def_val);
		return std::move(h_iterator(tail_hor_.nodep()));
	}
	else
	{
		auto new_ver_list = build_ver_list(height_, def_val);
		auto next_list = previous;
		++next_list;
		join_ver_list(new_ver_list, next_list);
		join_ver_list(previous, new_ver_list);
		set_size(width_ + 1, height_);

		return std::move(h_iterator(new_ver_list.nodep()));
	}
}

template <typename T>
typename forked_linked_list<T>::v_iterator
forked_linked_list<T>::insert_hor_list(v_iterator previous, const T &def_val)
{
	// if(previous.nodep() == nullptr)
	// 	return previous;
	//
	// if(previous == tail_var_)
	// {
	// 	// push back
	// 	push_back_hor_list(def_val);
	// 	return std::move(v_iterator(tail_var_.nodep()));
	// }
	// else
	// {
	// 	auto new_hor_list = build_hor_list(width_, def_val);
	// 	auto next_list = previous;
	// 	++next_list;
	// 	join_hor_list(new_hor_list, next_list);
	// 	join_hor_list(previous, new_hor_list);
	// 	set_size(width_, height_ + 1);
	//
	// 	return std::move(v_iterator(new_hor_list.nodep()));
	// }

	if(previous.nodep() == nullptr)
	{
		return std::move(previous);
	}

	if(previous == tail_hor_)
	{
		// push back
		push_back_hor_list(def_val);
		return std::move(v_iterator(tail_var_.nodep()));
	}
	else
	{
		auto new_hor_list = build_hor_list(width_, def_val);
		auto next_list = previous;
		++next_list;
		join_hor_list(new_hor_list, next_list);
		join_hor_list(previous, new_hor_list);
		set_size(width_, height_ + 1);

		return std::move(v_iterator(new_hor_list.nodep()));
	}
}

template <typename T>
void forked_linked_list<T>::pop_back_ver_list()
{

}

template <typename T>
void forked_linked_list<T>::pop_back_hor_list()
{

}

template <typename T>
void forked_linked_list<T>::pop_front_ver_list()
{
	// if(head_.nodep() != nullptr)
	// {
	// 	auto itr = head_;
	// 	head_.forward_hor();
	// 	scrap_ver_list(itr);
	//
	// 	set_size(width_ - 1, height_);
	// }
}

template <typename T>
void forked_linked_list<T>::pop_front_hor_list()
{
	// if(head_.nodep() != nullptr)
	// {
	// 	auto itr = head_;
	// 	head_.forward_var();
	// 	scrap_hor_list(itr);
	//
	// 	set_size(width_, height_ - 1);
	// }
}

template <typename T>
typename forked_linked_list<T>::h_iterator
forked_linked_list<T>::erase_ver_list(h_iterator previous)
{
	// if(previous == tail_hor_)
	// 	return previous;
	//
	// auto next = previous;
	// auto after_next = previous;
	// ++next;
	// ++after_next;
	// ++after_next;
	//
	// join_ver_list(previous, after_next);
	// scrap_ver_list(next);
	//
	// set_size(width_ - 1, height_);
	//
	// return after_next;
}

template <typename T>
typename forked_linked_list<T>::v_iterator
forked_linked_list<T>::erase_hor_list(v_iterator previous)
{
	// if(previous == tail_var_)
	// 	return previous;
	//
	// auto next = previous;
	// auto after_next = previous;
	// ++next;
	// ++after_next;
	// ++after_next;
	//
	// join_hor_list(previous, after_next);
	// scrap_hor_list(next);
	//
	// set_size(width_, height_ - 1);
	//
	// return after_next;
}

template <typename T>
void forked_linked_list<T>::clear()
{
// 	while(head_.nodep() != nullptr)
// 	{
// 		pop_front_hor_list();
// 	}
//
	// set_size(0, 0);
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
typename forked_linked_list<T>::vh_iterator
forked_linked_list<T>::build(size_t width, size_t height, const T &def_val)
{
	if(width * height == 0)
		return std::move(vh_iterator());

	// create a base list
	auto origin = build_hor_list(width, def_val);

	auto itr = origin;
	for(size_t i = 1; i < height; ++i)
	{
		join_hor_list(itr, build_hor_list(width, def_val));

		// move to the node above
		itr.forward_var();
	}

	return std::move(origin);
}

template <typename T>
typename forked_linked_list<T>::vh_iterator
forked_linked_list<T>::build_ver_list(size_t height, const T &def_val)
{
	if(height == 0)
		return std::move(vh_iterator(nullptr, run_dir::kVertical));

	auto head = vh_iterator(new node(def_val), run_dir::kVertical);
	auto itr = head;
	for(size_t i = 1; i < height; ++i)
	{
		itr.nodep()->v_next = new node(def_val);
		++itr;
	}

	return head;
}

template <typename T>
typename forked_linked_list<T>::vh_iterator
forked_linked_list<T>::build_hor_list(size_t width, const T &def_val)
{
	if(width == 0)
		return std::move(vh_iterator(nullptr, run_dir::kHorizontal));

	auto head = vh_iterator(new node(def_val), run_dir::kHorizontal);
	auto itr = head;
	for(size_t i = 1; i < width; ++i)
	{
		itr.nodep()->h_next = new node(def_val);
		++itr;
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
typename forked_linked_list<T>::vh_iterator
forked_linked_list<T>::join_ver_list(vh_iterator left, vh_iterator right)
{
	assert(left != vhend());

	auto l_itr = left;
	{
	for(; left != vhend(); left.forward_var(), right.forward_var())
		left.nodep()->h_next = right.nodep();
	}

	return std::move(l_itr);
}

template <typename T>
typename forked_linked_list<T>::vh_iterator
forked_linked_list<T>::join_hor_list(vh_iterator below, vh_iterator above)
{
	assert(below != vhend());

	auto b_itr = below;
	for(; below != vhend(); below.forward_hor(), above.forward_hor())
	{
		below.nodep()->v_next = above.nodep();
	}

	return std::move(b_itr);
}

template <typename T>
void forked_linked_list<T>::scrap_ver_list(vh_iterator head)
{
	for(auto np = head.nodep(); np != nullptr; np = head.nodep())
	{
		head.forward_var();
		delete np;
	}
}

template <typename T>
void forked_linked_list<T>::scrap_hor_list(vh_iterator head)
{
	for(auto np = head.nodep(); np != nullptr; np = head.nodep())
	{
		head.forward_hor();
		delete np;
	}
}

template <typename T>
void forked_linked_list<T>::on_size_zero()
{
	head_ = tail_hor_ = tail_var_ = vhend();
}

template <typename T>
void forked_linked_list<T>::set_tails()
{
	if(head_ == vhend())
	{
		tail_var_ = tail_hor_ = vhend();
	}
	else
	{
		// find horizontal tail
		tail_hor_ = head_;
		for(; tail_hor_.nodep()->h_next != nullptr; tail_hor_.forward_hor());
		// find vertical tail
		tail_var_ = head_;
		for(; tail_var_.nodep()->v_next != nullptr; tail_var_.forward_var());
	}
}

} /* namespace dlib */
