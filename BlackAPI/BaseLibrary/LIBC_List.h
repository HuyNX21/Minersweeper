//
// File: LIBC_List.h
// Summary: LIBC_List-compatible implementation backed by std::list and std::mutex
// Note: Keep manual Lock/UnLock usage when shared across tasks.
//       This replaces SYSF_sem* wrappers with std::mutex (C++11 standard).
//

#if !defined(__LIBC_LIST_H__)
#define __LIBC_LIST_H__

#include <list>
#include <mutex>
#include <new>

#include "BLKC_Log.h"

template <class TYPE> class LIBC_List
{
private:
    std::list<TYPE*>                     m_list;
    typename std::list<TYPE*>::iterator  m_current;
    std::mutex                           m_mutex;

    void removeAll(void)
    {
        m_list.clear();
        m_current = m_list.end();
    }

public:
    LIBC_List()
        : m_list(), m_current(m_list.end())
    {
    }

    ~LIBC_List()
    {
        removeAll();
    }

    void Lock(void)
    {
        m_mutex.lock();
    }

    void UnLock(void)
    {
        m_mutex.unlock();
    }

    void add(TYPE* pData)
    {
        try {
            m_list.push_back(pData);
        }
        catch (const std::bad_alloc&) {
            LOG_ERROR("LIBC_List: malloc failed");
        }
    }

    void del(TYPE* pData)
    {
        for (typename std::list<TYPE*>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
            if (*it == pData) {
                if (m_current == it) {
                    ++m_current;
                }
                m_list.erase(it);
                break;
            }
        }
    }

    TYPE* findFirst(void)
    {
        if (m_list.empty()) {
            return NULL;
        }

        m_current = m_list.begin();
        TYPE* dtptr = *m_current;
        ++m_current;
        return dtptr;
    }

    TYPE* findNext(void)
    {
        if (m_current == m_list.end()) {
            return NULL;
        }

        TYPE* dtptr = *m_current;
        ++m_current;
        return dtptr;
    }

    short getCount() const
    {
        return static_cast<short>(m_list.size());
    }

    void delAll()
    {
        removeAll();
    }
};

#endif // !defined(__LIBC_LIST_H__)
