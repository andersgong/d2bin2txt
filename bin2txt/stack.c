#include "global.h"

static unsigned char *m_abGlobalStack = NULL;
static unsigned int m_uiStackElemSize = 0;
static unsigned int m_uiStackElemCount = 0;
static unsigned int m_uiStackIndex = 0;

void * Stack_Create(unsigned int uiElemSize, unsigned int uiElemCount)
{
    if ( NULL != m_abGlobalStack && uiElemCount * uiElemSize > m_uiStackElemCount * m_uiStackElemSize )
    {
        MemMgr_Free(m_abGlobalStack);
        m_abGlobalStack = NULL;
    }

    if ( NULL == m_abGlobalStack )
    {
        m_abGlobalStack = (unsigned char *)MemMgr_Malloc(uiElemCount * uiElemSize);
    }

    if ( NULL == m_abGlobalStack )
    {
        return NULL;
    }

    m_uiStackElemSize = uiElemSize;
    m_uiStackElemCount = uiElemCount;
    m_uiStackIndex = 0;

    return m_abGlobalStack;
}

void Stack_Release(void *pvStack)
{
    if ( NULL != m_abGlobalStack )
    {
        MemMgr_Free(m_abGlobalStack);
        m_abGlobalStack = NULL;
    }

    m_uiStackElemSize = 0;
    m_uiStackElemCount = 0;
    m_uiStackIndex = 0;
}

int Stack_Push(void *pvStack, unsigned char *pcElement, unsigned int uiElemSize)
{
    if ( m_uiStackIndex >= m_uiStackElemCount || uiElemSize > m_uiStackElemSize )
    {
        assert(0);
        return 0;
    }

    memcpy(&m_abGlobalStack[m_uiStackIndex * m_uiStackElemSize], pcElement, uiElemSize);
    m_abGlobalStack[m_uiStackIndex * m_uiStackElemSize + uiElemSize] = 0;
    m_uiStackIndex++;

    return 1;
}

int Stack_Pop(void *pvStack, unsigned char **ppcElement)
{
    if ( m_uiStackIndex <= 0 )
    {
        assert(0);
        return 0;
    }

    m_uiStackIndex--;
    *ppcElement = &m_abGlobalStack[m_uiStackIndex * m_uiStackElemSize];

    return 1;
}

int Stack_IsEmpty(void *pvStack)
{
    if ( m_uiStackIndex <= 0 )
    {
        return 1;
    }

    return 0;
}

