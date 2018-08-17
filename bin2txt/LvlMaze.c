#include "global.h"

#define FILE_PREFIX "LvlMaze"
#define NAME_PREFIX "lm"

/*
Title 	LvlMaze.txt File Guide
Description 	by Myhrginoc
Sent by 	
OVERVIEW:

This is the file that controls how many ds1 (rooms) and how large each ds1 are for random underground levels (mazes).

RELATED .TXT FILES:

This file is using:

Levels.txt


COLUMN DESCRIPTIONS :

Name 	descriptive, not loaded in game. Corresponds with Name field in Levels.txt.
Level 	ID from Levels.txt. Cave 1 is the Den of Evil, its associated treasure level is quest only.
Rooms 	the minimum number of .ds1 map sections that will make up the maze in Normal difficulty.

Rooms(N) 	the minimum number of .ds1 map sections that will make up the maze in Nightmare difficulty.

Rooms(H) 	the minimum number of .ds1 map sections that will make up the maze in Hell difficulty.
SizeX 	the size in the X direction of any component ds1 map section.

SizeY 	the size in the Y direction of any component ds1 map section.
Merge 	Possibly related to how adjacent .ds1s are connected with each other, but what the different values are for is unknown.
Beta 	Included in the original Diablo II beta tests and in the demo version..

*/

/*
A.Name = 描述性字段，不出现于游戏中。对应Levels.txt中的‘Name’字段。
B.Level = Levels.txt中ID。如Cave1--邪恶洞穴(Den of Evil)，关联的财富级别(treasure level)只是任务(quest)级。
C.Rooms = 普通难度下组成该迷宫(maze)的ds1地图片段(sections)的最小数量。
D.Rooms(N) = 噩梦难度下组成该迷宫(maze)的ds1地图片段(sections)的最小数量。
E.Rooms(H) = 地狱难度下组成该迷宫(maze)的ds1地图片段(sections)的最小数量。
F.SizeX = ds1地图片段在‘X’方向分量的尺寸大小。
G.SizeY = ds1地图片段在‘Y’方向分量的尺寸大小。
H.Merge = (TBD-不清楚)。
I.Beta = 是否包含在原版diablo2的测试版本和演示版本中。1=是，0=否。

补充说明：感谢Paul提供的一些相关信息。其中，‘SizeX’和‘SizeY’不一定取相同的值，但是尺寸必须与符合ds1片段(sections)。因为ds1网格起始坐标在(0,0)，一个‘SizeX=8，SizeY=8’的片段共有‘9*9=81’个小片(tiles)。
*/

typedef struct
{
    unsigned int vLevel;
    unsigned int vRooms;
    unsigned int vRoomsmybr1Nmybr2;
    unsigned int vRoomsmybr1Hmybr2;
    unsigned int vSizeX;
    unsigned int vSizeY;
    unsigned int vMerge;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "Name",
    NULL,
};

static char *m_apcNotUsed[] =
{
    "Beta",
    NULL,
};

static int LvlMaze_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "Name") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, iLineNo);
        }

        return 1;
    }

    return 0;
}

int process_lvlmaze(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Level, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Rooms, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Roomsmybr1Nmybr2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Roomsmybr1Hmybr2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SizeX, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SizeY, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Merge, UINT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnFieldProc = LvlMaze_FieldProc;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
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

