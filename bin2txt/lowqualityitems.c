#include "global.h"

#define FILE_PREFIX "lowqualityitems"
#define NAME_PREFIX "li"

typedef struct
{
    unsigned char vName[34];
} ST_LINE_INFO;

static unsigned int m_iLowQualityItemCount = 0;

static int LowQualityItems_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "Name") )
    {
        if ( 0 == pstLineInfo->vName[0] )
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, m_iLowQualityItemCount);
            m_iLowQualityItemCount++;
            return 1;
        }

        m_iLowQualityItemCount++;
    }

    return 0;
}

int process_lowqualityitems(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Name, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnConvertValue = LowQualityItems_ConvertValue;

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

