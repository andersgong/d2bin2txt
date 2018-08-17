#include "global.h"

#define FILE_PREFIX "monequip"

/*
Title 	MonEquip.txt File Guide (v 1.0)
Description 	by Nefarius
Sent by 	
MonEquip.txt File Guide
By Nefarius


Note: Before you can do anything in here, you must set the "inventory" column in MonStats.txt to true (1).
this tells the game to look for equipment data inside MonEquip.txt
NOTE: Never set that column to true if you don't have the appropriate entries in MonEquip.txt, you will get an unhandled exception.
Furthermore, you should leave the last line intact, if you add new lines add them infront of the last line.



monster - This column contains the ID pointer to MonStats.txt, make sure this is accurate (otherwise you will crash for the same reasons as above).

oninit - Boolean, 0 = monster is created by skill, 1 = monster is created by level.

item1-3 - The 3-4 letter code of the item from weapons, armor or misc.txt

loc1-3 - The slot to equip the item in. (see BodyLocs.txt for more details)

mod1-3 - Item quality of the equipped item. (see table below)

eol - End of Line.




Item Quality:

1 - low quality
2 - normal
3 - superior
4 - magic
5 - set
6 - rare
7 - unique
8 - crafted
9 - tempered

*/

/*
文件名解析：
Mon：Monster，即怪物。
Equip：装备。
所以本文件描述了某些怪物的装备，其实就是血鸟、飞行的弯刀、女武神、影子战士和影子大师的装备。
此文件中的每一行表示一个特定等级的怪物。


回复

    2楼
    2011-09-23 22:34

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    3楼
    2011-09-23 22:34

    举报 |

    zqtjingzi
    小吧主
    12

monster：怪物名，与Monstats.txt关联。

oninit：此怪物是否在地图初始化时就生成，即此怪物是否是由技能召唤出来的。0代表是由技能召唤出来的。

level：怪物的等级。当怪物的等级大于某行此列的值时，就能获得此行的装备，且此列值越大的优先级越高。

item1-3：怪物身上增加的第1-3件装备。

loc1-3：第1-3件装备的位置。与BodyLocs.txt关联。

mod1-3：第1-3件装备的品质。品质说明见后面。

eol：行尾标志，必须为0。


回复

    4楼
    2011-09-23 22:34

    举报 |

    zqtjingzi
    小吧主
    12

补充说明：
mod列的值与装备的品质关系：
mod = 1 —— 低品质，即破碎的、损坏的之类。
mod = 2 —— 普通的，即白色装备。
mod = 3 —— 超强的。
mod = 4 —— 魔法的，即蓝色装备。
mod = 5 —— 套装。
mod = 6 —— 稀有的，即黄色装备。
mod = 7 —— 唯一的，即暗金装备。
mod = 8 —— 手工的，即橙色装备。（实际游戏中应该无法出现橙色装备）


回复

    5楼
    2011-09-23 22:34

    举报 |

    zqtjingzi
    小吧主
    12

特殊说明1：
在此文件中出现的怪物，在Monstats.txt中相应行的inventory列一定要为1。而且在Monstats.txt中inventory列为1的怪物一定要在此文件中有至少一行描述。否则游戏会出错。


回复

    6楼
    2011-09-23 22:34

    举报 |

    zqtjingzi
    小吧主
    12

特殊说明2：
此文件中的最后一行一定要保留。如果你想为自行怪物添加装备而增加新的行的话，一定要在最后一行之前添加。

*/

typedef struct
{
    unsigned short vmonster;   //MonStats
    unsigned short vlevel;

    unsigned int voninit;

    unsigned char vitem1[4];
    unsigned char vitem2[4];
    unsigned char vitem3[4];

    unsigned char vloc1; //bodylocs
    unsigned char vloc2; //bodylocs
    unsigned char vloc3; //bodylocs
    unsigned char vmod1;

    unsigned char vmod2;
    unsigned char vmod3;
    unsigned short iPadding6;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] = 
{
    "eol",
    NULL,
};

static int MonEquip_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "eol") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static int MonEquip_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "monster") )
    {
        if ( 0xFFFF == pstLineInfo->vmonster )
        {
            strcpy(acOutput, "*end*  do not remove");
        }
        else
        {
            pcResult = MonStats_GetStatsName(pstLineInfo->vmonster);
            if ( pcResult )
            {
                strcpy(acOutput, pcResult);
            }
            else
            {
                acOutput[0] = 0;
            }
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "loc1") )
    {
        pcResult = BodyLocs_GetLocStr(pstLineInfo->vloc1);
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
    else if ( !strcmp(acKey, "loc2") )
    {
        pcResult = BodyLocs_GetLocStr(pstLineInfo->vloc2);
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
    else if ( !strcmp(acKey, "loc3") )
    {
        pcResult = BodyLocs_GetLocStr(pstLineInfo->vloc3);
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

int process_monequip(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, monster, USHORT);   //MonStats
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, level, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, oninit, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item1, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item2, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item3, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, loc1, UCHAR); //bodylocs
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, loc2, UCHAR); //bodylocs
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, loc3, UCHAR); //bodylocs
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod1, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod3, UCHAR);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(bodylocs, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(monstats, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = MonEquip_ConvertValue;
            m_stCallback.pfnFieldProc = MonEquip_FieldProc;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

