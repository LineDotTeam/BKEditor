#include "stdafx.h"
#include "uieditor_dlg.h"
#include "uieditor_logic.h"

KEditDialogView::KEditDialogView(HINSTANCE hInstance)
: CBkDialogImpl<KEditDialogView>(XML_BK_MAIN_DEF)
, m_pEditImpl(NULL)
{
    m_pEditImpl = new KEditDialogImpl(hInstance, this);
}

KEditDialogView::~KEditDialogView()
{
    delete m_pEditImpl;
    m_pEditImpl = NULL;
}

BOOL KEditDialogView::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
    if (m_pEditImpl != NULL)
    {
        return m_pEditImpl->OnInitDialog(wndFocus, lInitParam);
    }
    return FALSE;
}

void KEditDialogView::OnUninitDialog()
{
    if (m_pEditImpl != NULL)
    {
        m_pEditImpl->OnUninitDialog();
    }
}

void KEditDialogView::OnPalette()
{
    if (m_pEditImpl != NULL)
    {
        m_pEditImpl->OnPalette();
    }
}

void KEditDialogView::OnSubmit()
{
    if (m_pEditImpl != NULL)
    {
        m_pEditImpl->OnSubmit();
    }
}

void KEditDialogView::OnDelete()
{
    if (m_pEditImpl != NULL)
    {
        m_pEditImpl->OnDelete();
    }
}

void KEditDialogView::OnSelectRadio(UINT uItemId)
{
    if (m_pEditImpl != NULL)
    {
        m_pEditImpl->OnSelectRadio(uItemId);
    }
}

void KEditDialogView::OnMinSize()
{
    if (m_pEditImpl != NULL)
    {
        m_pEditImpl->OnMinSize();
    }
}

void KEditDialogView::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (m_pEditImpl != NULL)
    {
        m_pEditImpl->OnLButtonDown(nFlags, point);
    }
}

void KEditDialogView::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_pEditImpl != NULL)
    {
        m_pEditImpl->OnMouseMove(nFlags, point);
    }
}

void KEditDialogView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (m_pEditImpl != NULL)
    {
        m_pEditImpl->OnKeyDown(nChar, nRepCnt, nFlags);
    }
}
