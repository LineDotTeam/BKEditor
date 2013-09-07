///////////////////////////////////////////////////////////////////////////
//
//  @ File      :   kcomp_imgbtn.h
//  @ Author    :   qianchi <qianchi@conew.com>
//  @ DateTime  :   [2013-9-4, 16:49:08]
//  @ Brief     :   
//
///////////////////////////////////////////////////////////////////////////
#ifndef __DEFINE_KCOMP_IMGBTN_H_
#define __DEFINE_KCOMP_IMGBTN_H_

#include "icomponent.h"

///////////////////////////////////////////////////////////////////////////

class KCompImgbtn
    : public IComponent
{
public:
    ///> @ Brief : ���캯��
    KCompImgbtn();

    ///> @ Brief : ��������
    virtual ~KCompImgbtn();

    ///> @ Brief : ��ʼ������
    virtual BOOL InitComp();

    ///> @ Brief : ����ʼ������
    virtual BOOL UninitComp();

private:
    static int m_nImgbtnId;
};

#endif ///> __DEFINE_KCOMP_IMGBTN_H_

///////////////////////////////////////////////////////////////////////////
