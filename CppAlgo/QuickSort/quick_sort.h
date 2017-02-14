#pragma once
#include "../Common/util.h"

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
size_t partition(T a[], size_t left, size_t right, T& pivot)
{
	size_t i = left;
	size_t j = right;

	while (true) {
		while ((i <= j) && (a[i++] < pivot));
		while ((j >= i) && (a[j--] > pivot));

		if (i >= j) {
			break;
		}
		else {
			nsxtalgo::swap(a[i], a[j]);
		}
	}
	
	nsxtalgo::swap(a[i], pivot);

	return i;
}

template<class T>
void quick_sort(T a[], int n)
{
	T v, t;
	int i, j;

	if (n > 1)	// 재귀호출의 종료조건 
	{
		v = a[n - 1];  // v는 pivot value
		i = -1;		// i는 왼쪽부터 검색할 위치 
		j = n - 1;    // j는 오른쪽부터 검색할 위치 
		while (true)
		{
			while (a[++i] < v);  // 축값보다 큰 값이 있나 검사
			while ((j > 0) && (a[--j] > v));
			if (i >= j) break;
			t = a[i];		// 두 값을 교환 
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];   // 축값과 축값의 위치에 있는 값을 바꿈 
		a[i] = a[n - 1];
		a[n - 1] = t;
		quick_sort(a, i);  // 왼쪽 구간 
		quick_sort(a + i + 1, n - i - 1);  // 오른쪽 구간 
	}
}

