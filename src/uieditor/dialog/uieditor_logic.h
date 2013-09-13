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
    ///> @ Brief : ���캯��
    KEditDialogImpl(HINSTANCE hInstance, KEditDialogView* pEditView);

    ///> @ Brief : ��������
    ~KEditDialogImpl();

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

private:
    ///> @ Brief : �������
    IComponent* _CompFactory(); 

    ///> @ Brief : �ػ�����
    void _Redraw();

    ///> @ Brief : �ػ����
    void _RedrawComponent();

    ///> @ Brief : �ػ�����
    void _RedrawAttrute();

    ///> @ Brief : ��ʼ�������
    void _InitEdit();

    ///> @ Brief : ��ʼ��������
    void _InitList();

    ///> @ Brief : �����ƶ���Դ����intת��Ϊstring
    void _CalcMovePos(const std::string& cstrLastPos, std::string& strNowPos);
    void _CalcPrePos(int nIndex, const std::string& strCmd, CStringA& strNum);

    ///> @ Brief : �Ƿ���ѡ�����
    int  _SelectComp();

    ///> @ Brief : ���������ƶ���Χ�Ƿ���ȷ
    void _CheckPoint(const CPoint& cPnt);

    ///> @ Brief : ����ѡ������Ľ���߿�
    void _DrawSelRect(CStringA& strNowXml);

    ///> @ Brief : ��������Ļ������ת��Ϊ�������������
    void _TransfromPoint(const CPoint& cPoint, CPoint& point);

private:
    CPoint      m_nowPoint;     // ��ǰ��
    CPoint      m_LastPoint;    // ��һ����
    HINSTANCE   m_hInstance;    // ��ǰʵ��

    UINT        m_uSelItemID;           // ��ǰѡ�е�CompID
    IComponent* m_pNowComp;             // ��ǰѡ�е�ʵ��
    std::vector<IComponent*> m_vecComp; // �ռ�vector����

    HICON       m_hIcon;
    int         m_nSelItem;

    KTipEdit3   m_kEdit[ATTRUTE_SIZE];
    KEditDialogView* m_pEditView;
};

#endif ///> __DEFINE_UIEDITOR_LOGIC_H_

///////////////////////////////////////////////////////////////////////////
