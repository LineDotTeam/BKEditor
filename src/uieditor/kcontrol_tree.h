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
#include <vector>
//
// -------------------------------------------------------------------------

class KControlNode
{
public:
    KControlNode();
    ~KControlNode();
    BOOL SetName(const wchar_t* strName);
    BOOL SetAttr(const wchar_t* pszKey, const wchar_t* pszValue);
    BOOL RemoveAttr(const wchar_t* pszKey);
    KControlNode* AddChild();
    BOOL RemoveChild(KControlNode* pChild);
    void Release();

private:
    CString m_strName;
    std::map<CString, CString> m_vecAttr;
    std::vector<KControlNode*> m_vecChildren;
};

// -------------------------------------------------------------------------
//
#endif // __KCONTROL_TREE_h_
