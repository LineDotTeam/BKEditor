/* -------------------------------------------------------------------------
//  File        :   control_pool.h
//  Author      :   Sum
//  Datet       :   2013/9/7 16:34
//  Brief       :   
//
// -----------------------------------------------------------------------*/
#ifndef __CONTROL_POOL_H_
#define __CONTROL_POOL_H_

#include "control/control_def.h"
#include "control/control_object/object.h"

namespace Control
{

class ControlPool
{
public:
    ControlPool();

    ~ControlPool();

    void Push(Object& object);

    void Pop();

    Object Find(Global::Define::uint32 nId);

    Object Begin();

    Object Next();

    Object End();

    Global::BOOL Empty() const;

    Global::Define::uint32 Size() const;

    void Clear();

private:
    vecControlPool m_vecControlPool;
    Global::Define::uint32 m_nPresenPos;
};

}

#endif // __CONTROL_POOL_H_