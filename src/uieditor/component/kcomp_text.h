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
    ///> @ Brief : 构造函数
    KCompText();

    ///> @ Brief : 析构函数
    virtual ~KCompText();

    ///> @ Brief : 初始化函数
    virtual BOOL InitComp();

    ///> @ Brief : 反初始化函数
    virtual BOOL UninitComp();

private:
    static int m_nTextId;
};


#endif ///> __DEFINE_KCOMP_TEXT_H_

///////////////////////////////////////////////////////////////////////////
