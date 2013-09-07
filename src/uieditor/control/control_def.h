/* -------------------------------------------------------------------------
//  File        :   control_def.h
//  Author      :   Sum
//  Datet       :   2013/9/7 16:48
//  Brief       :   
//
// -----------------------------------------------------------------------*/
#ifndef __CONTROL_DEF_H_
#define __CONTROL_DEF_H_

#include <map>
#include <vector>

namespace Control
{

typedef enum _ControlType
{
    emCONTROLTYPE_NULL,
}ControlType;

typedef enum _ControlArea
{
    emCONTROLAREA_HEAD,
    emCONTROLAREA_BODY,
    emCONTROLAREA_FOOT,
}ControlArea;

typedef struct _Object Object;

typedef std::vector<Object> vecControlPool;
typedef std::vector<Object>::iterator vecControlPoolIt;
typedef std::vector<Object>::const_pointer vecControlPoolConstIt;

}

#endif // __CONTROL_DEF_H_