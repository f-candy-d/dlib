#include <ctime>
#include <iostream>
#include "normarized_int.h"
#include "normarized_int_optimized_pow2.h"

void time_test()
{
	clock_t start, end;
	int loop = 10000000;
	dlib::normarized_int norm_int(1, 1024);
	dlib::normarized_int_optimized_pow2 norm_int_p2(1, 1024);

	std::cout << "forward..." << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		norm_int += 1;
	}
	end = clock();
	std::cout << "operator+=() norm_int    :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		++norm_int;
	}
	end = clock();
	std::cout << "operator++() norm_int    :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		norm_int.fast_incr();
	}
	end = clock();
	std::cout << "fast_incr()  norm_int    :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		norm_int.forward(1);
	}
	end = clock();
	std::cout << "forward(1)   norm_int    :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		norm_int_p2 += 1;
	}
	end = clock();
	std::cout << "operator+=() norm_int_p2 :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		++norm_int_p2;
	}
	end = clock();
	std::cout << "operator++() norm_int_p2 :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		norm_int_p2.fast_incr();
	}
	end = clock();
	std::cout << "fast_incr()  norm_int_p2 :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		norm_int_p2.forward(1);
	}
	end = clock();
	std::cout << "forward(1)   norm_int_p2 :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0, offset = 0, length = 1024; i < loop; ++i)
	{
		offset = (offset + 1)&(length - 1);
	}
	end = clock();
	std::cout << "(i + 1) & (length - 1)   :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	std::cout << "\nbackforawd..." << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		norm_int -= 1;
	}
	end = clock();
	std::cout << "operator-=() norm_int    :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		--norm_int;
	}
	end = clock();
	std::cout << "operator--() norm_int    :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		norm_int.fast_decr();
	}
	end = clock();
	std::cout << "fast_decr()  norm_int    :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		norm_int_p2 -= 1;
	}
	end = clock();
	std::cout << "operator-=() norm_int_p2 :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		--norm_int_p2;
	}
	end = clock();
	std::cout << "operator--() norm_int_p2 :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0; i < loop; ++i)
	{
		norm_int_p2.fast_decr();
	}
	end = clock();
	std::cout << "fast_decr()  norm_int_p2 :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';

	start = clock();
	for(int i = 0, offset = 0, length = 1024; i < loop; ++i)
	{
		offset = (offset + 1)&(length - 1);
	}
	end = clock();
	std::cout << "(i + 1) & (length - 1)   :: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';
}

int main(int argc, char const *argv[])
{
	dlib::normarized_int norm_int_1; // <- default. loop through numbers [0,1) , *norm_int is 0
	dlib::normarized_int norm_int_2(5, 5); // <- loop thgough numbers [5, 10) , *norm_int is 5
	dlib::normarized_int norm_int(5, 5, 9); // <- loop thgough numbers [5, 10) , *norm_int is 9

	// forward...
	++norm_int; // <- *norm_int is 5
	norm_int.advance(7); // <- *norm_int is 7
	norm_int += 3; // <- *norm_int is 5

	// backward...
	--norm_int; // <- *norm_int is 9
	norm_int.advance(-4); // <- *norm_int is 5
	norm_int -= 6; // <- *norm_int is 9

	// get a value...
	std::cout << "value -> " << *norm_int << '\n';

	dlib::normarized_int_optimized_pow2 norm_int_op_1; // <- default. loop through numbers [0,1) , *norm_int is 0
	dlib::normarized_int_optimized_pow2 norm_int_op_2(5, 4); // <- loop thgough numbers [5, 10) , *norm_int is 5
	dlib::normarized_int_optimized_pow2 norm_int_op(5, 4, 6); // <- loop thgough numbers [5, 10) , *norm_int is 9

	// forward...
	++norm_int_op; // <- *norm_int is 5
	norm_int_op.advance(7); // <- *norm_int is 7
	norm_int_op += 3; // <- *norm_int is 5

	// backward...
	--norm_int_op; // <- *norm_int is 9
	norm_int_op.advance(-4); // <- *norm_int is 5
	norm_int_op -= 6; // <- *norm_int is 9

	// get a value...
	std::cout << "value -> " << *norm_int_op << '\n';

	// time_test();

	return 0;
}
