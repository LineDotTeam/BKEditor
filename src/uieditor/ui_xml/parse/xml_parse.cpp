/* -------------------------------------------------------------------------
//  File        :   xml_parse.cpp
//  Author      :   Sum
//  Datet       :   2013/9/7 20:58
//  Brief       :   
//
// -----------------------------------------------------------------------*/
//
#include "xml_parse.h"
#include <atlbase.h>
#include "include/utils.h"

std::string g_strMustAttribute_all[] =
{
    ID_OBJECT_ATTRIBUTE,
    POS_OBJECT_ATTRIBUTE
};

std::string g_strOptionalAttribute_all[] =
{
    CID_OBJECT_ATTRIBUTE,
    SKIN_OBJECT_ATTRIBUTE,
    STYLE_OBJECT_ATTRIBUTE,
    VISIBLE_OBJECT_ATTRIBUTE,
    ENABLE_OBJECT_ATTRIBUTE,
};

XMLParse::XMLParse()
{

}

XMLParse::~XMLParse()
{

}

Global::BOOL XMLParse::Parse(const std::wstring& strPath,
    Control::ControlPool& controlpool)
{
    if (strPath.empty())
    {
        return FALSE;
    }

    controlpool.Clear();

    TiXmlDocument xmlTiny;

    if(xmlTiny.LoadFile(CW2A(strPath.c_str()).m_psz))
    {
        return _Parse(xmlTiny);
    }

    return TRUE;
}

Global::BOOL XMLParse::_Parse(TiXmlDocument& document)
{
    TiXmlElement* controlobject = document.RootElement();
    std::string sRootName = controlobject->Value();
    
    if (sRootName != XML_DIALOG_ROOT)
    {
        return FALSE;
    }

    TiXmlNode* controlobjectNode = document.FirstChild(XML_DIALOG_ROOT);

    if (controlobjectNode == NULL)
    {
        return false;
    }

    KControlNode* pNode = new KControlNode;

    for (controlobject = controlobjectNode->FirstChildElement();
        controlobject != NULL;
        controlobject = controlobject->NextSiblingElement())
    {
        _ParseControl(*controlobject,
            g_strMustAttribute_all,
            g_strOptionalAttribute_all,
            XML_DIALOG_CONTROL_EDIT,
            pNode);
        _ParseControl(*controlobject,
            g_strMustAttribute_all,
            g_strOptionalAttribute_all,
            XML_DIALOG_CONTROL_BUTTON,
            pNode);
        _ParseControl(*controlobject,
            g_strMustAttribute_all,
            g_strOptionalAttribute_all,
            XML_DIALOG_CONTROL_TEXT,
            pNode);
        _ParseControl(*controlobject,
            g_strMustAttribute_all,
            g_strOptionalAttribute_all,
            XML_DIALOG_CONTROL_LIST,
            pNode);
    }

    return TRUE;
}

Global::BOOL XMLParse::IsElementObject(TiXmlElement& element,
    const std::string& strName)
{
    if (strName.empty())
    {
        return FALSE;
    }

    if (strName == element.Value())
    {
        return TRUE;
    }

    return FALSE;
}

Global::BOOL XMLParse::_ParseControl(TiXmlElement& element,
    std::string strMustAttribute[],
    std::string strOptionalAttribute[],
    const std::string& strName,
    KControlNode* pNode)
{
    if (!pNode
        || strName.empty()
        || strMustAttribute == NULL
        || strOptionalAttribute == NULL)
    {
        return FALSE;
    }

    if (IsElementObject(element, strName.c_str()))
    {
        KControlNode* pNodeChild = pNode->AddChild();
        pNodeChild->SetName(CA2W(strName.c_str()).m_psz);

        for (Global::Define::uint32 nIndex = 0;
            nIndex < sizeof(strMustAttribute) / sizeof(std::string);
            ++nIndex)
        {
            std::string strValue;
            if (!utils::GetXmlStrAttributeA(&element, strMustAttribute[nIndex].c_str(), strValue))
            {
                return FALSE;
            }
        }

        for (Global::Define::uint32 nIndex = 0;
            nIndex < sizeof(strOptionalAttribute) / sizeof(std::string);
            ++nIndex)
        {
            std::string strValue;
            utils::GetXmlStrAttributeA(&element, strOptionalAttribute[nIndex].c_str(), strValue);
            pNodeChild->SetAttr(CA2W(strOptionalAttribute[nIndex].c_str()).m_psz, CA2W(strValue.c_str()));
        }
    }

    return TRUE;
}
