#include "global.h"

#define FILE_PREFIX "RarePrefix"

/*
文件名解析：
Rare：稀有的，在暗黑里指亮金的。
Prefix：前缀，就是词缀中的前缀。
Suffix：后缀，就是词缀中的后缀。
所以这两个文件描述了所有亮金级词缀的前缀与后缀的相关信息。
此文件中的每一行表示一个词缀前缀或后缀。


回复

    2楼
    2011-09-30 22:15

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    3楼
    2011-09-30 22:16

    举报 |

    zqtjingzi
    小吧主
    12

Name：前缀名或后缀名。该稀有物品前缀的字符串键值(string key),tbl文件的左端入口

version：适用的最低游戏版本。'0'-diablo2原版,‘1‘-破坏之王

itype1-7：此词缀适用于的第1-7种装备类型。包含物品类型(见附录)。

etype1-4：此词缀不适用的第1-4种装备类型，所有etype应是某一itype的子类型。排除物品类型(见附录)。

此词缀最终能够适用的装备类型为sum(itype1-7) - sum(etype1-4)，即所有itype的总和再除去etype中的类型。

add：价格增加因子。卖给NPC时价格增加因子(和因子?)，与skills.txt中类似

divide：价格约束因子。卖给NPC时的价格减少因子(除因子?)。

multiply：价格放大因子。价格增加因子(乘因子?)，与skills.txt中类似


回复

    4楼
    2011-09-30 22:16

    举报 |

    zqtjingzi
    小吧主
    12

特殊说明1：
之所以把这两个文件放在一起说明是因为它们所含有的列是一模一样的。


回复

    5楼
    2011-09-30 22:16

    举报 |

    zqtjingzi
    小吧主
    12

特殊说明2：
所有亮金级词缀都没有属性，只有名字和适用的装备类型。也就是说某一亮金级词缀是否出现只与装备底材类型有关，而且相同属性的装备词缀可能完全不一样。反之也是，相同名字的亮金装备属性可能完全不一样。

附录:itype & etype

itype = Inclusion TYPE(包含类型) & etype = Exclusion TYPE(排除类型)

这个决定了一个给定的词缀可以在{itype}所包含的物品类型上产生，而不能产生于{etype}所包含的物品类型。

比如：itype = {weap,armo} etype = {axe,helm,belt}
这个表示该词缀可以产生在所有的武器和盔甲上，但是在斧子,头盔和腰带上不能产生。

通过这种方法(在‘itype’和‘etype’里面设定物品类型)，你可以控制某类物品是否能产生(或者说接受)该词缀，比如让某个(些)词缀只能在剑(swords)上产生，或者不能让它在剑上产生。当然，首先你必须知道该物品的代码。

注意：以上的说明同样适应于其他有‘itype/etype’的.txt文件，如automagic,rareprefix/suffix。
*/

typedef struct
{
    unsigned int iPadding0;
    unsigned int iPadding1;
    unsigned int iPadding2;

    unsigned short iPadding3;
    unsigned short vversion;

    unsigned short vitype1;
    unsigned short vitype2;

    unsigned short vitype3;
    unsigned short vitype4;

    unsigned short vitype5;
    unsigned short vitype6;

    unsigned short vitype7;
    unsigned short vetype1;

    unsigned short vetype2;
    unsigned short vetype3;

    unsigned short vetype4;
    unsigned char vname[32];

    unsigned short iPadding17;
} ST_LINE_INFO;

static char *m_apcNotUsed[] =
{
    "divide",
    "multiply",
    "add",
    NULL,
};

static int RarePrefix_ConverValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int id;
    int result = 0;

    if ( strlen("itype1") == strlen(acKey) && 1 == sscanf(acKey, "itype%d", &id) )
    {
        unsigned short *pwItype = &pstLineInfo->vitype1;
        pcResult = ItemTypes_GetItemCode(pwItype[id - 1]);
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
        unsigned short *pwItype = &pstLineInfo->vetype1;
        pcResult = ItemTypes_GetItemCode(pwItype[id - 1]);
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

int process_rareprefix(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, version, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype4, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype5, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype6, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itype7, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etype1, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etype2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etype3, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, etype4, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, name, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(itemtypes, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = RarePrefix_ConverValue;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

