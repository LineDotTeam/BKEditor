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

///////////////////////////////////////////////////////////////////////////

class KEditDialogImpl;
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
    KEditDialogImpl* m_pEditImpl;
};


#endif ///> __DEFINE_MYWINDOW_H_

///////////////////////////////////////////////////////////////////////////
