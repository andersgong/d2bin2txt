#include "global.h"

#define FILE_PREFIX "DifficultyLevels"
#define NAME_PREFIX "dl"

/*
Title 	Difficultylevels.txt File Guide
Description 	by Nefarius, Joel Falcou, Jarulf & Foxbat
Sent by 	

OVERVIEW :

This file is used for setting some global game parameters that depend on the difficulty levels of the game.

RELATED .TXT FILES :

This file has no link with any other .txt, this is just a simple table of parameters.

COLUMN DESCRIPTIONS :
Name
	Difficulty name. Don't even think to add one.
 
ResistPenalty
	The value removed from the player resistances within this difficulty.
 
DeathExpPenalty
	The percentage of experience you loose at death on this difficulty.
 
UberCodeOddsNormal
	

Not used.

Pre 1.07 this was the percentage of low quality / normal / superior exceptional items dropped on this specific difficulty.
 
UberCodeOddsGood
	

Not used.

Pre 1.07 this was the percentage of magic / rare / set / unique exceptional items dropped on this specific difficulty.
 
UltraCodeOddsNormal
UltraCodeOddsGood
 
	

Not used, and didn't exist pre 1.07.
 
MonsterSkillBonus
	Additional skill points added to monster skills specified in MonStats.txt for this difficulty. It has nothing to do with missile damage bonus.
 
MonsterFreezeDivisor
MonsterColdDivisor
 
	

Divisor values applyed to monsters for their Freezing Length and Cold Length duration for this difficulty.

Don't set this value to zero.
 
AiCurseDivisor
LifeStealDivisor
ManaStealDivisor
 
	Divisor values for AI altering states (Dim Vision, Terror etc), and not other curses, Life Leech and Mana Leech for this difficulty.

Don't set this value to zero if you're modding versions older then v1.10, in v1.10 a value of zero will disable the nerf completely.
 
UniqueDamageBonus
ChampionDamageBonus
 
	Effective percentage of damage and attack rating added to Extra Strong Unique/Minion and Champion monsters.
The bonus equals BonusFromMonUMod/100*ThisField
 
HireableBossDamagePercent  
	This is a percentage of how much damage your Mercenaries do to an Act Boss.

In Hell, since the value is 25, they're doing only 1/4 of their normal damage against a Boss.
 
MonsterCEDamagePercent
	Monster Corpse Explosion damages percent limit.

Monsters HP increase with number of players in the game, and therefore the Corpse Explosion damages increase as well, but these damages are limited per difficulty as what this column indicates.
 
StaticFieldMin
	Minimum percentage of Hit Points left on monsters hit by Static Field.

Setting this column for the 3 Difficulties to 0 will make Static Field work the same way it did in Classic Diablo II.
 
GambleRare
GambleSet
GambleUnique
GambleUber
GambleUltra
 
	Parameters in hardcoded functions that are used when gambling Rare, Set, Unique, Exceptional and Elite items in this Difficulty.

See that link for knowing how the columns works.
 */

/*
文件名解析：
Difficulty Levels：难度级别，即游戏中的普通、恶梦、地狱三个难度。
所以此文件就是描述游戏中三个难度中的一些特殊信息，如抗性惩罚。
此文件中的每一行表示一个难度，其实总共也就3行。

Name：难度的名称。

ResistPenalty：在此难度下的抗性惩罚。

DeathExpPenalty：在此难度下死亡损失的经验值。

UberCodeOddsNormal：无用参数。

UberCodeOddsGood：无用参数。

UltraCodeOddsNormal：无用参数。

UltraCodeOddsGood：无用参数。

MonsterSkillBonus：在此难度下怪物的技能等级提升。
每种难度下针对怪物额外附加的技能点数，对应MonStats.txt中对怪物技能的描述；不过对于“弓”系魔法无效。

MonsterFreezeDivisor：在此难度下怪物的冻结状态持续时间的衰减因子。
每中难度下怪物冰冻魔法的除数（既然是除数，就不能为0）。 

MonsterColdDivisor：在此难度下怪物的冰冻状态持续时间的衰减因子。

AiCurseDivisor：在此难度下怪物的被诅咒状态持续时间的衰减因子。

LifeStealDivisor：在此难度下击中怪物后的偷取生命数值的衰减因子。
每种难度下怪物“诅咒”、“偷血”、“偷魔法”技能的除数，同样不能为0。

ManaStealDivisor：在此难度下击中怪物后的偷取法力数值的衰减因子。

UniqueDamageBonus：在此难度下金怪伤害的额外提升百分比。

ChampionDamageBonus：在此难度下头目怪伤害的额外提升百分比。

HireableBossDamagePercent：在此难度下雇佣兵对BOSS伤害的衰减百分比。
针对每一关中的BOSS级别怪物，你的佣兵所做的损伤百分比；比如：在“地狱”难度下的数值为25，意思就是对于BOSS级别的怪物只做1/4的伤害。

MonsterCEDamagePercent：在此难度下怪物暴尸伤害的衰减百分比。
怪物“暴尸"技能的百分比限制；说明一下，通常的“暴尸”伤害率都是根据游戏中角色的数量决定的，这列数值的意思就是限制过大的暴尸”伤害率。 

StaticFieldMin：在此难度下静态力场技能的杀伤能力。如地狱难度此列为50，也就是说当怪物所剩的生命大于50%时，静态力场都有效。0代表使用默认值。
静态攻击对于怪物的最小伤害值；如果三种难度下均设定为0的话，就以非资料片的默认值为准。

GambleRare：赌博出稀有（亮金）物品的频率。

GambleSet：赌博出套装（绿色）物品的频率。

GambleUnique：赌博出唯一（暗金）物品的频率。

GambleUber：无用参数。

GambleUltra：无用参数。

*eol：行尾标志，必须为0。

关于GambleUber和GambleUltra两列的说明有误，现修改如下：

GambleUber：赌博出扩展级物品的概率。 1 + (ilvl - excep qlvl) * GambleUber / 100

GambleUltra：赌博出精英级物品的概率。1 + (ilvl - elite qlvl) * GambleUltra / 100

另外做补充说明，赌博成色判断的顺序及相应概率如下：
蓝色 = 100 - ((GambleRare + GambleSet + GambleUnique) / 1000)
暗金 = (GambleRare - GambleSet - GambleUnique) / 1000
绿色 = (GambleSet + GambleUnique) / 1000
亮金 = (GambleUnique) / 1000
*/

typedef struct
{
    int vResistPenalty;
    unsigned int vDeathExpPenalty;
    unsigned int vUberCodeOddsNormal;
    unsigned int vUberCodeOddsGood;

    unsigned int vMonsterSkillBonus;
    unsigned int vMonsterFreezeDivisor;
    unsigned int vMonsterColdDivisor;
    unsigned int vAiCurseDivisor;
    unsigned int vUltraCodeOddsNormal;
    unsigned int vUltraCodeOddsGood;

    unsigned int vLifeStealDivisor;
    unsigned int vManaStealDivisor;
    unsigned int vUniqueDamageBonus;
    unsigned int vChampionDamageBonus;
    unsigned int vHireableBossDamagePercent;
    unsigned int vMonsterCEDamagePercent;

    unsigned int vStaticFieldMin;
    unsigned int vGambleRare;
    unsigned int vGambleSet;
    unsigned int vGambleUnique;

    unsigned int vGambleUber;
    unsigned int vGambleUltra;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "Name",
    NULL,
};

static int DifficultyLevels_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "Name") )
    {
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, iLineNo);
        }
        return 1;
    }

    return 0;
}

int process_difficultylevels(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ResistPenalty, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DeathExpPenalty, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, UberCodeOddsNormal, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, UberCodeOddsGood, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MonsterSkillBonus, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MonsterFreezeDivisor, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MonsterColdDivisor, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AiCurseDivisor, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, UltraCodeOddsNormal, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, UltraCodeOddsGood, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LifeStealDivisor, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ManaStealDivisor, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, UniqueDamageBonus, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ChampionDamageBonus, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HireableBossDamagePercent, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MonsterCEDamagePercent, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StaticFieldMin, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, GambleRare, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, GambleSet, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, GambleUnique, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, GambleUber, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, GambleUltra, UINT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            File_CopyFile(acTemplatePath, acTxtPath, "cubemod", ".txt");
            File_CopyFile(acTemplatePath, acTxtPath, "cubetype", ".txt");

            m_stCallback.pfnFieldProc = DifficultyLevels_FieldProc;
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

