#include "stdafx.h"
#include "kcomp_text.h"

int KCompText::m_nTextId = 70000;

KCompText::KCompText()
    : IComponent(m_nTextId++, "text")
{
    UIEDITOR_XML_ATTRIBUTE_REGISTER_BEGIN()
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("class")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("href")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("show")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("value")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("tip")
    UIEDITOR_XML_ATTRIBUTE_REGISTER_END()
}

KCompText::~KCompText()
{

}

BOOL KCompText::InitComp()
{
    _SetInit();

    CStringA strTmp;
    strTmp.Format("%d", m_nId);

    SetCompAttrute("value", m_strCompType);
    SetCompAttrute("class", "cont_text");
    SetCompAttrute("height", "30");
    SetCompAttrute("width",  "100");
    SetCompAttrute("id", strTmp.GetString());
    return TRUE;
}

BOOL KCompText::UninitComp()
{
    return FALSE;
}