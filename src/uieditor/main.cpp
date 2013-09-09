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

#include <iostream>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TestRunner.h>
#include <cppunit/ui/text/TestRunner.h>

int main()
{
    CppUnit::TestResult    controller;
    CppUnit::TestResultCollector result;
    CppUnit::TestResultCollector rc;

    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    runner.eventManager().addListener(&result);
    runner.run();

    CppUnit::TextOutputter o(&rc, std::cout);
    o.write();
    return rc.wasSuccessful() ? 0 : -1;
}

#endif