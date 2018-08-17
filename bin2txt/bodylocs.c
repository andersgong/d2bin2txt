#include "global.h"

#define FILE_PREFIX "bodylocs"

typedef struct
{
    char vCode[4];
} ST_LINE_INFO;

typedef struct
{
    char vCode[5];
} ST_BODY_LOCS;

static char *m_apcInternalProcess[] =
{
    "Body Location",
    "*EOL",
    NULL,
};

static unsigned int m_iBodyLocs = 0;
static ST_BODY_LOCS *m_astBodyLocs = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astBodyLocs, ST_BODY_LOCS);

static int BodyLocs_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "Body Location") )
    {
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
        {
            strncpy(acOutput, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
        }

        strncpy(m_astBodyLocs[m_iBodyLocs].vCode, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
        String_Trim(m_astBodyLocs[m_iBodyLocs].vCode);
        m_iBodyLocs++;

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

static char *BodyLocs_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strncpy(pcKey, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

static int process_bodylocs_x(char *acTemplatePath, char *acBinPath, char *acTxtPath)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Code, STRING);

    m_iBodyLocs = 0;

    //m_stCallback.pfnGetKey = BodyLocs_GetKey;
    m_stCallback.pfnFieldProc = BodyLocs_FieldProc;
    m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
    m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);   
    m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

    return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
        pstValueMap, Global_GetValueMapCount(), &m_stCallback);
}

int process_bodylocs(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            return process_bodylocs_x(acTemplatePath, acBinPath, acTxtPath);
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

char *BodyLocs_GetLocStr(unsigned int id)
{
    if ( id >= m_iBodyLocs )
    {
        return NULL;
    }

    return m_astBodyLocs[id].vCode;
}

