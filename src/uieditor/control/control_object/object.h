/* -------------------------------------------------------------------------
//  File        :   object.h
//  Author      :   Sum
//  Datet       :   2013/9/7 16:05
//  Brief       :   
//
// -----------------------------------------------------------------------*/
#ifndef __OBJECT_H_
#define __OBJECT_H_

#include <atlstr.h>
#include "include/global_def.h"

namespace Control
{

typedef struct _Object
{
    _Object()
    {
        nId = nControlId = 0;
        nX = nY = 0;
        nWidth = nHeight = 0;
        bIsVisible = TRUE;
        bIsEnable = TRUE;
    }

    Global::Define::uint32 nId;
    Global::Define::uint32 nControlId;
    Global::Define::uint32 nX;
    Global::Define::uint32 nY;
    Global::Define::uint32 nWidth;
    Global::Define::uint32 nHeight;
    Global::BOOL bIsVisible;
    Global::BOOL bIsEnable;
    CString strStyleName;
    CString strSkinName;
}Object;

}

#endif // __OBJECT_H_