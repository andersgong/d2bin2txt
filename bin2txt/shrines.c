#include "global.h"

#define FILE_PREFIX "shrines"
#define NAME_PREFIX "sr"

typedef struct
{
    unsigned int vCode;
    unsigned int vArg0;
    unsigned int vArg1;

    unsigned int vDurationmyspinmyspframes;

    unsigned char vresetmysptimemyspinmyspminutes;
    unsigned char vrarity;
    unsigned char vviewmyspname[32];

    unsigned char vniftyphrase[32];

    unsigned short iPadding20;
    unsigned int iPadding21;
    unsigned int iPadding22;
    unsigned int iPadding23;
    unsigned int iPadding24;
    unsigned int iPadding25;
    unsigned int iPadding26;
    unsigned int iPadding27;
    unsigned int iPadding28;
    unsigned int iPadding29;

    unsigned int iPadding30;
    unsigned int iPadding31;
    unsigned int iPadding32;
    unsigned int iPadding33;
    unsigned int iPadding34;
    unsigned int iPadding35;
    unsigned int iPadding36;
    unsigned int iPadding37;
    unsigned int iPadding38;
    unsigned int iPadding39;

    unsigned int iPadding40;
    unsigned int iPadding41;
    unsigned int iPadding42;
    unsigned int iPadding43;

    unsigned short iPadding44;
    unsigned short veffectclass;

    unsigned short vLevelMin;
    unsigned short iPadding45;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "Shrine Type",
    "Shrine name",
    NULL,
};

static char *m_apcNotUsed[] =
{
    "Effect",
    NULL,
};

static int Shrines_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "Shrine Type") )
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

        return 1;
    }
    else if ( !strcmp(acKey, "Shrine name") )
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

        return 1;
    }

    return 0;
}

int process_shrines(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Code, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Arg0, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Arg1, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Durationmyspinmyspframes, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, resetmysptimemyspinmyspminutes, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rarity, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, viewmyspname, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, niftyphrase, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, effectclass, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LevelMin, USHORT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnFieldProc = Shrines_FieldProc;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;
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

