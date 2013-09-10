#include "stdafx.h"
#include "kcomp_button.h"

int KCompButton::m_nButtonId = 72000;

KCompButton::KCompButton()
    : IComponent(m_nButtonId++, "button")
{

}

KCompButton::~KCompButton()
{

}

BOOL KCompButton::InitComp()
{
    std::string strAttrTmp[MAX_PATH] = {"id", "class", "href", "height", "width", "pos", "show", "value", "tip",
                                        "crbg", "crtext", "font", "valign", "align", "skin", "*"};
    for (size_t i = 0; strAttrTmp[i] != "*"; ++i)
    {
        m_mapAttrute.insert(std::make_pair(strAttrTmp[i], ""));
    }

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