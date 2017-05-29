#include <iostream>
#include "normarized_uint.h"

int main(int argc, char const *argv[])
{
	dlib::normarized_uint nn(1, 10, 3);
	for(size_t i = 0; i < 20; ++i)
	{
		std::cout << "n = " << *(nn + i) << '\n';
		// ++nn;
		// nn.forward(2);
	}

	std::cout << "nn.begin = " << nn.begin() << '\n';
	std::cout << "nn.end = " << nn.end() << '\n';
	std::cout << "nn.length = " << nn.length() << '\n';

	nn.reset(5, 2, 6);
	for(size_t i = 0; i < 20; ++i)
	{
		std::cout << "n = " << *(nn + i) << '\n';
		// ++nn;
		// nn.forward(2);
	}

	std::cout << "nn.begin = " << nn.begin() << '\n';
	std::cout << "nn.end = " << nn.end() << '\n';
	std::cout << "nn.length = " << nn.length() << '\n';

	return 0;
}
