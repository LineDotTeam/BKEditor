/* -------------------------------------------------------------------------
//  File        :   write_read_lock.h
//  Author      :   Sum
//  Datet       :   2013/8/8 17:11
//  Brief       :   
//
// -----------------------------------------------------------------------*/
#ifndef __WRITE_READ_LOCK_H_
#define __WRITE_READ_LOCK_H_

#include "global_def.h"
#include <Windows.h>

namespace Publish
{

class KWriteReadLock
{
public:
    KWriteReadLock(Global::Define::uint32 nMaxValue = 1000);

    ~KWriteReadLock();

    void ReadLock();

    void UnReadLock();

    Global::BOOL TryRead();

    void WriteLock();

    void UnWriteLock();

    Global::BOOL TryWrite();

private:
    Global::Define::uint32 m_nReaderCount;      ///> 读者计数
    Global::Define::uint32 m_nMaxReader;        ///> 最大并发读者数
    CRITICAL_SECTION m_WriteLock;               ///> 写锁
    CRITICAL_SECTION m_ReadLock;                ///> 读锁
    CRITICAL_SECTION m_ReaderCount;             ///> 读者计数访问互斥锁
    CRITICAL_SECTION m_MaxReaderLock;           ///> 最大并发读者锁
};

}

#endif // __WRITE_READ_LOCK_H_