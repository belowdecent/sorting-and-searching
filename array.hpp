#pragma once

template<typename T>
struct Array {
	T* data;
	int size;
};

typedef unsigned short u16;

#define ARRAY_MAX 32768

void fill(Array<u16> arr);
void fill_sorted(Array<u16> arr);

void print(Array<u16> arr);
bool is_sorted(Array<u16> arr);
bool is_sorted_reverse(Array<u16> arr);
void benchmark(int array_size, int runs, void (*sort)(Array<u16>));
