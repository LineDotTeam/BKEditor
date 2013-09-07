#include "kcomp_button.h"

int KCompButton::m_nButtonId = 72000;

KCompButton::KCompButton()
{

}

KCompButton::~KCompButton()
{

}

BOOL KCompButton::InitComp()
{
    m_strCompType = "button";
    m_nId         = m_nButtonId++;

    std::string strAttrTmp[MAX_PATH] = {"id", "class", "href", "height", "width", "pos", "show", "value", "tip",
                                        "crbg", "crtext", "font", "valign", "align", "skin", "*"};
    for (size_t i = 0; strAttrTmp[i] != "*"; ++i)
    {
        m_mapAttrute.insert(std::make_pair(strAttrTmp[i], ""));
    }

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