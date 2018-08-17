#include "global.h"

#define FILE_PREFIX "lvlprest"
#define NAME_PREFIX "lp"

/*
Title 	LvlPrest.txt File Guide (v. 2)
Description 	by Xenast
Sent by 	
Lvlprest.txt

Name: Name of the level
*Reference only

Def: Related to Automap, must be a consecutive value

Levelid: The ID of the level from levels.txt
*Leave at 0 if the ds1 is not a preset level

Populate: 1 yes/0 no
If set to no monsters will not be able to spawn on the ds1, used for special maze rooms such as stairs leading up/down
*Causes Unhandled Exception if you add other monster objects when column is set to 0

Logicals: 1 yes/0 no
Setting to 1 allows walls to fade

Outdoors: 1 yes/0 no
Set to 1 for outdoor ds1's, 0 for indoor ds1's

Animate: 1 yes/0 no
Controls wether or not animated tiles will animate in the level

KillEdge: 1 yes/0 no
Removes the tiles bordering the east and south edge of the ds1 in game

FillBlanks: 1 yes/0 no
Setting to yes makes all blank tilespaces unwalkable

SizeX: Tells the x size of the map,
*Leave at 0 for preset areas since preset area size is defined in levels.txt

SizeY: Tells the y size of the map
*Leave at 0 for preset areas since preset area size is defined in levels.txt

Automap: 1 yes/0 no
Reveals full automap for level
*Only works for preset maps

Scan: 1 yes/0 no
Setting to yes allows warps to be selected

Pops: see below

PopPad: see below

Files: The amount of versions the map has, based on entries in File 1 to File 6 columns

File 1 to File 6: The location of the ds1 versions, leave at 0 for files that don't exist

Dt1mask: Number telling the game which tiles to use from lvltypes.txt

Beta:1 for beta, 0 not beta
*Reference only

Expansion:1 for expansion, 0 for non-expansion
*Reference Only


Pops and PopPad:

Pops are the special tiles with the Style (main-index) of 8 - 29. These remove the target style set from the map, revealing tiles in another layer.

    The Sequence number determines which Style set will be removed. These may be walls, floors or roof tiles.

    To operate, two "Pop tiles" are placed to form a square around the area of tiles to remove.

    The PopPad column in lvlprest.txt determines the line of the "trigger pad". It determines the number of sub-tile units south & west the trigger line is offset.

    You can only have one set of each style of pop. If you have 2 sets neither will operate properly, even if they have different target styles. So to have multiple pops in a level, you must use a different Style (main index) on each pair of pop tiles.



Note: When setting pops and poppad its best to reference an existing ds1 that contains the dt1's requiring these columns to help determine what value to use


Credits:
~SVR for Pop and PopPad explanation
~Go][um for the Logicals discovery

*/

/*
文件名解析：
Lvl：level，级别，在这里指地图。
Prest：preset，预设。
本文件描述了所有地图的预设信息。


回复

    2楼
    2011-09-28 23:55

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    3楼
    2011-09-28 23:55

    举报 |

    zqtjingzi
    小吧主
    12

Name：地图名，仅用作注释。

Def：在本文件中的位置。从0开始的连续整数。

LevelId：地图编号。与Levels.txt关联。为0的表示不是预设地图。

Populate：此地图中是否有怪物（包括NPC）。

Logicals：墙壁是否可通过。

Outdoors：此地图是否在户外。

Animate：此地图是否有动画。

KillEdge：此地图在右下方向的边界是否被删除。

FillBlanks：地图空白处是否可到达。

SizeX：地图的横坐标。

SizeY：地图的纵坐标。

Automap：是否自动生成地图，与AutoMap.txt关联。

Scan：地图是否可卷曲。

Pops：不知道什么含义。

PopPad：不知道什么含义。

Files：此地图的版本数。

File1-6：此地图各个版本对应的文件。

Dt1mask：指向LvlTypes.txt的数字。

Beta：无用参数，用作注释。

Expansion：是否是资料片所有。
*/

typedef struct
{
    int vDef;
    int vLevelId;
    int vPopulate;
    int vLogicals;
    int vOutdoors;
    int vAnimate;
    int vKillEdge;
    int vFillBlanks;
    int vExpansion;
    int iPadding9;

    int vSizeX;
    int vSizeY;
    int vAutoMap;
    int vScan;
    int vPops;
    int vPopPad;
    int vFiles;

    unsigned char vFile1[60];

    unsigned char vFile2[60];

    unsigned char vFile3[60];

    unsigned char vFile4[60];

    unsigned char vFile5[60];

    unsigned char vFile6[60];

    int vDt1Mask;
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

static int LvlPrest_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
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

int process_lvlprest(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Def, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LevelId, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Populate, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Logicals, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Outdoors, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Animate, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, KillEdge, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FillBlanks, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Dt1Mask, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SizeX, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SizeY, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AutoMap, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Scan, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Pops, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PopPad, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Files, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, File1, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, File2, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, File3, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, File4, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, File5, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, File6, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Expansion, INT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnFieldProc = LvlPrest_FieldProc;
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

