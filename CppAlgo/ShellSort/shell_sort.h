#pragma once

template<class T>
void shell_sort(T a[], int n)
{
	int i, j, k, h;
	T v;

	for (h = n / 2; h > 0; h /= 2) {
		for (i = 0; i < h; i++) {
			for (j = i + h; j < n; j += h) {
				
				v = a[j];
				k = j;

				while (k > h - 1 && a[k - h] > v) {
					a[k] = a[k - h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
}


template<class T>
void shell_sort_3h(T a[], int n)
{
	// h = 3*h + 1 수열 사용
	int i, j, k, h;
	T v;

	// n 보다 작은 최대의 h 를 찾음
	for (h = 1; h < n; h = 3 * h + 1);

	for (h /= 3; h > 0; h /= 3) {
		for (i = 0; i < h; i++) {
			for (j = i + h; j < n; j += h) {

				v = a[j];
				k = j;

				while (k > h - 1 && a[k - h] > v) {
					a[k] = a[k - h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
}