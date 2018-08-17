#include "global.h"

#define FILE_PREFIX "uniquetitle"
#define NAME_PREFIX "ut"

typedef struct
{
    unsigned short vName;   //strings
} ST_LINE_INFO;

static char *m_apcInternalProcess[] = 
{
    "Namco",
     NULL,
};

static unsigned int m_iUniqueTitle = 0;

static int UniqueTitle_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "Name") )
    {
        pcResult = String_FindString(pstLineInfo->vName, NULL);
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }

    return result;
}

static int UniqueTitle_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    int result = 0;

    if ( !strcmp("Namco", acKey) )
    {
        if ( 0 == pcTemplate[0] )
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, m_iUniqueTitle);
            result = 1;
        }

        m_iUniqueTitle++;
    }

    return result;
}

int process_uniquetitle(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
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
            m_stCallback.pfnConvertValue = UniqueTitle_ConvertValue;
            m_stCallback.pfnFieldProc = UniqueTitle_FieldProc;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

