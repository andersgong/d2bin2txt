#include "global.h"

#define FILE_PREFIX "hiredesc"

typedef struct
{
    char vCode[4];
} ST_LINE_INFO;

typedef struct
{
    char vCode[5];
} ST_HIRE_DESC;

static unsigned int m_iHireDesc = 0;
static ST_HIRE_DESC *m_astHireDesc = NULL;

static char *m_apcInternalProcess[] =
{
    "Hireling Description",
    "*EOL",
    NULL,
};

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astHireDesc, ST_HIRE_DESC);

char *HireDesc_GetDesc(unsigned int id)
{
    if ( id >= m_iHireDesc )
    {
        return NULL;
    }

    return m_astHireDesc[id].vCode;
}

static int HireDesc_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "Hireling Description") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            strncpy(acOutput, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
        }

        strncpy(m_astHireDesc[m_iHireDesc].vCode, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
        String_Trim(m_astHireDesc[m_iHireDesc].vCode);
        m_iHireDesc++;

        return 1;
    }
    else if ( !strcmp(acKey, "*EOL") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static char *HireDesc_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strcpy(pcKey, pstLineInfo->vCode);
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

int process_hiredesc(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Code, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iHireDesc = 0;

            //m_stCallback.pfnGetKey = HireDesc_GetKey;
            m_stCallback.pfnFieldProc = HireDesc_FieldProc;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
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

