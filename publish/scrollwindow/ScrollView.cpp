#include "ScrollWindow.h"

namespace scroll
{
	CScrollView::CScrollView()
		: m_nPosX( 0 )
		, m_nPosY( 0 )
		, m_hMemDC( 0 )
		, m_hFont( 0 )
		, m_pVerticalScrollBar( 0 )
		, m_pHorizontalScrollBar( 0 )
	{
	}

	CScrollView::~CScrollView()
	{
		Clear();
	}

	void CScrollView::Init( INT nWidth, INT nHeight )
	{ 
		m_nWidth = nWidth; 
		m_nHeight = nHeight;

		m_nViewWidth = 0;
		m_nViewHeight = 0;
	}

	void CScrollView::Append( IDrawItem * pItem )
	{
		if( m_hWnd )
		{
			m_vecItem.push_back( pItem );

			RECT rect = pItem->CalcRect( m_hMemDC, m_nViewWidth, m_nViewHeight, m_nWidth );
			if( m_nViewHeight < rect.bottom )
			{
				m_nViewHeight = rect.bottom;
				if( m_pVerticalScrollBar )
					m_pVerticalScrollBar->NotifyScrollSizeChanged( m_nHeight, m_nViewHeight );
			}

			::InvalidateRect( m_hWnd, NULL, FALSE );
		}
	}

	void CScrollView::SetVerticalScrollBar( IScrollBar * pVerticalScrollBar )
	{
		m_pVerticalScrollBar = pVerticalScrollBar;
	}

	void CScrollView::SetHorizontalScrollBar( IScrollBar * pHorizontalScrollBar )
	{
		m_pHorizontalScrollBar = pHorizontalScrollBar;
	}

	void CScrollView::SetFont( HFONT hFont )
	{ 
		m_hFont = hFont;
		::SelectObject( m_hMemDC, m_hFont );
	}

	void CScrollView::NotifyVerticalScrollPosChanged( INT nPos, INT nHeight )
	{
		if( m_hWnd )
		{
			m_nPosY = (m_nViewHeight - m_nHeight) * nPos / nHeight;

			m_nPosY = min( m_nPosY, m_nViewHeight - m_nHeight );
			m_nPosY = max( 0, m_nPosY );

			::InvalidateRect( m_hWnd, NULL, FALSE );
		}
	}

	void CScrollView::NotifyHorizontalScrollPosChanged( INT nPos, INT nWidth )
	{
		if( m_hWnd )
		{
			m_nPosX = (m_nViewWidth - m_nWidth) * nPos / nWidth;
			::InvalidateRect( m_hWnd, NULL, FALSE );
		}
	}

	LRESULT CScrollView::OnPaint( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
	{
		PAINTSTRUCT ps;
		HDC hDC = ::BeginPaint( m_hWnd, &ps );
		RECT rect;
		::GetClientRect( m_hWnd, &rect );

		HBRUSH hBrush = (HBRUSH)::CreateSolidBrush( RGB( 254, 239, 192 ) );
		::PatBlt( m_hMemDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top, PATCOPY );
		::DeleteObject( hBrush );

		for( vector<IDrawItem *>::iterator iter = m_vecItem.begin(); iter != m_vecItem.end(); iter++ )
			(*iter)->Draw( m_hMemDC, m_nPosX, m_nPosY, m_nWidth, m_nHeight );
		
		::BitBlt( hDC, 0, 0, m_nWidth, m_nHeight, m_hMemDC, 0, 0, SRCCOPY );

		::EndPaint( m_hWnd, &ps );
		return TRUE;
	}

	LRESULT CScrollView::OnCreate( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
	{
		HDC hDC = ::GetDC( m_hWnd );
		m_hMemDC = ::CreateCompatibleDC( hDC );
		
		::SetBkMode( m_hMemDC, TRANSPARENT );
		::SelectObject( m_hMemDC, m_hFont );

		::ReleaseDC( m_hWnd, hDC );

		return TRUE;
	}

	LRESULT CScrollView::OnSize( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
	{
		INT xSize = (INT)(LOWORD(lParam)), ySize = (INT)(HIWORD(lParam));
		HDC hDC = ::GetDC( m_hWnd );
		HBITMAP hBitmap = CreateCompatibleBitmap( hDC, xSize, ySize );
		::SelectObject( m_hMemDC, hBitmap );
		::DeleteObject( hBitmap );
		::ReleaseDC( m_hWnd, hDC );
		return TRUE;
	}

	LRESULT CScrollView::OnDestroy( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
	{
		::DeleteDC( m_hMemDC );
		m_hMemDC = NULL;

		return TRUE;
	}

	LRESULT CScrollView::OnMoseWheel( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
	{
		short nSize = (short)HIWORD(wParam);
		
		m_nPosY -= nSize;
		m_nPosY = min( m_nPosY, m_nViewHeight - m_nHeight );
		m_nPosY = max( 0, m_nPosY );

		if( m_pVerticalScrollBar )
			m_pVerticalScrollBar->NotifyScrollPosChanged( m_nPosY, m_nViewHeight - m_nHeight );

		::InvalidateRect( m_hWnd, NULL, FALSE );
		return TRUE;
	}

	LRESULT CScrollView::OnMouseMove( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
	{
		::SetFocus( m_hWnd );
		return TRUE;
	}

	void CScrollView::Clear()
	{
		for( vector<IDrawItem *>::iterator iter = m_vecItem.begin(); iter != m_vecItem.end(); iter++ )
		{
			IDrawItem * item = *iter;
			item->Destroy();
			delete item;
		}

		m_vecItem.clear();
	}
}