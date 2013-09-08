/* -------------------------------------------------------------------------
//  File        :   kcontrol_tree.cpp
//  Author      :   Chen Xuanyi
//  Datet       :   2013/9/7 21:02
//  Brief       :   
//
// -----------------------------------------------------------------------*/
//
#include "stdafx.h"
#include "kcontrol_tree.h"
//
// -------------------------------------------------------------------------

KControlNode::KControlNode()
{
}

KControlNode::~KControlNode()
{
    Release();
}

BOOL KControlNode::SetName(const wchar_t* pszName)
{
    BOOL bRet = FALSE;

    if (pszName == NULL)
    {
        goto Exit0;
    }

    m_strName = pszName;
    bRet = TRUE;

Exit0:
    return bRet;
}

BOOL KControlNode::SetAttr(const wchar_t* pszKey, const wchar_t* pszValue)
{
    BOOL bRet = FALSE;

    if (pszKey == NULL || pszValue == NULL)
    {
        goto Exit0;
    }

    m_mapAttr[pszKey] = pszValue;
    bRet = TRUE;

Exit0:
    return bRet;
}

BOOL KControlNode::RemoveAttr(const wchar_t* pszKey)
{
    BOOL bRet = FALSE;
    std::map<CString, CString>::iterator iterFind;

    if (pszKey == NULL)
    {
        goto Exit0;
    }

    iterFind = m_mapAttr.find(pszKey);
    if (iterFind != m_mapAttr.end())
    {
        m_mapAttr.erase(iterFind);
        bRet = TRUE;
    }

Exit0:
    return bRet;
}

KControlNode* KControlNode::AddChild()
{
    KControlNode* pChild = new KControlNode();
    if (pChild)
    {
        m_listChildren.push_back(pChild);
    }

    return pChild;
}

BOOL KControlNode::RemoveChild(KControlNode* pChild)
{
    BOOL bRet = FALSE;
    
    if (pChild == NULL)
    {
        goto Exit0;
    }

    m_listChildren.remove(pChild);
    delete pChild;
    pChild = NULL;

    bRet = TRUE;

Exit0:
    return bRet;
}

void KControlNode::Release()
{
    std::list<KControlNode*>::iterator iterChild = m_listChildren.begin();

    for (; iterChild != m_listChildren.end(); ++iterChild)
    {
        if (*iterChild)
        {
            delete *iterChild;
            *iterChild = NULL;
        }
    }
}

BOOL KControlNode::GetName(CString& strName) const
{
    strName = m_strName;

    return TRUE;
}

BOOL KControlNode::GetAttr(const wchar_t* pszKey, CString& strValue) const
{
    BOOL bRet = FALSE;
    std::map<CString, CString>::const_iterator iterFind;
    if (pszKey == NULL)
    {
        goto Exit0;
    }

    iterFind = m_mapAttr.find(pszKey);
    if (iterFind != m_mapAttr.end())
    {
        strValue = iterFind->second;
        bRet = TRUE;
    }

Exit0:
    return bRet;
}

BOOL KControlNode::GetAllAttr(std::map<CString, CString>& mapAttr) const
{
    mapAttr = m_mapAttr;

    return TRUE;
}

BOOL KControlNode::GetAllChildren(std::list<KControlNode*>& listChildren) const
{
    listChildren = m_listChildren;

    return TRUE;
}

// -------------------------------------------------------------------------