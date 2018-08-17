#include "global.h"

#define FILE_PREFIX "MissCalc"

typedef struct
{
    unsigned char vcode[4];
} ST_LINE_INFO;

typedef struct
{
    char vcode[5];
} ST_MISS_CALC;

static char *m_apcNotUsed[] =
{
    "*desc",
    NULL,
};

static unsigned int m_iMissCalc = 0;
static ST_MISS_CALC *m_astMissCalc = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astMissCalc, ST_MISS_CALC);

static int MissCalc_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "code") )
    {
        strncpy(m_astMissCalc[m_iMissCalc].vcode, pstLineInfo->vcode, sizeof(pstLineInfo->vcode));
        String_Trim(m_astMissCalc[m_iMissCalc].vcode);
        m_iMissCalc++;
    }

    return 0;
}

static char *MissCalc_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strcpy(pcKey, pstLineInfo->vcode);
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

int process_misscalc(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, code, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iMissCalc = 0;

            m_stCallback.pfnConvertValue = MissCalc_ConvertValue;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            //m_stCallback.pfnGetKey = MissCalc_GetKey;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

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

char *MissCalc_GetCalcCode(unsigned int id)
{
    if ( id >= m_iMissCalc )
    {
        return NULL;
    }

    return m_astMissCalc[id].vcode;
}

