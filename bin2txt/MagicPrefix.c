#include "global.h"

#define FILE_PREFIX "MagicPrefix"

/*
Name - This field controls what string will be displayed in-game for this affix (in the case of AutoMagic.txt this field is unused).

Version - This field controls whenever or not this affix can appear in classic games.


    0 - pre v08 affixes (needed so characters from those versions can be imported to current ones).

    1 - post v08 affixes (affixes available in classic and LoD).

    100 - LoD-only affixes (affixes available only in LoD).



Spawnable - A boolean that controls whenever or not this affix can be picked by the randomizer that assigns affixes to magic and rare items. 0 = cannot be picked, 1 = can be picked. Untested: You should be able to use unspawnable affixes via cube 
recipes however, similar to the way the game handles unspawnable items.

Rare - A boolean that controls whenever or not this affix can be picked by the randomizer when assigning affixes to a rare item. 0 = cannot appear on rare items (magic only), 1 = can appear on rare and magic items.

Level - The quality level (qLvl) of this affix, for this affix to be available on an item, that item must have an item level (iLvl) of at least this amount. The iLvl is equal to the level of the monster that drops the item, or the generation level (for 
vendors). The iLvl of an item is further influenced by the magic lvl field in WEAPONS.txt and ARMOR.txt (and MISC.txt).

MaxLevel - An extremely powerful but badly underused field. This controls the point at which this affix will no longer appear on items. Say we have a Level of 10 and a MaxLevel of 15, then the affix will only appear on items with a iLvl of 10-15, 
whereas it will never appear on items with iLvls 1-9 and 16-99. This is the easiest way to get those crappy low-level affixes of higher level drops to ensure that those are useful.

LevelReq - The general level requirement that your character must meet before he can use an item that has this affix.

ClassSpecific - This does not work the way RicFaith suggested in his 1.09 guides. As you can see, it appears on +skilltab items, and we all know that you can find skiller grand charms for every class irregardless of what class you are. I assume that 
this is a bug fix to the problem that appeared during the early expansion beta, there +skilltab items effected all classes that used the item and not only the class that they were supposed to effect.

Class - This field controls the character class for whom the class specific level requirement appears.

ClassLevelReq - The level requirement your character must meet before he can use an item with this affix if his class is the class specified in the Class column. So lets say Class is Ama and normal LevelReq is 20 while ClassLevelReq is 25. Then an 
Amazon will be able to use this item at cLvl 20 while all other classes would need to be cLvl 25.

Frequency - This works the same way rarity works in all other files. It controls the probability of this affix being picked by the randomizer within this affix group. In classic days, the game simply rolled a random on all available affixes, ever since 
v08 they are using this field (badly), which leads to the crappy rare items we see today. Lets say we have 5 affixes inside a group with Frequencies of 1, 5, 10, 50 and 100, then the chance for each of these to appear in case the game selects an affix 
from this group is: 1/166, 5/166, 10/166, 50/166 and 100/166 (~1%, 3%, 6%, 30% and 60%). In short, the chance for an affix to appear is frequency/total_frequency. This field can hold values from 0 to 255. 0 will effectivelt make the affix never appear (
unless accessed by a cube recipe, but see under Spawnable).

Group - The group an affix is assigned to. The game cannot pick more then one affix from each group, this is used to prevent an item from spawning say with Ferocious and Cruel at the same time. (be aware that you can put affixes in MagicSuffix, 
MagicPrefix and AutoMagic in the same group, thus having prefix A never spawn together with suffix B). A blank field obviously puts the affix in group 0, this is not a bug.

Mod1Code to Mod3Code - The modifier(s) granted by this affix. This is an ID pointer from PROPERTIES.txt.

Mod1Param to Mod3Param - The parameter passed to the associated modifier. Whenever a modifier uses the parameter or not depends on the modifier, see PROPERTIES.txt.

Mod1Min to Mod3Min - The minimum value passed to the associated modifier. Whenever, and if so how, the modifier uses this value depends on the modifier, see PROPERTIES.txt.

Mod1Max to Mod3Max - The maximum value passed to the associated modifier. Whenever, and if so how, the modifier uses this value depends on the modifier, see PROPERTIES.txt.

Transform - A boolean that controls whenever or not this affix will alter the color of the item it appears on. 0 = do not change color, 1 = change color.

TransformColor - An ID pointer from COLORS.txt, this determines what color the modifier will give this item when the Transform boolean is true.

iType1 to iType7 - These fields are ID pointers to ItemTypes.txt that control what item types this affix can appear on. The affix can appear on all item types that inherit the item type in this field. So putting 'armo' in here will make it appear on all 
armor (etc).

eType1 to eType5 - These fields are ID pointers to ItemTypes.txt that control what item types this affix will never appear on. The affix will not appear on any item type that inherits this item type. So putting 'armo' here would prevent it from showing 
up on all armor (etc).

Divide - This does not work the way the name suggests (the fields are all filled with 0), if it works at all that is, it doesn't appear to work in ItemStatCost so it probably doesn't here either. But if it did work like that other column is supposed to 
work, this controls the percentage the price is reduced by in 1024th. Where 1024 equals 100%.

Multiply - The price of the item is multiplied by this value when this affix is present on it (keep away from this field unless you want to make something extremely expensive without editing ItemStatCost or the base prices). In 1024ths.

Add - The hard amount that is added to the price of this item when this affix is present on it.

*/

/*
文件名1：MagicPrefix.txt
文件名2：MagicSuffix.txt
文件路径：暗黑所在文件夹/data/global/excel/


()
打赏

    回复

    1楼
    2011-09-16 23:28

    举报 |

本吧精品
【受属性】Build一个不掉Mana的顶球SOR
大箱子整理工具第2版BoxTool终于完成
[最后一水]DOS游戏怀旧大截图..
重温经典：追忆《暗黑破坏神1》
本吧精品
【蚊帐出品】暗黑新乐趣MOD发布~
十年之后，你还会不会打开暗黑2，满怀期待的开始MF么
【毕须博须自制MOD】---------【暗吧破坏神---最初版】
休闲娱乐solo：盾击圣骑

    zqtjingzi
    小吧主
    12

文件名解析：
Magic：魔法，在这里指魔法属性。
Prefix：前缀，就是魔法词缀中的前缀。
Suffix：后缀，就是魔法词缀中的后缀。
所以这两个文件描述了所有魔法词缀前缀与后缀的相关信息。
此文件中的每一行表示一个词缀前缀或后缀。


回复

    2楼
    2011-09-16 23:29

    举报 |

    zqtjingzi
    小吧主
    12

特殊说明：之所以把这两个文件放在一起说明是因为它们所含有的列几乎是一模一样的。


回复

    3楼
    2011-09-16 23:29

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    4楼
    2011-09-16 23:29

    举报 |

    zqtjingzi
    小吧主
    12

Name：前缀名或后缀名。

version：适用的最低游戏版本。’0‘-diablo原版;‘100‘-破坏之王。

spawnable：是否可在游戏中生成。1=是，0=否

rare：此词缀是否能在稀有（亮金）物品上出现。如+3单系技能的词缀此列为0，所以这样的属性不能出现在稀有（亮金）物品上。1=是，0=否

level：词缀等级。只有当物品等级大于此词缀的词缀等级时，此词缀才可能出现在这一物品上。产生该前缀所必需的怪物级别(见附件A)。

maxLevel：词缀等级上限。当此列有值时，此词缀只会出现在物品等级小于此等级的物品上。该前缀能产生的最大级别，如超过将不再产生(见附件A)。

levelreq：使用带有此词缀物品的角色等级需求。，可能用来增加基本需求

classSpecfic：是否为某一职业专用。设置为特定角色才能产生该前缀(ama,sor,nec,pal,bar,dru,ass)。

class：是否对某一职业有特殊的使用等级需求。若有的话，此列当填写职业代码。如传送聚气词缀。对除法师外的所有职业使用等级至少为24级，而法师18级就够了。

classLevelreq：紧跟上一列，特定职业的需求。

frequency：在同一组词缀中此词缀出现的频率。

group：词缀所属的词缀组。对每一个物品而言，属于同一词缀组的词缀只能出现一个。
将类似的若干前缀组合，并计算其几率(见附件A)。
M-X.(参考代码表)

mod1Code：此词缀的第1个属性。

mod1Param：此词缀的第1个属性的参数。

mod1Min：此词缀的第1个属性的最小值参数。

mod1Max：此词缀的第1个属性的最大值参数。

以下的mod2Code至mod3Max这8列分别表示此词缀的第2、3个属性，具体含义参考第1条属性的解释。



回复

    5楼
    2011-09-16 23:30

    举报 |

    zqtjingzi
    小吧主
    12

transform：此词缀是否会使物品变色。1代表变色，0代表不变色。

transformColor：当此词缀会使物品变色时，此物品所变成的颜色。与Colors.txt关联。

itype1-7：此词缀适用于的第1-7种装备类型。

etype1-3(5)：此词缀不适用的第1-3(5)种装备类型，所有etype应是某一itype的子类型。

说明：在MagicPrefix.txt中etype共有5列，在MagicSuffix.txt中etype共有3列。
此词缀最终能够适用的装备类型为sum(itype1-7) - sum(etype1-3(5))，即所有itype的总和再除去etype中的类型。

divide：价格因子1。卖给NPC时的价格减少因子

multiply：价格因子2。

add：价格因子3。

*eol：行尾标志，必须为0。

附件A -- 组，频率和前缀的决定： 

#若干个类似的前缀(一般为同一类型,当然并不是非得如此,)通过一个数字标志组成一个群组，如121-152共32个前缀都属于同一组(101)，如果你懂一点e文的话，你会发现它们都有类似‘神圣的,圣洁的’的意思(如‘holy’,‘saintly’)
！当游戏在寻找一个可利用的前缀时，同一组中的前缀它只会选择一个。这样可以防止前缀的重复(overlapping)，比如两个’+1 light radius‘(加1照亮范围)，毫无疑问，这是非常浪费的。

#’哪些前缀是可获得的‘可通过下面的方式计算得出 ---- 由Ruvanal提供

先介绍几个术语：
alvl = 前缀等级。对一个物品而言，它被用来与‘level’和‘maxlevel’的值进行比较(‘level’和‘maxlevel’说明见上,这些可以在前缀和后缀表中查到!)。当你参考某个‘前缀/后缀’时，它的值就在‘level’栏。
ilvl = 固有等级(一般参考物品等级(item level),当然如果是物品的产生等级(item creation level)的话会更好一些)。当一个物品产生(或者说被创造)时，这个值也就同时被设定了。
mlvl = 怪物等级。
clvl = 角色等级。
qlvl = 质量等级。这个值可以在armor.txt,weapon.txt和misc.txt的level栏查到。这个值被用来产生武器(weapXX)和盔甲(armoXX)的财富级别(treasure classes)。
magic_lvl = 某些物品上的魔法等级奖励。到目前为止,只有下面这些物品有这种奖励：权杖(‘wands’,只是‘普通和扩展级’,精华级无),杖(staves),天球(’orbs‘,取值1)和圈冠(‘circlets’,circlet(头圈)=3,Coronet(宝冠)=8,Tiara(三重冠)=13,Diadem(王冠)=1.)。

当一个有前缀的物品产生时，‘alvl’值通过下面的方法从‘ilvl’和‘qlvl’值计算得到*：
If (ilvl>99) then {ilvl=99} 
if (qlvl>ilvl) then {ilvl=qlvl} ;**
if (magic_lvl>0) then {alvl=ilvl+magic_lvl} 
else 
{ 
if (ilvl<(99-qlvl/2)) 
then {alvl=ilvl-qlvl/2} 
else {alvl=2*ilvl-99} 
} 
If (alvl>99) then {alvl=99} 
*注：所有的计算结果(包括每一步)均取整数。
**注：这个新的‘ilvl’值只在计算过程中使用。储存在物品数据文件(items data file)中的‘ilvl’值保持不变。 

#当游戏已经知道哪些词缀可以用来被分派时，它还要知道如何从给定的有多重选择的前缀组中选择合适的前缀。这个工作将由‘frequency’(频率)栏来完成。

‘Frequency’(频率)决定了该前缀被选中的几率，频率值越高产生几率越大。
举个例子说明：
假设：Mod1freq=5,Mod2freq=3,Mod3freq=2,Mod4freq=1
如果只能产生'Mod1'和'Mod2',则产生它们的概率如下：
'Mod1' = 5/(5+3)=5/8=62.5%
'Mod2' = 3/(5+3)=5/8=37.5%
如果四个修饰均能产生,则相应的概率如下：
'Mod1' = 5/(5+3+2+1) = 5/11=45.5%
'Mod2' = 3/(5+3+2+1) = 3/11=27.3%
'Mod3' = 2/(5+3+2+1) = 2/11=18.2%
'Mod4' = 1/(5+3+2+1) = 1/11=9.1%

由上面可以看出，你可以在一个更高的等级(higher level)上通过'maxlevel'栏将那些低质量(lower quality)的前缀滤掉。通过设定'maxlevel‘值使其有一个交叠区，你可以使那些类型的前缀在所有的级别(all levels)上都可以获得，从而有效的保持那些强大的(powerful)前缀能聚集(
pool)在一起。
-------------------------------------------------------------------------------------
附件B -- itype & etype

itype = Inclusion TYPE(包含类型) & etype = Exclusion TYPE(排除类型)

这个决定了一个给定的词缀可以在{itype}所包含的物品类型上产生，而不能产生于{etype}所包含的物品类型。

比如：itype = {weap,armo} etype = {axe,helm,belt}
这个表示该词缀可以产生在所有的武器和盔甲上，但是在斧子,头盔和腰带上不能产生。

通过这种方法(在‘itype’和‘etype’里面设定物品类型)，你可以控制某类物品是否能产生(或者说接受)该词缀，比如让某个(些)词缀只能在剑(swords)上产生，或者不能让它在剑上产生。当然，首先你必须知道该物品的代码。

注意：以上的说明同样适应于其他有‘itype/etype’的.txt文件，如automagic,rareprefix/suffix。

*/

typedef struct
{
    unsigned char vName[32];

    unsigned short iPadding8;
    unsigned short vversion;

    unsigned int vmod1code; //properties
    int vmod1param;
    int vmod1min;
    int vmod1max;

    unsigned int vmod2code; //properties
    int vmod2param;
    int vmod2min;
    int vmod2max;

    unsigned int vmod3code; //properties
    int vmod3param;
    int vmod3min;
    int vmod3max;

    unsigned short vspawnable;
    unsigned short vtransformcolor; //colors

    unsigned short vlevel;
    unsigned short iPadding22;

    unsigned int vgroup;

    unsigned int vmaxlevel;

    unsigned char vrare;
    unsigned char vlevelreq;
    unsigned char vclassspecific; //playerclass
    unsigned char vclass; //playerclass

    unsigned short vclasslevelreq;
    unsigned short vitype1; //itemtypes

    unsigned short vitype2;
    unsigned short vitype3;

    unsigned short vitype4;
    unsigned short vitype5;

    unsigned short vitype6;
    unsigned short vitype7;

    unsigned short vetype1; //itemtypes
    unsigned short vetype2;

    unsigned short vetype3;
    unsigned short vetype4;

    unsigned short vetype5;
    unsigned short vfrequency;

    unsigned int vdivide;
    unsigned int vmultiply;
    unsigned int vadd;
} ST_LINE_INFO;

static char *m_apcNotUsed[] =
{
    "*comment",
    "transform",
    NULL,
};

static int MagicPrefix_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int id;
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
    else if ( !strcmp(acKey, "mod3code") )
    {
        pcResult = Properties_GetProperty(pstLineInfo->vmod3code);
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
    else if ( !strcmp(acKey, "transformcolor") )
    {
        pcResult = Colors_GetColorCode(pstLineInfo->vtransformcolor);
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
    else if ( !strcmp(acKey, "classspecific") )
    {
        pcResult = PlayerClass_GetClass(pstLineInfo->vclassspecific);
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
    else if ( !strcmp(acKey, "class") )
    {
        pcResult = PlayerClass_GetClass(pstLineInfo->vclass);
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
    else if ( strlen("itype1") == strlen(acKey) && 1 == sscanf(acKey, "itype%d", &id) )
    {
        unsigned short *pwIType = &pstLineInfo->vitype1;
        pcResult = ItemTypes_GetItemCode(pwIType[id - 1]);
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
        unsigned short *pwIType = &pstLineInfo->vetype1;
        pcResult = ItemTypes_GetItemCode(pwIType[id - 1]);
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

static char *MagicPrefix_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strcpy(pcKey, pstLineInfo->vName);
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

int process_magicprefix(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Name, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, version, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod1code, UINT); //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod1param, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod1min, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod1max, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod2code, UINT); //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod2param, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod2min, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod2max, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod3code, UINT); //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod3param, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod3min, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod3max, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, spawnable, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, transformcolor, USHORT); //colors

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, level, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, group, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, maxlevel, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rare, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, levelreq, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, classspecific, UCHAR); //playerclass
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, class, UCHAR); //playerclass

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, classlevelreq, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype1, USHORT); //itemtypes

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype3, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype4, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype5, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype6, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype7, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etype1, USHORT); //itemtypes
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etype2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etype3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etype4, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etype5, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, frequency, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, divide, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, multiply, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, add, UINT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(properties, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(colors, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(playerclass, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(itemtypes, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            //m_stCallback.pfnGetKey = MagicPrefix_GetKey;
            m_stCallback.pfnConvertValue = MagicPrefix_ConvertValue;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

