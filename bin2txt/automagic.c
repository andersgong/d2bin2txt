#include "global.h"

#define FILE_PREFIX "automagic"

/*
Automagic.txt - v1.10 (and presumably 1.11x)
Composed by Quatl
(This information was already availible here, I didn't discover any of this. I only typed and formated it.)

OVERVIEW

This file controls auto-affix mods for item drops. Auto mods add magical properties to items without changeing their magic type. This file is very versitile, and gives you fairly fine control over when, and on what, various properties will appear. You 
can create groups of auto mods, and control mods by level. You can also set probibilities of various mods in a group appearing.

RELATED .TXT FILES

This file is useing:
* Properties.txt
* Itemtypes.txt

This file is used by:
* Weapons.txt ("auto prefix" column)
* Armor.txt ("auto prefix" column)

COLUMN DESCRIPTIONS :
______________________________________________________________________________

Name: String Comment
Blizzard lists the equivelent prefix/affix here. You can use what ever you wish here though. Handy for keeping track of groups.

______________________________________________________________________________

version: 100=LOD Only, 0=Classic & LOD
Which game versions allow this autoprefix spawn.

______________________________________________________________________________

spawnable: Boolean Value
Does this autoprefix spawn in the game. You can dissable this line by setting this to 0, or enable it with 1

______________________________________________________________________________

rare: Boolean Value
Does this autoprefix spawn on rare (that is yellow colored) items in the game. You can dissable this modifier on rares by setting this to 0, or enable it with 1 This allows some fine control if combinations of effects that stack would make a rare too 
powerful.

______________________________________________________________________________

level: Numeric Value
The minimum level this autoprefix can be chosen. Also used to control by level grouping of mods. You can use this to combine multiple rows so that autoprefixes are assigned based on the level of the treasure drop. See group column description below. 
Additional information can be found in the 1.09 version file guide

______________________________________________________________________________

maxlevel: Numeric Value
The maximum level this autoprefix can be chosen.

______________________________________________________________________________

levelreq: Numeric Value
Level requirement push for this autoprefix. This value is added to the levelreq stat of the item generated with this mod.

______________________________________________________________________________

class: Class Code
If this is a modifier for a specific class, the class code should be entered here. This should be used by the drop calculations of class specific items (I'm not certain of this.) Can be used to make modifiers like "+ skill (class only)", or "+ skill tab
". It also enables the next column. [Class codes are: ama, nec, sor, pal, bar, dru, ass]

______________________________________________________________________________

classlevelreq: Numeric Value
If class is set, this should allow a seperate level req push for this class. This is a polite thing to do, as other classes gain no advantage from class specific modifiers. I am uncertain that this actualy works.

______________________________________________________________________________

frequency: Numeric Value
For autoprefix groups, what is the reletive probibility of this autoprefix, vs other valid choices. Higher numbers are more common than lower ones. The 1.09 version file guide has some formuae relateing to this.

______________________________________________________________________________

group: Numeric Value
Lines containing the same value in this column are treated as a group. Only one auto prefix from a group is chosen. levelreq, classlevelreq, and frequency modify the behavior of groups. The 1.09 version file guide has a very nice tutorial about how to 
set up groups.

The group number must also be entered in the "auto prefix" column of each entry in Weapons.txt or Armor.txt in order for the property to appear.
______________________________________________________________________________

mod1code - mod3code: Property Code from Properties.txt
These determine the actual properties which make up this autoprefix. Each autoprefix can include up to three modifiers.

modXparam, modXmin, modXmax Numeric Value
For each modXcode, these set the quantities for each property. See Properties.txt for details on how to set values for various modifiers. Note: modXparam fields do suport calcs ( see Farmulae Guide.) Seems of limited utility to me, but is an opretunity 
for funkiness.

______________________________________________________________________________


transform: Boolean Value
Enables colorization of items with this autoprefix. If set to 1, the item will be palet shifted useing the color code in transformcolor, set to 0 (or leave empty) to dissable.

transformcolor: Color Code
If transform = 1, this sets the color code for the transformation.
Transform Color -> Code (from colors.txt)
White -> whit
Light Grey -> gry
Dark Grey -> dgry
Black -> blac
Light Blue -> blu
Dark Blue -> dblu
Crystal Blue -> cblu
Light Red -> lred
Dark Red -> dred
Crystal Red -> cred
Light Green -> lgrn
Dark Green -> dgrn
Crystal Green -> cgrn
Light Yellow -> lyel
Dark Yellow -> dyel
Light Gold -> lgld
Dark Gold -> dgld
Light Purple -> lpur
Dark Purple -> dpur
Orange -> oran
Bright White -> bwht

______________________________________________________________________________

itype1 - itype7: Type Code from Itemtypes.txt
"Include type", place an item type code in any of these columns to allow that item type to recieve mods from this line. See Note Below.

etype1 - etype3: Type Code from Itemtypes.txt
"Exclude type", place an item type code in any of these columns to prevent that item type recieve recieve mods from this line. See Note Below.

Note: These fields are redundant, but can cause problems if set wrong. Since you must set a group number in the relevent text files for auto prefixes to function (and those rows are typed items already.) Set itype1 = weap, itype2 = armo, and itype3 = 
misc and use groups. See group column in this file.

(This is different from 1.09, I supose because of the way class specific items work. It is more versitile this way, but more work and more prone to error.)

______________________________________________________________________________

divide: Numeric Value
The items price is devided by this value.

multiply: Numeric Value
The items price is multiplied by this value.

add: Numeric Value
This value is added to the items price.

______________________________________________________________________________


-------------------------------
Another one. It's nice to have easy to read refrence materials around. I'll do more as I have time. If anyone has corrections, sugestions, or additional information that should be here please let me know.

-Quatl

*/

typedef struct
{
    unsigned char vName[32];

    unsigned short wTblIndex;
    unsigned short vversion;

    unsigned int vmod1code;
    unsigned int vmod1param;
    unsigned int vmod1min;
    unsigned int vmod1max;

    unsigned int vmod2code;
    unsigned int vmod2param;
    unsigned int vmod2min;
    unsigned int vmod2max;

    unsigned int vmod3code;
    unsigned int vmod3param;
    unsigned int vmod3min;
    unsigned int vmod3max;

    unsigned char vspawnable;
    unsigned char iPadding21;
    unsigned short vtransformcolor;

    unsigned int vlevel;

    unsigned int vgroup;

    unsigned int vmaxlevel;

    unsigned char vrare;
    unsigned char vlevelreq;
    unsigned char vclassspecific;   //playerclass
    unsigned char vclass;   //playerclass

    unsigned short vclasslevelreq;
    unsigned short vitype1;  //itemtypes

    unsigned short vitype2;
    unsigned short vitype3;

    unsigned short vitype4;
    unsigned short vitype5;
    unsigned short vitype6;
    unsigned short vitype7;

    unsigned short vetype1;
    unsigned short vetype2;
    unsigned short vetype3;
    unsigned short vetype4; //实际无用，bin文件不同不用管

    unsigned short vetype5; //实际无用，bin文件不同不用管
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

static char *AutoMagic_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strncpy(pcKey, pstLineInfo->vName, sizeof(pstLineInfo->vName));
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

static int AutoMagic_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "classspecific") )
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
    else if ( !strcmp(acKey, "itype1") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vitype1);
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
    else if ( !strcmp(acKey, "itype2") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vitype2);
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
    else if ( !strcmp(acKey, "itype3") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vitype3);
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
    else if ( !strcmp(acKey, "itype4") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vitype4);
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
    else if ( !strcmp(acKey, "itype5") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vitype5);
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
    else if ( !strcmp(acKey, "itype6") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vitype6);
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
    else if ( !strcmp(acKey, "itype7") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vitype7);
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
    else if ( !strcmp(acKey, "etype1") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vetype1);
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
    else if ( !strcmp(acKey, "etype2") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vetype2);
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
    else if ( !strcmp(acKey, "etype3") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vetype3);
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
    else if ( !strcmp(acKey, "etype4") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vetype4);
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
    else if ( !strcmp(acKey, "etype5") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vetype5);
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
    else if ( !strcmp(acKey, "mod1code") )
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

    return result;
}

int process_automagic(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Name, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, version, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod1code, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod1param, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod1min, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod1max, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod2code, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod2param, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod2min, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod2max, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod3code, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod3param, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod3min, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mod3max, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, spawnable, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, transformcolor, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, level, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, group, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, maxlevel, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rare, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, levelreq, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, classspecific, UCHAR);   //playerclass
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, class, UCHAR);   //playerclass

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, classlevelreq, USHORT);
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
            MODULE_DEPEND_CALL(playerclass, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(itemtypes, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(colors, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(properties, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            //m_stCallback.pfnGetKey = AutoMagic_GetKey;
            m_stCallback.pfnConvertValue = AutoMagic_ConvertValue;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

