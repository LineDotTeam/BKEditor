#include "kcomp_text.h"

int KCompText::m_nTextId = 70000;

KCompText::KCompText()
{

}

KCompText::~KCompText()
{

}

BOOL KCompText::InitComp()
{
    m_strCompType = "text";
    m_nId         = m_nTextId++;

    std::string strAttrTmp[MAX_PATH] = {"id", "class", "href", "height", "width", "pos", "show", "value", "tip", 
                                        "*"};
    for (size_t i = 0; strAttrTmp[i] != "*"; ++i)
    {
        m_mapAttrute.insert(std::make_pair(strAttrTmp[i], ""));
    }

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