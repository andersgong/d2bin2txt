#include "global.h"

#define FILE_PREFIX "monai"
#define NAME_PREFIX "ma"

typedef struct
{
    unsigned short vIndex;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "all over in",
    NULL,
};

typedef struct
{
    char vAI[32];
} ST_MON_AI;

static unsigned int m_iMonAiCount = 0;
static ST_MON_AI *m_astMonAi = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astMonAi, ST_MON_AI);

static int MonAI_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "AI") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->vIndex);
        }

        strncpy(m_astMonAi[pstLineInfo->vIndex].vAI, acOutput, sizeof(m_astMonAi[pstLineInfo->vIndex].vAI));
        m_iMonAiCount++;
        return 1;
    }

    return 0;
}

static char *MonAI_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    memset(pcKey, 0, sizeof(pcKey));
    sprintf(pcKey, "%u", pstLineInfo->vIndex);
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

static int process_monai_x(char *acTemplatePath, char *acBinPath, char *acTxtPath)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Index, USHORT);

    m_iMonAiCount = 0;

    //m_stCallback.pfnGetKey = MonAI_GetKey;
    m_stCallback.pfnFieldProc = MonAI_FieldProc;
    m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
    m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
    m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

    return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
        pstValueMap, Global_GetValueMapCount(), &m_stCallback);
}

int process_monai(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            return process_monai_x(acTemplatePath, acBinPath, acTxtPath);
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

char *MonAi_GetAiName(unsigned int id)
{
    if ( id >= m_iMonAiCount )
    {
        return NULL;
    }

    return m_astMonAi[id].vAI;
}

