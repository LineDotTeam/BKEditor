///////////////////////////////////////////////////////////////////////////
//
//  @ File      :   uieditor_logic.h
//  @ Author    :   qianchi <qianchi@conew.com>
//  @ DateTime  :   [2013-9-13, 9:48:13]
//  @ Brief     :   
//
///////////////////////////////////////////////////////////////////////////
#ifndef __DEFINE_UIEDITOR_LOGIC_H_
#define __DEFINE_UIEDITOR_LOGIC_H_

#include <vector>
#include <ktipedit/ktip_edit3.h>
#include "component/icomponent.h"

///////////////////////////////////////////////////////////////////////////
class KEditDialogView;
class KEditDialogImpl
{
public:
    ///> @ Brief : 构造函数
    KEditDialogImpl(HINSTANCE hInstance, KEditDialogView* pEditView);

    ///> @ Brief : 析构函数
    ~KEditDialogImpl();

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
    KEditDialogView* m_pEditView;
};

#endif ///> __DEFINE_UIEDITOR_LOGIC_H_

///////////////////////////////////////////////////////////////////////////
