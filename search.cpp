#include "search.hpp"
#include <cstdlib>
#include <chrono>
#include <iostream>

int linear_search(Array<u16> arr, u16 el) {
	for (int i = 0; i < arr.size; i++) {
		if (arr.data[i] == el) return i;
	}

	return -1;
}

int new_d(int i, int j, int k, Array<u16> arr) {
	return (j - i) * (k - arr.data[i]) / (arr.data[j] - arr.data[i]);
}

int interpolation_search(Array<u16> arr, u16 el) {
	int d;

	int i = 0;
	int j = arr.size - 1;
	int middle;

	for (int d = new_d(i, j, el, arr); d > 0; d = new_d(i, j, el, arr)) {
		middle = i + d;

		if (arr.data[middle] == el) {
			break;
		} else if (arr.data[middle] < el) {
			i = middle + 1;
		} else {
			j = middle - 1;
		}
	}

	if (arr.data[middle] == el) return -1;

	while (arr.data[middle - 1] == el) {
		middle -= 1;
	}

	return middle;
}

bool test_search(Array<u16> arr, u16 target, int index) {
	if (index == -1) {
		if (linear_search(arr, target) != -1) return false;
	}

	if (target != arr.data[index]) return false;

	for (int i = 0; i < index; i++) {
		if (arr.data[index - i] == target) return false;
	}

	return true;
}


void search_benchmark_internal(
	int array_size, 
	int runs, 
	int element_count,
	int (*search)(Array<u16>, u16),
	void (*fill_array)(Array<u16>)
) {
	namespace chrono = std::chrono;
	Array<u16> arr = {
		.data = (u16*)malloc(array_size * sizeof(u16)),
		.size = array_size,
	};

	std::cout << "Size: " << array_size<< ". Runs: " << runs << "\n";

	long total_time = 0;

	for (int i = 0; i < runs; i++) {
		fill_array(arr);
		chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
		for (int j = 0; j < element_count; j++) {
			int target = std::rand() % ARRAY_MAX;
			search(arr, target);
		}
		chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();
		long dur = chrono::duration_cast<chrono::milliseconds>(end - start).count();

		total_time += dur;

		std::cout 
			<< "Search completed " << arr.size
			<< " in " << dur << "ms.\n";
	}
}

void search_benchmark(int array_size, int runs, int (*search)(Array<u16>, u16)) {
	search_benchmark_internal(array_size, runs, 100000, search, fill);
}

void search_benchmark_sorted(int array_size, int runs, int (*search)(Array<u16>, u16)) {
	search_benchmark_internal(array_size, runs, 100000, search, fill_sorted);
}
