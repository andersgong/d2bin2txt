#include "global.h"

static void *m_apvLogMem[500] = {NULL};

void MemMgr_Init()
{
    unsigned int i;

    for ( i = 0; i < sizeof(m_apvLogMem) / sizeof(m_apvLogMem[0]); i++ )
    {
        m_apvLogMem[i] = NULL;
    }
}

static void MemMgr_LogMem(void *pvAddr)
{
    unsigned int i;

    if ( NULL == pvAddr )
    {
        return;
    }

    for ( i = 0; i < sizeof(m_apvLogMem) / sizeof(m_apvLogMem[0]); i++ )
    {
        if ( NULL == m_apvLogMem[i] )
        {
            m_apvLogMem[i] = pvAddr;
            break;
        }
    }
}

void *MemMgr_Malloc(unsigned int size)
{
    void *pvResult = malloc(size);

    MemMgr_LogMem(pvResult);

    return pvResult;
}

void MemMgr_Free(void *pvAddr)
{
    unsigned int i;

    if ( NULL == pvAddr )
    {
        return;
    }

    for ( i = 0; i < sizeof(m_apvLogMem) / sizeof(m_apvLogMem[0]); i++ )
    {
        if ( pvAddr == m_apvLogMem[i] )
        {
            free(pvAddr);
            m_apvLogMem[i] = NULL;
            break;
        }
    }
}

void MemMgr_FreeAll()
{
    unsigned int i;

    for ( i = 0; i < sizeof(m_apvLogMem) / sizeof(m_apvLogMem[0]); i++ )
    {
        if ( NULL != m_apvLogMem[i] )
        {
            free(m_apvLogMem[i]);
            m_apvLogMem[i] = NULL;
        }
    }
}

