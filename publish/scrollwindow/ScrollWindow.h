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
		//定义宽度和总体高度
		INT		m_nWidth;
		INT		m_nHeight;
		INT		m_nBarHeight;
		INT		m_nBarMinHeight;

		//定义滑块和背景皮肤的上面和下面固定的不可拉升的高度，中间部分可拉升
		INT		m_nItemHeight;
		INT		m_nBarTop;
		INT		m_nBarBottom;
		INT		m_nBgTop;
		INT		m_nBgBottom;

		//定义区域
		BOOL	m_bMouseDown;
		DWORD	m_dwMouseArea;
		DWORD	m_dwArea;
		void	InitAreaRect();

		//定义可滚动区域
		INT		m_nViewTop;
		INT		m_nViewBottom;

		//定义位置
		INT		m_nPos;

		//定义每个区域的矩形框
		RECT	m_rectArea[6];
		BOOL	PtInRect( INT nPosX, INT nPosY, RECT &rect );

		//定义需要滚动的视图
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
		//定义宽和高
		INT		m_nWidth;
		INT		m_nHeight;

		//定义可视区域宽、高和当前显示的位置
		INT		m_nViewHeight;
		INT		m_nViewWidth;
		INT		m_nPosX;
		INT		m_nPosY;

		//绘制
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