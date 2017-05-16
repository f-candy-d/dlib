#include <iostream>
#include "forked_linked_list.h"

int main(int argc, char const *argv[])
{
	dlib::forked_linked_list<int> fl_list(5, 5, 5);

	std::cout << "[ forked-linked-list tutorial ]" << '\n';
	std::cout << "size = " << fl_list.size() << '\n';

	// for(auto v_itr = fl_list.vbegin(); v_itr != fl_list.vend(); ++v_itr)
	// {
	// 	auto h_itr = fl_list.hbegin();
	// 	*h_itr = *v_itr;
	// 	for(; h_itr != fl_list.hend(); ++h_itr)
	// 	{
	// 		std::cout << *h_itr << ", ";
	// 	}
	// 	std::cout << '\n';
	// }
	// std::cout << '\n';

	int c = 10;
	for(auto v_itr = fl_list.begin(); v_itr != fl_list.end(); v_itr.forward_var())
	{
		for(auto h_itr = v_itr; h_itr != fl_list.end(); h_itr.forward_hor())
		{
			*h_itr = c;
			++c;
		}
	}

	for(auto v_itr = fl_list.begin(); v_itr != fl_list.end(); v_itr.forward_var())
	{
		for(auto h_itr = v_itr; h_itr != fl_list.end(); h_itr.forward_hor())
		{
			std::cout << *h_itr << ", ";
		}
		std::cout << '\n';
	}

	return 0;
}
