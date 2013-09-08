/* -------------------------------------------------------------------------
//  File        :   xml_parse.h
//  Author      :   Sum
//  Datet       :   2013/9/7 20:46
//  Brief       :   
//
// -----------------------------------------------------------------------*/
#ifndef __XML_PARSE_H_
#define __XML_PARSE_H_

#include "include/global_def.h"
#include "ui_xml/ui_xml_def.h"
#include "control/control_def.h"
#include "control/control_pool/control_pool.h"
#include "control/control_tree/kcontrol_tree.h"
#include "3rdparty/tinyxml/tinyxml.h"

class XMLParse
{
public:
    XMLParse();

    ~XMLParse();

    Global::BOOL Parse(const std::wstring& strPath,
        Control::ControlPool& controlpool);

private:
    Global::BOOL _Parse(TiXmlDocument& document);

    Global::BOOL IsElementObject(TiXmlElement& element,
        const std::string& strName);

    Global::BOOL _ParseControl(TiXmlElement& element,
        KControlNode* pNode);

    Global::BOOL _ParseControlAll(TiXmlElement& element,
        KControlNode* pNode);
};

#endif // __XML_PARSE_H_