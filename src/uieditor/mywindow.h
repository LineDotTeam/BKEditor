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
    ///> @ Brief : 构造函数
    KMyWindow(HINSTANCE hInstance);

    ///> @ Brief : 析构函数
    ~KMyWindow();

protected:
    ///> @ Brief : 初始化窗口函数
    BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);

    ///> @ Brief : 画板被点击函数
    void OnPalette();

    ///> @ Brief : 提交当前属性
    void OnSubmit();

    ///> @ Brief : 删除当前组件
    void OnDelete();

    ///> @ Brief : 当单选按钮被选中时
    void OnSelectRadio(UINT uItemId);

    ///> @ Brief : 当组件被选中时
    void OnSelectComp(UINT uItemId);

    ///> @ Brief : 反初始化窗口函数
    void OnUninitDialog();

    ///> @ Brief : 最小化
    void OnMinSize();

    ///> @ Brief : 左键点击
    void OnLButtonDown(UINT nFlags, CPoint point);

    ///> @ Brief : 当键盘按下
    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

    ///> @ Brief : 鼠标移动
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
    CPoint      m_nowPoint;     // 当前点
    CPoint      m_LastPoint;    // 上一个点
    HINSTANCE   m_hInstance;    // 当前实例

    UINT        m_uSelItemID;           // 当前选中的CompID
    IComponent* m_pNowComp;             // 当前选中的实例
    std::vector<IComponent*> m_vecComp; // 空间vector容器
    
    HICON       m_hIcon;

    KTipEdit3   m_kEdit[ATTRUTE_SIZE];
    KListBox    m_kListBox;
};


#endif ///> __DEFINE_MYWINDOW_H_

///////////////////////////////////////////////////////////////////////////
