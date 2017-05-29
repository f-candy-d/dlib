#include <iostream>
#include "normarized_int.h"

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

	// get a value
	std::cout << "value -> " << *norm_int << '\n';

	return 0;
}
