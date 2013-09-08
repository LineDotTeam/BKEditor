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
    TiXmlElement* pControlObject = document.RootElement();
    std::string sRootName = pControlObject->Value();
    
    if (sRootName != XML_DIALOG_ROOT)
    {
        return FALSE;
    }

    TiXmlNode* pControlObjectNode = document.FirstChild(XML_DIALOG_ROOT);

    if (pControlObjectNode == NULL)
    {
        return false;
    }

    KControlNode* pNode = new KControlNode;

    pControlObject = pControlObjectNode->FirstChildElement();

    if (!pControlObject)
    {
        return FALSE;
    }

    return _ParseControlAll(*pControlObject, pNode);
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
    KControlNode* pNode)
{
    if (!pNode)
    {
        return FALSE;
    }

    KControlNode* pNodeChild = pNode->AddChild();
    TiXmlAttribute* pAttribute = element.FirstAttribute();

    if (!pAttribute
        || !pNodeChild)
    {
        return FALSE;
    }

    pNodeChild->SetName(CA2W(element.Value()).m_psz);

    for (; pAttribute != NULL;
        pAttribute = pAttribute->Next())
    {
        std::string strName(pAttribute->Name());
        std::string strValue(pAttribute->Value());

        if (strName.empty())
        {
            if (strValue.empty())
            {
                strValue = "0";
            }

            pNodeChild->SetAttr(CA2W(strName.c_str()).m_psz,
                CA2W(pAttribute->Value()).m_psz);
        }
    }

    if (element.FirstChildElement())
    {
        _ParseControlAll(element, pNodeChild);
    }

    return TRUE;
}

Global::BOOL XMLParse::_ParseControlAll(TiXmlElement& element,
    KControlNode* pNode)
{
    if (!pNode)
    {
        return FALSE;
    }

    for (TiXmlElement* pControlObject = element.FirstChildElement();
        pControlObject != NULL;
        pControlObject = pControlObject->NextSiblingElement())
    {
        _ParseControl(element, pNode);
    }

    return TRUE;
}
