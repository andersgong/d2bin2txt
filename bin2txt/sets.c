#include "global.h"

#define FILE_PREFIX "sets"
#define NAME_PREFIX "se"

/*
Title 	Sets.txt File Guide
Description 	by Alkalund, revised by Myhrginoc
Sent by 	
Refer to the Set Items File Guide for fields that define the attributes of specific items in a set.

index: string key linked to by the set field in SetItems.txt - used to tie all of the set's items to the same set.

name: string key to item's name in a .tbl file.

version: 0 = Available in Classic D2 and LoD Expansion; 100 = available in LoD Expansion only.

level: set level, perhaps intended as a minimum level for partial or full attributes to appear (reference only, not loaded into game).

GOLD ATTRIBUTES

PCode2a,PCode2b to PCode5a,PCode5b: An ID pointer of a property from Properties.txt, these columns control each of the five pairs of different partial set modifiers a set item can grant you at most.

PParam2a,PParam2b to PParam5a,PParam5b: The parameter passed on to the associated property, this is used to pass skill IDs, state IDs, monster IDs, montype IDs and the like on to the properties that require them, these fields support calculations.

PMin2a,PMin2b to PMin5a,PMin5b: Minimum value to assign to the associated property. Certain properties have special interpretations based on stat encoding (e.g. chance-to-cast and charged skills). See the File Guides for Properties.txt and ItemStatCost.
txt for further details.

PMax2a,PMax2b to PMax5a,PMax5b: Maximum value to assign to the associated property. Certain properties have special interpretations based on stat encoding (e.g. chance-to-cast and charged skills). See the File Guides for Properties.txt and ItemStatCost.
txt for further details.

FCode1 to FCode8: An ID pointer of a property from Properties.txt, these columns control each of the eight different full set modifiers a set item can grant you at most.

FParam1 to FParam8: The parameter passed on to the associated property, this is used to pass skill IDs, state IDs, monster IDs, montype IDs and the like on to the properties that require them, these fields support calculations.

FMin1 to FMin8: Minimum value to assign to the associated property. Certain properties have special interpretations based on stat encoding (e.g. chance-to-cast and charged skills). See the File Guides for Properties.txt and ItemStatCost.txt for further 
details.

FMax1 to FMax8: Maximum value to assign to the associated property. Certain properties have special interpretations based on stat encoding (e.g. chance-to-cast and charged skills). See the File Guides for Properties.txt and ItemStatCost.txt for further 
details.

*eol: terminator field, not used in game, primary purpose is to keep Microsoft Excel from misbehaving.

APPENDIX

Gold attributes will appear depending on how many set items are equipped, both partial set attributes (not all set items equipped) and full set attributes (all set items equipped only). If a set has X number of items, at most there will be X-1 partial 
attributes on any item.

PCode2a,PCode2b -> when any second set item is also equipped.
PCode3a,PCode3b -> when any third set item is also equipped.
PCode4a,PCode4b -> when any fourth set item is also equipped.
PCode5a,PCode5b -> when any fifth set item is also equipped.

*/

/*
index –物品名称索引；
name –绿色套装的名称；
version –物品出现的版本，0代表原版，100代表资料片；
level –套装的级别；
PCode2a –套装的物品拥有两套以上时所提供的附加第一级别魔法属性；
PParam2a -套装的物品拥有两套以上时所提供的魔法属性参数（第一级别）；
PMin2a -套装的物品拥有两套以上时所提供的魔法属性的最小值（第一级别）；
PMax2a -套装的物品拥有两套以上时所提供的魔法属性的最大值（第一级别）；
PCode2b -套装的物品拥有两套以上时所提供的附加第二级别魔法属性；
PParam2b -套装的物品拥有两套以上时所提供的魔法属性参数（第二级别）；
PMin2b -套装的物品拥有两套以上时所提供的魔法属性的最小值（第二级别）；
PMax2b -套装的物品拥有两套以上时所提供的魔法属性的最大值（第二级别）；
PCode3a -套装的物品拥有三套以上时所提供的附加第一级别魔法属性；
PParam3a -套装的物品拥有三套以上时所提供的魔法属性参数（第一级别）；
PMin3a -套装的物品拥有三套以上时所提供的魔法属性的最小值（第一级别）；
PMax3a -套装的物品拥有两套以上时所提供的魔法属性的最大值（第一级别）；
PCode3b -套装的物品拥有三套以上时所提供的附加第二级别魔法属性；
PParam3b -套装的物品拥有三套以上时所提供的魔法属性参数（第二级别）；
PMin3b -套装的物品拥有三套以上时所提供的魔法属性的最小值（第二级别）；
PMax3b -套装的物品拥有三套以上时所提供的魔法属性的最小值（第二级别）；

之后诸如：Pcode#a、Pparam#a、Pmin#a、Pmax#a、Pcode#b、Pparam#b、Pmin#b、Pmax#b等参见以上描述即可。


FCode1 – 全套装备集齐后的附加1号魔法属性；
FParam1 -全套装备集齐后的附加1号魔法参数；
FMin1 -全套装备集齐后的附加1号魔法属性的最小值；
FMax1 -全套装备集齐后的附加1号魔法属性的最大值；

之后诸如：Fcode#、Fparam#、Fmin#、Fmax#等参见以上描述即可。

*eol –文件结束标志。 

*/

/*
文件名解析：
Set(s)：套装。
所以此文件记录了游戏中所有套装。
文件中的每一行代表一个套装。


回复

    2楼
    2011-09-08 21:08

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    3楼
    2011-09-08 21:08

    举报 |

    zqtjingzi
    小吧主
    12

Index：物品索引，也是此套装在游戏中的代码。

Name：名字，此套装在游戏中的名字。

Version：物品所能出现的最低版本。

Level：此套装的套装等级，也就是此套装中每件装备的物品等级。

PCode2a：属性2a的代码。所谓2a，就是指穿齐两件套装后获得的第一个属性。同理，2b是指穿齐两件套装后获得的第二个属性。3a是指穿齐三件套装后获得的第一个属性。

PParam2a：属性2a的参数。

PMin2a：属性2a的最小值参数。

PMax2a：属性2a的最大值参数。

以下2b、3a、3b、4a、4b、5a、5b各4列，含义类似。

FCode1-8：穿齐全部套装后的第1-8个属性的代码。

FParam1-8：穿齐全部套装后的第1-8个属性的参数。

FMin1-8：穿齐全部套装后的第1-8个属性的最小值参数。

FMax1-8：穿齐全部套装后的第1-8个属性的最大值参数。

Eol：行结束标志，必须填0。
*/

typedef struct
{
    unsigned short wSetId;
    unsigned short vname;   //strings

    unsigned int vversion;

    unsigned int iPadding2;
    unsigned int dwSetItems;

    int vPCode2a;   //properties
    int vPParam2a;  //skills
    int vPMin2a;
    int vPMax2a;

    int vPCode2b;   //properties
    int vPParam2b;  //skills
    int vPMin2b;
    int vPMax2b;

    int vPCode3a;   //properties
    int vPParam3a;  //skills
    int vPMin3a;
    int vPMax3a;

    int vPCode3b;   //properties
    int vPParam3b;  //skills
    int vPMin3b;
    int vPMax3b;

    int vPCode4a;   //properties
    int vPParam4a;  //skills
    int vPMin4a;
    int vPMax4a;

    int vPCode4b;   //properties
    int vPParam4b;  //skills
    int vPMin4b;
    int vPMax4b;

    int vPCode5a;   //properties
    int vPParam5a;  //skills
    int vPMin5a;
    int vPMax5a;

    int vPCode5b;   //properties
    int vPParam5b;  //skills
    int vPMin5b;
    int vPMax5b;

    int vFCode1;    //properties
    int vFParam1;
    int vFMin1;
    int vFMax1;

    int vFCode2;    //properties
    int vFParam2;
    int vFMin2;
    int vFMax2;

    int vFCode3;    //properties
    int vFParam3;
    int vFMin3;
    int vFMax3;

    int vFCode4;    //properties
    int vFParam4;
    int vFMin4;
    int vFMax4;

    int vFCode5;    //properties
    int vFParam5;
    int vFMin5;
    int vFMax5;

    int vFCode6;    //properties
    int vFParam6;
    int vFMin6;
    int vFMax6;

    int vFCode7;    //properties
    int vFParam7;
    int vFMin7;
    int vFMax7;

    int vFCode8;    //properties
    int vFParam8;
    int vFMin8;
    int vFMax8;

    unsigned int iPadding68;    //D2SetItemsTxt* pSetItem1
    unsigned int iPadding69;

    unsigned int iPadding70;
    unsigned int iPadding71;
    unsigned int iPadding72;
    unsigned int iPadding73;
} ST_LINE_INFO;

typedef struct
{
    int vPCode2a;   //properties
    int vPParam2a;  //skills
    int vPMin2a;
    int vPMax2a;
} ST_SET_CODE;

static char *m_apcInternalProcess[] =
{
    "index",
    "*eol",
    NULL,
};

static char *m_apcNotUsed[] =
{
    "level",
    NULL,
};

typedef struct
{
    unsigned char vindex[32];
} ST_SET_INDEX;

static unsigned int m_iSetCount = 0;
static ST_SET_INDEX *m_astSets = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astSets, ST_SET_INDEX);

char *Sets_GetSetName(unsigned int id)
{
    if ( id < m_iSetCount )
    {
        return m_astSets[id].vindex;
    }

    return NULL;
}

static int Sets_FieldProc_Pre(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
#ifdef USE_NAME_TOBE_ID
    char *pcResult;
#endif

    if ( !strcmp(acKey, "index") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
#ifdef USE_NAME_TOBE_ID
            pcResult = String_FindString(pstLineInfo->vname, NULL);
            if ( pcResult && strcmp("dummy", pcResult) )
            {
                strcpy(acOutput, pcResult);
            }
            else
#endif
            {
                sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->wSetId);
            }
        }

        strncpy(m_astSets[m_iSetCount].vindex, acOutput, sizeof(m_astSets[m_iSetCount].vindex));
        String_Trim(m_astSets[m_iSetCount].vindex);
        m_iSetCount++;

        return 1;
    }
    else if ( !strcmp(acKey, "*eol") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static int Sets_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
#ifdef USE_NAME_TOBE_ID
    char *pcResult;
#endif

    if ( !strcmp(acKey, "index") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
#ifdef USE_NAME_TOBE_ID
            pcResult = String_FindString(pstLineInfo->vname, NULL);
            if ( pcResult && strcmp("dummy", pcResult) )
            {
                strcpy(acOutput, pcResult);
            }
            else
#endif
            {
                sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->wSetId);
            }
        }

        return 1;
    }
    else if ( !strcmp(acKey, "*eol") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static int Sets_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int id;
    int result = 0;

    if ( !strcmp("name", acKey) )
    {
        pcResult = String_FindString(pstLineInfo->vname, NULL);
        if ( pcResult && strcmp("dummy", pcResult) )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->wSetId);
        }
        result = 1;
    }
    else if ( 'a' == acKey[strlen(acKey) - 1] && 1 == sscanf(acKey, "PCode%da", &id) )
    {
        ST_SET_CODE *pstSetItem = (ST_SET_CODE *)&pstLineInfo->vPCode2a;
        pcResult = Properties_GetProperty(pstSetItem[(id - 2) * 2].vPCode2a);
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
    else if ( 'a' == acKey[strlen(acKey) - 1] && 1 == sscanf(acKey, "PParam%da", &id) )
    {
        ST_SET_CODE *pstSetItem = (ST_SET_CODE *)&pstLineInfo->vPCode2a;
        pcResult = Properties_GetProperty(pstSetItem[(id - 2) * 2].vPCode2a);
        if ( pcResult )
        {
            if ( !strcmp("oskill", pcResult) )
            {
                pcResult = Skills_GetSkillName(pstSetItem[(id - 2) * 2].vPParam2a);
                if ( pcResult )
                {
                    strcpy(acOutput, pcResult);
                }
                else
                {
                    sprintf(acOutput, "%d", pstSetItem[(id - 2) * 2].vPParam2a);
                }
            }
            else if ( !strcmp("state", pcResult) )
            {
                pcResult = States_GetStateName(pstSetItem[(id - 2) * 2].vPParam2a);
                if ( pcResult )
                {
                    strcpy(acOutput, pcResult);
                }
                else
                {
                    sprintf(acOutput, "%d", pstSetItem[(id - 2) * 2].vPParam2a);
                }
            }
            else
            {
                sprintf(acOutput, "%d", pstSetItem[(id - 2) * 2].vPParam2a);
            }
        }
        else
        {
            acOutput[0] = 0;
        }

        result = 1;
    }
    else if ( 'b' == acKey[strlen(acKey) - 1] && 1 == sscanf(acKey, "PCode%db", &id) )
    {
        ST_SET_CODE *pstSetItem = (ST_SET_CODE *)&pstLineInfo->vPCode2b;
        pcResult = Properties_GetProperty(pstSetItem[(id - 2) * 2].vPCode2a);
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
    else if ( 'b' == acKey[strlen(acKey) - 1] && 1 == sscanf(acKey, "PParam%db", &id) )
    {
        ST_SET_CODE *pstSetItem = (ST_SET_CODE *)&pstLineInfo->vPCode2b;
        pcResult = Properties_GetProperty(pstSetItem[(id - 2) * 2].vPCode2a);
        if ( pcResult )
        {
            if ( !strcmp("oskill", pcResult) )
            {
                pcResult = Skills_GetSkillName(pstSetItem[(id - 2) * 2].vPParam2a);
                if ( pcResult )
                {
                    strcpy(acOutput, pcResult);
                }
                else
                {
                    sprintf(acOutput, "%d", pstSetItem[(id - 2) * 2].vPParam2a);
                }
            }
            else if ( !strcmp("state", pcResult) )
            {
                pcResult = States_GetStateName(pstSetItem[(id - 2) * 2].vPParam2a);
                if ( pcResult )
                {
                    strcpy(acOutput, pcResult);
                }
                else
                {
                    sprintf(acOutput, "%d", pstSetItem[(id - 2) * 2].vPParam2a);
                }
            }
            else
            {
                sprintf(acOutput, "%d", pstSetItem[(id - 2) * 2].vPParam2a);
            }
        }
        else
        {
            acOutput[0] = 0;
        }

        result = 1;
    }
    else if ( strlen("FCode1") == strlen(acKey) && 1 == sscanf(acKey, "FCode%d", &id) )
    {
        ST_SET_CODE *pstSetItem = (ST_SET_CODE *)&pstLineInfo->vFCode1;
        pcResult = Properties_GetProperty(pstSetItem[id - 1].vPCode2a);
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
    else if ( strlen("FParam1") == strlen(acKey) && 1 == sscanf(acKey, "FParam%d", &id) )
    {
        ST_SET_CODE *pstSetItem = (ST_SET_CODE *)&pstLineInfo->vFCode1;
        pcResult = Properties_GetProperty(pstSetItem[id - 1].vPCode2a);
        if ( pcResult )
        {
            if ( !strcmp("oskill", pcResult) )
            {
                pcResult = Skills_GetSkillName(pstSetItem[id - 1].vPParam2a);
                if ( pcResult )
                {
                    strcpy(acOutput, pcResult);
                }
                else
                {
                    sprintf(acOutput, "%d", pstSetItem[id - 1].vPParam2a);
                }
            }
            else if ( !strcmp("state", pcResult) )
            {
                pcResult = States_GetStateName(pstSetItem[id - 1].vPParam2a);
                if ( pcResult )
                {
                    strcpy(acOutput, pcResult);
                }
                else
                {
                    sprintf(acOutput, "%d", pstSetItem[id - 1].vPParam2a);
                }
            }
            else
            {
                sprintf(acOutput, "%d", pstSetItem[id - 1].vPParam2a);
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

static void Sets_InitValueMap(ST_VALUE_MAP *pstValueMap, ST_LINE_INFO *pstLineInfo)
{
    INIT_VALUE_BUFFER;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, name, USHORT);   //strings

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, version, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PCode2a, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PParam2a, INT);  //skills
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMin2a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMax2a, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PCode2b, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PParam2b, INT);  //skills
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMin2b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMax2b, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PCode3a, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PParam3a, INT);  //skills
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMin3a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMax3a, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PCode3b, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PParam3b, INT);  //skills
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMin3b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMax3b, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PCode4a, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PParam4a, INT);  //skills
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMin4a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMax4a, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PCode4b, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PParam4b, INT);  //skills
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMin4b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMax4b, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PCode5a, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PParam5a, INT);  //skills
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMin5a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMax5a, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PCode5b, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PParam5b, INT);  //skills
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMin5b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PMax5b, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FCode1, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FParam1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMin1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMax1, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FCode2, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FParam2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMin2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMax2, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FCode3, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FParam3, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMin3, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMax3, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FCode4, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FParam4, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMin4, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMax4, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FCode5, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FParam5, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMin5, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMax5, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FCode6, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FParam6, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMin6, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMax6, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FCode7, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FParam7, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMin7, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMax7, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FCode8, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FParam8, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMin8, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FMax8, INT);
}

int process_sets(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            MODULE_DEPEND_CALL(string, acTemplatePath, acBinPath, acTxtPath);

            Sets_InitValueMap(pstValueMap, pstLineInfo);

            m_iSetCount = 0;

            m_stCallback.pfnFieldProc = Sets_FieldProc_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(string, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(properties, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(skills, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(states, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            Sets_InitValueMap(pstValueMap, pstLineInfo);

            m_stCallback.pfnConvertValue = Sets_ConvertValue;
            m_stCallback.pfnFieldProc = Sets_FieldProc;
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

