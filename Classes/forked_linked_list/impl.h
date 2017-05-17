/**********************************************************************************
 *
 * The implementation file of forked_linked_list class.
 *
 **********************************************************************************/
#include "forked_linked_list.h"

namespace dlib
{

template <typename T>
forked_linked_list<T>::forked_linked_list()
:head_(nullptr)
,tail_var_(nullptr)
,tail_hor_(nullptr)
,width_(0)
,height_(0)
{}

template <typename T>
forked_linked_list<T>::forked_linked_list(size_t width, size_t height)
:head_(nullptr)
,tail_var_(nullptr)
,tail_hor_(nullptr)
,width_(width)
,height_(height)
{
	head_ = build(width, height);
}

template <typename T>
forked_linked_list<T>::forked_linked_list(size_t width, size_t height, const T& def_val)
:head_(nullptr)
,tail_var_(nullptr)
,tail_hor_(nullptr)
,width_(width)
,height_(height)
{
	head_ = build(width, height, def_val);
}

template <typename T>
void forked_linked_list<T>::push_back_ver_list(const T &def_val)
{

}

template <typename T>
void forked_linked_list<T>::push_back_hor_list(const T &def_val)
{

}

template <typename T>
void forked_linked_list<T>::push_front_ver_list(const T &def_val)
{
	head_ = join_ver_list(h_iterator(build_ver_list(height_, def_val)), h_iterator(head_));
	if(head_ != nullptr)
	{
		set_size(width_ + 1, height_);
	}
}

template <typename T>
void forked_linked_list<T>::push_front_hor_list(const T &def_val)
{
	head_ = join_hor_list(v_iterator(build_hor_list(width_, def_val)), v_iterator(head_));
	if(head_ != nullptr)
	{
		set_size(width_, height_ + 1);
	}
}

template <typename T>
typename forked_linked_list<T>::h_iterator
forked_linked_list<T>::insert_ver_list(h_iterator previous, const T &def_val)
{

}

template <typename T>
typename forked_linked_list<T>::v_iterator
forked_linked_list<T>::insert_hor_list(v_iterator previous, const T &def_val)
{

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
	if(head_ != nullptr)
	{
		auto np = head_->h_next;
		scrap_ver_list(vh_iterator(head_, run_dir::kVertical));
		head_ = np;

		set_size(width_ - 1, height_);
	}
}

template <typename T>
void forked_linked_list<T>::pop_front_hor_list()
{
	if(head_ != nullptr)
	{
		auto np = head_->v_next;
		scrap_hor_list(vh_iterator(head_, run_dir::kVertical));
		head_ = np;

		set_size(width_, height_ - 1);
	}
}

template <typename T>
typename forked_linked_list<T>::h_iterator
forked_linked_list<T>::erase_ver_list(h_iterator previous)
{

}

template <typename T>
typename forked_linked_list<T>::v_iterator
forked_linked_list<T>::erase_hor_list(v_iterator previous)
{

}

template <typename T>
void forked_linked_list<T>::clear()
{
	while(head_ != nullptr)
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
	else if(head_ == nullptr)
	{
		head_ = build(width, height, def_val);
	}
	else
	{
		// resize width
		auto diff_w = width - width_;

		if(0 < diff_w)
		{
			for(size_t i = 0; i < diff_w; ++i)
			{
				push_back_ver_list(def_val);
			}
		}
		else if(diff_w < 0)
		{
			for(size_t i = 0; i < diff_w * -1; ++i)
			{
				pop_back_ver_list();
			}
		}

		// resize height
		auto diff_h = height - height_;

		if(0 < diff_h)
		{
			for(size_t i = 0; i < diff_h; ++i)
			{
				push_back_hor_list(def_val);
			}
		}
		else if(diff_h < 0)
		{
			for(size_t i = 0; i < diff_h * -1; ++i)
			{
				pop_back_hor_list();
			}
		}
	}

	set_size(width, height);
}

template <typename T>
typename forked_linked_list<T>::node*
forked_linked_list<T>::build(size_t width, size_t height, const T &def_val)
{
	if(width * height == 0)
		return nullptr;

	// create a base list
	auto origin = build_hor_list(width, def_val);

	auto v_itr = v_iterator(origin);
	for(size_t i = 1; i < height; ++i)
	{
		join_hor_list(v_itr, v_iterator(build_hor_list(width, def_val)));

		// move to the node above
		++v_itr;
	}

	return origin;
}

template <typename T>
typename forked_linked_list<T>::node*
forked_linked_list<T>::build_ver_list(size_t height, const T &def_val)
{
	if(height == 0)
		return nullptr;

	auto head = new node(def_val);
	auto np = head;
	for(size_t i = 1; i < height; ++i)
	{
		np->v_next = new node(def_val);
		np = np->v_next;
	}

	return head;
}

template <typename T>
typename forked_linked_list<T>::node*
forked_linked_list<T>::build_hor_list(size_t width, const T &def_val)
{
	if(width == 0)
		return nullptr;

	auto head = new node(def_val);
	auto np = head;
	for(size_t i = 1; i < width; ++i)
	{
		np->h_next = new node(def_val);
		np = np->h_next;
	}

	return head;
}

template <typename T>
void forked_linked_list<T>::set_size(size_t width, size_t height)
{
	width_ = width;
	height_ = height;
}

template <typename T>
typename forked_linked_list<T>::node*
forked_linked_list<T>::join_ver_list(vh_iterator left, vh_iterator right)
{
	auto l_itr = left;
	for(; left != vend() && right != vend(); left.forward_var(), right.forward_var())
	{
		left.nodep()->h_next = right.nodep();
	}

	return l_itr.nodep();
}

template <typename T>
typename forked_linked_list<T>::node*
forked_linked_list<T>::join_hor_list(vh_iterator below, vh_iterator above)
{
	auto b_itr = below;
	for(; below != hend() && above != hend(); below.forward_hor(), above.forward_hor())
	{
		below.nodep()->v_next = above.nodep();
	}

	return b_itr.nodep();
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

} /* namespace dlib */
