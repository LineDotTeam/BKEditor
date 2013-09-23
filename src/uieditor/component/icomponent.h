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
    ///> @ Brief : ���캯��
    IComponent(int nId, const std::string& strType);

    ///> @ Brief : ��������
    virtual ~IComponent();

    ///> @ Brief : ��ʼ������
    virtual BOOL InitComp() = 0;

    ///> @ Brief : ����ʼ������
    virtual BOOL UninitComp() = 0;

public:
    ///> @ Brief : ������ID
    int  GetId() const;

    ///> @ Brief : ����������
    BOOL GetCompType(std::string& strCompType) const;

    ///> @ Brief : ��ǰ��������
    size_t GetAttruteSize();

    ///> @ Brief : ��ȡ���λ��
    BOOL GetCompRect(RECT& rect) const;
    void SetCompRect(const RECT& rect);

    ///> @ Brief : ����������
    BOOL GetCompAttrute(const std::string& cstrAttrName, std::string& strAttrValue) const;
    BOOL GetCompAttrute(size_t nIndex, std::string& strAttrValue) const;

    ///> @ Brief : �����������
    BOOL SetCompAttrute(const std::string& cstrAttrName, const std::string& cstrAttrValue);
    BOOL SetCompAttrute(size_t nIndex, const std::string& cstrAttrValue);

    ///> @ Brief : ��ʼ������
    BOOL InitAttrute(KTipEdit3* pEdit);

public:
    ///> @ Brief : �������
    BOOL DrawComponent(CStringA& strXml);

    ///> @ Brief : ��������
    BOOL DrawAttrute(CStringA& strXml);

protected:
    void _SetCompRect(const std::string& cstrAttrValue);

    void _SetAttr2Xml(CStringA& strXML);

    void _SetInit();

protected:
    CBkDialogView                       m_richView;         // �Ի���
    int                                 m_nId;              // ���ID
    std::string                         m_strCompType;      // �������
    std::map<std::string, std::string>  m_mapAttrute;       // ���Լ�
    CRect                               m_rcPos;            // �����������, �ڻ�������е�λ��

    BOOL                                m_bIsInit;          // �Ƿ��ʼ��
};

#endif ///> __DEFINE_ICOMPONENT_H_

///////////////////////////////////////////////////////////////////////////
