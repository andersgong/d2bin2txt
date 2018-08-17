#include "global.h"

#define FILE_PREFIX "missiles"
#define NAME_PREFIX "ml"

/*
Title 	Missiles.txt File Guide v. 2
Description 	by Nefarius and Brother Laz
Sent by 	
Missiles.txt File Guide
By Nefarius and Brother Laz








Initialization

Missile – ID Pointer, this pointer is used to assign the missile to skills and units (Skills.txt and Monstats.txt), never use the same name twice (it won't cause you to crash, but only the first instance will be used when accessed via txt-linkage, note
, if the ID is different you still can launch the missile via code).

Id – The actual ID of the missile the pointer above refers to, if you would access your missile via code directly, you would use this! The ID must be different for each missile (ranging between 0 and 32767). You must also take care to not leave gaps 
between IDs, this is known to lead to unexplained errors and other weird behaviour.




Functions

Note: I will not detail any of the missile functions here, I don't have enough experience in this field (and there already is a missile-function guide by Mishy23 -> which you can read by clicking here). You should also be aware that some functions will 
work properly only when linked to a skill, such as homing missiles! - Nefarius

pCltDoFunc – Client movement function. Defines the graphical behavior of the missile while it is active ("before it vanishes").

pCltHitFunc – Client collision function. Defines the graphical behaviour of the missile at the moment of collision ("the warhead" if you want to call it that way icon_razz.gif).

pSrvDoFunc – Server movement function. Defines the actual behavior of the missile while it is active ("before it vanishes"), note, without a matching client function, the effect will not be displayed, for example if it is to launch additional missiles, 
these missiles will be invisible. A "server-side-only" missile cannot initialize any client-side code, thus any missile it will launch will also be invisible!

pSrvHitFunc – Server collision function. Defines how the missile behaves at the moment of collision, the same rules apply here as they did for the server movement function.

pSrvDmgFunc – Server damage function. Defines special routines to be done when the missile damages ("hits") a unit. This ranges from stunning units (without using stun damage!) to "damaging" mana instead of life.




Calculations

Note: These columns are only used if the proper functions are called by this missile. Also, all columns preceded by an asterisk ("*") are comment fields!

SrvCalc1 – This column contains the server movement calculation.

Param1-5 – These columns contain parameters passed on to the server movement function (these parameters can also be used by the server movement calculation).

CltCalc1 – This column is the client side equivalent to the SrvCalc1 column.

CltParam1-5 – These columns are the client side equivalents to the Param1-5 columns. Normally their values should not be different to the Param1-5 columns, some specially client-side effects such as trails will require them to be different however (the 
trails are a client-side only, so they do not need a server part)!

SHitCalc1 – This column contains the server collision calculation.

sHitPar1-3 – These columns contain the server collision parameters, as with those for the movement functions, they can be used in the SHitCalc1 field.

CHitCalc1 – Client side equivalent to SHitCalc1.

cHitPar1-3 – Client side equivalents to sHitPar1-3 columns.

DmgCalc1 – Calculation used for damage modifications.

dParam1-2 – Parameters for the damage functions, can be used in DmgCalc1 column.




Velocity settings

Vel – Base velocity (the speed this missile starts with), this controls the distance in pixels the missile travels each frame. Speeds near the break point (above 240) cause it to wrap around and move backwards.

MaxVel – Maximum velocity, this column is used if you use positive acceleration as the speed-limit.

VelLev – Velocity per unit level (missiles are units), in case the missile is fired by a monster its ulvl is the mlvl of the unit. In case it is fired by a skill function its ulvl is the slvl of the skill. NOTE: This column may or may not have any 
effect, in tests Brother Laz didn't notice a difference.

Accel – A positive number will make this missile accelerate until its velocity will reach the value in the MaxVel column. A negative value will make the missile slow down until it stands still (0 velocity), you can use this column to cause missiles to 
accelerate past the break point (FF) and thus move in a boomerang fashion (go backwards again). NOTE: Missiles slowing to 0 may not damage anything, you should use a collision function like SFIA or Freezing Arrow to release something else that does 
damage.




Range settings

Range – The number of frames this missile will exists after being created, see as a "self destruction" timer. One may ask why the missiles must vanish, but imagine missiles flying infinitely into the void, not a good way to manage RAM.

LevRange – Additional range per unit level. This works exactly like VelLev, but unlike that column, this column here has an effect.




Light settings

Light – Diameter of the missiles light radius in subtiles.

Flicker – Random alteratring to light radius diameter (in subtiles), use by fire-effects to cause them to flicker (hence the column name) in the existing radius diameter (IE. it doesn't make the radius any larger).

Red, Green, Blue – These columns control the RGB color values of the light radius, obviously 255,255,255 = White and so on, to get any other color then white you need to run in Direct3D (note: windowed mode = always directdraw).




Animation settings

InitSteps – Frames before the missile becomes visible (more technically, frames before the missile is created on the client).

Activate – This column is used for those missiles created from a central point (holybolts unleashed by the fist of heaven, lightning enchanted boss charged bolts, their scarab equivalent etc), it is also used for missiles that will only damage you 
after you touch them for a longer time (the "fingers" of the death maulers for example). Thus, this column is the server side equivalent to InitSteps, this is the delay in frames before the missile can actually do anything besides existing graphically.

LoopAnim – Boolean, 1=Repeat this animation for the time of existence (range), 0=Play this animation once and then vanish (warning: the missile will only vanish from the client if the animation is shorter then the range).

CelFile – The name of the DCC file to used for this missile, the files are stored in dataglobalmissiles, can contain subdirectories.

animrate – As far as I can say it has no function at all, I have set it to 0 and the animations still played at regular speed (16 frames per second as specified in the AnimSpeed column).

AnimLen – The length (in frames) of this animation (for a single direction). If you have a missile with 64 frames and 8 directions, you would enter 8 in this column for obvious reasons.

AnimSpeed – Number of frames played by second, this is not modified by animrate. I don't know why Blizzard has two columns that practically do almost the same, but I assume this is simply a result of the absence of missile *.COF (and thus also *.D2) 
files as the animrate column seams to be ignored (it was in my tests, it is probably there only to avoid crashes in the DCC routines).

RandStart – Causes the animation to start playing at the specified frame. From the name you would think it controls a random starting frame but it does not, it just causes the animation to start at the specified frame.

SubLoop – Boolean, 1=This missile will repeat a specific sequence as long as enough range is left, 0=This missile will play it's animation normally (as defined in the LoopAnim column).

SubStart – Starting frame of the SubLoop.

SubStop – Ending frame of the SubLoop (when it reaches this frame it will either go back to SubStart frame or it will play on until the missile disappears if not enough range is left)




Collision settings A

CollideType – Controls the which type of collision to check for, 3=Normal collision, 6=Z-collision (a missile "dropping from above"), 1=Used mostly for missiles that lay on the floor, waiting for the character to walk over them (like spidergoo and 
spikes) NOTE: This is not required for trap missiles, 8=Fire collision (fire walls etc), related to softhit or per-frame-damage setups. Obviously, 0=No collision detection mode. There are at least 3 unused ones (2,5,7). For a better explanation of what 
these types of collision detection mean:

Type Wall-tiles Units Floor-tiles
0 false false false
1 false true false
3 true true false
6 true false false
8 true true true


CollideKill – Boolean, Will this missile get destroyed upon collision. 1=Always destroy this missile upon collision (overrides almost all other settings, Frozen Orb collision function is known to ignore this column), 0=Don't destroy this missile upon 
collision.

CollideFriend – Boolean, Can this missile collide with allies (such as holybolt), 1=Allow friendly collision, 0=Disallow friendly collision.

LastCollide – Unknown to both me and Brother Laz, but this boolean seams to be related to some special behavior on missiles that don't vanish upon collision, such as fire effects and some other effects that are client-side only. In short, it is usually 
enabled only for missiles with a "physical collision effect". - In any event, this column can be left 0, it won't effect anything noticeable.

Collision – Unknown to both me and Brother Laz, but this boolean is related to the previous one, many missiles that have no "physical collision" but still perform a collision event will have this set to 1 (fire effects). - In any event, this column can 
be left 0, it won't effect anything noticeable.

ClientCol – Unknown to both me and Brother Laz, I assume this name stands for ClientCollision, but what exactly it handles remains a mystery. - In any event, this column can be left 0, it won't effect anything noticeable.

ClientSend – Boolean, could be related to updating lifeorb display on the player when walking into firestorm or shock field.

NextHit – Use collision timer after first collision (1=yes, 0=no), the timer is used to avoid excessive damage (and to annoy players).

NextDelay – Number of frames to deactivate all server-side collision settings for this missile post collision and to make the attacked unit ignore all subsequent missile attacks. For example, a missile with a NextDelay of 25 will be unable to "damage" 
any target for 1 second after each successful server-side collision. Apparently the monster being hit will also become "immune to missiles" for the duration of this timer.




Size / Coordinate settings

xoffset, yoffset, zoffset – Shift the placement of this missile by # pixels on the x, y or z axis, point 0 is either the top left corner of the DCC or the pivot (I haven't tested enough to be sure).

Size – Diameter in subtiles. Probably works identical to the size settings in MonStats2.txt from -1 to 3. Basically 1=Fills only 1 subtile, 2=Fills 4 subtiles, 3=Fills 9 subtiles.




Unknown settings

SrcTown - boolean, most likely controls whenever a missile vanishes when the person goes to a town via a TP ("PK trapping preventation), it is enabled only for missiles that can be used to trap a way point for example (fire walls and such effects).

CltSrcTown – Used together with the above, probably controls some graphical aspects of the vanishing (the number may control a frame, but this is just a wild guess.

CanDestroy – unknown (boolean).




Collision settings B

ToHit – Does this missile use Attack Rating ("chance to hit") or does it "always" (it's 95% actually) hit ("guided arrow behaviour"). You can easily make all missiles require Attack Rating by changing this boolean column to true (1). Whenever it uses 
the additional AR given by skills.txt is unknown, Brother Laz noticed that even the regular vanilla elemental arrows may be bugged and ignore their AR bonus (spankyou very much Blizzard).

AlwaysExplode – Will this missile always call it's Collision Functions when it is destroyed. 1=Yes, 0=No. (For example, Frozen Orb will always explode into a nova, even if it just runs out of range). Some collision functions, such as the Lightning Fury 
collision, will ignore this column and always explode server-side...




Misc. settings and flags (mostly booleans)

Explosion – Boolean, 1=Is an explosion (meaning that it does not exist on the server, this will override all other settings!), 0=Is not an explosion.

Town – Boolean, 1=Does not vanish when spawned inside a town, 0=Vanishes when spawned inside a town (such as the trails left by the Druid's vines).

NoUniqueMod – Boolean, 1=Does not get bonuses from boss modifiers (such as fire damage if the boss spawns as Fire Enchanted), 0=Receives all bonuses applicable.

NoMultiShot – Boolean, 1=Is not effected by the multishot modifier of bosses, 0=Is effected by the multishot modifier of bosses as usual. Note: Blizzard forgot to enable this on some boss-death events, such as Shenk...

Holy – Flag, controls which units this missile can hit, 0=All units, 1=Only undead, 2=Only demons, 3=All units. – I didn't test this extensively, done from memory.

CanSlow – Boolean, 1=Is effected by skill_handofathena stat (slow missiles), 0=Is not effected by skill_handofathena stat.

ReturnFire – Boolean, 1=Can trigger "collision events" on the target, 0=Cannot trigger collision events on the target. *Collision events are all those things that happen "upon getting hit" for example. Blizzard erroneously enabled this on the Arctic 
Blast used by the Frozen Horrors and Nihlathak. NOTE: May or may not effect other "on hit" events, such as casting a skill or "thorns".

GetHit – Boolean, 1=Can knock the target into GH mode ("hit recovery") upon collision, 0=Never knock target into GH mode upon collision.

SoftHit – Boolean, unknown, used only for Shockfield on Ground and Firestorn, Apparently this setting handles the frequency of the unit being "visually" hurt by the missile (probably the unit's lifebar being updated, which was bugged originally).

KnockBack – Percentage chance (0-100) to knock target back, the default is 0 obviously, if you enter 100 in here the target will always be knocked back after every single successful collision.

Trans – Not a boolean, 0=Draw graphic normally, 1=Alpha-blending ("the darker the areas are the more transparent they become"), 2=Special blending mode (usually causes the missile to display black-and-white).

Qty – Does this missile use up quantity (1=use quantity, 0=don't use quantity). NOTE: This requires a special starting function in skills.txt to work. Also, if you enable this for strafe for example, it will use the number of missiles it actually fires 
rather then a constant 1

Pierce – Is this missile effected by pierce (1=effected by pierce, 0=not effected by pierce). This refers to the "pierce" modifier and to the Amazon skill Pierce.

SpecialSetup – Boolean, unknown, enabled only for potions. I am unsure what this controls, the "arc" is not handled by this, there is a special check in code for potion itype. Maybe this has to do with displaying correct missile damage in weapons.txt?





Skill settings

MissileSkill – Boolean, used to transfer elemental damage from items to the splash radius of the missile and to diss all other damage modifiers (ever wondered why Freezing Arrow has SrcDmg set to 128 in skills.txt, yet the splash radius does no 
physical damage?).

Skill – If you enter the ID Pointer ("the name") of a skill here this missile will retrieve all of it's damage/hit data from this skill. The columns being read from skills.txt instead of missiles.txt are the following: ResultFlags, HitFlags, HitShift, 
HitClass, SrcDamage (SrcDam in skills.txt!), MinDam, MinLevDam1-5, MaxDam, MaxLevDam1-5, DmgSymPerCalc, EType, EMin, EMinLev1-5, EMax, EMaxLev1-5, EDmgSymPerCalc, ELen, ELenLev1-3, ELenSymPerCalc.





Event flags

ResultFlags – unknown (to both of us). 4=Used for normal missiles, 5=Used for explosions (all things with HitFlags of 2!), 8=Used for missiles that never damage anything. Most likely behaves similar to CollideType but what it really does...

HitFlags – unknown, 2=Used for explosions, 5=Used for freezing arrow. This could play a more important role then originally expected. Likely related to "splash damage elemental carry over" mentioned further above (MissileSkill).




Damage settings

HitShift – this is a "damage divisor", damage, as well as hitpoints, mana and stamina is handled in 256ths. 8=256/256, 7=128/256, 6=64/256, 5=32/256, 4=16/256, 3=8/256, 2=4/256, 1=2/256, 0=1/256. This roughly equals: 100%, 50%, 25%, 12.5%, 6.25%, 3.125%
, 1.5625%, 0.78125% and 0.390625% of the actual damage.

ApplyMastery – Used only for MeteorFire and VampireMeteorFire. Most likely used to boost the damage of these unlinked missiles via mastery bonuses..

SrcDamage – "Source Damage", this controls whenever the game should append the source units attack properties to the missile or not. Thi column is using 128ths (128=100%). This does not only reflect damage, but all other modifiers related to attack, 
including lifesteal and manasteal. Set this to -1 (poison clouds) to get rid of SrcDmg from skills.txt.

Half2HSrc – Boolean, 1=Halven damage when a two handed weapon is used, 0=Keep full damage when a two handed weapon is used.

SrcMissDmg – Used only for the poison clouds created by the expansion Viper's poison javelin I assume this tells it how much damage it should carry over from the base missile.

MinDamage, MaxDamage – Basic minimum and maximum physical damage of this missile.

MinLevDam1-5, MaxLevDam1-5 – Additional physical damage to deal out per missile level (the unit level of the missile, either equal to the attacker's level or to the skill level). The range is: ulvl 2-8, ulvl 9-16, ulvl 17-22, ulvl 23-28 and ulvl 29+

DmgSymPerCalc – Physical damage synergy, works just like the synergy column in skills.txt, only that it has much fewer functions, AFAIK it only supports getting skill level, not way to obtain stat values etc.

EType – Elemental damage type. fire, ltng (Lightning), mag (Magic), cold, pois (Poison), life (Life-steal), mana (Mana-steal), stam (Stamina-steal), stun (note, "stun damage" is ignored, stun uses only duration), rand (either lightning, fire, cold or 
poison – picked at every successful hit), burn (Burning damage, bugged, gives no EXP from kills, otherwise works like poison, you need to have low HitShift to make it work properly!), frze (Freeze, by itself this is handled like cold damage, you need 
to use special server damage functions to actually cause the unit to become frozen solid).

EMin, EMax – Just like MinDamage and MaxDamage, just for elemental damage (duh).

MinELev1-5, MaxELev1-5 – I doubt I have to explain this. This is like MinLevDam1-5 and MaxLevDam1-5, just for elemental damage.

EDmgSymPerCalc – Same as DmgSymPerCalc, just for elemental damage.

ELen – Duration (used for stun, poison and burning damage), the duration is handled in frames, 25=1 second.

ELevLen1-3 – Extra duration per missile unit level. (check intervals)




Misc. Settings

HitClass – Hit classes are a rather "enigmatic" part of D2, but they are technically just client side effects for collisions. For example the Hit class #6 is responsible for the "pierce noise" when a throwing weapon hits something. #10 is probably the 
same just for "smaller piercing missiles" like Arrows. #2 is used for throwing axes, #64 causes the "electric sound" (used for lightning based missiles to make that special sound), #32 is used for fire walls and the like, #176 for liquid attacks (slime-
missiles for example), #80 is used for Poison Nova, #48 for some cold effects. The hitclasses used in other txt files (MonStats2.txt, Skills.txt and possibly others that I forgot) can also be used here.

NumDirections – Number of directions of the DCC file loaded via the CelFile column. Make sure this matches the DCC to avoid crashes and the like. NOTE: Brother Laz says that this column is of no importance, I personally remember getting crashes in pre 1
.09 days, so ignore this column or fill it, it seams more important that the "Length" column is correct, probably like animrate, which is only there to avoid internal conflicts due to the absence of COF files.

LocalBlood – Related to skills that cause blood to be spilled around. 0=Can't bleed, 1=Can it bleed, 2=Can it bleed and is it effected by open wounds.

DamageRate – How does this missile handle magic_damage_reduced stat. An empty column means the effect is applied completely every single frame. Blizzard added this to avoid people from almost nullifying fire wall damage with just 5+ Magic Damage 
reducing items. (Get detailed formula)





Client side settings A: Sounds

TravelSound – ID Pointer from Sounds.txt to the WAV file the game plays when the missile is created. This is also used for sound effects that should loop for the time of the missiles existence. NOTE: Using looping sounds here can cause crashes (don't 
use long looping sound effects such as Music).

HitSound – ID Pointer from Sounds.txt to the WAV file the game plays when the missile collides with a target.

ProgSound – ID Pointer from Sounds.txt to the WAV file the game plays at special events, defined by the client side functions related to collisions.




Client side settings B: Graphics

ProgOverlay – ID Pointer from Overlays.txt for the DCC file to use as an overlay for special events defined by the client side functions related to collisions.

ExplosionMissile – The ID pointer from Missiles.txt for the explosion to create upon collision, this is only created if the missile successfully collides with a unit or an obstacle (what it can collide with is controlled by CollideType) or when 
AlwaysExplode is enabled..




Appended missiles

Note: These columns are only accessed if the movement or collision functions use them! Also, all these columns use ID Pointers ("names")

SubMissile1-3 – Server part of the missiles spawned by the movement function.

HitSubMissile1-3 – Server part of the missiles spawned by the collision function.

CltSubMissile1-3 – Client part of SubMissile1-3.

CltHitSubMissile1-3 – Client part of HitSubMissile1-3.





Line terminator

EOL – End of Line, must be set to 0 if you use M$ Excel, to prevent it from blowing up the table.

*/

/*
文件名解析：
missile：导弹，发射物。
此文件记录了游戏中所有发射物的信息，每一行表示一种发射物。


回复

    2楼
    2012-01-12 20:55

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    3楼
    2012-01-12 20:55

    举报 |

    我爱皮猴儿
    世界之石
    10

插之


回复

    4楼
    2012-01-12 20:55

    举报 |

    zqtjingzi
    小吧主
    12

Missile：发射物名称索引。

Id：发射物数字索引。

pCltDoFunc：此发射物的客户端移动函数。

pCltHitFunc：此发射物的客户端碰撞函数。

pSrvDoFunc：此发射物的服务器端移动函数。

pSrvHitFunc：此发射物的服务器端碰撞函数。

pSrvDmgFunc：此发射物的特殊伤害计算函数。

SrvCalc1：服务器端移动函数所需的计算公式。

Param1-5：服务器端移动函数所需的参数。

CltCalc1：客户端移动函数所需的计算公式。

CltParam1-5：客户端移动函数所需的参数。

SHitCalc1：服务器端碰撞函数所需的计算公式。

sHitPar1-3：服务器端碰撞函数所需的参数。

CHitCalc1：客户端碰撞函数所需的计算公式。

cHitPar1-3：客户端碰撞函数所需的参数。

DmgCalc1：特殊伤害计算函数所需的计算公式。

dParam1-2：特殊伤害计算函数所需的参数。


回复

    5楼
    2012-01-12 20:55

    举报 |

    zqtjingzi
    小吧主
    12

Vel：此发射物的基础速度。

MaxVel：此发射物的最大速度。

VelLev：此发射物随等级增加的速度。但经测试似乎没有效果。

Accel：此发射物的加速度。最大速度如MaxVel，最小速度为0。

Range：此发射物的寿命，以帧为单位。

LevRange：此发射物每提高一级增加的寿命。

Light：此发射物的照亮范围。

Flicker：此发射物在闪烁时增加的照亮范围。实际上没有测试出效果。

Red/Green/Blue：照亮范围内的光亮颜色。

InitSteps：此发射物在可见之前的准备期所用帧数。

Activate：此发射物在发生作用之前的准备期所用帧数。

LoopAnim：布尔值。是否在寿命结束前循环重复发射物动作。

CelFile：此发射物的外观图片。

animrate：含义未知。

AnimLen：此发射物在每个方向上的动作帧数。

AnimSpeed：动作速度，每秒播放帧数。

RandStart：动作起始帧号。

SubLoop：布尔值，是否有子循环动作。

SubStart：子循环的起始帧号。

SubStop：子循环的结束贴。


回复

    6楼
    2012-01-12 20:56

    举报 |

    zqtjingzi
    小吧主
    12

CollideType：碰撞类型。具体碰撞效果如下：
类型号 墙 单位 地面
0 否 否 否
1 否 是 否
3 是 是 否
6 是 否 否
8 是 是 是

CollideKill：布尔值。此发射物是否会因为碰撞消失。

CollideFriend：布尔值。此发射物是否会与同盟者发生碰撞。

LastCollide：含义未知。

Collision：含义未知。

ClientCol：含义未知。

ClientSend：布尔值，是否需要向服务端发送消息。

NextHit：布尔值。是否具有第二击延迟效果。

NextDelay：第二击延迟效果的帧数。

x/y/z offset：x/y/z方向上的偏移。

Size：此发射物的大小。

SrcTown：含义未知

CltSrcTown：含义未知。

CanDestroy：含义未知。

ToHit：此发射物是否使用攻击准确率属性。

AlwaysExplode：布尔值。此发射物被摧毁时是否总会触发碰撞函数。

Explosion：布尔值。是否是爆炸发射物。

Town：布尔值。是否能在城内存在。

NoUniqueMod：布尔值。是否不被金怪奖励属性影响。

NoMultiShot：布尔值。是否不被多重射击属性影响。


回复

    7楼
    2012-01-12 20:56

    举报 |

    s420295286
    守护天使
    12



回复

    8楼
    2012-01-12 20:56

    举报 |

    zqtjingzi
    小吧主
    12

Holy：此发射物的神圣属性。具体作用如下：
0：不具有神圣属性。
1：忽视不死生物的抗性。
2：忽视恶魔生物的抗性。
3：忽视不死生物和恶魔生物的抗性。

CanSlow：布尔值。是否会被慢速箭技能减速。

ReturnFire：布尔值。是否会触发目标的碰撞事件（如被击中事件）。

GetHit：布尔值。是否能让目标进行打击状态。

SoftHit：含义未知。

KnockBack：击退目标的几率。

Trans：显示参数。

Qty：布尔值。此发射物是否会消耗数量。

Pierce：布尔值。此发射物是否受穿刺效果影响。

SpecialSetup：含义未知。

MissileSkill：布尔值。是否对爆炸范围内的目标只造成元素伤害。

Skill：是否使用对应技能的属性（如伤害、攻击类型）。

ResultFlags：含义未知。

HitFlags：含义未知。

HitShift：伤害放缩因子。采取二进制移位方式进行放缩。
0 = 1/256
1 = 2/256
2 = 4/256...8 = 256/256
9 = 512/256

ApplyMastery：布尔值。是否使用元素支配的伤害提升奖励。

SrcDamage：普通攻击伤害附加比例。缩减因子为128。

Half2HSrc：布尔值。当装备双手武器时是否将伤害减半。

SrcMissDmg：次级发射物上附加初始发射物伤害的比例。修改这列就能去除bug蛇毒云技能中的物理伤害。


回复

    9楼
    2012-01-12 20:56

    举报 |

    zqtjingzi
    小吧主
    12

MinDamage：初始最小物理伤害值。

MinLevDam1-5：每级增加的最小物理伤害值。

MaxDamage：初始最大伤害值。

MaxLevDam1-5：每级增加的最大伤害值。

DmgSymPerCalc：物理伤害加成计算公式。

EType：元素伤害类别。与ElemTypes.txt关联。

EMin：初始元素伤害最小值。

MinELev1-5：每级增加的元素伤害最小值。

EMax：初始元素伤害最大值。

MaxELev1-5：每级增加的元素伤害最大值。

EDmgSymPerCalc：元素伤害加成计算公式。

ELen：元素伤害效果的持续帧数。

ELevLen1-3：每级增加的元素伤害效果持续帧数。


回复

    10楼
    2012-01-12 20:57

    举报 |

    zqtjingzi
    小吧主
    12

HitClass：击打类别。

NumDirections：可能的朝向数。

LocalBlood：流血状态。

DamageRate：对伤害减少属性的响应。

TravelSound：发射时的声音。

HitSound：碰撞里的声音。

ProgSound：特殊事件时的声音。

ProgOverlay：特殊事件时的显示效果。

ExplosionMissile：碰撞时产生的次级发射物。

SubMissile1-3：服务器端移动函数中释放的次级发射物。

HitSubMissile1-4：服务器商碰撞函数中释放的次级发射物。

CltSubMissile1-3：客户端移动函数中释放的次级发射物。

CltHitSubMissile1-4：客户端碰撞函数中释放的次级发射物。

EOL：行尾标志，必须为0。

*/

typedef struct
{
    unsigned int vId;

#if 1
    unsigned short vBitCombined;
#else
    unsigned short vMissileSkill : 1;
    unsigned short vHalf2HSrc : 1;
    unsigned short vNoUniqueMod : 1;
    unsigned short vNoMultiShot : 1;
    unsigned short vSrcTown : 1;
    unsigned short vTown : 1;
    unsigned short vReturnFire : 1;
    unsigned short vApplyMastery : 1;
    unsigned short vSoftHit : 1;
    unsigned short vGetHit : 1;
    unsigned short vClientSend : 1;
    unsigned short vCanDestroy : 1;
    unsigned short vCanSlow : 1;
    unsigned short vPierce : 1;
    unsigned short vExplosion: 1;
    unsigned short vLastCollide : 1;
#endif

    unsigned short wPadding;

    unsigned short vpCltDoFunc;
    unsigned short vpCltHitFunc;

    unsigned short vpSrvDoFunc;
    unsigned short vpSrvHitFunc;

    unsigned short vpSrvDmgFunc;
    unsigned short vTravelSound;    //sounds.txt

    unsigned short vHitSound;       //sounds.txt
    unsigned short vExplosionMissile;   //对应自身

    unsigned short vSubMissile1;   //对应自身
    unsigned short vSubMissile2;   //对应自身

    unsigned short vSubMissile3;   //对应自身
    unsigned short vCltSubMissile1;   //对应自身

    unsigned short vCltSubMissile2;   //对应自身
    unsigned short vCltSubMissile3;   //对应自身

    unsigned short vHitSubMissile1;   //对应自身
    unsigned short vHitSubMissile2;   //对应自身

    unsigned short vHitSubMissile3;   //对应自身
    unsigned short vHitSubMissile4;   //对应自身

    unsigned short vCltHitSubMissile1;   //对应自身
    unsigned short vCltHitSubMissile2;   //对应自身

    unsigned short vCltHitSubMissile3;   //对应自身
    unsigned short vCltHitSubMissile4;   //对应自身

    unsigned short vProgSound;      //sounds.txt
    unsigned short vProgOverlay;    //56 bytes，对应overlay.txt

    int vParam1;
    int vParam2;
    int vParam3;
    int vParam4;
    int vParam5;

    int vsHitPar1;
    int vsHitPar2;
    int vsHitPar3;

    int vCltParam1;
    int vCltParam2;
    int vCltParam3;
    int vCltParam4;
    int vCltParam5;

    int vcHitPar1;
    int vcHitPar2;
    int vcHitPar3;

    int vdParam1;
    int vdParam2;  //128 bytes

    unsigned int vSrvCalc1; //misscode
    unsigned int vCltCalc1;
    unsigned int vSHitCalc1;
    unsigned int vCHitCalc1;
    unsigned int vDmgCalc1;

    unsigned short vHitClass;
    unsigned short vRange;

    unsigned short vLevRange;
    unsigned char vVel;
    unsigned char vVelLev;

    unsigned short vMaxVel;
    short vAccel;  //160 bytes

    unsigned short vanimrate;
    short vxoffset;

    short vyoffset;
    short vzoffset;

    unsigned int vHitFlags;

    unsigned short vResultFlags;
    unsigned char vKnockBack;
    char bPadding3; //176 bytes

    unsigned int vMinDamage;
    unsigned int vMaxDamage;
    unsigned int vMinLevDam1;
    unsigned int vMinLevDam2;
    unsigned int vMinLevDam3;
    unsigned int vMinLevDam4;
    unsigned int vMinLevDam5;
    unsigned int vMaxLevDam1;
    unsigned int vMaxLevDam2;
    unsigned int vMaxLevDam3;
    unsigned int vMaxLevDam4;
    unsigned int vMaxLevDam5;

    unsigned int vDmgSymPerCalc;    //misscode

    unsigned int vEType;   //对应elemtypes的索引

    unsigned int vEMin;
    unsigned int vEmax;
    unsigned int vMinELev1;
    unsigned int vMinELev2;
    unsigned int vMinELev3;
    unsigned int vMinELev4;
    unsigned int vMinELev5;
    unsigned int vMaxELev1;
    unsigned int vMaxELev2;
    unsigned int vMaxELev3;
    unsigned int vMaxELev4;
    unsigned int vMaxELev5; //280 bytes

    unsigned int vEDmgSymPerCalc;   //misscode

    unsigned int vELen;
    unsigned int vELevLen1;
    unsigned int vELevLen2;
    unsigned int vELevLen3;  //300 bytes

    unsigned char vCltSrcTown; 
    unsigned char vSrcDamage;
    unsigned char vSrcMissDmg;
    unsigned char vHoly;

    unsigned char vLight;
    unsigned char vFlicker;
    unsigned char vRed;
    unsigned char vGreen;

    unsigned char vBlue;
    unsigned char vInitSteps;
    unsigned char vActivate;
    unsigned char vLoopAnim;    //312 bytes

    unsigned char vCelFile[64];

    unsigned int vAnimLen;
    unsigned int vRandStart;

    unsigned char vSubLoop;
    unsigned char vSubStart;
    unsigned char vSubStop;
    unsigned char vCollideType;

    unsigned char vCollision;
    unsigned char vClientCol;
    unsigned char vCollideKill;
    unsigned char vCollideFriend;

    unsigned char vNextHit;
    unsigned char vNextDelay;
    unsigned char vSize;
    unsigned char vToHit;

    unsigned char vAlwaysExplode;
    unsigned char vTrans;
    unsigned short vQty;

    unsigned int vSpecialSetup;

    unsigned short vSkill;  //对应skills.txt
    unsigned short vHitShift;

    unsigned int iPadding3;

    unsigned int vDamageRate;

    unsigned char vNumDirections;
    unsigned char vAnimSpeed;   //418 bytes
    unsigned char vLocalBlood;
    unsigned char bUnKnown2;
} ST_LINE_INFO; //420 bytes

typedef struct
{
    unsigned char vMissile[32];
} ST_MISSILES;

static char *m_apcNotUsed[] = 
{
    "*srv calc 1 desc",
    "*param1 desc",
    "*param2 desc",
    "*param3 desc",
    "*param4 desc",
    "*param5 desc",
    "*client calc 1 desc",
    "*client param1 desc",
    "*client param2 desc",
    "*client param3 desc",
    "*client param4 desc",
    "*client param5 desc",
    "*server hit calc 1 desc",
    "*server hit param1 desc",
    "*server hit param2 desc",
    "*server hit param3 desc",
    "*client hit calc1 desc",
    "*client hit param1 desc",
    "*client hit param2 desc",
    "*client hit param3 desc",
    "*damage calc 1",
    "*damage param1 desc",
    "*damage param2 desc",
    NULL,
};

static char *m_apcInternalProcess[] = 
{
    "Missile",
    "EOL",
    NULL,
};

static unsigned int m_iMisslesCount = 0;
static ST_MISSILES *m_astMissiles = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astMissiles, ST_MISSILES);

static int Missiles_FieldProc_Pre(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "Missile") )
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

        strncpy(m_astMissiles[m_iMisslesCount].vMissile, acOutput, sizeof(m_astMissiles[m_iMisslesCount].vMissile));
        String_Trim(m_astMissiles[m_iMisslesCount].vMissile);
        m_iMisslesCount++;
        return 1;
    }
    else if ( !strcmp(acKey, "EOL") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static int Missiles_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "Missile") )
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
    else if ( !strcmp(acKey, "EOL") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

char *Missiles_GetMissile(unsigned int id)
{
    if ( id >= m_iMisslesCount )
    {
        return NULL;
    }

    return m_astMissiles[id].vMissile;
}

static int Missiles_BitProc(void *pvLineInfo, char *acKey, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    int result = 0;

    if ( !strcmp(acKey, "MissileSkill") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 15)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "Half2HSrc") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 14)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "NoUniqueMod") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 13)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "NoMultiShot") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 12)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "SrcTown") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 11)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "Town") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 10)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "ReturnFire") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 9)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "ApplyMastery") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 8)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "SoftHit") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 7)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "GetHit") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 6)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "ClientSend") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 5)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "CanDestroy") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 4)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "CanSlow") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "Pierce") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "Explosion") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "LastCollide") )
    {
        sprintf(acOutput, "%d", ((pstLineInfo->vBitCombined & 1)) != 0);
        result = 1;
    }

    return result;
}

static int Missiles_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "ExplosionMissile") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vExplosionMissile);
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
    else if ( !strcmp(acKey, "SubMissile1") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vSubMissile1);
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
    else if ( !strcmp(acKey, "SubMissile2") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vSubMissile2);
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
    else if ( !strcmp(acKey, "SubMissile3") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vSubMissile3);
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
    else if ( !strcmp(acKey, "HitSubMissile1") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vHitSubMissile1);
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
    else if ( !strcmp(acKey, "HitSubMissile2") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vHitSubMissile2);
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
    else if ( !strcmp(acKey, "HitSubMissile3") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vHitSubMissile3);
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
    else if ( !strcmp(acKey, "HitSubMissile4") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vHitSubMissile4);
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
    else if ( !strcmp(acKey, "CltSubMissile1") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vCltSubMissile1);
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
    else if ( !strcmp(acKey, "CltSubMissile2") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vCltSubMissile2);
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
    else if ( !strcmp(acKey, "CltSubMissile3") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vCltSubMissile3);
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
    else if ( !strcmp(acKey, "CltHitSubMissile1") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vCltHitSubMissile1);
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
    else if ( !strcmp(acKey, "CltHitSubMissile2") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vCltHitSubMissile2);
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
    else if ( !strcmp(acKey, "CltHitSubMissile3") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vCltHitSubMissile3);
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
    else if ( !strcmp(acKey, "CltHitSubMissile4") )
    {
        pcResult = Missiles_GetMissile(pstLineInfo->vCltHitSubMissile4);
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
    else if ( !strcmp(acKey, "ProgOverlay") )
    {
        pcResult = Overlay_GetOverlay(pstLineInfo->vProgOverlay);
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
    else if ( !strcmp(acKey, "EType") )
    {
        pcResult = ElemTypes_GetElemStr(pstLineInfo->vEType);
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
    else if ( !strcmp(acKey, "TravelSound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vTravelSound);
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
    else if ( !strcmp(acKey, "HitSound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vHitSound);
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
    else if ( !strcmp(acKey, "ProgSound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vProgSound);
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
    else if ( !strcmp(acKey, "SrcDamage") )
    {
        if ( 0xFF == pstLineInfo->vSrcDamage )
        {
            strcpy(acOutput, "-1");
            result = 1;
        }
    }
    else if ( !strcmp(acKey, "Skill") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vSkill);
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
    else if ( !strcmp(acKey, "SrvCalc1") )
    {
        pcResult = MissCode_GetExpression(pstLineInfo->vSrvCalc1);
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
    else if ( !strcmp(acKey, "CltCalc1") )
    {
        pcResult = MissCode_GetExpression(pstLineInfo->vCltCalc1);
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
    else if ( !strcmp(acKey, "SHitCalc1") )
    {
        pcResult = MissCode_GetExpression(pstLineInfo->vSHitCalc1);
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
    else if ( !strcmp(acKey, "CHitCalc1") )
    {
        pcResult = MissCode_GetExpression(pstLineInfo->vCHitCalc1);
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
    else if ( !strcmp(acKey, "DmgCalc1") )
    {
        pcResult = MissCode_GetExpression(pstLineInfo->vDmgCalc1);
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
    else if ( !strcmp(acKey, "DmgSymPerCalc") )
    {
        pcResult = MissCode_GetExpression(pstLineInfo->vDmgSymPerCalc);
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
    else if ( !strcmp(acKey, "EDmgSymPerCalc") )
    {
        pcResult = MissCode_GetExpression(pstLineInfo->vEDmgSymPerCalc);
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

int process_missiles(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Id, UINT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, MissileSkill, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, Half2HSrc, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, NoUniqueMod, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, NoMultiShot, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, SrcTown, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, Town, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, ReturnFire, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, ApplyMastery, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, SoftHit, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, GetHit, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, ClientSend, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, CanDestroy, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, CanSlow, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, Pierce, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, Explosion, BitCombined, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, LastCollide, BitCombined, BIT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, pCltDoFunc, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, pCltHitFunc, USHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, pSrvDoFunc, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, pSrvHitFunc, USHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, pSrvDmgFunc, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TravelSound, USHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitSound, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ExplosionMissile, USHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SubMissile1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SubMissile2, USHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SubMissile3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitSubMissile1, USHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitSubMissile2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitSubMissile3, USHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitSubMissile4, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltSubMissile1, USHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltSubMissile2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltSubMissile3, USHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltHitSubMissile1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltHitSubMissile2, USHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltHitSubMissile3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltHitSubMissile4, USHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ProgSound, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ProgOverlay, USHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Param1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Param2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Param3, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Param4, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Param5, INT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sHitPar1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sHitPar2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, sHitPar3, INT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltParam1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltParam2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltParam3, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltParam4, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltParam5, INT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cHitPar1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cHitPar2, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cHitPar3, INT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dParam1, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dParam2, INT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitClass, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Range, USHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LevRange, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Vel, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, VelLev, UCHAR);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxVel, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Accel, SHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, animrate, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, xoffset, SHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, yoffset, SHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, zoffset, SHORT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitFlags, UINT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ResultFlags, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, KnockBack, UCHAR);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinDamage, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxDamage, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinLevDam1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinLevDam2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinLevDam3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinLevDam4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinLevDam5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxLevDam1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxLevDam2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxLevDam3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxLevDam4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxLevDam5, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EType, UINT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EMin, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Emax, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinELev1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinELev2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinELev3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinELev4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinELev5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxELev1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxELev2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxELev3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxELev4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxELev5, UINT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ELen, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ELevLen1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ELevLen2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ELevLen3, UINT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltSrcTown, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SrcDamage, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SrcMissDmg, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Holy, UCHAR);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Light, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Flicker, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Red, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Green, UCHAR);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Blue, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InitSteps, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Activate, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LoopAnim, UCHAR);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CelFile, STRING);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AnimLen, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, RandStart, UINT);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SubLoop, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SubStart, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SubStop, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CollideType, UCHAR);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Collision, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ClientCol, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CollideKill, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CollideFriend, UCHAR);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, NextHit, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, NextDelay, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Size, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ToHit, UCHAR);
    
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AlwaysExplode, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Trans, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Qty, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SpecialSetup, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitShift, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DamageRate, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, NumDirections, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LocalBlood, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AnimSpeed, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SrvCalc1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CltCalc1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SHitCalc1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CHitCalc1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DmgCalc1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DmgSymPerCalc, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, EDmgSymPerCalc, UINT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnFieldProc = Missiles_FieldProc_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            m_iMisslesCount = 0;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(missiles, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(overlay, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(elemtypes, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(sounds, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(skills, acTemplatePath, acBinPath, acTxtPath);

            if ( 0 == MissCode_ParseBin(acTemplatePath, acBinPath, acTxtPath) )
            {
                return 0;
            }
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnFieldProc = Missiles_FieldProc;
            m_stCallback.pfnConvertValue = Missiles_ConvertValue;
            m_stCallback.pfnBitProc = Missiles_BitProc;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

