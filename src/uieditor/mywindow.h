///////////////////////////////////////////////////////////////////////////
//
//  @ File      :   mywindow.h
//  @ Author    :   qianchi <qianchi@conew.com>
//  @ DateTime  :   [2013-9-2, 10:54:07]
//  @ Brief     :   
//
///////////////////////////////////////////////////////////////////////////
#ifndef __DEFINE_MYWINDOW_H_
#define __DEFINE_MYWINDOW_H_

#include "stdafx.h"
#include <ktipedit/ktip_edit3.h>
#include <vector>
#include "bkwinres.h"

#include "kcomp_img.h"
#include "kcomp_text.h"
#include "kcomp_button.h"
#include "kcomp_imgbtn.h"
#include "mylistbox.h"

#define LEFT_OFFSET 200
#define TOP_OFFSET  30

///////////////////////////////////////////////////////////////////////////

class KMyWindow
    : public CBkDialogImpl<KMyWindow>
{
public:
    ///> @ Brief : ���캯��
    KMyWindow(HINSTANCE hInstance);

    ///> @ Brief : ��������
    ~KMyWindow();

protected:
    ///> @ Brief : ��ʼ�����ں���
    BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);

    ///> @ Brief : ���屻�������
    void OnPalette();

    ///> @ Brief : �ύ��ǰ����
    void OnSubmit();

    ///> @ Brief : ɾ����ǰ���
    void OnDelete();

    ///> @ Brief : ����ѡ��ť��ѡ��ʱ
    void OnSelectRadio(UINT uItemId);

    ///> @ Brief : �������ѡ��ʱ
    void OnSelectComp(UINT uItemId);

    ///> @ Brief : ����ʼ�����ں���
    void OnUninitDialog();

    ///> @ Brief : ��С��
    void OnMinSize();

    ///> @ Brief : ������
    void OnLButtonDown(UINT nFlags, CPoint point);

    ///> @ Brief : �����̰���
    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

    ///> @ Brief : ����ƶ�
    void OnMouseMove(UINT nFlags, CPoint point);

protected:
    BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
        BK_NOTIFY_ID_COMMAND(CLOSE_BUTTON,   OnUninitDialog)
        BK_NOTIFY_ID_COMMAND(MINSIZE_BUTTON, OnMinSize)
        BK_NOTIFY_ID_COMMAND(MAIN_OPERATE,   OnPalette)
        BK_NOTIFY_ID_COMMAND(SUBMIT_BUTTION, OnSubmit)
        BK_NOTIFY_ID_COMMAND(DELETE_BUTTION, OnDelete)
        BK_NOTIFY_ID_COMMAND_EX(enRadio_Begin, enRadio_Begin + 3, OnSelectRadio)
        BK_NOTIFY_ID_COMMAND_EX(enCompId_Begin, enCompId_End,     OnSelectComp)
    BK_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CBkDialogImpl<KMyWindow>)
        MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
        CHAIN_MSG_MAP(CBkDialogImpl<KMyWindow>)
        MSG_WM_INITDIALOG(OnInitDialog)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_KEYDOWN(OnKeyDown)
        MESSAGE_HANDLER(WM_EDIT_CHANGE, _OnChangeSize)
	END_MSG_MAP()

private:
    LRESULT _OnChangeSize(UINT nFlag, WPARAM wParam, LPARAM lParam, BOOL bHandled);

    IComponent* _CompFactory(); 

    void _Redraw();

    void _RedrawComponent();

    void _RedrawAttrute();

    void _InitEdit();

    void _InitList();

    void _CalcMovePos(const std::string& cstrLastPos, std::string& strNowPos);

    void _CalcPrePos(int nIndex, const std::string& strCmd, CStringA& strNum);

private:
    CPoint      m_nowPoint;     // ��ǰ��
    CPoint      m_LastPoint;    // ��һ����
    HINSTANCE   m_hInstance;    // ��ǰʵ��

    UINT        m_uSelItemID;           // ��ǰѡ�е�CompID
    IComponent* m_pNowComp;             // ��ǰѡ�е�ʵ��
    std::vector<IComponent*> m_vecComp; // �ռ�vector����
    
    HICON       m_hIcon;

    KTipEdit3   m_kEdit[ATTRUTE_SIZE];
    KListBox    m_kListBox;
};


#endif ///> __DEFINE_MYWINDOW_H_

///////////////////////////////////////////////////////////////////////////
