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
    ///> @ Brief : ��������
    virtual ~IComponent();

    ///> @ Brief : ��ʼ������
    virtual BOOL InitComp() = 0;

    ///> @ Brief : ����ʼ������
    virtual BOOL UninitComp() = 0;

    ///> @ Brief : ������ID
    virtual int  GetId() const;

    ///> @ Brief : ����������
    virtual BOOL GetCompType(std::string& strCompType) const;

    ///> @ Brief : �������
    virtual BOOL DrawComponent(CStringA& strXml);

    ///> @ Brief : �����������
    virtual BOOL SetCompAttrute(const std::string& cstrAttrName, const std::string& cstrAttrValue);
    virtual BOOL SetCompAttrute(size_t nIndex, const std::string& cstrAttrValue);

    ///> @ Brief : ����������
    virtual BOOL GetCompAttrute(const std::string& cstrAttrName, std::string& strAttrValue) const;

    ///> @ Brief : ��������
    virtual BOOL DrawAttrute(CStringA& strXml);

    ///> @ Brief : ��ʼ����������
    virtual BOOL InitAttrute(KTipEdit3* pEdit);

protected:
    BOOL _IsInitComp() const;    

    void _SetAttr2Xml(CStringA& strXML);

protected:
    CBkDialogView                       m_richView;         // �Ի���
    int                                 m_nId;              // ��ǰ�����ID
    std::string                         m_strCompType;      // �������
    std::map<std::string, std::string>  m_mapAttrute;       // ���Լ�
};

#endif ///> __DEFINE_ICOMPONENT_H_

///////////////////////////////////////////////////////////////////////////
