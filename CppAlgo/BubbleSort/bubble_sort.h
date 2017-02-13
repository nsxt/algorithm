#pragma once
#include "../Common/util.h"

/*
[ Pseudo Code ]

procedure bubbleSort( list : array of items )

	loop = list.count;

	for i = 0 to loop-1 do:
		swapped = false

		for j = 0 to loop-1 do:
			// compare the adjacent elements
			if list[j] > list[j + 1] then
				// swap them
				swap(list[j], list[j + 1])
				swapped = true
			end if
		end for

		// if no number was swapped that means
		// array is sorted now, break the loop.
		if (not swapped) then
			break
		end if

	end for

end procedure return list
*/

template<class T>
void bubble_sort(T a[], size_t n)
{
	bool swapped;

	for (size_t i = 0; i < n - 1; i++) {
		swapped = false;

		for (size_t j = 0; j < n - 1; j++) {
			if (a[j] > a[j + 1]) {
				nsxtalgo::swap(a[j], a[j + 1]);
				swapped = true;
			}
		}

		if (!swapped) {
			break;
		}
	}
}