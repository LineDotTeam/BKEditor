#pragma once

#include <string.h>
#include <Windows.h>
#include <vector>
#include "3rdparty\tinyxml\tinyxml.h"

namespace utils
{
    BOOL GetXmlStrAttributeA( TiXmlElement *pElement, char *pName, std::string &strData );
    BOOL GetXmlIntAttribute( TiXmlElement *pElement, char *pName, int &nData );
    template<class T>
    inline T* vector_to_array(std::vector<T>* v)
    {
        return v->empty() ? NULL : &*v->begin();
    }
}