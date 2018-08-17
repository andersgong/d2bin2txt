#include "global.h"

#define FILE_PREFIX "monlvl"
#define NAME_PREFIX "mv"

/*
Title 	MonLvl.txt File Guide
Description 	by Kingpin
Sent by 	
I didn't see that this is mentioned here. In MonLvl.txt all L-XX columns is used for ladder/single player and tcp-ip. So here is a fileguide for this file.

MonLvl.txt

AC: Armor Class (Normal), is calculated together with monstats.txt column(s) {(MonLvl.txt Ac * Monstats.txt AC) / 100},
Closed battle.net only

AC(N): Armor Class (Nightmare), is calculated together with monstats.txt column(s) {(MonLvl.txt Ac * Monstats.txt AC) / 100}, Closed battle.net only

AC(H): Armor Class (Hell), is calculated together with monstats.txt column(s) {(MonLvl.txt Ac * Monstats.txt AC) / 100},
Closed battle.net only

L-AC: Armor Class (Normal), is calculated together with monstats.txt column(s) {(MonLvl.txt Ac * Monstats.txt AC) / 100}, Ladder/Single player/tcp-ip

L-AC(N): Armor Class (Nightmare), is calculated together with monstats.txt column(s) {(MonLvl.txt Ac * Monstats.txt AC) /
100}, Ladder/Single player/tcp-ip

L-AC(H): Armor Class (Hell), is calculated together with monstats.txt column(s) {(MonLvl.txt Ac * Monstats.txt AC) / 100}, Ladder/Single player/tcp-ip

TH: To Hit (Normal), is calculated together with monstats.txt column(s) {(MonLvl.txt TH * Monstats.txt A1TH and MonLvl.txt TH * Monstats.txt A2TH) / 100}, Closed battle.net only

TH(N): To Hit (Nightmare) , is calculated together with monstats.txt column(s) {(MonLvl.txt TH * Monstats.txt A1TH and
MonLvl.txt TH * Monstats.txt A2TH) / 100}, Closed battle.net only

TH(H): To Hit (Hell), is calculated together with monstats.txt column(s) {(MonLvl.txt TH * Monstats.txt A1TH and MonLvl.txt TH * Monstats.txt A2TH) / 100}, Closed battle.net only

L-TH: To Hit (Normal), is calculated together with monstats.txt column(s) {(MonLvl.txt TH * Monstats.txt A1TH and MonLvl.txt TH * Monstats.txt A2TH) / 100}, Ladder/Single player/tcp-ip

L-TH(N): To Hit (Nightmare), is calculated together with monstats.txt column(s) {(MonLvl.txt TH * Monstats.txt A1TH and
MonLvl.txt TH * Monstats.txt A2TH) / 100}, Ladder/Single player/tcp-ip

L-TH(H): To Hit (Hell), is calculated together with monstats.txt column(s) {(MonLvl.txt TH * Monstats.txt A1TH and MonLvl.txt TH * Monstats.txt A2TH) / 100}, Ladder/Single player/tcp-ip
HP: Hitpoints (Normal), is calculated together with monstats.txt column(s) {(MonLvl.txt HP * Monstats.txt minHP) / 100 and
MonLvl.txt HP * Monstats.txt maxHP) / 100}, Closed battle.net only

HP(N): Hitpoints (Nightmare), is calculated together with monstats.txt column(s) {(MonLvl.txt HP * Monstats.txt minHP) / 100 and MonLvl.txt HP * Monstats.txt maxHP) / 100}, Closed battle.net only

HP(H): Hitpoints (Hell), is calculated together with monstats.txt column(s) {(MonLvl.txt HP * Monstats.txt minHP) / 100 and
MonLvl.txt HP * Monstats.txt maxHP) / 100)}, Closed battle.net only

L-HP: Hitpoints (Normal), is calculated together with monstats.txt column(s) {(MonLvl.txt HP * Monstats.txt minHP) / 100 and MonLvl.txt HP * Monstats.txt maxHP) / 100)}, Ladder/Single player/tcp-ip

L-HP(N): Hitpoints (Nightmare), is calculated together with monstats.txt column(s) {(MonLvl.txt HP * Monstats.txt minHP) / 100 and MonLvl.txt HP * Monstats.txt maxHP) / 100) / 100}, Ladder/Single player/tcp-ip

L-HP(H): Hitpoints (Hell), is calculated together with monstats.txt column(s) {(MonLvl.txt HP * Monstats.txt minHP) / 100 and MonLvl.txt HP * Monstats.txt maxHP) / 100)}, Ladder/Single player/tcp-ip

DM: Damage (Normal), is calculated together with monstats.txt column(s) {(MonLvl.txt DM * Monstats.txt A1MinD) / 100 and
MonLvl.txt DM * Monstats.txt A1MaxD) / 100 and MonLvl.txt DM * Monstats.txt A2MinD) / 100 and MonLvl.txt DM * Monstats.txt A2MaxD) / 100}, Closed battle.net only

DM(N): Damage (Nightmare), is calculated together with monstats.txt column(s) {(MonLvl.txt DM * Monstats.txt A1MinD) / 100 and MonLvl.txt DM * Monstats.txt A1MaxD) / 100 and MonLvl.txt DM * Monstats.txt A2MinD) / 100 and MonLvl.txt DM * Monstats.txt 
A2MaxD) / 100}, Closed battle.net only

DM: Damage (Normal), is calculated together with monstats.txt column(s) {(MonLvl.txt DM * Monstats.txt A1MinD) / 100 and
MonLvl.txt DM * Monstats.txt A1MaxD) / 100 and MonLvl.txt DM * Monstats.txt A2MinD) / 100 and MonLvl.txt DM * Monstats.txt A2MaxD) / 100}, Closed battle.net only

DM(H): Damage (Hell), is calculated together with monstats.txt column(s) {DM: Damage (Normal) is calculated together with monstats.txt ac column {(MonLvl.txt DM * Monstats.txt A1MinD) / 100 and MonLvl.txt DM * Monstats.txt A1MaxD) / 100 and MonLvl.txt 
DM * Monstats.txt A2MinD) / 100 and MonLvl.txt DM * Monstats.txt A2MaxD) / 100}, Closed battle.net only

L-DM: Damage (Normal), is calculated together with monstats.txt column(s) {(MonLvl.txt DM * Monstats.txt A1MinD) / 100 and MonLvl.txt DM * Monstats.txt A1MaxD) / 100 and MonLvl.txt DM * Monstats.txt A2MinD) / 100 and MonLvl.txt DM * Monstats.txt A2MaxD) 
/ 100}, Closed battle.net only

DM: Damage (Normal) , is calculated together with monstats.txt column(s) {(MonLvl.txt DM * Monstats.txt A1MinD) / 100 and MonLvl.txt DM * Monstats.txt A1MaxD) / 100 and MonLvl.txt DM * Monstats.txt A2MinD) / 100 and MonLvl.txt DM * Monstats.txt A2MaxD) 
/ 100}, Ladder/Single player/tcp-ip

L-DM(N): Damage (Nightmare), is calculated together with monstats.txt column(s) {(MonLvl.txt DM * Monstats.txt A1MinD) / 100 and MonLvl.txt DM * Monstats.txt A1MaxD) / 100 and MonLvl.txt DM * Monstats.txt A2MinD) / 100 and MonLvl.txt DM * Monstats.txt 
A2MaxD) / 100}, Ladder/Single player/tcp-ip

DM: Damage (Normal), is calculated together with monstats.txt column(s) {(MonLvl.txt DM * Monstats.txt A1MinD) / 100 and
MonLvl.txt DM * Monstats.txt A1MaxD) / 100 and MonLvl.txt DM * Monstats.txt A2MinD) / 100 and MonLvl.txt DM * Monstats.txt A2MaxD) / 100}, Ladder/Single player/tcp-ip

L-DM(H): Damage (Hell) , is calculated together with monstats.txt column(s) {(MonLvl.txt DM * Monstats.txt A1MinD) / 100 and MonLvl.txt DM * Monstats.txt A1MaxD) / 100 and MonLvl.txt DM * Monstats.txt A2MinD) / 100 and MonLvl.txt DM * Monstats.txt A2MaxD
) / 100}, Ladder/Single player/tcp-ip

DM: Damage (Normal) is calculated together with monstats.txt ac column {(MonLvl.txt DM * Monstats.txt A1MinD) / 100 and
MonLvl.txt DM * Monstats.txt A1MaxD) / 100 and MonLvl.txt DM * Monstats.txt A2MinD) / 100 and MonLvl.txt DM * Monstats.txt A2MaxD) / 100}, Ladder/Single player/tcp-ip

XP: Experience Points (Normal) , is calculated together with monstats.txt column(s) {(MonLvl.txt XP * Monstats.txt Exp
) / 100 }, Closed battle.net only

XP(N): Experience Points (Nightmare) , is calculated together with monstats.txt column(s) {(MonLvl.txt XP * Monstats.txt Exp) / 100 }, Closed battle.net only

XP(H): Experience Points (Hell) , is calculated together with monstats.txt column(s) {(MonLvl.txt XP * Monstats.txt Exp
) / 100 }, Closed battle.net only

L-XP: Experience Points (Normal) , is calculated together with monstats.txt column(s) {(MonLvl.txt XP * Monstats.txt Exp
) / 100 }, Ladder/Single player/tcp-ip

L-XP(N): Experience Points (Nightmare) , is calculated together with monstats.txt column(s) {(MonLvl.txt XP * Monstats.txt Exp) / 100 }, Ladder/Single player/tcp-ip

L-XP(H): Experience Points (Hell) , is calculated together with monstats.txt column(s) {(MonLvl.txt XP * Monstats.txt Exp
) / 100 }, Ladder/Single player/tcp-ip

*/

/*
AC: 盔甲(AC 防御) (普通),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt Ac*Monstats.txt AC)/100},封闭式战网；

AC:(N)盔甲(AC 防御) (恶梦),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt Ac*Monstats.txt AC)/100},封闭式战网；

AC:(H) 盔甲(AC 防御) (地狱),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt Ac*Monstats.txt AC)/100},封闭式战网；

L-AC:盔甲(AC 防御) (普通),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt Ac*Monstats.txt AC)/100},Ladder模式/单人游戏/tcp- ip；

L-AC:(N) 盔甲(AC 防御) (恶梦),连同 monstats.txt 列 (s) 一并计算 {/( MonLvl.txt Ac*Monstats.txt AC)/100}, Ladder模式/ 单人游戏/ tcp- ip；

L-AC:(H)盔甲(AC 防御) (地狱),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt Ac*Monstats.txt AC)/100},Ladder模式/单人游戏/tcp- ip；

TH:to hit(应该指攻击等级) (普通),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt TH*Monstats.txt A1TH 和 MonLvl.txt TH*Monstats.txt A2TH)/100},封闭式战网；

TH:(N) to hit(应该指攻击等级) (恶梦),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt TH* Monstats.txt A1TH 和 MonLvl.txt TH*Monstats.txt A2TH)/100}, 封闭式战网；

TH:(H)to hit(应该指攻击等级)(应该指攻击等级) (地狱),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt TH*Monstats.txt A1TH 和 MonLvl.txt TH*Monstats.txt A2TH)/100},封闭式战网；

L-TH:to hit(应该指攻击等级) (普通),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt TH*Monstats.txt A1TH 和 MonLvl.txt TH*Monstats.txt A2TH)/100},Ladder模式/单人游戏/tcp- ip；

L-TH:(N) to hit(应该指攻击等级) (恶梦),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt TH* Monstats.txt A1TH 和MonLvl.txt TH*Monstats.txt A2TH)/100}, Ladder模式/ 单人游戏/ tcp- ip；

L-TH:(H)to hit(应该指攻击等级) (地狱),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt TH*Monstats.txt A1TH 和 MonLvl.txt TH*Monstats.txt A2TH)/100},Ladder模式/单人游戏/tcp- ip；

HP: 生命值(普通),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt HP*Monstats.txt minHP)/100 和
MonLvl.txt HP*Monstats.txt maxHP)/100}, 封闭式战网；

HP:(N)生命值(恶梦),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt HP*Monstats.txt minHP)/100 和 MonLvl.txt HP*Monstats.txt maxHP)/100},封闭式战网；

HP:(H) 生命值(地狱),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt HP*Monstats.txt minHP)/100 和MonLvl.txt HP*Monstats.txt maxHP)/100)}, 封闭式战网；

L-HP: 生命值(普通),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt HP*Monstats.txt minHP)/100 和 MonLvl.txt HP*Monstats.txt maxHP)/100)}, Ladder模式/ 单人游戏/ tcp- ip；

L-HP:(N)生命值(恶梦),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt HP*Monstats.txt minHP)/100 和 MonLvl.txt HP*Monstats.txt maxHP)/100)/100},Ladder模式/单人游戏/tcp- ip；

L-HP:(H) 生命值(地狱),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt HP*Monstats.txt minHP)/100 和 MonLvl.txt HP*Monstats.txt maxHP)/100)}, Ladder模式/ 单人游戏/ tcp- ip；

DM: 损害 (普通),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt DM*Monstats.txt A1MinD)/100 和
MonLvl.txt DM*Monstats.txt A1MaxD)/100 和 MonLvl.txt DM*Monstats.txt A2MinD)/100 和 MonLvl.txt DM*Monstats.txt A2MaxD)/100}, 封闭式战网；

DM:(N)损害 (恶梦),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt DM*Monstats.txt A1MinD)/100 和 MonLvl.txt DM*Monstats.txt A1MaxD)/100 和 MonLvl.txt DM*Monstats.txt A2MinD)/100 和 MonLvl.txt DM*Monstats.txt A2MaxD)/100},封闭式战网；

DM: 损害 (普通),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt DM*Monstats.txt A1MinD)/100 和
MonLvl.txt DM*Monstats.txt A1MaxD)/100 和 MonLvl.txt DM*Monstats.txt A2MinD)/100 和 MonLvl.txt DM*Monstats.txt A2MaxD)/100}, 封闭式战网；

DM:(H) 损害 (地狱),连同 monstats.txt 列 (s) 一并计算 {DM:损害 (普通) 连同 monstats.txt ac 列一并计算{(MonLvl.txt DM*Monstats.txt A1MinD)/100 和 MonLvl.txt DM*Monstats.txt A1MaxD)/100 和 MonLvl.txt DM*Monstats.txt A2MinD)/100 和 MonLvl.txt DM*Monstats.
txt A2MaxD)/100},只封闭式战网；

L-DM:损害 ( 普通),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt DM*Monstats.txt A1MinD)/100 和 MonLvl.txt DM*Monstats.txt A1MaxD)/100 和 MonLvl.txt DM*Monstats.txt A2MinD)/100 和 MonLvl.txt DM*Monstats.txt A2MaxD)/100},只封闭式战网；

DM:损害 (普通),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt DM*Monstats.txt A1MinD)/100 和 MonLvl.txt DM*Monstats.txt A1MaxD)/100 和 MonLvl.txt DM*Monstats.txt A2MinD)/100 和 MonLvl.txt DM*Monstats.txt A2MaxD)/100},Ladder模式/单人游戏/tcp- ip；

L-DM:(N)损害 (恶梦),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt DM*Monstats.txt A1MinD)/100 和 MonLvl.txt DM*Monstats.txt A1MaxD)/100 和 MonLvl.txt DM*Monstats.txt A2MinD)/100 和 MonLvl.txt DM*Monstats.txt A2MaxD)/100},Ladder模式/单人游戏/tcp- ip；

DM: 损害 (普通),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt DM*Monstats.txt A1MinD)/100 和
MonLvl.txt DM* Monstats.txt A1MaxD)/100 和 MonLvl.txt DM*Monstats.txt A2MinD)/100 和 MonLvl.txt DM*Monstats.txt A2MaxD)/100},Ladder模式/单人游戏/tcp- ip；

L-DM:(H)损害 (地狱),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt DM*Monstats.txt A1MinD)/100 和 MonLvl.txt DM*Monstats.txt A1MaxD)/100 和 MonLvl.txt DM*Monstats.txt A2MinD)/100 和 MonLvl.txt DM*Monstats.txt A2MaxD)/100},Ladder模式/单人游戏/tcp- ip；

DM: 损害 (普通) 连同 monstats.txt ac 列一并计算 {( MonLvl.txt DM*Monstats.txt A1MinD)/100 和
MonLvl.txt DM*Monstats.txt A1MaxD)/100 和 MonLvl.txt DM*Monstats.txt A2MinD)/100 和 MonLvl.txt DM*Monstats.txt A2MaxD)/100},Ladder模式/单人游戏/tcp- ip；

XP: 经验点 (普通),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt XP* Monstats.txt Exp
)/100}, 封闭式战网；

XP:(N)经验点 (恶梦),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt XP*Monstats.txt Exp)/100},只封闭式战网；

XP:(H) 经验点 (地狱),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt XP* Monstats.txt Exp
)/100}, 封闭式战网；

L-XP: 经验点 (普通),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt XP* Monstats.txt Exp
)/100}, Ladder模式/ 单人游戏/ tcp- ip；

L-XP:(N)经验点 (恶梦),连同 monstats.txt 列 (s) 一并计算{(MonLvl.txt XP*Monstats.txt Exp)/100},Ladder模式/单人游戏/tcp- ip；

L-XP:(H) 经验点 (地狱),连同 monstats.txt 列 (s) 一并计算 {( MonLvl.txt XP* Monstats.txt Exp
)/100},Ladder模式/单人游戏/tcp-ip。
*/

/*
文件名解析：
Mon：monster（怪物）的简称。
Lvl：level（等级）的简写。
所以本文件描述了怪物等级相关的一些属性。
此文件中的每一行表示一个等级。


回复

    2楼
    2011-09-19 23:21

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    3楼
    2011-09-19 23:21

    举报 |

    zqtjingzi
    小吧主
    12

Level：等级。在这里指怪物的等级。

L-AC：普通难度下的怪物在此等级时的防御值。

L-AC(N)：恶梦难度下的怪物在此等级时的防御值。

L-AC(H)：地狱难度下的怪物在此等级时的防御值。

L-TH：普通难度下的怪物在此等级时的攻击准确率。

L-TH(N)：恶梦难度下的怪物在此等级时的攻击准确率。

L-TH(H)：地狱难度下的怪物在此等级时的攻击准确率。

L-HP：普通难度下的怪物在此等级时的生命值。

L-HP(N)：恶梦难度下的怪物在此等级时的生命值。

L-HP(H)：地狱难度下的怪物在此等级时的生命值。

L-DM：普通难度下的怪物在此等级时的伤害值。

L-DM(N)：恶梦难度下的怪物在此等级时的伤害值。

L-DM(H)：地狱难度下的怪物在此等级时的伤害值。

L-XP：普通难度下的怪物在此等级时的经验值。

L-XP(N)：恶梦难度下的怪物在此等级时的经验值。

L-XP(H)：地狱难度下的怪物在此等级时的经验值。


回复

    4楼
    2011-09-19 23:21

    举报 |

    zqtjingzi
    小吧主
    12

特殊说明：本文件中所有的怪物属性值都并不是实际游戏中怪物的属性值，还需要乘以在monstats.txt中每种怪物的属性缩放因子才是真正的属性值。如实际某种怪物的防御值应为 L-AC * level * AC，其中AC就是此怪物在monstats.txt中AC列的值。

*/

typedef struct
{
    unsigned int vAC;
    unsigned int vACmybr1Nmybr2;
    unsigned int vACmybr1Hmybr2;

    unsigned int vLmysubAC;
    unsigned int vLmysubACmybr1Nmybr2;
    unsigned int vLmysubACmybr1Hmybr2;

    unsigned int vTH;
    unsigned int vTHmybr1Nmybr2;
    unsigned int vTHmybr1Hmybr2;

    unsigned int vLmysubTH;
    unsigned int vLmysubTHmybr1Nmybr2;
    unsigned int vLmysubTHmybr1Hmybr2;

    unsigned int vHP;
    unsigned int vHPmybr1Nmybr2;
    unsigned int vHPmybr1Hmybr2;

    unsigned int vLmysubHP;
    unsigned int vLmysubHPmybr1Nmybr2;
    unsigned int vLmysubHPmybr1Hmybr2;

    unsigned int vDM;
    unsigned int vDMmybr1Nmybr2;
    unsigned int vDMmybr1Hmybr2;

    unsigned int vLmysubDM;
    unsigned int vLmysubDMmybr1Nmybr2;
    unsigned int vLmysubDMmybr1Hmybr2;

    unsigned int vXP;
    unsigned int vXPmybr1Nmybr2;
    unsigned int vXPmybr1Hmybr2;

    unsigned int vLmysubXP;
    unsigned int vLmysubXPmybr1Nmybr2;
    unsigned int vLmysubXPmybr1Hmybr2;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "Level",
    NULL,
};

static unsigned int m_iMonLvlCount = 0;

static int MonLvl_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
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
            sprintf(acOutput, "%s%u", NAME_PREFIX, m_iMonLvlCount);
        }

        m_iMonLvlCount++;

        return 1;
    }

    return 0;
}

int process_monlvl(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AC, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ACmybr1Nmybr2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ACmybr1Hmybr2, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubAC, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubACmybr1Nmybr2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubACmybr1Hmybr2, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TH, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, THmybr1Nmybr2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, THmybr1Hmybr2, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubTH, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubTHmybr1Nmybr2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubTHmybr1Hmybr2, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HP, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HPmybr1Nmybr2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HPmybr1Hmybr2, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubHP, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubHPmybr1Nmybr2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubHPmybr1Hmybr2, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DM, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DMmybr1Nmybr2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DMmybr1Hmybr2, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubDM, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubDMmybr1Nmybr2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubDMmybr1Hmybr2, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, XP, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, XPmybr1Nmybr2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, XPmybr1Hmybr2, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubXP, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubXPmybr1Nmybr2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LmysubXPmybr1Hmybr2, UINT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnFieldProc = MonLvl_FieldProc;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
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

