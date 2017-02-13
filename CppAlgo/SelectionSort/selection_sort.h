#pragma once

#include "../Common/util.h"

template<class T>
void selection_sort(T a[], size_t n)
{
/*
	Step 1 − Set MIN to location 0
	Step 2 − Search the minimum element in the list
	Step 3 − Swap with value at location MIN
	Step 4 − Increment MIN to point to next element
	Step 5 − Repeat until list is sorted
*/
	for (size_t i = 0; i < n - 1; i++) {
		T min_value = a[i];
		size_t min_index = i;

		for (size_t j = i + 1; j < n; j++) {
			if (a[j] < a[i]) {
				min_index = j;
			}
		}

		if (i != min_index) {
			nsxtalgo::swap(a[i], a[min_index]);
		}
	}
}