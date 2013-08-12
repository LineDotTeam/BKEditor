/* -------------------------------------------------------------------------
//  File        :   thread_auto_lock.h
//  Author      :   Sum
//  Datet       :   2013/8/5 17:29
//  Brief       :   
//
// -----------------------------------------------------------------------*/
#ifndef __THREAD_LOCK_AUTO_H_
#define __THREAD_LOCK_AUTO_H_

#include <Windows.h>

namespace Publish
{

class KThreadLock
{
public:
    KThreadLock();
    ~KThreadLock();

    BOOL Lock();

    void UnLock();

private:
    CRITICAL_SECTION m_csLock;
};

class KThreadAutoLock
{
public:
    KThreadAutoLock(KThreadLock& lock)
        : m_Lock(lock)
    {
        m_Lock.Lock();
    }

    ~KThreadAutoLock()
    {
        m_Lock.UnLock();
    }

private:
    KThreadLock& m_Lock;
};

}

#endif // __THREAD_LOCK_AUTO_H_