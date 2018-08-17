#include "global.h"

#define FILE_PREFIX "Experience"

/*
文件名解析：
Experience：经验。
所以此文件就是描述角色最大等级以及每一级升级所需的经验。

Level：级别。

Amazon：亚马逊升下一级所需的经验。

Sorceress：法师升下一级所需的经验。

Necromancer：死灵法师升下一级所需的经验。

Paladin：圣骑士升下一级所需的经验。

Barbarian：野蛮人升下一级所需的经验。

Druid：德鲁依升下一级所需的经验。

Assassin：刺客升下一级所需的经验。

事实上每个角色在相同级别时升下一级所需的经验都是相同的，但这么写给我们制作自己的MOD提供了很方便的前提。

ExpRatio：每一级时的经验衰减因子。每一级时人物所获得的经验为（原经验）* ExpRation / 1024。
经验值的除数，一般为2的倍数，否则容易出现无法正常升级的现象

MaxLvl - 角色所能提升的最高级别（需要相应的经验值）。


此文件原本共有102行。
第1行是列名。
第2行是MaxLevel。即每个角色所能达到的最大级别。
第3-102行为从0级开始，升到下一级所需的经验，以及角色在此等级时的经验衰减情况。

假如想要更改等级上限至200，只需将第2行，即MaxLevel行的值都改为200，最后一列不用改。然后在文件末尾增加101行，分别表示从100级开始升到下一级所需的经验，然后填写好相应的经验要求即可。需要说明的是，经验值最大不能超过2^32 -1 = 4,294,967,295，一但超过将从0
重新开始累积。这是由于存储方式及位数决定的。

chunqiang666: 你好，我计算发现人物90多级的时候升级经验是按照百分之9.01递增的，这样的话在101级时升级所需经验就是4560454391了，已经超出最大值了，这个应该怎么办呢？可以自己设定升级经验的递增百分比么？谢谢。
2013-3-15 17:53回复
zqtjingzi: 回复 chunqiang666 :原版游戏中只定义了99级之前的升级需求，之后的扩展是非常自由的。甚至你可以设置99级之后每100点经验就升一级
2013-3-15 18:44回复
chunqiang666: 回复 zqtjingzi :哦，谢谢了，我按照1.0000901倍递增的，哈哈。你还是凡人修仙传吧的会员啊？
2013-3-15 19:55回复
chunqiang666: 回复 zqtjingzi :之前看过一个帖子里写等级设定最好不要超过127，说是超过127就需要改什么东西才行，是这样的么？谢谢！
2013-3-17 20:58回复

我也说一句
*/

typedef struct
{
    unsigned int vAmazon;
    unsigned int vSorceress;
    unsigned int vNecromancer;
    unsigned int vPaladin;

    unsigned int vBarbarian;
    unsigned int vDruid;
    unsigned int vAssassin;
    unsigned int vExpRatio;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "Level",
    NULL,
};

static int Experience_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "Level") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            sprintf(acOutput, "%u", iLineNo - 1);
        }
        return 1;
    }

    return 0;
}

int process_experience(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Amazon, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Sorceress, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Necromancer, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Paladin, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Barbarian, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Druid, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Assassin, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ExpRatio, UINT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnFieldProc = Experience_FieldProc;
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

