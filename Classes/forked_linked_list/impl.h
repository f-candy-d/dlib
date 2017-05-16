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

}

template <typename T>
void forked_linked_list<T>::push_front_hor_list(const T &def_val)
{

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

}

template <typename T>
void forked_linked_list<T>::pop_front_hor_list()
{

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
	origin_ = nullptr;
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
		auto h_np = v_np;
		auto h_np2 = build_hor_list(width, def_val);

		for(size_t j = 0; j < width; ++j)
		{
			h_np->v_next = h_np2;
			// move to the right node
			h_np = h_np->h_next;
			h_np2 = h_np2->h_next;
		}

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

} /* namespace dlib */
