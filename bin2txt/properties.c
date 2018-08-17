#include "global.h"

#define FILE_PREFIX "properties"
#define NAME_PREFIX "pr"

/*
Title 	Properties.txt File Guide
Description 	by Joel Falcou (revised by Myhrginoc)
Sent by 	
This file depends on ItemStatCost.txt. A stat must be defined there in order to use its ID in the stat1-7 fields.

The bulk of the file consists of seven finction blocks. Each block has a function index (FuncX) and three parameters (SetX, ValX, StatX). Parameters are only useful if the underlying function is written to interpret them.

A "*" in the field name means it is a comment field not loaded into the game.

code: property identifier to use in other txt files anywhere a property is applied (e.g. MagicPrefix, MagicSuffix, Automagic, MonProp, Gems, Runes, Sets, SetItems, UniqueItems, Cubemain).

*done: 1 if the property is active (boolean).

set1 to set7: parameter to the property function, if the function can use it (see Color property)

val1 to val7: parameter to the property function, if the function can use it (see class skills properties).

func1 to func7: Function used to assign a value to a property (see list below)

stat1 to stat7: Stat applied by the property (see ItemStatCost.txt), if the function uses it.

*desc: Description of the property

*param: Description of the param value

*min: Description of the min value

*max: Description of the max value

*notes: Additional comments

*eol: terminator field, not used in game, primary purpose is to keep Microsoft Excel from misbehaving.


APPENDIX: Functions of Properties.txt

Here are some functions used by the properties.txt to link param/min/max value to the actual bonus of the properties.

1 - Applies a value to a stat, can use SetX parameter.
2 - defensive function only, similar to 1 ???
3 - Apply the same min-max range as used in the previous function block (see res-all).
4 - not used ???
5 - Dmg-min related ???
6 - Dmg-max related ???
7 - Dmg% related ???
8 - ??? use for speed properties (ias, fcr, etc ...)
9 - Apply the same param and value in min-max range, as used in the previous function block.
10 - skilltab skill group ???
11 - event-based skills ???
12 - random selection of parameters for parameter-based stat ???
13 - durability-related ???
14 - inventory positions on item ??? (related to socket)
15 - use min field only
16 - use max field only
17 - use param field only
18 - Related to /time properties.
19 - Related to charged item.
20 - Simple boolean stuff. Use by indestruct.
21 - Add to group of skills, group determined by stat ID, uses ValX parameter.
22 - Individual skill, using param for skill ID, random between min-max.
23 - ethereal
24 - property applied to character or target monster ???
25--32 can be used in custom code. Check plugin documentation for syntax.

*/

/*
注意：带“*”号的列游戏都不读入的；

code - 这里的代码用在前、后缀，暗金和套装相关文件的物品属性里；
*done - 1为已完成（实际上没用）；
set1-7 - 有颜色的这列为1；可能为布尔类型；
val1-7 - 一些属性有固定的值？（比如+亚马逊技能）；
func1-7 - 属性值的计算公式（看下面）；
stat1-7 - 人物基本属性变化(参照itemstatcost.txt) ；
*desc - 对该属性的描述；
*param - 对属性参数的描述；
*min - 对属性最小值的描述；
*max - 对属性最大值的描述；
*notes - 其他；
*eol - 行结束。

func1-7:
通过以下函数由param/min/max计算实际的奖励：
1 - 使用STAT的值；
2 - 无用参数；
3 - 给几个属性以相同的值 (比如加所有抗性)；用这个的话，Func1 应设为1；
5 - 有关Dmg-min；
6 - 有关Dmg-max；
7 - 有关Dmg%；
8 - 与速度有关的属性使用(ias,fcr 等...)；
10 - 未知或无用参数；
11 - 未知或无用参数；
12 - 未知或无用参数；
13 - 未知或无用参数；
14 - 与凹槽有关的参数；
15 - 使用min的值；
16 - 使用MAX的值；
17 - 使用PARAM的值；
18 - 与时间有关的属性；
19 - 与带聚气技能的物品有关；
20 - 无法破坏；
21 - 与职业专用的东东有关：前面的VALUE必须是职业ID（0到6）；
22 - 给任意职业加特定技能的(比如野蛮人那个变狼的帽子)；
23 - 未知或无用参数；
24 - 未知或无用参数。
*/

/*
文件名解析：Property(ies)就是属性的意思。
此文件中的每一行表示可能出现在装备上的一个属性。


回复

    2楼
    2011-09-04 11:26

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：注意：带“*”号的列游戏是不读入的，也就是说这些列相当于注释。


回复

    3楼
    2011-09-04 11:26

    举报 |

    zqtjingzi
    小吧主
    12

code：属性的代码，会在魔法前、后缀，暗金装备文件的物品属性处使用。
比如你想给装备添加一个全技能的属性，那么你就要找到全技能的代码，应该是在106行，代码为allskills，把这个代码添加到装备的prob列，再加上一个合理的参数，此装备就有+全技能的属性了。

*done：此属性的编辑是否已完成，0为未完成，1为已完成，但实际游戏中此列不起作用。

set1-7：大概是与颜色有关的列，可能为布尔类型，我也没太弄清楚此列是什么含义，但除了Color属性外其它属性都没有使用这些列。


回复

    4楼
    2011-09-04 11:27

    举报 |

    zqtjingzi
    小吧主
    12

val1-7：加某职业技能专用的列，作为职业代码使用。职业代码见后面。

func1-7：此属性的参数计算方法，后面会详细说明。

stat1-7：此属性对人物的影响，(参照ItemStatCost.txt) 。

*desc：对该属性的描述。
*param：对该属性如何使用param值的描述。
*min：对该属性如何min值的描述。
*max：对该属性如何max值的描述。
*notes：其他的一些注释。*eol：行结束标志，必须填0。


回复

    5楼
    2011-09-04 11:27

    举报 |

    zqtjingzi
    小吧主
    12

func1-7:通过以下方式使用param/min/max的值来计算属性的数值x：
1：min <= x <= max，只取整数，均匀分布。
2：与“1”一样（应该有所区别，但是我没发现）。
3：只可能出现在func2-7这几列中，表示使用与func1同样的方式，用于加所有抗性这样的属性。而且此时func1应该为1。
4：没见过
5：取值方式与“1”一样，但只能由dmg-min属性使用，所有其它使用此函数的属性都将变为dmg-min，即增加最小伤害值。
6：取值方式与“1”一样，但只能由dmg-max属性使用，所有其它使用此函数的属性都将变为dmg-max，即增加最大伤害值。
7：取值方式与“1”一样，但只能由dmg%属性使用，所有其它使用此函数的属性都将变为dmg%，即增加百分比伤害值。
8：取值方式与“1”一样，但与速度有关的属性(ias,fcr,frw)都使用这个，但经个人尝试，用“1”也可以。
9：没见过。
10：加某一系技能专用。参数使用方式如下：使用param的值作为技能系代码，使用min和max的值作为变量范围。系代码见后面。
11：触发技能专用。参数使用方式如下：使用param的值作为技能代码，使用min的值作为触发机率，使用max的值作为技能等级。
12：加随机技能属性专用（如奥马斯长袍）。使用param的值作为技能等级，用min和max来限定随机数的取值范围，此随机数作为技能代码使用。
13：取值方式与“1”一样，但使用此函数的装备在生成时耐久度为满值。
14：取值方式与“1”一样，但只能由sock属性使用，所有其它使用此函数的属性都将变为sock，即增加凹槽。
15：使用min的值。
16：使用max的值。
17：使用param的值。
18：随时间变化属性专用。参数使用方式如下：使用param的值作为属性最高时的时间段（0=白天，1=黄昏，2=夜晚，3=黎明），此时的属性值为max，当处于对立时间段（如白天对立夜晚）时使用min作为属性值。其余中间两个时间段使用min和max的平均值。
19：聚气技能属性专用。参数使用方式如下：使用param的值作为技能代码，使用min的值作为聚气数，使用max的值作为技能等级。
20：无法破坏属性专用。不使用其它参数，所有其它使用此函数的属性都将变为无法破坏属性。
21：取值方式与“1”一样，但要求此列前面的val列必须有值，且使用此值作为职业代码决定此属性的职业限制。
22：加某一项技能属性专用。参数使用方式如下：使用param的值作为技能代码，使用min和max的值作为所加技能等级的范围。
23：无形属性专用。不使用其它参数，所有其它使用此函数的属性都将变为无形属性。
24：state属性专用。参数使用方式如下：使用param的值作为状态索引，用min和max的值来限定此状态是否有效。
36：地狱火炬的加随机一个职业这个属性专用。使用此列前的val列作为技能等级，用min和max来限定随机数的范围，此随机数作为职业代码使用。



回复

    6楼
    2011-09-04 11:29

    举报 |

    zqtjingzi
    小吧主
    12

职业代码如下：
0 = 亚马逊
1 = 法师
2 = 死灵
3 = 圣骑
4 = 野蛮人
5 = 德鲁依
6 = 刺客




回复

    7楼
    2011-09-04 11:29

    举报 |

    zqtjingzi
    小吧主
    12

系代码：
0 = ama弓
1 = ama被动
2 = ama标枪
3 = sor火焰
4 = sor闪电
5 = sor冰
6 = nec诅咒
7 = nec骨毒
8 = nec召唤
9 = pal战斗
10= pal攻击
11= pal防御
12= bar战斗
13= bal支配
14= bar战嚎
15= dru召唤
16= dru变形
17= dru元素
18= asn陷阱
19= asn影子
20= asn武学


回复

    8楼
    2011-09-04 11:30

    举报 |

    zqtjingzi
    小吧主
    12

完毕。
如果有错误请指出。
祝各位游戏愉快。



我原来确实说的不够全面，但对于法拳的火焰技能我是这么理解的，火焰技能与其它职业技能如法师技能使用了同样的val=1和func=21，但其区别就在于使用了不同的stat，火焰技能用了item_elemskill这个stat，而法师技能使用了item_addclassskills这一stat。此二者因为func
相同，所以选择参数的方式是相同的，但区别就在于候选**不一样。职业技能中的val指定的是职业列表中的某个职业，而火焰技能（严格说来应该叫元素技能）指定的是元素类型，且应该是指向Elemtypes.txt的指针。如果你将火焰技能的val1改成2
，你就会发现它加成的技能变成了闪电技能，即Elemtypes.txt中的第二行（我验证过）。

另外对于火焰技能的界定是在skills.txt中写明的，所有EType列的值是fire的都是火焰技能，除法师外不光有尸爆，像亚马逊的爆裂箭，圣骑的圣火都属性火焰技能，都是能够被法拳提高技能等级的。

*/

typedef struct
{
    unsigned short vcode;
    unsigned char vset1;
    unsigned char vset2;

    unsigned char vset3;
    unsigned char vset4;
    unsigned char vset5;
    unsigned char vset6;

    unsigned char vset7;
    unsigned char iPadding2;
    unsigned short vval1;

    unsigned short vval2;
    unsigned short vval3;

    unsigned short vval4;
    unsigned short vval5;

    unsigned short vval6;
    unsigned short vval7;

    unsigned char vfunc1;
    unsigned char vfunc2;
    unsigned char vfunc3;
    unsigned char vfunc4;

    unsigned char vfunc5;
    unsigned char vfunc6;
    unsigned char vfunc7;
    unsigned char iPadding7;

    unsigned short vstat1;
    unsigned short vstat2;

    unsigned short vstat3;
    unsigned short vstat4;

    unsigned short vstat5;
    unsigned short vstat6;

    unsigned short vstat7;
} ST_LINE_INFO;

typedef struct
{
    unsigned char vcode[32];
} ST_PROPERTY;

static char *m_apcInternalProcess[] =
{
    "*eol",
    NULL,
};

static char *m_apcNotUsed[] =
{
    "*done",
    "*desc",
    "*param",
    "*min",
    "*max",
    "*notes",
    NULL,
};

static unsigned int m_iPropertyCount = 0;
static ST_PROPERTY *m_astProperty = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astProperty, ST_PROPERTY);

static int Properties_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "*eol") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

char *Properties_GetProperty(unsigned int id)
{
    if ( id >= m_iPropertyCount )
    {
        return NULL;
    }

    return m_astProperty[id].vcode;
}

static int Properties_ConvertValue_Pre(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    int result = 0;

    if ( !strcmp("code", acKey) )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->vcode);
        }

        strncpy(m_astProperty[pstLineInfo->vcode].vcode, acOutput, sizeof(m_astProperty[pstLineInfo->vcode].vcode));
        String_Trim(m_astProperty[pstLineInfo->vcode].vcode);
        m_iPropertyCount++;
        result = 1;
    }

    return result;
}

static int Properties_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;
    int id;

    if ( !strcmp("code", acKey) )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->vcode);
        }

        result = 1;
    }
    else if ( strstr(acKey, "stat") && 1 == sscanf(acKey, "stat%d", &id) )
    {
        unsigned short *psSkill = (short *)&pstLineInfo->vstat1;
        pcResult = ItemStatCost_GetStateName(psSkill[id-1]);
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

int process_properties(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, code, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, set1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, set2, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, set3, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, set4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, set5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, set6, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, set7, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, val1, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, val2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, val3, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, val4, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, val5, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, val6, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, val7, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, func1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, func2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, func3, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, func4, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, func5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, func6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, func7, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stat1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stat2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stat3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stat4, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stat5, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stat6, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stat7, USHORT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iPropertyCount = 0;

            m_stCallback.pfnConvertValue = Properties_ConvertValue_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(itemstatcost, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = Properties_ConvertValue;
            m_stCallback.pfnFieldProc = Properties_FieldProc;
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

