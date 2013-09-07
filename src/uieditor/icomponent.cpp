#include "icomponent.h"

IComponent::~IComponent()
{

}

int IComponent::GetId() const
{
    if (_IsInitComp())
    {
        return m_nId;
    }
    return 0;
}

BOOL IComponent::GetCompType(std::string& strCompType) const
{
    if (_IsInitComp())
    {
        if (!m_strCompType.empty())
        {
            strCompType = m_strCompType;
            return TRUE;
        }
    }
    return FALSE;
}

BOOL IComponent::SetCompAttrute(const std::string& cstrAttrName, const std::string& cstrAttrValue)
{
    if (_IsInitComp())
    {
        std::map<std::string, std::string>::iterator iter = m_mapAttrute.find(cstrAttrName);
        if (iter != m_mapAttrute.end())
        {
            iter->second = cstrAttrValue;
            return TRUE;
        }
    }
    return FALSE;
}

BOOL IComponent::SetCompAttrute(size_t nIndex, const std::string& cstrAttrValue)
{
    if (_IsInitComp())
    {
        if (nIndex < 0 || nIndex >= m_mapAttrute.size())
        {
            return FALSE;
        }

        std::map<std::string, std::string>::iterator iter = m_mapAttrute.begin();
        while(nIndex--)
        {
            ++iter;
        }

        iter->second = cstrAttrValue;
        return TRUE;
    }
    return FALSE;
}

BOOL IComponent::GetCompAttrute(const std::string& cstrAttrName, std::string& strAttrValue) const
{
    if (_IsInitComp())
    {
        std::map<std::string, std::string>::const_iterator iter = m_mapAttrute.find(cstrAttrName);
        if (iter != m_mapAttrute.end())
        {
            strAttrValue = iter->second;
            return TRUE;
        }
    }
    return FALSE;
}

BOOL IComponent::DrawComponent(CStringA& strXml)
{
    CStringA strAttr;
    std::string strValue;

    _SetAttr2Xml(strAttr);
    GetCompAttrute("value", strValue);

    strXml.Empty();
    strXml.Format("<%s%s>%s</%s>", m_strCompType.c_str(), strAttr.GetString(), strValue.c_str(), m_strCompType.c_str());
    return TRUE;
}

BOOL IComponent::DrawAttrute(CStringA& strXml)
{
    strXml.Empty();

    CStringA strTmp;
    int i = 0;

    for (std::map<std::string, std::string>::iterator iter = m_mapAttrute.begin(); iter != m_mapAttrute.end(); ++iter, ++i)
    {
        strTmp.Empty();
        strTmp.Format("<text class=\"cont_text\" pos=\"10,%d,80,%d\">%s :</text><realwnd id=\"%d\" show=\"1\" pos=\"80,%d,190,%d\"/>", 
            50 + i * ATTRUTE_HEIGHT, 50 + i * ATTRUTE_HEIGHT + ATTRUTE_HEIGHT - 10, iter->first.c_str(),
            enAttruteEdit_Begin + i, 50 + i * ATTRUTE_HEIGHT + 5, 50 + i * ATTRUTE_HEIGHT + ATTRUTE_HEIGHT - 5);
        strXml.Append(strTmp);
    }
    return TRUE;
}

BOOL IComponent::InitAttrute(KTipEdit3* pEdit)
{
    int i = 0;
    CString strTmp;

    for (std::map<std::string, std::string>::iterator iter = m_mapAttrute.begin(); iter != m_mapAttrute.end(); ++iter, ++i)
    {
        strTmp.Format(L"%s", CA2W(iter->second.c_str()));
        pEdit[i].SetText(strTmp);
    }

    return TRUE;
}

BOOL IComponent::_IsInitComp() const
{
    if (m_mapAttrute.empty())
    {
        MessageBoxA(NULL, NULL, "No InitComp", NULL);
        return FALSE;
    }
    return TRUE;
}

void IComponent::_SetAttr2Xml(CStringA& strXML)
{
    strXML.Empty();
    std::string strAttr("");

    for (std::map<std::string, std::string>::iterator iter = m_mapAttrute.begin(); iter != m_mapAttrute.end(); ++iter)
    {
        if (iter->second != "")
        {
            strAttr += " ";
            strAttr += iter->first;
            strAttr += "=\"";
            strAttr += iter->second;
            strAttr += "\"";
        }
    }
    strXML.Append(strAttr.c_str());
}
