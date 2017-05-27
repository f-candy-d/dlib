#include <iostream>
#include <iomanip>
#include "ring_buffer.h"

template <typename T>
void log_buffer(const dlib::ring_buffer<T> buffer)
{
	std::cout << "----------------------------------" << '\n';
	std::cout << "size() = " << buffer.size() << '\n';
	std::cout << "capacity() = " << buffer.capacity() << '\n';
	std::cout << "indx => ";
	for(size_t i = 0; i < buffer.size(); ++i)
		std::cout << std::setfill('_') << std::setw(3) << i << "|";
	std::cout << "\ndata => ";
	for(size_t i = 0; i < buffer.size(); ++i)
		std::cout << std::setfill('_') << std::setw(3) << buffer[i] << "|";
	std::cout << "\n----------------------------------" << '\n';
}

int main(int argc, char const *argv[])
{
	dlib::ring_buffer<int> buffer(0, 7, 0);
	log_buffer<int>(buffer);

	buffer.push_back(1);
	buffer.push_back(2);
	buffer.push_back(3);
	buffer.push_back(4);
	buffer.push_back(5);
	buffer.push_back(6);
	buffer.push_back(7);
	log_buffer(buffer);
	std::cout << "front => " << buffer.front() << '\n';
	std::cout << "back => " << buffer.back() << '\n';

	buffer.push_back(8);
	log_buffer(buffer);
	std::cout << "front => " << buffer.front() << '\n';
	std::cout << "back => " << buffer.back() << '\n';

	buffer.push_back(9);
	log_buffer(buffer);
	std::cout << "front => " << buffer.front() << '\n';
	std::cout << "back => " << buffer.back() << '\n';

	buffer.push_front(10);
	log_buffer(buffer);
	std::cout << "front => " << buffer.front() << '\n';
	std::cout << "back => " << buffer.back() << '\n';

	buffer.push_front(11);
	buffer.push_front(12);
	log_buffer(buffer);
	std::cout << "front => " << buffer.front() << '\n';
	std::cout << "back => " << buffer.back() << '\n';

	buffer.pop_back();
	buffer.pop_back();
	buffer.pop_front();
	log_buffer(buffer);
	std::cout << "front => " << buffer.front() << '\n';
	std::cout << "back => " << buffer.back() << '\n';

	buffer.change_capacity(15, 0);
	log_buffer(buffer);
	std::cout << "front => " << buffer.front() << '\n';
	std::cout << "back => " << buffer.back() << '\n';

	buffer.clear();
	log_buffer(buffer);
	std::cout << "front => " << buffer.front() << '\n';
	std::cout << "back => " << buffer.back() << '\n';

	buffer.free_memory();
	log_buffer(buffer);
	std::cout << "front => " << buffer.front() << '\n';
	std::cout << "back => " << buffer.back() << '\n';

	return 0;
}
