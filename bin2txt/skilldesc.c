#include "global.h"

#define FILE_PREFIX "skilldesc"
#define NAME_PREFIX "sd"

/*
Title 	SkillDesc.txt File Guide (v. 2)
Description 	by Ric Faith
Sent by 	
SkillDesc.txt File Guide
& descline reference
by RicFaith

Overview:
Skilldesc is an important part of the skill making process. It gives the modder the ability to fully customize the skill descriptions of his skills. It is also important for the placement and arrangement of skills on the skilltrees.

Files used by SkillDesc:
Missiles.txt
Monstats.txt
Skills.txt

String.tbl
Expansionstring.tbl
Patchstring.tbl

Note:
Patchstring > Expansionstring > String
This means that any entry in Patchstring will overwrite the an entry of the same index in Expansionstring or String, and any entry in Expansionstring will overwrite another entry sharing the same name in String. Thus to find the most recent string, you 
should check in the order stated above.

Naming convention:
So as to make certain things clearer, and to simplify this File Guide, here are some naming conventions that I will use while describing:

string(s) - refers to an entry in any of the .tbl files
tree(s) or page(s) - the skill trees available to the character
shortcut(s) - the list of skills that show up when you press 'S'
charscreen - character screen, shows up when you press 'C'
selected skill - one of the two active skills that are set to your mouse buttons

--------------------

skilldesc
name of the skilldesc, referenced by skills.txt (col D).

--------------------

SkillPage
Allowed values = 0 - 3
Determines which page the skill will show up.
0 - not on trees
1 - bottom page
2 - middle page
3 - top page

--------------------

SkillRow
Allowed values = 0 - 6
Determines which row the skill will show up.
0 - not on page
1 - top row
6 - bottom row

--------------------

SkillColumn
Allowed values = 0 - 3
Determines which column the skill will show up.
0 - not on page
1 - left column
2 - middle column
3 - right column

--------------------

ListRow
Allowed Values = -1 - 4
Determines which row the skill will show up in the shortcuts
-1 & every other value - skill will not shot up
0 - reserved for basic attacks and unsummon
1-3 - for skills, from bottom up, usually the same value as SkillPage, but not necessarily
4 - reserved for Identify and Town Portal

--------------------

ListPool
Allowed Values = 0 - 2
Used only by Identify and Town Portal scrolls.
0 - Everything else
1 - scroll of identify
2 - scroll of town portal

--------------------

IconCel
Allowed Values = 0 - X (user defined, read below)
Used to determine the icons (usable and unusable) used by the skill. Value that is put here determines the usable icon, and the next icon will be the unusable icon. Icons always come in pairs, so if you're making your own skill icons, do put them in the 
right order.

If skill is a class skill, icons will be taken from :
dataglobaluispellsXXskillicon.dc6 where XX is -
XX Class
am Amazon
as Assassin
ba Barbarian
dr Druid
ne Necromancer
pa Paladin
so Sorceress

If skill is not a class skill, icons will be taken from :
dataglobaluispellsskillicon.dc6

--------------------

str name
This is the string that is used as the skill name in the trees, the shortcuts and the selected skill.

--------------------

str short
This is the string that is used as the skill description in the shortcuts and the selected skill.

--------------------

str long
This is the string that is used as the skill description in the trees.

--------------------

str alt
This is the string that is used as the skill name in the charscreen.

--------------------

str mana
Usual values = StrSkill3 or (blank)
Even if your skill has no mana cost, putting a string here will not display a 0 mana cost. You can use StrSkill3 ("Mana Cost: ") or your own fancy string for mana cost. Eg. Raven has its own mana cost string ("Mana Cost Per Raven")

--------------------

descdam
Allowed values = 1 - 24 or (blank)
If your skill deals damage, then you need to use this to tell skilldesc how to go about calculating the damage. Here is a list of the various values for descdam.
descdam   description
1   attack
2   kick
3   throw
4   left hand throw
5   check dmg cols
6   arrow with explode
7   attacks w dmg increases
8   inferno type dmg
9   blaze,firestorm
10   smite
11   vengeance
12   blessed hammer
13   double throw
14   hunger
15   kick combo
16   kick AoE
17   cstrike
18   royal strike
19   2h attacks
20   assn chargeups
21   lightbolt
22   javelin with explode
23   rabies
24   blade fury


Some skills have their own special descdam, so you should check the most relevant skill to yours to see if it requires something different, otherwise it's almost always 5.

--------------------

ddam calc1 / ddam calc2
If your skill has an increase in damage, you'll need to fill in one or both of these columns. The resulting damage is given by this formula:
Damage = (Original Damage) * (100 + ddam calc1)/100 + ddam calc2
Thus if your skill has a %age increase in damage, put the increase or calc in ddam calc1. Or if your skill has a flat +X increase in damage, put the increase or calc in ddam calc2.

--------------------

pXdmelem / pXdmmin / pXdmmax where X = 1 - 3
These are only used by the Assassin charge-up attacks. These columns describe the necessary details.
pXdmelem - the element type for that charge
pXdmmin - minimum damage for that charge
pXdmmax - maximum damage for that charge

--------------------

descatt
Allowed values = 1 - 5 or (blank)
If your skill has an increase in attack rating, you will need to fill this column. I can't see any difference between 1 and 2, so I guess you should look at the skill that is closest to yours.
descatt   description
1   increase in attack rating
2   increase in attack rating
3   throw
4   left hand throw
5   kick finishers



--------------------

descmissileX where X = 1 - 3
In the case where your damage, duration or other values are taken from missiles, you will need to put the primary missile in descmissile1. Currently, it seems that the descmissile2 and descmissile3 are only used by assassin charge-ups, but I think you 
should be able to put other missiles here for description too.

--------------------------------------------------------------------------------

From here, the real stuff begins. Since it is highly repetive in nature, I will explain it differently.

There are 3 main sections for descriptions, desc, dsc2 and dsc3. First a breakdown of where these descriptions show up.

desc - shows up in trees, shortcuts and selected skill.
dsc2 - shows up in trees, shortcuts and selected skill.
dsc3 - shows up in trees only.

Next, I'll describe what the different descriptions show.

Shortcuts and Selected skill - desc and dsc2 show current level stats only.

Trees -
desc show current and next level stats
dsc2 show current stats
dsc3 show current stats (but is currently used for synergies)
For a more precise layout of the stats, see Appendix A below.

--------------------

If you leave a set blank, they will simply be ignored. So you can fill any
sets of columns, the blank ones will be skipped.

Now, we will cover the different parts of a description. I will use just 1 set of columns for simplicity, the effect is the same for all columns. Each set of columns will have:
descline, desctexta, desctextb, desccalca, desccalcb
with various numbers appended to them.

--------------------

descline
Allowed values = 1 - 75 or (blank)
This tells skilldesc the format of the description, which values to take and which order to place them. Read further for an example. All desclines and their usage can be found in Appendix B.

--------------------

desctexta / desctextb
These are strings that may be filled or left blank. Some desclines are not picky about whether these are filled, but since there are so many desclines, you can find something that matches your needs quite closely.

--------------------

desccalca / desccalcb
These are numbers or calcs that may be filled or left blank. Similar to desctexts, desccalcs may be treated as empty or 0 if not present, so if you don't need the extra space, choose a suitable descline.

--------------------

In Appendix B, I used the following notation:
S1 & S2 refer to desctexta and desctextb respectively. S for String because that is what these two columns are.
C1 & C2 refer to desccalca and desccalcb respectively. C for Calc
I used S1,S2,C1,C2 because these are immediately identifiable. Most of the desclines come with fixed text. You can change the 'fixed' part in the .tbl files, but you'll be changing them for all skills that use that descline. Anyway there are so many 
workarounds that you really don't have to change it, just use another descline.

Example 1:
I'll use descline 3 as an example.
Descline 3 gives the following output: S1C1S2
This means that if my input is
S1 = "Good"
S2 = "Nothing"
C1 = 4
C2 = 365
The result will be "Good4Nothing". There are no spaces, because the output merely concatenates everything. C2 is ignored because it is not included in the output.
If S1 was blank, the output is "4Nothing"
If S2 was blank, the output is "Good4"
If C1 was blank, the output is "GoodNothing"

I'm sure that is quite clear, now on to some of the more complex desclines

Example 2:
Some desclines don't use string or calcs, so I'll show a nice one for poison skills.
Descline 14 has the following output:
Poison Damage: X-Y
over Z seconds

Yes, some desclines produce more than one line, but they're usually a little hardcoded. This descline reads the values of EMin, EMax and ELen from skills.txt and does some math before displaying the values.

For this example, I'll use Poison Nova Lvl 1
From skills.txt:
HitShift = 4
EMin = 14
EMax = 25
ELen = 50

First, some things you have to know about the values in Len, this value is in frames, and Diablo has 25 frames to a second. Thus Poison Nova does damage for 2 seconds.

Next, for HitShift, this is because Blizzard uses 8 bits of accuracy for HitPoints, Mana and Stamina. HitShift for Poison Nova is 4, so the damage is "divided" by 2^4 = 16.

Anyway, back to the descline and the formula.
The output has X,Y and Z, this is because even these values are not raw values. Here's how we calculate them:
X = EMin*ELen/16 = 43
Y = EMax*ELen/16 = 78
Z = ELen/25 = 2

Last thing to note, Blizzard rounds everything down to the integer. So 3/4 = 0, 41/40 = 79/40 = 1.

In the end, we get the final output:
Poison Damage: 43-78
over 2 seconds

--------------------

Conclusion:

Skilldesc can get a bit tricky, and sometimes some things just don't work so well. My advice is that even though some of the desclines may look perfect for your skill description, if they don't work, try using some of the more common ones. Some of the 
desclines are not used in skilldesc, I found them by trying every number. Some are only used by one skill, so I classed it as being specific, though they may still be able to work, don't get too worked up when it doesn't. In my opinion, you can do a lot 
with just the basic few. You can do your own calcs and display a raw number instead of leaving it to the hardcoded desclines. But it's up to the individual modder icon_smile.gif

----------------------------------------

Appendix A: Layout of Skill Description on the Tree.

-----

str name
str long

(all dsc2 lines)

Current Level: X
(all desc lines)

Next Level: X+1
(all desc lines)

(all dsc3 lines)

-----

As mentioned earlier, synergies are using dsc3 lines, so they'll be shown right at the bottom. If you want some stats that only show for current level, use dsc2. If you want stats that show for current and next levels, use desc.

----------------------------------------

Appendix B: List of desclines

This list is a bit long (75 entries), so I put it in a code. I'm thinking of making an excel page that allows you to put values in to see the result, but there may or may not be a need for it. I'll see how it goes. If you think that it'd be good, PM me 
so I know there's a demand.

Explanations:
descline = descline number
formula used = result from the inputs
calc/desc = in the event that the numbers are not directly related to inputs S1,S2,C1,C2, I explained it here
elem = if this descline refers to a specific elem, because of the calc method or if it can take any elem based on the EType in skills.txt, then I'll state it here
reference = the files it references, such as skills.txt, missiles.txt etc.
descline   formula   used   calc/desc   elem   reference   specific
1   null   1   almost all damaging skills use this         
2   S1+C1S2   1            
3   S1C1S2   1            
4   S1+C1   1            
5   S1C1   1            
6   +C1S1   1            iron skin
7   C1S1   1            
8   ^ S1S2   1   Automatically displays AR Bonus         
9   S1S2Damage: +C2   1   Automatically displays Dmg Bonus         
10   (Elem) Damage: X-Y   1   X,Y = Dmg   any   skills   
11   ^ S1S2   1   Describes a skill dmg?         
12   S1: C1 seconds   1            
13   Life: C1   1   For displaying summon's life         
14   Poison Damage: X-Ynover Z seconds   1   X,Y=(Dmg)*Len/16, Z=len/25   pois   skills   
15   S1:S2   0            
16   Duration: (C1/25)-(C2/25) seconds   1   C1,C2 in frames         mind blast
17   S2S1C1-C2 per second   1            fists of fire
18   S1   1            
19   S2S1(C1*2/3) yards   1   C1 in Game length units         
20   S1+C1 percentS2   0            
21   S1C1 percentS2   0            
22   Average Fire Damage: X-Y per second   1   X,Y=(dmg*7/3) (hitshift 4)   fire   missiles   
23   Duration: X seconds   1   X = (range/25)      missiles   
24   S1: X-Y   1   X,Y=(dmg/2)      skills   
25   S1S2   1            
26   Average (Elem) Damage: X-Y per second   1   X-Y=(dmg*25/16) (hitshift 4)   any   skills   
27   Average Fire Damage: X-Y per second   1   X,Y=(dmg*14/3) (hitshift 4)   fire   skills   
28   Radius: 1 Yard   1   HC, game value can be changed      skills   fire ball
29   X Yards   1   X=(range*2/3)      missiles   fire wall
30   Fire Duration: X   1   X=(submissile1.range/25)   fire   missiles   fire wall
31   S1(C1/25) seconds   1   C1 in frames         
32   S1S2+C1 percent   1            
33   S1S2   1            skel mastery
34   Damage: X-Y   1   X,Y=monster damage /w bonuses      monstats,skills   raise skel
35   S1: C1-C2   1            fire golem
36   C1(S1 or S2)   1   To determine plurality         
37   S1(C1*2/3) yards   1   C1 in Game length units         
38   S1C1-C2S2   1            
39   null   1   Used by Clay, Blood, Iron Golems         
40   (C1:Color)S2S1   1   Color Codes below         
41   Fire Damage: C1-C2   1      fire      fire golem
42   S1: +C1.C2 S2   1            inferno sentry
43   S1(C1/25)-(C2/25)S2   1            holy fire
44   S1(C1/256)-(C2/256)S2   0   C1,C2 used for true HP/MP/SP display         
45   Thorns Damagen1 percent damage returned   0   HC         
46   S1   0            
47   S1C1-C2   1            holy bolt
48   Magic Damage: X-Y   1   X,Y=Dmg   mag   skills   blessed hammer
49   S1: X-Y   1   X,Y=Dmg (used for smite dmg by HShield)      skills   holy shield
50   S1: X-Y   1   X,Y=(hitsubmissile1.dmg)      missiles   FoH
51   S1   1            
52   S1+C1-C2S2   1            
53   null,HC for isc?   1            
54   null,HC for ibk?   1            
55   null,HC for tsc?   1            
56   null,HC for tbk?   1            
57   S1+(C1/25) seconds   1   C1 in frames         lycanthropy
58   S1S2+C1-C2   0            
59   S2S1C1-C2   1            inferno sentry
60   S1+(C1/256)S2   0   C1 used for true HP/MP/SP display         
61   S1(C1/256)S2   1   C1 used for true HP/MP/SP display         blade fury
62   S1S2C1-C2   1            
63   S1: +C1% S2   1            
64   S1: +C1/C2 S2   0            
65   S1: S2   0            
66   S1(C1)S1   1   S1 has a (%d%%) where C1 will be         
67   S1: +C1 S2   1            
68   C1S1S2   1            sacrifice
69   S1: S2 C1   0            
70   S1S2+C1   1            
71   S1: S2   1            
72   +C1/C2 S1   1            
73   C1/C2 S1   1   eg 3/4 Weap Dmg for Multishot         
74   S1   0            
75   S1   0            



----------------------------------------

Appendix C: Color Codes

The values that you can put in the C1 column for skilldesc 40 and a couple of others can be found here:
0 - Light Gray (normal text)
1 - Red
2 - Bright Green (Set Items)
3 - Blue (Magic Items)
4 - Gold (Unique Items)
5 - Dark Gray (Socketed/Ethereal Items)
6 - Transparent (Text Doesn't Show)
7 - Tan
8 - Orange (Crafted Items)
9 - Yellow (Rare Items)

*/

typedef struct
{//total 288 bytes
    unsigned short wSkillDesc;
    unsigned char vSkillPage;
    unsigned char vSkillRow;

    unsigned char vSkillColumn;
    unsigned char vListRow;
    unsigned char vListPool;
    unsigned char vIconCel;

    //0-9999 string.txt 10000-19999 patchstring.txt 20000- expansionstring.txt
    unsigned short vstrmyspname;
    unsigned short vstrmyspshort;

    unsigned short vstrmysplong;
    unsigned short vstrmyspalt;

    unsigned short vstrmyspmana;
    ////////////////////////////////////////////
    unsigned short vdescdam;

    unsigned short vdescatt;
    char acPadding20[2];

    unsigned int vddammyspcalc1;    //skilldesccode
    unsigned int vddammyspcalc2;

    unsigned char vp1dmelem; //elemtypes
    unsigned char vp2dmelem; //elemtypes
    unsigned char vp3dmelem; //elemtypes
    char acPadding2;

    unsigned int vp1dmmin;  //skilldesccode
    unsigned int vp2dmmin;
    unsigned int vp3dmmin;
    unsigned int vp1dmmax;
    unsigned int vp2dmmax;
    unsigned int vp3dmmax;

    unsigned short vdescmissile1;   //missiles
    unsigned short vdescmissile2;   //missiles

    unsigned short vdescmissile3;   //missiles
    unsigned char vdescline1;
    unsigned char vdescline2;

    unsigned char vdescline3;
    unsigned char vdescline4;
    unsigned char vdescline5;
    unsigned char vdescline6;

    unsigned char vdsc2line1;
    unsigned char vdsc2line2;
    unsigned char vdsc2line3;
    unsigned char vdsc2line4;

    unsigned char vdsc3line1;
    unsigned char vdsc3line2;
    unsigned char vdsc3line3;
    unsigned char vdsc3line4;

    unsigned char vdsc3line5;
    unsigned char vdsc3line6;
    unsigned char vdsc3line7;
    unsigned char bPadding20;

    //0-9999 string.txt 10000-19999 patchstring.txt 20000- expansionstring.txt
    unsigned short vdesctexta1;
    unsigned short vdesctexta2;

    unsigned short vdesctexta3;
    unsigned short vdesctexta4;

    unsigned short vdesctexta5;
    unsigned short vdesctexta6;

    unsigned short vdsc2texta1;
    unsigned short vdsc2texta2;

    unsigned short vdsc2texta3;
    unsigned short vdsc2texta4;

    unsigned short vdsc3texta1;
    unsigned short vdsc3texta2;

    unsigned short vdsc3texta3;
    unsigned short vdsc3texta4;

    unsigned short vdsc3texta5;
    unsigned short vdsc3texta6;

    unsigned short vdsc3texta7;
    unsigned short vdesctextb1;

    unsigned short vdesctextb2;
    unsigned short vdesctextb3;

    unsigned short vdesctextb4;
    unsigned short vdesctextb5;

    unsigned short vdesctextb6;
    unsigned short vdsc2textb1;

    unsigned short vdsc2textb2;
    unsigned short vdsc2textb3;

    unsigned short vdsc2textb4;
    unsigned short vdsc3textb1;

    unsigned short vdsc3textb2;
    unsigned short vdsc3textb3;

    unsigned short vdsc3textb4;
    unsigned short vdsc3textb5;

    unsigned short vdsc3textb6;
    unsigned short vdsc3textb7;
    ////////////////////////////////////////////

    //char acPadding4[136];
    unsigned int vdesccalca1;   //skilldesccode
    unsigned int vdesccalca2;
    unsigned int vdesccalca3;
    unsigned int vdesccalca4;
    unsigned int vdesccalca5;
    unsigned int vdesccalca6;
    unsigned int vdsc2calca1;
    unsigned int vdsc2calca2;
    unsigned int vdsc2calca3;
    unsigned int vdsc2calca4;
    unsigned int vdsc3calca1;
    unsigned int vdsc3calca2;
    unsigned int vdsc3calca3;
    unsigned int vdsc3calca4;
    unsigned int vdsc3calca5;
    unsigned int vdsc3calca6;
    unsigned int vdsc3calca7;

    unsigned int vdesccalcb1;
    unsigned int vdesccalcb2;
    unsigned int vdesccalcb3;
    unsigned int vdesccalcb4;
    unsigned int vdesccalcb5;
    unsigned int vdesccalcb6;
    unsigned int vdsc2calcb1;
    unsigned int vdsc2calcb2;
    unsigned int vdsc2calcb3;
    unsigned int vdsc2calcb4;
    unsigned int vdsc3calcb1;
    unsigned int vdsc3calcb2;
    unsigned int vdsc3calcb3;
    unsigned int vdsc3calcb4;
    unsigned int vdsc3calcb5;
    unsigned int vdsc3calcb6;
    unsigned int vdsc3calcb7;
} ST_LINE_INFO;

typedef struct
{
    char vskilldesc[32];
} ST_SKILL_DESC;

static char *m_apcInternalProcess[] = 
{
    "skilldesc",
    "eol",
    NULL,
};

static unsigned int m_iSkillDescCount = 0;
static ST_SKILL_DESC *m_astSkillDesc = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astSkillDesc, ST_SKILL_DESC);

static int SkillDesc_FieldProc_Pre(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "skilldesc") )
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

        strncpy(m_astSkillDesc[m_iSkillDescCount].vskilldesc, acOutput, sizeof(m_astSkillDesc[m_iSkillDescCount].vskilldesc));
        String_Trim(m_astSkillDesc[m_iSkillDescCount].vskilldesc);
        m_iSkillDescCount++;
        return 1;
    }
    else if ( !strcmp(acKey, "eol") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static int SkillDesc_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "skilldesc") )
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
    else if ( !strcmp(acKey, "eol") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

char *SkillDesc_GetDesc(unsigned int id)
{
    if ( id >= m_iSkillDescCount )
    {
        return NULL;
    }

    return m_astSkillDesc[id].vskilldesc;
}

static int SkillDesc_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int id;
    int result = 0;

    if ( !strcmp(acKey, "ListRow") && 255 == pstLineInfo->vListRow )
    {
        strcpy(acOutput, "-1");
        result = 1;
    }
    else if ( !strcmp(acKey, "str name") )
    {
        pcResult = String_FindString_2(pstLineInfo->vstrmyspname, "dummy", "x");
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
    else if ( !strcmp(acKey, "str short") )
    {
        pcResult = String_FindString_2(pstLineInfo->vstrmyspshort, "dummy", "x");
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
    else if ( !strcmp(acKey, "str long") )
    {
        pcResult = String_FindString_2(pstLineInfo->vstrmysplong, "dummy", "x");
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
    else if ( !strcmp(acKey, "str alt") )
    {
        pcResult = String_FindString_2(pstLineInfo->vstrmyspalt, "dummy", "x");
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
    else if ( !strcmp(acKey, "str mana") )
    {
        pcResult = String_FindString_2(pstLineInfo->vstrmyspmana, "dummy", "x");
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
    else if ( 1 == sscanf(acKey, "desctexta%d", &id) )
    {
        unsigned short *psSkill = (short *)&pstLineInfo->vdesctexta1;
        pcResult = String_FindString_2(psSkill[id - 1], "dummy", "x");
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
    else if ( 1 == sscanf(acKey, "dsc2texta%d", &id) )
    {
        unsigned short *psSkill = (short *)&pstLineInfo->vdsc2texta1;
        pcResult = String_FindString_2(psSkill[id - 1], "dummy", "x");
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
    else if ( 1 == sscanf(acKey, "dsc3texta%d", &id) )
    {
        unsigned short *psSkill = (short *)&pstLineInfo->vdsc3texta1;
        pcResult = String_FindString_2(psSkill[id - 1], "dummy", "x");
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
    else if ( 1 == sscanf(acKey, "desctextb%d", &id) )
    {
        unsigned short *psSkill = (short *)&pstLineInfo->vdesctextb1;
        pcResult = String_FindString_2(psSkill[id - 1], "dummy", "x");
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
    else if ( 1 == sscanf(acKey, "dsc2textb%d", &id) )
    {
        unsigned short *psSkill = (short *)&pstLineInfo->vdsc2textb1;
        pcResult = String_FindString_2(psSkill[id - 1], "dummy", "x");
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
    else if ( 1 == sscanf(acKey, "dsc3textb%d", &id) )
    {
        unsigned short *psSkill = (short *)&pstLineInfo->vdsc3textb1;
        pcResult = String_FindString_2(psSkill[id - 1], "dummy", "x");
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
    else if ( !strcmp(acKey, "p1dmelem") )
    {
        pcResult = ElemTypes_GetElemStr(pstLineInfo->vp1dmelem);
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
    else if ( !strcmp(acKey, "p2dmelem") )
    {
        pcResult = ElemTypes_GetElemStr(pstLineInfo->vp2dmelem);
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
    else if ( !strcmp(acKey, "p3dmelem") )
    {
        pcResult = ElemTypes_GetElemStr(pstLineInfo->vp3dmelem);
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
    else if ( !strcmp(acKey, "descmissile1") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vdescmissile1);
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
    else if ( !strcmp(acKey, "descmissile2") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vdescmissile2);
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
    else if ( !strcmp(acKey, "descmissile3") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vdescmissile3);
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
    else if ( !strcmp(acKey, "ddam calc1") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vddammyspcalc1);
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
    else if ( !strcmp(acKey, "ddam calc2") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vddammyspcalc2);
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
    else if ( !strcmp(acKey, "p1dmmin") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vp1dmmin);
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
    else if ( !strcmp(acKey, "p2dmmin") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vp2dmmin);
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
    else if ( !strcmp(acKey, "p3dmmin") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vp3dmmin);
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
    else if ( !strcmp(acKey, "p1dmmax") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vp1dmmax);
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
    else if ( !strcmp(acKey, "p2dmmax") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vp2dmmax);
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
    else if ( !strcmp(acKey, "p3dmmax") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vp3dmmax);
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
    else if ( !strcmp(acKey, "desccalca1") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdesccalca1);
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
    else if ( !strcmp(acKey, "desccalca2") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdesccalca2);
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
    else if ( !strcmp(acKey, "desccalca3") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdesccalca3);
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
    else if ( !strcmp(acKey, "desccalca4") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdesccalca4);
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
    else if ( !strcmp(acKey, "desccalca5") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdesccalca5);
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
    else if ( !strcmp(acKey, "desccalca6") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdesccalca6);
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
    else if ( !strcmp(acKey, "dsc2calca1") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc2calca1);
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
    else if ( !strcmp(acKey, "dsc2calca2") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc2calca2);
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
    else if ( !strcmp(acKey, "dsc2calca3") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc2calca3);
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
    else if ( !strcmp(acKey, "dsc2calca4") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc2calca4);
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
    else if ( !strcmp(acKey, "dsc3calca1") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calca1);
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
    else if ( !strcmp(acKey, "dsc3calca2") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calca2);
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
    else if ( !strcmp(acKey, "dsc3calca3") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calca3);
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
    else if ( !strcmp(acKey, "dsc3calca4") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calca4);
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
    else if ( !strcmp(acKey, "dsc3calca5") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calca5);
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
    else if ( !strcmp(acKey, "dsc3calca6") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calca6);
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
    else if ( !strcmp(acKey, "dsc3calca7") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calca7);
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
    else if ( !strcmp(acKey, "desccalcb1") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdesccalcb1);
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
    else if ( !strcmp(acKey, "desccalcb2") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdesccalcb2);
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
    else if ( !strcmp(acKey, "desccalcb3") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdesccalcb3);
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
    else if ( !strcmp(acKey, "desccalcb4") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdesccalcb4);
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
    else if ( !strcmp(acKey, "desccalcb5") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdesccalcb5);
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
    else if ( !strcmp(acKey, "desccalcb6") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdesccalcb6);
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
    else if ( !strcmp(acKey, "dsc2calcb1") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc2calcb1);
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
    else if ( !strcmp(acKey, "dsc2calcb2") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc2calcb2);
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
    else if ( !strcmp(acKey, "dsc2calcb3") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc2calcb3);
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
    else if ( !strcmp(acKey, "dsc2calcb4") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc2calcb4);
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
    else if ( !strcmp(acKey, "dsc3calcb1") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calcb1);
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
    else if ( !strcmp(acKey, "dsc3calcb2") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calcb2);
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
    else if ( !strcmp(acKey, "dsc3calcb3") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calcb3);
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
    else if ( !strcmp(acKey, "dsc3calcb4") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calcb4);
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
    else if ( !strcmp(acKey, "dsc3calcb5") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calcb5);
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
    else if ( !strcmp(acKey, "dsc3calcb6") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calcb6);
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
    else if ( !strcmp(acKey, "dsc3calcb7") )
    {
        pcResult = SkillDescCode_GetExpression(pstLineInfo->vdsc3calcb7);
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

int process_skilldesc(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkillPage, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkillRow, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkillColumn, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ListRow, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ListPool, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, IconCel, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, strmyspname, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, strmyspshort, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, strmysplong, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, strmyspalt, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, strmyspmana, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descdam, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descatt, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, p1dmelem, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, p2dmelem, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, p3dmelem, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descmissile1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descmissile2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descmissile3, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descline1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descline2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descline3, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descline4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descline5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descline6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2line1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2line2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2line3, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2line4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3line1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3line2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3line3, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3line4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3line5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3line6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3line7, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desctexta1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desctexta2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desctexta3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desctexta4, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desctexta5, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desctexta6, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2texta1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2texta2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2texta3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2texta4, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3texta1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3texta2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3texta3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3texta4, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3texta5, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3texta6, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3texta7, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desctextb1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desctextb2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desctextb3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desctextb4, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desctextb5, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desctextb6, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2textb1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2textb2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2textb3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2textb4, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3textb1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3textb2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3textb3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3textb4, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3textb5, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3textb6, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3textb7, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ddammyspcalc1, UINT);    //skilldesccode
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ddammyspcalc2, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, p1dmmin, UINT);  //skilldesccode
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, p2dmmin, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, p3dmmin, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, p1dmmax, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, p2dmmax, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, p3dmmax, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desccalca1, UINT);   //skilldesccode
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desccalca2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desccalca3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desccalca4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desccalca5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desccalca6, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2calca1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2calca2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2calca3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2calca4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calca1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calca2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calca3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calca4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calca5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calca6, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calca7, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desccalcb1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desccalcb2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desccalcb3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desccalcb4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desccalcb5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, desccalcb6, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2calcb1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2calcb2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2calcb3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc2calcb4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calcb1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calcb2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calcb3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calcb4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calcb5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calcb6, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dsc3calcb7, UINT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnFieldProc = SkillDesc_FieldProc_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            m_iSkillDescCount = 0;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(string, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(itemtypes, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(elemtypes, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(missiles, acTemplatePath, acBinPath, acTxtPath);

            if ( 0 == SkillDescCode_ParseBin(acTemplatePath, acBinPath, acTxtPath) )
            {
                return 0;
            }
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnFieldProc = SkillDesc_FieldProc;
            m_stCallback.pfnConvertValue = SkillDesc_ConvertValue;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

