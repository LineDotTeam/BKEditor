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

#include <ktipedit/ktip_edit3.h>
#include <vector>

#include "bkwinres.h"
#include "component/kcomp_img.h"
#include "component/kcomp_text.h"
#include "component/kcomp_button.h"
#include "component/kcomp_imgbtn.h"

///////////////////////////////////////////////////////////////////////////

class KEditDialogView
    : public CBkDialogImpl<KEditDialogView>
{
public:
    ///> @ Brief : 构造函数
    KEditDialogView(HINSTANCE hInstance);

    ///> @ Brief : 析构函数
    ~KEditDialogView();

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
    BK_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CBkDialogImpl<KEditDialogView>)
        MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
        CHAIN_MSG_MAP(CBkDialogImpl<KEditDialogView>)
        MSG_WM_INITDIALOG(OnInitDialog)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_KEYDOWN(OnKeyDown)
	END_MSG_MAP()

private:
    ///> @ Brief : 生成组件
    IComponent* _CompFactory(); 

    ///> @ Brief : 重绘所有
    void _Redraw();

    ///> @ Brief : 重绘组件
    void _RedrawComponent();

    ///> @ Brief : 重绘属性
    void _RedrawAttrute();

    ///> @ Brief : 初始化输入框
    void _InitEdit();

    ///> @ Brief : 初始化下拉框
    void _InitList();

    ///> @ Brief : 计算移动电源，将int转化为string
    void _CalcMovePos(const std::string& cstrLastPos, std::string& strNowPos);
    void _CalcPrePos(int nIndex, const std::string& strCmd, CStringA& strNum);

    ///> @ Brief : 是否有选中组件
    int  _SelectComp();

    ///> @ Brief : 检查组件的移动范围是否正确
    void _CheckPoint(const CPoint& cPnt);

    ///> @ Brief : 绘制选中组件的焦点边框
    void _DrawSelRect(CStringA& strNowXml);

    ///> @ Brief : 将整个屏幕的坐标转化为绘制组件的坐标
    void _TransfromPoint(const CPoint& cPoint, CPoint& point);

private:
    CPoint      m_nowPoint;     // 当前点
    CPoint      m_LastPoint;    // 上一个点
    HINSTANCE   m_hInstance;    // 当前实例

    UINT        m_uSelItemID;           // 当前选中的CompID
    IComponent* m_pNowComp;             // 当前选中的实例
    std::vector<IComponent*> m_vecComp; // 空间vector容器
    
    HICON       m_hIcon;
    int         m_nSelItem;

    KTipEdit3   m_kEdit[ATTRUTE_SIZE];
};


#endif ///> __DEFINE_MYWINDOW_H_

///////////////////////////////////////////////////////////////////////////
