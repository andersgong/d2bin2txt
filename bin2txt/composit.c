#include "global.h"

#define FILE_PREFIX "composit"

typedef struct
{
    unsigned char vName[32];
    unsigned char vToken[20];
} ST_LINE_INFO;

static char *Composit_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strncpy(pcKey, pstLineInfo->vToken, sizeof(pstLineInfo->vToken));
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

int process_composit_x(char *acTemplatePath, char *acBinPath, char *acTxtPath)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Name, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Token, STRING);

    //m_stCallback.pfnGetKey = Composit_GetKey;

    return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
        pstValueMap, Global_GetValueMapCount(), &m_stCallback);
}

int process_composit(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            return process_composit_x(acTemplatePath, acBinPath, acTxtPath);
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

