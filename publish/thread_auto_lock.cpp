/* -------------------------------------------------------------------------
//  File        :   thread_auto_lock.h.cpp
//  Author      :   Sum
//  Datet       :   2013/8/6 15:25
//  Brief       :   
//
// -----------------------------------------------------------------------*/
//
#include "thread_auto_lock.h"

namespace Publish
{

KThreadLock::KThreadLock()
{
    InitializeCriticalSection(&m_csLock);
}

KThreadLock::~KThreadLock()
{
    DeleteCriticalSection(&m_csLock);
}

BOOL KThreadLock::Lock()
{
    EnterCriticalSection(&m_csLock);
    return TRUE;
}

void KThreadLock::UnLock()
{
    LeaveCriticalSection(&m_csLock);
}

}