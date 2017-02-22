#pragma once

#include <cstring>
#include <cassert>

template<class T>
void merge_sort(T a[], int n)
{
	int i, j, k;
	int run_a, run_b;
	int size;
	T* b;

	b = new T[n];
	assert(b != nullptr);

	// �迭�� Ȧ���� �϶��� ���� ������ b �迭�� ������ ������ ���� a �迭�� ����Ǵ� ������ ����
	// �迭�� �ʱ�ȭ �ϰ�, a �迭�� ������ ��Ҹ� b �� ����
	std::memset(b, n, sizeof(int) * n);
	b[n - 1] = a[n - 1];

	for (size = 1; size < n; size *= 2) {
		
		run_a = 0;
		run_b = size;

		while (run_b < n) {
			
			i = run_a;
			j = run_b;
			k = run_a;

			while (i < run_a + size || (j < run_b + size && j < n)) {				
				if (a[i] > a[j]) {
					if (j < run_b + size && j < n)
						b[k++] = a[j++];
					else
						b[k++] = a[i++];
				}
				else {
					if (i < run_a + size)
						b[k++] = a[i++];
					else
						b[k++] = a[j++];
				}
			}
			run_a += 2 * size;
			run_b += 2 * size;
		}

		for (i = 0; i < n; i++)
			a[i] = b[i];
	}

	delete [] b;
}


template<class T>
void merge_sort_ex(T a[], int n)
{
	int i, j, k;
	int run_a, run_b;
	int size;
	T* b;

	b = new T[n];
	assert(b != nullptr);

	T* src = a;
	T* tmp = b;

	for (size = 1; size < n; size *= 2) {
		run_a = 0;
		run_b = size;

		while (run_b < n) {
			i = run_a;
			j = run_b;
			k = run_a;

			while (i < run_a + size || (j < run_b + size && j < n)) {
				if (src[i] > src[j]) {
					if (j < run_b + size && j < n)
						tmp[k++] = src[j++];
					else
						tmp[k++] = src[i++];
				}
				else {
					if (i < run_a + size)
						tmp[k++] = src[i++];
					else
						tmp[k++] = src[j++];
				}
			}

			run_a += 2 * size;
			run_b += 2 * size;
		}

		T* t = src;
		src = tmp;
		tmp = t;
	}

	if (tmp == a) {
		for (int i = 0; i < n; i++)
			a[i] = b[i];
	}

	delete[] b;
}