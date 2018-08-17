#include "global.h"

#define FILE_PREFIX "overlay"
#define NAME_PREFIX "ol"

/*
 Overlay.txt File Guide

Overview:
This txt controls the overlay graphics. These graphics are usually associated with casting animations, auras, curses/buffs and states.
Used by:
states.txt
skills.txt
missiles.txt
internally by the code

Column Descriptions:
Overlay
This column defines the name the game will associate with your overlay in the related files.
Filename
Where is the overlay? The game looks at dataglobaloverlays for a dcc file.
Version
Which game version? (0 = classic and 100 = expansion)
Frames
The game don't read it, instead the game reads the # of frames from the DCC file.
Character
Misleading, you can write on this field with no consequence if you want.
PreDraw
Does it show behind characters/monsters? (boolean, 0 = in front of the images, 1 = behind the images)

Least used Columns:
1ofN (Default value is 1)
1ofN is for random overlay states that may set the overlay to index+rand(1ofN). I have no idea how to use it.
Dir (Default value is 0)
Produces no noticeable effect. You can even write on this field with no consequence if you want.
Open (Default values between 0 and 1)
Beta (Default values between 0 and 1)
None of these columns produces a noticeable effect. You can even write on this field with no consequence if you want. They are probably comment fields related to the game development.

Position Settings:
Note: All values are in pixels.
Xoffset
Positive values (+) place it to the left and Negative Values (-) to the right the target base.
Yoffset
Positive values (+) place it bellow and Negative Values (-) above the target base.
Height1, Height2 , Height3 and Height4
These values modify the placement on Y-axis according to the unit height value (monstats2).
Note: If the value set on monstats2 is 0, then it uses Height2. (Thanks Nefarius for clarifying what heights are used for)
	Quote: 	
	
	
	This is actually a index in an array. That refers to the four height columns in Overlays.txt
Height1, Height2, Height3, Height4
Players always use Height2
A special case, if you set OverlayHeight to 0 ( the value returned by D2Common.10090 is decremented by 1 ), the special case -1 will
use a height 75 (i.e. the default ). 	
		

Note: Testing has shown that height 4 is only used by primeevils.

Animation Settings:
AnimRate
It controls how fast the animation play. Testing has show it this field controls how many frames of animation are played per 25 frames of time. i.e. number of frames per second .
LoopWaitTime (Default value is 0)
This column seems to produce no effect. Nefarius pointed that it is used by the game for some overlays that loop only after waiting for short period of time.
Note: Only "itemgleam, multigleam, npcalert, gleamtest3 and gleamtest4" have values on this.


Transparency and Light Settings:
Trans
It changes the overlay color accordingly to the value is set.
0 - Faded
1 - Half Solid with small black borders
2 - Entirely Solid with small black borders
3 - Entirely Solid without black borders (black = transparent)
4 - Darkened and Transparent (like a shadow)
5 - Entirely Solid with big black borders
6 - It looks like "2"...
7 - Whitened and Entirely Solid with small black boarders (high gamma)
8 - Like "3" but it flickers
9 - It looks like "2"...
InitRadius
It seems to control the light radius increase per frame. Never set this to 0 or less, or it crashes the game.
Radius
Controls the maximum light radius, must be bigger or equal to InitRadius. The Light radius only expands unfortunately...
Red, Green, Blue
They control the color of the light radius.

Settings with Unknown effects:
NumDirections (Default value is 1)
Produces no noticeable effect. You can even write on this field with no consequence if you want. The game reads the # of directions from the DCC file.
Note: Only "vulturedemonfeathers" overlay have a value of 4.
LocalBlood
Not used by vanilla. LocalBlood is only used if you edit data/color.txt and set the localblood global boolean to true. What it does is replace blood colors with the entires from GreenBlood.dat.
Note: In vanilla it's only used by two overlays "durieldead_rear" and "tentacleheadbloodripple".

Recommended Readings:
MagicMatze posted a nice guide on using overlays to display a custom messages back on 2004.

Also check the File Guides for:
States.txt
Skills.txt
Missiles.txt

Tips, Ideas and Suggestions:
1 - You can add an overlay to almost any skill by using the "castoverlay" column on skills.txt. You could even add the monster animation as an overlay and produce an illusion effect while it casts some spell.
2 - You can add overlays to the targets of some skills. This is done by adding the overlay to "srvoverlay". For example: vengeance could cause that neat overlay on "extravengeance" easily, if you want.
3 - Some missiles hit functions allows overlays. The classic 10/X (charged bolt function) being the most prominent example.
4 - How the overlay is played depends on how it has been called. Usually only overlays used by states.txt are repeated.*/

typedef struct
{
    char acPadding[2];
    unsigned char vFilename[64];//Where is the overlay? The game looks at data/global/overlays for a dcc file.
    unsigned short vversion;

    unsigned int vFrames;
    unsigned int vPreDraw;
    unsigned int v1ofN;

    unsigned char vDir;
    unsigned char vOpen;
    unsigned short vBeta;

    int vXoffset;
    int vYoffset;
    int vHeight1;
    int vHeight2;
    int vHeight3;
    int vHeight4;
    unsigned int vAnimRate;

    unsigned int vInitRadius;
    unsigned int vRadius;
    unsigned int vLoopWaitTime;

    unsigned char vTrans;
    unsigned char vRed;
    unsigned char vGreen;
    unsigned char vBlue;

    unsigned char vNumDirections;
    unsigned char vLocalBlood;
    char acPadding2[2];
} ST_LINE_INFO;

typedef struct
{
    unsigned char voverlay[32];
} ST_OVERLAY;

static char *m_apcNotUsed[] =
{
    "Character",
    NULL,
};

static char *m_apcInternalProcess[] =
{
    "overlay",
    NULL,
};

static unsigned int m_iOverlayCount = 0;
static ST_OVERLAY *m_astOverlay = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astOverlay, ST_OVERLAY);

static int OverLay_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "overlay") )
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

        strncpy(m_astOverlay[m_iOverlayCount].voverlay, acOutput, sizeof(m_astOverlay[m_iOverlayCount].voverlay));
        String_Trim(m_astOverlay[m_iOverlayCount].voverlay);
        m_iOverlayCount++;
        return 1;
    }

    return 0;
}

char *Overlay_GetOverlay(unsigned int id)
{
    if ( id >= m_iOverlayCount )
    {
        return NULL;
    }

    return m_astOverlay[id].voverlay;
}

int process_overlay(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Filename, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, version, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Frames, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PreDraw, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, 1ofN, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Dir, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Open, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Beta, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Xoffset, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Yoffset, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Height1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Height2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Height3, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Height4, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AnimRate, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InitRadius, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Radius, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LoopWaitTime, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Trans, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Red, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Green, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Blue, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, NumDirections, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LocalBlood, UCHAR);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iOverlayCount = 0;

            m_stCallback.pfnFieldProc = OverLay_FieldProc;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;
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

