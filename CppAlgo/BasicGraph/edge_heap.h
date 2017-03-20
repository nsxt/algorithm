#pragma once

template<class VERTEX> class EdgeHeap
{
public:
	typedef long EDGE;

	struct Pair {
		VERTEX v1;
		VERTEX v2;
		EDGE w;
		Pair(const VERTEX& vv1, const VERTEX& vv2, EDGE ww) { v1 = vv1; v2 = vv2; w = ww; }
		Pair() { w = 0; }
	};

public:
	EdgeHeap(int size = 100)
	{
		elems_ = new Pair[size];
		size_ = size;
		len_ = 0;
	}

	~EdgeHeap()
	{
		delete[] elems_;
	}

public:
	Pair& at(int k) { return elems_[k - 1]; }

	bool empty() { return len_ == 0; }

	void up_heap(int k)
	{
		Pair p;
		p = at(k);
		while (p.w > at(k / 2).w && k > 1) {
			at(k) = at(k / 2);
			k /= 2;
		}
		at(k) = p;
	}

	void down_heap(int k)
	{
		int i;
		Pair p;
		p = at(k);
		while (k <= len_ / 2) {
			i = k * 2;
			
			if (i < len_ && at(i + 1).w > at(i).w)
				i++;

			if (p.w > at(i).w || p.w == at(i).w)
				break;

			at(k) = at(i);
			k = i;
		}

		at(k) = p;
	}

	bool insert(const VERTEX& p, const VERTEX& v, EDGE w)
	{
		if (len_ >= size_ - 1)
			return false;

		at(++len_) = Pair(p, v, w);
		up_heap(len_);

		return true;
	}

	Pair extract()
	{
		Pair p = at(1);
		at(1) = at(len_--);
		down_heap(1);
		return p;
	}

	bool update(const VERTEX& p, const VERTEX& v, EDGE w)
	{
		// 정점 찾기
		for (int i = 0; i < len_; i++) {
			if (elems_[i].v2 == v && elems_[i].w < w) {
				elems_[i].w = w;
				elems_[i].v1 = p;

				for (int k = len_ / 2; k >= 1; k--)
					down_heap(k);

				return true;
			}
		}
		return false;
	}

protected:
	Pair* elems_;
	long size_;
	long len_;
};
