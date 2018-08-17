#include "global.h"

#define FILE_PREFIX "monumod"
#define NAME_PREFIX "mu"

/*
Title 	MonUMod.txt File Guide
Description 	by 54x & Red Havoc
Sent by 	

OVERVIEW :

MonUMod.txt controls general and special abilites of :

    Champions
    Random Unique monsters
    SuperUnique monsters

as well as all their respective minions.

 

Warning : this file is tricky, as it contain 1 table of parameters inside. The 2 last columns of datas are in fact to be considered as a complete another file, they have no relations between the columns / lines of the rest of MonUMod.txt.

In case you wonder, this is ugly and not a logical way to proceed, don't do that at home when you're making your own databases; instead make 2 separate tables.

RELATED .TXT FILES :
     	

This file is using:

    MonType.txt

	

This file is used by :

    SuperUniques.txt

COLUMN DESCRIPTIONS :
uniquemod 	This column is just for reference and not used in another file. It holds short keywords that describe the modifier of each line, so you know what youre messing with.

For a precise description see the SuperUniques.txt file guide, columns Mod1, Mod2 and Mod3.
 
id 	This column is used for the internal Id of the modifier.

These Id numbers are entered into the Mod1, Mod2 and Mod3 columns in SuperUniques.txt to give bosses their special skills.
 
enabled 	

Is the modifier usable or not ?

    1 = enabled and can be used
    0 = not enabled and wont work in the game
     

version 	

Modifier for Classic D2 and / or LoD ?

    0 = can be used in both D2 Classic and LoD
    100 = can only be used in the LoD Expansion
     

xfer 	

Display "Minions" under the life bar ?

For instance SuperUniques has up to 3 Mods. If at least 1 of them has the column xfer set to 1, then the Minions of this Boss will have "Minions" displayed under their life bar.
 
champion 	

Champion-only ?

    1 = the modifier is for Champions only
    0 = can be used by SuperUniques, Champions ...
     

fPick 	Maybe means forbidden pick and restricts the spawning of several modifiers on one boss, e.g. "Lightning Enchanted" bosses dont get "Multiple Shots" as well.

How it's working exactly is not known tough.
 
exclude1
exclude2 	

Monster Type exclusion.

These two columns can be used to exclude peculiar monster types from spawning with a certain boss modifier. If the type value from MonTypes.txt is entered here, no randomly spawned boss monster of this category (and its sub-categories) will ever have 
this modifier.

For instance, Sandleapers will never spawn with the Lightning Enchanted property.
 
cpick
cpick (N)
cpick (H) 	Is it available for Champions on this Difficulty ?

These columns restrict the range of modifiers that will spawn on champions in different diffculties. An empty cell in one of the columns means, the modifier will not appear on champions in the corresponding difficulty.

Note, that you may add (boss-only) modifiers to champions if you also set their Champion column to 1 and enter a value in their cpick columns.

By entering higher numbers you can increase the frequency in which the modifier is used : if you set, for example, cpick for the fanatic modifier to 7 and the value for the possessed to 1, fanatic champions will occur like seven times more often in 
normal difficulty than possessed champions.
 
upick
upick (N)
upick (H) 	These columns work exactly like the cpick columns and control which modifiers will spawn on random Uniques bosses in the three difficulties. An higher value means the modifier will spawn more often.
 
fInit 	Not read by the game. You can use it as a comment field.
 

 

 

The next two columns are composing a parameter table. The column *constant desc is a description of the parameter, while the column constants is the value of that parameter.
constants 	

This column includes the values that will set up general properties of champions, bosses and their minions. The values are described in the column to the right, *constant desc.

Some parameters have different values per difficulty, while others are global for the 3 difficulties.

Here's the content of that table, in a more handy form :

Global Parameter
	
      Value
champion chance
	
20
champion +tohit%
	
75
champion +dmg%
	
100
minion +tohit%
	
50
unique +tohit%
	
100
minion +dmg% (strong)
	
75
unique +dmg% (strong)  
	
150

 
Parameter per Difficulty
	
    Normal
	
  Nightmare
	
        Hell
minion +hp%
	
200
	
200
	
175
champion +hp%
	
300
	
250
	
200
unique +hp%
	
700
	
550
	
325
minion +elem min dmg%
	
0
	
33
	
33
minion +elem max dmg%
	
0
	
50
	
50
champion +elem min dmg%  
	
33
	
33
	
33
champion +elem max dmg
	
50
	
50
	
50
unique +elem min dmg%
	
66
	
66
	
66
unique +elem max dmg%
	
100
	
100
	
100


 
*constant desc   	This column tells what the values in the constants column do affect.
 
*eol 	End Of Line.

Do not remove this column ! Its purpose is to ensure the last column of the tabulated text files are always filled. Be sure that all rows of this column are filled with a value.

*/

/*
文件名解析：
Mon：Monster，即怪物。
U：Unique，唯一的，特殊的。
Mod：Modifier，修饰，即特殊属性。
所以本文件就是描述所有可能在金怪（包括头目怪）身上出现的特殊属性，如特别快速等。
此文件中的每一行表示一个特殊属性。


回复

    2楼
    2011-09-22 22:41

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    3楼
    2011-09-22 22:41

    举报 |

    jayhorusosiris
    天堂信徒
    11

好贴留名混脸熟求姐姐


回复

    4楼
    2011-09-22 22:41

    举报 |

    zqtjingzi
    小吧主
    12

UniqueMod：金怪特殊属性（以后简称UMod）的名字，仅仅作为注释使用。

ID：此UMod的编号，供其它文件使用。

Enabled：此UMod是否可用。

Version：此UMod适用的最低版本。

xfer：有此UMod的金怪身边的小怪名字下是否显示“喽啰”字眼。

Champion：此UMod是否为头目怪独有。

fPick：此列有值的UMod不能为同一金怪共有。

exclude1：此UMod不能出现的怪物类型1。

exclude2：此UMod不能出现的怪物类型2。

cpick：在普通难度下的头目怪能否有此UMod。

cpick(N)：在恶梦难度下的头目怪能否有此UMod。

cpick(H)：在地狱难度下的头目怪能否有此UMod。

upick：在普通难度下的随机金怪能否有此UMod，且数值越大此UMod出现的频率越大。

upick(N)：在恶梦难度下的随机金怪能否有此UMod，且数值越大此UMod出现的频率越大。

upick(H)：在地狱难度下的随机金怪能否有此UMod，且数值越大此UMod出现的频率越大。

fInit：无用列，删除也可。

constants：金怪及其喽啰的能力提升值。提升的能力与其所在哪个UMod行无关，而要看后面紧跟的*constant desc列。

*constant desc：金怪及其喽啰可能提升的能力。与其所在哪个UMod行无关。

*eol：行尾标志，必须为0。


回复

    5楼
    2011-09-22 22:41

    举报 |

    zqtjingzi
    小吧主
    12

完毕。
如果有错误请指出。
祝各位游戏愉快。

补充说明：
constants表格整理，即金怪、头目怪及其喽啰的能力提升值（1.13版本）

头目怪出现的概率：20%，即头目怪与金怪的比例约为1：4

普通——喽啰： 生命 +100% 攻击准确率 + 50% 伤害 + 75% 元素伤害 + 0% - 0%
恶梦——喽啰： 生命 + 75% 攻击准确率 + 50% 伤害 + 75% 元素伤害 + 33% - 50%
地狱——喽啰： 生命 + 50% 攻击准确率 + 50% 伤害 + 75% 元素伤害 + 33% - 50%
普通——头目： 生命 +200% 攻击准确率 + 75% 伤害 +100% 元素伤害 + 33% - 50%
恶梦——头目： 生命 +150% 攻击准确率 + 75% 伤害 +100% 元素伤害 + 33% - 50%
地狱——头目： 生命 +100% 攻击准确率 + 75% 伤害 +100% 元素伤害 + 33% - 50%
普通——金怪： 生命 +300% 攻击准确率 +100% 伤害 +150% 元素伤害 + 66% -100%
恶梦——金怪： 生命 +200% 攻击准确率 +100% 伤害 +150% 元素伤害 + 66% -100%
地狱——金怪： 生命 +100% 攻击准确率 +100% 伤害 +150% 元素伤害 + 66% -100% 
*/

typedef struct
{
    unsigned int vid;

    unsigned short vversion;
    unsigned char venabled;
    unsigned char vxfer;

    unsigned char vchampion;
    unsigned char vfPick;
    unsigned short vexclude1;   //MonType

    unsigned short vexclude2;   //MonType
    unsigned short vcpick;

    unsigned short vcpickmyspmybr1Nmybr2;
    unsigned short vcpickmyspmybr1Hmybr2;

    unsigned short vupick;
    unsigned short vupickmyspmybr1Nmybr2;

    unsigned short vupickmyspmybr1Hmybr2;
    unsigned short iPadding6;

    unsigned int vconstants;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "uniquemod",
    "*eol",
    NULL,
};

static char *m_apcNotUsed[] =
{
    "fInit",
    "*constant desc",
    NULL,
};

static int MonUMOD_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "uniquemod") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else if ( 0 < iLineNo )
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->vid);
        }
        else
        {
            acOutput[0] = 0;
        }
#else
        sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->vid);
#endif

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

static int MonUMod_ConverValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "exclude1") )
    {
        pcResult = MonType_GetType(pstLineInfo->vexclude1);
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
    else if ( !strcmp(acKey, "exclude2") )
    {
        pcResult = MonType_GetType(pstLineInfo->vexclude2);
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

int process_monumod(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, id, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, version, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, enabled, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, xfer, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, champion, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, fPick, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, exclude1, USHORT);   //MonType

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, exclude2, USHORT);   //MonType
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cpick, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cpickmyspmybr1Nmybr2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cpickmyspmybr1Hmybr2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, upick, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, upickmyspmybr1Nmybr2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, upickmyspmybr1Hmybr2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, constants, UINT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(montype, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = MonUMod_ConverValue;
            m_stCallback.pfnFieldProc = MonUMOD_FieldProc;
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

