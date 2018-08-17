#include "global.h"

#define FILE_PREFIX "LvlWarp"
#define NAME_PREFIX "lw"

typedef struct
{
    int vId;
    int vSelectX;
    int vSelectY;
    int vSelectDX;
    int vSelectDY;
    int vExitWalkX;
    int vExitWalkY;
    int vOffsetX;
    int vOffsetY;
    int vLitVersion;
    int vTiles;
    unsigned char vDirection[4];
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "Name",
    NULL,
};

static char *m_apcNotUsed[] =
{
    "Beta",
    NULL,
};

static int LvlWarp_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    int result = 0;

    if ( !strcmp(acKey, "Name") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, iLineNo);
        }

        result = 1;
    }

    return result;
}

int process_lvlwarp(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Id, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SelectX, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SelectY, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SelectDX, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SelectDY, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ExitWalkX, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ExitWalkY, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OffsetX, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OffsetY, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LitVersion, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Tiles, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Direction, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnFieldProc = LvlWarp_FieldProc;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;
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

