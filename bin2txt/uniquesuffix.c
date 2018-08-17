#include "global.h"

#define FILE_PREFIX "uniquesuffix"
#define NAME_PREFIX "us"

typedef struct
{
    unsigned short vName;   //strings
} ST_LINE_INFO;

static int UniqueSuffix_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "Name") )
    {
        pcResult = String_FindString(pstLineInfo->vName, "dummy");
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->vName);
        }
        result = 1;
    }

    return result;
}

int process_uniquesuffix(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Name, USHORT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(string, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = UniqueSuffix_ConvertValue;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}


