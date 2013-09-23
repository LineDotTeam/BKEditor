/* -------------------------------------------------------------------------
//  File        :   c_component_def.h
//  Author      :   Sum
//  Datet       :   2013/9/22 21:36
//  Brief       :   
//
// -----------------------------------------------------------------------*/
#ifndef __C_COMPONENT_DEF_H_
#define __C_COMPONENT_DEF_H_

#include <string>

#define UIEDITOR_OBJECT_ATTRIBUTE_BEGIN() \
    HRESULT SetAttribute( \
        std::string& strAttributeName, \
        std::string& strAttributeValue) \
    { \
        hrRetturn = 0;

#define UIEDITOR_OBJECT_ATTRIBUTE_END() \
        return hrRetturn; \
    }

#define UIEDITOR_OBJECT_ATTRIBUTE_STRING_ITEM(strItemName, strItemValue) \
        if (strAttributeName == strItemName) \
        { \
            m_mapAttrute.insert(std::make_pair(strItemName, "")); \
            SetCompAttrute(strItemName, strItemValue); \
            hrRetturn = 0; \
        } \

#define UIEDITOR_XML_ATTRIBUTE_REGISTER_BEGIN() \
    {

#define UIEDITOR_XML_ATTRIBUTE_REGISTER_STRING(strName) \
        m_mapAttrute.insert(std::make_pair(strName, ""));

#define UIEDITOR_XML_ATTRIBUTE_REGISTER_END() \
    }

#endif // __C_COMPONENT_DEF_H_