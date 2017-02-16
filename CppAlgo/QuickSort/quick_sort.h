#pragma once

#include <cmath>
#include "../Common/util.h"
#include "../ListStack/list_stack.h"
#include "../ArrayStack/array_stack.h"
#include "../InsertionSort/insertion_sort.h"


template<class T>
int partition(T a[], int low, int high)
{
	T& pivot = a[high];
	int i = low;
	int j = high - 1;

	while (true) {
		for (; i < high; i++) {
			if (a[i] > pivot)
				break;
		}

		for (; j > low; j--) {
			if (a[j] < pivot)
				break;
		}

		if (i >= j)
			break;

		nsxtalgo::swap(a[i], a[j]);
	}

	nsxtalgo::swap(a[i], pivot);

	return i;
}


template<class T>
int partition_random(T a[], int low, int high)
{
	int n = high - low + 1;
	int pivot = int(((double)rand() / (double)RAND_MAX)*(double)(n - 1));

	nsxtalgo::swap(a[pivot + low], a[high]);

	return partition(a, low, high);
}


/*
	Recursion version
*/
template<class T>
void quick_sort(T a[], int n)
{
	if (n > 1)
	{
		int low = 0;
		int high = n - 1;

		int i = partition(a, low, high);

		quick_sort(a, i);
		quick_sort(a + i + 1, n - i - 1);
	}
}


/*
	List Stack version
*/
template<class T>
void quick_sort_liststack(T a[], int n)
{
	int i;
	int low, high;
	ListStack<int> stack;

	low = 0;
	high = n - 1;

	stack.push(high);
	stack.push(low);

	while (!stack.empty())
	{
		low = static_cast<int>(stack.pop());
		high = static_cast<int>(stack.pop());

		if (high - low + 1 > 1)
		{
			i = partition(a, low, high);

			stack.push(high);	// high
			stack.push(i + 1);  // low
						
			stack.push(i-1);	// high
			stack.push(low);	// low
		}
	}
}



/*
	Array Stack version
*/
template<class T>
void quick_sort_arraystack(T a[], int n)
{
	int i;
	int low, high;
	ArrayStack<int> stack(n * 2 + 2);

	low = 0;
	high = n - 1;

	stack.push(high);
	stack.push(low);

	while (!stack.empty())
	{
		low = static_cast<int>(stack.pop());
		high = static_cast<int>(stack.pop());

		if (high - low + 1 > 1)
		{
			i = partition(a, low, high);

			stack.push(high);	// high
			stack.push(i + 1);  // low

			stack.push(i - 1);	// high
			stack.push(low);	// low
		}
	}
}



/*
	Random Pivot version
*/
template<class T>
void quick_sort_random(T a[], int n)
{
	int i;
	int low, high;
	ArrayStack<int> stack(n * 2 + 2);

	low = 0;
	high = n - 1;

	stack.push(high);
	stack.push(low);

	while (!stack.empty())
	{
		low = static_cast<int>(stack.pop());
		high = static_cast<int>(stack.pop());

		if (high - low + 1 > 1)
		{
			i = partition_random(a, low, high);

			stack.push(high);	// high
			stack.push(i + 1);  // low

			stack.push(i - 1);	// high
			stack.push(low);	// low
		}
	}
}


/*
Pivot Median Sort
*/
template<class T>
int pivot_median_sort(T a[], int low, int high)
{
	int n = high - low + 1;

	if (n > 1) {
		int pivot = int(std::round(((double)n / (double)2))) + low - 1;

		if (a[low] > a[pivot]) {
			nsxtalgo::swap(a[low], a[pivot]);
		}
		if (a[pivot] > a[high]) {
			nsxtalgo::swap(a[pivot], a[high]);
		}
		if (a[low] > a[pivot]) {
			nsxtalgo::swap(a[low], a[pivot]);
		}

		return pivot;
	}

	return n;
}


/*
	Median Sorted Pivot partition
*/
template<class T>
int partition_median(T a[], int low, int high)
{
	int pivot = pivot_median_sort(a, low, high);
	nsxtalgo::swap(a[pivot], a[high - 1]);
	return partition(a, low + 1, high - 1);
}


/*
	Median Pivot version
*/
template<class T>
void quick_sort_median(T a[], int n)
{
	int i;
	int low, high;	
	ArrayStack<int> stack(n * 2 + 2);

	low = 0;
	high = n - 1;
	stack.push(high);
	stack.push(low);

	while (!stack.empty())
	{
		low = static_cast<int>(stack.pop());
		high = static_cast<int>(stack.pop());

		if (high - low + 1 > 3)
		{
			i = partition_median(a, low, high);	

			stack.push(high);
			stack.push(i + 1);

			stack.push(i - 1);
			stack.push(low);
		}
		else {
			pivot_median_sort(a, low, high);
		}
	}
}


/*
	Insertion and Median version
*/
template<class T>
void quick_sort_sub(T a[], int n)
{
	int i;
	int low, high;
	ArrayStack<int> stack(n * 2 + 2);

	low = 0;
	high = n - 1;
	stack.push(high);
	stack.push(low);

	while (!stack.empty())
	{
		low = static_cast<int>(stack.pop());
		high = static_cast<int>(stack.pop());

		if (high - low + 1 > 10)
		{
			i = partition_median(a, low, high);

			stack.push(high);
			stack.push(i + 1);

			stack.push(i - 1);
			stack.push(low);
		}
		else {
			insertion_sort(a + low, high - low + 1);
		}
	}
}