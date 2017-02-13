#pragma once

/*
[Algorithm]
Step 1 − If it is the first element, it is already sorted. return 1;
Step 2 − Pick next element
Step 3 − Compare with all elements in the sorted sub-list
Step 4 − Shift all the elements in the sorted sub-list that is greater than the
value to be sorted
Step 5 − Insert the value
Step 6 − Repeat until list is sorted

[Pseudocode]
procedure insertionSort( A : array of items )
	int holePosition
	int valueToInsert

	for i = 1 to length(A) inclusive do:

		// select value to be inserted
		valueToInsert = A[i]
		holePosition = i

		// locate hole position for the element to be inserted
		while holePosition > 0 and A[holePosition - 1] > valueToInsert do:
			A[holePosition] = A[holePosition - 1]
			holePosition = holePosition - 1
		end while

		// insert the number at hole position
		A[holePosition] = valueToInsert

	end for

end procedure
*/

template<class T>
void insertion_sort(T a[], size_t n)
{
	for (size_t i = 1; i < n; i++) {
		T v = a[i];
		size_t j = i;
		
		while (j > 0 && a[j - 1] > v) {
			a[j] = a[j - 1];
			j--;
		}
		a[j] = v;
	}
}