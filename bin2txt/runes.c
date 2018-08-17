#include "global.h"

#define FILE_PREFIX "runes"

/*
Title 	Runes.txt
Description 	by Nefarius
Sent by 	
Name: This controls the string key that will be looked up inside the TBLs to display the name of this item in-game.

Rune Name: The name of the runeword, probably for reference only as the string key is determined by the previous column.

Complete: Is this rune word completed and useable (can it be made) in-game? (boolean 0 = cannot be made in-game, 1 = can be made in-game).

Server: Is this rune word restricted to the realms (setting this to true will have the same effect as setting Complete to false). (boolean 0 = runeword available both in single player / open games and on the realms, 1 = runeword available only on the 
realms).

IType1 to IType6: These are ID pointers from ItemTypes.txt and control in what item type this runeword can be made.

EType1 to EType3: These are ID pointers from ItemTypes.txt and control in what item type this runeword cannot be made (even when this item type is a subtype of an item type specified within IType1 to IType6.

*runes: The names of the runes used in the runeword, as they would appear in the item display. Comment field only.

Rune1 to Rune6: These are ID pointers from Misc.txt (note: technically also from the Armor and Weapon tables). The fields control what runes are required to make the rune word and in what order they are to be socketed.

T1Code1 to T1Code7: An ID pointer of a property from Properties.txt, these columns control each of the 7 modifiers that a runeword can have at most.

T1Param1 to T1Param7: The parameter passed on to the associated property, this is used to pass skill IDs, state IDs, monster IDs, montype IDs and the like on to the properties that require them, these fields support calculations.

T1Min1 to T1Min6: Minimum value to assign to the associated property. Certain properties have special interpretations based on stat encoding (e.g. chance-to-cast and charged skills). See the File Guide for Properties.txt and ItemStatCost.txt for further 
details.

T1Max1 to T1Max6: Maximum value to assign to the associated property. Certain properties have special interpretations based on stat encoding (e.g. chance-to-cast and charged skills). See the File Guide for Properties.txt and ItemStatCost.txt for further 
details.

eol: terminator field, not used in game, primary purpose is to keep Microsoft Excel from misbehaving.

*/

/*
文件名解析：
Rune(s)：符文，此处的意思为符文之语。
此文件记录了游戏中所有符文之语，每一行代表一个。


回复

    2楼
    2011-09-09 18:55

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：
Name: 符文之语的编号，统一以Runeword*的形式表达，不可重复
Rune Name: 此符文之语的名字，如精神此列就是Spirit
Complete: 是否完成，即是否可在游戏中使用。1代表可以，0不可以
Server: 无用参数
iType1-6: 此符文之语适用的装备类型，与ItemTypes.txt关联
eType1-3: 此符文之语不适用的装备类型，所填值应是某一iType的子类型，与ItemTypes.txt关联
此符文之语最终适用的装备类型集合为 {x=适用装备类型集合|x属于某一iType且x不属于任意eType}
如某一种符文之语可能适用除了剑以外的所有武器，那就就在iType1填weap，eType1填swor

*Runes 此符文之语的注释，一般来说都会写成此符文之语的顺序
在某个神符之语中，需要的神符，一定要按顺序[从第一个需求神符~最后一个需求神符（总数不多于6个）]；

Rune1-6 此符文之语组成符文的代码，有顺序要求，如精神是r07 r10 r09 r11
T1Code1-7 属性1-7的代码，与properties关联 某个神符之语的固定魔法属性
T1Param1-7 属性1-7的参数
T1Min1-7 属性1-7的最小值参数
T1Max1-7 属性1-7的最大值参数

由此可知，符文之语装备最多有7项附加属性

回复

    3楼
    2011-09-09 18:55

    举报 |

    zqtjingzi
    小吧主
    12

此外需要注意的是，通过我的试验，当你想增加新的符文之语时，通过新加一行的方式来做是不行的，会在游戏过程中制作好此装备的瞬间出错。所以如果我们想制作自己的符文之语，可以利用那些complete列不为1的行，然后只需在PatchString.tbl
中将此行的编号重新赋予一个我们想要的中文名字即可。

*/

typedef struct
{
    unsigned char vName[64];

    unsigned char vRunemyspName[64];

    unsigned char vcomplete;
    unsigned char vserver;
    unsigned short iPadding32;

    unsigned short iPadding33;
    unsigned short vitype1; //itemtypes

    unsigned short vitype2; //itemtypes
    unsigned short vitype3; //itemtypes

    unsigned short vitype4; //itemtypes
    unsigned short vitype5; //itemtypes

    unsigned short vitype6; //itemtypes
    unsigned short vetype1; //itemtypes

    unsigned short vetype2; //itemtypes
    unsigned short vetype3; //itemtypes

    unsigned int vRune1;    //miscs
    unsigned int vRune2;

    unsigned int vRune3;
    unsigned int vRune4;

    unsigned int vRune5;
    unsigned int vRune6;

    int vT1Code1;  //properties
    int vT1Param1;
    int vT1Min1;
    int vT1Max1;

    int vT1Code2;  //properties
    int vT1Param2;
    int vT1Min2;
    int vT1Max2;

    int vT1Code3;  //properties
    int vT1Param3;
    int vT1Min3;
    int vT1Max3;

    int vT1Code4;  //properties
    int vT1Param4;
    int vT1Min4;
    int vT1Max4;

    int vT1Code5;  //properties
    int vT1Param5;
    int vT1Min5;
    int vT1Max5;

    int vT1Code6;  //properties
    int vT1Param6;
    int vT1Min6;
    int vT1Max6;

    int vT1Code7;  //properties
    int vT1Param7;
    int vT1Min7;
    int vT1Max7;
} ST_LINE_INFO;

typedef struct
{
    unsigned int vT1Code1;  //properties
    unsigned int vT1Param1;
    unsigned int vT1Min1;
    unsigned int vT1Max1;
} ST_RUNE_CODE;

static char *m_apcInternalProcess[] =
{
    "eol",
    NULL,
};

static char *m_apcNotUsed[] =
{
    "*runes",
    NULL,
};

static int Runes_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "eol") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static int Runes_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int id;
    int result = 0;

    if ( strlen("itype1") == strlen(acKey) && 1 == sscanf(acKey, "itype%d", &id) )
    {
        unsigned short *pwItype = &pstLineInfo->vitype1;
        pcResult = ItemTypes_GetItemCode(pwItype[id - 1]);
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
    else if ( strlen("etype1") == strlen(acKey) && 1 == sscanf(acKey, "etype%d", &id) )
    {
        unsigned short *pwItype = &pstLineInfo->vetype1;
        pcResult = ItemTypes_GetItemCode(pwItype[id - 1]);
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
    else if ( strlen("Rune1") == strlen(acKey) && 1 == sscanf(acKey, "Rune%d", &id) )
    {
        unsigned int *pwItype = &pstLineInfo->vRune1;
        pcResult = Misc_GetItemUniqueCode(pwItype[id - 1]);
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
    else if ( strlen("T1Code1") == strlen(acKey) && 1 == sscanf(acKey, "T1Code%d", &id) )
    {
        ST_RUNE_CODE *pwItype = (ST_RUNE_CODE *)&pstLineInfo->vT1Code1;
        pcResult = Properties_GetProperty(pwItype[id - 1].vT1Code1);
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
    else if ( strlen("T1Param1") == strlen(acKey) && 1 == sscanf(acKey, "T1Param%d", &id) )
    {
        ST_RUNE_CODE *pwItype = (ST_RUNE_CODE *)&pstLineInfo->vT1Code1;
        if ( 0 != pwItype[id - 1].vT1Param1 )
        {
            pcResult = Skills_GetSkillName(pwItype[id - 1].vT1Param1);
            if ( pcResult )
            {
                strcpy(acOutput, pcResult);
            }
            else
            {
                sprintf(acOutput, "%d", pwItype[id - 1].vT1Param1);
            }
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }

    return result;
}

int process_runes(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Name, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, RunemyspName, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, complete, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, server, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype1, USHORT); //itemtypes

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype2, USHORT); //itemtypes
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype3, USHORT); //itemtypes

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype4, USHORT); //itemtypes
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype5, USHORT); //itemtypes

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype6, USHORT); //itemtypes
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etype1, USHORT); //itemtypes

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etype2, USHORT); //itemtypes
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etype3, USHORT); //itemtypes

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Rune1, UINT);    //miscs
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Rune2, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Rune3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Rune4, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Rune5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Rune6, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Code1, INT);  //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Param1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Min1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Max1, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Code2, INT);  //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Param2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Min2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Max2, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Code3, INT);  //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Param3, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Min3, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Max3, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Code4, INT);  //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Param4, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Min4, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Max4, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Code5, INT);  //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Param5, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Min5, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Max5, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Code6, INT);  //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Param6, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Min6, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Max6, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Code7, INT);  //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Param7, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Min7, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, T1Max7, INT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(itemtypes, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(armor, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(weapons, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(misc, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(properties, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(skills, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = Runes_ConvertValue;
            m_stCallback.pfnFieldProc = Runes_FieldProc;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

