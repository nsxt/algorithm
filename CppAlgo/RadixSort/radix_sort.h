#pragma once
#include "../Common/util.h"
#include "../ArrayStack/array_stack.h"

inline unsigned long bits(unsigned long x, unsigned long k, unsigned long j)
{
	return (x >> k) & ~(~0 << j);
}

void radix_exchange_sort(unsigned long a[], int n, int b = 31)
{	
	int i = 0;		// Low
	int j = n - 1;	// High

	if (n > 1 && b >= 0) {

		while (true)
		{
			while (bits(a[i], b, 1) == 0 && i < j) i++;
			while (bits(a[j], b, 1) != 0 && i < j) j--;
			
			if (i >= j) 
				break;

			nsxtalgo::swap(a[i], a[j]);
		}
		
		if (bits(a[n - 1], b, 1) == 0) j++;   // 모두 0인경우 대비

		radix_exchange_sort(a, j, b - 1);
		radix_exchange_sort(a + i, n - j, b - 1);
	}
}