#ifndef _DrawHashMap_h
#define _DrawHashMap_h

#include "../Search/HashMap.h"
#include "../String/AString.h"

#include <afxwin.h>

// MFC���ø����̼ǿ��� ����� ���� Release Multithreaded ������ ����ؾ� �Ѵ�. 
#pragma comment(lib, "../cppalgo/ReleaseMT/cppalgo.lib")

struct StringHash
{
	unsigned long hash(const cppalgo::String& key) const {
		unsigned long nHash = 0;
		for (int i = 0; i < key.GetLength(); i++)
			nHash = (nHash << 5) + nHash + key[i];
		return nHash;
	}
};

class DrawHashMap : public cppalgo::HashMap<cppalgo::String, StringHash>
{
public:
	DrawHashMap(const StringHash& hash, int nSize) : cppalgo::HashMap<cppalgo::String, StringHash>(hash, nSize) {
		m_nXMargin = 50;
		m_nYMargin = 10;
		m_nWidth = 200;
		m_nHeight = 20;
	}
	~DrawHashMap() {}

	void Draw(CDC *pDC);

protected:
	int m_nXMargin;
	int m_nYMargin;
	int m_nWidth;
	int m_nHeight;
};

#endif