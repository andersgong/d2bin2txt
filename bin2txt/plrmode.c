#include "global.h"

#define FILE_PREFIX "plrmode"

typedef struct
{
    unsigned char vName[32];
    unsigned char vToken[20];
} ST_LINE_INFO;

typedef struct
{
    unsigned char vName[32];
    //unsigned char vToken[20];
    unsigned char vCode[20];
} ST_PLRMODE;

static char *m_apcInternalProcess[] =
{
    "Code",
    NULL,
};

static unsigned int m_iPlrModeCount = 0;
static ST_PLRMODE *m_astPlrMode = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astPlrMode, ST_PLRMODE);

static int PlrMode_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    int result = 0;

    if ( !strcmp("Code", acKey) )
    {
        if ( 0 == pcTemplate[0] )
        {
            strncpy(m_astPlrMode[m_iPlrModeCount].vCode, pstLineInfo->vToken, sizeof(m_astPlrMode[m_iPlrModeCount].vCode));
            strncpy(m_astPlrMode[m_iPlrModeCount].vName, pstLineInfo->vName, sizeof(m_astPlrMode[m_iPlrModeCount].vName));
            strcpy(acOutput, m_astPlrMode[m_iPlrModeCount].vCode);
            result = 1;
        }
        else
        {
            strncpy(m_astPlrMode[m_iPlrModeCount].vCode, pcTemplate, sizeof(m_astPlrMode[m_iPlrModeCount].vCode));
            strncpy(m_astPlrMode[m_iPlrModeCount].vName, pstLineInfo->vName, sizeof(m_astPlrMode[m_iPlrModeCount].vName));
        }
        m_iPlrModeCount++;
    }

    return result;
}

static char *PlrMode_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strcpy(pcKey, pstLineInfo->vToken);
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

int process_plrmode(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Name, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Token, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iPlrModeCount = 0;

            m_stCallback.pfnFieldProc = PlrMode_FieldProc;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            //m_stCallback.pfnGetKey = PlrMode_GetKey;
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

char *PlrMode_GetCode(unsigned int id)
{
    if ( id >= m_iPlrModeCount )
    {
        return NULL;
    }

    return m_astPlrMode[id].vCode;
}

