///////////////////////////////////////////////////////////////////////////
//
//  @ File      :   kcomp_text.h
//  @ Author    :   qianchi <qianchi@conew.com>
//  @ DateTime  :   [2013-9-3, 11:33:33]
//  @ Brief     :   
//
///////////////////////////////////////////////////////////////////////////
#ifndef __DEFINE_KCOMP_TEXT_H_
#define __DEFINE_KCOMP_TEXT_H_

#include "icomponent.h"

///////////////////////////////////////////////////////////////////////////

class KCompText
    : public IComponent
{

public:
    ///> @ Brief : ���캯��
    KCompText();

    ///> @ Brief : ��������
    virtual ~KCompText();

    ///> @ Brief : ��ʼ������
    virtual BOOL InitComp();

    ///> @ Brief : ����ʼ������
    virtual BOOL UninitComp();

private:
    static int m_nTextId;
};


#endif ///> __DEFINE_KCOMP_TEXT_H_

///////////////////////////////////////////////////////////////////////////
