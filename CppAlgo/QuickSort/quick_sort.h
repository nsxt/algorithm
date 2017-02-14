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

	if (n > 1)	// ���ȣ���� �������� 
	{
		v = a[n - 1];  // v�� pivot value
		i = -1;		// i�� ���ʺ��� �˻��� ��ġ 
		j = n - 1;    // j�� �����ʺ��� �˻��� ��ġ 
		while (true)
		{
			while (a[++i] < v);  // �ప���� ū ���� �ֳ� �˻�
			while ((j > 0) && (a[--j] > v));
			if (i >= j) break;
			t = a[i];		// �� ���� ��ȯ 
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];   // �ప�� �ప�� ��ġ�� �ִ� ���� �ٲ� 
		a[i] = a[n - 1];
		a[n - 1] = t;
		quick_sort(a, i);  // ���� ���� 
		quick_sort(a + i + 1, n - i - 1);  // ������ ���� 
	}
}

