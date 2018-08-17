#include "global.h"

#define FILE_PREFIX "monplace"
#define NAME_PREFIX "me"

typedef struct
{
    unsigned short vId;
} ST_LINE_INFO;

typedef struct
{
    char vcode[32];
} ST_MON_PLACE;

static char *m_apcInternalProcess[] =
{
    "code",
    NULL,
};

static unsigned int m_iMonPlaceCount = 0;
static ST_MON_PLACE *m_astMonPlace = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astMonPlace, ST_MON_PLACE);

static int MonPlace_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "code") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->vId);
        }

        strncpy(m_astMonPlace[pstLineInfo->vId].vcode, acOutput, sizeof(m_astMonPlace[pstLineInfo->vId].vcode));
        String_Trim(m_astMonPlace[pstLineInfo->vId].vcode);
        m_iMonPlaceCount++;
        return 1;
    }

    return 0;
}

int process_monplace(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Id, USHORT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iMonPlaceCount = 0;

            m_stCallback.pfnFieldProc = MonPlace_FieldProc;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            break;

        default:
            break;
    }

    return 1;
}

char *MonPlace_GetPlaceName(unsigned int id)
{
    if ( id >= m_iMonPlaceCount )
    {
        return NULL;
    }

    return m_astMonPlace[id].vcode;
}

