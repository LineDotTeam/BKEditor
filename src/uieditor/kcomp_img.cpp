#include "kcomp_img.h"

int KCompImg::m_nImgId = 76000;

KCompImg::KCompImg()
{

}

KCompImg::~KCompImg()
{

}

BOOL KCompImg::InitComp()
{
    m_strCompType = "img";
    m_nId         = m_nImgId++;

    std::string strAttrTmp[MAX_PATH] = {"id", "class", "href", "height", "width", "pos", "show", "value", "tip",
                                        "crbg", "crtext", "font", "valign", "align", "skin", "sub", "*"};
    for (size_t i = 0; strAttrTmp[i] != "*"; ++i)
    {
        m_mapAttrute.insert(std::make_pair(strAttrTmp[i], ""));
    }

    CStringA strTmp;
    strTmp.Format("%d", m_nId);

    SetCompAttrute("value", m_strCompType);
    SetCompAttrute("crbg", "777777");
    SetCompAttrute("height", "100");
    SetCompAttrute("width",  "100");
    SetCompAttrute("id", strTmp.GetString());
    return TRUE;
}

BOOL KCompImg::UninitComp()
{
    return FALSE;
}

