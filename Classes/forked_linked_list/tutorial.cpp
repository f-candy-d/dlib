#include <iostream>
#include "forked_linked_list.h"

template <typename T>
void print_list(dlib::forked_linked_list<T>& list)
{
	std::cout << '\n' << "[ list log ]" << '\n';
	for(auto v_itr = list.vhbegin(); v_itr != list.vhend(); v_itr.forward_var())
	{
		for(auto h_itr = v_itr; h_itr != list.vhend(); h_itr.forward_hor())
		{
			std::cout << *h_itr << ", ";
		}
		std::cout << '\n';
	}

	std::cout << "# size = " << list.size() << " | capacity = " << list.capaicty() << '\n';

	std::cout << '\n';
}

int main(int argc, char const *argv[])
{
	std::cout << "[ forked-linked-list tutorial ]" << "\n\n";

	dlib::forked_linked_list<int> list(5, 5, 5);

	std::cout << "# list => dlib::forked_linked_list<int> list(5, 5, 5);" << '\n';
	print_list<int>(list);

	int c = 10;
	for(auto v_itr = list.vhbegin(); v_itr != list.vhend(); v_itr.forward_var())
	{
		for(auto h_itr = v_itr; h_itr != list.vhend(); h_itr.forward_hor())
		{
			*h_itr = c;
			++c;
		}
	}

	print_list(list);

	// push back
	std::cout << "# push_back_ver_list(22)" << '\n';
	std::cout << "# push_back_hor_list(33)" << '\n';
	list.push_back_ver_list(22);
	list.push_back_hor_list(33);
	print_list(list);

	// push front
	std::cout << "# push_front_ver_list(44)" << '\n';
	std::cout << "# push_front_hor_list(55)" << '\n';
	list.push_front_ver_list(44);
	list.push_front_hor_list(55);
	print_list(list);

	// insert
	std::cout << "# insert_ver_list(++(list.hbegin()), 66)" << '\n';
	std::cout << "# insert_hor_list(++(list.vbegin()), 77)" << '\n';
	list.insert_ver_list(++(list.hbegin()), 66);
	list.insert_hor_list(++(list.vbegin()), 77);
	print_list(list);

	// // pop back
	// std::cout << "# pop_back_ver_list()" << '\n';
	// std::cout << "# pop_back_hor_list() x2" << '\n';
	// list.pop_back_ver_list();
	// list.pop_back_hor_list();
	// list.pop_back_hor_list();
	// print_list(list);

	// pop front
	std::cout << "# pop_front_ver_list() x2" << '\n';
	std::cout << "# pop_front_hor_list()" << '\n';
	list.pop_front_ver_list();
	list.pop_front_ver_list();
	list.pop_front_hor_list();
	print_list(list);

	/**
	 * list2
	 */
	dlib::forked_linked_list<int> list2;
	std::cout << "# list2 => dlib::forked_linked_list<int> list2;" << '\n';
	print_list(list2);

	// push back
	std::cout << "# push_back_ver_list(22)" << '\n';
	std::cout << "# push_back_hor_list(33)" << '\n';
	list2.push_back_ver_list(22);
	list2.push_back_hor_list(33);

	// push front
	std::cout << "# push_front_ver_list(44)" << '\n';
	std::cout << "# push_front_hor_list(55)" << '\n';
	list2.push_front_ver_list(44);
	list2.push_front_hor_list(55);

	// insert
	std::cout << "# insert_ver_list(++(list2.hbegin()), 66)" << '\n';
	std::cout << "# insert_hor_list(++(list2.vbegin()), 77)" << '\n';
	list2.insert_ver_list(++(list2.hbegin()), 66);
	list2.insert_hor_list(++(list2.vbegin()), 77);

	// // pop back
	// std::cout << "# pop_back_ver_list()" << '\n';
	// std::cout << "# pop_back_hor_list() x2" << '\n';
	// list2.pop_back_ver_list();
	// list2.pop_back_hor_list();
	// list2.pop_back_hor_list();

	// pop front
	std::cout << "# pop_front_ver_list() x2" << '\n';
	std::cout << "# pop_front_hor_list()" << '\n';
	list2.pop_front_ver_list();
	list2.pop_front_ver_list();
	list2.pop_front_hor_list();

	print_list(list2);

	return 0;
}
