/* -------------------------------------------------------------------------
//  File        :   global_def.h
//  Author      :   Sum
//  Datet       :   2013/8/6 23:31
//  Brief       :   
//
// -----------------------------------------------------------------------*/
#ifndef __GLOBAL_DEF_H_
#define __GLOBAL_DEF_H_

#include <string>

namespace Global
{

namespace Define
{
    typedef unsigned char       uint8;
    typedef unsigned short      uint16;
    typedef unsigned int        uint32;
    typedef unsigned long long  uint64;
    typedef char                int8;
    typedef short               int16;
    typedef int                 int32;
    typedef long long           int64;
}

#ifndef UNICODE
#define tstring string
#else
#define tstring wstring
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

typedef int BOOL;

#define __STRUCT__ struct
#define interface __STRUCT__

}

#endif // __GLOBAL_DEF_H_