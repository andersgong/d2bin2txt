#include "global.h"

#define FILE_PREFIX "storepage"

typedef struct
{
    char vCode[4];
} ST_LINE_INFO;

typedef struct
{
    char vCode[5];
} ST_STORE_PAGE;

static unsigned int m_iStorePage = 0;
static ST_STORE_PAGE *m_astStorePage = NULL;

static char *m_apcInternalProcess[] =
{
    "Store Page",
    NULL,
};

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astStorePage, ST_STORE_PAGE);

static int StorePage_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "Store Page") )
    {
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
        {
            strncpy(acOutput, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
        }

        strncpy(m_astStorePage[m_iStorePage].vCode, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
        m_iStorePage++;
        return 1;
    }

    return 0;
}

static char *StorePage_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strcpy(pcKey, pstLineInfo->vCode);
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

static int process_storepage_x(char *acTemplatePath, char *acBinPath, char *acTxtPath)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Code, STRING);

    m_iStorePage = 0;

    //m_stCallback.pfnGetKey = StorePage_GetKey;
    m_stCallback.pfnFieldProc = StorePage_FieldProc;
    m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
    m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
    m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

    return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
        pstValueMap, Global_GetValueMapCount(), &m_stCallback);
}

int process_storepage(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            return process_storepage_x(acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_OTHER_DEPEND:
        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
        case EN_MODULE_INIT:
        default:
            break;
    }

    return 1;
}

char *StorePage_GetCode(unsigned int id)
{
    if ( id >= m_iStorePage )
    {
        return NULL;
    }

    return m_astStorePage[id].vCode;
}

