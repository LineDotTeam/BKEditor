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
    ///> @ Brief : ���캯��
    KEditDialogView(HINSTANCE hInstance);

    ///> @ Brief : ��������
    ~KEditDialogView();

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
