/**********************************************************************************
 *
 * Node class of forked_linked_list. May/19/2017
 *
 **********************************************************************************/
#ifndef DLIB_CLASSES_FORKED_LINKED_LIST_NODE_H
#define DLIB_CLASSES_FORKED_LINKED_LIST_NODE_H

namespace dlib
{
namespace forked_linked_list_bits
{

template <typename T> struct node
{
	T value;
	struct node* v_next;
	struct node* h_next;

	node() :value(),v_next(nullptr),h_next(nullptr) {}
	node(const T& val, struct node* vnxt = nullptr, struct node* hnxt = nullptr)
	:value(val),v_next(vnxt),h_next(hnxt) {}
};

} /* namespace forked_linked_list_bits */
} /* namespace dlib */

#endif
