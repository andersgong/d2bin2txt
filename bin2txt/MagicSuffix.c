#include "global.h"

#define FILE_PREFIX "MagicSuffix"

/*
文件名1：MagicSuffix.txt
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
Suffix：前缀，就是魔法词缀中的前缀。
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

version：适用的最低游戏版本。

spawnable：是否可在游戏中生成。

rare：此词缀是否能在稀有（亮金）物品上出现。如+3单系技能的词缀此列为0，所以这样的属性不能出现在稀有（亮金）物品上。

level：词缀等级。只有当物品等级大于此词缀的词缀等级时，此词缀才可能出现在这一物品上。

maxLevel：词缀等级上限。当此列有值时，此词缀只会出现在物品等级小于此等级的物品上。

levelreq：使用带有此词缀物品的角色等级需求。

classSpecfic：是否为某一职业专用。

class：是否对某一职业有特殊的使用等级需求。若有的话，此列当填写职业代码。如传送聚气词缀。对除法师外的所有职业使用等级至少为24级，而法师18级就够了。

classLevelreq：紧跟上一列，特定职业的需求。

frequency：在同一组词缀中此词缀出现的频率。

group：词缀所属的词缀组。对每一个物品而言，属于同一词缀组的词缀只能出现一个。

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

说明：在MagicSuffix.txt中etype共有5列，在MagicSuffix.txt中etype共有3列。
此词缀最终能够适用的装备类型为sum(itype1-7) - sum(etype1-3(5))，即所有itype的总和再除去etype中的类型。

divide：价格因子1。

multiply：价格因子2。

add：价格因子3。

*eol：行尾标志，必须为0。
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

static int MagicSuffix_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
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


static char *MagicSuffix_GetKey(void *pvLineInfo, char *pcKey, int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strcpy(pcKey, pstLineInfo->vName);
    *iKeyLen = (int)strlen(pcKey);

    return pcKey;
}

int process_magicsuffix(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
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
            //m_stCallback.pfnGetKey = MagicSuffix_GetKey;
            m_stCallback.pfnConvertValue = MagicSuffix_ConvertValue;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

