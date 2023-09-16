#pragma once

#include "array.hpp"

int linear_search(Array<u16> arr, u16 el);
int interpolation_search(Array<u16> arr, u16 el);

void search_benchmark(int array_size, int runs, int (*search)(Array<u16>, u16));
void search_benchmark_sorted(int array_size, int runs, int (*search)(Array<u16>, u16));
