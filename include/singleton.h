#ifndef SINGLETON
#define SINGLETON

#define NULL 0

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

typedef int BOOL;

template<typename T>
class Singleton
{
protected:
    static T* m_pInst;

    Singleton() {}
    virtual ~Singleton() {}

public:
    static T* Instance()
    {
        if (m_pInst == NULL)
        {
            m_pInst = new T();
        }
        return m_pInst;
    }

    static void Destroy()
    {
        if (m_pInst != NULL)
        {
            delete m_pInst;
        }
        m_pInst = NULL;
    }

    virtual BOOL Initialize() { return TRUE; }

private:
    Singleton(const Singleton &s);
    Singleton& operator=(const Singleton &s);
};


#endif