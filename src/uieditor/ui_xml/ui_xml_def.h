/* -------------------------------------------------------------------------
//  File        :   ui_xml_def.h
//  Author      :   Sum
//  Datet       :   2013/9/7 15:28
//  Brief       :   
//
// -----------------------------------------------------------------------*/
#ifndef __UI_XML_DEF_H_
#define __UI_XML_DEF_H_

#include <string>
#include <vector>

typedef std::vector<std::string> vecControlXmlInfo;
typedef std::vector<std::string>::iterator vecControlXmlInfoIt;
typedef std::vector<std::string>::const_iterator vecControlXmlInfoConstIt;

typedef std::vector<std::vector<std::string> > vecControlXmlListInfo;
typedef std::vector<std::vector<std::string> >::iterator vecControlXmlListInfoIt;
typedef std::vector<std::vector<std::string> >::const_iterator vecControlXmlInfoListConstIt;

#define XML_DIALOG_ROOT                     "dialog"

#define XML_DIALOG_CONTROL_EDIT             "edit"
#define XML_DIALOG_CONTROL_BUTTON           "button"
#define XML_DIALOG_CONTROL_TEXT             "text"
#define XML_DIALOG_CONTROL_LIST             "list"
#define XML_DIALOG_CONTROL_DLG              "dlg"

#define ID_OBJECT_ATTRIBUTE                 "id"
#define CID_OBJECT_ATTRIBUTE                "cid"
#define STYLE_OBJECT_ATTRIBUTE              "style"
#define SKIN_OBJECT_ATTRIBUTE               "skin"
#define POS_OBJECT_ATTRIBUTE                "pos"
#define VISIBLE_OBJECT_ATTRIBUTE            "visible"
#define ENABLE_OBJECT_ATTRIBUTE             "enable"

#define HEAD_OBJECT_AREA                    "head"
#define BODY_OBJECT_AREA                    "body"
#define FOOT_OBJECT_AREA                    "foot"


#endif // __UI_XML_DEF_H_