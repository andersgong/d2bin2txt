#include "global.h"

#define FILE_PREFIX "chartemplate"
#define NAME_PREFIX "ct"

typedef struct
{
    unsigned char vName[30];
    unsigned char vClass;   //playerclass
    unsigned char vLevel;

    unsigned char vAct;
    unsigned char vstr;
    unsigned char vdex;
    unsigned char vint;

    unsigned char vvit;
    unsigned char vMana;
    unsigned char vHitpoints;
    unsigned char vManaRegenBonus;

    unsigned char vVelocity;
    unsigned char vAttackRate;
    unsigned short vOtherRate;

    unsigned int vRightSkill;

    unsigned int vSkill1;
    unsigned int vSkill2;
    unsigned int vSkill3;
    unsigned int vSkill4;
    unsigned int vSkill5;
    unsigned int vSkill6;
    unsigned int vSkill7;
    unsigned int vSkill8;
    unsigned int vSkill9;

    unsigned int vSkillLevel1;
    unsigned int vSkillLevel2;
    unsigned int vSkillLevel3;
    unsigned int vSkillLevel4;
    unsigned int vSkillLevel5;
    unsigned int vSkillLevel6;
    unsigned int vSkillLevel7;
    unsigned int vSkillLevel8;
    unsigned int vSkillLevel9;

    unsigned char vitem1[4];

    unsigned char vitem1loc;
    unsigned char vitem1count;
    unsigned short iPadding31;

    unsigned char vitem2[4];

    unsigned char vitem2loc;
    unsigned char vitem2count;
    unsigned short iPadding33;

    unsigned char vitem3[4];

    unsigned char vitem3loc;
    unsigned char vitem3count;
    unsigned short iPadding35;

    unsigned char vitem4[4];

    unsigned char vitem4loc;
    unsigned char vitem4count;
    unsigned short iPadding37;

    unsigned char vitem5[4];

    unsigned char vitem5loc;
    unsigned char vitem5count;
    unsigned short iPadding39;

    unsigned char vitem6[4];

    unsigned char vitem6loc;
    unsigned char vitem6count;
    unsigned short iPadding41;

    unsigned char vitem7[4];

    unsigned char vitem7loc;
    unsigned char vitem7count;
    unsigned short iPadding43;

    unsigned char vitem8[4];

    unsigned char vitem8loc;
    unsigned char vitem8count;
    unsigned short iPadding45;

    unsigned char vitem9[4];

    unsigned char vitem9loc;
    unsigned char vitem9count;
    unsigned short iPadding47;

    unsigned char vitem10[4];

    unsigned char vitem10loc;
    unsigned char vitem10count;
    unsigned short iPadding49;

    unsigned char vitem11[4];

    unsigned char vitem11loc;
    unsigned char vitem11count;
    unsigned short iPadding51;

    unsigned char vitem12[4];

    unsigned char vitem12loc;
    unsigned char vitem12count;
    unsigned short iPadding53;

    unsigned char vitem13[4];

    unsigned char vitem13loc;
    unsigned char vitem13count;
    unsigned short iPadding55;

    unsigned char vitem14[4];

    unsigned char vitem14loc;
    unsigned char vitem14count;
    unsigned short iPadding57;

    unsigned char vitem15[4];

    unsigned char vitem15loc;
    unsigned char vitem15count;
    unsigned short iPadding59;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "Template",
    NULL,
};

static char *m_apcNotUsed[] =
{
    "tot",
    "LifePerLevel",
    "ManaPerLevel",
    "LifePerVitality",
    "ManaPerMagic",
    "Total Skills",
    "SkillName",
    "baseWClass",
    NULL,
};

static int CharTemplate_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "Class") )
    {
        pcResult = PlayerClass_GetClass(pstLineInfo->vClass);
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

static int CharTemplate_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "Template") )
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

int process_chartemplate(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Name, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Class, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Level, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Act, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, str, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dex, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, int, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, vit, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mana, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Hitpoints, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ManaRegenBonus, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Velocity, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AttackRate, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OtherRate, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, RightSkill, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill6, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill7, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill8, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill9, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkillLevel1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkillLevel2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkillLevel3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkillLevel4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkillLevel5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkillLevel6, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkillLevel7, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkillLevel8, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkillLevel9, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item1, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item1loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item1count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item2, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item2loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item2count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item3, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item3loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item3count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item4, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item4loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item4count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item5, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item5loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item5count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item6, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item6loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item6count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item7, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item7loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item7count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item8, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item8loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item8count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item9, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item9loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item9count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item10, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item10loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item10count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item11, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item11loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item11count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item12, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item12loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item12count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item13, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item13loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item13count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item14, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item14loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item14count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item15, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item15loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item15count, UCHAR);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(playerclass, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = CharTemplate_ConvertValue;
            m_stCallback.pfnFieldProc = CharTemplate_FieldProc;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

