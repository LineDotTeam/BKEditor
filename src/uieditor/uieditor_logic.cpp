#include "stdafx.h"
#include "uieditor_dlg.h"
#include "uieditor_logic.h"
#include "component/kcomp_button.h"
#include "component/kcomp_imgbtn.h"
#include "component/kcomp_text.h"
#include "component/kcomp_img.h"

KEditDialogImpl::KEditDialogImpl(HINSTANCE hInstance)
: KEditDialogView(hInstance)
, m_hInstance(hInstance)
, m_uSelItemID(0)
, m_pNowComp(NULL)
, m_hIcon(NULL)
, m_nSelItem(-1)
{

}

KEditDialogImpl::~KEditDialogImpl()
{

}

BOOL KEditDialogImpl::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
    _InitEdit();
    _InitList();
    m_hIcon = ::LoadIcon(m_hInstance, MAKEINTRESOURCE(ICO_DUBA));

    if (m_hIcon != NULL)
    {
        SetIcon(m_hIcon);
        return TRUE;
    }
    return FALSE;
}

void KEditDialogImpl::OnPalette()
{
    SetFocus();
    if (m_uSelItemID != 0)
    {
        IComponent* pCompTmp = _CompFactory();

        if (pCompTmp != NULL)
        {
            m_vecComp.push_back(pCompTmp);

            SetItemCheck(m_uSelItemID, FALSE);
            m_uSelItemID = 0;
            m_pNowComp   = pCompTmp;

            CStringA strPos;
            CPoint   cPoint;

            _TransfromPoint(m_nowPoint, cPoint);
            strPos.Format("%d,%d", cPoint.x, cPoint.y);
            m_pNowComp->SetCompAttrute("pos", strPos.GetString());
        }
    }
    else if (m_nSelItem == -1)
    {
        m_pNowComp = NULL;
    }
    _Redraw();
}

void KEditDialogImpl::OnSubmit()
{
    if (m_pNowComp == NULL)
    {
        return;
    }

    BOOL bIsSet = FALSE;
    CString strTmp;
    std::string strCmd;

    // 不知道有多少属性？
    for (size_t i = 0; i < ATTRUTE_SIZE; ++i)
    {
        m_kEdit[i].GetText(strTmp);
        strCmd = CW2A(strTmp.GetString());
        bIsSet = m_pNowComp->SetCompAttrute(i, strCmd);
        if (!bIsSet)
        {
            break;
        }
    }

    _Redraw();
}

void KEditDialogImpl::OnDelete()
{
    if (m_pNowComp != NULL)
    {
        for (std::vector<IComponent*>::iterator iter = m_vecComp.begin(); iter != m_vecComp.end(); ++iter)
        {
            if (*iter == m_pNowComp)
            {
                m_vecComp.erase(iter);
                m_pNowComp->UninitComp();
                delete m_pNowComp;
                m_pNowComp = NULL;
                break;
            }
        }
    }
    _Redraw();
}

void KEditDialogImpl::OnSelectRadio(UINT uItemId)
{
    m_uSelItemID = uItemId;
}

void KEditDialogImpl::OnUninitDialog()
{
    if (m_hIcon != NULL)
    {
        DestroyIcon(m_hIcon);
        //CloseHandle(m_hIcon);
    }

    for (size_t i = 0; i < m_vecComp.size(); ++i)
    {
        if (m_vecComp[i] != NULL)
        {
            m_vecComp[i]->UninitComp();
            delete m_vecComp[i];
            m_vecComp[i] = NULL;
        }
    }

    m_vecComp.clear();
    EndDialog(0);
}

void KEditDialogImpl::OnMinSize(HWND hwnd)
{
    ::ShowWindow(hwnd, SW_SHOWMINIMIZED);
}

void KEditDialogImpl::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_nowPoint   = point;
    m_nSelItem = _SelectComp();

    if (m_nSelItem != -1)
    {
        SetFocus();
        m_pNowComp = m_vecComp[m_nSelItem];
        _RedrawAttrute();
    }
}

void KEditDialogImpl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    CPoint cPoint;

    switch(nChar)
    {
    case VK_DELETE:
        OnDelete();
        return;
    case VK_LEFT:
        cPoint.x = m_nowPoint.x - 1;
        cPoint.y = m_nowPoint.y;
        break;
    case VK_RIGHT:
        cPoint.x = m_nowPoint.x + 1;
        cPoint.y = m_nowPoint.y;
        break;
    case VK_UP:
        cPoint.x = m_nowPoint.x;
        cPoint.y = m_nowPoint.y - 1;
        break;
    case VK_DOWN:
        cPoint.x = m_nowPoint.x;
        cPoint.y = m_nowPoint.y + 1;
        break;
    default:
        return;
    }

    OnMouseMove(MK_LBUTTON, cPoint);
}

void KEditDialogImpl::OnMouseMove(UINT nFlags, CPoint point)
{
    if (nFlags == MK_LBUTTON && m_pNowComp != NULL)
    {
        _CheckPoint(point);

        std::string strPos;
        std::string strLastPos;

        m_pNowComp->GetCompAttrute("pos", strLastPos);
        _CalcMovePos(strLastPos, strPos);
        m_pNowComp->SetCompAttrute("pos", strPos);

        _Redraw();
    }
}

IComponent* KEditDialogImpl::_CompFactory()
{
    IComponent* pCompTmp = NULL;

    switch(m_uSelItemID)
    {
    case enRadio_Begin + 0:
        pCompTmp = new KCompText;
        break;
    case enRadio_Begin + 1:
        pCompTmp = new KCompButton;
        break;
    case enRadio_Begin + 2:
        pCompTmp = new KCompImgbtn;
        break;
    case enRadio_Begin + 3:
        pCompTmp = new KCompImg;
        break;
    default:
        pCompTmp = new KCompText;
        break;
    }

    if (pCompTmp != NULL)
    {
        pCompTmp->InitComp();
    }
    return pCompTmp;
}

void KEditDialogImpl::_Redraw()
{
    _RedrawComponent();

    _RedrawAttrute();
}

void KEditDialogImpl::_RedrawComponent()
{
    CStringA    strPreXml;
    CStringA    strNowXml("<text></text>");

    for (size_t i = 0; i < m_vecComp.size(); ++i)
    {
        m_vecComp[i]->DrawComponent(strPreXml);
        strNowXml.Append(strPreXml);
    }

    _DrawSelRect(strNowXml);

    SetPanelXml(MAIN_OPERATE, strNowXml.GetString());
}

void KEditDialogImpl::_RedrawAttrute()
{
    CStringA    strNowXml("<text></text>");
    BOOL        bBtnVisible = FALSE;

    if (m_pNowComp != NULL)
    {
        m_pNowComp->DrawAttrute(strNowXml);

        SetPanelXml(ATTR_OPERATE, strNowXml.GetString());

        m_pNowComp->InitAttrute(m_kEdit);

        bBtnVisible = TRUE;
    }
    else
    {
        SetPanelXml(ATTR_OPERATE, strNowXml.GetString());
    }

    SetItemVisible(SUBMIT_BUTTION, bBtnVisible);
    SetItemVisible(DELETE_BUTTION, bBtnVisible);
}

void KEditDialogImpl::_InitEdit()
{
    for (int i = 0; i < ATTRUTE_SIZE; ++i)
    {
        m_kEdit[i].SetNotify(m_hWnd);
        m_kEdit[i].SetStyle(ES_MULTILINE | ES_WANTRETURN);
        m_kEdit[i].Create(GetViewHWND(), NULL, NULL, WS_CHILD, 0, enAttruteEdit_Begin + i);
        m_kEdit[i].SetFont(BkFontPool::GetFont(FALSE, FALSE, FALSE, 8));
        m_kEdit[i].SetColor(RGB(0, 0, 0));
        m_kEdit[i].SetBgColor(RGB(255, 255, 255));
    }
}

void KEditDialogImpl::_InitList()
{

}

void KEditDialogImpl::_CalcMovePos(const std::string& cstrLastPos, std::string& strNowPos)
{
    std::string strPos[4];

    size_t nLastPos = 0;
    size_t nPos     = 0;

    for (int i = 0; i < 4; ++i)
    {
        strPos[i].erase();
        nPos = cstrLastPos.find(",", nLastPos);
        if (nPos != -1)
        {
            strPos[i] = cstrLastPos.substr(nLastPos, nPos - nLastPos);
            nLastPos = nPos + 1;
        }
        else
        {
            strPos[i] = cstrLastPos.substr(nLastPos, cstrLastPos.size() - nLastPos);
            nLastPos = cstrLastPos.size();
            continue;
        }
    }

    strNowPos.erase();
    CStringA strTmp;

    for (int i = 0; i < 4; ++i)
    {
        _CalcPrePos(i, strPos[i], strTmp);
        strNowPos += strTmp.GetString();
    }

    if (strNowPos.size() != 0)
    {
        strNowPos = strNowPos.substr(0, strNowPos.size() - 1);
    }
}

void KEditDialogImpl::_CalcPrePos(int nIndex, const std::string& strCmd, CStringA& strNum)
{
    strNum.Empty();

    int nNum = -1;
    if (nIndex % 2 == 0)
    {
        nNum = strCmd.empty() ? -1 : atoi(strCmd.c_str()) + m_nowPoint.x - m_LastPoint.x;
    }
    else
    {
        nNum = strCmd.empty() ? -1 : atoi(strCmd.c_str()) + m_nowPoint.y - m_LastPoint.y;
    }

    if (nNum != -1)
    {
        strNum.Format("%d,", nNum);
    }
}

int KEditDialogImpl::_SelectComp()
{
    CRect crect;
    CPoint cPoint;
    for (size_t i = 0; i < m_vecComp.size(); ++i)
    {
        m_vecComp[i]->GetCompRect(crect);
        _TransfromPoint(m_nowPoint, cPoint);

        if (crect.PtInRect(cPoint))
        {
            return (int)i;
        }
    }
    return -1;
}

void KEditDialogImpl::_CheckPoint(const CPoint& cPnt)
{
    if (cPnt.x < 0  || 
        cPnt.x > RIGHT_LIMIT - LEFT_LIMIT||
        cPnt.y < 0   || 
        cPnt.y > BOTTOM_LIMIT - TOP_LIMIT)
    {
        return;
    }
    m_LastPoint = m_nowPoint;
    m_nowPoint  = cPnt;
}

void KEditDialogImpl::_DrawSelRect(CStringA& strNowXml)
{
    if (m_pNowComp != NULL)
    {
        CStringA strTmp;
        CRect rect;
        m_pNowComp->GetCompRect(rect);

        // top
        strTmp.Format("<hr class=\"line_style\" pos=\"%d,%d,%d,%d\"/>", 
            rect.left, rect.top, rect.right, rect.top);
        strNowXml.Append(strTmp);

        // bottom
        strTmp.Format("<hr class=\"line_style\" pos=\"%d,%d,%d,%d\"/>", 
            rect.left, rect.bottom, rect.right, rect.bottom);
        strNowXml.Append(strTmp);

        // left
        strTmp.Format("<hr class=\"line_style\" pos=\"%d,%d,%d,%d\"/>", 
            rect.left, rect.top, rect.left, rect.bottom);
        strNowXml.Append(strTmp);

        // right
        strTmp.Format("<hr class=\"line_style\" pos=\"%d,%d,%d,%d\"/>", 
            rect.right, rect.top, rect.right, rect.bottom);

        strNowXml.Append(strTmp);
    }
}

void KEditDialogImpl::_TransfromPoint(const CPoint& cPoint, CPoint& point)
{
    point.x = cPoint.x - LEFT_LIMIT;
    point.y = cPoint.y - TOP_LIMIT;
}
