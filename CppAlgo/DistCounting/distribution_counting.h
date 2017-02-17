#pragma once
#include <cstring>

/*
	Distribution Counting Sort Algorithm

	example data = { 5, 5, 5, 4, 0, 2, 3, 3, 3, 5, 5, 5, 4, 2, 3, 2 }

	[ PSEUDOCODE FOR COUNTING SORT (taken from CLR) ]
	1. Initialize counting array to all zeros.
	2. Count the number of times each value occurs in the input.
	3. Modify the counting array to give the number of values smaller than index
	   Transfer numbers from input to output array at locations provided by counting array
*/
void dist_counting_sort(size_t a[], int n, int m)
{
	size_t *count = new size_t[m];
	size_t *b = new size_t[n];
	int i, pos;

	std::memset(count, 0, sizeof size_t * m);
	std::memset(b, 0, sizeof size_t * n);

	for (i = 0; i < n; i++) {
		count[a[i]]++;
	}

	for (i = 1; i < m; i++) {
		count[i] += count[i - 1];
	}

	for (i = 0; i < n; i++) {
		pos = count[a[i]]--;
		b[pos] = a[i];
	}

	std::memcpy(a, b, sizeof size_t * n);
}

