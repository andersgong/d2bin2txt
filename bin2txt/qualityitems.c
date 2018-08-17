#include "global.h"

#define FILE_PREFIX "qualityitems"

/*
Qualityitems.txt - v1.10 (and presumably 1.11x)
Composed by Quatl with help from Nefarius, and Myhrginoc

OVERVIEW

Controls properties for superior quality items.
Each row holds settings for both armor and weapons.
I assume the probibility of each row is the same.
New rows may be added, and are functional. I have no clue as to limits.

RELATED .TXT FILES
This file is useing
* Properties.txt
* Itemtypes.txt (only indirectly see below)


COLUMN DESCRIPTIONS :
______________________________________________________________________________

nummods: 1 or 2
How many mods appear on items the game makes superior useing this row

______________________________________________________________________________

mod1code: String Code from properties.txt
%ac, or red-mag, for example. 1st property for items of this quality, seems to allow any property
mod1param, mod1min, mod1max: Numeric Value
Same as any other property setting field. See properties.txt for details.

______________________________________________________________________________

mod2code: String Code from properties.txt
2nd property for armors of this quality (when nummods = 2)
mod2param, mod2min, mod2max: Numeric Value
Same as any other property setting field. See properties.txt for details.

______________________________________________________________________________

ToHitMin -> Dur%Max: Numeric Value
Out dated. You can safely use these for your own comments or whatever.
Not loaded by the game
(Thanks Myhrginoc)

______________________________________________________________________________

effect1, effect2: String_Key
String Key from a tbl file. I'm not sure if this has to be a valid key.
Loaded, but not displayed by the game.
(Thanks Myhrginoc)

______________________________________________________________________________

armor -> belt: Boolean Value
Filter items allowing this row's mods
1 = allow, 0 = dissalow
Note: These types are the original hardcoded item types
(Thanks Nefarius.) Helm for instance is not an option. I asume that
itemtypes.txt types that inherit from one of these types will cascade
properly.
Item type Cascades:
(From Nefarius; not fully confirmed)
armor -> tors, helm
weapon -> mele (except thro, rod, orb)
shield -> shld
throw -> thro
scepter -> scep
wand -> wand
staff -> staf
bow -> miss (xbow/bow)
boots -> boot
gloves -> glov
belt -> belt
(type comb ? could be either throw or weapon or both, not checked)

______________________________________________________________________________

level: Numeric Value
Level requirement push

______________________________________________________________________________

multiply: Numeric Value
Item's cost multiplied by this value.

______________________________________________________________________________

add: Numeric Value
Item's cost increased by this value.

______________________________________________________________________________

I realize this is a simple file , but I think it has potential for some interesting things, and I couldn't find much on it. Hopefuly someone will find it handy. Note this file is not included in the standard txt extract package, so you'll have to milk 
it from d2exp by hand.

-Quatl

*/

/*
文件名解析：
Quality：高品质的，即超强的。
Items：道具，即装备。
本文件描述了所有超强类型的装备的信息。
此文件中的每一行表示一种超强类型。


回复

    2楼
    2011-09-26 23:59

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    3楼
    2011-09-26 23:59

    举报 |

    zqtjingzi
    小吧主
    12

nummods：此超强类型有几个附加属性。只能为1或者2。

mod1code：第1个附加属性的属性名，与Properties.txt关联。

mod1param：第1个附加属性的参数。

mod1min：第1个附加属性的最小值参数。

mod1max：第1个附加属性的最大值参数。

mod2code、mod2param、mod2min、mod2max含义参考mod1。

ToHitMin：仅用作注释。

ToHitMax：仅用作注释。

Dam%Min：仅用作注释。

Dam%Max：仅用作注释。

AC%Min：仅用作注释。

AC%Max：仅用作注释。

Dur%Min：仅用作注释。

Dur%Max：仅用作注释。

effect1：无用参数，但被游戏读入。

effect2：无用参数，但被游戏读入。

armor：此超强类型能否出现在防具上。

weapon：此超强类型能否出现在武器上。

shield：此超强类型能否出现在盾牌上。

thrown：此超强类型能否出现在投掷武器上。

scepter：此超强类型能否出现在权杖（pal杖）上。

wand：此超强类型能否出现在法杖（nec杖）上。

staff：此超强类型能否出现在手杖（sor杖）上。

bow：此超强类型能否出现在弓上。

boots：此超强类型能否出现在鞋上。

gloves：此超强类型能否出现在手套上。

belt：此超强类型能否出现在腰带上。

level：此超强类型对物品等级的要求。

multiply：价格放大因子。

add：价格增加因子。
*/

typedef struct
{
    unsigned char varmor;
    unsigned char vweapon;
    unsigned char vshield;
    unsigned char vscepter;

    unsigned char vwand;
    unsigned char vstaff;
    unsigned char vbow;
    unsigned char vboots;

    unsigned char vgloves;
    unsigned char vbelt;
    unsigned char vnummods;
    unsigned char iPadding2;

    unsigned int vmod1code; //properties
    unsigned int vmod1param;
    unsigned int vmod1min;
    unsigned int vmod1max;

    unsigned int vmod2code; //properties
    unsigned int vmod2param;
    unsigned int vmod2min;
    unsigned int vmod2max;

    unsigned char veffect1[32];
    unsigned char veffect2[32];

    unsigned int iPadding27;
} ST_LINE_INFO;

static char *m_apcNotUsed[] =
{
    "ToHitMin",
    "ToHitMax",
    "Dam%Min",
    "Dam%Max",
    "AC%Min",
    "AC%Max",
    "Dur%Min",
    "Dur%Max",
    "thrown",
    "level",
    "multiply",
    "add",
    NULL,
};

static int QualityItems_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "mod1code") )
    {
        pcResult = Properties_GetProperty(pstLineInfo->vmod1code);
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
    else if ( !strcmp(acKey, "mod2code") )
    {
        pcResult = Properties_GetProperty(pstLineInfo->vmod2code);
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

int process_qualityitems(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, armor, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, weapon, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, shield, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, scepter, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, wand, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, staff, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, bow, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, boots, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gloves, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, belt, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, nummods, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod1code, UINT); //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod1param, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod1min, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod1max, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod2code, UINT); //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod2param, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod2min, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod2max, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, effect1, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, effect2, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(properties, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = QualityItems_ConvertValue;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

