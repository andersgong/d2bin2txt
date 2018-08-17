#include "global.h"

#define FILE_PREFIX "charstats"

/*
Title 	CharStats.txt
Description 	by Nefarius
Sent by 	
class: The character class this line refers to (this is just a reference field, you can't actually change this).

str: The amount of strength this character class will start with.

dex: The amount of dexterity this character class will start with.

int: The amount of energy and mana this character class will start with.

vit: The amount of vitality and a portion of life this character class will start with.

tot: This field is not used by the game, and never served any purpose, it's only there as reference (it contains the sum of str, dex, int and hp).

stamina: The amount of stamina this character class will start with.

hpadd: The amount of life added to the amount of life granted by the vit column.

PercentStr: Unused (but loaded by code and repurposeable).

PercentDex: Unused (but loaded by code and repurposeable).

PercentInt: Unused (but loaded by code and repurposeable).

PercentVit: Unused (but loaded by code and repurposeable).

ManaRegen: The number of seconds that need to elapse until mana is completely regenerated, thus lower values make mana regenerate faster, higher values slow the process down.

ToHitFactor: This value is added to the basic attack rating of this character class (not that this really makes a difference later on). WARNING: Unless you alter the attack rating calculation in the games code, large negative values here will give the 
characters negative attack rating early on.

WalkVelocity: The speed of this character class when walking (used to be 7 prior to LoD).

RunVelocity: The speed of this character class when running (used to be 11 prior to LoD).

RunDrain: Rate at which this character class burns stamina when running, the lower the value the slower the loss of stamina.

Comment: I really wonder what this could be!?

LifePerLevel: Amount of life earned for each level up. This value is in fourths, thus the lowest bonus possible is 64/256 (on quarter of one on-screen point, the fractional value is used by the game however).

StaminaPerLevel: Amount of stamina earned for each level up. This value is in fourths, thus the lowest bonus possible is 64/256 (on quarter of one on-screen point, the fractional value is used by the game however).

ManaPerLevel: Amount of mana earned for each level up. This value is in fourths, thus the lowest bonus possible is 64/256 (on quarter of one on-screen point, the fractional value is used by the game however).

LifePerVitality: Amount of life earned for each point invested in vitality. This value is in fourths, thus the lowest bonus possible is 64/256 (on quarter of one on-screen point, the fractional value is used by the game however).

StaminaPerVitality: Amount of stamina earned for each point invested in vitality. This value is in fourths, thus the lowest bonus possible is 64/256 (on quarter of one on-screen point, the fractional value is used by the game however).

ManaPerMagic: Amount of mana earned for each point invested in energy. This value is in fourths, thus the lowest bonus possible is 64/256 (on quarter of one on-screen point, the fractional value is used by the game however).

StatPerLevel: Amount of stat points earned at each level up.

#walk: Reference field, contains the length of the WL animation in frames.

#run: Reference field, contains the length of the RN animation in frames.

#swing: Reference field, contains the length of the A1 animation (when wielding a melee weapon) in frames.

#spell: Reference field, contains the length of the SC animation in frames.

#gethit: Reference field, contains the length of the GH animation in frames.

#bow: Reference field, contains the length of the A1 animation (when wielding a bow) in frames.

BlockFactor: The amount of blocking that is added to the base shield blocking from Armor.txt for display and calculation purposes.

StartSkill: An ID pointer from Skills.txt, this controls what skill bonus will spawn on the characters starting weapon.

Skill 1 to Skill 10: The skills that this character class starts with (these skills will always be available from cLvl 1 onwards), obviously these are ID pointers from Skills.txt too.

StrAllSkills: This field tells the game what string to display for the bonus to all class skills (ex: +1 to all Amazon skills).

StrSkillTab1: This field tells the game what string to display for the bonus to all skills of the first skill tab (ex: +1 to all Bow and Crossbow skills).

StrSkillTab2: This field tells the game what string to display for the bonus to all skills of the second skill tab (ex: +1 to all Passive and Magic skills).

StrSkillTab3: This field tells the game what string to display for the bonus to all skills of the third skill tab (ex: +1 to all Javelin and Spear skills).

StrClassOnly: This field tells the game what string to display for class specific items (and class specific skill boni) (ex: Amazon Only).

baseWClass: What weapon class will the game default to when no weapon is equipped (by default this is 'hth', which makes the game load the DCC files associated with that animation, and thus the player appears unarmed, for example you could change this 
to '1hs' and the player will appear as if wielding an invisible 1-handed slashing weapon.

item1 to item10: This field is an ID pointer from Weapons.txt, Armor.txt and Misc.txt, it controls what item this character will start with (aka the newbie equipment). To make a character start with the horadric cube for example you would set this to '
box' (without the quotes of course).

item1loc to item10loc: The location in which the associated item will be placed, this is an ID pointer from BodyLocs.txt, to make the item appear in the inventory leave this field blank, if the item can be placed in the belt it will be created there (as 
long as there are belt slots left).

item1count to item10count: The amount of items of the associated item type to create, thus if you want to make your character start with 8 rather then 4 health potions you'd set the value to 8 rather then 4.

*/

/*
每列的含义如下：

class：职业名称。

str：每个职业的初始力量值。

dex：每个职业的初始敏捷值。

int：每个职业的初始精力值。

vit：每个职业的初始体力值。

tot：每个职业的初始属性值的总和。实际上没有用处，可以删除。

stamina：每个职业的初始耐力值。

Hpadd：每个职业的初始生命值基数。控制玩家在提升生命点数时，生命值所能获得的最大提升数值；

角色的最终初始生命值为hpadd + vit。

PercentStr：无用参数。

PercentDex：无用参数。

PercentInt：无用参数。

PercentVit：无用参数。

ManaRegen：每个职业的初始魔法值回复速度，含义为从魔法值为0到回复满需要多少秒。所以此列的值越小魔法回复速度越快。

ToHitFactor：每个职业的初始攻击准确率基数。

WalkVelocity：每个职业的初始走路速度。

RunVelocity：每个职业的初始跑步速度。

RunDrain：每个职业跑步时耐力的下降速度。数值越小表示跑步时耐力减少的越慢。

Comment：无用参数，可以删除。

LifePerLevel：每个职业升级时增加的生命值因子，除以4后为每级实际增加的生命值。

StaminaPerLevel：每个职业升级时增加的耐力值因子，除以4后为每级实际增加的耐力值。

ManaPerLevel：每个职业升级时增加的法力值因子，除以4后为每级实际增加的法力值。

LifePerVitality：每个职业每加一点体力增加的生命值因子，除以4后为每点体力实际增加的生命值。

StaminaPerVitality：每个职业每加一点体力值增加的耐力值因子，除以4后为每点体力实际增加的耐力值。

ManaPerMagic：每个职业每个一点精力增加的法力值因子，除以4后为每点精力值实际增加的法力值。

#walk：每个职业走路时的动画的长度，以帧为单位。

#run：每个职业跑步时的动画的长度，以帧为单位。

#swing：每个职业用近战武器攻击时的动画的长度，以帧为单位。

#spell：每个职业使用法术时的动画的长度，以帧为单位。

#gethit：每个职业被击中时的动画的长度，以帧为单位。

#bow：每个职业用弓攻击时的动画的长度，以帧为单位。

BlockFactor：每个职业使用盾牌时的基础格挡概率。此值会加到盾牌格挡率的显示中。

StartSkill：每个职业的初始武器上所附加的技能。与Skills.txt关联。

Skill 1-10：每个职业的基础技能，包括投掷、踢击、回城、辨识、解除召唤等。

StrAllSkills：加此职业技能的属性的显示字符串。如“+3 法师技能等级”。

StrSkillTab1-3：加此职业第1-3个技能系的属性的显示字符串。如“+3 火焰系技能”。

StrClassOnly：限此职业使用的属性的显示字符串。如“限野蛮人使用”。

baseWClass：空手时默认使用的武器类型。都默认为空手类型（这也算是一种武器类型），与WeaponClass.txt关联。

item 1-10：每个职业的第1-10个初始道具。

item 1-10 loc：每个职业的第1-10个初始道具的位置。

item 1-10 count：每个职业的第1-10个初始道具的数量。

*/

typedef struct
{
    char vitem[4]; //每个职业的第1-10个初始道具。
    unsigned char vitemloc;      //每个职业的第1-10个初始道具的位置。index，对应bodylocs.txt
    unsigned char vitemcount;    //每个职业的第1-10个初始道具的数量。
    char acPadding[2];  //填充字节，无意义
} ST_ITEM_INFO;

typedef struct
{
    char acHead[32];    //填充字节，无意义

    char vclass[16];   //职业名称。

    unsigned char vstr;          //每个职业的初始力量值。
    unsigned char vdex;          //每个职业的初始敏捷值。
    unsigned char vint;          //每个职业的初始精力值。
    unsigned char vvit;          //每个职业的初始体力值。

    //tot：每个职业的初始属性值的总和。实际上没有用处，可以删除。
    unsigned char vstamina;      //每个职业的初始耐力值。
    unsigned char vhpadd;        //每个职业的初始生命值基数。
    //角色的最终初始生命值为hpadd + vit。
    unsigned char vPercentStr;   //无用参数。
    unsigned char vPercentInt;   //无用参数。

    unsigned char vPercentDex;   //无用参数。
    unsigned char vPercentVit;   //无用参数。
    unsigned char vManaRegen;   //每个职业的初始魔法值回复速度，含义为从魔法值为0到回复满需要多少秒。所以此列的值越小魔法回复速度越快。
    unsigned char bUnknown;

    int vToHitFactor;   //每个职业的初始攻击准确率基数。

    unsigned char vWalkVelocity; //每个职业的初始走路速度。
    unsigned char vRunVelocity;  //每个职业的初始跑步速度。
    unsigned char vRunDrain;     //每个职业跑步时耐力的下降速度。数值越小表示跑步时耐力减少的越慢。
    unsigned char vLifePerLevel; //每个职业升级时增加的生命值因子，除以4后为每级实际增加的生命值。

    unsigned char vStaminaPerLevel;  //每个职业升级时增加的耐力值因子，除以4后为每级实际增加的耐力值。
    unsigned char vManaPerLevel; //每个职业升级时增加的法力值因子，除以4后为每级实际增加的法力值。
    unsigned char vLifePerVitality;  //每个职业每加一点体力增加的生命值因子，除以4后为每点体力实际增加的生命值。
    unsigned char vStaminaPerVitality;   //每个职业每加一点体力值增加的耐力值因子，除以4后为每点体力实际增加的耐力值。

    unsigned char vManaPerMagic; //每个职业每个一点精力增加的法力值因子，除以4后为每点精力值实际增加的法力值。
    unsigned char vBlockFactor;  //每个职业使用盾牌时的基础格挡概率。此值会加到盾牌格挡率的显示中。
    char acPadding[2];  //填充字节，无意义

    char vbaseWClass[4];   //空手时默认使用的武器类型。都默认为空手类型（这也算是一种武器类型），与WeaponClass.txt关联。

    unsigned char vStatPerLevel; //
    unsigned char iPadding1;
    unsigned short vStrAllSkills;

    unsigned short vStrSkillTab1;
    unsigned short vStrSkillTab2;

    unsigned short vStrSkillTab3;
    unsigned short vStrClassOnly;

    char vitem1[4]; //每个职业的第1-10个初始道具。
    unsigned char vitem1loc;      //每个职业的第1-10个初始道具的位置。index，对应bodylocs.txt
    unsigned char vitem1count;    //每个职业的第1-10个初始道具的数量。
    char acPadding3[2];  //填充字节，无意义

    char vitem2[4]; //每个职业的第1-10个初始道具。
    unsigned char vitem2loc;      //每个职业的第1-10个初始道具的位置。index，对应bodylocs.txt
    unsigned char vitem2count;    //每个职业的第1-10个初始道具的数量。
    char acPadding4[2];  //填充字节，无意义

    char vitem3[4]; //每个职业的第1-10个初始道具。
    unsigned char vitem3loc;      //每个职业的第1-10个初始道具的位置。index，对应bodylocs.txt
    unsigned char vitem3count;    //每个职业的第1-10个初始道具的数量。
    char acPadding5[2];  //填充字节，无意义

    char vitem4[4]; //每个职业的第1-10个初始道具。
    unsigned char vitem4loc;      //每个职业的第1-10个初始道具的位置。index，对应bodylocs.txt
    unsigned char vitem4count;    //每个职业的第1-10个初始道具的数量。
    char acPadding6[2];  //填充字节，无意义

    char vitem5[4]; //每个职业的第1-10个初始道具。
    unsigned char vitem5loc;      //每个职业的第1-10个初始道具的位置。index，对应bodylocs.txt
    unsigned char vitem5count;    //每个职业的第1-10个初始道具的数量。
    char acPadding7[2];  //填充字节，无意义

    char vitem6[4]; //每个职业的第1-10个初始道具。
    unsigned char vitem6loc;      //每个职业的第1-10个初始道具的位置。index，对应bodylocs.txt
    unsigned char vitem6count;    //每个职业的第1-10个初始道具的数量。
    char acPadding8[2];  //填充字节，无意义

    char vitem7[4]; //每个职业的第1-10个初始道具。
    unsigned char vitem7loc;      //每个职业的第1-10个初始道具的位置。index，对应bodylocs.txt
    unsigned char vitem7count;    //每个职业的第1-10个初始道具的数量。
    char acPadding9[2];  //填充字节，无意义

    char vitem8[4]; //每个职业的第1-10个初始道具。
    unsigned char vitem8loc;      //每个职业的第1-10个初始道具的位置。index，对应bodylocs.txt
    unsigned char vitem8count;    //每个职业的第1-10个初始道具的数量。
    char acPadding10[2];  //填充字节，无意义

    char vitem9[4]; //每个职业的第1-10个初始道具。
    unsigned char vitem9loc;      //每个职业的第1-10个初始道具的位置。index，对应bodylocs.txt
    unsigned char vitem9count;    //每个职业的第1-10个初始道具的数量。
    char acPadding11[2];  //填充字节，无意义

    char vitem10[4]; //每个职业的第1-10个初始道具。
    unsigned char vitem10loc;      //每个职业的第1-10个初始道具的位置。index，对应bodylocs.txt
    unsigned char vitem10count;    //每个职业的第1-10个初始道具的数量。
    char acPadding12[2];  //填充字节，无意义

    unsigned short vStartSkill;  //每个职业的初始武器上所附加的技能。与Skills.txt关联。index FF无效，对应skills.txt
    unsigned short vSkillmysp1;  //每个职业的基础技能，包括投掷、踢击、回城、辨识、解除召唤等。index FF无效，对应skills.txt
    unsigned short vSkillmysp2;
    unsigned short vSkillmysp3;
    unsigned short vSkillmysp4;
    unsigned short vSkillmysp5;
    unsigned short vSkillmysp6;
    unsigned short vSkillmysp7;
    unsigned short vSkillmysp8;
    unsigned short vSkillmysp9;
    unsigned short vSkillmysp10;

    char acTail[2];     //填充字节，无意义
} ST_LINE_INFO;

static char *m_apcNotUsed[] =
{
    "tot",
    "Comment",
    "#walk",
    "#run",
    "#swing",
    "#spell",
    "#gethit",
    "#bow",
    NULL,
};

static char *CharStats_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strncpy(pcKey, pstLineInfo->vclass, sizeof(pstLineInfo->vclass));
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

static int CharStats_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    int id;
    char *pcResult;
    int result = 0;

    if ( strstr(acKey, "loc") && 1 == sscanf(acKey, "item%dloc", &id) )
    {
        ST_ITEM_INFO *pstItemInfo = (ST_ITEM_INFO *)pstLineInfo->vitem1;
        pcResult = BodyLocs_GetLocStr(pstItemInfo[id - 1].vitemloc);
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
    else if ( !strcmp(acKey, "StartSkill") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vStartSkill);
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
    else if ( 1 == sscanf(acKey, "Skill %d", &id) )
    {
        unsigned short *psSkill = (short *)&pstLineInfo->vSkillmysp1;
        pcResult = Skills_GetSkillName(psSkill[id-1]);
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
    else if ( !strcmp(acKey, "StrAllSkills") )
    {
        pcResult = String_FindString(pstLineInfo->vStrAllSkills, NULL);
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
    else if ( !strcmp(acKey, "StrSkillTab1") )
    {
        pcResult = String_FindString(pstLineInfo->vStrSkillTab1, NULL);
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
    else if ( !strcmp(acKey, "StrSkillTab2") )
    {
        pcResult = String_FindString(pstLineInfo->vStrSkillTab2, NULL);
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
    else if ( !strcmp(acKey, "StrSkillTab3") )
    {
        pcResult = String_FindString(pstLineInfo->vStrSkillTab3, NULL);
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
    else if ( !strcmp(acKey, "StrClassOnly") )
    {
        pcResult = String_FindString(pstLineInfo->vStrClassOnly, NULL);
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

int process_charstats(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, class, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, str, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dex, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, int, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, vit, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stamina, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, hpadd, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PercentStr, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PercentInt, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PercentDex, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PercentVit, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ManaRegen, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ToHitFactor, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, WalkVelocity, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, RunVelocity, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, RunDrain, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LifePerLevel, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StaminaPerLevel, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ManaPerLevel, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LifePerVitality, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StaminaPerVitality, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ManaPerMagic, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BlockFactor, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, baseWClass, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StatPerLevel, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StrAllSkills, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StrSkillTab1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StrSkillTab2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StrSkillTab3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StrClassOnly, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item1, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item1loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item1count, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item2, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item2loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item2count, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item3, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item3loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item3count, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item4, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item4loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item4count, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item5, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item5loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item5count, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item6, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item6loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item6count, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item7, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item7loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item7count, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item8, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item8loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item8count, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item9, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item9loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item9count, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item10, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item10loc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, item10count, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StartSkill, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skillmysp1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skillmysp2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skillmysp3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skillmysp4, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skillmysp5, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skillmysp6, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skillmysp7, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skillmysp8, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skillmysp9, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skillmysp10, USHORT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(bodylocs, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(string, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(skills, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnGetKey = CharStats_GetKey;
            m_stCallback.pfnConvertValue = CharStats_ConvertValue;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

