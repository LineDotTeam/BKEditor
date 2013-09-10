#include "stdafx.h"
#include "kcomp_imgbtn.h"

int KCompImgbtn::m_nImgbtnId = 74000;

KCompImgbtn::KCompImgbtn()
    : IComponent(m_nImgbtnId++, "imgbtn")
{

}

KCompImgbtn::~KCompImgbtn()
{

}

BOOL KCompImgbtn::InitComp()
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
    SetCompAttrute("height", "100");
    SetCompAttrute("width",  "100");
    SetCompAttrute("id", strTmp.GetString());
    return TRUE;
}

BOOL KCompImgbtn::UninitComp()
{
    return FALSE;
}
