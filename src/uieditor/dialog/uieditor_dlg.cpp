#include "stdafx.h"
#include "uieditor_dlg.h"

KMyWindow::KMyWindow(HINSTANCE hInstance)
: CBkDialogImpl<KMyWindow>(XML_BK_MAIN_DEF)
, m_hInstance(hInstance)
, m_uSelItemID(0)
, m_pNowComp(NULL)
, m_hIcon(NULL)
{
}

KMyWindow::~KMyWindow()
{

}

BOOL KMyWindow::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
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

void KMyWindow::OnUninitDialog()
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

void KMyWindow::OnPalette()
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
            strPos.Format("%d,%d", m_nowPoint.x - LEFT_OFFSET, m_nowPoint.y - TOP_OFFSET);
            m_pNowComp->SetCompAttrute("pos", strPos.GetString());
        }
        _Redraw();
    }
    else
    {
        m_pNowComp = NULL;
        _RedrawAttrute();
    }
    
}

void KMyWindow::OnSubmit()
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

void KMyWindow::OnDelete()
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

void KMyWindow::OnSelectRadio(UINT uItemId)
{
    m_uSelItemID = uItemId;
}

IComponent* KMyWindow::_CompFactory()
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

void KMyWindow::OnSelectComp(UINT uItemId)
{
    SetFocus();
    for (size_t i = 0; i < m_vecComp.size(); ++i)
    {
        if (m_vecComp[i]->GetId() == uItemId)
        {
            m_pNowComp = m_vecComp[i];
            _RedrawAttrute();
            return;
        }
    }
    m_pNowComp = NULL;
    _RedrawAttrute();
}

void KMyWindow::OnMinSize()
{
    ::ShowWindow(m_hWnd, SW_SHOWMINIMIZED);
}

void KMyWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_nowPoint = point;
}

void KMyWindow::OnMouseMove(UINT nFlags, CPoint point)
{
    if (nFlags == MK_LBUTTON && m_pNowComp != NULL)
    {
        m_LastPoint = m_nowPoint;
        m_nowPoint  = point;

        std::string strPos;
        std::string strLastPos;

        m_pNowComp->GetCompAttrute("pos", strLastPos);
        _CalcMovePos(strLastPos, strPos);
        m_pNowComp->SetCompAttrute("pos", strPos);

        _Redraw();
    }
}

void KMyWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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

void KMyWindow::_Redraw()
{
    _RedrawComponent();

    _RedrawAttrute();
}

void KMyWindow::_RedrawComponent()
{
    CStringA    strPreXml;
    CStringA    strNowXml("<text></text>");

    for (size_t i = 0; i < m_vecComp.size(); ++i)
    {
        m_vecComp[i]->DrawComponent(strPreXml);
        strNowXml.Append(strPreXml);
    }
    SetPanelXml(MAIN_OPERATE, strNowXml.GetString());
}

void KMyWindow::_RedrawAttrute()
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

void KMyWindow::_InitEdit()
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

void KMyWindow::_InitList()
{
}

LRESULT KMyWindow::_OnChangeSize(UINT nFlag, WPARAM wParam, LPARAM lParam, BOOL bHandled)
{
    return 0;
}

void KMyWindow::_CalcMovePos(const std::string& cstrLastPos, std::string& strNowPos)
{
    std::string strPos[4];

    int nLastPos = 0;
    int nPos     = 0;

    for (int i = 0; i < 4; ++i)
    {
        strPos[i].erase();
        nPos = (int)cstrLastPos.find(",", nLastPos);
        if (nPos != -1)
        {
            strPos[i] = cstrLastPos.substr(nLastPos, nPos - nLastPos);
            nLastPos = nPos + 1;
        }
        else
        {
            strPos[i] = cstrLastPos.substr(nLastPos, cstrLastPos.size() - nLastPos);
            nLastPos = (int)cstrLastPos.size();
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

void KMyWindow::_CalcPrePos(int nIndex, const std::string& strCmd, CStringA& strNum)
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
