#pragma once

#include "bkwnddlg.h"

/*
使用另外一个资源XML来加载子元素

<dlgfile src=16 />
*/
class CBkDialogFile
    : public CBkDialog
{
    BKOBJ_DECLARE_CLASS_NAME(CBkDialogFile, "dlgfile")

public:

	// 解析xml，加载
    virtual BOOL Load(TiXmlElement* pTiXmlElem)
    {
		if (!CBkWindow::Load(pTiXmlElem))
			return FALSE;

		// 获得xml里的src属性
		CStringA	strSrc = pTiXmlElem->Attribute("src");

		ATLASSERT( !strSrc.IsEmpty() );

		if (strSrc.IsEmpty())
			return FALSE;

		CStringA	strXML;
		UINT		uResId = atoi(strSrc);
		// 根据src指定的值，加载另外的xml
		BOOL		bRet   = BkResManager::LoadResource(uResId,strXML);
		
		ATLASSERT(bRet);

		if (!bRet)
			return TRUE;

		// 解析xml
		TiXmlDocument xmlDoc;
		{
			xmlDoc.Parse(strXML, NULL, TIXML_ENCODING_UTF8);
		}
		if (xmlDoc.Error())
		{
			ATLASSERT(NULL);
			return FALSE;
		}

		// 作为子控件加载
		TiXmlElement *pSubTiElement = xmlDoc.RootElement();
        bRet = __super::LoadChilds(pSubTiElement);

        return bRet;
    }

protected:

};