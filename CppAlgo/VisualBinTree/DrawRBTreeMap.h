#ifndef _DrawRBTreeMap_h
#define _DrawRBTreeMap_h

#include "../Search/RBTreeMap.h"
#include "../String/AString.h"
#include <afxwin.h>

// MFC���ø����̼ǿ��� ����� ���� Release Multithreaded ������ ����ؾ� �Ѵ�. 
#pragma comment(lib, "../cppalgo/ReleaseMT/cppalgo.lib")

class DrawRBTreeMap : public cppalgo::RBTreeMap<cppalgo::String>
{
public:
	DrawRBTreeMap() : cppalgo::RBTreeMap<cppalgo::String>() { m_nDY = 50; m_nXMargin = 10; m_nYMargin = 20; }
	~DrawRBTreeMap() {}

	void Draw(CDC *pDC, const RECT& rt);
protected:
	int m_nDY;
	int m_nXMargin;
	int m_nYMargin;

	void _DrawNode(CDC *pDC, Node *p, int x1, int x2, int y);
	void _DrawLink(CDC *pDC, Node *p, int x1, int x2, int y);
};

#endif