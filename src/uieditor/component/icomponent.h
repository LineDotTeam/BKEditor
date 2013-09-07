///////////////////////////////////////////////////////////////////////////
//
//  @ File      :   kcomponent.h
//  @ Author    :   qianchi <qianchi@conew.com>
//  @ DateTime  :   [2013-9-3, 11:00:50]
//  @ Brief     :   
//
///////////////////////////////////////////////////////////////////////////
#ifndef __DEFINE_ICOMPONENT_H_
#define __DEFINE_ICOMPONENT_H_

#include <ktipedit/ktip_edit3.h>
#include <string>
#include <map>
#include "bkwinres.h"

#define ATTRUTE_HEIGHT 35
#define ATTRUTE_SIZE   20

///////////////////////////////////////////////////////////////////////////

class IComponent
{
public:
    ///> @ Brief : 析构函数
    virtual ~IComponent();

    ///> @ Brief : 初始化函数
    virtual BOOL InitComp() = 0;

    ///> @ Brief : 反初始化函数
    virtual BOOL UninitComp() = 0;

    ///> @ Brief : 获得组件ID
    virtual int  GetId() const;

    ///> @ Brief : 获得组件类型
    virtual BOOL GetCompType(std::string& strCompType) const;

    ///> @ Brief : 绘制组件
    virtual BOOL DrawComponent(CStringA& strXml);

    ///> @ Brief : 设置组件属性
    virtual BOOL SetCompAttrute(const std::string& cstrAttrName, const std::string& cstrAttrValue);
    virtual BOOL SetCompAttrute(size_t nIndex, const std::string& cstrAttrValue);

    ///> @ Brief : 获得组件属性
    virtual BOOL GetCompAttrute(const std::string& cstrAttrName, std::string& strAttrValue) const;

    ///> @ Brief : 绘制属性
    virtual BOOL DrawAttrute(CStringA& strXml);

    ///> @ Brief : 初始化绘制属性
    virtual BOOL InitAttrute(KTipEdit3* pEdit);

protected:
    BOOL _IsInitComp() const;    

    void _SetAttr2Xml(CStringA& strXML);

protected:
    CBkDialogView                       m_richView;         // 对话框
    int                                 m_nId;              // 当前组件的ID
    std::string                         m_strCompType;      // 组件类型
    std::map<std::string, std::string>  m_mapAttrute;       // 属性集
};

#endif ///> __DEFINE_ICOMPONENT_H_

///////////////////////////////////////////////////////////////////////////
