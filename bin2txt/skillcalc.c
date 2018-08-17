#include "global.h"

#define FILE_PREFIX "skillcalc"

typedef struct
{
    char vcode[4];
} ST_LINE_INFO;

typedef struct
{
    char vcode[5];
} ST_SKILL_CALC;

static char *m_apcNotUsed[] = 
{
    "*desc",
    NULL,
};

static unsigned int m_uiSkillCalcCount = 0;
static ST_SKILL_CALC *m_astSkillCalc = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astSkillCalc, ST_SKILL_CALC);

char *SkillCalc_GetCalc(unsigned int id)
{
    if ( id >= m_uiSkillCalcCount )
    {
        return NULL;
    }

    return m_astSkillCalc[id].vcode;
}

static int SkillCalc_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    int result = 0;

    if ( !strcmp(acKey, "code") )
    {
        strncpy(m_astSkillCalc[m_uiSkillCalcCount].vcode, pstLineInfo->vcode, sizeof(pstLineInfo->vcode));
        String_Trim(m_astSkillCalc[m_uiSkillCalcCount].vcode);
        m_uiSkillCalcCount++;
    }

    return result;
}

int process_skillcalc(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, code, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_uiSkillCalcCount = 0;

            m_stCallback.pfnConvertValue = SkillCalc_ConvertValue;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
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

