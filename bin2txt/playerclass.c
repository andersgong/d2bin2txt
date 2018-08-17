#include "global.h"

#define FILE_PREFIX "playerclass"

typedef struct
{
    char vCode[4];
} ST_LINE_INFO;

typedef struct
{
    char vCode[5];
} ST_PLAYER_CLASS;

static char *m_apcInternalProcess[] =
{
    "Player Class",
    NULL,
};

static unsigned int m_iPlayerClass= 0;
static ST_PLAYER_CLASS *m_astPlayerClass = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astPlayerClass, ST_PLAYER_CLASS);

static int PlayerClass_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "Player Class") )
    {
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
        {
            strncpy(acOutput, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
        }

        strncpy(m_astPlayerClass[m_iPlayerClass].vCode, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
        String_Trim(m_astPlayerClass[m_iPlayerClass].vCode);
        m_iPlayerClass++;

        return 1;
    }

    return 0;
}

static char *PlayerClass_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strcpy(pcKey, pstLineInfo->vCode);
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

static int process_playerclass_x(char *acTemplatePath, char *acBinPath, char *acTxtPath)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Code, STRING);

    m_iPlayerClass = 0;

    //m_stCallback.pfnGetKey = PlayerClass_GetKey;
    m_stCallback.pfnFieldProc = PlayerClass_FieldProc;
    m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
    m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
    m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

    return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
        pstValueMap, Global_GetValueMapCount(), &m_stCallback);
}

int process_playerclass(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            return process_playerclass_x(acTemplatePath, acBinPath, acTxtPath);
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

char *PlayerClass_GetClass(unsigned int id)
{
    if ( id >= m_iPlayerClass )
    {
        return NULL;
    }

    return m_astPlayerClass[id].vCode;
}

