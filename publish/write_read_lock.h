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
    Global::Define::uint32 m_nReaderCount;      ///> ���߼���
    Global::Define::uint32 m_nMaxReader;        ///> ��󲢷�������
    CRITICAL_SECTION m_WriteLock;               ///> д��
    CRITICAL_SECTION m_ReadLock;                ///> ����
    CRITICAL_SECTION m_ReaderCount;             ///> ���߼������ʻ�����
    CRITICAL_SECTION m_MaxReaderLock;           ///> ��󲢷�������
};

}

#endif // __WRITE_READ_LOCK_H_