/* -------------------------------------------------------------------------
//  File        :   control_pool.cpp
//  Author      :   Sum
//  Datet       :   2013/9/7 17:50
//  Brief       :   
//
// -----------------------------------------------------------------------*/
//
#include "control_pool.h"

namespace Control
{

ControlPool::ControlPool()
{
    m_nPresenPos = 0;
}

ControlPool::~ControlPool()
{

}

void ControlPool::Push(Object& object)
{
    m_vecControlPool.push_back(object);
}

void ControlPool::Pop()
{
    m_vecControlPool.pop_back();
}

Object ControlPool::Find(Global::Define::uint32 nId)
{
    if (m_vecControlPool.empty())
    {
        return Object();
    }

    for (vecControlPoolIt it = m_vecControlPool.begin();
        it != m_vecControlPool.end();
        ++it)
    {
        if ((*it).nId == nId)
        {
            return (*it);
        }
    }

    return Object();
}

void ControlPool::Clear()
{
    m_vecControlPool.clear();
}

Object ControlPool::Begin()
{
    m_nPresenPos = 0;

    if (m_vecControlPool.empty())
    {
        return Object();
    }

    return m_vecControlPool[m_nPresenPos];
}

Object ControlPool::Next()
{
    ++m_nPresenPos;

    if (m_nPresenPos >= m_vecControlPool.size())
    {
        return Object();
    }

    return m_vecControlPool[m_nPresenPos];
}

Object ControlPool::End()
{
    return Object();
}

Global::BOOL ControlPool::Empty() const
{
    return m_vecControlPool.empty();
}

Global::Define::uint32 ControlPool::Size() const
{
    return (Global::Define::uint32)m_vecControlPool.size();
}

}