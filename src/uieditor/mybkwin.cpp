#include "stdafx.h"
#include <windows.h>
#include "mywindow.h"
#include "kcomp_text.h"

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