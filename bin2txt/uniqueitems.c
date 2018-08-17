#include "global.h"

#define FILE_PREFIX "uniqueitems"

/*
Title 	UniqueItems.txt
Description 	by Nefarius (written from scratch)
Sent by 	
Index: The ID pointer that is referenced by the game in TreasureClassEx.txt and CubeMain.txt, this also controls the string that will be used to display the item's name in-game.

Version: What game version was this unique item added in, 0 referes to real classic Diablo II (1.00-1.06), 1 refers to new classic Diablo II (1.07-1.11) and 100 refers to the Expansion Set, items with 100 will be unable to drop in Classic Diablo II.

Ladder: Is this item available only in Ladder and Single Player games? (boolean, 0 = available in all game types, 1 = available only in single player and ladder gaes).

Rarity: Chance to pick this unique item if more then one unique item of the same base item exist, this uses the common rarity/total_rarity formula, so if you have two unique rings, one with a rarity of 100 the other with a rarity of 1, then the first 
will drop 100/101 percent of the time (99%) and the other will drop 1/101 percent of the time (1%), rarity can be anything between 1 and 255 (rarity of less then 1 will be set to 1 by the code).

NoLimit: Can this item drop more then once per game? (boolean, 0 = can drop only once per game, 1 = can drop more then once per game). Basically when the game drops a unique item it sets a check mark in a table it holds in memory of what unique items 
were dropped, when, should you be lucky enough to get the same item again, it will check whenever this item has been dropped already, and if NoLimit is false, it will drop a rare item with enhanced durability instead.

Lvl: The quality level of this unique item, monsters, cube recipes, vendors, objects and the like most be at least this level or higher to be able to drop this item, otherwise they would drop a rare item with enhanced durability.

Lvl Req: The character level required to use this unique item.

Code: The code of the base form of this unique item, this is an ID pointer from Weapons.txt, Armor.txt or Misc.txt.

Carry1: Is the player only permitted to hold a single copy of this item at a time? (in reality this just prevents the player from picking up the item when it is dropped on the floor and it prevents the player from putting this item in the trading window)
. (boolean, 0 = allow the player to hold as many of this item as he wants, 1 = allow the player to hold a single copy only).

Cost Mult: The base item's price is multiplied by this value when sold, repaired or bought from a vendor.

Cost Add: After the price has been multiplied, this amount of gold is added to the price on top.

ChrTransform: Palette shift to apply to the the DCC component-file and the DC6 flippy-file (whenever or not the color shift will apply is determined by Weapons.txt, Armor.txt or Misc.txt). This is an ID pointer from Colors.txt.

InvTransform: Palette shift to apply to the the DC6 inventory-file (whenever or not the color shift will apply is determined by Weapons.txt, Armor.txt or Misc.txt). This is an ID pointer from Colors.txt.

FlippyFile: Overrides the flippyfile specified in Weapons.txt, Armor.txt or Misc.txt for the base item. This field contains the file name of the DC6 flippy animation.

InvFile: Overrides the invfile and uniqueinvfile specified in Weapons.txt, Armor.txt or Misc.txt for the base item. This field contains the file name of the DC6 inventory graphic.

DropSound: Overrides the dropsound (the sound played when the item hits the ground) specified in Weapons.txt, Armor.txt or Misc.txt for the base item. This field contains an ID pointer from Sounds.txt.

DropSfxFrame: How many frames after the flippy animation starts playing will the associated drop sound start to play. This overrides the values in Weapons.txt, Armor.txt or Misc.txt.

UseSound: Overrides the usesound (the sound played when the item is consumed by the player) specified in Weapons.txt, Armor.txt or Misc.txt for the base item. This field contains an ID pointer from Sounds.txt.

Prop1-12: An ID pointer of a property from Properties.txt, these columns control each of the 12 different modifiers a unique item can grant you at most. (In a-lay-mens-terms: "the stat that can spawn on the unique item.")

Par1-12: The parameter passed on to the associated property, this is used to pass skill IDs, state IDs, monster IDs, montype IDs and the like on to the properties that require them, these fields support calculations.

Min1-12: Minimum value to assign to the associated property. (In a-lay-mans-term's: "minimum value of the stat.")

Max1-12: Maximum value to assign to the associated property. (In a-lay-man's-terms: "maximum value of the stat.")

*EoL, *Type and *Uber are of course not loaded.

*/

/*
Index：物品名称，通常为固定的字符关键字；

Version：物品所出现的版本，0代表原版，1代表原版补丁，100代表资料片；

Enabled：物品是否包含“掉落”属性，0代表从不掉落，1代表掉落；

Ladder：物品是否包含在“天梯”模式下；

Rarity：物品的稀有程度；

Nolimit：无用参数；

Lvl：掉落该物品怪物的级别；

Lvl req：使用该物品角色的等级；

Code：物品代码，通常包括在“Weapon.txt、armor.txt、misc.txt”三个文件中；

Type：物品代码说明（仅供参考）；

Uber：是否为Uber物品（到目前为止，所有版本均未使用）；

Carry1：是否只允许携带一套本物品（1代表“是”，0代表“否”）；

Cost mult：物品价格计算底数；

Cost add：物品价格计算参数；

Chrtransform：角色使用该物品后的颜色；

Invtransform：物品栏中该物品的颜色；

Flippy file：物品整体外观所选用的图像；

Invfile：此物品在物品栏中所采用的图像；

Dropsound：物品掉落时所采用的声音；

Dropsfxframe：物品掉落时声音延长时间；

Usesound：物品装备时所使用的声音；

Prop1：此物品的第一个魔法属性；

Par1：第一个魔法属性参数，如：冷冻时间或者冷冻损伤；

Min1：确定魔法属性的最小值；

Max1：确定魔法属性的最大值。

说明：之后诸如“Prop2、Par2、Min2、Max2…”等等均参照上述4项解释即可。


Eol：文件结束标志。


*/

/*
文件名解析：
Unique：惟一的，即暗黑里的暗金类别
Item(s)：道具，即装备。
所以此文件记录了游戏中所有暗金装备。
文件中的每一行代表一个暗金装备


回复

    2楼
    2011-09-04 00:03

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：



回复

    3楼
    2011-09-04 00:03

    举报 |

    zqtjingzi
    小吧主
    12

Index：物品名称，也是此暗金物品在游戏中的代码（如物品名称翻译的键值或合成公式中的代码）。如乔丹之石在此列的值就是The Stone of Jordan。除非是自己新加的行否则不建议修改此列。


回复

    4楼
    2011-09-04 00:04

    举报 |

    zqtjingzi
    小吧主
    12

Version：物品所能出现的最低版本，0代表原版，1代表原版补丁，100代表资料片。如乔丹之石在此列的值为0，而火炬在此列的值为100。如果你想在原版中也能资料片的暗金装备，如地狱火炬和毁灭小符，就将它们此列的值改为0即可。

Enabled：物品是否可在游戏中出现，0代表不能出现，1代表可以出现。如乔丹之石在此列的值为1，而收缩戒指在此列的值为0（所以你应该没有见过这个戒指）。在阅读此文件的过程中，你会发现有一些行此列的值为0
，也就是说这些写好的暗金装备并不会在游戏中出现，你可以将它们改为1然后再到游戏中欣赏一下。另外如果对于你新加的装备，一定要将此列设为1。

Ladder：物品是否包含在“天梯”模式下。单机游戏由于没有天梯所以不受此列影响。

Rarity：物品的稀有程度。此属性代表了在同类型的底材中此暗金装备掉落的概率大小。如乔丹之石此列为1，而拿各的戒指此列为15。所以在物品等级足够的情况下乔丹之石的掉率是拿各的十五分之一。

Nolimit：无用参数。


回复

    5楼
    2011-09-04 00:04

    举报 |

    zqtjingzi
    小吧主
    12

Lvl：掉落该物品怪物的级别。此属性的含义可参考物品掉落原理一贴。大概就是说只有当怪物等级超过此列的值的时候才可能掉落此暗金装备。所以如果你想让皮叔掉愤青，将愤青的此列减小到86以下即可。

Lvl req：使用此装备所需的角色的等级。这个不用多解释了吧，如马拉此列为67。

Code：此暗金装备底材的代码，通常包括在“Weapon.txt、armor.txt、misc.txt”三个文件中。如乔丹之石此列的值为rin，就是戒指的代码。所有底材的代码请见http://tieba.baidu.com/f?kz=1193058424。

Type：此暗金装备底材的说明。如乔丹之石此列的值为ring，即戒指的英文单词。

Uber：是否为Uber物品，未使用属性。

Carry1：是否只允许携带一件本物品，1代表“是”，0代表“否”。如毁灭小符此列的值为1。

Cost mult：物品卖给NPC时的价格计算参数。

Cost add：物品卖给NPC时的价格计算参数。


回复

    6楼
    2011-09-04 00:05

    举报 |

    zqtjingzi
    小吧主
    12

Chrtransform：角色装备该物品后在人物形象中显示的颜色。如鸟人甲此列为dblu，即蓝色。而圣堂武士的力量（小鸟人甲）此列为cgrn，即绿色。

Invtransform：物品栏中该物品的颜色。一般来说与上一属性一样。

Flippy file：角色装备该物品后在人物形象中显示时所使用的图像。如果你想为你新加的暗金装备改个样子，就需要自己指定图片，若想使用默认的不填此列即可。

Invfile：此物品在物品栏中所使用的图像。可自己指定图片，若想使用默认的不填此列即可。

Dropsound：物品掉落时发出的声音。此列一般为空，表示使用默认值，即与此暗金装备的底材掉落时发出同样的声音。

Dropsfxframe：物品掉落时声音延长时间。此列一般为空，表示使用默认值，即与此暗金装备的底材掉落时有同样的声音延长。

Usesound：物品装备时所使用的声音。此列一般为空，表示使用默认值，即与此暗金装备的底材掉落时有同样的使用声音。



回复

    7楼
    2011-09-04 00:05

    举报 |

    zqtjingzi
    小吧主
    12

Prop1：此物品的第一个属性。所有可用属性在Properties.txt写明。如乔丹之石此列为mana，就是加法力的那个属性。

Par1：第一个属性的参数。如乔丹之石此列为空。因为mana不使用这个参数

Min1：第一个属性的最小值。如乔丹之石此列为20。表示最少加20法力。

Max1：第一个属性的最大值。如乔丹之石此列为20。表示最多加20法力。

由于属性之间的不同性，故每个属性有3个参数来描述，即上面的par、min和max。
每个属性使用哪个或哪几个参数请参照Properties.txt中的func1列。
如str/lvl属性只使用par参数，若par=8，则代表每级增加1点力量。
又如str属性不使用par，它使用min和max两个参数，为min为5，max为10，则代表此装备增加的力量在5到10之前变化，即常说的变量。
如果你将此文件中所有min的值都改为对应max的值，那么所有新打出的暗金装备就都变成极品变量了，效果可参考JPXXX。

说明：之后诸如“Prop2、Par2、Min2、Max2…”等等均参照上述4项解释，每个暗金装备最多可有12个属性，即prop12,par12,min12,max12。
*/

typedef struct
{
    unsigned short iPadding0;
    unsigned char vindex[32];

    unsigned short iPadding8;
    unsigned int vversion;

    unsigned char vcode[4];

#if 1
    unsigned char vBitCombined;
#else
    //01
    unsigned char iPadding11 : 4;

    unsigned char vladder : 1;
    unsigned char vcarry1 : 1;
    unsigned char vnolimit : 1;
    unsigned char venabled : 1;
#endif

    unsigned char iPadding11[3];

    unsigned int vrarity;

    unsigned short vlvl;
    unsigned short vlvlmyspreq;

    unsigned char vchrtransform;    //colors
    unsigned char vinvtransform;    //colors
    unsigned char vflippyfile[32];

    unsigned char vinvfile[32];

    unsigned short iPadding30;

    unsigned int vcostmyspmult;

    unsigned int vcostmyspadd;

    unsigned short vdropsound;  //sounds
    unsigned short vusesound;   //sounds

    unsigned int vdropsfxframe;

    int vprop1;    //properties
    int vpar1;
    int vmin1;
    int vmax1;

    int vprop2;    //properties
    int vpar2;
    int vmin2;
    int vmax2;

    int vprop3;    //properties
    int vpar3;
    int vmin3;
    int vmax3;

    int vprop4;    //properties
    int vpar4;
    int vmin4;
    int vmax4;

    int vprop5;    //properties
    int vpar5;
    int vmin5;
    int vmax5;

    int vprop6;    //properties
    int vpar6;
    int vmin6;
    int vmax6;

    int vprop7;    //properties
    int vpar7;
    int vmin7;
    int vmax7;

    int vprop8;    //properties
    int vpar8;
    int vmin8;
    int vmax8;

    int vprop9;    //properties
    int vpar9;
    int vmin9;
    int vmax9;

    int vprop10;    //properties
    int vpar10;
    int vmin10;
    int vmax10;

    int vprop11;    //properties
    int vpar11;
    int vmin11;
    int vmax11;

    int vprop12;    //properties
    int vpar12;
    int vmin12;
    int vmax12;
} ST_LINE_INFO;

typedef struct
{
    int vprop1;    //properties
    int vpar1;
    int vmin1;
    int vmax1;
} ST_UNIQUEITEM;

typedef struct
{
    unsigned char vindex[32];
} ST_SEARCHITEMS;

static char *m_apcNotUsed[] =
{
    "*type",
    "*uber",
    NULL,
};

static char *m_apcInternalProcess[] =
{
    "*eol",
    NULL,
};

static unsigned int m_uiUniqueItemCount = 0;
static ST_SEARCHITEMS *m_astUniqueItems = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astUniqueItems, ST_SEARCHITEMS);

char *UniqueItems_GetItemUniqueCode(unsigned int id)
{
    if ( id - 1 < m_uiUniqueItemCount )
    {
        return m_astUniqueItems[id - 1].vindex;
    }

    return NULL;
}

static int UniqueItems_ConvertValue_Pre(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    int result = 0;

    if ( !strcmp(acKey, "index") )
    {
        strncpy(m_astUniqueItems[m_uiUniqueItemCount].vindex, pstLineInfo->vindex, sizeof(m_astUniqueItems[m_uiUniqueItemCount].vindex));
        String_Trim(m_astUniqueItems[m_uiUniqueItemCount].vindex);
        m_uiUniqueItemCount++;
    }

    return result;
}

static int UniqueItems_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "*eol") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static int UniqueItems_BitProc(void *pvLineInfo, char *acKey, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    int result = 0;

    if ( !strcmp(acKey, "ladder") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "carry1") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "nolimit") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "enabled") )
    {
        sprintf(acOutput, "%d", ((pstLineInfo->vBitCombined & 1)) != 0);
        result = 1;
    }

    return result;
}

static int UniqueItems_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int id;
    int result = 0;

    if ( !strcmp(acKey, "chrtransform") )
    {
        pcResult = Colors_GetColorCode(pstLineInfo->vchrtransform);
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
    else if ( !strcmp(acKey, "invtransform") )
    {
        pcResult = Colors_GetColorCode(pstLineInfo->vinvtransform);
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
    else if ( !strcmp(acKey, "dropsound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vdropsound);
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
    else if ( !strcmp(acKey, "usesound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vusesound);
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
    else if ( 1 == sscanf(acKey, "prop%d", &id) )
    {
        ST_UNIQUEITEM *pstUniqueItem = (ST_UNIQUEITEM *)&pstLineInfo->vprop1;
        pcResult = Properties_GetProperty(pstUniqueItem[id - 1].vprop1);
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

int process_uniqueitems(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, index, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, version, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, code, STRING);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, ladder, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, carry1, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, nolimit, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, enabled, BitCombined, BIT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rarity, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lvl, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lvlmyspreq, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, chrtransform, UCHAR);    //colors
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invtransform, UCHAR);    //colors
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, flippyfile, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invfile, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, costmyspmult, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, costmyspadd, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dropsound, USHORT);  //sounds
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, usesound, USHORT);   //sounds

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dropsfxframe, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prop1, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, par1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, min1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, max1, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prop2, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, par2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, min2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, max2, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prop3, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, par3, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, min3, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, max3, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prop4, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, par4, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, min4, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, max4, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prop5, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, par5, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, min5, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, max5, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prop6, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, par6, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, min6, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, max6, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prop7, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, par7, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, min7, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, max7, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prop8, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, par8, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, min8, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, max8, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prop9, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, par9, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, min9, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, max9, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prop10, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, par10, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, min10, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, max10, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prop11, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, par11, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, min11, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, max11, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, prop12, INT);    //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, par12, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, min12, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, max12, INT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_uiUniqueItemCount = 0;

            m_stCallback.pfnConvertValue = UniqueItems_ConvertValue_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(colors, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(sounds, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(properties, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = UniqueItems_ConvertValue;
            m_stCallback.pfnBitProc = UniqueItems_BitProc;
            m_stCallback.pfnFieldProc = UniqueItems_FieldProc;
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

