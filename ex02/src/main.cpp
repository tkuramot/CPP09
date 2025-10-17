#include "PMergeMe.hpp"
#include <iostream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <iomanip>
#include <sys/time.h>

static int parsePositiveInt(const std::string& str) {
	if (str.empty()) {
		throw std::runtime_error("Error");
	}

	for (size_t i = 0; i < str.length(); ++i) {
		if (!std::isdigit(str[i])) {
			throw std::runtime_error("Error");
		}
	}

	std::istringstream iss(str);
	long num;
	iss >> num;

	if (iss.fail() || num < 0 || num > std::numeric_limits<int>::max()) {
		throw std::runtime_error("Error");
	}

	return static_cast<int>(num);
}

static void parseArguments(int argc, char **argv,
                           std::vector<int>& vec,
                           std::deque<int>& deq) {
	if (argc < 2) {
		throw std::runtime_error("Error: No arguments provided");
	}

	for (int i = 1; i < argc; ++i) {
		int num = parsePositiveInt(argv[i]);
		vec.push_back(num);
		deq.push_back(num);
	}
}

static void displaySequence(const std::string& prefix, const std::vector<int>& container) {
	std::cout << prefix;

	size_t size = container.size();

	for (size_t i = 0; i < size; ++i) {
		std::cout << container[i];
		if (i + 1 < size) {
			std::cout << " ";
		}
	}

	std::cout << std::endl;
}

static void displayTime(const std::string& containerName, size_t size, double microseconds) {
	std::cout << "Time to process a range of " << size
	          << " elements with " << containerName << " : "
	          << std::fixed << std::setprecision(5) << microseconds << " us"
	          << std::endl;
}

static double getTimeDifference(struct timeval start, struct timeval end) {
	return (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
}

int main(int argc, char **argv) {
	try {
		std::vector<int> vec;
		std::deque<int> deq;

		parseArguments(argc, argv, vec, deq);

		std::vector<int> original = vec;

		displaySequence("Before: ", original);

		struct timeval start_vec, end_vec;
		gettimeofday(&start_vec, NULL);
		PMergeMe::sort(vec.begin(), vec.end());
		gettimeofday(&end_vec, NULL);
		double time_vec = getTimeDifference(start_vec, end_vec);

		struct timeval start_deq, end_deq;
		gettimeofday(&start_deq, NULL);
		PMergeMe::sort(deq.begin(), deq.end());
		gettimeofday(&end_deq, NULL);
		double time_deq = getTimeDifference(start_deq, end_deq);

		displaySequence("After:  ", vec);
		displayTime("std::vector", vec.size(), time_vec);
		displayTime("std::deque", deq.size(), time_deq);

	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
