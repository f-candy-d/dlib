#include <iostream>
#include "forked_linked_list.h"
#include "node_cursor.h"

template <typename T>
void print_list(dlib::forked_linked_list<T>& list)
{
	std::cout << '\n' << "[ forked-linked-list log  | size = " << list.size() << " (" << list.width() << "x" << list.height() << ") | capacity = " << list.capaicty() << " (" << list.capacity_width() << "x" << list.capacity_height() << ") ]" << '\n';
	for(auto v_itr = list.vhbegin(); v_itr != list.vhend(); v_itr.forward_ver())
	{
		for(auto h_itr = v_itr; h_itr != list.vhend(); h_itr.forward_hor())
		{
			std::cout << *h_itr << ", ";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

int main(int argc, char const *argv[])
{
	std::cout << "[ forked-linked-list tutorial ]" << "\n\n";

	dlib::forked_linked_list<char> list(5, 5, 'D');

	std::cout << "# list => dlib::forked_linked_list<char> list(5, 5, 'D')" << '\n';
	print_list<char>(list);

	std::cout << "# change values..." << '\n';

	char c = 'a';
	for(auto v_itr = list.vhbegin(); v_itr != list.vhend(); v_itr.forward_ver())
	{
		for(auto h_itr = v_itr; h_itr != list.vhend(); h_itr.forward_hor())
		{
			*h_itr = c;
			++c;
		}
	}

	print_list(list);

	// push back
	std::cout << "# push_back_ver_list('A')" << '\n';
	list.push_back_ver_list('A');
	print_list(list);
	std::cout << "# push_back_hor_list('B')" << '\n';
	list.push_back_hor_list('B');
	print_list(list);

	// push front
	std::cout << "# push_front_ver_list('C')" << '\n';
	list.push_front_ver_list('C');
	print_list(list);
	std::cout << "# push_front_hor_list('D')" << '\n';
	list.push_front_hor_list('D');
	print_list(list);

	// insert
	std::cout << "# insert_ver_list(++(list.hbegin()), 'E')" << '\n';
	list.insert_ver_list(++(list.hbegin()), 'E');
	print_list(list);
	std::cout << "# insert_hor_list(++(list.vbegin()), 'F')" << '\n';
	list.insert_hor_list(++(list.vbegin()), 'F');
	print_list(list);

	// // pop back
	std::cout << "# pop_back_ver_list()" << '\n';
	list.pop_back_ver_list();
	print_list(list);
	std::cout << "# pop_back_hor_list()" << '\n';
	list.pop_back_hor_list();
	print_list(list);

	// pop front
	std::cout << "# pop_front_ver_list()" << '\n';
	list.pop_front_ver_list();
	print_list(list);
	std::cout << "# pop_front_hor_list()" << '\n';
	list.pop_front_hor_list();
	print_list(list);

	// erase
	std::cout << "# erase_ver_list(++list.hbegin())" << '\n';
	list.erase_ver_list(++list.hbegin());
	print_list(list);
	std::cout << "# erase_hor_list(++list.vbegin())" << '\n';
	list.erase_hor_list(++list.vbegin());
	print_list(list);

	// clear
	std::cout << "# clear()" << '\n';
	list.clear();
	print_list(list);

	// push back again
	std::cout << "# push_back_ver_list('G')" << '\n';
	list.push_back_ver_list('G');
	print_list(list);

	// push front again
	std::cout << "# push_front_ver_list('H')" << '\n';
	std::cout << "# push_front_hor_list('I')" << '\n';
	list.push_front_ver_list('H');
	list.push_front_hor_list('I');
	print_list(list);

	// resize( to bigger size)
	std::cout << "# resize(10, 15, n)" << '\n';
	list.resize(10, 15, 'n');
	print_list(list);

	// resize( to smaller size)
	std::cout << "# resize(1, 5)" << '\n';
	list.resize(1, 5);
	print_list(list);

	// clear
	std::cout << "# clear()" << '\n';
	list.clear();
	print_list(list);

	return 0;
}
