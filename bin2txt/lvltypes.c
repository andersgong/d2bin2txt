#include "global.h"

#define FILE_PREFIX "lvltypes"
#define NAME_PREFIX "lt"

typedef struct
{
    unsigned char vFilemysp1[60];
    unsigned char vFilemysp2[60];
    unsigned char vFilemysp3[60];
    unsigned char vFilemysp4[60];
    unsigned char vFilemysp5[60];
    unsigned char vFilemysp6[60];
    unsigned char vFilemysp7[60];
    unsigned char vFilemysp8[60];
    unsigned char vFilemysp9[60];
    unsigned char vFilemysp10[60];
    unsigned char vFilemysp11[60];
    unsigned char vFilemysp12[60];
    unsigned char vFilemysp13[60];
    unsigned char vFilemysp14[60];
    unsigned char vFilemysp15[60];
    unsigned char vFilemysp16[60];
    unsigned char vFilemysp17[60];
    unsigned char vFilemysp18[60];
    unsigned char vFilemysp19[60];
    unsigned char vFilemysp20[60];
    unsigned char vFilemysp21[60];
    unsigned char vFilemysp22[60];
    unsigned char vFilemysp23[60];
    unsigned char vFilemysp24[60];
    unsigned char vFilemysp25[60];
    unsigned char vFilemysp26[60];
    unsigned char vFilemysp27[60];
    unsigned char vFilemysp28[60];
    unsigned char vFilemysp29[60];
    unsigned char vFilemysp30[60];
    unsigned char vFilemysp31[60];
    unsigned char vFilemysp32[60];

    unsigned int vAct;
    unsigned int vExpansion;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "Name",
    "Id",
    NULL,
};

static char *m_apcNotUsed[] =
{
    "Beta",
    NULL,
};

static unsigned int m_iLvlTypesCount = 0;

static int LvlTypes_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
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
    else if ( !strcmp("Id", acKey) )
    {
#ifdef USE_TEMPLATE
        if ( 0 == pcTemplate[0] )
#endif
        {
            sprintf(acOutput, "%d", m_iLvlTypesCount);
            result = 1;
        }

        m_iLvlTypesCount++;
    }

    return result;
}

int process_lvltypes(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp1, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp2, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp3, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp4, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp5, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp6, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp7, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp8, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp9, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp10, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp11, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp12, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp13, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp14, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp15, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp16, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp17, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp18, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp19, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp20, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp21, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp22, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp23, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp24, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp25, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp26, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp27, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp28, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp29, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp30, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp31, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filemysp32, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Act, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Expansion, UINT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iLvlTypesCount = 0;

            m_stCallback.pfnFieldProc = LvlTypes_FieldProc;
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

