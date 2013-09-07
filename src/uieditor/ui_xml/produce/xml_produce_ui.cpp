/* -------------------------------------------------------------------------
//  File        :   xml_produce_ui.cpp
//  Author      :   Sum
//  Datet       :   2013/9/7 15:59
//  Brief       :   
//
// -----------------------------------------------------------------------*/
//
#include "xml_produce_ui.h"

UIXmlProduce::UIXmlProduce()
{

}

UIXmlProduce::~UIXmlProduce()
{

}

Global::BOOL UIXmlProduce::Produce(const ControlPool& controlpool,
    const std::wstring& strPath)
{
    if (strPath.empty()
        || controlpool.Empty())
    {
        return FALSE;
    }

    
    return TRUE;
}
