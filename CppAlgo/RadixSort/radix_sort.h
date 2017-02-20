#pragma once

#include <cstring>
#include "../Common/util.h"
#include "../ArrayStack/array_stack.h"

inline unsigned long bits(unsigned long x, unsigned long k, unsigned long j)
{
	return (x >> k) & ~(~0 << j);
}

void radix_exchange_sort(unsigned long a[], int n, int b = 31)
{	
	int i = 0;		// left
	int j = n - 1;	// right

	if (n > 1 && b >= 0) {

		while (true) {

			while (bits(a[i], b, 1) == 0 && i < j) {
				i++;
			}

			while (bits(a[j], b, 1) != 0 && i < j) {
				j--;
			}
			
			if (i >= j) 
				break;

			nsxtalgo::swap(a[i], a[j]);
		}
		
		if (bits(a[n - 1], b, 1) == 0) j++;   // 모두 0인경우 대비

		radix_exchange_sort(a, j, b - 1);
		radix_exchange_sort(a + i, n - j, b - 1);
	}
}

void radix_exchange_sort_stack(unsigned long a[], int n)
{
	int i, j;
	int l, r;
	int b;

	ArrayStack<int> stack(32 * 3 + 3);

	b = 31;
	l = 0;
	r = n - 1;

	stack.push(b);
	stack.push(r);
	stack.push(l);

	while (!stack.empty()) {

		l = stack.pop();
		r = stack.pop();
		b = stack.pop();

		if (r > l && b >= 0) {
			i = l;
			j = r;

			while (true) {
				
				while (bits(a[i], b, 1) == 0 && i < j) {
					i++;
				}

				while (bits(a[j], b, 1) == 1 && i < j) {
					j--;
				}

				if (i >= j)
					break;

				nsxtalgo::swap(a[i], a[j]);
			}

			if (bits(a[r], b, 1) == 0) j++;

			stack.push(b - 1);
			stack.push(r);
			stack.push(j);

			stack.push(b - 1);
			stack.push(j - 1);
			stack.push(l);
		}
	}
}


void straight_radix_sort(unsigned long a[], int n)
{
	int i, j;
	unsigned long *b, *count;
	unsigned long w = 32;
	unsigned long m = 8;
	unsigned long mv = (1 << m);

	b = new unsigned long[n];
	std::memset(b, 0, sizeof(unsigned long) * n);

	count = new unsigned long[mv];

	for (i = 0; i < w / m; i++)
	{
		std::memset(count, 0, sizeof(unsigned long) * mv);

		for (j = 0; j < n; j++)
			count[bits(a[j], i*m, m)]++;

		for (j = 1; j < mv; j++)
			count[j] = count[j] + count[j - 1];

		for (j = n - 1; j >= 0; j--)
			b[--count[bits(a[j], i*m, m)]] = a[j];

		std::memcpy(a, b, sizeof(unsigned long) * n);
	}

	delete[] b;
	delete[] count;
}