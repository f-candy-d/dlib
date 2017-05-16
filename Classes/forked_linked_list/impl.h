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
{}

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

}

template <typename T>
void forked_linked_list<T>::resize(size_t width, size_t height)
{

}

} /* namespace dlib */
