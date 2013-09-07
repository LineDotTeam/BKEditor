#ifndef _SCROLL_WINDOW_H_
#define _SCROLL_WINDOW_H_

#include <atlbase.h>
#include <atlwin.h>
#include <vector>
using namespace std;

#include "ScrollDefines.h"

namespace scroll
{
	class CVerticalScrollBar
		: public CWindowImpl<CVerticalScrollBar, CWindow, CControlWinTraits>
		, public IScrollBar
	{
	public:
		DECLARE_WND_CLASS(_T("kvscrollbar"))

		BEGIN_MSG_MAP(CVerticalScrollBar)
			MESSAGE_HANDLER(WM_SIZE, OnSize)
			MESSAGE_HANDLER(WM_PAINT, OnPaint)
			MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
			MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
			MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
			MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
			MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		END_MSG_MAP()

	public:

		CVerticalScrollBar();
		~CVerticalScrollBar();

	public:
		void Init( DWORD dwArea, HBITMAP hBitmap );
		void Init( DWORD dwArea, HBITMAP hBitmap, INT nMinSize, INT nBarTop, INT nBarBottom, INT nBgTop, INT nBgBottom );
		void SetScrollView( IScrollView *pScrollView );
		void NotifyScrollSizeChanged( INT nHeight, INT nViewHeight );
		void NotifyScrollPosChanged( INT nPos, INT nViewHeight );

	protected:
		BOOL HasArea( DWORD dwArea ) { return dwArea == (m_dwArea & dwArea); }

	protected:
		LRESULT OnSize( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled );
		LRESULT OnPaint( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled );
		LRESULT OnEraseBkgnd( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled );
		LRESULT OnLButtonDown( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled );
		LRESULT OnLButtonUp( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled );
		LRESULT OnMouseMove( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled );
		LRESULT OnMouseLeave( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled );

	protected:
		//�����Ⱥ�����߶�
		INT		m_nWidth;
		INT		m_nHeight;
		INT		m_nBarHeight;
		INT		m_nBarMinHeight;

		//���廬��ͱ���Ƥ�������������̶��Ĳ��������ĸ߶ȣ��м䲿�ֿ�����
		INT		m_nItemHeight;
		INT		m_nBarTop;
		INT		m_nBarBottom;
		INT		m_nBgTop;
		INT		m_nBgBottom;

		//��������
		BOOL	m_bMouseDown;
		DWORD	m_dwMouseArea;
		DWORD	m_dwArea;
		void	InitAreaRect();

		//����ɹ�������
		INT		m_nViewTop;
		INT		m_nViewBottom;

		//����λ��
		INT		m_nPos;

		//����ÿ������ľ��ο�
		RECT	m_rectArea[6];
		BOOL	PtInRect( INT nPosX, INT nPosY, RECT &rect );

		//������Ҫ��������ͼ
		IScrollView * m_pScrollView;

	private:
		INT		m_nMousePos;
		HBITMAP m_hBitmap;
	};

	class CScrollView
		: public CWindowImpl<CScrollView, CWindow, CControlWinTraits>
		, public IScrollView
	{
	public:
		DECLARE_WND_CLASS(_T("kscrollview"))
		BEGIN_MSG_MAP(CScrollView)
			MESSAGE_HANDLER(WM_PAINT, OnPaint)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
			MESSAGE_HANDLER(WM_SIZE, OnSize)
			MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
			MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMoseWheel)
			MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		END_MSG_MAP()
	public:
		CScrollView();
		~CScrollView();
		
		void Init( INT nWidth, INT nHeight );
		void Append( IDrawItem * pItem );
		void SetVerticalScrollBar( IScrollBar * pVerticalScrollBar );
		void SetHorizontalScrollBar( IScrollBar * pHorizontalScrollBar );
		void SetFont( HFONT hFont );
	public:
		void NotifyVerticalScrollPosChanged( INT nPos, INT nHeight );
		void NotifyHorizontalScrollPosChanged( INT nPos, INT nWidth );

	protected:
		LRESULT OnPaint( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled );
		LRESULT OnCreate( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled );
		LRESULT OnSize( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled );
		LRESULT OnDestroy( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled );
		LRESULT OnMoseWheel( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled );
		LRESULT OnMouseMove( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled );

	protected:
		//�����͸�
		INT		m_nWidth;
		INT		m_nHeight;

		//�������������ߺ͵�ǰ��ʾ��λ��
		INT		m_nViewHeight;
		INT		m_nViewWidth;
		INT		m_nPosX;
		INT		m_nPosY;

		//����
		vector<IDrawItem *> m_vecItem;
		HDC		m_hMemDC;
		HFONT	m_hFont;

	protected:
		IScrollBar	*m_pVerticalScrollBar;
		IScrollBar	*m_pHorizontalScrollBar;

	private:
		void Clear();
	};
}

#endif