#include "utils.h"
#include <cstdio>

namespace utils
{

BOOL utils::GetXmlStrAttributeA( TiXmlElement *pElement, const char *pName, std::string &strData )
{
    if (pElement)
    {
        const char *pStr = pElement->Attribute(pName);
        if (pStr)
        {
            strData = std::string(pStr);
            return true;
        }
    }
    return false;
}

BOOL utils::GetXmlIntAttribute( TiXmlElement *pElement, const char *pName, int &nData )
{
    if (pElement)
    {
        const char *pStr = pElement->Attribute(pName);
        if (pStr)
        {
                nData = atoi(pStr);
                return true;
        }
    }
    return false;
}

}