/* -------------------------------------------------------------------------
//  File        :   xml_produce_ui.cpp
//  Author      :   Sum
//  Datet       :   2013/9/7 15:59
//  Brief       :   
//
// -----------------------------------------------------------------------*/
//
#include "xml_produce_ui.h"
#include <atlbase.h>

UIXmlProduce::UIXmlProduce()
{

}

UIXmlProduce::~UIXmlProduce()
{

}

Global::BOOL UIXmlProduce::Produce(const KControlNode& controltree,
    const std::wstring& strPath)
{
    if (strPath.empty())
    {
        return FALSE;
    }

    return _Produce(controltree, strPath);
}

Global::BOOL UIXmlProduce::_Produce(const KControlNode& controltree,
    const std::wstring& strPath)
{
    if (strPath.empty())
    {
        return FALSE;
    }

    TiXmlDocument document;
    std::list<KControlNode*> listElement;
    document.LinkEndChild(new TiXmlDeclaration("1.0", "UTF-8", ""));

    controltree.GetAllChildren(listElement);

    for (std::list<KControlNode*>::iterator it = listElement.begin();
        it != listElement.end();
        ++it)
    {
        TiXmlElement* pElement = new TiXmlElement("");

        if (pElement
            && _AddXml(controltree, pElement))
        {
            document.LinkEndChild(pElement);
        }
        else
        {
            if (pElement)
            {
                delete pElement;
                pElement = NULL;
            }
        }
    }

    return document.SaveFile(CW2A(strPath.c_str()).m_psz);
}

Global::BOOL UIXmlProduce::_AddXml(const KControlNode& controltree,
    TiXmlElement* pNode)
{
    if (!pNode)
    {
        return FALSE;
    }

    CString csName;
    std::map<CString, CString> mapArr;
    std::list<KControlNode*> listElement;

    controltree.GetAllChildren(listElement);
    controltree.GetAllAttr(mapArr);
    controltree.GetName(csName);

    pNode->SetValue(CW2A(csName).m_psz);

    for (std::map<CString, CString>::iterator it = mapArr.begin();
        it != mapArr.end();
        ++it)
    {
        pNode->SetAttribute(CW2A(it->first).m_psz, CW2A(it->second).m_psz);
    }

    for (std::list<KControlNode*>::iterator it = listElement.begin();
        it != listElement.end();
        ++it)
    {
        TiXmlElement* pElement = new TiXmlElement("");

        if (pElement
            && _AddXml(*(*it), pElement))
        {
            pNode->LinkEndChild(pElement);
        }
        else
        {
            if (pElement)
            {
                delete pElement;
                pElement = NULL;
            }
        }
    }

    return TRUE;
}
