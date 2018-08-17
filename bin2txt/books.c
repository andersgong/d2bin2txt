#include "global.h"

#define FILE_PREFIX "books"
#define NAME_PREFIX "bk"

/*
Name：书名，未使用。

Nameco：名字后缀。此书的命名为Book + 后缀。

Completed：是否已完成。

ScrollSpellCode：对应卷轴的物品代码。

BookSpellCode：书的物品代码。

pSpell：使用效果。

SpellIcon：是否有使用图标。

ScrollSkill：使用卷轴对应的技能。

BookSkill：使用书对应的技能，即数量减1，并相当于使用一个卷轴。

BaseCost：书的价格。

CostPerCharge：每增加一个卷轴所增加的价格。
*/

typedef struct
{
    unsigned short vName; //strings
    char vSpellIcon;
    unsigned char iPadding0;

    unsigned int vpSpell;

    unsigned int vScrollSkill;  //skills
    unsigned int vBookSkill;    //skills

    unsigned int vBaseCost;

    unsigned int vCostPerCharge;

    unsigned char vScrollSpellCode[4];
    unsigned char vBookSpellCode[4];
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "Completed",
    "Namco",
    NULL,
};

static int Books_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "Namco") )
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
    else if ( !strcmp(acKey, "Completed") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            acOutput[0] = '1';
            acOutput[1] = 0;
        }

        return 1;
    }

    return 0;
}

static int Books_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "Name") )
    {
        pcResult = String_FindString(pstLineInfo->vName, "dummy");
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
    else if ( !strcmp(acKey, "ScrollSkill") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vScrollSkill);
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
    else if ( !strcmp(acKey, "BookSkill") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vBookSkill);
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

int process_books(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Name, USHORT); //strings
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SpellIcon, CHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, pSpell, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ScrollSkill, UINT);  //skills
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BookSkill, UINT);    //skills

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BaseCost, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CostPerCharge, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ScrollSpellCode, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BookSpellCode, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(string, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(skills, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnFieldProc = Books_FieldProc;
            m_stCallback.pfnConvertValue = Books_ConvertValue;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

