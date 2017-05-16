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
:origin_(nullptr)
,width_(0)
,height_(0)
{}

template <typename T>
forked_linked_list<T>::forked_linked_list(size_t width, size_t height)
:origin_(nullptr)
,width_(width)
,height_(height)
{
	origin_ = build(width, height);
}

template <typename T>
forked_linked_list<T>::forked_linked_list(size_t width, size_t height, const T& def_val)
:origin_(nullptr)
,width_(width)
,height_(height)
{
	origin_ = build(width, height, def_val);
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
	if(height_ == 0)
		return;

	origin_ = join_ver_list(build_ver_list(height_, def_val), origin_);
	set_size(width_ + 1, height_);
}

template <typename T>
void forked_linked_list<T>::push_front_hor_list(const T &def_val)
{
	if(width_ == 0)
		return;

	origin_ = join_hor_list(build_hor_list(width_, def_val), origin_);
	set_size(width_, height_ + 1);
}

template <typename T>
typename forked_linked_list<T>::iterator
forked_linked_list<T>::insert_ver_list(iterator previous, const T &def_val)
{

}

template <typename T>
typename forked_linked_list<T>::iterator
forked_linked_list<T>::insert_hor_list(iterator previous, const T &def_val)
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
	if(origin_ != nullptr)
	{
		auto np = origin_->h_next;
		scrap_ver_list(origin_);
		origin_ = np;

		set_size(width_ - 1, height_);
	}
}

template <typename T>
void forked_linked_list<T>::pop_front_hor_list()
{
	if(origin_ != nullptr)
	{
		auto np = origin_->v_next;
		scrap_hor_list(origin_);
		origin_ = np;

		set_size(width_, height_ - 1);
	}
}

template <typename T>
typename forked_linked_list<T>::iterator
forked_linked_list<T>::erase_ver_list(iterator previous)
{

}

template <typename T>
typename forked_linked_list<T>::iterator
forked_linked_list<T>::erase_hor_list(iterator previous)
{

}

template <typename T>
void forked_linked_list<T>::clear()
{
	while(origin_ != nullptr)
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
	else if(origin_ == nullptr)
	{
		origin_ = build(width, height, def_val);
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

	auto v_np = origin;
	for(size_t i = 1; i < height; ++i)
	{
		join_hor_list(v_np, build_hor_list(width, def_val));

		// move to the node above
		v_np = v_np->v_next;
	}

	return origin;
}

template <typename T>
typename forked_linked_list<T>::node*
forked_linked_list<T>::build_ver_list(size_t height, const T &def_val)
{
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
forked_linked_list<T>::join_ver_list(node* left, node* right)
{
	for(auto l_itr = iterator(left, itr_dir::kVertical), r_itr = iterator(right, itr_dir::kVertical);
		l_itr != vend() && r_itr != vend();
		++l_itr, ++r_itr)
	{
		l_itr.nodep()->h_next = r_itr.nodep();
	}

	return left;
}

template <typename T>
typename forked_linked_list<T>::node*
forked_linked_list<T>::join_hor_list(node* below, node* above)
{
	for(auto b_itr = iterator(below, itr_dir::kHorizontal), a_itr = iterator(above, itr_dir::kHorizontal);
		b_itr != vend() && a_itr != vend();
		++b_itr, ++a_itr)
	{
		b_itr.nodep()->v_next = a_itr.nodep();
	}

	return below;
}

template <typename T>
void forked_linked_list<T>::scrap_ver_list(node *head)
{
	for(auto np = head; head != nullptr; np = head)
	{
		head = head->v_next;
		delete np;
	}
}

template <typename T>
void forked_linked_list<T>::scrap_hor_list(node *head)
{
	for(auto np = head; head != nullptr; np = head)
	{
		head = head->h_next;
		delete np;
	}
}

} /* namespace dlib */
