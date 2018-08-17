#include "global.h"

#define FILE_PREFIX "events"
#define NAME_PREFIX "ev"

/*
在现有的TXT文件中，有一个名为Events.txt的TXT文件，只有14行2列，很小很小，但作用不可低估。“Events”简单翻
释过来就“事件”之意，Events.txt文件中记录了13个“Events（事件）”。来看一下都有什么事件发生于游戏中。

事件名称 — 事件描述

hitbymissile — 发出发射物打击敌人(被动性质)；

damagedinmelee — 使混战范围内的敌人受到伤害(被动防御性质)；

damagedbymissile — 使敌人受到发射物伤害(被动性质)；

attackedinmelee — 对混战范围内的敌人进行攻击(主动防御性质)；

doactive — 激活技能状态；

domeleedamage — 使自身受到的伤害返回给对方(主动性质)；

domissiledamage — 使敌人受到发射物攻击伤害(主动性质)；

domeleeattack — 对近身敌人攻击(主动性质)；

domissileattack — 对附近敌人进行发射物攻击(主动性质)；

kill — 杀死敌人后得到治疗；

killed — 被杀死；

absorbdamage — 吸收伤害(主动性质)；

levelup — 等级增加。

关于Events.txt所有的事件资料，知道了它的文件引导，还须知道另外一件事，就是“Event Functions”，直释就是“事件函数”，而这个“事件函数”还真真正正是个“数”，分别是“1～31”共31个“事件函数”，还是先来看一下具体内容。

事件函数 — 功能描述

1 — 在装甲上加上冰弹报复打击

2 — 在装甲上加上冻结报复打击

3 — 在装甲上加上霜冻报复打击

4 — 使敌人造成的伤害返还于本身

5 — 使敌人被攻击时生命流向攻击者

6 — 使攻击者受到物理伤害

7 — 反击

8 — 让附近的怪物因恐惧而奔逃

9 — 使怪物目盲

10 — 攻击者受到闪电伤害

11 — 攻击者受到火焰伤害

12 — 攻击者受到冰冻伤害

13 — 损失法力

14 — 冻结目标

15 — 撕开伤口

16 — 压碎打击

17 — 增加法力

18 — 增加生命

19 — 减缓敌人

20 — 在攻击时释放技能

21 — 在被攻击时释放技能

22 — 吸收物理伤害

23 — 当鲜血石魔受到生命损失的同时石魔的所属者也同样损失生命

24 — 吸收物理伤害、火伤害、电伤害、冰伤害中的一种或多种

25 — 吸收火、电、冰三种元素伤害

26 — 当鲜血石魔取得生命的同时石魔的所属者也同样取得生命

27 — 无论是黏土石魔受伤或是敌人受伤，都使敌人速度减慢。

28 — 增加生命

29 — 把死去敌人的灵魂来增加生命和魔法

30 — 在升级或死亡时释放技能

31 — 复活

以上便是全部的“事件函数”和功能简介。


*/

typedef struct
{
    unsigned short vevent;
} ST_LINE_INFO;

static char *m_apcNotUsed[] =
{
    "*desc",
    NULL,
};

typedef struct
{
    char vevent[64];
} ST_EVENTS;

static unsigned int m_iEventsCount = 0;
static ST_EVENTS *m_astEvents = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astEvents, ST_EVENTS);

static int Events_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "event") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->vevent);
        }

        strncpy(m_astEvents[m_iEventsCount].vevent, acOutput, sizeof(m_astEvents[m_iEventsCount].vevent));
        String_Trim(m_astEvents[m_iEventsCount].vevent);
        m_iEventsCount++;
        return 1;
    }

    return 0;
}

static int process_events_x(char *acTemplatePath, char *acBinPath, char *acTxtPath)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, event, USHORT);

    m_iEventsCount = 0;

    m_stCallback.pfnConvertValue = Events_ConvertValue;
    m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
    m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
    m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

    return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
        pstValueMap, Global_GetValueMapCount(), &m_stCallback);
}

int process_events(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            return process_events_x(acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_OTHER_DEPEND:
        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
        case EN_MODULE_INIT:
        default:
            break;
    }

    return 1;
}

char *Events_GetEventName(unsigned int id)
{
    if ( id >= m_iEventsCount )
    {
        return NULL;
    }

    return m_astEvents[id].vevent;
}

