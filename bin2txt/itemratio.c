#include "global.h"

#define FILE_PREFIX "itemratio"
#define NAME_PREFIX "ir"

/*
Title 	ItemRatio.txt File Guide
Description 	by Ulmo
Sent by 	

OVERVIEW :

ItemRatio.txt is used to determine the quality of dropped items. The game decides the quality of item (unique/.../lowquality) by first testing if it is unique, if not it tests if it is rare, if not ..., and if all fail the item of "low quality". 
ItemRatio.txt controls the probabilities of success of successive tests.
The order is :
Unique > Set > Rare > Magic > Hi quality > Normal > Low quality

RELATED .TXT FILES :

As far as I know, this file is not using/used by other .txt files. But the game has to know is the current item is uber/elite, and if it is class-specific, which involve Armor.txt/Misc.txt/Weapons.txt and ItemTypes.txt. The game also checks item’s qLvl 
(“level” column in Armor.txt/Misc.txt/Weapons.txt) and monsters’ levels (this use MonStats.txt and Levels.txt but exact behaviour is out of the scope of this file guide).

COLUMN DESCRIPTIONS :

Function
	

Human reference only. The game reads the next 3 entries to choose the proper line.

 

D2C class specific items don't appear in vanilla. The line used if you make such items is LoD/class specific (I have tested).

Version
	

Current game : 0 for D2C, 1 for LoD

Uber
	

0 for normal items, 1 for exceptional/elite

Class Specific
	

1 if item has type (or equiv) "Class Specific". Or nonempty column "class" in ItemTypes.txt. I don't know what is exactly checked.

0 else.

D2C class specific items don't appear in vanilla. The line used if you make such items is LoD/class specific (I have tested).

Unique
	

Base chance of being unique. The higher, the rarer. (“chance” must be understood as “one over chance …”)

UniqueDivisor
	

Influence of monster level / item quality level. High value counter the bonus of high level monsters giving better items (see Mishy23’s note below).

UniqueMin
	

Limitation of the influence of monster/quality levels and of MF bonus. Again the higher, the rarer.

Rare

RareDivisor

RareMin
	

Same for rare items.

Set

SetDivisor

SetMin
	

Guess J

HiQuality

HiQualityDivisor
	

idem, but no limitation (and no MF any more).

Normal

NormalDivisor
	

Idem.

Let's see how the game use this : when a drop occurs, the game follows the TC until getting a base object. For exemple a "skull cap". Then it test if the item become unique/set/rare/.../Low quality.
For this it uses the proper line of ItemRatio.txt, the MF bonus of the character who made the drop (character + minion if a minion killed the monster), and the maximum values of unique/set/magic/rare crossed while following TreasureClassEx.txt (the 
maximum value, not the first seen, not the last non null, not the sum, ... Heavily tested by Paul).

The game decides the quality of item (unique/.../lowquality) by first testing if it is unique, if not it tests if it is rare, if not ..., and if all fail the item of "low quality".
The order is :
Unique > Set > Rare > Magic > Hi quality > Normal > Low quality

the unique test :
The base probability of being unique is probability = 1 / Unique, Unique taken from ItemRatio.
Then this base chance is decreased by (MonsterLvl - QualityLvl) / UniqueDivisor , where QualityLvl is the level read in armor/misc/weapons.
Now this value is multiplied by 128 (some extra precision).
And comes the effect of EMF (MF with diminushing return) : chance = chance * 100 / (100 + EMF) .
Chance is compared with UniqueMin from ItemRatio.txt (so note that XXXmin is in essence 128 time bigger than XXX).
And finally the TC bonus is applied : chance = chance - (chance * unique_factor) / 1024 , where unique_factor is the maximum value of "unique" seems in TreasureClassEx.txt.
Now the games picks a random number between 0 and chance-1. If this random number is less or equal than 127, the objet is unique.

Same procedure is used (but with different diminushing return) for set/rare/magic tests.
And also for Hi quality/normal, but without MF, without XXXmin, and without XXX_factor.

 

A notes on XXXDivisor :
Well mishy23 explained it very well so I'll just be lazy and quote him :

 

Just to expand on RareDiv,
When it comes to determining what rarity(magic/rare/unique) item is,
the difference in itemlevel (qlvl) and monsterlevel (mlvl) make a large difference in overall determination.
Thats why its easier to get magic items and higher on lower level items, then it is on higher level objects.
This is why you usually see white items first when new itemtypes become available, and magic versions dont drop with much regularity until after your fighting higher level monsters.

As Ulmo said (MonsterLvl - Qlvl) / UniqueDivisor is the formula,
so the if a very high level monster drops a very low level base item,
well this raisies chance item can be magic, rare, etc...
while if a medium level monster drops a medium level base item, well that difference is very small and the chance to get magic, rare, etc...is not modified very much at all.

RareDiv, makes this level difference between monster and item its dropping matter less the higher the div is.

Div does not in itself divide the overall chance for dropping magic, rare, unique, just the modification of this chance by the monsterlvl-itemlvl curve.

 

 

Also, you can think of XXXmin as a way to counter too high values of MF.

 

Effective MF formulae :
For magic, it is just EMF = MF
For Rare/Set/Unique, Diminushing return is only used if MF > 10. In this case, EMF = MF*X/(MF+X) , i.e. going slower and slower from 0 to X. With X = 250 for uniques, X = 500 for Sets, and X = 600 for Rares.

Exemple :
A ring (qlvl = 1) dropped by Andarielle in hell (Mlvl = 78) with +300% MF (I use here the QuestDrop).

 

So base chance is 400, then becomes 400 - (78 - 1)/1 = 323
extra-precision : chance = 323*128 = 41344
MF : chance = 41344 * 100 / (100 + 136) = 17518
UniqueMin is lower than chance and is ignored.
for Andarielle questdrop in hell (TC = "Andarielq (H)", Unique_factor = 995
So chance = 17518 - (17518 * 995) / 1024 = 496
This means 128/496 = 25.81% chances of being unique.

Acknowledgements :
First Myrdinn who teached me almost everything I know, but also Paul Simary for long discussions and many testing, and Joel for his both knowledge and disponibility.

*/

/*
文件名解析：
Item：道具，即装备。
Ratio：比值，在这里指判定几率。
本文件描述了各种成色的装备判定的概率。
此文件中的每一行表示一种适用于不同情况的计算方法。


回复

    2楼
    2011-09-29 23:19

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    3楼
    2011-09-29 23:19

    举报 |

    zqtjingzi
    小吧主
    12

Function：仅作注释用。

Version：适用版本。0表示非资料片，1代表资料片。

Uber：此行是否用于特殊装备。如果此行用于杰出装备，则为1

Class Specific：此行是否作用于角色专用物品。如果此行用于专用物品等于1

Unique：暗金物品的基础判定几率。

UniqueDivisor：怪物等级对暗金物品判定几率的影响。
掉落暗金物品的可能性是 1 / (U - (drop level - item level)/UD)
由Treasure Class（TC）和magic find（MF）修正

UniqueMin：暗金物品的最小判定几率。
此列无用但是一直读入，如果你要dll编辑物品掉落代码，可以将他们用作自定义字段

Rare、RareDivisor、：亮金物品的相关属性。
亮金的可能性是 1 / (R - (drop level - item level)/RD)
由Treasure Class（TC）和magic find（MF）修正

RareMin
此列无用但是一直读入，如果你要dll编辑物品掉落代码，可以将他们用作自定义字段

Set、SetDivisor、：绿色物品的相关属性。
出现套装的可能性是 1 / (S - (drop level - item level)/SD)
由Treasure Class（TC）和magic find（MF）修正

SetMin
此列无用但是一直读入，如果你要dll编辑物品掉落代码，可以将他们用作自定义字段

Magic、MagicDivisor、：蓝色物品的相关属性。
魔法物品掉落的机率是 1 / (M - (drop level - item level)/MD)
由Treasure Class（TC）和magic find（MF）修正

MagicMin
此列无用但是一直读入，如果你要dll编辑物品掉落代码，可以将他们用作自定义字段

HiQuality、HiQualityDivisor：超强物品的相关属性。
高亮物品掉落的机率是 1 / (H - (drop level - itemlevel)/HD) 
由Treasure Class（TC）和magic find（MF）修正

Normal、NormalDivisor：普通物品的相关属性。
白色正常物品出现的可能性是 1 / (N - (drop level - item level)/ND)
由Treasure Class（TC）和magic find（MF）修正


回复

    4楼
    2011-09-29 23:19

    举报 |

    zqtjingzi
    小吧主
    12

补充说明：
各种几率值如何使用还请参数精品区轻寒的物品掉落原理一贴。
http://tieba.baidu.com/p/1010218627
*/

typedef struct
{
    unsigned int vUnique;
    unsigned int vUniqueDivisor;
    unsigned int vUniqueMin;
    unsigned int vRare;
    unsigned int vRareDivisor;
    unsigned int vRareMin;
    unsigned int vSet;
    unsigned int vSetDivisor;
    unsigned int vSetMin;
    unsigned int vMagic;

    unsigned int vMagicDivisor;
    unsigned int vMagicMin;
    unsigned int vHiQuality;
    unsigned int vHiQualityDivisor;
    unsigned int vNormal;
    unsigned int vNormalDivisor;

    unsigned short vVersion;
    unsigned char vUber;
    unsigned char vClassmyspSpecific;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "Function",
    NULL,
};

static int ItemRatio_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "Function") )
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

    return 0;
}

int process_itemratio(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Unique, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, UniqueDivisor, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, UniqueMin, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Rare, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, RareDivisor, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, RareMin, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Set, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SetDivisor, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SetMin, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Magic, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MagicDivisor, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MagicMin, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HiQuality, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HiQualityDivisor, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Normal, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, NormalDivisor, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Version, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Uber, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ClassmyspSpecific, UCHAR);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnFieldProc = ItemRatio_FieldProc;
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

