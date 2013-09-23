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
#include "component_def.h"

#define ATTRUTE_HEIGHT 35
#define ATTRUTE_SIZE   20

#define LEFT_LIMIT      200
#define RIGHT_LIMIT     1000
#define TOP_LIMIT       30
#define BOTTOM_LIMIT    800

///////////////////////////////////////////////////////////////////////////

class IComponent
{
public:
    ///> @ Brief : 构造函数
    IComponent(int nId, const std::string& strType);

    ///> @ Brief : 析构函数
    virtual ~IComponent();

    ///> @ Brief : 初始化函数
    virtual BOOL InitComp() = 0;

    ///> @ Brief : 反初始化函数
    virtual BOOL UninitComp() = 0;

public:
    ///> @ Brief : 获得组件ID
    int  GetId() const;

    ///> @ Brief : 获得组件类型
    BOOL GetCompType(std::string& strCompType) const;

    ///> @ Brief : 当前属性数量
    size_t GetAttruteSize();

    ///> @ Brief : 获取组件位置
    BOOL GetCompRect(RECT& rect) const;
    void SetCompRect(const RECT& rect);

    ///> @ Brief : 获得组件属性
    BOOL GetCompAttrute(const std::string& cstrAttrName, std::string& strAttrValue) const;
    BOOL GetCompAttrute(size_t nIndex, std::string& strAttrValue) const;

    ///> @ Brief : 设置组件属性
    BOOL SetCompAttrute(const std::string& cstrAttrName, const std::string& cstrAttrValue);
    BOOL SetCompAttrute(size_t nIndex, const std::string& cstrAttrValue);

    ///> @ Brief : 初始化属性
    BOOL InitAttrute(KTipEdit3* pEdit);

public:
    ///> @ Brief : 绘制组件
    BOOL DrawComponent(CStringA& strXml);

    ///> @ Brief : 绘制属性
    BOOL DrawAttrute(CStringA& strXml);

protected:
    void _SetCompRect(const std::string& cstrAttrValue);

    void _SetAttr2Xml(CStringA& strXML);

    void _SetInit();

protected:
    CBkDialogView                       m_richView;         // 对话框
    int                                 m_nId;              // 组件ID
    std::string                         m_strCompType;      // 组件类型
    std::map<std::string, std::string>  m_mapAttrute;       // 属性集
    CRect                               m_rcPos;            // 组件矩形区域, 在绘制组件中的位置

    BOOL                                m_bIsInit;          // 是否初始化
};

#endif ///> __DEFINE_ICOMPONENT_H_

///////////////////////////////////////////////////////////////////////////
