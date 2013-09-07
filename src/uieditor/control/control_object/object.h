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
#include "control/control_def.h"

namespace Control
{

interface IObject
{
    virtual CString ToXml() const = 0;
};

typedef struct _Object : public IObject
{
    _Object()
    {
        nId = nControlId = 0;
        nX = nY = 0;
        nWidth = nHeight = 0;
        bIsVisible = TRUE;
        bIsEnable = TRUE;
        controlarea = emCONTROLAREA_BODY;
    }

    virtual CString ToXml() const
    {
        return _T("");
    }

    Global::Define::uint32 nId;
    Global::Define::uint32 nControlId;
    Global::Define::uint32 nX;
    Global::Define::uint32 nY;
    Global::Define::uint32 nWidth;
    Global::Define::uint32 nHeight;
    ControlArea controlarea;
    Global::BOOL bIsVisible;
    Global::BOOL bIsEnable;
    CString strStyleName;
    CString strSkinName;
}Object;

}

#endif // __OBJECT_H_