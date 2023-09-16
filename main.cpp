#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>

#include "array.hpp"
#include "search.hpp"
#include "sorts.hpp"


int main() {
	namespace chrono = std::chrono;

	std::srand(chrono::steady_clock::now().time_since_epoch().count());
	Array<u16> arr = {
		.data = (u16*)malloc(20 * sizeof(u16)),
		.size = 20,
	};

	std::cout << "Shell sort:\n\n";

	fill(arr);
	std::cout << "Unsorted:\n";
	print(arr);

	shell_sort(arr);

	if (!is_sorted(arr)) {
		std::cout << "Error in sorting!\n";
		return 1;
	}

	std::cout << "Sorted:\n";
	print(arr);
	std::cout << "\n";

	std::cout << "Benchmark:\n";
	benchmark(10000000, 10, shell_sort);
	std::cout << "\n\n";


	std::cout << "Reverse selection sort:\n\n";

	fill(arr);
	std::cout << "Unsorted:\n";
	print(arr);

	selection_sort_reverse(arr);

	if (!is_sorted_reverse(arr)) {
		std::cout << "Error in sorting!\n";
		return 1;
	}

	std::cout << "Sorted:\n";
	print(arr);
	std::cout << "\n";

	std::cout << "Benchmark:\n";
	benchmark(100000, 10, selection_sort_reverse);
	std::cout << "\n\n";

	std::cout << "Linear search:\n\n";
	fill(arr);
	std::cout << "Generated array:\n";
	print(arr);
	u16 i = 5682;
	std::cout << "Enter target element: ";
	// std::cin >> i;

	int result = linear_search(arr, i);
	if (result > 0) {
		std::cout << "Element " << i << " is placed at index " << result << "\n";
	} else {
		std::cout << "Element not found!\n";
	}

	std::cout << "Benchmark:\n";
	search_benchmark(10000000, 10, linear_search);
	std::cout << "\n\n";

	std::cout << "Benchmark interpolated:\n";
	search_benchmark_sorted(10000000, 10, interpolation_search);
	std::cout << "\n\n";
	
	free(arr.data);
	return 0;
}
