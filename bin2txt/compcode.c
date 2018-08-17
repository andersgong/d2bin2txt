#include "global.h"

#define FILE_PREFIX "compcode"

typedef struct
{
    char vcode[4];
} ST_LINE_INFO;

typedef struct
{
    char vcomponent[5];
} ST_COMPCODE;

static char *m_apcInternalProcess[] =
{
    "component",
    NULL,
};

static unsigned int m_iCompcodeCount = 0;
static ST_COMPCODE *m_astCompcode = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astCompcode, ST_COMPCODE);

static int Compcode_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "component") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            strncpy(acOutput, pstLineInfo->vcode, sizeof(pstLineInfo->vcode));
        }

        strncpy(m_astCompcode[m_iCompcodeCount].vcomponent, pstLineInfo->vcode, sizeof(pstLineInfo->vcode));
        m_iCompcodeCount++;
        return 1;
    }

    return 0;
}

static char *Compcode_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strncpy(pcKey, pstLineInfo->vcode, sizeof(pstLineInfo->vcode));
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

int process_compcode(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, code, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iCompcodeCount = 0;

            m_stCallback.pfnFieldProc = Compcode_FieldProc;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            //m_stCallback.pfnGetKey = Compcode_GetKey;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            break;

        default:
            break;
    }

    return 1;
}

char *Compcode_GetCode(unsigned int id)
{
    if ( id >= m_iCompcodeCount )
    {
        return NULL;
    }

    return m_astCompcode[id].vcomponent;
}

