#include "global.h"

#define FILE_PREFIX "gamble"

typedef struct
{
    char vcode[12];
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "name",
    NULL,
};

static int Gamble_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "name") )
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

        return 1;
    }

    return 0;
}

static char *Gamble_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strcpy(pcKey, pstLineInfo->vcode);
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

int process_gamble(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, code, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            //m_stCallback.pfnGetKey = Gamble_GetKey;
            m_stCallback.pfnFieldProc = Gamble_FieldProc;
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

