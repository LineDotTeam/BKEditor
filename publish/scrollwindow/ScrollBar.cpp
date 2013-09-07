#include "ScrollWindow.h"

namespace scroll
{
	CVerticalScrollBar::CVerticalScrollBar()
	{
	}

	CVerticalScrollBar::~CVerticalScrollBar()
	{
	}

	void CVerticalScrollBar::Init( DWORD dwArea, HBITMAP hBitmap )
	{
		Init( dwArea, hBitmap, 20, 0, 0, 0, 0 );
	}

	void CVerticalScrollBar::Init( DWORD dwArea, HBITMAP hBitmap, INT nMinSize, INT nBarTop, INT nBarBottom, INT nBgTop, INT nBgBottom )
	{
		if( hBitmap == NULL )
			return;

		BITMAP bitmap = { 0 };
		::GetObject( hBitmap, sizeof(BITMAP), (LPVOID) &bitmap );

		m_nWidth = bitmap.bmWidth / 10;
		m_nHeight = 0;
		m_nBarHeight = nMinSize;
		m_nBarMinHeight = nMinSize;

		m_nItemHeight = bitmap.bmHeight;
		m_nBarTop = nBarTop;
		m_nBarBottom = nBarBottom;
		m_nBgTop = nBgTop;
		m_nBgBottom = nBgBottom;

		m_bMouseDown = FALSE;
		m_dwMouseArea = Area_Null;
		m_dwArea = dwArea;

		m_nViewTop = 0;
		m_nViewBottom = 0;

		m_nPos = 0;

		m_pScrollView = 0;
		m_nMousePos = 0;

		m_hBitmap = hBitmap;
	}

	void CVerticalScrollBar::SetScrollView( IScrollView *pScrollView )
	{
		m_pScrollView = pScrollView;
	}

	void CVerticalScrollBar::NotifyScrollSizeChanged( INT nHeight, INT nViewHeight )
	{
		if( nViewHeight > 0 )
		{
			m_nBarHeight = (m_nViewBottom - m_nViewTop) * nHeight / nViewHeight;
			m_nBarHeight = max( m_nBarHeight, m_nBarMinHeight );
			m_nBarHeight = min( m_nViewBottom - m_nViewTop, m_nBarHeight );

			m_rectArea[3].top = m_nViewTop + m_nPos;
			m_rectArea[3].bottom = m_rectArea[3].top + m_nBarHeight;
			if( m_hWnd )
				::InvalidateRect( m_hWnd, NULL, FALSE );
		}
	}

	void CVerticalScrollBar::NotifyScrollPosChanged( INT nPos, INT nViewHeight )
	{
		if( nViewHeight > 0 )
		{
			m_nPos = (m_nViewBottom - m_nViewTop - m_nBarHeight ) * nPos / nViewHeight;
			m_nPos = max( m_nPos, 0 );
			m_nPos = min( m_nPos, m_nViewBottom - m_nViewTop - m_nBarHeight );

			m_rectArea[3].top = m_nViewTop + m_nPos;
			m_rectArea[3].bottom = m_rectArea[3].top + m_nBarHeight;

			if( m_hWnd )
				::InvalidateRect( m_hWnd, NULL, FALSE );
		}
	}

	LRESULT CVerticalScrollBar::OnSize( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
	{
		if( (INT)wParam != SIZE_MINIMIZED )
		{
			m_nHeight = (INT)HIWORD( lParam );
			m_nViewBottom = m_nHeight;
			InitAreaRect();
		}

		return TRUE;
	}

	LRESULT CVerticalScrollBar::OnPaint( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
	{
		PAINTSTRUCT ps;
		HDC hDC = ::BeginPaint( m_hWnd, &ps );
		HDC hMemDC = ::CreateCompatibleDC( hDC );
		::SelectObject( hMemDC, m_hBitmap );

		INT nItemHeight = m_nItemHeight / 3;
		INT xUnit = 0;
		for( INT nIndex = 0; nIndex < 6; nIndex++ )
		{
			DWORD dwArea = 1 << nIndex;
			if( HasArea( dwArea ) )
			{
				INT left = m_rectArea[nIndex].left, top = m_rectArea[nIndex].top, right = m_rectArea[nIndex].right, bottom = m_rectArea[nIndex].bottom;
				INT xMemPos = 0, yMemPos = 0;
				
				if( dwArea == Area_LineL || dwArea == Area_PageL || dwArea == Area_PageW || dwArea == Area_LineW )
				{
					xMemPos = xUnit * m_nWidth;
					if( m_dwMouseArea == dwArea )
						yMemPos += nItemHeight;
					if( m_dwMouseArea == dwArea && m_bMouseDown )
						yMemPos += nItemHeight;
					
					::BitBlt( hDC, left, top, m_nWidth, nItemHeight, hMemDC, xMemPos, yMemPos, SRCCOPY );

					xUnit++;
				}
				else if( dwArea == Area_Bg )
				{
					xMemPos = xUnit * m_nWidth;
					if( m_dwMouseArea == dwArea )
						xMemPos += m_nWidth;
					if( m_dwMouseArea == dwArea && m_bMouseDown )
						xMemPos += m_nWidth;

					::BitBlt( hDC, left, top, m_nWidth, m_nBgTop, hMemDC, xMemPos, yMemPos, SRCCOPY );
					::BitBlt( hDC, left, bottom - m_nBgBottom, m_nWidth, m_nBgBottom, hMemDC, xMemPos, yMemPos + nItemHeight - m_nBgBottom, SRCCOPY );

					::StretchBlt( hDC, left, top + m_nBgTop, m_nWidth, bottom - top - m_nBgTop - m_nBgBottom, hMemDC, xMemPos, yMemPos + m_nBgTop, m_nWidth, nItemHeight - m_nBgTop - m_nBgBottom, SRCCOPY );
					xUnit += 3;
				}
				else if( dwArea == Area_Bar )
				{
					xMemPos = xUnit * m_nWidth;
					if( m_dwMouseArea == dwArea )
						xMemPos += m_nWidth;
					if( m_dwMouseArea == dwArea && m_bMouseDown )
						xMemPos += m_nWidth;

					::BitBlt( hDC, left, top, m_nWidth, m_nBarTop, hMemDC, xMemPos, yMemPos, SRCCOPY );
					::BitBlt( hDC, left, bottom - m_nBarBottom, m_nWidth, m_nBarBottom, hMemDC, xMemPos, yMemPos + nItemHeight - m_nBarBottom, SRCCOPY );
					
					::StretchBlt( hDC, left, top + m_nBarTop, m_nWidth, bottom - top - m_nBarTop - m_nBarBottom, hMemDC, xMemPos, yMemPos + m_nBarTop, m_nWidth, nItemHeight - m_nBarTop - m_nBarBottom, SRCCOPY );
					xUnit += 3;
				}
			}
		}
		
		::DeleteDC( hMemDC );
		::EndPaint( m_hWnd, &ps );
		
		return TRUE;
	}

	LRESULT CVerticalScrollBar::OnEraseBkgnd( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
	{
		return TRUE;
	}

	LRESULT CVerticalScrollBar::OnLButtonDown( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
	{
		INT xPos = (INT)(LOWORD(lParam)), yPos = (INT)(HIWORD(lParam));
		m_nMousePos = yPos;

		for( INT nIndex = 0; nIndex < 6; nIndex++ )
		{
			DWORD dwArea = 1 << nIndex;
			if( PtInRect( xPos, yPos, m_rectArea[nIndex] ) )
			{
				m_dwMouseArea = dwArea;
				m_bMouseDown = TRUE;

				if( Area_Bar == dwArea )
					::SetCapture( m_hWnd );
			}
		}

		::InvalidateRect( m_hWnd, NULL, FALSE );
		return TRUE;
	}

	LRESULT CVerticalScrollBar::OnLButtonUp( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
	{
		INT xPos = (INT)(LOWORD(lParam)), yPos = (INT)(HIWORD(lParam));
		if( m_dwMouseArea == Area_Bar )
		{
			::ReleaseCapture();
			if( yPos >= m_nViewTop && yPos <= m_nViewBottom )
			{
				m_nPos += (yPos - m_nMousePos);
				m_nPos = max( 0, m_nPos );
				m_nPos = min( m_nViewBottom - m_nViewTop - m_nBarHeight, m_nPos );

				m_rectArea[3].top = m_nViewTop + m_nPos;
				m_rectArea[3].bottom = m_rectArea[3].top + m_nBarHeight;

				if( m_pScrollView )
					m_pScrollView->NotifyVerticalScrollPosChanged( m_nPos, m_nViewBottom - m_nViewTop - m_nBarHeight );
			}
		}

		if( yPos >= 0 && yPos <= m_nHeight )
		{
			switch( m_dwMouseArea )
			{
			case Area_LineL:
				m_nPos = 0;
				break;
			case Area_PageL:
				m_nPos -= 10;
				break;
			case Area_PageW:
				m_nPos += 10;
				break;
			case Area_LineW:
				m_nPos = m_nViewBottom - m_nBarHeight;
				break;
			}
			
			m_nPos = max( 0, m_nPos );
			m_nPos = min( m_nViewBottom - m_nViewTop - m_nBarHeight, m_nPos );

			m_rectArea[3].top = m_nViewTop + m_nPos;
			m_rectArea[3].bottom = m_rectArea[3].top + m_nBarHeight;

			if( m_pScrollView )
				m_pScrollView->NotifyVerticalScrollPosChanged( m_nPos, m_nViewBottom - m_nViewTop - m_nBarHeight );
		}

		m_bMouseDown = FALSE;
		m_dwMouseArea = Area_Null;

		for( DWORD dwArea = Area_LineL, nIndex = 0; dwArea <= Area_LineW; dwArea *= 2, nIndex++ )
		{
			if( PtInRect( xPos, yPos, m_rectArea[nIndex] ) )
				m_dwMouseArea = dwArea;
		}

		::InvalidateRect( m_hWnd, NULL, FALSE );
		return TRUE;
	}

	LRESULT CVerticalScrollBar::OnMouseMove( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
	{
		INT xPos = (INT)(LOWORD(lParam)), yPos = (INT)(HIWORD(lParam));
	
		BOOL bRefresh = FALSE;
		if( m_bMouseDown && m_dwMouseArea == Area_Bar )
		{
			if( yPos >= m_nViewTop && yPos <= m_nViewBottom )
			{
				m_nPos += (yPos - m_nMousePos);
				m_nMousePos = yPos;

				m_nMousePos = min( m_nMousePos, m_nViewBottom );
				m_nMousePos = max( m_nMousePos, m_nViewTop );

				m_nPos = max( 0, m_nPos );
				m_nPos = min( m_nViewBottom - m_nViewTop - m_nBarHeight, m_nPos );

				m_rectArea[3].top = m_nViewTop + m_nPos;
				m_rectArea[3].bottom = m_rectArea[3].top + m_nBarHeight;

				if( m_pScrollView )
					m_pScrollView->NotifyVerticalScrollPosChanged( m_nPos, m_nViewBottom - m_nViewTop - m_nBarHeight );

				bRefresh = TRUE;
			}
		}
		else
		{
			for( INT nIndex = 0; nIndex < 6; nIndex++ )
			{
				DWORD dwArea = 1 << nIndex;
				if( PtInRect( xPos, yPos, m_rectArea[nIndex] ) )
				{
					m_dwMouseArea = dwArea;
					bRefresh = TRUE;
				}
			}
		}

		if( bRefresh )
			::InvalidateRect( m_hWnd, NULL, FALSE );

		return TRUE;
	}

	LRESULT CVerticalScrollBar::OnMouseLeave( UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled )
	{
		if( !(m_bMouseDown && m_dwMouseArea == Area_Bar) )
			m_bMouseDown = FALSE;

		m_dwMouseArea = Area_Null;
		
		::InvalidateRect( m_hWnd, NULL, FALSE );
		return TRUE;
	}

	void CVerticalScrollBar::InitAreaRect()
	{
		for( INT i = 0; i < 6; i++ )
		{
			memset( &(m_rectArea[i]), 0, sizeof(RECT) );
			m_rectArea[i].right = m_nWidth;
		}

		INT nItemHeight = m_nItemHeight / 3;
		if( HasArea( Area_LineL ) )
		{
			m_rectArea[0].top = 0;
			m_rectArea[0].bottom = m_rectArea[0].top + nItemHeight;

			m_nViewTop += nItemHeight;
		}

		if( HasArea( Area_PageL ) )
		{
			m_rectArea[1].top = m_rectArea[0].bottom;
			m_rectArea[1].bottom = m_rectArea[1].top + nItemHeight;

			m_nViewTop += nItemHeight;
		}

		if( HasArea( Area_LineW ) )
		{
			m_rectArea[5].bottom = m_nHeight;
			m_rectArea[5].top = m_rectArea[5].bottom - nItemHeight;
			
			m_nViewBottom -= nItemHeight;
		}

		if( HasArea( Area_PageW ) )
		{
			m_rectArea[4].bottom = m_rectArea[5].top;
			m_rectArea[4].top = m_rectArea[4].bottom - nItemHeight;
		
			m_nViewBottom -= nItemHeight;
		}

		if( HasArea( Area_Bg ) )
		{
			m_rectArea[2].top = m_nViewTop;
			m_rectArea[2].bottom = m_nViewBottom;
		}

		if( HasArea( Area_Bar ) )
		{
			m_rectArea[3].top = m_nViewTop + m_nPos;
			m_rectArea[3].bottom = m_rectArea[3].top + m_nBarHeight;
		}
	}

	BOOL CVerticalScrollBar::PtInRect( INT nPosX, INT nPosY, RECT &rect )
	{
		return nPosX >= rect.left && nPosX <= rect.right && nPosY >= rect.top && nPosY <= rect.bottom;
	}
}