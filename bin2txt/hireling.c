#include "global.h"

#define FILE_PREFIX "hireling"

/*
Title 	Hireling.txt File Guide
Description 	by Draco & Ric Faith
Sent by 	
OVERVIEW:

This file handles everything related to hirelings. In here you set what hirelings that is avaible to hire, what items they are able to use, their stats and what skills they are using.

RELATED .TXT FILES:

This file is using:

    ItemTypes.txt
    Skills.txt



COLUMN DESCRIPTIONS :

Hireling 	Description of hireling type, this column has no function, it only serves as a comment field to make it easier.
SubType 	Description of hireling sub-type, this column has no function, it only serves as a comment field to make it easier.
Version 	Classic = 0, Expansion = 100
Id 	ID number to segregate the hirelings and threshold lvls.
Class 	reference to column 'hcIdx' in monstats.txt for monster class.
Act 	Act where merc can be hired.
Difficulty 	Normal = 1, NM = 2, Hell = 3
Level 	rmlvl of the hireling (what level is required to 'upgrade' skills/stats)
Seller 	reference to column 'hcIdx' in monstats.txt for NPC.
NameFirst, NameLast 	Range from which the game looks to get random names for the hirelings.
Gold 	Cost of hireling, compounded by mlvl
Exp/Lvl 	Factor used in the calculation of Exp required between mlvls. The threshold for the next level (L+1) from the current level (L) is (exp/lvl)*L*L*(L+1).
HP 	Life at Base Lvl.
HP/Lvl 	Amount of additional Life given at Lvl up.
Defence 	DR (Defence Rating) at Base Lvl.
Def/Lvl 	Amount of additional DR given at Lvl up.
Str 	Strength at Base Lvl.
Str/Lvl 	Amount (in 8ths) of additional Strength given at Lvl up.
Dex 	Dexterity at Base Lvl.
Dex/Lvl 	Amount (in 8ths) of additional Dexterity given at Lvl up.
AR 	Attack Rating at Base Lvl.
AR/Lvl 	Amount of additional AR given at Lvl up.
Share 	Used to co-relate between threshold lvls between Normal, NM, Hell Hirelings.
Dmg-Min, Dmg-Max 	Range of Damage dealt at Base lvl.
Dmg-Lvl 	Amount (in 8ths) of additional Damage given at Lvl up.
Resist 	All Resistance at Base Lvl.
Resist/Lvl 	Amount (in 8ths) of additional All Resist given at lvl up.
WType1, WType2 	Can't be changed, is the itemtype of the items that can be carried in weapon slots.
HireDesc 	A reference for .tbl files.
Default Chance 	The Chance that Hireling will use weapon and normal attack instead skill.
Skill (1-6) 	Reference to Skill column in skills.txt.
Mode (1-6) 	The Mode to use for the skill:
Generally-
1 -> Auras
4 -> Attack
5 -> Attack (use for Barbs, works the same way as Mode=4)
7 -> Cast
14-> Seq (use for Jab)
Chance (1-6) 	The Chance that hireling will use Skill at Base Lvl:
It is calculated by probability: Using the example for Normal Fire Rogue, 1st Threshold,
Default Chance = 75, Inner Sight = 10, Fire Arrow = 25
So by probability (Chance/TotChance *100%):
Default (Attack) = 75/110 *100% = 68.18%
Inner Sight = 10/110 *100% = 9.09%
Fire Arrow = 25/110 *100% = 22.73%
To move along to the 2nd Threshold:
Default Chance = 75, Inner Sight = 10, Fire Arrow = 69
So: Default (Attack) = 48.70%, Inner Sight = 6.49%, Fire Arrow = 44.81%
So you can see, when you go from one threshold to the next, the values may change depending on your Chance set. Ideally you should push your intended favourite higher so it will occur more often.
ChancePerLevel (1-6) 	Amount of additional Chance given at lvl up, used to improve the chances of certain skills as during leveling .
Level (1-6) 	The sLvl of the Skill at Base lvl.
LvlPerLvl (1-6) 	Factor in improving slvl at lvl up (0=no increment).
Head, Torso, Weapon, Shield 	References to the anims for monster parts. 

*/

/*
文件名解析：
Hireling：雇佣兵。
所以此文件就是描述所有雇佣兵的信息。
此文件中的每一行表示一条雇佣兵信息。

每列的含义如下：

Hireling：佣兵的名称，仅作为注释。

SubType：佣兵的类型，仅作为注释。

Version：佣兵出现的版本，0为非资料片，100为资料片。

Id：佣兵的编号，不同名称或相同名称不同类型的佣兵编号不可相同。

Class：佣兵的怪物类型，与MonStats.txt关联。

Act：此佣兵的雇佣地点。

Difficulty：雇佣此佣兵的难度级别。1代表普通，2代表恶梦，3代表地狱。

Level：佣兵的进阶级别。每当佣兵到达某一进阶级别时，都会根据此行后面所写的参数改变佣兵的成长，此种改变一般表现为成长增加，即每升一级所提升的属性增加，所以我将其称之为进阶级别。

Seller：佣兵的主人的编号，或者说是佣兵的出售者。与Monstats.txt关联。

NameFirst：字符串编号，与佣兵名字相关，后面具体说明。

NameLast：字符串编号，与佣兵名字相关，后面具体说明。

佣兵的名字是从游戏内部的名字列表中随机选取的，此列表中每个名字都有一个编号。而此佣兵名字的字符串编号必须处于NameFirst和NameLast之间，含边界。

Gold：佣兵的价格基数。注意：这个价格根据佣兵的魔法级别而不同

Exp/Lvl：佣兵每升一级所需要的经验值基数。

HP：佣兵在初始级别的生命值。

Hp/Lvl：每升一级所增加的生命值，无衰减因子，即此列的值是多少则每升一级加多少生命。

Defense：佣兵在进阶级别时的基础防御值。佣兵在不穿装备情况下的防御值为基础防御值 + 敏捷/4。

Def/Lvl：每升一级所增加的基础防御值，无衰减因子，即此列的值是多少则每升一级加多少防御。

Str：佣兵在进阶级别时的力量。

Str/Lvl：每升一级所增加的力量，衰减因子为8，即若此列的值是8，则每升一级加8/8=1点力量。

Dex：佣兵在进阶级别时的敏捷。

Dex/Lvl：每升一级所增加的敏捷，衰减因子为8，即若此列的值是8，则每升一级加8/8=1点敏捷。

AR：佣兵在进阶级别时的基础攻击准确率。

AR/Lvl：每升一级所增加的基础攻击准确率。无衰减因子。

Share：不知道什么意思的参数，大概描述了佣兵的阶位。

Dmg-Min：佣兵在进阶级别时的基础最小伤害值。佣兵在不穿装备情况下的最小伤害值为：基础最小伤害值 * (1 + 力量/100)。

Dmg-Max：佣兵在进阶级别时的基础最大伤害值。佣兵在不穿装备情况下的最大伤害值为：基础最在伤害值 * (1 + 力量/100)。

Dmg/Lvl：每升一级所增加的基础伤害值，衰减因子为8，最小伤害值与最大伤害值共享此参数。

Resist：佣兵在进阶级别时的抗性。

Resist/Lvl：每升一级所增加的抗性，衰减因子为4。

WType1：可使用的第一种武器（盾牌）类型。

WType2：可使用的第二种武器（盾牌）类型。

HireDesc：在购买佣兵时显示的佣兵说明（和相关的*.tbl文件关联）。

Default Chance：佣兵使用普通攻击的频率。

Skill1：佣兵的第1个技能。

Mode1：佣兵第1个技能的MOD（使用方式）。
佣兵技能的模式: 
一般情况下：
1 -> 光、电动作，
4 -> 攻击动机，
5 -> 攻击动机(主要对于野蛮人佣兵，和Mode=4类似)， 
7 -> 投掷，
14-> Jab技能专用；

Chance1：佣兵使用第1个技能的频率。

ChancePerLevel1：每升一级所增加的使用第1个技能频率。

Level：佣兵在进阶级别时的第1个技能的技能等级。

LvlPerLvl1：每升一级所拉增加的第1个技能的技能等级，衰减因子为32。

以下Skill2、Mode2、……、LvlPerLvl6是对佣兵可能拥有的第2到6个技能的描述，含义参考第1个技能的解释。

Head：无用参数，删之也可。

Torso：无用参数，删之也可。

Weapon：无用参数，删之也可。

Shield：无用参数，删之也可。

*eol：行尾标志，必须为0。

特殊说明1：如果某一种佣兵在此文件中对应了不止一行对其进行描述，那么一定是有不同进阶级别的原因。

特殊说明2：有多个进阶级别的佣兵在雇佣菜单里只能显示按照最低阶的成长计算出来的状态，但当你雇佣后，如果其等级达到了2阶或更高阶的级别，那么其属性会自动增长至符合其所在阶位的成长情况。所以就可能会出现在雇佣菜单里显示此佣兵只有1000血，但你雇佣后发现有1500
血的情况。

*/

typedef struct
{
    unsigned int vVersion;
    unsigned int vId;
    unsigned int vClass;
    unsigned int vAct;
    unsigned int vDifficulty;
    unsigned int vSeller;
    unsigned int vGold;
    unsigned int vLevel;
    unsigned int vExpmyslashLvl;
    unsigned int vHP;

    unsigned int vHPmyslashLvl;
    unsigned int vDefense;
    unsigned int vDefmyslashLvl;
    unsigned int vStr;
    unsigned int vStrmyslashLvl;
    unsigned int vDex;
    unsigned int vDexmyslashLvl;
    unsigned int vAR;
    unsigned int vARmyslashLvl;
    unsigned int vShare;

    unsigned int vDmgmysubMin;
    unsigned int vDmgmysubMax;
    unsigned int vDmgmyslashLvl;
    unsigned int vResist;
    unsigned int vResistmyslashLvl;
    unsigned int vDefaultChance;

    unsigned int vHead;
    unsigned int vTorso;
    unsigned int vWeapon;
    unsigned int vShield;

    unsigned int vSkill1;   //skills
    unsigned int vSkill2;
    unsigned int vSkill3;
    unsigned int vSkill4;
    unsigned int vSkill5;
    unsigned int vSkill6;

    unsigned int vChance1;
    unsigned int vChance2;
    unsigned int vChance3;
    unsigned int vChance4;
    unsigned int vChance5;
    unsigned int vChance6;

    unsigned int vChancePerLvl1;
    unsigned int vChancePerLvl2;
    unsigned int vChancePerLvl3;
    unsigned int vChancePerLvl4;
    unsigned int vChancePerLvl5;
    unsigned int vChancePerLvl6;

    unsigned char vMode1;
    unsigned char vMode2;
    unsigned char vMode3;
    unsigned char vMode4;

    unsigned char vMode5;
    unsigned char vMode6;
    unsigned char vLevel1;
    unsigned char vLevel2;

    unsigned char vLevel3;
    unsigned char vLevel4;
    unsigned char vLevel5;
    unsigned char vLevel6;

    unsigned char vLvlPerLvl1;
    unsigned char vLvlPerLvl2;
    unsigned char vLvlPerLvl3;
    unsigned char vLvlPerLvl4;

    unsigned char vLvlPerLvl5;
    unsigned char vLvlPerLvl6;
    unsigned char vHireDesc; //hiredesc
    unsigned char vNameFirst[32];

    unsigned char vNameLast[37];
} ST_LINE_INFO;


static char *m_apcNotUsed[] =
{
    "Hireling",
    "SubType",
    "WType1",
    "WType2",
    NULL,
};

static int Hireling_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int id;
    int result = 0;

    if ( strlen("Skill1") == strlen(acKey) && 1 == sscanf(acKey, "Skill%d", &id) )
    {
        unsigned int *psSkill = &pstLineInfo->vSkill1;

        pcResult = Skills_GetSkillName(psSkill[id - 1]);
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
    else if ( !strcmp(acKey, "HireDesc") )
    {
        pcResult = HireDesc_GetDesc(pstLineInfo->vHireDesc);
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

int process_hireling(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Version, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Id, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Class, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Act, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Difficulty, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Seller, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Gold, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Level, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ExpmyslashLvl, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HP, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HPmyslashLvl, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Defense, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DefmyslashLvl, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Str, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StrmyslashLvl, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Dex, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DexmyslashLvl, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AR, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ARmyslashLvl, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Share, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DmgmysubMin, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DmgmysubMax, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DmgmyslashLvl, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Resist, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ResistmyslashLvl, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DefaultChance, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Head, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Torso, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Weapon, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Shield, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill1, UINT);   //skills
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill6, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Chance1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Chance2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Chance3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Chance4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Chance5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Chance6, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ChancePerLvl1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ChancePerLvl2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ChancePerLvl3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ChancePerLvl4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ChancePerLvl5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ChancePerLvl6, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode3, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode4, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Level1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Level2, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Level3, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Level4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Level5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Level6, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LvlPerLvl1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LvlPerLvl2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LvlPerLvl3, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LvlPerLvl4, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LvlPerLvl5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LvlPerLvl6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HireDesc, UCHAR); //hiredesc
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, NameFirst, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, NameLast, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(skills, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(hiredesc, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = Hireling_ConvertValue;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

