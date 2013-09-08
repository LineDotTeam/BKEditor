/* -------------------------------------------------------------------------
//  File        :   i_xml_produce.h
//  Author      :   Sum
//  Datet       :   2013/9/7 15:32
//  Brief       :   
//
// -----------------------------------------------------------------------*/
#ifndef __I_XML_PRODUCE_H_
#define __I_XML_PRODUCE_H_

#include "3rdparty/tinyxml/tinyxml.h"
#include "include/utils.h"
#include "include/global_def.h"
#include "control/control_pool/control_pool.h"
#include <string>

interface IXmlProduce
{
    virtual Global::BOOL Produce(const Control::ControlPool& controlpool,
        const std::wstring& strPath) = 0;
};

#endif // __I_XML_PRODUCE_H_