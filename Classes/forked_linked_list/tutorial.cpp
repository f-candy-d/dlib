#include <iostream>
#include "forked_linked_list.h"

int main(int argc, char const *argv[])
{
	dlib::forked_linked_list<int> list(5, 5, 5);

	std::cout << "[ forked-linked-list tutorial ]" << '\n';
	std::cout << "size = " << list.size() << '\n';

	// for(auto v_itr = list.vbegin(); v_itr != list.vend(); ++v_itr)
	// {
	// 	auto h_itr = list.hbegin();
	// 	*h_itr = *v_itr;
	// 	for(; h_itr != list.hend(); ++h_itr)
	// 	{
	// 		std::cout << *h_itr << ", ";
	// 	}
	// 	std::cout << '\n';
	// }
	// std::cout << '\n';

	int c = 10;
	for(auto v_itr = list.vhbegin(); v_itr != list.vhend(); v_itr.forward_var())
	{
		for(auto h_itr = v_itr; h_itr != list.vhend(); h_itr.forward_hor())
		{
			*h_itr = c;
			++c;
		}
	}

	for(auto v_itr = list.vhbegin(); v_itr != list.vhend(); v_itr.forward_var())
	{
		for(auto h_itr = v_itr; h_itr != list.vhend(); h_itr.forward_hor())
		{
			std::cout << *h_itr << ", ";
		}
		std::cout << '\n';
	}

	list.push_front_ver_list(99);
	list.push_front_hor_list(77);

	std::cout << "push front ver/hor list" << '\n';

	for(auto v_itr = list.vhbegin(); v_itr != list.vhend(); v_itr.forward_var())
	{
		for(auto h_itr = v_itr; h_itr != list.vhend(); h_itr.forward_hor())
		{
			std::cout << *h_itr << ", ";
		}
		std::cout << '\n';
	}

	std::cout << "size = " << list.size() << '\n';

	list.pop_front_hor_list();
	list.pop_front_ver_list();

	std::cout << "pop front ver/hor list" << '\n';

	for(auto v_itr = list.vhbegin(); v_itr != list.vhend(); v_itr.forward_var())
	{
		for(auto h_itr = v_itr; h_itr != list.vhend(); h_itr.forward_hor())
		{
			std::cout << *h_itr << ", ";
		}
		std::cout << '\n';
	}

	std::cout << "size = " << list.size() << '\n';

	std::cout << "clear!" << '\n';
	list.clear();

	for(auto v_itr = list.vhbegin(); v_itr != list.vhend(); v_itr.forward_var())
	{
		for(auto h_itr = v_itr; h_itr != list.vhend(); h_itr.forward_hor())
		{
			std::cout << *h_itr << ", ";
		}
		std::cout << '\n';
	}

	std::cout << "size = " << list.size() << " | width = " << list.width() << " | height = " << list.height() << '\n';
	std::cout << "add 3 lines" << '\n';

	list.push_front_hor_list(11);
	list.push_front_hor_list(22);
	list.push_front_hor_list(33);

	for(auto v_itr = list.vhbegin(); v_itr != list.vhend(); v_itr.forward_var())
	{
		for(auto h_itr = v_itr; h_itr != list.vhend(); h_itr.forward_hor())
		{
			std::cout << *h_itr << ", ";
		}
		std::cout << '\n';
	}

	std::cout << "size = " << list.size() << " | width = " << list.width() << " | height = " << list.height() << '\n';

	std::cout << "pop front ver list" << '\n';
	list.pop_front_ver_list();

	for(auto v_itr = list.vhbegin(); v_itr != list.vhend(); v_itr.forward_var())
	{
		for(auto h_itr = v_itr; h_itr != list.vhend(); h_itr.forward_hor())
		{
			std::cout << *h_itr << ", ";
		}
		std::cout << '\n';
	}

	std::cout << "size = " << list.size() << " | width = " << list.width() << " | height = " << list.height() << '\n';

	dlib::forked_linked_list<int> list2;
	list2.resize(5, 5, 11);

	std::cout << "list22" << '\n';
	for(auto v_itr = list2.vhbegin(); v_itr != list2.vhend(); v_itr.forward_var())
	{
		for(auto h_itr = v_itr; h_itr != list2.vhend(); h_itr.forward_hor())
		{
			std::cout << *h_itr << ", ";
		}
		std::cout << '\n';
	}

	std::cout << "size = " << list2.size() << " | width = " << list2.width() << " | height = " << list2.height() << '\n';

	return 0;
}
