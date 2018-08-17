#include "global.h"

#define FILE_PREFIX "itemstatcost"
#define NAME_PREFIX "is"

/*
Stat - An Id pointer used in other *.txt files (Properties.txt, Skills.txt, States.txt and also within ItemStatCost.txt) to refer to this stat, this field must be unique, otherwise you're looking into a world of glitches and bugs.

Id - This field isn't compiled into the bin files, and thus only serves as reference for the internal numeric Id. The internal idea is identical to the # of the record in the array (that is, the first stat would be 0, the second 1 and so on).

Send Other - A boolean that controls whenever the value of this stat is sent to other players, this is only semi functional because most of this is hardcoded to specific stats only, leave it set only for the stats that are being sent in vanilla (Strength
, Dexterity etc) because the game needs to keep clients up to date on these values to function properly (otherwise you'll just glitch up the game).

Signed - A boolean that controls whenever the stat is signed (can be both positive and negative) or unsigned (can only be positive), this doesn't really seam to make any difference because whenever a stat is really signed or unsigned depends on how the 
code is designed to use it, and not on this column, for example Life, Mana, Stamina (etc) can all become negative when they exceed 8388607 * 256 no matter what you set this too, I suspect this simply has to do with the way the game reads stat packets 
because these packets generally only transmit stats in WORD size and it would need to know if they are signed or unsigned for a semi-proper conversion (...)

Send Bits - How many bits of data the game will attempt to fit into a stat update packet for the value of the stat if the stat is sent to clients, again this is not really utilized too a very great extent because most of this is hardcoded, in general 
for signed stats, it is best to set this to 1 more then Save Bits (so say, if save bits is 31 then set this to 32), for unsigned stats it shouldn't matter. Stats with Save Bits of 32 are never treated as signed, always unsigned, and you can't really set 
Send Bits to above 32 bits anyway (for very obvious reasons).

Send Param - How many bits of data the game will attempt to fit into a stat update packet for the parameter of the stat if the stat is sent to clients, it is best to set this to 1 more then Save Param Bits unless it is set to 32 bits (in which case it 
is unsigned), otherwise the param is always signed. This is used to transmit things like the skill granted by oskills (etc), however the same applies here as applied to the previous column, this is almost entirely hardcoded.

UpdateAnimRate - This boolean tells the game to call the speed handler and properly adjust the speed of a unit when a stat with this boolean set to true is altered on the unit (via a skill for example), this is for example the case when an aura is 
applied, so that the speed of the unit changes immediately and not after the current cycle (either attack, walk to a cell etc) ends... As usual, this is rather hardcoded so you'd need to expand the code if you add custom speed stats like these!

Saved - This boolean controls whenever the value of the stat is saved on characters inside the *.d2s file after you leave the game, be aware that statNo 511 is used to signify the "End-Of-Stat-Section" and cannot be used, there are reports that only 
stats 0 to 255 are saveable and other reports that all 510 stats are saveable, I haven't tested this myself so I cannot validate either claim ATM... Looking at the *.d2s reading and writing code I however could not find any artificially imposed 
limitation (other then the aforementioned fact stat 511 cannot be used for anything).

CSvSigned - If the previous column is set to true, this boolean controls whenever the stat is saved in signed or unsigned format, this makes no real difference, other then the fact the way it is written and read from the *.d2s is different (this has 
more revelance when you have the source code at hand and don't want to get tons of warning messages about signed / unsigned mismatch I guess)...

CSvBits - How many bits of data are allocated to the value of this stat within the *.d2s file stat section when the stat is saved (only used if the Saved boolean is true), for unsigned stats you can go all the way to 32 bits (allowing for a range of 0 
to 4294967295), for signed stats you can go only to 31 bits (allowing for a range of -2147483648 to 2147483647), it makes no real difference as stated for the previous column, keep it like in vanilla for the existing stats though, it works so no need to 
fix it. Setting this field to 32 bits for a signed stat has the same effect as setting CSvSigned to false.

CSvParam - How many bits of data are allocated to the parameter of this stat within the *.d2s file stat section when the stat is saved (only used if the Saved boolean is true), the parameter is always signed, unless you set this to 32 bits, in which 
case it becomes unsigned. The same applies here as for the previous column...

fCallback - This boolean controls whenever the stat-assignment callback function is called by the game if the value of this stat changes, this is used to assign / remove item events, skills, auras, states and more to the character / monster... For new 
special effects you have to expand the callback function... It will work fine for new stats that trigger item events however!

fMin - This boolean controls whenever the game will attempt to keep the stat in range calling a special function (and at times doing this inline, such as when the stats are altered by an aura), this prevents stats like strength, dexterity, energy, 
vitality (etc) from dropping below zero...

MinAccr - This field (a DWORD btw) controls the minimum value that the stat is capped to, this seams (I haven't verified this) to work hand-in-hand with fMin, however the times I've seen the code access that flag inline I haven't seen it utilize this 
column, but rather use hardcoded minimum values!

Encode - This field tells the game whenever to encode the stat (and in this case in what way to encode it) when it is saved to conserve space, this is used for complex stats with more then just a parameter and a value such as 'chance to cast on event', 
which have to store the chance, sLvl and the skill to cast, the arithmetics of this are rather complex and aren't within the scope of this fileguide, you can read about them in several old forum posts however... For new stats, follow the theme vanilla 
is using and use this only if you try to duplicate a stat that is encoded in vanilla!

Add and Multiply - These two fields control the additional price added to an item's cost (be aware that certain stats like armorclass on armors (etc) are treated more then once as there are hardcoded cases for them!), the bonus equals: cost * (1 + value 
* multiply / 1024)) + add (...)

Divide - This field is not used by the code anymore, the game uses a inline function for all this price judgling, and it never accesses divide, rather it uses a hardcoded division by 1024!

ValShift - This field tells the game how the stat is going to be read from and written to items, it does not control whenever the stat is generally used in higher precision, this is entirely hardcoded! Basically this field is only there to save space in 
the *.d2s file, so that instead of having to save +256 life it will simply save +1 life when this stat is present on an item!

1.09-Save Bits and 1.09-Save Add - These fields are used only for items imported from v1.07 - v1.09, they replace Save Bits and Save Add so that you can convert the items to the old stat format to the new one, character stats didn't use ItemStatCost.txt 
prior to v1.10 so this doesn't apply to those stats... If you want to prevent people from cheating by creating a v1.09 character and then entering your mod with hacked items (that will get automatically converted by the game), simply blank out all these 
columns and they'll get a nice "bad stats" or "bad inventory" error in their face icon_wink.gif

Save Bits and Save Add - These fields control how many bits of data are allocated to the value of this stat within the *.d2s file item stat section ONLY, they have almost no realtime application at all, stats granted by skills and monster stats (etc) 
are not in any way or form bound to this! The only realtime application this has is when an item is getting compressed / decompressed (which happens every time you pick it up or do anything with it) any way, with this misconception taken off the shelf, 
lets look at how they work. Save Bits controls how many bits of data are allocated to the stat value (see discussion under CSvBits for more info about unsigned / signed implications on what values you can use in this field), the actual maximum value of 
the stat is therefore equal to 2^SaveBits-1, now Save Add comes into play, this controls how large the negative range of the stat can be, for example a Save Add equal to 100 would allow you to use -100 for this stat on an item, this also means the 
maximum value possible for the stat decreases by 100, thus the final range possible for a stat is -SaveAdd to 2^SaveBits-(SaveAdd+1).

Save Param Bits - This field controls how many bits of data are allocated to the parameter of this stat when it is saved on items, the same applies here as to the previous column and to CSvParam so refer to the description of these columns, Save Add 
does not effect the maximum or minimum value of the stat's parameter however... It is best to set this to 17 for all stats that use any form of Id for their parameter (either a skill or a monster etc), because most Id ranges are capped to 65,535, and 
these parameters always being signed unless they are set to store 32 bits means this will allow you to use all Ids without any fear of glitches or bugs!

KeepZero - This boolean supposedly controls whenever to prevent the stat from going negative, probably working hand-in-hand with some of the fMin implementations, at best the effect is however only client-side, as we all know stats like mana and stamina 
can roll over when they exceed 8388607 * 256!

Op, Op Param, Op Base and Op Stat1 to Op Stat3 - These fields control special forms of stat assignment used for example for stats that add a bonus depending on cLvl (etc), I'll explain each of the op methods in detail below (there are in total 13 op 
formulae, but not all are used by the game)... Leaving this field blank or setting it to 0 will use the default op, that just adds the stat to the unit directly... In the below formulae, opstat refers to the stats set in the three Op Stat columns, 
statvalue refers to the value of the stat itself (the stat that has the op stuff assigned to it), basevalue refers to the stat set in the Op Base column and param refers to the value set in the Op Param column!

1 - adds opstat.base * statvalue / 100 to the opstat.

2 - adds (statvalue * basevalue) / (2 ^ param) to the opstat, this does not work properly with any stat other then level because of the way this is updated, it is only refreshed when you re-equip the item, your character is saved or you level up, 
similar to passive skills, just because it looks like it works in the item description does not mean it does, the game just recalculates the information in the description every frame, while the values remain unchanged serverside.

3 - this is a percentage based version of op #2, look at op #2 for information about the formula behind it, just remember the stat is increased by a percentage rather then by adding an integer.

4 - this works the same way op #2 works, however the stat bonus is added to the item and not to the player (so that +defense per level properly adds the defense to the armor and not to the character directly!)

5 - this works like op #4 but is percentage based, it is used for percentage based increase of stats that are found on the item itself, and not stats that are found on the character.

6 - like for op #7, however this adds a plain bonus to the stat, and just like #7 it also doesn't work so I won't bother to explain the arithmetic behind it either.

7 - this is used to increase a stat based on the current daytime of the game world by a percentage, there is no need to explain the arithmetics behind it because frankly enough it just doesn't work serverside, it only updates clientside so this op is 
essentially useless.

8 - hardcoded to work only with maxmana, this will apply the proper amount of mana to your character based on CharStats.txt for the amount of energy the stat added (doesn't work for non characters)

9 - hardcoded to work only with maxhp and maxstamina, this will apply the proper amount of maxhp and maxstamina to your character based on CharStats.txt for the amount of vitality the stat added (doesn't work for non characters)

10 - doesn't do anything, this has no switch case in the op function.

11 - adds opstat.base * statvalue / 100 similar to 1 and 13, the code just does a few more checks

12 - doesn't do anything, this has no switch case in the op function.

13 - adds opstat.base * statvalue / 100 to the value of opstat, this is useable only on items it will not apply the bonus to other unit types (this is why it is used for +% durability, +% level requirement, +% damage, +% defense [etc]).


Direct - this boolean controls whenever this stat has a maximum stat associated with it, which among others means that unless you screw up something badly, this stat can never exceed the value of the maximum stat and that any change to this stat is 
permanent (a skill that alters mana, hitpoints or stamina is permanent, while a skill that alters maxmana, maxhp and maxstamina is temporary). You do not need to specify a maximum stat for the effect to be permanent, this can be used to get kill 
counters to work (look for SVR's old post).

MaxStat - the maximum stat associated with this stat, this field only ever has an effect if Direct is set to true, see the discussion under that field. Percentage based increases to the max stat will usually alter this stat too, however this has some 
hardcoded aspects to it and is not entirely softcoded.

ItemSpecific - this boolean controls whenever this stat is specific to a single item, that is, if you socket a jewel that adds +durability or +quantity into something else, the quantity or durability of both items will not stack when a general call to 
GetStat is returned, however whenever this works properly is unknown, I at least haven't tested it and nobody else has either. It should also prevent the stat from being added to the item owners accumulated total of that stat.

DamageRelated - this boolean controls whenever the stat will be restricted to a single weapon and not stack with the item owners accumulated total of that stat when he equips the weapon (this is used to prevent barbarians who dual wield from for example 
having 50% lifesteal if one weapon has 1% and the other 49% no matter what weapon they swing). To explain this more indepth, when you swing your weapon the game copies all these stats (from the weapon involved) to a temporary statlist that is then 
flushed after the attack is completed (this is not 100% what happens, but it should give you an idea).

ItemEvent1 and ItemEvent2 - the event (from Events.txt) that will trigger the associated event function be aware that not every event will work with every event function, and some event functions will not work when set as an item event!

ItemEventFunc1 and ItemEventFunc2 - the event function associated with the corresponding event set in the previous columns. Below is a list of events and what they do.

1 - shoots a missile at the owner of a missile that has just hit you (Chilling Armor uses this)
2 - freezes the attacker for a set duration the attacker (Frozen Armor uses this)
3 - does cold damage to and chills the attacker (Shiver Armor uses this)
4 - % of damage taken is done to the attacker (Iron Maiden, thorns uses a hardcoded stat)
5 - % of damage done added to life, bypassing the targets resistance (used by Life Tap)
6 - attacker takes physical damage of #
7 - knocks the target back
8 - induces fear in the target making it run away
9 - applies Dim Vision to the target (it casts the actual curse on the monster)
10 - attacker takes lightning damage of #
11 - attacker takes fire damage of #
12 - attacker takes cold damage of #
13 - % damage taken is added to mana
14 - freezes the target
15 - causes the target to bleed and lose life (negative life regen)
16 - crushing blow against the target
17 - mana after killing a monster
18 - life after killing a demon
19 - slows the target
20 - casts a skill against the defender
21 - casts a skill against the attacker
22 - absorbs physical damage taken (used by Bone Armor)
23 - transfers damage done from the summon to the owner (used by Blood Golem)
24 - used by Energy Shield to absorb damage and shift it from life to mana
25 - absorbs elemental damage taken (used by Cyclone Armor)
26 - transfers damage taken from the summon to the owner (used by Blood Golem)
27 - used to slow the attacker if he hits a unit that has the slow target stat (used by Clay Golem)
28 - life after killing a monster
29 - destroys the corpse of a killed monster (rest in peace effect)
30 - cast a skill when the event occurs, without a target
31 - reanimate the target as the specified monster


DescPriority - the higher this value is the further up in the item description this stat will be listed, if more then one stat share the same priority they are listed in the order they are inside the file, valid values range between 0 and 255.

DescFunc - the function used for generating the description for this stat, this works like the descfuncs in SkillDesc.txt pretty much. See below for an explanation of individual functions, these are listed the way they would show up if DescVal is set to 
1. This follows the syntax Char used in the old fileguide, but includes the functions he didn't cover.

1 - +[value] [string1]
2 - [value]% [string1]
3 - [value] [string1]
4 - +[value]% [string1]
5 - [value*100/128]% [string1]
6 - +[value] [string1] [string2]
7 - [value]% [string1] [string2]
8 - +[value]% [string1] [string2]
9 - [value] [string1] [string2]
10 - [value*100/128]% [string1] [string2]
11 - Repairs 1 Durability In [100 / value] Seconds
12 - +[value] [string1]
13 - +[value] to [class] Skill Levels
14 - +[value] to [skilltab] Skill Levels ([class] Only)
15 - [chance]% to case [slvl] [skill] on [event]
16 - Level [sLvl] [skill] Aura When Equipped
17 - [value] [string1] (Increases near [time])
18 - [value]% [string1] (Increases near [time])
19 - this is used by stats that use Blizzard's sprintf implementation (if you don't know what that is, it won't be of interest to you eitherway I guess), look at how prismatic is setup, the string is the format that gets passed to their sprintf spinoff.
20 - [value * -1]% [string1]
21 - [value * -1] [string1]
22 - [value]% [string1] [montype] (warning: this is bugged in vanilla and doesn't work properly, see CE forum)
23 - [value]% [string1] [monster]
24 - used for charges, we all know how that desc looks icon_wink.gif
25 - not used by vanilla, present in the code but I didn't test it yet
26 - not used by vanilla, present in the code but I didn't test it yet
27 - +[value] to [skill] ([class] Only)
28 - +[value] to [skill]

DescVal - Controls whenever and if so in what way the stat value is shown, 0 = doesn't show the value of the stat, 1 = shows the value of the stat infront of the description, 2 = shows the value of the stat after the description.

DescStrPos - The string used for the description when the stat value is positive.

DescStrNeg - The string used for the description when the stat value is negative.

DescStr2 - An additional string used by some DescFuncs, usually used as a suffix or for aditional info (such as per character level etc).

dGrp - When all stats in this group are present on the same item and they all have the same value, replace their description with the associated group description.

dGrpFunc - The same as DescFunc, just for the group description

dGrpVal - The same as DescVal, just for the group description

dGrpStrPos - The same as DescStrPos, just for the group description

dGrpStrNeg - The same as DescStrNeg, just for the group description

dGrpStr2 - The same as DescStr2, just for the group description

Stuff - Stay far away from this column unless you really know what you're doing and / or work for Blizzard, this column is used during bin-file creation to generate a cache regulating the op-stat stuff and other things, changing it can be futile, it 
works like the constants column in MonUMod.txt and has no other relation to ItemStatCost.txt, the first stat in the file simply must have this set or else you may break the entire op stuff.

*/

/*
A.Stat = 属性名。
B.ID = 属性ID。
C.Send Other = 很可能用来决定在联机游戏时，此属性是否发送给其他人,只针对那些对图象要求较高的属性(faster attack/cast/gethit rate)。由于某些原因,敏捷(dexterity)和力量(strength)也同时被发送。留意一下txt文件即知。
D.Signed = 该属性值是否为有符号数。也就是说该属性是否能为负值(negative)。
E.Sendbits = 在客户端和服务器之间传送此值时所用的位长。
F.Send Param = 与客户端和服务器有关的参数。
G.UpdateAnimateRate = ???。可能情况：取布尔值，告诉客户端更新角色动画的速率。
H.Saved = 角色存档时该属性是否同时被保存。物品上的属性随物品一起保存。
I.CSvSigned = 在角色存档是否采用有符号数来保存该属性。1=是,0=否。
J.CSvBits = 存储位长,在角色存档中采取多少位保存。能够保存的最大值为''2^CSvBits-1''。
K.CSvParam = 存储参数,与保存某些属性的参数有关。
L.fCallback = ???
M.fMin = ???
N.MinAccr = ???
O.Encode = 与编码方式有关。
P/Q/R.Add/Multiply/Divide = 计算物品价格时的参数值。(其他txt文件同)
S.ValShift = 决定值以多大的精度变化?。’1‘表示有2^1=2阶精度,’2‘则有2^2=4阶精度,’8‘具有2^8=256阶精度,比如生命点就按1/256的精度进行计算。
T/U.1.09-Save Bits/1.09-Save Add = 在1.09版中的存储位长/相对1.09的增加值。可能与角色转换有关,即1.09的存档导入1.10。
V/W.Save Bits/Save Add = 用来处理物品上数值的保存。同时也决定了该属性可能的最小和最大值。其中,‘’Save Bits‘’决定了属性值的存储位长,‘’Save Add‘’决定了最小值,且和''Save Bits'一起决定最大值。
结果为:stat最小值 = - [Save Add];
stat最大值 = 2^[Save Bits] - [Save Add] - 1;
比如:"Save Add'' = 32,"Save Bits = 8"
则有:最小值 = - 32;
最大值 = 2^8 - 32 -1 = 256 - 33 = 223
X.SaveParamBits = 决定参数以多少位(bits)保存(???)。
Y.keepzero = 布尔值，控制该属性能否出现负值(或者理解为有消极效果)。1=不能。
Z.op = 操作数ID。用来计算该属性产生的效果。
已知的ID及其效果:
1 : op 状态按 [statvalue] 百分比增加（op stats are increased by [statvalue] percent）
2 : op 状态按 [statvalue] * [op base] / 2^[op param]增加（op stats are increased by [statvalue] * [op base] / 2^[op param]）
3 : 未使用，效果未知（not used, effect unknown）
4 : 似乎是和2的效果相同（seems to have the same effect as 2）
5 : op 状态按 [statvalue] * [op base] / 2^[op param]百分比增加（op stats are increased by [statvalue] * [op base] / 2^[op param] percent）
6 : op 状态按时间增加（op stats are increased by time）
7 : op 状态按时间和百分比增加（op stats are increased by time and percent）
8 : 用来计算法力值基于能量值的增加（used to calculate the mana based on energy）
9 : 用来计算生命力和体力值基于活力值的增加（used to calculate the hitpoints and stamina based on vitality）
AA.op param = 见’op‘。
AB.op base = 见’op‘。
AC/AD/AE.op stat1-op stat3 = 控制状态,见’op‘。
AF.direct = 如果该属性能加成到其他属性上,此处设置为1。比如当装备上一个+30mana的物品时,你的最大mana值也会同时增加。
AG.maxstat = 当‘’direct=1‘’时,该属性能加成到的最大属性。
AH.itemspecific = 该属性是否为某类(个)物品独有(且只能影响此类/个物品),比如耐久度,孔数等。比如你可以在这里设置使你的第二件武器不会增加第一件武器的攻击速度。
AI.damagerelated = 该属性是否与‘’伤害‘’(damage)有关。1=是。(效果未知)
AJ.itemevent1 = 当事件(event)发生时,触发‘’intemeventfuc1‘’(见下)。 
AK.itemeventfunc1 = 作用在‘’itemevent1‘’上的函数。使用的函数如下:
6:attacker takes damage of [statvalue] // 攻击者获得伤害
7:knockback // 弹回
8:howl effect // bar的吼叫效果
9:stupidity effect // 致盲效果
10:attacker takes lightning damage of [statvalue] // 攻击者获得闪电伤害
14:freeze effect // 冰冻效果
15: openwounds effect // 撕裂伤口效果
16:crushing blow // 一击致命(或者’粉碎性打击‘?!)
17:get mana (after kill) // 每杀死一个怪物得到魔法值
18:get life (after demon kill) 
19:slow effect // 迟缓效果
20:skill is released // 技能释放,触发事件:被围攻&杀死怪物等
21:skill is released //类似20?!
28:get life (after kill) // 每杀死一个怪物得到生命值
29:slain monster rests in peace // 杀死怪物回复平静
30:skill is released // 释放技能,触发事件:被杀死&升级
31:reanimate slain monster // 杀死怪物后被鼓舞
AL.itemevent2 = 当事件(event)发生时,执行‘’intemeventfuc2‘’
AM.itemeventfunc2 = 作用在‘’itemevent2‘’上的函数。
AN.descpriority =控制该属性在物品上显示的优先级。值越高,在物品上出现得越早。(尚不能确定)
AO.descfunc = 控制属性显示方式的函数。以下是其中的一些:
1 : + [数值] [字符串]（+[value] [string]）
2 : [数值]% [字符串]（[value]% [string]）
3 : [数值] [字符串]（[value] [string]）
4 : + [数值]% [字符串]（+[value]% [string]）
5 : [数值/1.28]% [字符串]，野蛮人的吼叫技能使用（[value/1.28]% [string] // used for howl）
6 : + [数值] [字符串] (基于角色等级)（+[value] [string] (based on character level)）
7 : [数值]% [字符串] (基于角色等级)（[value]% [string] (based on character level)）
8 : + [数值]% [字符串] (基于角色等级)（+[value]% [string] (based on character level)）
9 : [数值] [字符串] (基于角色等级)（[value] [string] (based on character level)）
10 : [数值/1.28]% [字符串] (基于角色等级)（[value/1.28]% [string] (based on character level)）
11 : 每 [100/数值] 秒自动修复1点耐久度（Repairs 1 durability in [100/value] seconds）
12 : + [数值] [字符串]，致盲和冰冻使用（+[value] [string] // used for stupidity, freeze）
13 : + [数值] 到 [角色] 技能等级（+[value] to [class] skill levels）
14 : + [数值] 到 [角色技能页] (仅限[角色])（+[value] to [skilltab] skills ([class] only)）
16 : 装备时显现等级 %d %s 灵气（Level %d %s Aura When Equipped）
AP.descval = 
0:不显示值。
1:值先显示,即显示顺序为‘’值+字符串‘’。比如“+5 to strength‘’(加5到力量)。
2:字符串先显示,然后才是值,即‘’字符串+值‘’。比如‘’strenght +5‘’(力量加5)。
AQ.descstrpos = 值为正时使用的描述性字符串。
AR.descstrneg = 值为负时使用的描述性字符串。
AS.descstr2 = 第二个显示字符(与’‘attributes/per level’‘有关--随等级增长属性,如’‘item-resist-cold-perlevel,ID=230’‘)。
AT.dgrp = 显示组。同一显示组中的相同属性将一起显示。
说明:该txt源文件中一共只有两组,每组含四个属性。
组一:’‘dgrp=1’‘,包括’‘strength(力量,ID=0)’‘,’‘energy(精力,ID=1)’‘,’‘dexterity(敏捷,ID=2)'',''vitality(生命,ID=3)''。
组二:''dgrp=2'',包括’‘fireresist(抗火,ID=39)'',''lightresist(抗闪电,ID=41)'',''coldresist(抗寒,ID=43)'',''poisonresist(抗毒,ID=45)''。
AU.dgrpfunc = 与‘’descfunc‘‘同,控制显示组(display groups)的显示方式。
AV.dgrpval = 与‘’descval‘’同,针对显示组。
AW.dgrpstrpos = 与’‘descstrpos’‘同,针对显示组。
AX.dgrpstrneg = 与’‘descstrneg’‘同,针对显示组。
AY.dgrpstr2 = 与’‘descstr2’‘同,针对显示组。
AZ.stuff = ???
BA.*eol = 行结束符’0‘。

注: op参数和显示方式参考了Sloovy的帖子,在此表示感谢！
*/

/*
文件名解析：
Item：道具，在这里表示装备。
Stat：状态，在这里表示属性。
Cost：开销，在这里表示某些相关信息。
所以此文件就是描述所有可能在装备出现的属性的相关信息。1.10版本以后此文件中又加入了人物属性的一些信息。
此文件中的每一行表示一条属性。


回复

    2楼
    2011-09-20 23:48

    举报 |

    zqtjingzi
    小吧主
    12

每列的含义如下：


回复

    3楼
    2011-09-20 23:48

    举报 |

    虫师林若
    天堂信徒
    11

留名


回复

    4楼
    2011-09-20 23:49

    举报 |

    zqtjingzi
    小吧主
    12

Stat：属性名。所以其它文件中都使用此列的名字来指明某条属性。

ID：属性编号。实际上没有用到。

Send Other：控制是否将此属性发送给其它人，但大多数时候都由硬代码写明。

Signed：此属性值是否为有符号数，但经本人测试并无效果，是由硬代码写明的。据说在联网传输时会用到此列。

Sendbits：联网传输此属性时所用的位长，但大多数时候都由硬代码写明。如果此属性值为有符号数，则此列的值最好为Save Bits + 1，且不要超过32。

Send Param：联网传输此属性的参数时所用的位长，但大多数时候都由硬代码写明。由于Param总为有符号数，所以此列的值最好为Save Param Bits + 1且不要超过32。

UpdateAnimateRate：当此属性变化时是否独立于检测循环外更新（可能会更快的获得效果），但大多数时候都由硬代码写明。

Saved：此属性的值是否存入.d2s文件中，基本只用于人物属性。

CSvSigned：若此属性存入.d2s文件中，是否使用有符号数存储。大多数时候由硬代码写明。

CSvBits：若此属性存入.d2s文件中，存储的位数是多少。

CSvParam：若此属性存入.d2s文件中，此属性参数的存储位数是多少。

fCallback：当此属性变化时，是否调用反馈函数以达到此属性的效果（如增加某一技能，会修改人物技能列表）。

fMin：此属性的值是否被限定在一定范围内。

MinAccr：若此属性的值受限，那么其最小值是多少。实际上此列不起作用，由硬代码写明。

Encode：当此属性的参数较为复杂时（如打击触发技能），使用何种编码方式存储属性参数。

Add：价格增加因子a。

Multiply：价格增加因子b。

Divide：价格计算底数，全为1024，实际上都不起作用，硬代码中写明是1024。

此属性对物品价格的影响应为 cost * (1 + value * multiply / 1024) + add。

ValShift：此属性值的精度。公式为1/2^n，n为此列的值。

1.09-Save Bits：在1.07-1.09版中的存储位长。

1.09-Save Add：在1.07-1.09版中的存储偏移量。

Save Bits：存储位长。硬代码中已写明，且游戏开始时会检测，若修改则会导致游戏出错。
Save Add：存储偏移量。

此属性可能存在的值受以上两列限制，最小值为-1 * SaveAdd，最大值为 2^SaveBits - SaveAdd - 1。

SaveParamBits：Param参数的存储位长。

keepzero：此属性是否能出现负值。但实际上并没有作用。




回复

    5楼
    2011-09-20 23:49

    举报 |

    zqtjingzi
    小吧主
    12

op：此属性值的计算公式，后面会列出op的取值**及对应的计算公式。

op param：计算公式中的参数。

op base：计算公式中的参数。

op stat1：此属性所影响的属性1。

op stat2：此属性所影响的属性2。

op stat3：此属性所影响的属性3。

direct：此属性是否有关联的最大值属性。

maxstat：此属性所关联的最大值属性，仅当direct=1时有作用。

itemspecific：此属性是否只作用于单一物品，手套上增加耐久度的属性不会改变鞋子的耐久度。

damagerelated：此属性是否只作用于单一武器，如第二件武器上的火焰伤害不会加到第一件武器上。

itemevent1：触发此属性函数1的事件，与Events.txt关联。如CB需要先击中怪物才能触发。

itemeventfunc1：事件1发生时触发的函数。函数的取值**和作用在后面集中说明。

itemevent2：触发此属性函数2的事件，与Events.txt关联。

itemeventfunc2：事件2发生时触发的函数。

descpriority：物品属性显示时的优先级，此列的值越高则此属性在装备的属性列表中越靠上，取值范围为0-255。

descfunc：文字描述此属性的方式，取值**和对应描述方式后面集中说明。

descval：如何显示此属性的值。0表示不显示值；1表示先显示值，如+5力量；2表示后显示值，如力量+5。

descstrpos：属性值为正数时的描述语句。

descstrneg：属性值为负数时的描述语句。

descstr2：描述方式中的语句2。

dgrp：此属性所属的描述组别。相同组别的属性若属性值相等会统一显示，如+1力量、+1敏捷、+1精力、+1体力会变成+1所有属性。抗性也一样。目前只有这两种组中坚力量。

dgrpfunc：含义同descfunc，用在组显示中。

dgrpval：含义同descval，用在组显示中。

dgrpstrpos：含义同descstrpos，用在组显示中。

dgrpstrneg：含义同descstrneg，用在组显示中。

dgrpstr2：含义同descstr2，用在组显示中。

stuff：如果你不是暴雪的工作人员的话请不要动这一列。bin文件生成时有用。

*eol：行尾标志，必须为0。


回复

    6楼
    2011-09-20 23:49

    举报 |

    zqtjingzi
    小吧主
    12

说明1：op的取值范围及计算方式：
设op param = p，op base = b，原属性值为v，最终属性值为s。
op = 1 —— s = b * v / 100
op = 2 —— s = b * v / 2^p
op = 3 —— s = b * v / 2^p 用于按百分比增加的属性。
op = 4 —— s = b * v / 2^p 用于作用于装备的属性。
op = 4 —— s = b * v / 2^p 用于按百分比增加且作用于装备的属性。
op = 6 —— 用于随时间变化的属性，已经没用了。
op = 7 —— 用于随时间变化且按百分比增加的属性，已经没用了。
op = 8 —— 只用于精力属性，会根据CharStats.txt中的属性对不同的角色加不同的最大魔法值。
op = 9 —— 只用于体力属性，会根据CharStats.txt中的属性对不同的角色加不同的最大生命值和最大耐力值。
op = 11—— s = b * v / 100 比1多了一些相关的检查。
op = 13—— s = b * v / 100 用于仅作用于一件装备的属性。


回复

    7楼
    2011-09-20 23:49

    举报 |

    zqtjingzi
    小吧主
    12

说明2：ItemEventFunc的取值范围及函数作用：
func = 1 —— 当有远程攻击命中你时发射一个导弹，如寒冰装甲。
func = 2 —— 冻结近身攻击你的人。
func = 3 —— 对近身攻击你的人造成一定的冰冷伤害。
func = 4 —— 按比例反弹近身攻击对你造成的伤害。
func = 5 —— 按比例将对敌人的伤害转化为生命。
func = 6 —— 攻击者受到伤害。
func = 7 —— 击退。
func = 8 —— 恐惧。
func = 9 —— 致盲。
func = 10—— 攻击者受到闪电伤害。
func = 11—— 攻击者受到火焰伤害。
func = 12—— 攻击者受到冰冷伤害。
func = 13—— 将受损的生命转化为法力。
func = 14—— 冻结目标。
func = 15—— 撕开伤口。
func = 16—— 压碎性打击。
func = 17—— 杀死怪物获得法力。
func = 18—— 杀死恶魔时获得生命。
func = 19—— 减速。
func = 20—— 对属性拥有者的攻击对象施放法术。
func = 21—— 对攻击属性拥有者的对象施放法术。
func = 22—— 吸收物理伤害。
func = 23—— 将召唤物造成的伤害转到角色身上。
func = 24—— 用法力抵消伤害。
func = 25—— 吸收元素伤害。
func = 26—— 将召唤物受到的伤害转到角色身上。
func = 27—— 对伤害到此属性拥有者的或此属性拥有者伤害到的减速。
func = 28—— 杀死怪物时获得生命。
func = 29—— 杀死怪物恢复平静。
func = 30—— 在某一事件发生时施放技能，不用选择施放对象。
func = 31—— 复活目标成为某一指定目标。


回复

    8楼
    2011-09-20 23:50

    举报 |

    zqtjingzi
    小吧主
    12

说明3：descfunc的取值范围及属性描述方式：
value为属性的值，string1为此属性本身对应的字符串，string2为descstr2中对应的字符串。
func = 1 —— +[value] [string1]
func = 2 —— [value]% [string1]
func = 3 —— [value] [string1]
func = 4 —— +[value]% [string1]
func = 5 —— [value*100/128]% [string1]
func = 6 —— +[value] [string1] [string2]
func = 7 —— [value]% [string1] [string2]
func = 8 —— +[value]% [string1] [string2]
func = 9 —— [value] [string1] [string2]
func = 10—— [value*100/128]% [string1] [string2]
func = 11—— 回复装备耐久度 1 于 [100/value] 秒内
func = 12—— +[value] [string1]
func = 13—— +[value] [某一职业] 技能等级
func = 14—— +[value] [某一系] 系技能
func = 15—— [当某一事件发生时有] [chance]% 机会施展等级 [技能等级] [技能名]
func = 16—— 赋予等级 [value] [灵气名] 灵气
func = 17—— [value] [string1] "(Increases near" [time] ")"
func = 18—— [value]% [string1] "(Increases near" [time] ")"
func = 20—— [value * -1]% [string1]
func = 21—— [value * -1] [string1]
func = 22—— [value]% [string1] [montype]
func = 23—— [value]% [string1] [monster]
func = 24—— 等级 [技能等级] ([剩余聚气数/总聚气数] 聚气 )
func = 27—— +[value] [技能名] (限[某一职业]使用)
func = 28—— +[value] [技能名]


回复

    9楼
    2011-09-20 23:50

    举报 |

    zqtjingzi
    小吧主
    12

特殊说明：此文件大量参考了某前辈的帖子，忘了叫什么了，先致歉再致敬


回复

    10楼
    2011-09-20 23:50

    举报 |

    zqtjingzi
    小吧主
    12

完毕。
如果有错误请指出。
祝各位游戏愉快。

7楼有个小错误。
有两行op = 4，第一个没错，第二个op = 4应该是op = 5。
应该很容易看出来吧，不过还是提醒一下的好。
*/

typedef struct
{
    unsigned int vID;

#if 1
    unsigned char vCombinedBits1;
    unsigned char vCombinedBits2;
#else
    unsigned char iPadding1_1 : 3;
    unsigned char vdirect : 1;

    unsigned char vitemspecific : 1;
    unsigned char vdamagerelated : 1;
    unsigned char vSigned : 1;
    unsigned char vSendmyspOther : 1;

    unsigned char iPading1 : 1;
    unsigned char iPading1_1 : 1;
    unsigned char vCSvSigned : 1;
    unsigned char vSaved : 1;

    unsigned char vfCallback : 1;
    unsigned char vfMin : 1;
    unsigned char vUpdateAnimRate : 1;
    unsigned char iPadding1_2 : 1;
#endif

    unsigned char iPadding1[2];

    unsigned char vSendmyspBits;
    unsigned char vSendmyspParammyspBits;
    unsigned char vCSvBits;
    unsigned char vCSvParam;

    unsigned int vDivide;
    int vMultiply;
    unsigned int vAdd;

    unsigned char vValShift;
    unsigned char vSavemyspBits;
    unsigned char v1mypoint09mysubSavemyspBits;
    unsigned char bUnKnown;

    int vSavemyspAdd;

    int v1mypoint09mysubSavemyspAdd;

    unsigned int vSavemyspParammyspBits;

    unsigned int iPadding10;
    unsigned int vMinAccr;

    unsigned char vEncode;
    unsigned char bUnKnown2;
    unsigned short vmaxstat;  //引用自身

    unsigned short vdescpriority;
    unsigned char vdescfunc;
    unsigned char vdescval;

    unsigned short vdescstrpos; //strings
    unsigned short vdescstrneg; //strings

    unsigned short vdescstr2;   //strings
    unsigned short vdgrp;

    unsigned char vdgrpfunc;
    unsigned char vdgrpval;
    unsigned short vdgrpstrpos; //strings

    unsigned short vdgrpstrneg; //strings
    unsigned short vdgrpstr2;   //strings

    unsigned short vitemevent1; //events
    unsigned short vitemevent2; //events

    unsigned short vitemeventfunc1;
    unsigned short vitemeventfunc2;

    unsigned int vkeepzero;

    unsigned char vop;
    unsigned char vopmyspparam;
    unsigned short vopmyspbase;   //引用自身

    unsigned short vopmyspstat1;  //引用自身
    unsigned short vopmyspstat2;  //引用自身

    unsigned short vopmyspstat3;  //引用自身
    unsigned short iPadding23;

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
    unsigned int iPadding48;
    unsigned int iPadding49;

    unsigned int iPadding50;
    unsigned int iPadding51;
    unsigned int iPadding52;
    unsigned int iPadding53;
    unsigned int iPadding54;
    unsigned int iPadding55;
    unsigned int iPadding56;
    unsigned int iPadding57;
    unsigned int iPadding58;
    unsigned int iPadding59;

    unsigned int iPadding60;
    unsigned int iPadding61;
    unsigned int iPadding62;
    unsigned int iPadding63;
    unsigned int iPadding64;
    unsigned int iPadding65;
    unsigned int iPadding66;
    unsigned int iPadding67;
    unsigned int iPadding68;
    unsigned int iPadding69;

    unsigned int iPadding70;
    unsigned int iPadding71;
    unsigned int iPadding72;
    unsigned int iPadding73;
    unsigned int iPadding74;
    unsigned int iPadding75;
    unsigned int iPadding76;
    unsigned int iPadding77;
    unsigned int iPadding78;
    unsigned int iPadding79;

    unsigned int vstuff;
} ST_LINE_INFO;

typedef struct
{
    char vStat[64];
} ST_ITEM_STATES;

static char *m_apcInternalProcess[] =
{
    "Stat",
    "*eol",
    NULL,
};

static unsigned int m_iItemStatesCount = 0;
static ST_ITEM_STATES *m_astItemStates = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astItemStates, ST_ITEM_STATES);

static int ItemStatCost_FieldProc_Pre(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "Stat") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->vID);
        }

        strncpy(m_astItemStates[m_iItemStatesCount].vStat, acOutput, sizeof(m_astItemStates[m_iItemStatesCount].vStat));
        String_Trim(m_astItemStates[m_iItemStatesCount].vStat);
        m_iItemStatesCount++;
        return 1;
    }
    else if ( !strcmp(acKey, "*eol") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static int ItemStatCost_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "Stat") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->vID);
        }

        return 1;
    }

    return 0;
}

static int ItemStatCost_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "maxstat") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vmaxstat);
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
    else if ( !strcmp(acKey, "descstrpos") )
    {
        pcResult = String_FindString(pstLineInfo->vdescstrpos, "dummy");
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
    else if ( !strcmp(acKey, "descstrneg") )
    {
        pcResult = String_FindString(pstLineInfo->vdescstrneg, "dummy");
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
    else if ( !strcmp(acKey, "descstr2") )
    {
        pcResult = String_FindString(pstLineInfo->vdescstr2, "dummy");
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
    else if ( !strcmp(acKey, "dgrpstrpos") )
    {
        pcResult = String_FindString(pstLineInfo->vdgrpstrpos, "dummy");
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
    else if ( !strcmp(acKey, "dgrpstrneg") )
    {
        pcResult = String_FindString(pstLineInfo->vdgrpstrneg, "dummy");
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
    else if ( !strcmp(acKey, "dgrpstr2") )
    {
        pcResult = String_FindString(pstLineInfo->vdgrpstr2, "dummy");
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
    else if ( !strcmp(acKey, "itemevent1") )
    {
        pcResult = Events_GetEventName(pstLineInfo->vitemevent1);
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
    else if ( !strcmp(acKey, "itemevent2") )
    {
        pcResult = Events_GetEventName(pstLineInfo->vitemevent2);
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
    else if ( !strcmp(acKey, "op stat1") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vopmyspstat1);
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
    else if ( !strcmp(acKey, "op stat2") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vopmyspstat2);
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
    else if ( !strcmp(acKey, "op stat3") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vopmyspstat3);
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
    else if ( !strcmp(acKey, "op base") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vopmyspbase);
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

static int ItemStatCost_BitProc(void *pvLineInfo, char *acKey, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    int result = 0;

    if ( !strcmp(acKey, "CSvSigned") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vCombinedBits2 & (1 << 5)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "Saved") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vCombinedBits2 & (1 << 4)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "fCallback") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vCombinedBits2 & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "fMin") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vCombinedBits2 & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "UpdateAnimRate") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vCombinedBits2 & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "direct") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vCombinedBits1 & (1 << 4)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "itemspecific") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vCombinedBits1 & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "damagerelated") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vCombinedBits1 & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "Signed") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vCombinedBits1 & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "Send Other") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vCombinedBits1 & 1) != 0);
        result = 1;
    }

    return result;
}

static char *ItemStatCost_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    sprintf(pcKey, "%u", pstLineInfo->vID);
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

int process_itemstatcost(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ID, UINT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, CSvSigned, CombinedBits2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, Saved, CombinedBits2, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, fCallback, CombinedBits2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, fMin, CombinedBits2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, UpdateAnimRate, CombinedBits2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, direct, CombinedBits1, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, itemspecific, CombinedBits1, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, damagerelated, CombinedBits1, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, Signed, CombinedBits1, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, SendmyspOther, CombinedBits1, BIT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SendmyspBits, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SendmyspParammyspBits, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CSvBits, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CSvParam, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Divide, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Multiply, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Add, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ValShift, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SavemyspBits, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, 1mypoint09mysubSavemyspBits, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SavemyspAdd, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, 1mypoint09mysubSavemyspAdd, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SavemyspParammyspBits, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MinAccr, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Encode, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, maxstat, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descpriority, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descfunc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descval, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descstrpos, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descstrneg, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, descstr2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dgrp, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dgrpfunc, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dgrpval, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dgrpstrpos, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dgrpstrneg, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dgrpstr2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itemevent1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itemevent2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itemeventfunc1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, itemeventfunc2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, keepzero, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, op, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, opmyspparam, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, opmyspbase, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, opmyspstat1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, opmyspstat2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, opmyspstat3, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stuff, UINT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iItemStatesCount = 0;

            //m_stCallback.pfnGetKey = ItemStatCost_GetKey;
            m_stCallback.pfnFieldProc = ItemStatCost_FieldProc_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(itemstatcost, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(string, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(events, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            //m_stCallback.pfnGetKey = ItemStatCost_GetKey;
            m_stCallback.pfnConvertValue = ItemStatCost_ConvertValue;
            m_stCallback.pfnFieldProc = ItemStatCost_FieldProc;
            m_stCallback.pfnBitProc = ItemStatCost_BitProc;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

char *ItemStatCost_GetStateName(unsigned int id)
{
    if ( id >= m_iItemStatesCount )
    {
        return NULL;
    }

    return m_astItemStates[id].vStat;
}

