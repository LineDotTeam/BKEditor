#include "stdafx.h"
#include "icomponent.h"

IComponent::IComponent(int nId, const std::string& strType)
: m_nId(nId)
, m_strCompType(strType)
, m_bIsInit(FALSE)
{
    m_rcPos.left   = 0;
    m_rcPos.right  = 0;
    m_rcPos.top    = 0;
    m_rcPos.bottom = 0;
}

IComponent::~IComponent()
{

}

int IComponent::GetId() const
{
    return m_nId;
}

BOOL IComponent::GetCompType(std::string& strCompType) const
{
    strCompType = m_strCompType;
    return TRUE;
}

size_t IComponent::GetAttruteSize()
{
    return m_mapAttrute.size();
}

BOOL IComponent::GetCompRect(CRect& rect) const
{
    if (m_bIsInit)
    {
        rect = m_rcPos;
        return TRUE;
    }
    return FALSE;
}

BOOL IComponent::GetCompAttrute(const std::string& cstrAttrName, std::string& strAttrValue) const
{
    if (m_bIsInit)
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

BOOL IComponent::GetCompAttrute(size_t nIndex, std::string& strAttrValue) const
{
    if (m_bIsInit)
    {
        if (nIndex < 0 || nIndex >= m_mapAttrute.size())
        {
            return FALSE;
        }

        std::map<std::string, std::string>::const_iterator iter = m_mapAttrute.begin();
        while(nIndex--)
        {
            ++iter;
        }

        strAttrValue = iter->second;
        return TRUE;
    }
    return FALSE;
}

BOOL IComponent::SetCompAttrute(const std::string& cstrAttrName, const std::string& cstrAttrValue)
{
    BOOL bIsSuccess = FALSE;
    
    if (m_bIsInit)
    {
        std::map<std::string, std::string>::iterator iter = m_mapAttrute.find(cstrAttrName);
        if (iter != m_mapAttrute.end())
        {
            iter->second = cstrAttrValue;
            bIsSuccess = TRUE;
        }
        if (cstrAttrName == "pos")
        {
            _SetCompRect(cstrAttrValue);
        }
    }

    return bIsSuccess;
}

BOOL IComponent::SetCompAttrute(size_t nIndex, const std::string& cstrAttrValue)
{
    BOOL bIsSuccess = FALSE;

    if (m_bIsInit)
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
        bIsSuccess = TRUE;

        if (iter->first == "pos")
        {
            _SetCompRect(cstrAttrValue);
        }
    }
    return bIsSuccess;
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

BOOL IComponent::DrawComponent(CStringA& strXml)
{
    if (m_bIsInit)
    {
        CStringA strAttr;
        std::string strValue;

        _SetAttr2Xml(strAttr);
        GetCompAttrute("value", strValue);

        strXml.Empty();
        strXml.Format("<%s%s>%s</%s>", m_strCompType.c_str(), strAttr.GetString(), strValue.c_str(), m_strCompType.c_str());
        return TRUE;
    }
    return FALSE;
}

BOOL IComponent::DrawAttrute(CStringA& strXml)
{
    if (m_bIsInit)
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
    return FALSE;
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

void IComponent::_SetInit()
{
    m_bIsInit = TRUE;
}

void IComponent::_SetCompRect(const std::string& cstrAttrValue)
{
    std::string strPos[4];

    size_t nLastPos = 0;
    size_t nPos     = 0;

    for (int i = 0; i < 4; ++i)
    {
        strPos[i].erase();
        nPos = cstrAttrValue.find(",", nLastPos);
        if (nPos != -1)
        {
            strPos[i] = cstrAttrValue.substr(nLastPos, nPos - nLastPos);
            nLastPos = nPos + 1;
        }
        else
        {
            strPos[i] = cstrAttrValue.substr(nLastPos, cstrAttrValue.size() - nLastPos);
            nLastPos = cstrAttrValue.size();
            continue;
        }
    }
    
    // ¸³Öµ
    if (strPos[0].size() != 0)
    {
        m_rcPos.left = StrToIntA(strPos[0].c_str());
    }

    if (strPos[1].size() != 0)
    {
        m_rcPos.top = StrToIntA(strPos[1].c_str());
    }

    if (strPos[2].size() != 0)
    {
        m_rcPos.right = StrToIntA(strPos[2].c_str());
    }
    else
    {
        m_rcPos.right = m_rcPos.left + StrToIntA(m_mapAttrute["width"].c_str());
    }

    if (strPos[3].size() != 0)
    {
        m_rcPos.bottom = StrToIntA(strPos[3].c_str());
    }
    else
    {
        m_rcPos.bottom = m_rcPos.top + StrToIntA(m_mapAttrute["height"].c_str());
    }
}
