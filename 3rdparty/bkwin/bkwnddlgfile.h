#pragma once

#include "bkwnddlg.h"

/*
ʹ������һ����ԴXML��������Ԫ��

<dlgfile src=16 />
*/
class CBkDialogFile
    : public CBkDialog
{
    BKOBJ_DECLARE_CLASS_NAME(CBkDialogFile, "dlgfile")

public:

	// ����xml������
    virtual BOOL Load(TiXmlElement* pTiXmlElem)
    {
		if (!CBkWindow::Load(pTiXmlElem))
			return FALSE;

		// ���xml���src����
		CStringA	strSrc = pTiXmlElem->Attribute("src");

		ATLASSERT( !strSrc.IsEmpty() );

		if (strSrc.IsEmpty())
			return FALSE;

		CStringA	strXML;
		UINT		uResId = atoi(strSrc);
		// ����srcָ����ֵ�����������xml
		BOOL		bRet   = BkResManager::LoadResource(uResId,strXML);
		
		ATLASSERT(bRet);

		if (!bRet)
			return TRUE;

		// ����xml
		TiXmlDocument xmlDoc;
		{
			xmlDoc.Parse(strXML, NULL, TIXML_ENCODING_UTF8);
		}
		if (xmlDoc.Error())
		{
			ATLASSERT(NULL);
			return FALSE;
		}

		// ��Ϊ�ӿؼ�����
		TiXmlElement *pSubTiElement = xmlDoc.RootElement();
        bRet = __super::LoadChilds(pSubTiElement);

        return bRet;
    }

protected:

};