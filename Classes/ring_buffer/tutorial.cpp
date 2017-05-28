#include <iostream>
#include <iomanip>
#include <memory>
#include "ring_buffer.h"

template <typename T>
void log_buffer(const dlib::ring_buffer<T> buffer)
{
	std::cout << "--------------------------------------------" << '\n';
	std::cout << "size() = " << buffer.size() << '\n';
	std::cout << "capacity() = " << buffer.capacity() << '\n';
	std::cout << "indx => ";
	for(size_t i = 0; i < buffer.capacity() + 1; ++i)
	{
			std::cout << std::setfill('_') << std::setw(3) << i << "|";
	}
	std::cout << "\ndata => ";
	for(auto itr = buffer.begin(); itr != buffer.end(); ++itr)
	{
		std::cout << std::setfill('_') << std::setw(3) << *itr << "|";
	}
	std::cout << "\nreal => ";
	// for(size_t i = 0; i < buffer.gross_capacity_; ++i)
	for(auto itr = buffer.begin_strage(); itr != buffer.end_strage(); ++itr)
	{
		std::cout << std::setfill('_') << std::setw(3) << *itr << "|";
	}

	std::cout << "\n\nfront => " << buffer.front() << "\nback => " << buffer.back() << '\n';

	std::cout << "--------------------------------------------" << '\n';
}

int main(int argc, char const *argv[])
{
	dlib::ring_buffer<int> buffer(0, 7, 0);
	std::cout << " # create a ring-buffer => dlib::ring_buffer<int> buffer(0, 7, 0)" << '\n';
	log_buffer<int>(buffer);

	std::cout << "push back x 7" << '\n';
	buffer.push_back(1);
	buffer.push_back(2);
	buffer.push_back(3);
	buffer.push_back(4);
	buffer.push_back(5);
	buffer.push_back(6);
	buffer.push_back(7);
	log_buffer<int>(buffer);

	std::cout << "push back x 3" << '\n';
	buffer.push_back(8);
	buffer.push_back(9);
	buffer.push_back(10);
	log_buffer<int>(buffer);

	std::cout << "push front x2" << '\n';
	buffer.push_front(11);
	buffer.push_front(12);
	log_buffer<int>(buffer);

	std::cout << "pop back x2" << '\n';
	buffer.pop_back();
	buffer.pop_back();
	log_buffer<int>(buffer);

	std::cout << "pop front x 1" << '\n';
	buffer.pop_front();
	log_buffer<int>(buffer);

	std::cout << "copy..." << '\n';
	auto buffer2 = buffer;

	std::cout << "expand capacity" << '\n';
	buffer.expand_capacity(14, 777);
	log_buffer<int>(buffer);

	std::cout << "shrink capacity" << '\n';
	buffer.shrink_capacity(3, 777);
	log_buffer<int>(buffer);

	std::cout << "clear" << '\n';
	buffer.clear();
	log_buffer<int>(buffer);

	std::cout << "copied buffer..." << '\n';
	log_buffer<int>(buffer2);

	dlib::ring_buffer<int> buffer(); // <- default, size() and capacity() is 0
	dlib::ring_buffer<int> buffer2(10, 6); // <- size() is 10, capacity() is 15
	dlib::ring_buffer<int> buffer3(10, 16, 6); // <- size() is 10, capacity() is 31
	dlib::ring_buffer<int> buffer4(buffer); // <- copy constructor

	buffer2.push_front(10); // <- append '10' to the front of the buffer
	buffer2.push_back(10); // <- append '10' to the back of the buffer

	int x = buffer2.front(); // <- get the first element of the buffer
	int y = buffer2[0]; // <- this is same as 'buffer.front()'

	buffer2.pop_front(); // <- remove the first element of the buffer
	buffer2.pop_back(); // <- remove the last element of the buffer

	buffer2.expand_capacity(buffer.capacity() * 2); // <- size() is 10, capacity() is 31
	buffer2.shrink_capacity(5); // <- size() is 7, capacity() is 7

	buffer2.clear(); // <- size() is 0, capacity() is 7

	// navigate through a ring-buffer from front to back using iterators
	for(auto itr = buffer2.begin(); itr != buffer2.end(); ++itr)
	{
		std::cout << "data -> " << *itr << '\n';
	}

	return 0;
}
