#pragma once
#include "../Common/util.h"
#include "../ListStack/list_stack.h"
#include "../ArrayStack/array_stack.h"

/*
[ Hoare partition scheme ]

algorithm quicksort(A, lo, hi) is
	if lo < hi then
	p := partition(A, lo, hi)
	quicksort(A, lo, p)
	quicksort(A, p + 1, hi)

algorithm partition(A, lo, hi) is
	pivot := A[lo]
	i := lo - 1
	j := hi + 1
	loop forever
	do
	i := i + 1
	while A[i] < pivot

	do
	j := j - 1
	while A[j] > pivot

	if i >= j then
	return j

	swap A[i] with A[j]
*/
template<class T>
int partition(T a[], int n)
{
	T& v = a[n - 1];
	int i = -1;
	int j = n - 1;

	while (true) {
		while (a[++i] < v);
		while ((i >= j) && (a[--j] > v));

		if (i >= j) 
			break;
		
		nsxtalgo::swap(a[i], a[j]);
	}
	
	nsxtalgo::swap(a[i], v);

	return i;
}

/*
	Random Pivot partition
*/
template<class T>
int partition_random(T a[], int n)
{
	int pivot = int(((double)rand() / (double)RAND_MAX)*(double)(n - 1));
	nsxtalgo::swap(a[pivot], a[n - 1]);
	return partition(a, n);
}

/*
	Recursion version
*/
template<class T>
void quick_sort(T a[], int n)
{
	if (n > 1)
	{
		int i = partition(a, n);
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
	int l, r;  // 스택에 저장할 구간의 정보 
	ListStack<int> stack;

	l = 0;
	r = n - 1;
	stack.push(r);
	stack.push(l);

	while (!stack.empty())
	{
		l = stack.top(); stack.pop();
		r = stack.top(); stack.pop();

		if (r - l + 1 > 1)   // 종료조건 r-l+1은 구간의 길이 
		{
			i = partition(a + l, r - l + 1);

			// right
			stack.push(r);		// r
			stack.push(i + 1);  // l

			// left
			stack.push(i - 1);	// r
			stack.push(l);		// l
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
	int l, r;  // 스택에 저장할 구간의 정보 
	ArrayStack<int> stack(n*2+2);

	l = 0;
	r = n - 1;
	stack.push(r);
	stack.push(l);

	while (!stack.empty())
	{
		l = stack.pop();
		r = stack.pop();

		if (r - l + 1 > 1)   // 종료조건 r-l+1은 구간의 길이 
		{
			i = partition(a + l, r - l + 1);

			// right
			stack.push(r);		// r
			stack.push(i + 1);  // l

			// left
			stack.push(i - 1);	// r
			stack.push(l);		// l
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
	int l, r;  // 스택에 저장할 구간의 정보 
	ArrayStack<int> stack(n * 2 + 2);

	l = 0;
	r = n - 1;
	stack.push(r);
	stack.push(l);

	while (!stack.empty())
	{
		l = stack.pop();
		r = stack.pop();

		if (r - l + 1 > 1)   // 종료조건 r-l+1은 구간의 길이 
		{
			i = partition_random(a + l, r - l + 1);

			// right
			stack.push(r);		// r
			stack.push(i + 1);  // l

								// left
			stack.push(i - 1);	// r
			stack.push(l);		// l
		}
	}
}