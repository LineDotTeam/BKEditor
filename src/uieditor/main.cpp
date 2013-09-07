#include "stdafx.h"
#include <windows.h>
#include "dialog/uieditor_dlg.h"
#include "component/kcomp_text.h"


#ifndef _CONSOLE
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int /*nCmdShow*/)
{
    CString strPath;
    GetModuleFileName((HMODULE)&__ImageBase, strPath.GetBuffer(MAX_PATH + 10), MAX_PATH);
    strPath.ReleaseBuffer();
    strPath.Truncate(strPath.ReverseFind(L'\\') + 1);
    strPath += L"res";

    BkResManager::SetResourcePath(strPath);

    BkSkin::LoadSkins(XML_BK_SKIN_DEF);
    BkStyle::LoadStyles(XML_BK_STYLE_DEF);
    BkString::Load(XML_BK_STRING_DEF);

    KMyWindow kWin(hInstance);
    kWin.DoModal();

    return 0;
}
#else

#include "control/control_tree/kcontrol_tree.h"
BOOL TestKControlNode();
int _tmain()
{
    BOOL bRet = FALSE;

    bRet = TestKControlNode();

    return bRet ? 0 : 1;
}

BOOL TestKControlNode()
{
    BOOL bRet = FALSE;

    KControlNode* pControlRoot = new KControlNode();

    if (pControlRoot == NULL)
    {
        goto Exit0;
    }

    pControlRoot->SetName(L"a");
    pControlRoot->SetAttr(L"key", L"value");
    pControlRoot->SetAttr(L"key2", L"value2");
    pControlRoot->RemoveAttr(L"key");

    KControlNode* pChild = pControlRoot->AddChild();

    if (pChild == NULL)
    {
        goto Exit0;
    }
    
    pChild->SetName(L"b");
    pChild->SetAttr(L"key", L"value");
    pChild->SetAttr(L"key2", L"value2");

    KControlNode* pChild2 = pChild->AddChild();

    if (pChild == NULL)
    {
        goto Exit0;
    }
    
    pChild2->SetName(L"c");
    pChild2->SetAttr(L"key", L"value");
    pChild2->SetAttr(L"key2", L"value2");

Exit0:
    if (pControlRoot)
    {
        delete pControlRoot;
        pControlRoot = NULL;
    }
    
    return bRet;
}

#endif