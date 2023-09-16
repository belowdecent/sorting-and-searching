#include "sorts.hpp"

void insertion_sort_partial(Array<u16> arr, int d, int offset) {
	for (int i = 1; i < arr.size / d; i++) {
		if (d * i + offset >= arr.size) break;
		u16 val = arr.data[d * i + offset];
		int j = i - 1;

		for (j = i - 1; j >= 0; j--) {
			if (val > arr.data[d * j + offset]) {
				break;
			}
		}
		j += 1;

		if (j < i) {
			for (int k = i; k > j; k--) {
				arr.data[k*d + offset] = arr.data[(k-1)*d + offset];
			}
		}
		arr.data[j*d + offset] = val;
	}
}

void insertion_sort(Array<u16> arr) {
	insertion_sort_partial(arr, 1, 0);
}

void shell_sort(Array<u16> arr) {
	int d = arr.size / 2;

	for (d = arr.size / 2; d > 1; d /= 2) {
		for (int offset = 0; offset < d; offset++) {
			insertion_sort_partial(arr, d, offset);
		}
	}

	insertion_sort(arr);
}

void selection_sort_reverse(Array<u16> arr) {
	for (int i = 0; i < arr.size; i++) {
		int max = i;

		for (int j = i; j < arr.size; j++) {
			if (arr.data[max] < arr.data[j]) max = j;
		}

		u16 buf = arr.data[max];
		arr.data[max] = arr.data[i];
		arr.data[i] = buf;
	}
}
