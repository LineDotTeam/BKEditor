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
    ///> @ Brief : 构造函数
    KCompButton();

    ///> @ Brief : 析构函数
    virtual ~KCompButton();

    ///> @ Brief : 初始化函数
    virtual BOOL InitComp();

    ///> @ Brief : 反初始化函数
    virtual BOOL UninitComp();

private:
    static int m_nButtonId;
};


#endif ///> __DEFINE_KCOMP_BUTTON_H_

///////////////////////////////////////////////////////////////////////////
