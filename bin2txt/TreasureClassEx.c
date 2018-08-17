#include "global.h"

#define FILE_PREFIX "TreasureClassEx"

/*
Title 	TreasureClassEx.txt File Guide (totally new)
Description 	by Nefarius
Sent by 	
TreasureClassEx.txt File Guide
By Nefarius







Treasure Class – This column defines the ID pointer (“the name”) of the treasureclass, this pointer is used by other files (and fields inside this file) to link to a specific line. An ID pointer must be unique, if you have two identical ID pointers 
the game will always use the first occurrence and ignore all others. Fields of this type are (almost always) case-sensitive. Files that use this ID pointer: MonStats.txt, SuperUniques.txt and TreasureClassEx.txt



Group and Level – These two columns go hand in hand, the first is used to group several treasureclasses together to form a “super-treasureclass”, the second one then gives each of these lines a level. The game will then use this to automatically 
attempt to balance the item drops according to the level you have put inside the second column. For example, if you give a level 10 monster a treasureclass, it will pick the treasureclass with the nearest level, so if you have one with 10 and another 
with 20, it will pick the first over the second, even if you linked the monster to the second treasureclass.



Picks – This column has two different functions, depending on the type of values you enter (either positive 0-6 or negative, -1 to -6). In the first case this is used as the number of loops to run the “pick drop” routine, in the second case it is 
used to determine exactly which items, and how many of each, to drop (see appendix). You cannot make the game drop more then 6 items with either method without code editing (there are other txt based methods to drop more then 6 items though).



Unique, Set, Rare, Magic – This is used to manipulate and fine-tune the drop ratio of items of the respective quality. Listing the whole “quality” calculation here is not necessary as this has been covered in many places, just know that the way this 
column works is:

if treasureclass-manipulator < 1024, then multiply chance by the term (1 – treasureclass-manipulator / 1024)

Thus a value of 1024 or larger will cause the game to always drop items of this quality, as the game will skip the multiplication and count the check an automatic success. (This does not mean a unique or set item is always generated, as there are other 
rules for those grades. But if those rules prevent either quality, the fallback to increased-durability rares or magical items will happen.)

Examples (chance is some number calculated from ItemRatio.txt and magic find rules):

(chance) * (1 – 768 / 1024) = 25% * (chance) = 4x better odds for successful check
(chance) * (1 – 512 / 1024) = 50% * (chance) = 2x better odds for successful check
(chance) * (1 – 256 / 1024) = 75% * (chance) = 1.33x better odds for successful check

I believe it should be clear now how this works.



NoDrop – Probability for “nothing”, I.E. just like all other items droppable by a treasureclass, this simply defines the probability of “nothing” to drop.



Item1-10 – The different items and treasureclasses linked to this line (“what it can drop”), this can either contain item codes, item pointers (=the “names” of unique items and set items), auto-treasureclasses (see ItemTypes.txt or appendix) and 
other treasureclasses. There are several special modifiers for this field that are supposedly enabled in 1.10, I have not used any of those myself so I don’t know if they work. For gold drops, you can use the mul flag to increase the number of coins in 
a gold pile (this is why bosses and champions always drop more gold then regular monsters).



Prob1-10 – This is the individual probability for each of the drops defined in the Item1-10 columns. (see appendix)



SumItems, TotalProb and DropChance – These columns have no purpose other then being used as comment fields (that’s what blizzard has used them for if you wonder what those values in some of them mean).



Term – This column is required to terminate the line if you’re using M$ Excel or another spreadsheet that likes messing up the table borders.






Appendix

Never replace or move the gold row around, the game needs this row to define gold drops (such as when you drop gold from your inventory AFAIK).

The chest rows are also accessed by code, albeit I am uncertain via what method, because it is definetly NOT via an ID, because one can move them around w/o any bad effects.


The auto-treasureclasses are used to group all items of a specific item type in a range of automatically generated TCs, such as armo3-99 and weap3-99. These TCs are softcoded in 1.10 and are now controlled by the TreasureClass column in ItemTypes.txt (
thanks to Paul Siramy for pointing me in the right direction).

The chance to drop is generated based on the values in the prob1-10 columns (this includes NoDrop). Lets say you have NoDrop set to 100, and the probability for items 1-3 set to 25,50 and 100 respectively.

Sum = 100+100+50+25 = 275

Chance of no drops: 36.5% (100/275)
Chance of item 1: 9% (25/275)
Chance of item 2: 18% (50/275)
Chance of item 3: 36.5% (100/275)

If the picks column contains negative values then the Prob1-10 columns are used as quantity indicators instead.

For example:

Picks = -6

Item1 = 2
Item2 = 1
Item3 = 3

This will make the game drop 2,1 and 3 of these items respectively.

*/

/*
文件名解析：
Treasure：宝藏。
Class：类别。
Ex：Expansion，扩展的，指资料片。
本文件描述了资料片中所有可能出现的宝藏类别(TC)。
此文件中的每一行表示一个TC。


回复

    2楼
    2011-09-25 21:11

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    3楼
    2011-09-25 21:11

    举报 |

    zqtjingzi
    小吧主
    12

Treasure Class：TC名。供其它txt文件使用。

group：此TC所属的TC组。TC升高时使用。

level：此TC的类别。TC升高时使用。

Picks：宝藏挑选次数。正数为有放回的挑选，负数为不放回的挑选。

Unique：出现暗金装备的概率修正数。

Set：出现套装装备的概率修正数。

Rare：出现亮金装备的概率修正数。

Magic：出现蓝色装备的概率修正数。

NoDrop：每次挑选时不掉落任何物品的频率。

Item1-10：可能出现的物品类型1-10。

Prob1-10：每次挑选时掉落1-10类物品的频率。

SumItems：无用参数。

TotalProb：无用参数。

DropChance：无用参数。

Term：行尾标志，必须为0。
*/

typedef struct
{
    char vTreasuremyspClass[32];

    int vPicks;

    short vgroup;
    short vlevel;

    short vMagic;
    short vRare;

    short vSet;
    short vUnique;

    int iPadding12;

    int vNoDrop;

    char vItem1[64];

    char vItem2[64];

    char vItem3[64];

    char vItem4[64];

    char vItem5[64];

    char vItem6[64];

    char vItem7[64];

    char vItem8[64];

    char vItem9[64];

    char vItem10[64];

    int vProb1;

    int vProb2;

    int vProb3;

    int vProb4;

    int vProb5;

    int vProb6;

    int vProb7;

    int vProb8;

    int vProb9;

    int vProb10;
} ST_LINE_INFO; //total 736 bytes

typedef struct
{
    unsigned char vTreasuremyspClass[36];
} ST_TREASURECLASSEX;

static char *m_apcInternalProcess[] =
{
    "Term",
    NULL,
};

static char *m_apcNotUsed[] =
{
    "SumItems",
    "TotalProb",
    "DropChance",
    NULL,
};

static unsigned int m_uiTcOffset = 0;
static unsigned int m_iTreasureClassEx = 0;
static ST_TREASURECLASSEX *m_astTreasureClassEx = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astTreasureClassEx, ST_TREASURECLASSEX);

void TreasureClassEx_SetOffset(unsigned int uiOffset)
{
    m_uiTcOffset = uiOffset;
    my_printf("set tc to %d\r\n", uiOffset);
}

char *TreasureClassEx_GetItemTreasureClass(unsigned int id)
{
    //id -= 161;    //原版
    //id -= 321;  //魔电
    //id -= 193;  //宝日8.4
    id -= m_uiTcOffset;

    if ( id < m_iTreasureClassEx && strcmp("Gold", m_astTreasureClassEx[id].vTreasuremyspClass) )
    {
        return m_astTreasureClassEx[id].vTreasuremyspClass;
    }

    return NULL;
}

static char *TreasureClassEx_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strcpy(pcKey, pstLineInfo->vTreasuremyspClass);
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

static int TreasureClassEx_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "Term") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        strncpy(m_astTreasureClassEx[m_iTreasureClassEx].vTreasuremyspClass, pstLineInfo->vTreasuremyspClass, sizeof(m_astTreasureClassEx[m_iTreasureClassEx].vTreasuremyspClass));
        String_Trim(m_astTreasureClassEx[m_iTreasureClassEx].vTreasuremyspClass);
        m_iTreasureClassEx++;
        return 1;
    }

    return 0;
}

int process_treasureclassex(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TreasuremyspClass, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Picks, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, group, SHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, level, SHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Magic, SHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Rare, SHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Set, SHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Unique, SHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, NoDrop, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Item1, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Item2, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Item3, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Item4, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Item5, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Item6, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Item7, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Item8, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Item9, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Item10, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob1, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob2, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob3, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob4, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob5, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob6, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob7, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob8, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob9, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob10, INT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            File_CopyFile(acTemplatePath, acTxtPath, "treasureclass", ".txt");

            m_iTreasureClassEx = 0;

            //m_stCallback.pfnGetKey = TreasureClassEx_GetKey;
            m_stCallback.pfnFieldProc = TreasureClassEx_FieldProc;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            break;

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

