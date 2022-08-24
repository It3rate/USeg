
#include <iostream>
#include <cstring>

#include "Segment.h"

int main(int argc, char* argv[]) 
{
	std::cout << "hello\n";

	const umath::Segment seg0(10.3,20.0);
	std::cout << "start = " << seg0.i_start_ << "\n";
	std::cout << "end = " << seg0.r_end_ << "\n";

    return 0;
}