#include "PMergeMe.hpp"
#include <iostream>

int main(int argc, char **argv) {
	try {
		PMergeMe sorter(argc, argv);
		sorter.sortAndDisplay();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
