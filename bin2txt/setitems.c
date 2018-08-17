#include "global.h"

#define FILE_PREFIX "setitems"

/*
Title 	SetItems.txt File Guide
Description 	by Alkalund & Char, revised by Myhrginoc
Sent by 	
index: string key to item's name in a .tbl file

set: string key to the index field in Sets.txt - the set the item is a part of.

item: base item code of this set item (matches code field in Weapons.txt, Armor.txt or Misc.txt files).

*item: name of the base item of this set item (reference only, not loaded into game).

Rarity: Chance to pick this set item if more then one set item of the same base item exist, this uses the common rarity/total_rarity formula, so if you have two set rings, one with a rarity of 100 the other with a rarity of 1, then the first will drop 
100/101 percent of the time (99%) and the other will drop 1/101 percent of the time (1%), rarity can be anything between 0 and 255.

lvl: The quality level of this set item, monsters, cube recipes, vendors, objects and the like most be at least this level or higher to be able to drop this item, otherwise they would drop a magical item with twice normal durability.

lvl req: The character level required to use this set item.

chrtransform: Palette shift to apply to the the DCC component-file and the DC6 flippy-file (whenever or not the color shift will apply is determined by Weapons.txt, Armor.txt or Misc.txt). This is an ID pointer from Colors.txt.

invtransform: Palette shift to apply to the the DC6 inventory-file (whenever or not the color shift will apply is determined by Weapons.txt, Armor.txt or Misc.txt). This is an ID pointer from Colors.txt.

invfile: Overrides the invfile and setinvfile specified in Weapons.txt, Armor.txt or Misc.txt for the base item. This field contains the file name of the DC6 inventory graphic (without the .dc6 extension).

flippyfile: Overrides the flippyfile specified in Weapons.txt, Armor.txt or Misc.txt for the base item. This field contains the file name of the DC6 flippy animation (without the .dc6 extension).

dropsound: Overrides the dropsound (the sound played when the item hits the ground) specified in Weapons.txt, Armor.txt or Misc.txt for the base item. This field contains an ID pointer from Sounds.txt.

dropsfxframe: How many frames after the flippy animation starts playing will the associated drop sound start to play. This overrides the values in Weapons.txt, Armor.txt or Misc.txt.

usesound: Overrides the usesound (the sound played when the item is consumed by the player) specified in Weapons.txt, Armor.txt or Misc.txt for the base item. This field contains an ID pointer from Sounds.txt.

cost mult: The base item's price is multiplied by this value when sold, repaired or bought from a vendor.

cost add: After the price has been multiplied, this amount of gold is added to the price on top.

add func: a property mode field that controls how the variable attributes will appear and be functional on a set item. See the appendix for further details about this field's effects.
0 -> no green properties on item (apropxx will appear as a blue attribute on the list instead).
1 -> green properties (apropxx) depend on which other items from the set are equipped.
2 -> green properties (apropxx) depend on how many other items from the set are equipped.

BLUE ATTRIBUTES

prop1 to prop9: An ID pointer of a property from Properties.txt, these columns control each of the nine different fixed (blue) modifiers a set item can grant you at most.

par1 to par9: The parameter passed on to the associated property, this is used to pass skill IDs, state IDs, monster IDs, montype IDs and the like on to the properties that require them, these fields support calculations.

min1 to min9: Minimum value to assign to the associated property. Certain properties have special interpretations based on stat encoding (e.g. chance-to-cast and charged skills). See the File Guide for Properties.txt and ItemStatCost.txt for further 
details.

max1 to max9: Maximum value to assign to the associated property. Certain properties have special interpretations based on stat encoding (e.g. chance-to-cast and charged skills). See the File Guide for Properties.txt and ItemStatCost.txt for further 
details.

GREEN ATTRIBUTES

aprop1a,aprop1b to aprop5a,aprop5b: An ID pointer of a property from Properties.txt, these columns control each of the five pairs of different variable (green) modifiers a set item can grant you at most.

apar1a,apar1b to apar5a,apar5b: The parameter passed on to the associated property, this is used to pass skill IDs, state IDs, monster IDs, montype IDs and the like on to the properties that require them, these fields support calculations.

amin1a,amin1b to amin5a,amin5b: Minimum value to assign to the associated property. Certain properties have special interpretations based on stat encoding (e.g. chance-to-cast and charged skills). See the File Guide for Properties.txt and ItemStatCost.
txt for further details.

amax1a,amax1b to amax5a,amax5b: Maximum value to assign to the associated property. Certain properties have special interpretations based on stat encoding (e.g. chance-to-cast and charged skills). See the File Guide for Properties.txt and ItemStatCost.
txt for further details.

*eol: terminator field, not used in game, primary purpose is to keep Microsoft Excel from misbehaving.

APPENDIX

Green attributes will appear depending on how many set items are equipped, if the add func field is either 1 or 2. If the add func field is 1, in addition to how many items, the green attributes are controlled by which other items you have equipped as 
well. If a set has X number of items, at most there will be X-1 green attributes on any item.

If add func = 2, these properties will appear as below. Many of the "classic" sets in the unmodded game have this configuration.
aprop1a, aprop1b -> when any second set item is also equipped.
aprop2a, aprop2b -> when any third set item is also equipped.
aprop3a, aprop3b -> when any fourth set item is also equipped.
aprop4a, aprop4b -> when any fifth set item is also equipped.
aprop5a, aprop5b -> when any sixth set item is also equipped.

The fun really begins when add func = 1. Different properties can emerge as different items are equipped in combination from the same set. The attributes appear for specific item pairs regardless of whether or how many other items from the set are also 
equipped. Civerb's Ward (shield) is the one and only example of this configuration in the unmodded game.

If the first item listed in the set definition is equipped, it will get the green property:
aprop1a, aprop1b -> when the second item listed in the set definition is also equipped.
aprop2a, aprop2b -> when the third item listed in the set definition is also equipped.
aprop3a, aprop3b -> when the fourth item listed in the set definition is also equipped.
aprop4a, aprop4b -> when the fifth item listed in the set definition is also equipped.
aprop5a, aprop5b -> when the sixth item listed in the set definition is also equipped.

If the second item listed in the set definition is equipped, it will get the green property:
aprop1a, aprop1b -> when the first item listed in the set definition is also equipped.
aprop2a, aprop2b -> when the third item listed in the set definition is also equipped.
aprop3a, aprop3b -> when the fourth item listed in the set definition is also equipped.
aprop4a, aprop4b -> when the fifth item listed in the set definition is also equipped.
aprop5a, aprop5b -> when the sixth item listed in the set definition is also equipped.

If the third item listed in the set definition is equipped, it will get the green property:
aprop1a, aprop1b -> when the first item listed in the set definition is also equipped.
aprop2a, aprop2b -> when the second item listed in the set definition is also equipped.
aprop3a, aprop3b -> when the fourth item listed in the set definition is also equipped.
aprop4a, aprop4b -> when the fifth item listed in the set definition is also equipped.
aprop5a, aprop5b -> when the sixth item listed in the set definition is also equipped.

If the fourth item listed in the set definition is equipped, it will get the green property:
aprop1a, aprop1b -> when the first item listed in the set definition is also equipped.
aprop2a, aprop2b -> when the second item listed in the set definition is also equipped.
aprop3a, aprop3b -> when the third item listed in the set definition is also equipped.
aprop4a, aprop4b -> when the fifth item listed in the set definition is also equipped.
aprop5a, aprop5b -> when the sixth item listed in the set definition is also equipped.

If the fifth item listed in the set definition is equipped, it will get the green property:
aprop1a, aprop1b -> when the first item listed in the set definition is also equipped.
aprop2a, aprop2b -> when the second item listed in the set definition is also equipped.
aprop3a, aprop3b -> when the third item listed in the set definition is also equipped.
aprop4a, aprop4b -> when the fourth item listed in the set definition is also equipped.
aprop5a, aprop5b -> when the sixth item listed in the set definition is also equipped.

If the sixth item listed in the set definition is equipped, it will get the green property:
aprop1a, aprop1b -> when the first item listed in the set definition is also equipped.
aprop2a, aprop2b -> when the second item listed in the set definition is also equipped.
aprop3a, aprop3b -> when the third item listed in the set definition is also equipped.
aprop4a, aprop4b -> when the fourth item listed in the set definition is also equipped.
aprop5a, aprop5b -> when the fifth item listed in the set definition is also equipped.

*/

/*
index – 物品名称；
set – 当前物品所属套装名称；
item – 当前物品的基本代码；
*item – 套装中当前物品的名称（注释用）；
rarity – 物品的稀有级别；
lvl – 物品的级别；
lvl req – 使用物品所需要的角色级别；
chrtransform – 当角色拥有当前物品时，颜色的变化；
invtransform – 物品栏中此物品的颜色变化；
invfile – 此物品所采用的图像（无扩展名的*.Dc6文件）；
flippyfile - 此物品装备时所采用的图像（无扩展名）；
dropsound – 此物品掉落时的声音；
dropsfxframe -此物品掉落时的声音播放声音的祯数；
usesound – 此物品在不可用状态下所采用的声音；
cost mult – 物品价格计算底数；
cost add – 物品价格计算参数；
add func – 额外的属性；
prop1 – 此物品的第一个附加属性；
par1 - 此物品的第一个附加属性类型；
min1 – 此物品的第一个附加属性的最小值；
max1 - 此物品的第一个附加属性的最大值；
prop2 – 此物品的第二个附加属性；
par2 - 此物品的第二个附加属性类型；
min2 - 此物品的第二个附加属性的最小值；
max2 – 此物品的第二个附加属性的最大值；
prop3 – 此物品的第三个附加属性；
par3 – 此物品的第三个附加属性类型；
min3 - 此物品的第三个附加属性的最小值；
max3 – 此物品的第三个附加属性的最大值；

此后诸如prop#、par#、min#、max#等参考以上解释；

aprop1a – 此物品的1号额外第一附加属性（绿色属性，即本套物品达到两套以上时所提供的附加属性）；
apar1a -此物品的1号额外第一附加属性的参数；
amin1a -此物品的1号额外第一附加属性最小值；
amax1a -此物品的1号额外第一附加属性最大值；
aprop1b -此物品的1号额外第二附加属性（绿色属性，即本套物品达到两套以上时所提供的附加属性）；
apar1b -此物品的1号额外第二附加属性的参数；
amin1b - -此物品的1号额外第二附加属性最小值；
amax1b -此物品的1号额外第二附加属性最大值；
aprop2a -此物品的2号额外第一附加属性（绿色属性，即本套物品达到三套以上时所提供的附加属性）；
apar2a -此物品的2号额外第一附加属性的参数；
amin2a -此物品的2号额外第一附加属性最小值；
amax2a -此物品的2号额外第一附加属性最大值；
aprop2b -此物品的2号额外第二附加属性（绿色属性，即本套物品达到三套以上时所提供的附加属性）；
apar2b -此物品的2号额外第二附加属性的参数；
amin2b -此物品的2号额外第二附加属性最小值；
amax2b -此物品的2号额外第二附加属性最大值；
aprop3a -此物品的3号额外第一附加属性（绿色属性，即本套物品达到四套以上时所提供的附加属性）；
apar3a -此物品的3号额外第一附加属性的参数；
amin3a -此物品的3号额外第一附加属性最小值；
amax3a -此物品的3号额外第一附加属性最大值；
aprop3b -此物品的3号额外第二附加属性（绿色属性，即本套物品达到四套以上时所提供的附加属性）；
apar3b -此物品的3号额外第二附加属性的参数；
amin3b -此物品的3号额外第二附加属性最小值；
amax3b -此物品的3号额外第二附加属性最大值；
aprop4a -此物品的4号额外第一附加属性（绿色属性，即本套物品达到五套以上时所提供的附加属性）；
apar4a -此物品的4号额外第一附加属性的参数；
amin4a -此物品的4号额外第一附加属性最小值；
amax4a -此物品的4号额外第一附加属性最大值；
aprop4b -此物品的4号额外第二附加属性（绿色属性，即本套物品达到五套以上时所提供的附加属性）；
apar4b -此物品的4号额外第二附加属性的参数；
amin4b -此物品的4号额外第二附加属性最小值；
amax4b -此物品的4号额外第二附加属性最大值；
aprop5a -此物品的5号额外第一附加属性（绿色属性，即本套物品达到六套以上时所提供的附加属性）；
apar5a -此物品的5号额外第一附加属性的参数；
amin5a -此物品的5号额外第一附加属性的最小值；
amax5a -此物品的5号额外第一附加属性的最大值；
aprop5b -此物品的5号额外第二附加属性（绿色属性，即本套物品达到六套以上时所提供的附加属性）；
apar5b -此物品的5号额外第二附加属性的参数；
amin5b -此物品的5号额外第二附加属性的最小值；
amax5b -此物品的5号额外第二附加属性的最大值；
*eol – 文件结束标志。
*/

/*
文件名解析：
Set：套装。
Item(s)：道具，即装备。
所以此文件记录了游戏中所有组成套装的装备。
文件中的每一行代表一件某套装中的装备。


回复

    2楼
    2011-09-08 21:10

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：

Index：物品索引，也是此套装组成物品在游戏中的代码和名称。

Set：此装备属性哪一个套装。与Sets.txt关联。

Item：装备底材代码。与Armor.txt、Weapons.txt和Misc.txt关联。

*Item：装备底材注释。

Rarity：物品的稀有程度。此属性代表了在同类型的底材中此套装装备掉落的概率大小。如塔拉夏的项链此列为1，而希弗伯的项链此列为7。所以在物品等级足够的情况下塔拉夏的项链的掉率是希弗伯的七分之一。

Lvl：此套装物品的物品级别，应与Sets.txt中对应套装的Level保持一致。

Lvl req：使用此装备所需的角色的等级。

Chrtransform：角色装备该物品后在人物形象中显示的颜色。

Invtransform：物品栏中该物品的颜色。一般来说与上一属性一样。

Invfile：此物品在物品栏中所使用的图像。可自己指定图片，若想使用默认的不填此列即可。

Flippy file：角色装备该物品后在人物形象中显示时所使用的图像。

Dropsound：物品掉落时发出的声音。此列一般为空，表示使用默认值，即与此暗金装备的底材掉落时发出同样的声音。

Dropsfxframe：物品掉落时声音延长时间。此列一般为空，表示使用默认值，即与此暗金装备的底材掉落时有同样的声音延长。

Usesound：物品装备时所使用的声音。此列一般为空，表示使用默认值，即与此暗金装备的底材掉落时有同样的使用声音。

Cost mult：物品卖给NPC时的价格计算参数。

Cost add：物品卖给NPC时的价格计算参数。

Add Func：是否有附加属性，或可称之为套装激活属性，在装备属性有以绿色文字显示。0代表没有，1或2代表有。我没发现1和2有什么区别。

Prop1-9：此物品的第一个属性。所有可用属性在Properties.txt写明。

Par1-9：第一个属性的参数。

Min1-9：第一个属性的最小值参数。

Max1-9：第一个属性的最大值参数。

由此可知，套装装备在不激活套装属性的前提下，每件最多只能有9个属性，而暗金装备最多有12个。

aProp1a：属性1a的代码。所谓1a，就是指除此件装备之外，再额外装备一件同套装备后附加的第一个属性。同理，1b指的是再额外装备一件同套装备后附加的第二个属性；2a指的是再额外装备两件同套装备后附加的第二个属性。

aPar1a：属性1a的参数。

aMin1a：属性1a的最小值参数。

aMax1a：属性1a的最大值参数。

以下1b、2a、2b、3a、3b、4a、4b、5a、5b各4列，含义类似。

由此可知，每多额外穿一件套装，每个套装组成装备最多增加2个属性。
所以从个人定制的角度，套装的可能性要远大于暗金装备，尤其是多件套装。
*/

typedef struct
{
    unsigned short wSetItemId;
    unsigned char vindex[32];

    unsigned short iPadding8;

    unsigned int dwTblIndex;

    unsigned char vitem[4];

    unsigned int vset;  //sets.txt

    unsigned short vlvl;
    unsigned short vlvlmyspreq;

    unsigned int vrarity;

    unsigned int vcostmyspmult;
    unsigned int vcostmyspadd;

    unsigned char vchrtransform;    //color
    unsigned char vinvtransform;    //color
    unsigned char vflippyfile[32];

    unsigned char vinvfile[32];

    unsigned short vdropsound;  //sounds

    unsigned short vusesound;   //sounds
    unsigned char vdropsfxframe;
    unsigned char vaddmyspfunc;

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

    int vaprop1a;   //properties
    int vapar1a;
    int vamin1a;
    int vamax1a;
    int vaprop1b;   //properties
    int vapar1b;
    int vamin1b;
    int vamax1b;

    int vaprop2a;   //properties
    int vapar2a;
    int vamin2a;
    int vamax2a;
    int vaprop2b;   //properties
    int vapar2b;
    int vamin2b;
    int vamax2b;

    int vaprop3a;   //properties
    int vapar3a;
    int vamin3a;
    int vamax3a;
    int vaprop3b;   //properties
    int vapar3b;
    int vamin3b;
    int vamax3b;

    int vaprop4a;   //properties
    int vapar4a;
    int vamin4a;
    int vamax4a;
    int vaprop4b;   //properties
    int vapar4b;
    int vamin4b;
    int vamax4b;

    int vaprop5a;   //properties
    int vapar5a;
    int vamin5a;
    int vamax5a;
    int vaprop5b;   //properties
    int vapar5b;
    int vamin5b;
    int vamax5b;
} ST_LINE_INFO;

typedef struct
{
    int vprop1;    //properties
    int vpar1;
    int vmin1;
    int vmax1;
} ST_SETITEM;

typedef struct
{
    unsigned char vindex[32];
} ST_SETITEMS;

static char *m_apcInternalProcess[] =
{
    "*eol",
    NULL,
};

static char *m_apcNotUsed[] =
{
    "*item",
    NULL,
};

static unsigned int m_uiSetItemCount = 0;
static ST_SETITEMS *m_astSetItems = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astSetItems, ST_SETITEMS);

char *SetItems_GetItemUniqueCode(unsigned int id)
{
    if ( id - 1 < m_uiSetItemCount )
    {
        return m_astSetItems[id - 1].vindex;
    }

    return NULL;
}

static int SetItems_ConvertValue_Pre(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    int result = 0;

    if ( !strcmp(acKey, "index") )
    {
        strncpy(m_astSetItems[m_uiSetItemCount].vindex, pstLineInfo->vindex, sizeof(m_astSetItems[m_uiSetItemCount].vindex));
        String_Trim(m_astSetItems[m_uiSetItemCount].vindex);
        m_uiSetItemCount++;
    }

    return result;
}

static int SetItems_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "*eol") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static int SetItems_ConverValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int id;
    int result = 0;

    if ( !strcmp("set", acKey) )
    {
        pcResult = Sets_GetSetName(pstLineInfo->vset);
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
    else if ( !strcmp("chrtransform", acKey) )
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
    else if ( !strcmp("invtransform", acKey) )
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
    else if ( !strcmp("dropsound", acKey) )
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
    else if ( !strcmp("usesound", acKey) )
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
    else if ( strlen("prop1") == strlen(acKey) && 1 == sscanf(acKey, "prop%d", &id) )
    {
        ST_SETITEM *pstSetItem = (ST_SETITEM *)&pstLineInfo->vprop1;
        pcResult = Properties_GetProperty(pstSetItem[id - 1].vprop1);
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
    else if ( strlen("par1") == strlen(acKey) && 1 == sscanf(acKey, "par%d", &id) )
    {
        ST_SETITEM *pstSetItem = (ST_SETITEM *)&pstLineInfo->vprop1;
        pcResult = Properties_GetProperty(pstSetItem[id - 1].vprop1);
        if ( pcResult )
        {
            if ( !strcmp("skill", pcResult) )
            {
                pcResult = Skills_GetSkillName(pstSetItem[id - 1].vpar1);
                if ( pcResult )
                {
                    strcpy(acOutput, pcResult);
                }
                else
                {
                    sprintf(acOutput, "%d", pstSetItem[id - 1].vpar1);
                }
            }
            else
            {
                sprintf(acOutput, "%d", pstSetItem[id - 1].vpar1);
            }
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( 'a' == acKey[strlen(acKey) - 1] && 1 == sscanf(acKey, "aprop%da", &id) )
    {
        ST_SETITEM *pstSetItem = (ST_SETITEM *)&pstLineInfo->vaprop1a;
        pcResult = Properties_GetProperty(pstSetItem[(id - 1) * 2].vprop1);
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
    else if ( 'a' == acKey[strlen(acKey) - 1] && 1 == sscanf(acKey, "apar%da", &id) )
    {
        ST_SETITEM *pstSetItem = (ST_SETITEM *)&pstLineInfo->vaprop1a;
        pcResult = Properties_GetProperty(pstSetItem[(id - 1) * 2].vprop1);
        if ( pcResult )
        {
            if ( !strcmp("skill", pcResult) )
            {
                pcResult = Skills_GetSkillName(pstSetItem[(id - 1) * 2].vpar1);
                if ( pcResult )
                {
                    strcpy(acOutput, pcResult);
                }
                else
                {
                    sprintf(acOutput, "%d", pstSetItem[(id - 1) * 2].vpar1);
                }
            }
            else
            {
                sprintf(acOutput, "%d", pstSetItem[(id - 1) * 2].vpar1);
            }
        }
        else
        {
            acOutput[0] = 0;
        }
        result = 1;
    }
    else if ( 'b' == acKey[strlen(acKey) - 1] && 1 == sscanf(acKey, "aprop%db", &id) )
    {
        ST_SETITEM *pstSetItem = (ST_SETITEM *)&pstLineInfo->vaprop1b;
        pcResult = Properties_GetProperty(pstSetItem[(id - 1) * 2].vprop1);
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
    else if ( 'b' == acKey[strlen(acKey) - 1] && 1 == sscanf(acKey, "apar%db", &id) )
    {
        ST_SETITEM *pstSetItem = (ST_SETITEM *)&pstLineInfo->vaprop1b;
        pcResult = Properties_GetProperty(pstSetItem[(id - 1) * 2].vprop1);
        if ( pcResult )
        {
            if ( !strcmp("skill", pcResult) )
            {
                pcResult = Skills_GetSkillName(pstSetItem[(id - 1) * 2].vpar1);
                if ( pcResult )
                {
                    strcpy(acOutput, pcResult);
                }
                else
                {
                    sprintf(acOutput, "%d", pstSetItem[(id - 1) * 2].vpar1);
                }
            }
            else
            {
                sprintf(acOutput, "%d", pstSetItem[(id - 1) * 2].vpar1);
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

int process_setitems(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, index, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, set, INT);  //sets.txt

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lvl, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lvlmyspreq, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rarity, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, costmyspmult, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, costmyspadd, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, chrtransform, UCHAR);    //color
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invtransform, UCHAR);    //color
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, flippyfile, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invfile, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dropsound, USHORT);  //sounds

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, usesound, USHORT);   //sounds
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dropsfxframe, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, addmyspfunc, UCHAR);

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

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aprop1a, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, apar1a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amin1a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amax1a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aprop1b, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, apar1b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amin1b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amax1b, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aprop2a, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, apar2a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amin2a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amax2a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aprop2b, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, apar2b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amin2b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amax2b, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aprop3a, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, apar3a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amin3a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amax3a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aprop3b, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, apar3b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amin3b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amax3b, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aprop4a, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, apar4a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amin4a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amax4a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aprop4b, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, apar4b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amin4b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amax4b, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aprop5a, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, apar5a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amin5a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amax5a, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, aprop5b, INT);   //properties
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, apar5b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amin5b, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, amax5b, INT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_uiSetItemCount = 0;

            m_stCallback.pfnConvertValue = SetItems_ConvertValue_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(sets, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(colors, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(sounds, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(properties, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(skills, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = SetItems_ConverValue;
            m_stCallback.pfnFieldProc = SetItems_FieldProc;
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

