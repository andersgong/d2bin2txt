#include "global.h"

#define FILE_PREFIX "LvlSub"
#define NAME_PREFIX "ls"

/*
LvlSub.txt

Name: Description, reference only.

Type: This value is used in Levels.txt, in the column "SubType". You'll notice that in LvlSub.txt some rows use the same value, we can say they forms groups. If you count each row of a group starting from 0, then you'll obtain what is written in Levels.
txt, columns "SubTheme", "SubWaypoint" and "SubShrine". (added by Paul Siramy)
for more details see: this post.

File: What Ds1 is being used.

Expansion: 0 for classic, 1 for Expansion.

CheckAll: Unknown as all have 0.

BordType: -1, 0, 1 or 2 (wall types have 0, 1, or 2. Non wall types have -1)

Gridsize: 1 or 2 I'm assuming this means a block of tiles ie: 4x4. (see below)

Dt1Mask: For some rows, this is their place in LvlTypes.txt. The Dt1 mask also includes the mask for the Floor.Dt1 of that level. (see Trials0 below)

Prob0: The probability of the Dt1 being spawned.

Trials0: This appears to be a chance of either a floor tile being spawned or the actual Dt1..

Max0: This appears to be how much will spawn in the Grid.

Prob1, Trials1 and so on, same as above.

Beta: 0 or 1



This addendum was written by Paul Siramy in regard to the "trials" columns.


I just did some tests. Here's how the game put Substitution Tiles, using LvlSub.txt :

In a level it place some "groups" of tiles. It means that usually when the game decide to place 1 substitution tile at a place, it place other ones just near around.

The rarity of these groups is controled by the ProbX column. The higher the value, the more groups will be placed in the level. Note that there can be less group than the value you set in ProbX. Apparently these groups are placed first, but they may be 
erased by other ds1 tiles, like a fallen camp. So don't set the ProbX to a too low value, as it sometimes happen in that case that no substitution tiles will appear.

For each group, it tries to place TrialsX substitution tiles, but the number of such tiles is capped at MaxX. So it's useless to set TrialsX < than MaxX. It probably works that way : the game choose a random number between 0 and TrialsX, and then 
compare it with MaxX value, caping it if necessary.

Why should one use higher TrialsX than MaxX ? To force the game to place a little more tiles. Example :

* I set TrialsX to 4 and MaxX to 4. I'll have 25% chances that the group will be composed of only 1 tile, 25% with 2 tiles, 25% with 3 tiles and 25% with 4 tiles.

* I set TrialsX to 6 and MaxX to 4. I'll have 50% chances that the group will be composed of 4 tiles, 17% with 1 tiles, 17% with 2 tiles and 17% with 3 tiles.

In conclusion, if you want few groups but with many substitution tiles, set ProbX to a low value (10), and TrialsX and MaxX to high values (30 20 for instance). On the contrary, if you prefer to disperse your substitutions tiles around the level, set 
ProbX to a high value (90) but TrialsX and MaxX to low value (4 2 for instance).



New Input, from a PM by I_only_pressed_Esc
I've been doing a bit of experimenting with Act1 wilderness border-inner walls generation.

I've found that Type 1 controls the actual border-inner wall generation to make it look "not square" and straight forward ie "wall hugging to find the next exit".

The ds1 cannot be edited as it is hardcoded to choose from god knows what. This is based on adding the ds1 to LvlPrest.txt and changing the dt1 mask.

The ds1 has a number of various tile grids 4x4 4x5 5x5 etc tiles that are picked to generate the border or inner walls. As the tile grids get bigger the variance increases.

The grids have a 1 tile border of a floor tile which obviously gets merged at generation of the level.

*/

typedef struct
{
    int vType;

    unsigned char vFile[60];

    int vCheckAll;
    int vBordType;
    int vDt1Mask;
    int vGridSize;

    int iPadding20;
    int iPadding21;
    int iPadding22;
    int iPadding23;
    int iPadding24;
    int iPadding25;
    int iPadding26;
    int iPadding27;
    int iPadding28;
    int iPadding29;

    int iPadding30;
    int iPadding31;
    int iPadding32;
    int iPadding33;
    int iPadding34;
    int iPadding35;
    int iPadding36;
    int iPadding37;
    int iPadding38;
    int iPadding39;

    int iPadding40;
    int iPadding41;
    int iPadding42;
    int iPadding43;
    int iPadding44;
    int iPadding45;
    int iPadding46;
    int iPadding47;
    int iPadding48;
    int iPadding49;

    int iPadding50;
    int iPadding51;
    int iPadding52;
    int iPadding53;
    int iPadding54;
    int iPadding55;
    int iPadding56;
    int iPadding57;
    int iPadding58;
    int iPadding59;

    int iPadding60;
    int iPadding61;
    int iPadding62;
    int iPadding63;
    int iPadding64;
    int iPadding65;
    int iPadding66;
    int iPadding67;
    int iPadding68;
    int iPadding69;

    int iPadding70;

    int vProb0;

    int vProb1;
    int vProb2;
    int vProb3;
    int vProb4;

    int vTrials0;

    int vTrials1;
    int vTrials2;
    int vTrials3;

    int vTrials4;

    int vMax0;

    int vMax1;
    int vMax2;
    int vMax3;
    int vMax4;

    int vExpansion;
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

static int LvlSub_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
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

int process_lvlsub(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Type, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, File, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CheckAll, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BordType, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Dt1Mask, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, GridSize, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob0, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob3, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Prob4, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Trials0, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Trials1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Trials2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Trials3, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Trials4, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Max0, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Max1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Max2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Max3, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Max4, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Expansion, INT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnFieldProc = LvlSub_FieldProc;
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

