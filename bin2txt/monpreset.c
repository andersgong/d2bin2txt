#include "global.h"

#define FILE_PREFIX "monpreset"

typedef struct
{
    unsigned char vAct;
    unsigned char iPadding0;
    unsigned short vPlace;
} ST_LINE_INFO;

static int MonPreset_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult = NULL;
    int result = 0;

    if ( !strcmp(acKey, "Place") )
    {
        if ( 1 == pstLineInfo->iPadding0 )
        {
            pcResult = MonStats_GetStatsName(pstLineInfo->vPlace);
        }
        else if ( 0 == pstLineInfo->iPadding0 )
        {
            pcResult = MonPlace_GetPlaceName(pstLineInfo->vPlace);
        }
        else if ( 2 == pstLineInfo->iPadding0 )
        {
            pcResult = SuperUniques_GetItemUniqueCode(pstLineInfo->vPlace);
        }
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

int process_monpreset(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Act, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Place, USHORT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(monstats, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(monplace, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(superuniques, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = MonPreset_ConvertValue;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

