#include "global.h"

#define FILE_PREFIX "arena"
#define NAME_PREFIX "ae"

typedef struct
{
    int vSuicide;
    int vPlayerKill;
    int vPlayerKillPercent;
    int vMonsterKill;
    int vPlayerDeath;
    int vPlayerDeathPercent;
    int vMonsterDeath;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "Arena",
    NULL,
};

static int Arena_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "Arena") )
    {
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, iLineNo);
        }
        return 1;
    }

    return 0;
}

static int process_arena_x(char *acTemplatePath, char *acBinPath, char *acTxtPath)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Suicide, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PlayerKill, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PlayerKillPercent, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MonsterKill, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PlayerDeath, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PlayerDeathPercent, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MonsterDeath, INT);

    m_stCallback.pfnFieldProc = Arena_FieldProc;
    m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

    return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
        pstValueMap, Global_GetValueMapCount(), &m_stCallback);
}

int process_arena(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            return process_arena_x(acTemplatePath, acBinPath, acTxtPath);
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

