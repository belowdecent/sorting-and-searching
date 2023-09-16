#include "array.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <chrono>

void fill(Array<u16> arr) {
	for (int i = 0; i < arr.size; i++) {
		arr.data[i] = (u16)(std::rand() % 32768);
	}
}

void fill_sorted(Array<u16> arr) {
	double max_increment = 2.0 * ARRAY_MAX / (double)arr.size;
	double current_val = double(std::rand()) / RAND_MAX * max_increment;

	for (int i = 0; i < arr.size; i++) {
		arr.data[i] = std::floor(current_val) > ARRAY_MAX ? ARRAY_MAX : std::floor(current_val);
		current_val += double(std::rand()) / RAND_MAX * max_increment;
	}
}

void print(Array<u16> arr) {
	for (int i = 0; i < arr.size; i++) {
		std::cout << arr.data[i] << " ";
	}
	std::cout << "\n";
}

bool is_sorted(Array<u16> arr) {
	for (int i = 1; i < arr.size; i++) {
		if (arr.data[i] < arr.data[i - 1]) return false;
	}

	return true;
}

bool is_sorted_reverse(Array<u16> arr) {
	for (int i = 1; i < arr.size; i++) {
		if (arr.data[i] > arr.data[i - 1]) return false;
	}

	return true;
}

void benchmark(int array_size, int runs, void (*sort)(Array<u16>)) {
	namespace chrono = std::chrono;
	Array<u16> arr = {
		.data = (u16*)malloc(array_size * sizeof(u16)),
		.size = array_size,
	};

	std::cout << "Size: " << array_size<< ". Runs: " << runs << "\n";

	long total_time = 0;

	for (int i = 0; i < runs; i++) {
		fill(arr);
		chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
		sort(arr);
		chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();
		long dur = chrono::duration_cast<chrono::milliseconds>(end - start).count();

		total_time += dur;

		if (is_sorted(arr)) { 
			std::cout 
				<< "Sorted an array of size " << arr.size
				<< " in " << dur << "ms.\n";
		} else if (is_sorted_reverse(arr)) {
			std::cout 
				<< "Reverse-sorted an array of size " << arr.size
				<< " in " << dur << "ms.\n";
		} else {
			std::cout << "sorter broke\n";
			exit(1);
		}

	}

	free(arr.data);
	long average_time = total_time / runs;
	std::cout
		<< "Finished " << runs << " runs in " << total_time << "ms.\n"
		<< "Average time: " << average_time << "ms.\n";
}
