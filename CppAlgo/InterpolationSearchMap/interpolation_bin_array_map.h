#pragma once
#include "../BinaryArrayMap/binary_array_seq_map.h"

/*
	"Interpolation Sequential Search" by using BinArraySeqMap class.

	: 내분법(보간) 선형 검색은 양의 정수의 미리 정렬된 자료를 대상으로 한다.
	  주어진 데이터가 선형에 가까운 그래프로 그려질때 보간 공식을 사용하여 중간 값을 구한다.

	: Left + (Key - Left) * (Right - Left) / (Right - Left)

*/

class InterpolationSeqMap : public BinArraySeqMap<int>
{
public:
	InterpolationSeqMap(int size = 100) : BinArraySeqMap<int>(size) {}
	~InterpolationSeqMap() {}

protected:
	virtual bool _find(MapPos& pos) const override
	{
		int mid;
		int left = 0;
		int right = len_ - 1;

		while (right >= left) {
			if (!(elems_[right] == elems_[left])) {

				mid = (int)(left + (pos.key - elems_[left]) * (right - left) / (elems_[right] - elems_[left]));

				if (mid < left) mid = left;
				if (mid > right) mid = right;
			}
			else {
				mid = left;	// 젯수가 0 인 경우, left <-> right 사이의 구간은 모두 같은값
			}

			if (pos.key == elems_[mid]) {
				pos.index = mid;
				return true;
			}

			// Binary Search (이분검색) - 범위를 좁힌다.
			if (pos.key > elems_[mid])
				left = mid + 1;
			else
				right = mid - 1;
		}

		return false;
	}
};
