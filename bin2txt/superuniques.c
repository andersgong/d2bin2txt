#include "global.h"

#define FILE_PREFIX "superuniques"
#define NAME_PREFIX "su"

/*
Title 	SuperUniques.txt File Guide
Description 	by 54x & Red Havoc
Sent by 	

OVERVIEW :

This file is used to define Superunique monsters and their properties. Superunique monsters are boss monsters which always appear at the same places and which always have the same special abilities (e.g. Corpsefire, Pindleskin).

RELATED .TXT FILES :
	

This file is using:

    Monsounds.txt
    Monstats.txt
    Monumod.txt
    TreasureclassEx.txt

	

This file is used by :

    MonPreset.txt

COLUMN DESCRIPTIONS :
Superunique 	The ID of the SuperUnique Monster.

Each SuperUnique Monster must be use a different ID.

Its the string to use into another .txt, like the column Place of MonPreset.txt.
Name 	The string key for this superunique which must be present in a .TBL file.

If this key is not found into any .TBL, then the SuperUnique Monster will have the infamous name "An Evil Force".
Class 	This column defines what monster type the SuperUnique will be. The codes are taken from the column Id in Monstats.txt.
hcIdx 	Hardcoded Index.

Original SuperUniques in the game (with hcIdx from 0 to 65) have some hardcoded stuff, and this column tells what to do with that SuperUnique.

If you create a new SuperUnique, you can add him some hardcoded stuff by using a hcIdx from 0 to 65. For instance, if you create a new SuperUnique with a hcIdx of 42 (line of Shenk the Overseer), then whatever the Class this monster will be (even if it 
is NOT an Overseer), 20 Enslaved (Shenk minions) will spawn around him.

If you prefer instead to have a more "normal" SuperUnique, use a hcIdx that is not originally used by the game, like 66 : since the game don't expect this index to exists, it have nothing hardcoded to it, therefore it won't do anything special to your 
new SuperUnique.
MonSound 	This column force a particular Superunique to use a special set of sounds for attacks, taunts, death... The Countess, for example, already uses this feature.

Taken from the column Id in MonSound.
Mod1
Mod2
Mod3 	These 3 columns assign special abilities to SuperUnique monsters such as "Fire Enchanted" or "Stone Skin". The parameters are the Id values of the corresponding property in Monumod.txt.

The following modifiers are available:

0 	None
1 	Inits the random name seed, automatically added to monster, you don't need to add this UMod.
2 	Increases the hitpoints, Automatically added to monster, you don't need to add this UMod.
3 	Increases the light radius. and picks a random color for it (bugged in v1.10+)
4 	Increases the monster level resulting in higher damage.
5 	Extra Strong : increases physical damage done by boss.
6 	Extra Fast : faster walk / run and attack speed.
7 	Cursed : randomly cast Amplify Damage when hitting
8 	Magic Resist : +50% resistance against Elemental attacks (Fire, Cold, Lightning and Poison)
9 	Fire Enchanted : additional fire damage and +50% fire resistance.
10 	When killed, release a poisonous cloud, like the Mummies in Act 2.
11 	Corpse will spawn little white maggots (like Duriel).
12 	Works for Bloodraven only, and seems to have something to do with her Death sequence.
13 	Ignore your Armor Class and nearly always hit you.
14 	
15 	When killed, all his minions die immediately as well.
16 	Adds base champion modifiers (champions only)
17 	Lightning Enchanted : additional lightning damage, +50% lightning resistance, and release Charged Bolts when hit.
18 	Cold Enchanted : additional cold damage, +50% cold resistance, and release Frost Nova upon death
19 	Assigns extra damage to hireling attacks, relic from pre-lod, causes bugged damage.
20 	Release Charged Bolts when hit, like the Scarabs in act 2.
21 	Code present, but seams to have no effect.
22 	Has to do with quests, but is non-functional for Superuniques which arent in relation to a quest.
23 	Have a poison aura that poison you when you're approaching him, adds poison damage to attack.
24 	Code present, but untested in v1.10+, does something else now.
25 	Mana Burn : steals mana from you and heals himself when hitting. Adds magic resistance.
26 	TeleHeal : randomly warps around when attacked and heals itself.
27 	Spectral Hit : deals random elemental damage when hitting
28 	Stone Skin : +80% physical damage resistance, increases defense
29 	Multiple Shots : Ranged attackers shoots several missiles at once.
30 	Random aura.
31 	Explode in a Corpse Explosion when killed.
32 	Explode with a fiery flash when killed (graphical effect only)
33 	Explode and freeze you when killed (like suicide minions). Note: hitpoints of boss are heavily reduced.
34 	Self-resurrect effect for Reanimate Horde, bugged on other units.
35 	Shatter into Ice pieces when killed, no corpse remains.
36 	Adds physical resistance and reduces movement speed(used for Champions only)
37 	Alters champion stats (used for Champions only)
38 	Champion cannot be cursed (used for Champions only)
39 	Alters champion stats (used for Champions only)
40 	Release a painworm when killed, but display is very buggy.
41 	Code present, but has no effect in-game, probably due to bugs
42 	Release a Nova when killed, but display is bugged.
MinGrp
MaxGrp 	These two columns control the Minimum and Maximum number of minions which will accompany the SuperUnique boss.

If both values differ from each other, the game will randomly choose a number within the defined range.
EClass 	

Expansion Class

    0 = D2 Classic monster
    1 = D2 Expansion monster

AutoPos 	

Ask the Monster to place himself within a radius from his original position (defined in the map), or not.

    0 = random position, into a large radius
    1 = spawn exacly as where expected

Stacks 	 

Whenever or not this superunique can spawn more then once in the same game (a la nolimit in uniqueitems.txt). If it can, the value should be 1, if it cant the value is 0.
Updated by Nefarius
Replaceable 	Unknown.
TC
TC(N)
TC(H) 	

Treasure Classes for the 3 Difficulties.

These columns list the treasureclass that is valid if this boss is killed and drops something.

Taken from the column Treasure Class in TreasureClassEx.txt (for D2 Classic, it's TreasureClass.txt).

    TC = Normal difficulty
    TC = Nightmare difficulty
    TC = Hell difficulty

*eol 	End Of Line.

Do not remove this column ! Its purpose is to ensure the last column of the tabulated text files are always filled.

*/

/*
文件名解析：
Super：超级。
Uniques：唯一。
本文件描述的是所有固定（超级）金怪的资料。
此文件中的每一行表示一个固定金怪。


回复

    2楼
    2011-09-06 20:51

    举报 |

    zqtjingzi
    小吧主
    12

Superunique：怪物的名字索引。这里的名称用在TCEx等文件里

Name：怪物的英文名字，也是tbl文件中的键名。

Class：怪物种类，也就是金怪的本体小怪是什么。与Monstats.txt相关联。

hcldx：怪物的数字索引。暗金怪的ID号，在添加新怪物时也用于DS1文件（的读取）；

MonSound：怪物所发出的声音。这写上你希望怪物使用的声音就行了，不用去改DLL了

Mod1-3：此固定金怪身上固定的增加属性，与MonUMod.txt关联。如毕须博须有两个固化属性，8（魔法抵抗）和9（火焰强化）。

MinGrp/MaxGrp：这两列描述此固定金怪身边会额外增加几个小怪。0的话表示周围没有小怪，若为此两列的值都为n，那么身边小怪数为n+m-1。其中m由MonStats.txt中MinGrp/MaxGrp决定。

EClass：是否是资料片新加的怪物种类。

AutoPos：是否由程序自动指定怪物位置。0代表有固定位置，1的话则有一定的随机性。

Stacks：是否记录首杀。0代表不记录，则每次杀死都等同于首杀，1则代表记录首杀，即之后都没有首杀效果。（不能确定）

Replaceable：不知道这一列是什么意思。

Utrans/Utrans(N)/Utrans(H)：此暗金怪在三个难度下的颜色变化。

TC/TC(N)/TC(H)：此暗金怪在三个难度下的物品掉落类别。TC的含义可参考物品掉落原理。

Eol：行尾标志，必须为0。

补充：景圣临

Superuniques.txt中的Mod1~3列中的内容与Monumod.txt中的uniquemod列中的内容对应（可供选择），Mod1~3是指定暗金怪的固有奖励属性。
*/

typedef struct
{
    unsigned short wHcIdx;
    unsigned short vName;   //strings

    unsigned int vClass;    //monstats

    unsigned int vhcIdx;

    unsigned int vMod1;
    unsigned int vMod2;
    unsigned int vMod3;

    unsigned int vMonSound; //sounds

    unsigned int vMinGrp;
    unsigned int vMaxGrp;

    unsigned char vAutoPos;
    unsigned char vEClass;
    unsigned char vStacks;
    unsigned char vReplaceable;

    unsigned char vUtrans;
    unsigned char vUtransmybr1Nmybr2;
    unsigned char vUtransmybr1Hmybr2;
    unsigned char iPadding10;

    unsigned short vTC;             //TreasureClassEx
    unsigned short vTCmybr1Nmybr2;  //TreasureClassEx

    unsigned short vTCmybr1Hmybr2;  //TreasureClassEx
    unsigned short iPadding12;
} ST_LINE_INFO;

typedef struct
{
    unsigned char vSuperunique[32];
} ST_SUPER_UNIQUES;

static char *m_apcInternalProcess[] =
{
    "Superunique",
    "*eol",
    NULL,
};

static unsigned int m_iSuperUniquesCount = 0;
static ST_SUPER_UNIQUES *m_astSuperUniques = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astSuperUniques, ST_SUPER_UNIQUES);

char *SuperUniques_GetItemUniqueCode(unsigned int id)
{
    if ( id < m_iSuperUniquesCount )
    {
        return m_astSuperUniques[id].vSuperunique;
    }

    return NULL;
}

static int SuperUniques_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
#ifdef USE_NAME_TOBE_ID
    char *pcResult = NULL;
#endif
    int result = 0;

    if ( !strcmp("Superunique", acKey) )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
#ifdef USE_NAME_TOBE_ID
            pcResult = String_FindString(pstLineInfo->vName, "dummy");

            if ( pcResult )
            {
                strcpy(acOutput, pcResult);
            }
            else
#endif
            {
                sprintf(acOutput, "%s%u", NAME_PREFIX, iLineNo);
            }
        }

        result = 1;
    }
    else if ( !strcmp(acKey, "*eol") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return result;
}

static int SuperUniques_ConvertValue_Pre(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
#ifdef USE_NAME_TOBE_ID
    char *pcResult = NULL;
#endif
    int result = 0;

    if ( !strcmp(acKey, "Name") )
    {
#ifdef USE_NAME_TOBE_ID
        pcResult = String_FindString(pstLineInfo->vName, "dummy");

        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
#endif
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, m_iSuperUniquesCount);
        }

        strncpy(m_astSuperUniques[m_iSuperUniquesCount].vSuperunique, acOutput, sizeof(m_astSuperUniques[m_iSuperUniquesCount].vSuperunique));
        String_Trim(m_astSuperUniques[m_iSuperUniquesCount].vSuperunique);
        m_iSuperUniquesCount++;

        result = 1;
    }

    return result;
}

static int SuperUniques_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult = NULL;
    int result = 0;

    if ( !strcmp(acKey, "Name") )
    {
        pcResult = String_FindString(pstLineInfo->vName, "dummy");

        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, m_iSuperUniquesCount);
        }

        result = 1;
    }
    else if ( !strcmp(acKey, "Class") )
    {
        pcResult = MonStats_GetStatsName(pstLineInfo->vClass);

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
    else if ( !strcmp(acKey, "MonSound") )
    {
        pcResult = MonSounds_GetItemSoundsCode(pstLineInfo->vMonSound);

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
    else if ( !strcmp(acKey, "TC") )
    {
        pcResult = TreasureClassEx_GetItemTreasureClass(pstLineInfo->vTC);

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
    else if ( !strcmp(acKey, "TC(N)") )
    {
        pcResult = TreasureClassEx_GetItemTreasureClass(pstLineInfo->vTCmybr1Nmybr2);

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
    else if ( !strcmp(acKey, "TC(H)") )
    {
        pcResult = TreasureClassEx_GetItemTreasureClass(pstLineInfo->vTCmybr1Hmybr2);

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

static void SuperUniques_InitValueMap(ST_VALUE_MAP *pstValueMap, ST_LINE_INFO *pstLineInfo)
{
    INIT_VALUE_BUFFER;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Name, USHORT);   //strings

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Class, UINT);    //monstats

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, hcIdx, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mod1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mod2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mod3, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MonSound, UINT); //sounds

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinGrp, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxGrp, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AutoPos, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EClass, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Stacks, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Replaceable, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Utrans, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Utransmybr1Nmybr2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Utransmybr1Hmybr2, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TC, USHORT);             //TreasureClassEx
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TCmybr1Nmybr2, USHORT);  //TreasureClassEx

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TCmybr1Hmybr2, USHORT);  //TreasureClassEx
}

int process_superuniques(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            MODULE_DEPEND_CALL(string, acTemplatePath, acBinPath, acTxtPath);

            SuperUniques_InitValueMap(pstValueMap, pstLineInfo);

            m_iSuperUniquesCount = 0;

            m_stCallback.pfnConvertValue = SuperUniques_ConvertValue_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(string, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(monstats, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(monsounds, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(treasureclassex, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            SuperUniques_InitValueMap(pstValueMap, pstLineInfo);

            m_stCallback.pfnConvertValue = SuperUniques_ConvertValue;
            m_stCallback.pfnFieldProc = SuperUniques_FieldProc;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

