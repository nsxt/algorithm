#pragma once
#include <cstring>
#include <cassert>
#include "../ArraySeqMap/array_seq_map.h"

/*
	"Binary Sequential Search" by using ArraySeqMap class.

	: ����(�̺�) ���� �˻��� ���� �ڷᰡ �̸� ���ĵǾ� �־�� �Ѵ�.
*/

template<class T> class BinArraySeqMap : public ArraySeqMap<T>
{
public:
	BinArraySeqMap(int size = 100) : ArraySeqMap<T>(size) {}
	~BinArraySeqMap() {}

public:
	virtual bool insert(const T& value) override
	{
		if (!ArraySeqMap<T>::insert(value))
			return false;

		// Insertion Sort
		int j = len_ - 1;
		while (j > 0) {
			if (elems_[j - 1] > value)
				elems_[j] = elems_[j - 1];
			else
				break;

			j--;
		}

		elems_[j] = value;

		return true;
	}

	virtual bool find_first(const T& key, T& value, MapPos& pos) const override
	{
		if (!ArraySeqMap<T>::find_first(key, value, pos))
			return false;

		// �ߺ��� Ű�� �������� �迭�Ǿ� �ִ� ���� �߰��� ��ġ������ ����ó��
		// ���� Ű�� �ߺ��� ���� �����̳ʶ�� �����̴�.
		int j = pos.index;
		while (j > 0) {
			if (!(elems_[j - 1] == value))
				break;

			j--;
		}

		pos.index = j;
		value = elems_[j];

		return true;
	}

	virtual bool find_next(T& value, MapPos& pos) const override
	{
		if (pos.index + 1 >= len_)
			return false;

		if (elems_[pos.index + 1] == pos.key) {
			pos.index++;
			value = elems_[pos.index];
			return true;
		}

		return false;
	}

protected:
	virtual bool _find(MapPos& pos) const override
	{
		int mid;
		int left = 0;
		int right = len_ - 1;

		while (right >= left) {
			
			mid = (right + left) / 2;

			if (pos.key == elems_[mid]) {
				pos.index = mid;
				return true;
			}

			if (pos.key > elems_[mid])
				left = mid + 1;
			else
				right = mid - 1;
		}

		return false;
	}
	
};