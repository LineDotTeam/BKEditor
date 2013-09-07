///////////////////////////////////////////////////////////////////////////
//
//  @ File      :   kcomp_img.h
//  @ Author    :   qianchi <qianchi@conew.com>
//  @ DateTime  :   [2013-9-4, 17:12:16]
//  @ Brief     :   
//
///////////////////////////////////////////////////////////////////////////
#ifndef __DEFINE_KCOMP_IMG_H_
#define __DEFINE_KCOMP_IMG_H_

#include "icomponent.h"

///////////////////////////////////////////////////////////////////////////

class KCompImg
    : public IComponent
{
public:
    ///> @ Brief : ���캯��
    KCompImg();

    ///> @ Brief : ��������
    virtual ~KCompImg();

    ///> @ Brief : ��ʼ������
    virtual BOOL InitComp();

    ///> @ Brief : ����ʼ������
    virtual BOOL UninitComp();

private:
    static int m_nImgId;
};


#endif ///> __DEFINE_KCOMP_IMG_H_

///////////////////////////////////////////////////////////////////////////
