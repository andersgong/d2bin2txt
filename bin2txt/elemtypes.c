#include "global.h"

#define FILE_PREFIX "elemtypes"

typedef struct
{
    char vCode[4];
} ST_LINE_INFO;

typedef struct
{
    char vCode[5];
} ST_ELEM_TYPES;

static char *m_apcInternalProcess[] =
{
    "Elemental Type",
    "*EOL",
    NULL,
};

static unsigned int m_iElemTypes = 0;
static ST_ELEM_TYPES *m_astElemTypes = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astElemTypes, ST_ELEM_TYPES);

static int ElemTypes_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "Elemental Type") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            strncpy(acOutput, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
        }

        strncpy(m_astElemTypes[m_iElemTypes].vCode, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
        String_Trim(m_astElemTypes[m_iElemTypes].vCode);
        m_iElemTypes++;

        return 1;
    }
    else if ( !strcmp(acKey, "*EOL") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static char *ElemTypes_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strcpy(pcKey, pstLineInfo->vCode);
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

int process_elemtypes(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Code, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iElemTypes = 0;

            //m_stCallback.pfnGetKey = ElemTypes_GetKey;
            m_stCallback.pfnFieldProc = ElemTypes_FieldProc;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
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

char *ElemTypes_GetElemStr(unsigned int id)
{
    if ( id >= m_iElemTypes )
    {
        return NULL;
    }

    return m_astElemTypes[id].vCode;
}

