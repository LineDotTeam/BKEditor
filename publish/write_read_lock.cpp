/* -------------------------------------------------------------------------
//  File        :   write_read_lock.cpp
//  Author      :   Sum
//  Datet       :   2013/8/8 19:16
//  Brief       :   
//
// -----------------------------------------------------------------------*/
//
#include "write_read_lock.h"

namespace Publish
{

KWriteReadLock::KWriteReadLock(Global::Define::uint32 nMaxValue /*= 1000*/)
    : m_nMaxReader(nMaxValue)
    , m_nReaderCount(0)
{
    ::InitializeCriticalSection(&m_ReadLock);
    ::InitializeCriticalSection(&m_WriteLock);
    ::InitializeCriticalSection(&m_MaxReaderLock);
    ::InitializeCriticalSection(&m_ReaderCount);
}

KWriteReadLock::~KWriteReadLock()
{
    ::DeleteCriticalSection(&m_ReaderCount);
    ::DeleteCriticalSection(&m_MaxReaderLock);
    ::DeleteCriticalSection(&m_WriteLock);
    ::DeleteCriticalSection(&m_ReadLock);
}

void KWriteReadLock::ReadLock()
{
    ::EnterCriticalSection(&m_WriteLock);
    ::EnterCriticalSection(&m_ReaderCount);
    m_nReaderCount++;

    if (m_nReaderCount == 1)
    {
        ::EnterCriticalSection(&m_ReadLock);
    }

    if (m_nReaderCount >= m_nMaxReader)
    {
        ::LeaveCriticalSection(&m_ReaderCount);
        ::LeaveCriticalSection(&m_ReaderCount);
        ::EnterCriticalSection(&m_MaxReaderLock); ///> 进入最大个数锁
        return;
    }

    ::LeaveCriticalSection(&m_ReaderCount);
    ::LeaveCriticalSection(&m_WriteLock);
}

void KWriteReadLock::UnReadLock()
{
    ::EnterCriticalSection(&m_ReaderCount);

    if (m_nReaderCount >= m_nMaxReader)
    {
        ::LeaveCriticalSection(&m_MaxReaderLock);
    }

    m_nReaderCount--;

    if (m_nReaderCount == 0)
    {
        ::LeaveCriticalSection(&m_ReadLock); ///> 最后一个读者
    }

    ::LeaveCriticalSection(&m_ReaderCount);
}

Global::BOOL KWriteReadLock::TryRead()
{

}

void KWriteReadLock::WriteLock()
{
    ::EnterCriticalSection(&m_WriteLock);
    ::EnterCriticalSection(&m_ReadLock);
}

void KWriteReadLock::UnWriteLock()
{
    ::LeaveCriticalSection(&m_ReadLock);
    ::LeaveCriticalSection(&m_WriteLock);
}

Global::BOOL KWriteReadLock::TryWrite()
{

}

}