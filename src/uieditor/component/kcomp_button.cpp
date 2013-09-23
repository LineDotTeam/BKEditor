#include "stdafx.h"
#include "kcomp_button.h"

int KCompButton::m_nButtonId = 72000;

KCompButton::KCompButton()
    : IComponent(m_nButtonId++, "button")
{
    UIEDITOR_XML_ATTRIBUTE_REGISTER_BEGIN()
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("class")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("href")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("show")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("value")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("tip")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("crbg")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("crtext")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("font")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("valign")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("align")
        UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING("skin")
    UIEDITOR_XML_ATTRIBUTE_REGISTER_END()
}

KCompButton::~KCompButton()
{

}

BOOL KCompButton::InitComp()
{
    _SetInit();

    CStringA strTmp;
    strTmp.Format("%d", m_nId);

    SetCompAttrute("value", m_strCompType);
    SetCompAttrute("crbg", "777777");
    SetCompAttrute("height", "30");
    SetCompAttrute("width",  "100");
    SetCompAttrute("id", strTmp.GetString());
    return TRUE;
}

BOOL KCompButton::UninitComp()
{
    return FALSE;
}