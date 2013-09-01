//////////////////////////////////////////////////////////////////////////
//   File Name: bkwndcombo.h
// Description: Combo Control
//     Creator: skylly
//     Version: 2012.3.29 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////
#pragma once 
#include <vector>
#include "combo/popuplistwnd.h"
#include "combo/tracktooltip.h"

#define WM_USER_KCOMBOBOX				(WM_USER + 1235)  //通知主窗口选择事件

typedef struct tagComBoItem{
	ATL::CString strWebUrl;
	ATL::CString strWebName;
} COMBOITEM;

class KComboBoxPopList : public KPopUpListWnd
{
public:

	KComboBoxPopList()
	{
	}

	~KComboBoxPopList()
	{
	}

	//一般pop使用
	BOOL PopUp( int xPos, int yPos, int nWidth )
	{
		ASSERT(m_hWnd);

		CRect newRect( xPos, yPos, xPos + nWidth, yPos );
		newRect.bottom += m_vecText.size() * GetItemHeight();

		SetItemWidth( nWidth );

		MoveWindow( newRect, TRUE );
		ShowWindow( SW_SHOWNORMAL );
		SetCapture();

		return TRUE;
	}

	BOOL IsPopUp()
	{
		return IsWindowVisible();
	}

	BOOL HideWnd()
	{
		ASSERT(m_hWnd);
		ShowWindow(SW_HIDE);
		ReleaseCapture();

		return TRUE;
	}

	void SetBorderStyle( COLORREF clr1, COLORREF clr2, COLORREF clr3, COLORREF clrSel)
	{
		m_clrBorder1	= clr1;
		m_clrBorder2	= clr2;
		m_clrBorder3	= clr3;
		m_clrSel		= clrSel;
	}

protected:

	void DrawBkGnd( CDCHandle& dc, int& xPos, int& yPos, COLORREF clrSel )
	{
		CRect rect;
		GetClientRect( &rect );
		dc.FillSolidRect( rect, RGB(0xFF, 0xFF, 0xFF));

		CRect rectSel( rect );
		if ( GetCurIndex() != -1 )
		{
			rectSel.top = GetCurIndex() * GetItemHeight() ;
			rectSel.bottom = ( GetCurIndex() + 1 ) * GetItemHeight();
			dc.FillSolidRect( rectSel, clrSel );
		}
	}

	void DrawBorder( CDCHandle &dc )
	{
		CRect rect;
		GetClientRect( &rect );

		CPen pen;
		HPEN hOldPen = NULL;
		pen.CreatePen( PS_SOLID, 1, m_clrBorder1 );

		hOldPen = dc.SelectPen( pen );
		dc.MoveTo( rect.left, rect.top );
		dc.LineTo( rect.left, rect.bottom - 1 );
		dc.LineTo( rect.right - 1, rect.bottom - 1 );
		dc.LineTo( rect.right - 1, rect.top  );

		if ( hOldPen )
			dc.SelectPen( hOldPen );
	}

	void DrawBorderComboBox( CDCHandle &dc )
	{
		CRect rect;
		GetClientRect( &rect );

		CPen pen;
		HPEN hOldPen = NULL;

		pen.CreatePen( PS_INSIDEFRAME, 1, RGB(133, 228, 255) );
		//pen.CreatePen( PS_SOLID, 1, m_clrBorder1 );

		hOldPen = dc.SelectPen( pen );
		dc.MoveTo( rect.left, rect.top);
		dc.LineTo( rect.left, rect.bottom - 1 );
		dc.LineTo( rect.right - 1, rect.bottom - 1 );
		dc.LineTo( rect.right - 1, rect.top );

		if ( hOldPen )
			dc.SelectPen( hOldPen );
	}

	void DrawBorderNormal( CDCHandle &dc )
	{
		CRect rect;
		GetClientRect( &rect );

		CBrush brush( ::CreateSolidBrush( m_clrBorder1 ) );
		dc.FrameRect( rect, brush );
	}

	virtual void DrawItemText( CDCHandle &dc, int& xPos, int& yPos )
	{
		CFont font( GetNormalFont() );
		HFONT hOldFont = dc.SelectFont( font );

		CRect rect;
		GetClientRect( &rect );
		rect.left += 4;

		dc.SetBkMode( TRANSPARENT );
		for ( UINT i = 0; i < m_vecText.size(); i ++ )
		{
			rect.top = i * GetItemHeight();
			rect.bottom = ( i + 1 ) * GetItemHeight();
			dc.DrawText( m_vecText[i], 
				m_vecText[i].GetLength(), 
				&rect, 
				DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS );
		}

		if ( hOldFont )
		{
			dc.SelectFont( hOldFont );
		}
	}

protected:

	COLORREF	m_clrBorder1;
	COLORREF	m_clrBorder2;
	COLORREF	m_clrBorder3;
};

enum{
	enum_TYPE_NONE			= 0x0000,
	enum_TYPE_EDIT			= 0x0001,	

	enum_TYPE_TIP			= 0x0002,
	enum_TYPE_LEFTLINE		= 0x0004,
	enum_TYPE_READONLY		= 0x0008,   //只读编辑框 仅有enum_TYPE_EDIT时才生效
};

#include "bkwndnotify.h"

class CbkCombo : public CBkWindow
{
	BKOBJ_DECLARE_CLASS_NAME(CbkCombo, "combo")

		CbkCombo() :
	m_pImg(NULL)
		, m_dwFont(0)
		, hPenNormal(NULL)
		, hPenFocus(NULL)
		, m_hWndEditor(NULL)
		, m_hBkBrush(NULL)
		, m_bFocused(false)
		, m_bMouseOver(false)
		, m_bMouseBtn(false)
		, m_bEnabled(true)  //之前忘了赋初值
		, m_uMaxChar(0)
		, m_bReadOnly(false)
		, m_bNumberMode(false)
		, m_bMultiLine(false)
		, m_bForever(true)   //是否永存
		, m_bPasswordMode(FALSE)
		, m_cPasswordChar(_T('*'))
		,	m_strGroup(_T(""))
		,m_pPopList(NULL),
		m_clrBorder1(RGB(78, 160, 209)),//m_clrBorder1(RGB(0x76,0x84,0x8F)),
		m_clrBorder2(RGB(0xDA,0xDB,0xDD)),
		m_clrBorder3(RGB(0xEE,0xEE,0xF0)),
		m_clrListSel(RGB(233, 245, 255)),//高亮项颜色//m_clrListSel(RGB(0xE6,0xF6,0xE9)),
		m_nCurSel(0),
		m_nFontSize(16),
		m_strTip(_T("")),
		m_nType(/* enum_TYPE_EDIT | enum_TYPE_TIP | */enum_TYPE_LEFTLINE )
	{
		//	//pCombo->SetType(enum_TYPE_EDIT |enum_TYPE_READONLY | enum_TYPE_LEFTLINE );  // | 
		m_pPopList = new KComboBoxPopList;
	}
	~CbkCombo()
	{
		BkWnds::UnregisterEditGroup(this, m_strGroup);
		CLear();
	}

	bool IsEnabled()
	{
		return m_bEnabled;
	}

	BOOL IsPasswordMode()
	{
		return m_bPasswordMode;
	}

	TCHAR GetPasswordChar() const
	{
		return m_cPasswordChar;
	}

	// Create children
	virtual BOOL Load(TiXmlElement* pTiXmlElem)
	{  
		if (!CBkWindow::Load(pTiXmlElem))
			return FALSE;

		CStringA strValue = pTiXmlElem->Value();
		if (strValue != "combo")
		{
			//             _Redraw();
			return FALSE;
		}

		int nItemHeight = m_dlgpos.Bottom.nPos - m_dlgpos.Top.nPos;
		if (m_pPopList)
		{
			m_pPopList->SetItemHeight( nItemHeight );
			m_pPopList->SetBorderStyle( m_clrBorder1, m_clrBorder2, m_clrBorder3, m_clrListSel);
		}

		return BkWnds::RegisterEditGroup(this, m_strGroup);
	}

	void OnDestroy()
	{
	}

	void SetType( int nType )
	{
		m_nType = nType;
	}

	void AddType( int nType )
	{
		m_nType |= m_nType;
	}

	void SetCurSel( int nIndex )
	{
		m_nCurSel = nIndex;
		ATLASSERT( m_nCurSel < m_vecItem.size() );

		if( m_nCurSel < m_vecItem.size() )
		{
			COMBOITEM* pItem = m_vecItem[m_nCurSel];
			if (pItem)
			{
				m_strInnerText = pItem->strWebName;
			}

			if( enum_TYPE_EDIT & m_nType && m_hWndEditor)
			{
				::SetWindowText(m_hWndEditor, pItem->strWebUrl );
			}
		}
	}

	int GetCurSel()
	{
		return m_nCurSel;
	}

	void DrawBorder( CDCHandle& dc )
	{
		COLORREF colorbd = 0;
		CRect rc = m_rcWindow;
		HPEN hPenOld = NULL;
		if (m_bMouseOver)
		{		
			colorbd = RGB(133, 228, 255);
			if (!hPenFocus)
			{
				hPenFocus = CreatePen(PS_INSIDEFRAME, 2, colorbd);
			}
			hPenOld = dc.SelectPen(hPenFocus);
		}
		else
		{		
			colorbd = RGB(78, 160, 209);
			if (!hPenNormal)
			{
				hPenNormal = CreatePen(PS_INSIDEFRAME, 1, colorbd);
			}
			hPenOld = dc.SelectPen(hPenNormal);
		}
		HBRUSH hBrushOld = dc.SelectBrush((HBRUSH)::GetStockObject(HOLLOW_BRUSH));
		dc.Rectangle(rc);
		dc.SelectBrush(hBrushOld);
		dc.SelectPen(hPenOld);
	}

	void DrawBtn(CDCHandle& dc)
	{
		CRect rect = m_rcWindow;

		CRgn rgn;
		CPoint point[3];
		int nHeight = rect.Height() / 3;

		point[0].x = rect.right - 3 * nHeight + 2 ;
		point[0].y = rect.top + nHeight + 1;

		point[1].x = rect.right - nHeight + 1;
		point[1].y = rect.top + nHeight + 1;

		point[2].x = rect.right - 2 * nHeight + 1;
		point[2].y = rect.top + 2 * nHeight + 1;

		rgn.CreatePolygonRgn(point, 3, ALTERNATE );
		CBrush brush;

		brush = ::CreateSolidBrush((m_bMouseOver && m_bMouseBtn) ? RGB(133, 228, 255) : m_clrBorder1);
		dc.FillRgn( rgn, brush );

		if( enum_TYPE_LEFTLINE & m_nType )
		{
			CPen pen;
			pen.CreatePen( PS_SOLID, 1, m_clrBorder1 );
			HPEN hOldPen = dc.SelectPen( pen );
			dc.MoveTo( rect.right - 4 * nHeight + 2, rect.top );
			dc.LineTo( rect.right - 4 * nHeight + 2, rect.bottom );
			if( hOldPen )
				dc.SelectPen( hOldPen );
		}
	}

	virtual BOOL NeedRedrawWhenStateChange()
	{
		return TRUE;
	}

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = ::DefWindowProc(m_hWndEditor, uMsg, wParam, lParam);
		if (!m_bForever)
			::PostMessage(m_hWndEditor, WM_CLOSE, 0, 0);
		return lRes;
	}

	LRESULT OnEditChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// Copy text back
		int cchLen = ::GetWindowTextLength(m_hWndEditor) + 1;
		LPTSTR pstr = static_cast<LPTSTR>(_alloca(cchLen * sizeof(TCHAR)));
		ATLASSERT(pstr);
		if( pstr == NULL ) return 0;
		::GetWindowText(m_hWndEditor, pstr, cchLen);
		m_strInnerText = pstr;
		//刷新bkwin控件
		NotifyInvalidate();
		//SendNotify(m_pOwner, _T("textchanged"));
		return 0;
	}

	COLORREF GetTextColor()
	{
		return RGB(0, 0, 0);
	}

	COLORREF GetNativeEditBkColor()
	{
		return RGB(255, 255, 255);
	}

	BOOL StartTrackMouseLeave()
	{
		TRACKMOUSEEVENT tme = { 0 };
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWndEditor;
		return _TrackMouseEvent(&tme);
	}

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = 0;
		bHandled = TRUE;

		if (uMsg == WM_KILLFOCUS ) 
			lRes = OnKillFocus(uMsg, wParam, lParam, bHandled);
		else if (uMsg == OCM_COMMAND) 
		{
			if (HIWORD(wParam) == EN_CHANGE)
				lRes = OnEditChanged(uMsg, wParam, lParam, bHandled);
			else if( HIWORD(wParam) == EN_UPDATE ) 
			{
				RECT rcClient;
				::GetClientRect(m_hWndEditor, &rcClient);
				::InvalidateRect(m_hWndEditor, &rcClient, FALSE);
			}
		}
		else if (uMsg == WM_LBUTTONDOWN)
		{
			CRect rect = m_rcWindow;
			POINT pt;
			pt.x = rect.left;
			pt.y = rect.bottom;
			//  
			ClientToScreen(m_hWndContainer, &pt );
			if( m_pPopList )
			{
				if( m_pPopList->IsWindow())
				{
					m_pPopList->SetCurIndex(m_nCurSel);
					CRect rcEdit;
					::GetWindowRect(m_hWndEditor, &rcEdit);
					m_pPopList->PopUp(pt.x, pt.y, rcEdit.Width());
				}
			}
		}
		else if (uMsg == WM_MOUSEWHEEL)
		{
			WORD fwKeys   =   LOWORD(wParam);   /*   key   flags   */     
			short zDelta   =   (short)   HIWORD(wParam);     
			/*   wheel   rotation   */   
			short xPos   =   (short)   LOWORD(lParam);     
			/*   horizontal   position   of   pointer   */   
			short yPos   =   (short)   HIWORD(lParam);     
			/*   vertical   position   of   pointer   */     
			bHandled = FALSE;
			bool bModify = false;
			short sOff = zDelta / WHEEL_DELTA;
			if (sOff <= -1)
			{
				if (m_nCurSel < (m_vecItem.size() - 1))
				{
					m_nCurSel++;
					bModify = true;
				}

			}
			else if (sOff >= 1)
			{
				if (m_nCurSel > 0)
				{
					m_nCurSel--;
					bModify = true;
				}
			}
			if (bModify)
			{
				COMBOITEM* pItem = m_vecItem[m_nCurSel];
				if (::IsWindow(m_hWndEditor) && pItem )
				{
					::SetWindowText(m_hWndEditor, pItem->strWebUrl);
					::SendMessage(m_hWndEditor,  EM_SETSEL, (0), (lstrlen(pItem->strWebUrl)));

					NotifyInvalidate();
				}
			}
		}
		else if (uMsg == WM_MOUSELEAVE)
		{
			m_bMouseOver = false;
			m_bMouseBtn = false;
			m_trackTooltip.ActiveTooltip( FALSE );
			//刷新bkwin控件
			NotifyInvalidate();
		}
		else if (uMsg == WM_MOUSEMOVE)
		{
			m_bMouseOver = true;

			if( enum_TYPE_TIP & m_nType )
			{
				m_trackTooltip.ActiveTooltip( TRUE );
				CRect rect = m_rcWindow;
				//GetWindowRect( rect );
				m_trackTooltip.ShowText( CPoint( rect.left - 12, rect.top - 45 ), m_strTip, -1 );
			}
			m_bMouseBtn = false;
			//刷新bkwin控件
			NotifyInvalidate();

			StartTrackMouseLeave();
		}
		else if( uMsg == WM_KEYDOWN && TCHAR(wParam) == VK_RETURN ) 
		{
			//SendNotify(m_pOwner, _T("return"));
		}
		else if( uMsg == OCM__BASE + WM_CTLCOLOREDIT  || uMsg == OCM__BASE + WM_CTLCOLORSTATIC ) 
		{
			if( GetNativeEditBkColor() == 0xFFFFFFFF ) return NULL;
			::SetBkMode((HDC)wParam, TRANSPARENT);
			DWORD dwTextColor = GetTextColor();
			::SetTextColor((HDC)wParam, RGB(GetBValue(dwTextColor),GetGValue(dwTextColor),GetRValue(dwTextColor)));
			if( m_hBkBrush == NULL ) {
				DWORD clrColor = GetNativeEditBkColor();
				m_hBkBrush = ::CreateSolidBrush(RGB(GetBValue(clrColor), GetGValue(clrColor), GetRValue(clrColor)));
			}
			return (LRESULT)m_hBkBrush;
		}
		else 
		{
			bHandled = FALSE;
		}
		return lRes;
	}

	void OnFinalMessage(HWND hWnd)
	{
		// Clear reference and die
		if( m_hBkBrush != NULL ) 
			::DeleteObject(m_hBkBrush);

		if ( m_pPopList )
		{
			if( m_pPopList->IsWindow() )
				m_pPopList->DestroyWindow();

			delete m_pPopList;
			m_pPopList = NULL;
		}

		if( m_nType & enum_TYPE_EDIT )
		{
			if( ::IsWindow(m_hWndEditor) )
				::DestroyWindow(m_hWndEditor);
		}

		if( m_nType & enum_TYPE_TIP )
			m_trackTooltip.UnInit();

	}

	static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		CbkCombo* pThis = NULL;
		if (uMsg == WM_NCCREATE) 
		{
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			pThis = static_cast<CbkCombo*>(lpcs->lpCreateParams);
			::SetProp(hWnd, _T("WndX"), (HANDLE) pThis);
			pThis->m_hWndEditor = hWnd;
		} 
		else
		{
			pThis = reinterpret_cast<CbkCombo*>(::GetProp(hWnd, _T("WndX")));
			if (uMsg == WM_NCDESTROY && pThis != NULL) 
			{
				LRESULT lRes = ::CallWindowProc(pThis->m_OldWndProc, hWnd, uMsg, wParam, lParam);
				// if( pThis->m_bSubclassed ) pThis->Unsubclass();
				::SetProp(hWnd, _T("WndX"), NULL);
				pThis->m_hWndEditor = NULL;
				pThis->OnFinalMessage(hWnd);
				return lRes;
			}
		}
		if (pThis != NULL) 
		{ 
			BOOL bHandled;
			pThis->HandleMessage(uMsg, wParam, lParam, bHandled);
		} 
		return ::CallWindowProc(pThis->m_OldWndProc, hWnd, uMsg, wParam, lParam);
	}

	LPCTSTR GetSuperClassName() const
	{
		return WC_EDIT;
	}

	LPCTSTR GetWindowClassName() const
	{
		return _T("BkCombo");
	}

	//注册窗口类
	bool RegisterSuperclass()
	{
		// Get the class information from an existing
		// window so we can subclass it later on...
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		if( !::GetClassInfoEx(NULL, GetSuperClassName(), &wc) ) {
			if( !::GetClassInfoEx((HINSTANCE)&__ImageBase, GetSuperClassName(), &wc) ) {
				ATLASSERT(!"Unable to locate window class");
				return NULL;
			}
		}
		m_OldWndProc = wc.lpfnWndProc;
		wc.lpfnWndProc = &CbkCombo::__ControlProc;
		wc.hInstance = (HINSTANCE)&__ImageBase;
		wc.lpszClassName = GetWindowClassName();
		ATOM ret = ::RegisterClassEx(&wc);
		ATLASSERT(ret!=NULL || ::GetLastError()==ERROR_CLASS_ALREADY_EXISTS);
		return ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
	}
#define UI_CLASSSTYLE_DIALOG     (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)
	UINT GetClassStyle() const { return UI_CLASSSTYLE_DIALOG; };

	//无用
	static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		CbkCombo* pThis = NULL;
		if( uMsg == WM_NCCREATE ) {
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			pThis = static_cast<CbkCombo*>(lpcs->lpCreateParams);
			pThis->m_hWndEditor = hWnd;
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(pThis));
		} 
		else
		{
			pThis = reinterpret_cast<CbkCombo*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
			if( uMsg == WM_NCDESTROY && pThis != NULL ) {
				LRESULT lRes = ::CallWindowProc(pThis->m_OldWndProc, hWnd, uMsg, wParam, lParam);
				::SetWindowLongPtr(pThis->m_hWndEditor, GWLP_USERDATA, 0L);
				//if( pThis->m_bSubclassed ) pThis->Unsubclass();
				pThis->m_hWndEditor = NULL;
				pThis->OnFinalMessage(hWnd);
				return lRes;
			}
		}
		if (pThis != NULL) 
		{ 
			BOOL bHandled;
			pThis->HandleMessage(uMsg, wParam, lParam, bHandled);
		} 
		return ::CallWindowProc(pThis->m_OldWndProc, hWnd, uMsg, wParam, lParam);
	}

	//无用
	bool RegisterWindowClass()
	{
		WNDCLASS wc = { 0 };
		wc.style = GetClassStyle();
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hIcon = NULL;
		wc.lpfnWndProc = &CbkCombo::__WndProc;
		wc.hInstance = (HINSTANCE)&__ImageBase;
		wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName  = NULL;
		wc.lpszClassName = GetWindowClassName();
		ATOM ret = ::RegisterClass(&wc);
		ATLASSERT(ret!=NULL || ::GetLastError()==ERROR_CLASS_ALREADY_EXISTS);
		return ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
	}

	void InitEditor()
	{
		if (!m_hWndContainer || m_hWndEditor)
			return;

		if (m_nType & enum_TYPE_EDIT)
		{
			DWORD dwStyle = WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_TABSTOP;
			DWORD dwExStyle = 0;
			HMENU hMenu = (HMENU)m_uCmdID;
			CRect rc = m_rcWindow;

			int nBtnWidth = 4 * ( rc.Height() / 3 );
			rc.DeflateRect(2, 2, nBtnWidth-2, 2);  //留出边框
			if (IsPasswordMode()) 
				dwStyle |= ES_PASSWORD;

			if (GetSuperClassName() != NULL && !RegisterSuperclass()) return;
			if (GetSuperClassName() == NULL && !RegisterWindowClass()) return;

			m_hWndEditor = ::CreateWindowEx(dwExStyle, GetWindowClassName(), NULL, dwStyle, rc.left, rc.top, rc.Width(),rc.Height(), m_hWndContainer,(HMENU)hMenu,(HINSTANCE)&__ImageBase, this);
			if (!m_hWndEditor)
			{
				DWORD dd = GetLastError();
				ATLVERIFY(FALSE);
				return;
			}
			
			if (enum_TYPE_READONLY & m_nType)
				m_bReadOnly = true;

			::SendMessage(m_hWndEditor, WM_SETFONT, (WPARAM)((HFONT)BkFontPool::GetFont(LOWORD(m_dwFont))), MAKELPARAM(TRUE, 0));  

			int cchMax = 100;
			::SendMessage(m_hWndEditor, EM_LIMITTEXT, (WPARAM)(cchMax), 0L);
			if (IsPasswordMode()) 
				::SendMessage(m_hWndEditor, EM_SETPASSWORDCHAR, (WPARAM)(UINT)(GetPasswordChar()), 0L);
			::SetWindowText(m_hWndEditor, m_strInnerText);
			::SendMessage(m_hWndEditor, EM_SETMODIFY, (WPARAM)(UINT)(FALSE), 0L);
			::SendMessage(m_hWndEditor, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM(0, 0));
			bool bEnabled = IsEnabled();
			::EnableWindow(m_hWndEditor, bEnabled);
			::SendMessage(m_hWndEditor, EM_SETREADONLY, (WPARAM)(BOOL)(m_bReadOnly), 0L);
			::ShowWindow(m_hWndEditor, SW_SHOWNOACTIVATE);//
			::SetFocus(m_hWndEditor); 
		}		
		if (m_nType & enum_TYPE_TIP)
		{
			m_trackTooltip.Init( m_hWndContainer );
			m_trackTooltip.SetRelay( TRUE, 500 );
		}
	}

	void DrawBkColor(CDCHandle& dc)
	{
		COLORREF colorbk = 0;
		if (m_bEnabled)
		{
			colorbk  = RGB(255, 255, 255);
		}
		else
		{
			colorbk = RGB(244, 244, 244);
		}

		dc.SetBkColor(colorbk);
		dc.ExtTextOut(0, 0, ETO_OPAQUE, &m_rcWindow, NULL, 0, NULL);
	}

	void DrawBkImage(CDCHandle& dc)
	{
	}

	void DrawStatusImage(CDCHandle& dc)
	{
		if (m_pImg == NULL)
		{
			//BkPngPool::_LoadPNGImageFromResourceID(3005, m_pImg);
		}

		Gdiplus::Graphics graphics(dc);
		CRect rc = m_rcWindow;
		//根据区域大小显示图片
		graphics.DrawImage(m_pImg, Gdiplus::Rect(rc.left, rc.top, rc.Width(), rc.Height()), 0, 0, rc.Width(), rc.Height(), Gdiplus::UnitPixel);
	}

	void DrawText(CDCHandle& dc)
	{	
		CRect rect = m_rcWindow;
		rect.left += 4;
		rect.top += 2;
		rect.bottom -= 2;
		rect.right -= 2;

		rect.right -= rect.Height();

		if( enum_TYPE_EDIT & m_nType )
		{

		}
		else
		{
			HFONT hOldFont = dc.SelectFont( BkFontPool::GetFont(LOWORD(m_dwFont)) );
			int nMode = dc.SetBkMode( TRANSPARENT );
			dc.DrawText( m_strInnerText, -1, rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE );
			dc.SetBkMode( nMode );
			if( hOldFont )
				dc.SelectFont( hOldFont );
		}
	}

	// 绘制循序：背景颜色->背景图->状态图->文本->边框
	void OnPaint(CDCHandle dc)
	{
		// dc.SetBkMode(TRANSPARENT);
		//drawText
		DrawBkColor(dc);
		DrawBkImage(dc);
		DrawStatusImage(dc);
		DrawText(dc);	
		//draw bmp
		DrawBtn( dc );
		DrawBorder(dc);
	} 

	void SetFocus()
	{
		m_bFocused = true;
	}

	void OnLButtonDown(UINT nFlags, CPoint point)
	{ 
		if( IsEnabled() )
		{
			if (m_hWndEditor == NULL)
			{
				InitEditor(); 
			}
			m_bFocused = true;
			if (m_rcWindow.PtInRect(point) )
			{
				if (m_hWndEditor)
				{//edit模式
					int nSize = GetWindowTextLength(m_hWndEditor);
					if( nSize == 0 )
						nSize = 1;

					::SendMessage(m_hWndEditor,  EM_SETSEL, (0), (nSize));
				}
				else
				{//非edit模式
					CRect rc = m_rcWindow;
					int nBtnWidth = 4 * ( rc.Height() / 3 );
					rc.DeflateRect(0, 0, nBtnWidth-2, 0);  //留出边框

					POINT pt;
					GetCursorPos(&pt);
					ScreenToClient(m_hWndContainer, &pt);
					bool bInRect = false;
					if (rc.PtInRect(pt))
					{//在edit范围
						return;
					}
				}

				CRect rect = m_rcWindow;
				POINT pt;
				pt.x = rect.left;
				pt.y = rect.bottom;
				//  
				ClientToScreen(m_hWndContainer, &pt );

				if( m_pPopList )
				{
					if( m_pPopList->IsWindow())
					{
						m_pPopList->SetCurIndex(m_nCurSel);
						m_pPopList->PopUp(pt.x, pt.y, m_rcWindow.Width());
					}
				}
			}

		}//if( IsEnabled() )
	}

	void OnMouseMove(UINT nFlags, CPoint point)
	{
		if (m_bEnabled)
		{
			m_bMouseOver = true;

			if( enum_TYPE_TIP & m_nType )
			{
				m_trackTooltip.ActiveTooltip( TRUE );
				CRect rect = m_rcWindow;
				//GetWindowRect( rect );
				m_trackTooltip.ShowText( CPoint( rect.left - 12, rect.top - 45 ), m_strTip, -1 );
			}

			CRect rc = m_rcWindow;
			int nBtnWidth = 4 * ( rc.Height() / 3 );
			rc.DeflateRect(0, 0, nBtnWidth-2, 0);  //留出边框

			bool bOldMouse = m_bMouseBtn;
			if (rc.PtInRect(point))
			{
				m_bMouseBtn = false;
			}
			else
			{
				m_bMouseBtn = true;
			}
			if (bOldMouse != m_bMouseBtn)
				NotifyInvalidate();
		}
	}

	HWND _GetRealWindow()
	{		
		if (m_bForever && m_hWndEditor == NULL)
		{
			InitEditor(); 
		}
		return m_hWndEditor;
	}

	void OnWindowPosChanged(LPWINDOWPOS lpWndPos)
	{
		CRect rcOldWnd = m_rcWindow;

		__super::OnWindowPosChanged(lpWndPos);

		if (rcOldWnd != m_rcWindow)
		{
			//移动窗口位置
			HWND hWndReal = _GetRealWindow();
			//by skylly 不让后面的子窗口排到前面的子窗口前面

			CRect rc = m_rcWindow;
			int nBtnWidth = 4 * ( rc.Height() / 3 );
			rc.DeflateRect(2, 2, nBtnWidth-2, 2);  //留出边框

			//::SetWindowPos(hWndReal, HWND_TOP, m_rcWindow.left, m_rcWindow.top, m_rcWindow.Width(), m_rcWindow.Height(), SWP_NOREDRAW);
			::SetWindowPos(hWndReal, HWND_TOP, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER | SWP_NOREDRAW);

			BKNMREALWNDRESIZED nms;
			nms.hdr.code = BKNM_REALWND_RESIZED;
			nms.hdr.hwndFrom = m_hWndContainer;
			nms.hdr.idFrom = ::GetDlgCtrlID(m_hWndContainer);
			nms.uItemID = GetCmdID();
			nms.rcWnd = rc;

			::SendMessage(m_hWndContainer, WM_NOTIFY, (LPARAM)nms.hdr.idFrom, (WPARAM)&nms);

			//显示窗口
			if (::IsWindowVisible(hWndReal))
			{
				CRect rcUpdate = rc;
				rcUpdate.MoveToXY(0, 0);
				//::RedrawWindow(_GetRealWindow(), rcUpdate, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				//::RedrawWindow(hWndReal, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ERASENOW);
				::InvalidateRect(hWndReal, NULL, TRUE);
				::SetWindowPos(hWndReal, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED);
			}
		}
	}

	void ShowRealWindow(BOOL bShow)
	{
		CRect rc;
		GetClientRect(_GetRealWindow(), rc);
		if (rc != m_rcWindow)
		{            
			rc = m_rcWindow;
			int nBtnWidth = 4 * ( rc.Height() / 3 );
			rc.DeflateRect(2, 2, nBtnWidth-2, 2);  //留出边框

			::SetWindowPos(_GetRealWindow(), HWND_TOP, rc.left, rc.top, rc.Width(), rc.Height(),  SWP_NOZORDER | SWP_NOREDRAW);
		}
		::ShowWindow(_GetRealWindow(), bShow ? SW_SHOW : SW_HIDE);
	}

	void OnMouseLeave()
	{
		m_bMouseOver = false;
		m_trackTooltip.ActiveTooltip( FALSE );
	}

	virtual void SetCursor()
	{
		CRect rc = m_rcWindow;
		int nBtnWidth = 4 * ( rc.Height() / 3 );
		rc.DeflateRect(0, 0, nBtnWidth-2, 0);  //留出边框

		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(m_hWndContainer, &pt);
		bool bInRect = false;
		if (rc.PtInRect(pt))
		{
			bInRect = true;
		}
		else
		{
		}
		::SetCursor(::LoadCursor(NULL, (m_bMouseOver && bInRect) ? IDC_IBEAM : IDC_ARROW));
	}

	LRESULT OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{
		/*   wheel   rotation   */   
		long xPos   =   pt.x;
		/*   horizontal   position   of   pointer   */   
		long yPos   =   pt.y;
		/*   vertical   position   of   pointer   */     
		SetMsgHandled(TRUE);
		bool bModify = false;
		short sOff = zDelta / WHEEL_DELTA;
		if (sOff <= -1)
		{
			if (m_nCurSel < (m_vecItem.size() - 1))
			{
				m_nCurSel++;
				bModify = true;
			}

		}
		else if (sOff >= 1)
		{
			if (m_nCurSel > 0)
			{
				m_nCurSel--;
				bModify = true;
			}
		}
		if (bModify)
		{
			COMBOITEM* pItem = m_vecItem[m_nCurSel];
			if (::IsWindow(m_hWndEditor) && pItem )
			{
				::SetWindowText(m_hWndEditor, pItem->strWebUrl);
				::SendMessage(m_hWndEditor,  EM_SETSEL, (0), (lstrlen(pItem->strWebUrl)));
			}
			m_strInnerText = pItem->strWebUrl;
			NotifyInvalidate();
			m_pPopList->SetCurIndex(m_nCurSel);
			m_pPopList->Invalidate();
		}

		return FALSE;
	}

	LRESULT OnUserSelect(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam/*, BOOL& bHandled*/)
	{
		m_nCurSel = (int) wParam;
		m_strInnerText = (LPCTSTR) lParam;

		//m_bChildSel = TRUE;

		::SendMessage( m_hWndContainer, WM_USER_KCOMBOBOX, wParam, lParam );

		if( m_nCurSel < m_vecItem.size() )
		{
			COMBOITEM* pItem = m_vecItem[m_nCurSel];
			if( IsWindow(m_hWndEditor) && pItem )
				::SetWindowText(m_hWndEditor, pItem->strWebUrl );

		}
		NotifyInvalidate();
		return TRUE;
	}

	void SetBorderStyle( COLORREF clr1, COLORREF clr2, COLORREF clr3, COLORREF clrSel=RGB(0xE6,0xF6,0xE9))
	{
		m_clrBorder1 = clr1;
		m_clrBorder2 = clr2;
		m_clrBorder3 = clr3;
		m_clrListSel = clrSel;

		if( m_pPopList )
			m_pPopList->SetBorderStyle(clr1, clr2, clr3, clrSel);
	}

	LPCTSTR GetInputWebUrl( )
	{
		ATL::CString strInput;
		if( ::IsWindow(m_hWndEditor) )
			::GetWindowText(m_hWndEditor, strInput.GetBuffer(0), MAX_PATH);

		COMBOITEM* pItem = CheckWebExist( strInput );

		if( pItem )
			m_strInnerText = pItem->strWebUrl;
		else
			m_strInnerText = strInput;

		return m_strInnerText;
	}

	LPCTSTR GetInputWebName( )
	{
		ATL::CString strInput;
		if( ::IsWindow(m_hWndEditor) )
			::GetWindowText(m_hWndEditor, strInput.GetBuffer(0), MAX_PATH);

		COMBOITEM* pItem = CheckWebExist( strInput );

		if( pItem )
			m_strInnerText = pItem->strWebName;
		else
			m_strInnerText = strInput;

		return m_strInnerText;
	}

	void SetInputText( LPCTSTR pszText )
	{
		m_strInnerText = pszText;
		if( ::IsWindow(m_hWndEditor) )
			::SetWindowText(m_hWndEditor, m_strInnerText );
	}

	void SetLabelString( LPCTSTR pszLabel )
	{
		m_strLabel = pszLabel;
	}

	//用户输出
	BOOL AddString( LPCTSTR pszUrl )
	{
		return AddString( pszUrl, pszUrl );
	}

	void OnShowWindow(BOOL bShow, UINT nStatus)
	{
		__super::OnShowWindow(bShow, nStatus);

		if (bShow)
		{
			// 如果父窗口或者父窗口的父窗口隐藏（主要是由于Tab切换），则不显示真实窗口
			CBkWindow* pWnd = this;

			while (TRUE)
			{
				pWnd = BkWnds::GetWindow(pWnd->GetParent());

				if (NULL == pWnd)
					break;

				if (!pWnd->IsVisible())
					return;
			}
		}

		ShowRealWindow(bShow);
	}

	COMBOITEM* CheckWebExist( LPCTSTR pszWeb )
	{
		BOOL bFind = FALSE;

		for ( UINT i = 0; i < m_vecItem.size(); i++ )
		{
			COMBOITEM * pItem = m_vecItem[i];
			if( pItem )
			{
				if( _tcsicmp( pszWeb, pItem->strWebUrl ) == 0 )
				{
					return pItem;
				}

				if( _tcsicmp( pszWeb, pItem->strWebName ) == 0 )
				{
					return pItem;
				}
			}
		}
		return NULL;
	}

private:
	//用于初始化
	BOOL AddInitString( LPCTSTR pszWebUrl, LPCTSTR pszWebName )
	{
		COMBOITEM* pItemFind = CheckWebExist(pszWebUrl);
		//找不到可以添加
		if( pItemFind )
			return FALSE;

		COMBOITEM *pItem = new COMBOITEM;
		pItem->strWebName = pszWebName;
		pItem->strWebUrl = pszWebUrl;
		m_vecItem.push_back( pItem );

		return TRUE;
	}

	BOOL AddString( LPCTSTR pszWebUrl, LPCTSTR pszWebName )
	{
		if (!AddInitString( pszWebUrl, pszWebName))
			return FALSE;

		HBITMAPVEC		vecBmp;
		TEXTVEC			vecText;
		InitWebName( vecText );
		if( m_pPopList)
		{
			if (m_pPopList->IsWindow())
				m_pPopList->DestroyWindow();
			m_pPopList->CreatePopUpList( this, m_hWndContainer, vecBmp, vecText, RGB(0xFF, 0xFF, 0xFF) );
		}
		return TRUE;
	}

public:
	void InitWebName( TEXTVEC& vecText )
	{
		for ( UINT i = 0; i < m_vecItem.size(); i++ )
		{
			COMBOITEM * pItem = m_vecItem[i];
			if( pItem )
			{
				vecText.push_back( pItem->strWebName );
			}
		}
	}

	void CLear()
	{
		for ( UINT i = 0; i < m_vecItem.size(); i++ )
			delete m_vecItem[i];

		m_vecItem.clear();
	}

	int Count()
	{
		return m_vecItem.size();
	}

	BOOL GetExistIndex(LPCTSTR pszWeb, int& nIndex)
	{
		if (NULL == pszWeb)
		{
			return FALSE;
		}

		for ( UINT i = 0; i < m_vecItem.size(); i++ )
		{
			COMBOITEM * pItem = m_vecItem[i];
			if( pItem )
			{
				if( _tcsicmp( pszWeb, pItem->strWebUrl ) == 0 )
				{
					nIndex = i;
					return TRUE;
				}

				if( _tcsicmp( pszWeb, pItem->strWebName ) == 0 )
				{
					nIndex = i;
					return TRUE;
				}
			}
		}

		return FALSE;
	}

protected:
	HBRUSH m_hBkBrush;  //画刷
	HPEN hPenNormal;  //pen
	HPEN hPenFocus;   //pen
	Gdiplus::Image* m_pImg;  //背景图
	DWORD m_dwFont;   //字体

	WNDPROC m_OldWndProc; //原始窗口处理函数
	HWND m_hWndEditor;  //控件句柄

	BOOL m_bPasswordMode; //密码模式
	TCHAR m_cPasswordChar; //密码掩码
	bool m_bEnabled;  //是否激活
	bool m_bFocused; //是否焦点
	bool m_bMouseOver;  //是否鼠标悬停
	bool m_bMouseBtn;  //是否在btn区域
	bool m_bForever;  //是否永存
	//所属分组
	CStringA m_strGroup;
	//下面几个暂时未用到
	bool m_bReadOnly; //是否只读
	bool m_bNumberMode; //是否数字
	bool m_bMultiLine; //是否多行
	UINT m_uMaxChar;  //最大字符数

protected:
	HWND					m_hParent;
	KComboBoxPopList*		m_pPopList;
	//BOOL					m_bChildSel;
	ATL::CString			m_strLabel;
	ATL::CString            m_strTip;

	COLORREF				m_clrBorder1;
	COLORREF				m_clrBorder2;
	COLORREF				m_clrBorder3;
	COLORREF				m_clrListSel;
	std::vector<COMBOITEM*>	m_vecItem;
	UINT					m_nCurSel; 
	KTrackTooltip			m_trackTooltip;
	int						m_nType;
	int                     m_nFontSize;

protected:
	BKWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)  
		MSG_WM_WINDOWPOSCHANGED(OnWindowPosChanged)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
		MSG_WM_MOUSEWHEEL(OnMouseWheel)
		MSG_WM_SHOWWINDOW(OnShowWindow)
		MESSAGE_HANDLER_EX(WM_USER_POPUPLIST, OnUserSelect)
		BKWIN_END_MSG_MAP()

		BKWIN_DECLARE_ATTRIBUTES_BEGIN()
		BKWIN_HEX_ATTRIBUTE("defaultfont", m_dwFont, FALSE)
		BKWIN_INT_ATTRIBUTE("password", m_bPasswordMode, FALSE)
		BKWIN_DECLARE_ATTRIBUTES_END()
};
