#pragma once
#include "../BinaryArrayMap/binary_array_seq_map.h"

/*
	"Interpolation Sequential Search" by using BinArraySeqMap class.

	: ���й�(����) ���� �˻��� ���� ������ �̸� ���ĵ� �ڷḦ ������� �Ѵ�.
	  �־��� �����Ͱ� ������ ����� �׷����� �׷����� ���� ������ ����Ͽ� �߰� ���� ���Ѵ�.

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
				mid = left;	// ������ 0 �� ���, left <-> right ������ ������ ��� ������
			}

			if (pos.key == elems_[mid]) {
				pos.index = mid;
				return true;
			}

			// Binary Search (�̺а˻�) - ������ ������.
			if (pos.key > elems_[mid])
				left = mid + 1;
			else
				right = mid - 1;
		}

		return false;
	}
};
