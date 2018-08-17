#include "global.h"

#define FILE_PREFIX "objects"

/*
Title 	Objects.txt
Description 	by Nefarius
Sent by 	
NOTE: For the sake of readability the columns are here not represented the way they are in the file (their order isn't).


Name: This controls the string that is displayed when you highlight this object.

description - not loaded: A reference field, it contains (or should contain) a brief description of what this object represents in-game, unforunately Blizzard didn't put much effort into these, thus the use of the info provided here is rather limited 
and often cryptic.

Id: Another reference field, it refers to the objects unique ID. This field is not used by the game, the IDs are based on the line number.

Token: A third reference field, this field refers to the graphics used by the object. To actually change what graphics the object uses you must edit ObjType.txt.

SpawnMax: Unused, at least altering this field didn't change a thing. Whenever, and how, an object is spawned is controlled only by PopulateFn. For reference, the Blizzard used the values 0, 1 and 2.

TrapProb: Unused, this was supposed to control the chance of the object being trapped, but this is since forever handled by object specific code.

SizeX and SizeY: This controls the amount of subtiles that this object occupies, setting this to very high values will prevent the object from spawning, so beware.

nTgtFX and nTgtFY: unknown (F probably stands for front)

nTgtBX and nTgtBY: unknown (B probably stands for back)

IsAttackable: Boolean, controls whenever the character will use mode NU or mode KK when clicking on this object.

0 = Use mode NU (neutral, idle)
1 = Use mode KK (kick)

EnvEffect: Boolean, unknown but apparently related to ambient sounds and other environment effects.

0 = Not related to environmental effects
1 = Related to environmental effects

IsDoor: Boolean, controls whenever the game treats this object as a door (this makes it display Open Door, Closed Door or Blocked Door instead of the objects actual string). This probably also controls whenever monsters capable of opening doors will 
detect that this object is a door.

0 = This object is not a door
1 = This object is a door

BlockVis: Boolean, controls whenever this object influences line of sight. This only works in conjunction with IsDoor. When this is set to true you are unable to select objects, units or items that are not within the same room as you are unless the door 
is opened. Otherwise you will be able to select things outside of your visions cone (this works similar to LoSDraw in Levels.txt). I'm unaware whenever this effects monsters too.

0 = Don't block the players vision
1 = Block the players vision


Orientation: Unknown, this seams to control what direction the object is facing. But changing it doesn't really have any influence that I could notice in-game (probably since most objects only have 1 direction to start with), it might be used by code to 
know what door to pick for what wall tile, so I'm not sure, for reference, the directions would be:


    1 - Southwest
    2 - Northwest
    3 - Southeast
    4 - Northeast



Trans: Controls what type of palette mapping is applied to the object. Though I couldn't notice any major differences in-game.

PreOperate: Boolean, unknown, they've set this to true for the same objects that have IsAttackable set to true, but I couldn't link this to any in-game behavior.

XOffset and YOffset: The graphical offset (from the animations pivot). This is in pixels rather then subtiles (at least as far as I noticed), so if you set these to -100 the objects graphics will appear shifted 100 pixels to the upper left corner from 
where the object actually is.

Draw: Boolean, controls whenever to draw the object's graphics or not. Note, it will still cast a shadow and the player will still be able to select it.

0 = Don't draw the objects graphics
1 = Draw the objects graphics

Red, Green and Blue: These three fields control the RGB values (the color) of the objects light radius (in case you assigned a light radius to it).

HD, TR, LG, RA, LA, RH, LH, SH and S1 to S8: Booleans, these columns control whenever the respective DCC components are selectable. Setting them to 0 will make the component in question unselectable. In my tests with TR they where still loaded however, 
unlike MonStats2.txt.

0 = Component is unselectable
1 = Component is selectable

TotalPieces: Total amount of selectable DCC components.

SubClass: This field determines what object special subclass this object belongs to:


    1 = Shrine (displays " Shrine")
    2 = Obelisk (does nothing)
    4 = Portal (do not use this for non-portal objects, it causes an assertion error)
    8 = Container (just displays the objects string)
    16 = Arcane Sanctuary Gateway (does nothing)
    32 = Well (does nothing)
    64 = Waypoint (displays " ")
    128 = Secret Jails Door (makes the object unselectable, while keeping it clickable)



XSpace and YSpace: Unknown, some value in subtiles, but I couldn't see any effects in-game.

NameOffset: How many pixels will the objects name be displaced from the pivot (on the z-axis). So setting this to -100 will make the name appear 100 pixels above the animations pixot.

MonsterOK: Boolean, unknown.

OperateRange: Apparently controls the distance in subtiles from which one can use this object, I played around with it, but didn't notice any different in-game.

ShrineFunction: Unused.

Restore: Boolean, controls whenever or not this object is stored in long-term memory and reappears when you return to a previously visited area. Setting this to 0 will make the object disappear once you leave the map.

0 = Allows object to disappear
1 = Object is stored in memory

Act: Reference field, a bit field referencing what Acts this object can appear in without glitching up. 15 refers to an object able to appear in all three acts without messing up.

Lockable: Boolean, controls whenever this object can be locked or note. Note: You need to use the proper InitFn function to make it use this column, another issue, the game will display "Locked Chest" instead of the objects actual name.

0 = Unlockable
1 = Lockable

Gore: Boolean, unknown, set to true only for corpses.

Sync: Boolean, unknown, I suspect that this tells the game whenever it should keep the client and server copies of this object in-sync or whenever it doesn't matter. This is usually set to false for those objects that are only spawned via DS1 files and 
thus cannot get out of sync. This could also be related keeping some other aspects in sync (see Paul's reply to this thread).

0 = Don't keep this object synchronised.
1 = Keep this object synchronised.

Flicker: Boolean, whenever or not the light emitted by this object should flicker.

0 = Don't allow light to flicker.
1 = Allow light to flicker.

Damage: Controls the amount of damage done by this object (only used when the proper OperateFn function is used), but the ratio used is unknown. If this is set to 0 the game will display a warning if it expects there to be damage.

Beta: Reference field, this is set to true if the object appeared in the beta, and to false if it wasen't.

Overlay: Boolean, unknown, seams to control whenever the game will draw an overlay ontop of the objects graphics while it is not used, but this is just a wild guess.

CollisionSubst: Boolean, controls whenever special collision checking will take place, but I can't figure out how exactly this works.

Left, Top, Right and Bottom: Could be controlling the bounding box of the object (clickable area).

RestoreVirgins: Boolean, whenever or not to restore only unused objects (those objects the player hasen't opened or used yet).

0 = Restore all objects
1 = Restore only unused objects

BlockMissiles: Boolean, controls whenever this object will be treated as a wall by missiles.

0 = Missiles can fly thru this object.
1 = Missiles will collide with this object.

DrawUnder: Boolean, controls whenever this object is to be drawn the same way as a floor tile (so for example monsters and players will be drawn on top of this object when their graphics overlap it, even if they stand behind the object).

0 = Draw normally
1 = Draw as a floor tile

OpenWarp: Boolean, controls whenever the game will display "To " or "trap door" when you highlight the object.

AutoMap: Determines how and if this object will appear on the automap, leaving it blank prevents it from spawning on the map.




Object Functions
Note: The following columns are the heart and soul of this file, they control what an object actually does when you click on it and other parts of it's behavior, they are links to an internal function table (which I will post when I get time to look for 
it, if it isn't posted already).

OperateFn: This controls the function called when the player clicks on the object.



    1 - Container (can be trapped with raising undead and fireballs, always drops at least one item as it seams) [used by Caskets]
    2 - Shrine (when you don't use the proper InitFn function the game will crash with an unhandled exception)
    3 - Container (can be trapped with various things, like poison clouds and fire patches, rarely drops an item) [used by Urns]
    4 - Container (can be trapped with various things, drops items more often then function 3 but less often then function 1) [used by Chests]
    5 - Container (can only be trapped by raising undead, rarely drops items, when trapped it doesn't make the trap sound icon_wink.gif) [used by barrels]
    6 - The Tower Tome (quest object, displays the Tower Quest introduction)
    7 - Exploding Object (does damage when used, never drops items) [used by exploding barrels]
    8 - Door (controls whenever you can open and close the object repeatedly)
    9 - Crain Stone (quest object, apply the correct sequence and a portal opens)
    10 - Cains Gibbet (quest object, click it and it spawns Cain)
    11 - Controls whenever it can be turned on an off, like a light switch icon_exclaim.gif (used for braziers which are by default unselectable icon_razz.gif, great work blizzard).
    12 - Tree of Inifuss (quest object, drops the bark scroll)
    13 - Doesn't work, but doesn't crash either.
    14 - Container (can be trapped by various things, drops items rather infrequently) [used by crates]
    15 - Portal (click to go somewhere else)
    16 - Trap Door (click to reveal a level entrance)
    17 - Obelisk (currently just makes the player say impossible, the actual code is gone)
    18 - Secret Door (in jails, this is a door you can't close)
    19 - Armor Rack (drop a random armor, based on area level)
    20 - Weapon Rack (drop a random weapon, based on area level)
    21 - Malus Stand (quest object, drops the horadric malus)
    22 - Well (useless unless properly set up)
    23 - Waypoint (click once to activate, click a second time to open the menu)
    24 - Tainted Sun Altar (quest object, drops the Viper Amulet)
    25 - Horadric Orifice (quest object, you insert the horadric staff into this --- I know how wrong that sounds)
    26 - Book Case (drops books and scrolls of identify and town portal)
    27 - Arcane Sactuary Teleport Gateway (no need to explain)
    28 - Lam Esen's Tome (quest object, click it and it drops the tome)
    29 - Slime Door (one way door, for the maggot lair)
    30 - Exploding Object (blows up and makes a blazing-sound) [used by the exploding cow]
    31 - Decoy Gidbinn Altar (quest object, click it to make the cannibal boss spawn)
    32 - Stash (doesn't work outside of town)
    33 - Wirt's Body (drops tons of gold and the leg)
    34 - Arcane Portal (the portal that lets you enter the arcane sanctuary)
    35 - Steeg Stone (not used and crashes)
    36 - Guild Vault (not used and crashes)
    37 - Trophy Case (not used and crashes)
    38 - Message Board (not used and crashes)
    39 - Quest Chest A (drops one horadric cube for each player)
    40 - Quest Chest B (drops one horadric scholl for each player)
    41 - Quest Chest C (drops one Staff of Kings for each player)
    42 - Horazon's Journal (quest object, displays the "seekers of the tomb of tal-rasha" intro)
    43 - Duriel's Door (the entrance to duriels chamber)
    44 - The stairs to the second level of the sewers (Act III)
    45 - The lever needed to open said stairs
    46 - The Gateway to Hell (the one in mephistos durance)
    47 - Stairs (don't know which, Maybe I'll check later)
    48 - Trapped Soul (don't blindly use this, it will crash when not properly set up)
    49 - The Hell Forge (quest object)
    50 - Stairs (again unknown, thanks to blizzards wonderful description)
    51 - Container (often drops items, doesn't seam to be trapped) [used by various jungle objects]
    52 - Diablo's Seal
    53 - The Compelling Orb
    54 - Diablo's Seal
    55 - Diablo's Seal
    56 - Diablo's Seal
    57 - Quest Chest D (drops one one of khalims body parts for each player)
    58 - Quest Chest E (drops one one of khalims body parts for each player)
    59 - Quest Chest F (drops one one of khalims body parts for each player)
    60 - Nothing (not used and crashes)
    61 - Act V Town Gate (click to open, once)
    62 - Statue that Spawns an Ancient A
    63 - Statue that Spawns an Ancient B
    64 - Statue that Spawns an Ancient C
    65 - The altar that triggers the Ancients
    66 - The door you can only open after killing the Ancients
    67 - Frozen Anya
    68 - Evil Urn (releases spiders, a random boss, or some items)
    69 - Unknown
    70 - Entrance to the Worldstone Chamber
    71 - Unknown
    72 - Portal to Act V (I think)
    73 - Portal to Credits (I think)




PopulateFn: This field controls what population function the game will use to spawn this object, a value of 0 (aka blank), will make the object in question unable to spawn. The following values are used by the game (more might exist but I didn't feel 
like testing for such):


    1 - Spawn random object from internal table (various caskets, various urns).
    2 - Use shrine population logic.
    3 - Spawn singular copies of the object, never adjacent to each other.
    4 - Spawns a group of barrels (normal and exploding barrels), the object itself is removed.
    5 - Spawns singular urns (randomly picked from an internal table).
    6 - Spawn many copies of this object, closely adjacent to each other.
    7 - Spawns a small group of staked rogues (picked from an internal table).
    8 - Spawn singular copies of this object, extremely far apart.
    9 - Spawn many copies of the object, slightly further apart then function 6.






InitFn: This controls what happens while the object is active on the map and what initially happens when the object is activated by an approaching player.



    1 = Shrine (probably responsible for picking a random shrine function to assign to this)
    2 = Container (used by urns)
    3 = Container (used by chests, probably controlls the lockable part)
    4 = Tower Quest Tome (likely checks quest status)
    5 = Door (probably used to check whenever it is closed or open)
    6 = Crain Stone (likely checks quest status)
    7 = Cains Gibbet (likely checks quest status)
    8 = Torch / Brazier (makes the object spawn in ON mode)
    9 = Inifuss (likely checks quest status)
    10 = Unused (spawns in ON mode, walking past it causes fire damage)
    11 = Portal (obviously you shouldn't use this)
    12 = Permanent Portal (ditto)
    13 = Invisible Object (does nothing noticeable)
    14 = Torch / Brazier (same as function number 8)
    15 = Malus Stand (probably checks quest status)
    16 = Well (probably defines how full the well is)
    17 = Waypoint (probably checks whenever the waypoint has been activated before)
    18 = Jerhyn Placeholder (near entrance)
    19 = Jerhyn Placeholder (near palace)
    20 = Tainted Sun Altar (probably checks quest status)
    21 = Horadric Orifice (probably checks quest status)
    22 = Fire (you take fire damage when walking past this)
    23 = Lam Esen's Tome (probably checks quest status)
    24 = Floor Spikes (stabs you when you stand near it)
    25 = Decoy Gidbinn Altar (probably checks quest status)
    26 = River of Flame Skeleton (I think it's this, dunno though)
    27 = Container (used by Goo Piles)
    28 = Spawns patches of gold near the object (icon_mrgreen.gif)
    29 = Arcane Sanctuary Entrance (didn't test, but it's the entrace to the whole place)
    30 = Harem Blocker (checks quest status, make you unable to enter)
    31 = Quest Chest A (for horadric cube)
    32 = Quest Chest B (for horadric scroll)
    33 = Quest Chest C (for Staff of Kings)
    34 = Troch / Brazier (like function 8, however it will randomly spawn in NU or ON mode)
    35 = Guild Vault (will probably crash)
    36 = Trophy Case (will probably crash)
    37 = Unused (does nothing)
    38 = Tyrael's Portal (Act II)
    39 = True Gidbinn Altar (probably checks quest status)
    40 = Message Board (will probably crash)
    41 = Sewer Stairs (the Act III sewers)
    42 = Sewer Lever (to open said stairs)
    43 = Darkwanderer Placeholder (probably checks quest status)
    44 = Gateway to Hell
    45 = Bridge to Gateway to Hell (raises when you come near)
    46 = Trapped Soul (spawns a trapped soul, from MonStats.txt)
    47 = Container (used by chests)
    48 = Hell Forge (probably checks quest status)
    49 = Hralti Placeholder (near entrance)
    50 = Hralti Placeholder (normal spot)
    51 = Container (trapped soul)
    52 = Natalya Placeholder (normal spot, checks quest status)
    53 = Stairs (but which I don't know)
    54 = Cain Placeholder (normal spot, checks quest status)
    55 = Diablo Placeholder (spawns big-D, if all seals are open)
    56 = Diablo's Seal
    57 = Container (used by Sparky Chests)
    58 = Changes the mode to NU after some time
    59 = Related to the Vile Childs the Dark Wanderer spawns.
    60 = Compelling Orb (checks quest status)
    61 = Cain's Portal
    62 = Caged Barbarian's Portal (don't know really)
    63 = Ancient Placeholder Alpha
    64 = Ancient Placeholder Beta
    65 = Ancient Placeholder Gamma
    66 = Anya Placeholder (start)
    67 = Anya Placeholder (end)
    68 = Nihlathak Placeholder (start)
    69 = Nihlathak Placeholder (end)
    70 = Larzuk Placeholder (for greeting, unused?)
    71 = Larzuk Placeholder (normal)
    72 = Ancient Altar (probably checks quest status)
    73 = Ancient Door (probably checks quest status)
    74 = Frozen Anya (probably checks quest status)
    75 = Worldstone Chamber Entrance (checks whenever baal is done with his spamming)
    76 = Appears to be yet another initFn 8 clone.
    77 = Tyrael's Portal (Act IV)
    78 = Tyrael's Portal (Act V)
    79 = Zoo (the functionality has been pulled from the game)




ClientFn: These are special client side functions.


    1 = Ambient Sound Generator
    2 = Rain Ripple
    4 = Unused (crashes since it expects modes objects don't have)
    5 = Unused (crashes since it expects modes objects don't have)
    6 = Unused (crashes since it expects modes objects don't have)
    7 = Burning Skeleton (for River of Flame I think)
    8 = Unused (does nothing)
    9 = Unused (does nothing)
    10 = Bubbles
    11 = Has to do with Baal's Lair
    12 = Has to do with the Arreat Summit
    13 = Dunno really
    14 = Another burning skeleton thing (for what area?)
    15 = Frozen Anya
    16 = Worldstone Chamber Gateway
    17 = Zoo (nothing)
    18 = Zoo Keeper (nothing)



Per ObjMode Settings
Note: The following columns come in groups of eight, each of them controls certain aspects of the object individually for each mode the object uses.


    0 - mode NU
    1 - mode OP
    2 - mode ON
    3 - mode S1
    4 - mode S2
    5 - mode S3
    6 - mode S4
    7 - mode S5



selectable: Boolean, controls whenever you can select the object (highlight when you scroll over).

0 = Unselectable
1 = Selectable

FrameCnt: How many frames does the mode in question have, setting this to 0 will make the game skip this mode.

FrameDelta: At what rate is this animation mode played (in 256ths).

cycleAnim: Boolean, probably determines whenever to loop the animation.

Lit: Diameter of the light radius emitted by this object (in subtiles).

BlocksLight: Boolean, whenever or not this object casts a shadow.

0 = Don't cast a shadow
1 = Cast a shadow

HasCollision: Boolean, whenever or not the game uses collision checking for this mode.

0 = Can't walk thru the object
1 = Can walk thru the object

Start: At what frame should the animation start playing.

OrderFlag: Controls whenever the object is to be drawn as a physical object, a wall or a floor.

0 = Physical object
1 = Floor
2 = Wall

Mode: Boolean, controls whenever the object has this animation mode or not.

Parm: Unknown, some parameter used by the object.








Thanks to everyone who has contributed additional info

Paul Siramy
snowknight
Kingpin

*/

typedef struct
{
    unsigned char vName[64];

    unsigned int iPadding16;
    unsigned int iPadding17;
    unsigned int iPadding18;
    unsigned int iPadding19;

    unsigned int iPadding20;
    unsigned int iPadding21;
    unsigned int iPadding22;
    unsigned int iPadding23;
    unsigned int iPadding24;
    unsigned int iPadding25;
    unsigned int iPadding26;
    unsigned int iPadding27;
    unsigned int iPadding28;
    unsigned int iPadding29;

    unsigned int iPadding30;
    unsigned int iPadding31;
    unsigned int iPadding32;
    unsigned int iPadding33;
    unsigned int iPadding34;
    unsigned int iPadding35;
    unsigned int iPadding36;
    unsigned int iPadding37;
    unsigned int iPadding38;
    unsigned int iPadding39;

    unsigned int iPadding40;
    unsigned int iPadding41;
    unsigned int iPadding42;
    unsigned int iPadding43;
    unsigned int iPadding44;
    unsigned int iPadding45;
    unsigned int iPadding46;
    unsigned int iPadding47;

    unsigned char vToken[3];
    unsigned char vSpawnMax;

    unsigned char vSelectable0;
    unsigned char vSelectable1;
    unsigned char vSelectable2;
    unsigned char vSelectable3;

    unsigned char vSelectable4;
    unsigned char vSelectable5;
    unsigned char vSelectable6;
    unsigned char vSelectable7;

    unsigned int vTrapProb;

    unsigned int vSizeX;
    unsigned int vSizeY;

    unsigned int vFrameCnt0;
    unsigned int vFrameCnt1;

    unsigned int vFrameCnt2;
    unsigned int vFrameCnt3;

    unsigned int vFrameCnt4;
    unsigned int vFrameCnt5;

    unsigned int vFrameCnt6;
    unsigned int vFrameCnt7;

    unsigned short vFrameDelta0;
    unsigned short vFrameDelta1;

    unsigned short vFrameDelta2;
    unsigned short vFrameDelta3;

    unsigned short vFrameDelta4;
    unsigned short vFrameDelta5;

    unsigned short vFrameDelta6;
    unsigned short vFrameDelta7;

    unsigned char vCycleAnim0;
    unsigned char vCycleAnim1;
    unsigned char vCycleAnim2;
    unsigned char vCycleAnim3;

    unsigned char vCycleAnim4;
    unsigned char vCycleAnim5;
    unsigned char vCycleAnim6;
    unsigned char vCycleAnim7;

    unsigned char vLit0;
    unsigned char vLit1;
    unsigned char vLit2;
    unsigned char vLit3;

    unsigned char vLit4;
    unsigned char vLit5;
    unsigned char vLit6;
    unsigned char vLit7;

    unsigned char vBlocksLight0;
    unsigned char vBlocksLight1;
    unsigned char vBlocksLight2;
    unsigned char vBlocksLight3;

    unsigned char vBlocksLight4;
    unsigned char vBlocksLight5;
    unsigned char vBlocksLight6;
    unsigned char vBlocksLight7;

    unsigned char vHasCollision0;
    unsigned char vHasCollision1;
    unsigned char vHasCollision2;
    unsigned char vHasCollision3;

    unsigned char vHasCollision4;
    unsigned char vHasCollision5;
    unsigned char vHasCollision6;
    unsigned char vHasCollision7;

    unsigned char vIsAttackable0;
    unsigned char vStart0;
    unsigned char vStart1;
    unsigned char vStart2;

    unsigned char vStart3;
    unsigned char vStart4;
    unsigned char vStart5;
    unsigned char vStart6;

    unsigned char vStart7;
    unsigned char vOrderFlag0;
    unsigned char vOrderFlag1;
    unsigned char vOrderFlag2;

    unsigned char vOrderFlag3;
    unsigned char vOrderFlag4;
    unsigned char vOrderFlag5;
    unsigned char vOrderFlag6;

    unsigned char vOrderFlag7;
    unsigned char vEnvEffect;
    unsigned char vIsDoor;
    unsigned char vBlocksVis;

    unsigned char vOrientation;
    unsigned char vPreOperate;
    unsigned char vTrans;
    unsigned char vMode0;

    unsigned char vMode1;
    unsigned char vMode2;
    unsigned char vMode3;
    unsigned char vMode4;

    unsigned char vMode5;
    unsigned char vMode6;
    unsigned char vMode7;
    unsigned char iPadding81;

    int vXoffset;
    int vYoffset;

    unsigned char vDraw;
    unsigned char vHD;
    unsigned char vTR;
    unsigned char vLG;

    unsigned char vRA;
    unsigned char vLA;
    unsigned char vRH;
    unsigned char vLH;

    unsigned char vSH;
    unsigned char vS1;
    unsigned char vS2;
    unsigned char vS3;

    unsigned char vS4;
    unsigned char vS5;
    unsigned char vS6;
    unsigned char vS7;

    unsigned char vS8;
    unsigned char vTotalPieces;
    char vXspace;
    char vYspace;

    unsigned char vRed;
    unsigned char vGreen;
    unsigned char vBlue;
    unsigned char vSubClass;

    int vNameOffset;

    unsigned char iPadding91;
    unsigned char vMonsterOK;
    unsigned char vOperateRange;
    unsigned char vShrineFunction;

    unsigned char vAct;
    unsigned char vLockable;
    unsigned char vGore;
    unsigned char vRestore;

    unsigned char vRestoreVirgins;
    unsigned char vSync;
    unsigned char iPadding93_1[2];

    int vParm0;
    int vParm1;
    int vParm2;
    int vParm3;

    int vParm4;
    int vParm5;
    int vParm6;
    int vParm7;

    unsigned char vnTgtFX;
    unsigned char vnTgtFY;
    unsigned char vnTgtBX;
    unsigned char vnTgtBY;

    unsigned char vDamage;
    unsigned char vCollisionSubst;
    unsigned short iPadding103;

    int vLeft;
    int vTop;
    int vWidth;
    int vHeight;

    unsigned char vBeta;
    unsigned char vInitFn;
    unsigned char vPopulateFn;
    unsigned char vOperateFn;

    unsigned char vClientFn;
    unsigned char vOverlay;
    unsigned char vBlockMissile;
    unsigned char vDrawUnder;

    unsigned int vOpenWarp;
    unsigned int vAutoMap;
} ST_LINE_INFO;

static char *m_apcNotUsed[] =
{
    "description - not loaded",
    "Flicker",
    NULL,
};

static char *m_apcInternalProcess[] = 
{
    "Id",
    NULL,
};

static unsigned int m_iObjectsCount = 0;

static int Objects_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    int result = 0;

    if ( !strcmp("Id", acKey) )
    {
#ifdef USE_TEMPLATE
        if ( 0 == pcTemplate[0] )
#endif
        {
            sprintf(acOutput, "%u", m_iObjectsCount);
            result = 1;
        }

        m_iObjectsCount++;
    }

    return result;
}

int process_objects(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Name, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Token, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SpawnMax, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Selectable0, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Selectable1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Selectable2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Selectable3, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Selectable4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Selectable5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Selectable6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Selectable7, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TrapProb, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SizeX, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SizeY, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameCnt0, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameCnt1, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameCnt2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameCnt3, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameCnt4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameCnt5, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameCnt6, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameCnt7, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameDelta0, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameDelta1, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameDelta2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameDelta3, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameDelta4, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameDelta5, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameDelta6, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FrameDelta7, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CycleAnim0, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CycleAnim1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CycleAnim2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CycleAnim3, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CycleAnim4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CycleAnim5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CycleAnim6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CycleAnim7, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Lit0, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Lit1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Lit2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Lit3, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Lit4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Lit5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Lit6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Lit7, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BlocksLight0, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BlocksLight1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BlocksLight2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BlocksLight3, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BlocksLight4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BlocksLight5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BlocksLight6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BlocksLight7, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HasCollision0, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HasCollision1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HasCollision2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HasCollision3, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HasCollision4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HasCollision5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HasCollision6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HasCollision7, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, IsAttackable0, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Start0, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Start1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Start2, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Start3, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Start4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Start5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Start6, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Start7, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OrderFlag0, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OrderFlag1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OrderFlag2, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OrderFlag3, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OrderFlag4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OrderFlag5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OrderFlag6, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OrderFlag7, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EnvEffect, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, IsDoor, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BlocksVis, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Orientation, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PreOperate, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Trans, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode0, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode3, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode4, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Mode7, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Xoffset, SHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Yoffset, SHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Draw, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HD, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TR, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LG, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, RA, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LA, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, RH, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LH, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SH, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S3, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S7, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S8, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TotalPieces, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Xspace, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Yspace, CHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Red, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Green, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Blue, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SubClass, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, NameOffset, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MonsterOK, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OperateRange, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ShrineFunction, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Act, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Lockable, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Gore, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Restore, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, RestoreVirgins, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Sync, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Parm0, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Parm1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Parm2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Parm3, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Parm4, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Parm5, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Parm6, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Parm7, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, nTgtFX, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, nTgtFY, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, nTgtBX, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, nTgtBY, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Damage, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CollisionSubst, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Left, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Top, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Width, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Height, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Beta, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InitFn, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PopulateFn, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OperateFn, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ClientFn, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Overlay, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BlockMissile, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DrawUnder, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OpenWarp, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AutoMap, UINT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnFieldProc = Objects_FieldProc;
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

