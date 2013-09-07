///////////////////////////////////////////////////////////////////////////
//
//  @ File      :   kcomp_button.h
//  @ Author    :   qianchi <qianchi@conew.com>
//  @ DateTime  :   [2013-9-4, 15:41:34]
//  @ Brief     :   
//
///////////////////////////////////////////////////////////////////////////
#ifndef __DEFINE_KCOMP_BUTTON_H_
#define __DEFINE_KCOMP_BUTTON_H_

#include "icomponent.h"

///////////////////////////////////////////////////////////////////////////

class KCompButton
    : public IComponent
{
public:
    ///> @ Brief : ���캯��
    KCompButton();

    ///> @ Brief : ��������
    virtual ~KCompButton();

    ///> @ Brief : ��ʼ������
    virtual BOOL InitComp();

    ///> @ Brief : ����ʼ������
    virtual BOOL UninitComp();

private:
    static int m_nButtonId;
};


#endif ///> __DEFINE_KCOMP_BUTTON_H_

///////////////////////////////////////////////////////////////////////////
