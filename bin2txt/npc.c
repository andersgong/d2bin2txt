#include "global.h"

#define FILE_PREFIX "npc"

/*
NPC.TXT File Guide

By Nefarius (in part based on Phrozen Heart & Mordini's guide)

The old guide is not very accurate when it comes to how the various columns interact, I hope this one will clear the shroud.




npc: an ID pointer to that NPCs row in monstats.txt, do not change this name, otherwise you will recieve an assertion error as soon as you open that vendors inventory.


buy mult: percentage of the items base price to use when it is bought by the NPC. This does not refer to the prices listed in armor, weapons or misc, it refers to the actual base price, that is, after all stat related boosts have been applied. This 
column holds a fraction of 1024, thus 512/1024 would be equal to 50%, lets say we have Cleglaw's Tooth, its actual price is 4027 gold, if we set this column to 1024 that is what we will recieve for selling it to an NPC, if we set this column to 512 we 
will recieve floor(price/1024*value) aka 2013 gold.


sell mult: this follows the same principle as the above, however this controls the price when you buy something from an NPC.


rep mult: this column controls the base price used as the basis of the item repair calculation, it follows the same principle as the two other columns above. But this does not control the actual repair price. How does the game do it then? First of all 
the base repair price is established using the same formula as for the other columns, namely floor(price/1024*value), now lets take Cleglaw's Tooth again for our example, if you set this column to 1024 then a full repair (when the item has 0 durability 
left), will cost 4027 gold, the full price of the item. Should it have 22/44 durability, you rather pay 2013 gold. Thus the whole repair calculation is basically: cost*(1-current_dur/maximum_dur). The recharge cost is added on top of the durability 
repair calculation. Note that the recharge cost is not controlled by this field, the parameters for this calc are spread throughout the games code and skills.txt.


questflag A, B and C: this controls the quest flag that must be checked in order for the following price alterations to take place.


questbuymult A, B and C: this controls the percentage the percentage indicated in the buy mult column is modified, lets say buy mult contains 512, if we put 1024 in questbuymult A the item will _not_ be sold at any different price, since we tell the 
game to use 100% of 50%, which quite clearly is 50%. Thus the Cleglaw's Tooth will be bought for 2013 gold, irregardless of the quest, but what if we set this column to 2048? Well, then we will recieve 4027 gold when we sell it to the npc, since we are 
telling the game to use 200% of 50%, which is 100%. Finally, if we set this column to 512 then we will recieve an item that costs 1006 gold, since we are now using 50% of 50%, which is 25%. The subsequent columns, questbuymult B and questbuymult C stack 
with this one, they do not replace it. So, to clear up the mess I just wrote:

base price = GLD
buy mult = BM
questbuymult = QBM1
questbuymult = QBM2
questbuymult = QBM3

floor( GLD / 1024 * BM / 1024 * QGM1 / 1024 * QGM2 / 1024 * QMG3 ) = actual price

So if we again use the example item from above, GLD=4027. Lets say BM=512 and QBM1-3 are all 2048, then we get: 16108 gold.



questsellmult A, B and C: the same as the above, only that this applies when you buy something from an NPC.


questrepmult A, B and C: again as the above, however this controls the alteration of the base repair price.


max buy, (N) and (H): the maximum amount of gold this NPC will ever pay you for an item you sell on the respective difficulty, the maximum is 2147483647.





Other facts

NPCs will never use values below 1 gold, thus an item that is worth 0 gold will still be bought for 1 gold and sold for 1 gold. This does not apply to gambling, where prices above the maximum result in free gambles. Prices above 2147483647 either as 
result of stats, base price in a file or the NPC calculation itself will be treated as 1.

The buy-price of some items will be off the sell-price by about 10% irregardless of NPC.txt, I haven't quite understood why this happens yet.

Selling price is not influenced by the amount of durability, it used to be like that early on.

*/

/*
Npc.txt文件引导。

npc : NPC的名字；

buy mult : NPC从玩家手中购买物品的价格比例；

sell mult : NPC向玩家出卖物品的价格比例；

rep mult : NPC修复玩家物品的价格比例；

questflag A : 由于完成了NPC所指定的任务而使得NPC的价格比例作出调整；比如说，“9”这个数值就表示你完成ACT2的Q1后NPC对其价格比例作出了调整；

questbuymult A : 完成特定任务后NPC从玩家手中购买物品的价格比例；

questsellmult A : 完成特定任务后NPC向玩家出卖物品的价格比例；

questreplmult A : 完成特定任务后NPC修复玩家物品的价格比例；

questflag B : 由于完成了NPC所指定的任务（第二个任务）而使得NPC的价格比例作出调整；

questbuymult B : 完成特定任务（第二个任务）后NPC从玩家手中购买物品的价格比例；

questsellmult B : 完成特定任务（第二个任务）后NPC向玩家出卖物品的价格比例；

questreplmult B : 完成特定任务（第二个任务）后NPC修复玩家物品的价格比例；

questflag C : 由于完成了NPC所指定的任务（第三个任务）而使得NPC的价格比例作出调整；

questbuymult C : 完成特定任务（第三个任务）后NPC从玩家手中购买物品的价格比例；

questsellmult C : 完成特定任务（第三个任务）后NPC向玩家出卖物品的价格比例；

questreplmult C : 完成特定任务（第三个任务）后NPC修复玩家物品的价格比例；

max buy : NPC在“普通”级别下购买玩家物品的价格上限；

max buy (N) : NPC在“恶梦”级别下购买玩家物品的价格上限；

max buy (H) : NPC在“地狱”级别下购买玩家物品的价格上限。
*/

/*
文件名解析：
Npc：玩游戏的应该都知道这个词的意思，这里单指可以出售东西的NPC。
本文件描述了所以可以出售东西的NPC的行情。
此文件中的每一行表示一个NPC。


回复

    2楼
    2011-09-24 21:20

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    3楼
    2011-09-24 21:20

    举报 |

    zqtjingzi
    小吧主
    12

npc：此NPC的名字，也monstats.txt关联。

buy mult：在此NPC处出售物品时的价格基数。记作b0。

sell mult：在此NPC处购买物品时的价格基数。记作c0。

rep mult：在此NPC处修理物品时的价格基数。记作r0。

questflag A：哪个任务会影响此NPC的价格基数。记作任务A。

questbuymult A：完成任务A后在此NPC处出售物品时的额外价格基数。记作bA。

questsellmult A：完成任务A后在此NPC处购买物品时的额外价格基数。记作sA。

questreplmult A：完成任务A后在此NPC处修理物品时的额外价格基数。记作rA。

questflag B：还有哪个任务会影响此NPC的价格基数。记作任务B。

questbuymult B：完成任务B后在此NPC处出售物品时的额外价格基数。记作bB。

questsellmult B：完成任务B后在此NPC处出售物品时的额外价格基数。记作sB。

questreplmult B：完成任务B后在此NPC处出售物品时的额外价格基数。记作rB。

questflag C：又有哪个任务会影响此NPC的价格基数。记作任务C。

questbuymult C：完成任务C后在此NPC处出售物品时的额外价格基数。记作bC。

questsellmult C：完成任务C后在此NPC处出售物品时的额外价格基数。记作sC。

questreplmult C：完成任务C后在此NPC处出售物品时的额外价格基数。记作rC。

max buy：普通难度下在此NPC处出售物品时的最高价格。

max buy (N)：恶梦难度下在此NPC处出售物品时的最高价格。

max buy (H)：地狱难度下在此NPC处出售物品时的最高价格。


回复

    4楼
    2011-09-24 21:21

    举报 |

    zqtjingzi
    小吧主
    12

补充说明1：
最终价格的计算：
假设A、B、C都不为0。则：
出售价格 = 原物品价格 * (b0 / 1024) * (bA / 1024) * (bB / 1024) * (bC / 1024) //出售时不受耐久度影响。
购买价格 = 原物品价格 * (s0 / 1024) * (sA / 1024) * (sB / 1024) * (sC / 1024) //购买时耐久度都为满值。
修理价格 = 原物品价格 * (已缺失的耐久度 / 总耐久度) * (r0 / 1024) * (rA / 1024) * (rB / 1024) * (rC / 1024)

出售、购买、修理的主语都为玩家。

原物品价格由两部分组成：(1) 由Weapons.txt、Armor.txt、Misc.txt决定的底材价格(2) 由ItemStatCost.txt决定的属性价格。


回复

    5楼
    2011-09-24 21:21

    举报 |

    zqtjingzi
    小吧主
    12

补充说明2：
在NPC处，除赌博外的一切价格最少为1，不会有免费的物品。

*/

typedef struct
{
    unsigned int vnpc;  //monstats

    unsigned int vsellmyspmult;
    unsigned int vbuymyspmult;
    unsigned int vrepmyspmult;

    unsigned int vquestflagmyspA;
    unsigned int vquestflagmyspB;
    unsigned int vquestflagmyspC;

    unsigned int vquestsellmultmyspA;
    unsigned int vquestsellmultmyspB;
    unsigned int vquestsellmultmyspC;

    unsigned int vquestbuymultmyspA;
    unsigned int vquestbuymultmyspB;
    unsigned int vquestbuymultmyspC;

    unsigned int vquestrepmultmyspA;
    unsigned int vquestrepmultmyspB;
    unsigned int vquestrepmultmyspC;

    unsigned int vmaxmyspbuy;
    unsigned int vmaxmyspbuymyspmybr1Nmybr2;
    unsigned int vmaxmyspbuymyspmybr1Hmybr2;
} ST_LINE_INFO;

static int NPC_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "npc") )
    {
        pcResult = MonStats_GetStatsName(pstLineInfo->vnpc);
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

int process_npc(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, npc, UINT);  //monstats

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, buymyspmult, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sellmyspmult, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, repmyspmult, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, questflagmyspA, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, questflagmyspB, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, questflagmyspC, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, questsellmultmyspA, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, questsellmultmyspB, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, questsellmultmyspC, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, questbuymultmyspA, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, questbuymultmyspB, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, questbuymultmyspC, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, questrepmultmyspA, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, questrepmultmyspB, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, questrepmultmyspC, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, maxmyspbuy, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, maxmyspbuymyspmybr1Nmybr2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, maxmyspbuymyspmybr1Hmybr2, UINT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(monstats, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = NPC_ConvertValue;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

