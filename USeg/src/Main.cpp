
#include <iostream>
#include <cstring>

#include "Segment.h"

int main(int argc, char* argv[])
{
	std::cout << "hello\n";

	const UMath::Segment seg0(10.3,20.0);
	std::cout << "start = " << seg0.m_start << "\n";
	std::cout << "end = " << seg0.m_end << "\n";

    return 0;
}