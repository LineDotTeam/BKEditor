/* -------------------------------------------------------------------------
//  File        :   kcontrol_tree.h
//  Author      :   Chen Xuanyi
//  Datet       :   2013/9/7 20:24
//  Brief       :   
//
// -----------------------------------------------------------------------*/
#ifndef __KCONTROL_TREE_h_
#define __KCONTROL_TREE_h_

#include <atlstr.h>
#include <map>
#include <list>
//
// -------------------------------------------------------------------------

class KControlNode
{
public:
    KControlNode();
    ~KControlNode();
    BOOL SetName(const wchar_t* pszName);
    BOOL GetName(CString& strName) const;
    BOOL SetAttr(const wchar_t* pszKey, const wchar_t* pszValue);
    BOOL GetAttr(const wchar_t* pszKey, CString& strValue) const;
    BOOL RemoveAttr(const wchar_t* pszKey);
    BOOL GetAllAttr(std::map<CString, CString>& mapAttr) const;
    KControlNode* AddChild();
    BOOL RemoveChild(KControlNode* pChild);
    BOOL GetAllChildren(std::list<KControlNode*>& listChildren) const;

    void Release();

private:
    CString m_strName;
    std::map<CString, CString>  m_mapAttr;
    std::list<KControlNode*>    m_listChildren;
};

// -------------------------------------------------------------------------
//
#endif // __KCONTROL_TREE_h_
