#include "global.h"

#define FILE_PREFIX "armor"

/*
Title 	Armor.txt File Guide
Description 	by Nefarius, Kingpin, Ric Faith & Paul Siramy
Sent by 	

OVERVIEW :

Armor.txt, Misc.txt and Weapons.txt have many identical columns. That's because in fact these 3 text files are part of 1 bigger file : when the game reads these 3 tables, it merges them all, one after another, into one and unique table.These 3 text 
files contain all the base items of the game : normal / exceptional / elite versions of items like armor, helm, gaunt, shield, weapon, gems, potion, key, scroll ...

Incidently, that means you can add columns to any one of these 3 files. For instance if you add the columns Transmogrify, TMogType, TMogMin and TMogMax to Armor.txt and use them for an Helm, then this Helm will be able to be Transmute into another item, 
something that doesn't look possible at first glance since the 4 columns are not originally in Armor.txt.

Note : to add columns in a .txt, don't use D2Excel, as this program can't do the job. Instead, use MS Excel or another spreadsheet that can import and export tab-delimited .txt files.

RELATED .TXT FILES :
	

This file is using:

    AutoMagic.txt
    Belt.txt
    Composit.txt
    ItemTypes.txt
    Missiles.txt
    Sound.txt

	

This file is used by :

    CharStats.txt
    CompCode.txt
    CubeMain.txt
    SetItems.txt
    UniqueItems.txt
    ...

COLUMN DESCRIPTIONS :
name 	Reference only, it's a comment field.
version 	0 = Classic D2
100 = Expansion

An item set to 100 cannot be generated in Classic Diablo II.
compactsave 	0 = don't use compact save
1 = use compact save

This is related to the savegames. An item that is saved in a compact way takes less space in the save file, but in counter-part it has no stats : no quantity, no automagic, no affixes, no damage, no armor, no durability ...

This is used by items that don't need any stats to be stored, like Healing Potions or Gems.
rarity 	0 = Exclude this item from armor racks
>= 1 = set the rarity for this item to drop from an armor rack, the higher, the rarer

Warning : there needs to be at least 1 armor with rarity 0 or 1 (but 1 is probably better), othervise the game will crash when you use an armor rack because it won't find any armor available.
spawnable 	0 = can never be sold by NPCs
1 = can be sold by NPCs
minac
maxac 	Minimum and Maximum Armor Class (AC) this item can have.

IitemStatsCost.txt sets the limit to how high these values can be.
absorbs 	Not used.

Older function was probably like "damage reduced by x".
speed 	
Positive value 	= slower walk/run
Negative value 	= faster walk/run
reqstr 	Required Strength, range from 0 to 65535.

If you set a higher value than 65535 or less than 0 you will have a rollover. For instance, if you try to use the value 65538, then it'll be replace by 2 in the game.
levelreq 	Level Requirement.

The minimum level the Player must be to use that item.
block 	Percent Chance to Block.

Block chances are capped at 75 %.
durability
nodurability
durwarning 	

durability = Base Durability

    255 is the maximum, higher values will make a rollover. So if you set Durability to 257 the item will be set to have a durability of only 1.

nodurability = does it even have a Durability ?

    1 = indestructible
    0 = use the Base Durability.

    Note that if the item is set to don't use durability, not only that it'll be an indestructible item, but you also won't read any durability line in the item description.

durwarning = durability where the warning icon appear.

    When the current durability of the item is less or equal to this value, an icon appear on the screen to inform the Player the location of the item which is about to break.

cost 	Base Cost.
gamble cost 	Override default Gamble Cost.

Only works for Rings and Amulets, in Misc.txt.
code
namestr 	

code = This is a 3-letter/number code.

    The code for an item. It needs to be unique; not used by any other item. It is used as reference into several other .txt files.

    It is NOT necessary to add this code to a TBL file anymore.

namestr = code OR name.

    If this string is NOT present in a TBL, it will be considered directly as the name of the item, but if this code IS present in a TBL then it'll be that TBL record that will be used as the name of the item instead.

    Note that if you want a string name with at least 1 space, then you'll have to create a record in a TBL.

normcode
ubercode
ultracode 	
normcode 	= code of the item in its normal version
ubercode 	= code of the item in its exceptional version
ultracode 	= code of the item in its elite version

To know the version of an item (like for a recipe that upgrade only normal items into their exceptional version), the game take its code, and compare it with these 3 columns.

For instance the Lion Helm has :

    code = ba7
    normcode = ba2
    ubercode = ba7
    ultracode = bac

Therefore the Lion Helm in an exceptional item, and then this cube recipe won't work.
level 	Base Item Level (also known as Quality Level - qlvl)

This is NOT the ilvl of the item (which determines what possible affixes can appear on the item). Instead, this quality level is used when the game create its weapXX and armoXX Treasure Classes (TC), and to avoid Monsters / Chests of droping any level 
of items. For instance, a monster with a Level of 20 cannot drop a level 30 armor used by the "armo30" preset TC.
magic lvl 	Additional Magic Level (also known as mlvl).

For instance if this value is set to 5 and you have find the item when gambling while you were at a Player level of 10, then you can get lvl 15 affixes on this item.
auto prefix 	Prefix that automatically spawn on this item.

Taken from the column group of AutoMagic.txt.
alternategfx 	This is the code of the DCC to use for a Player Animation.

For instance, the Gothic Shield (code=gts) has kit in its alternategfx column. That means that if a Barbarian equip himself whith that shield, in his A1 (Attack 1) mode animation his SH (Shield) layer component will use the DCC BASHKITA11HS.DCC, and NOT 
the file BASHGTSA11HS.DCC nor the file BASHBUCA11HS.DCC.
OpenBetaGfx 	

Not used.

Reference what alternategfx it was using in the D2 Beta.
spelloffset 	Unknown.

Only present in Armor.txt.
component 	Layer of the Player Animation that the item is using.

Taken from Composit.txt, that's the index of the line :

0 : 	HD (Head) 	8 : 	S1 (Right Shoulder)
1 : 	TR (Torso) 	9 : 	S2 (Left Shoulder)
2 : 	LG (Legs) 	10 : 	S3 (Necro Shield)
3 : 	RA (Right Arm) 	11 : 	S4 (Special 4)
4 : 	LA (Left Arm) 	12 : 	S5 (Special 5)
5 : 	RH (Right Hand) 	13 : 	S6 (Special 6)
6 : 	LH (Left Hand) 	14 : 	S7 (Special 7)
7 : 	SH (Shield) 	15 : 	S8 (Special 8)

A value of 16 means that the item don't use any layers, since this is an invalid index in Composit.txt.
rArm
lArm
Torso
Legs
rSPad
lSPad 	

Composition of an Armor. Each component in unmodded D2 can have 3 versions, Light / Medium / Heavy. These columns indicates wich version to use for all components (which DCC to use for all layers).

    0 = LIT (Light)
    1 = MED (Medium)
    2 = HVY (Heavy)

rArm 	: layer RA (Right Arm)
lArm 	: layer LA (Left Arm)
Torso 	: layer TR (Torso)
Legs 	: layer LG (Legs)
rSPad 	: layer S1 (Special 1 - Right Shoulder)
lSPad 	: layer S2 (Special 2 - Left Shoulder)

For instance the Quilted Armor has rSPad = 1 and lSPad = 1. Therefore this armor when equiped by an Amazon will be all red (LIT version) except for the shoulders that will be both gray (MED version).
flippyfile
invfile
uniqueinvfile
setinvfile 	

These 4 columns are DC6 filename to use for various situation
flippyfile 	: animation when the item drop
invfile 	: item in the inventory
uniqueinvfile 	: if present, file to use for the Unique version
setinvfile 	: if present, file to use for the Set version

All these files are in the DataGlobalItems directory. For instance if the flippyfile cell has flpcap, then the game will use the file DataGlobalItemsflpcap.dc6 when the item drop.
invwidth
invheight 	Width and Height of the item in the Inventory, in number of cells.
hasinv
gemsockets
gemapplytype 	

These 3 columns are used as Socketing parameters.

hasinv = indicate if the item has an "inventory". This one is needed to store the gems / runes within.

    1 = can be socketed
    0 = cannot be socketed

gemsockets = potential maximum of sockets for this item.

    Note that in any cases the item won't be able to have more sockets than its number of inventory cells (invwidth * invheight).

    In addition, there are 3 columns in ItemTypes.txt that limit this number of sockets, based on the level of the monster that drop the item. The columns are MaxSock1, MaxSock25 and MaxSock40.

    For instance if an helm has gemsockets = 4, but MaxSock1 = 2, then this helm, when drop by a monster of level < 25, will only have 2 sockets.

gemapplytype = gem effect.

    0 = weapon
    1 = armor / helm
    2 = shield

    If you use another value, your item won't be able to have sockets.

useable 	

Does this item do something special when right-click ?

    1 = useable
    0 = not useable

This column is used especially in Misc.txt, for Potions / Scrolls.

Note : The game know what to with the item by its code. Unless you're doing dll editing, don't expect an item to do something just because you have set this column to 1.
throwable 	

Not used.

Can this item be thrown ?

    1 = throwable
    0 = not throwable

This information is in ItemTypes.txt in fact : in Armor.txt and Misc.txt the column is all filled with 0, and is not present in Weapons.txt.
missiletype 	Missile to shoot if you throw this item.

Taken from the column Id in Missiles.txt.
stackable
minstack
maxstack
qntwarning 	

stackable = can this item be stacked ?

    1 = stackable, has quantity
    0 = not stackable

minstack = Minimum quantity the item has when spawned.

maxstack = Maximum quantity the item can have.

qntwarning = quantity where the warning icon appear.

    When the current quantity of the item is less or equal to this value, an icon appear on the screen to inform the Player that he has wasted most of the stack.

These columns are not used in Armor.txt, only in Misc.txt (Keys, Books) and Weapons.txt (Javelins, Arrows ...)
type
type2 	Base Types of the item. Types are used for Cube Recipes, Socketing...

They're taken from the column Code in ItemTypes.txt.
dropsound
dropsfxframe
usesound 	

dropsound = Tells what sound to use when the item drops.

    The code is taken from the column Sound in Sound.txt.

dropsfxframe = Number of frames the sound will play.

usesound = Tells what sound to use when the item is used.

    For instance, this column is used when the player is moving the item around his Inventory.

    The code is taken from the column Sound in Sound.txt.

quest
questdiffcheck 	

quest = Some hardcoded ID for Quests items.

    A Quest item is Unique, you can only pick one with the same ID, and you can't sell it to a NPC.

questdiffcheck = this item has a difficulty check.

    when set to 1, this item will work as a Quest item only in the difficuly where it has been spawned. This is how the game block you from using a Viper Amulet get in Normal difficulty to work in Nightmare difficulty.

    This column is originaly only present in Misc.txt and Weapons.txt.

unique 	1 = only unique version
0 = no restrictions

This is used by quest items, to ensure there's only a Unique version of the item.

If a non-quest item set this column to 1, then only Unique versions of this item will spawned.
transparent 	Unknown, apparently has no effect in game.

Maybe a flag indicating if the item use some kind of translucency effect or not ?
transtbl 	Unknown, apparently has no effect in game.

Maybe some kind of translucency level, if the transparent column is set ?
quivered 	

1 = this item needs ammunitions
0 = no ammunitions required

This column is not used in Armor.txt nor in Misc.txt, just in Weapons.txt (Bows, Crossbows)
lightradius 	Not used.
belt 	

in Armor.txt:

This is an index telling which type of Belt it is :
0 	: Not used / Belt 	Not used / (1 row)
1 	: Sash 	(2 rows)
2 	: Not used 	(1 row - starting belt)
3 	: Girdle 	(4 rows)
4 	: Light Belt 	(2 rows)
5 	: Heavy Belt 	(3 rows)
6 	: Uber Belt 	(4 rows)



This is an ( hardcoded ? ) index of the line to use from Belt.txt. Only the lines above Expansion are used.

Uber Belt is a type of Belt found in Nightmare / Hell.

in Misc.txt :

The column have another meaning :

    0 = can NOT be put into a belt
    1 = can be placed into a belt

Since Misc.txt and Armor.txt are part of the same file, it seems that the game looks for the type of the item first, and *then* decide how to understand the value in this column.
mindam
maxdam 	

Minimum and Maximum damage that this item provide.

Note that the damages aren't always apparent in the item description.

	on Shield 	= 	Smite damages
	on Boots 	= 	Kick damages
	on Weapon 	= 	1-Hand Melee damages
StrBonus
DexBonus 	

StrBonus = Amount of Strength to double the item damages.


DexBonus = Amount of Dexterity to double the item damages.


In Armor.txt only Boots are using these columns, but for a better explanation here's the exemple of the Maiden Spear in Weapons.txt, since it's the same logic anyway.

The Maiden Spear has :
	StrBonus 	= 	80
	DexBonus 	= 	50
	2handmindam 	= 	18
	2handmaxdam 	= 	24

If the Player has Strength = 100 and Dexterity = 120, the Maiden Spear will provide 83-111 damages instead of 18-24 :

    Damages bonus by Strength :
    Min 	= 	18 * 100 / 80 = 22.5
    Max 	= 	24 * 100 / 80 = 30


    Damages Bonus by Dexterity :
    Min 	= 	18 * 120 / 50 = 43.2
    Max 	= 	24 * 120 / 50 = 57.6


    Total Min damages = 18 + 22 + 43 = 83

    Total Max damages = 24 + 30 + 57 = 111

gemoffset 	Placeholder field used to link a socketable item with the corresponding record in Gems.txt, where one exists. Data is filled in at game loading time. Unknown if non-zero values allow multiple record selectivity.
bitfield1 	

Bitfield used primarily for various things, but now only for knowing the composition of the item :

    1 = Leather item
    3 = Metal item

The Iron Golem can only be summoned from Metal Items.
vendorMin
vendorMax
vendorMagicMin
vendorMagicMax
vendorMagicLvl 	

These columns control what the different Vendors can sells.

Replace vendor by :

    Charsi
    Gheed
    Akara
    Fara
    Lysander
    Drognan
    Hratli
    Alkor
    Ormus 	Elzix
    Asheara
    Cain
    Halbu
    Jamella
    Larzuk
    Malah
    Drehya

vendorMin / vendorMax = Minimum / Maximum amount of items of this type the vendor can sell. Do not increase too much, you will CRASH if the game spawns too many items.

vendorMagicMin / vendorMagicMax = Minimum / Maximum amount of magical items of this type the vendor can sell.

vendorMagicLvl = Maximum Magic Level an item can get from the affixes.
PermStoreItem 	

This column is not originally present in Armor.txt (only in Misc.txt and Weapons.txt), but you should add it. It is used to make Permanent items, so Vendors will always sell them.

    1 = always present in a Vendor inventory
    0 = not always sellable

Source Art
Game Art
	Not used.
Transform
InvTrans 	

Transform = colormap to use for the animated version of the item.

InvTrans = colormap to use for the inventory version.

For a detailled explanation, check this doc
SkipName 	For items like the viper amulet (which doesn't say Viper Amulet twice). It makes the game skips the Base name in the item description.
NightmareUpgrade
HellUpgrade
	code of the item the Vendor will sell instead of this item in Nightmare / Hell. xxx = no change.
nameable 	

Used by the reward of Anya's quest : is the Item Nameable ?

    1 = can be personalized
    0 = can't be personalized*/

/*
Name：名字（不用再多解释了吧）。

Version：物品所适用版本。按轻寒的说法是0代表1.07之前的版本，1代表1.07之后的非资料片版本，100代表资料片。
    虽然本人没有那么些版本可供实验，但本人相信轻寒的话。
    （如果一个物品的此项数值被设定为100的话，那么它将无法在原版中出现）。

CompactSave：此物品是否被压缩存储。0代表不压缩，1代表压缩。往往只有**、钥匙这样的没有本身属性的将此列置为1，以节省存储空间。

Rarity：稀有度。在同一TC中出现的概率，值越大掉落的概率越大。请参考物品掉落原理。
    0 = 从装备架中剔除此类物品的任何信息；1或者更大的数字可以调整此类物品的掉宝率。
    说明：你至少应该拥有1个以上的此项数值不为零的装备，否则游戏就会出错而无法正常运行。

Spawnable：是否可在游戏中生成。1代表可以，0代表不可以。不出意外此列都是1。
    是否能够被NPC出售。说明：这里是能否被出售的关键设定，它高于其它位置（相关TXT文件）的设定。1=能够被NPC出售，0=无法出售。

MinAc：此防具的防御值下限。如果想让底材都是极品的话就将此列改为和MaxAc一样即可。事实上JPXXX就是这么做的。
    物品的最低价格；需要注意同itemstatscost.txt中的关联。

MaxAc：此防具的防御值上限。
    物品的最高价格；需要注意同itemstatscost.txt中的关联。

Absorbs：惭愧，此列的意思我也不太清楚，猜测是对伤害的吸收效果。

Speed：此防具对速度的降低程度。0代表不降低，数字越大速度越慢。
    控制速度的参数；Possitive value = 速度减慢，negative value = 提升速度。

ReqStr：装备的力量需求。需要的强壮点数0-65535。

Block：盾牌专有，基础格挡概率。挡格率（最大数值为75%）。

Durability：耐久度上限。耐久度0-255。

NoDurability：没有耐久度，即天生无法破坏。如幻化之刃，但防具中暂时没有。
    是否无法损坏1=无法损害, 0=使用 “durability”的设置。

Level：物品等级。含义请参考轻寒的物品掉落原理。

LevelReq：装备的等级需求。角色使用物品所需要的级别。

Cost：物品卖出时的基础价格。

Gamble Cost：看名字应该是别人在你这赌博时出的价格，但实际上没有这个功能，所以此列应该没有作用。可以肯定的是此列不影响赌博时的价格。

Code：物品代码。内部代码；为3个字节，定制自己的物品时必备。

NameStr：名字索引，即tbl中的键名，实际上与Code总是保持一致，不理解为什么要单做此列。
    如果对于物品名称的相应TBL文件中没有定义此物品的名称，就采用这里的名字。

Magic lvl：物品的魔法等级。作用请参考物品掉落原理。物品魔法属性需要的级别。

Auto prefix：自动附带属性。如法球的加血加蓝，圣骑专用盾的加伤害和准确率。与AutoMagic.txt关联。

alternateGfx：DCC代码。当角色使用此物品时所采用的动作。

OpenBetaGfx：惭愧，没测试出此列有什么作用。

normcode：此物品所对应的普通级别的物品的代码。

ubercode：此物品所对应的扩展级别的物品的代码。

ultracode：此物品所对应的精华级别的物品的代码。

spelloffset：法术抵消效果。但实际上好像没有此效果，此列也没有使用。

component：角色使用此物品时，采用哪一层（Layer）；同文件关联。这是我抄来的，我也没理解。

invwidth：物品在物品栏中的宽度。

invheight：物品在物品栏中的高度。

hasinv：物品是否能够被打孔；1能够打孔，0不能打孔。
    （你可以到itemtypes.txt文件中的MaxSock参数下确定孔的数量，一般所采用的数值为1/25/40）。

gemsockets：物品所允许的最大孔数，不能超过此物品所属类别的最大孔数，否则以类别的为准。

gemapplytype：此物品在镶嵌上宝石类物品后使用宝石的那种效果：0=武器；1=装备/头盔；2=防具。

flippyfile：物品外观所使用的图标指针。掉落时所采用的影象。

invfile：物品在物品栏中所使用的图标指针。

uniqueinvfile：此装备底材对应的唯一物品（暗金）所使用的图标指针。

setinvfile：此装备底材对应的套装中物品所使用的图标指针。

Character Armor gfx display:角色采用此种物品时的动作（0=无显示；1=布类装备；2=铁类装备）。
此下6列表示角色在装备此装备后身上6个部位的变化。0表示没变化，1表示按照布类装备变化，2表示按照铁类装备变化。
rArm =右手
lArm =左手
Torso = 盔甲
Legs = 腿
rSPad = 右肩膀
lSPad = 左肩膀

useable：能否用右键使用。0表示不可以，1表示可以。

throwable：能否被投掷。0表示不可以，1表示可以。

stackable：同种物品能否叠加。0表示不可以，1表示可以。如箭矢此列为1。

minstack：可叠加物品生成时的最小数量。

maxstack：可叠加物品一摞的的最大数量。

type：基本类型。同itemtypes.txt关联。

type2：次要类型；同itemtypes.txt关联。

dropsound：物品掉落时的声音；同sounds.txt关联。

dropsfxframe：物品掉落时动画所占的祯数。

usesound：物品使用时的声音；同sounds.txt关联。

unique：此物品是否只能是唯一（暗金）物品。0表示不是，1代表是。如吉得宝此列为1，但在防具中目前还没有这样的物品。

transparent：不知道什么意思的参数，但都填0。

transtbl：不知道什么意思的参数，但都填5。

quivered：是否是成套才能使用的物品，目前只有弓和弩是。1=是，0=否。

lightradius：不知道什么意思的参数。

belt：腰带专用，表示在belts.txt中的位置。

quest：任务物品专用，所属任务的编号。

missiletype：投掷物品专用。投掷出的物品的类型，同missiles.txt文件关联。

durwarning：在耐久度降低到多少时出现物品损坏提示（就是屏幕右方的图标提示）。

qntwarning：可叠加物品专用，在数量在下降到多少时出现数量不足提示。

mindam：最小伤害值。防具中只有盾牌（盾击）可鞋子（踢击）使用此属性。

maxdam：最大伤害值。防具中只有盾牌（盾击）可鞋子（踢击）使用此属性。

StrBonus：力量对此装备伤害值的影响因子。角色采用“踢”这个动作时对于强壮的影响。

DexBonus：敏捷对此装备伤害值的影响因子。角色采用“踢”这个动作时对于敏捷的影响。

gemoffset：不知道什么意思的参数，但都填0。

bitfield1：装备的内部定义类型。说明：1为布类物品；3为铁类物品。

***Min：名字是***的NPC出售这件物品时的最小数量。

***Max：名字是***的NPC出售这件物品时的最大数量。

***MagicMin：NPC出售这件物品时其所能包含的魔法属性的最少项。此项不为0，NPC才会出售魔法物品。

***MagicMax：NPC出售这件物品时其所能包含的魔法属性的最多项。此项大于1，NPC才会出售有2个属性的魔法物品。

***MagicLvl：魔法物品在出售时所能包含的最大的魔法前后缀级别。说明：同MagicPrefix.txt、MagicSuffix、AutoMagic三个文件关联。

Source Art：不什么什么意思的参数，都不填。

Game Art：不知道什么意思的参数，都不填。


Transform：动作索引。
invTrans：动作索引。
以上两列据说要协同使用。索引，告诉程序使用哪一个整体动作。

SkipName：是否不显示底材的名字。如吉得宝。

NightmareUpgrade：在“恶梦”难度下，会卖这种物品的NPC改卖什么物品（xxx表示还卖这个）。如轻微治疗药剂hp1在此列的值为hp4，表示在普通难度卖轻微治疗药剂的NPC在恶梦难度改卖强力药剂了。

HellUpgrade：在“地狱”难度下，会卖此种物品的NPC改卖什么物品（xxx表示还卖这个）。如轻微治疗药剂hp1在此列的值为hp5，表示在普通难度卖轻微治疗药剂的NPC在恶梦难度改卖超级治疗药剂了。

mindam：不知道什么意思的参数，但是都填0。

PermStoreItem：是否总在NPC处有出售。

maxdam：不知道什么意思的参数，但是都填0。

nameable：是否能够被重命名，即能否被个人化。0表示不能，1表示能。如ACT5中的Q3

*/

typedef struct
{
    unsigned char vflippyfile[32];

    unsigned char vinvfile[32];

    unsigned char vuniqueinvfile[32];

    unsigned char vsetinvfile[32];

    unsigned char vcode[4];

    unsigned char vnormcode[4];

    unsigned char vubercode[4];

    unsigned char vultracode[4];

    unsigned char valternategfx[4];

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

    unsigned int vminac;

    unsigned int vmaxac;

    unsigned int vgamblemyspcost;

    unsigned int vspeed;

    unsigned int vbitfield1;

    unsigned int vcost;

    unsigned int vminstack;
    unsigned int vmaxstack;

    unsigned int iPadding59;

    unsigned int vgemoffset;

    unsigned short vnamestr; //strings
    unsigned char vversion;
    unsigned char iPadding61;

    unsigned short vautomyspprefix;
    unsigned short vmissiletype;

    unsigned char vrarity;
    unsigned char vlevel;
    unsigned char vmindam;
    unsigned char vmaxdam;

    unsigned int iPadding64;

    unsigned short iPadding65;
    unsigned short vStrBonus;

    unsigned short vDexBonus;
    unsigned short vreqstr;

    unsigned short vreqdex;
    unsigned char vabsorbs;
    unsigned char vinvwidth;

    unsigned char vinvheight;
    unsigned char vblock;
    unsigned char vdurability;
    unsigned char vnodurability;

    unsigned char iPadding69;
    unsigned char vcomponent;
    unsigned char vrArm;
    unsigned char vlArm;

    unsigned char vTorso;
    unsigned char vLegs;
    unsigned char vrSPad;
    unsigned char vlSPad;

    unsigned char iPadding71;
    unsigned char vuseable;
    unsigned short vtype;

    unsigned short vtype2;
    unsigned short iPadding72;

    unsigned short vdropsound;  //sounds
    unsigned short vusesound;   //sounds

    unsigned char vdropsfxframe;
    unsigned char vunique;
    unsigned short vquest;

    unsigned char vtransparent;
    unsigned char vtranstbl;
    unsigned char iPadding75;
    unsigned char vlightradius;

    unsigned short vbelt;
    unsigned char vstackable;
    unsigned char vspawnable;

    unsigned char iPadding77;
    unsigned char vdurwarning;
    unsigned char vqntwarning;
    unsigned char vhasinv;

    unsigned char vgemsockets;
    unsigned char iPadding78[3];

    unsigned char iPadding79[2];
    unsigned char vgemapplytype;
    unsigned char vlevelreq;

    unsigned char vmagicmysplvl;
    unsigned char vTransform;
    unsigned char vInvTrans;
    unsigned char vcompactsave;

    unsigned char vSkipName;
    unsigned char vnameable;
    unsigned char vAkaraMin;
    unsigned char vGheedMin;

    unsigned char vCharsiMin;
    unsigned char vFaraMin;
    unsigned char vLysanderMin;
    unsigned char vDrognanMin;

    unsigned char vHraltiMin;
    unsigned char vAlkorMin;
    unsigned char vOrmusMin;
    unsigned char vElzixMin;

    unsigned char vAshearaMin;
    unsigned char vCainMin;
    unsigned char vHalbuMin;
    unsigned char vJamellaMin;

    unsigned char vMalahMin;
    unsigned char vLarzukMin;
    unsigned char vDrehyaMin;
    unsigned char vAkaraMax;

    unsigned char vGheedMax;
    unsigned char vCharsiMax;
    unsigned char vFaraMax;
    unsigned char vLysanderMax;

    unsigned char vDrognanMax;
    unsigned char vHraltiMax;
    unsigned char vAlkorMax;
    unsigned char vOrmusMax;

    unsigned char vElzixMax;
    unsigned char vAshearaMax;
    unsigned char vCainMax;
    unsigned char vHalbuMax;

    unsigned char vJamellaMax;
    unsigned char vMalahMax;
    unsigned char vLarzukMax;
    unsigned char vDrehyaMax;

    unsigned char vAkaraMagicMin;
    unsigned char vGheedMagicMin;
    unsigned char vCharsiMagicMin;
    unsigned char vFaraMagicMin;

    unsigned char vLysanderMagicMin;
    unsigned char vDrognanMagicMin;
    unsigned char vHraltiMagicMin;
    unsigned char vAlkorMagicMin;

    unsigned char vOrmusMagicMin;
    unsigned char vElzixMagicMin;
    unsigned char vAshearaMagicMin;
    unsigned char vCainMagicMin;

    unsigned char vHalbuMagicMin;
    unsigned char vJamellaMagicMin;
    unsigned char vMalahMagicMin;
    unsigned char vLarzukMagicMin;

    unsigned char vDrehyaMagicMin;
    unsigned char vAkaraMagicMax;
    unsigned char vGheedMagicMax;
    unsigned char vCharsiMagicMax;

    unsigned char vFaraMagicMax;
    unsigned char vLysanderMagicMax;
    unsigned char vDrognanMagicMax;
    unsigned char vHraltiMagicMax;

    unsigned char vAlkorMagicMax;
    unsigned char vOrmusMagicMax;
    unsigned char vElzixMagicMax;
    unsigned char vAshearaMagicMax;

    unsigned char vCainMagicMax;
    unsigned char vHalbuMagicMax;
    unsigned char vJamellaMagicMax;
    unsigned char vMalahMagicMax;

    unsigned char vLarzukMagicMax;
    unsigned char vDrehyaMagicMax;
    unsigned char vAkaraMagicLvl;
    unsigned char vGheedMagicLvl;

    unsigned char vCharsiMagicLvl;
    unsigned char vFaraMagicLvl;
    unsigned char vLysanderMagicLvl;
    unsigned char vDrognanMagicLvl;

    unsigned char vHraltiMagicLvl;
    unsigned char vAlkorMagicLvl;
    unsigned char vOrmusMagicLvl;
    unsigned char vElzixMagicLvl;

    unsigned char vAshearaMagicLvl;
    unsigned char vCainMagicLvl;
    unsigned char vHalbuMagicLvl;
    unsigned char vJamellaMagicLvl;

    unsigned char vMalahMagicLvl;
    unsigned char vLarzukMagicLvl;
    unsigned char vDrehyaMagicLvl;
    unsigned char iPadding102;

    unsigned char vNightmareUpgrade[4];

    unsigned char vHellUpgrade[4];

    unsigned int iPadding105;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "name",
    NULL,
};

static char *m_apcNotUsed[] =
{
    "OpenBetaGfx",
    "spelloffset",
    "throwable",
    "quivered",
    "Source Art",
    "Game Art",
    NULL,
};

typedef struct
{
    unsigned char vcode[5];
} ST_ARMOR;

static unsigned int m_iArmorCount = 0;
static ST_ARMOR *m_astArmor = NULL;

static unsigned int m_iMinDamFlag = 0;
static unsigned int m_iMaxDamFlag = 0;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astArmor, ST_ARMOR);

char *Armor_GetArmorCode(unsigned int id)
{
    if ( id >= m_iArmorCount )
    {
        return NULL;
    }

    return m_astArmor[id].vcode;
}

unsigned int Armor_GetArmorCount()
{
    return m_iArmorCount;
}

extern char *String_FindString2(unsigned int id, char** ppcFilter);
static int Armor_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "dropsound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vdropsound);
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
    else if ( !strcmp(acKey, "usesound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vusesound);
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
    else if ( !strcmp(acKey, "namestr") )
    {
        pcResult = String_FindString(pstLineInfo->vnamestr, "dummy");
        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            //acOutput[0] = 0;
            strcpy(acOutput, pstLineInfo->vcode);
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "type") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vtype);
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
    else if ( !strcmp(acKey, "type2") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vtype2);
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
    else if ( !strcmp(acKey, "mindam") )
    {
        //第二组mindam无用，统一填0
        if ( 0 == m_iMinDamFlag )
        {
            m_iMinDamFlag = 1;
        }
        else
        {
            m_iMinDamFlag = 0;
            strcpy(acOutput, "0");
            result = 1;
        }
    }
    else if ( !strcmp(acKey, "maxdam") )
    {
        //第二组maxdam无用，统一填0
        if ( 0 == m_iMaxDamFlag )
        {
            m_iMaxDamFlag = 1;
        }
        else
        {
            m_iMaxDamFlag = 0;
            strcpy(acOutput, "0");
            result = 1;
        }
    }

    return result;
}

static int Armor_FieldProc_Pre(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "name") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            strncpy(acOutput, pstLineInfo->vcode, sizeof(pstLineInfo->vcode));
        }

        strncpy(m_astArmor[m_iArmorCount].vcode, pstLineInfo->vcode, sizeof(pstLineInfo->vcode));
        String_Trim(m_astArmor[m_iArmorCount].vcode);
        m_iArmorCount++;
        return 1;
    }

    return 0;
}

static int Armor_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "name") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            strncpy(acOutput, pstLineInfo->vcode, sizeof(pstLineInfo->vcode));
        }

        return 1;
    }

    return 0;
}

static char *Armor_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strncpy(pcKey, pstLineInfo->vcode, sizeof(pstLineInfo->vcode));
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

int process_armor(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, flippyfile, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invfile, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, uniqueinvfile, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, setinvfile, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, code, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, normcode, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ubercode, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ultracode, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, alternategfx, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, minac, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, maxac, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gamblemyspcost, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, speed, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, bitfield1, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cost, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, minstack, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, maxstack, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gemoffset, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, namestr, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, version, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, automyspprefix, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, missiletype, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rarity, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, level, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mindam, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, maxdam, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StrBonus, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DexBonus, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, reqstr, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, reqdex, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, absorbs, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invwidth, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invheight, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, block, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, durability, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, nodurability, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, component, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rArm, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lArm, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Torso, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Legs, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rSPad, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lSPad, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, useable, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, type, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, type2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dropsound, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, usesound, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dropsfxframe, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, unique, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, quest, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, transparent, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, transtbl, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lightradius, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, belt, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stackable, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, spawnable, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, durwarning, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, qntwarning, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, hasinv, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gemsockets, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gemapplytype, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, levelreq, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, magicmysplvl, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Transform, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InvTrans, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, compactsave, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkipName, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, nameable, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AkaraMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, GheedMin, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CharsiMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FaraMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LysanderMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DrognanMin, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HraltiMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AlkorMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OrmusMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ElzixMin, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AshearaMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CainMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HalbuMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, JamellaMin, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MalahMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LarzukMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DrehyaMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AkaraMax, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, GheedMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CharsiMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FaraMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LysanderMax, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DrognanMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HraltiMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AlkorMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OrmusMax, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ElzixMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AshearaMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CainMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HalbuMax, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, JamellaMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MalahMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LarzukMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DrehyaMax, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AkaraMagicMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, GheedMagicMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CharsiMagicMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FaraMagicMin, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LysanderMagicMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DrognanMagicMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HraltiMagicMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AlkorMagicMin, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OrmusMagicMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ElzixMagicMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AshearaMagicMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CainMagicMin, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HalbuMagicMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, JamellaMagicMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MalahMagicMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LarzukMagicMin, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DrehyaMagicMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AkaraMagicMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, GheedMagicMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CharsiMagicMax, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FaraMagicMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LysanderMagicMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DrognanMagicMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HraltiMagicMax, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AlkorMagicMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OrmusMagicMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ElzixMagicMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AshearaMagicMax, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CainMagicMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HalbuMagicMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, JamellaMagicMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MalahMagicMax, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LarzukMagicMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DrehyaMagicMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AkaraMagicLvl, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, GheedMagicLvl, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CharsiMagicLvl, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FaraMagicLvl, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LysanderMagicLvl, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DrognanMagicLvl, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HraltiMagicLvl, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AlkorMagicLvl, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OrmusMagicLvl, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ElzixMagicLvl, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AshearaMagicLvl, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CainMagicLvl, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HalbuMagicLvl, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, JamellaMagicLvl, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MalahMagicLvl, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LarzukMagicLvl, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DrehyaMagicLvl, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, NightmareUpgrade, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HellUpgrade, STRING);

    m_iMinDamFlag = 0;
    m_iMaxDamFlag = 0;

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iArmorCount = 0;

            //m_stCallback.pfnGetKey = Armor_GetKey;
            m_stCallback.pfnFieldProc = Armor_FieldProc_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(sounds, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(string, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(itemtypes, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            //m_stCallback.pfnGetKey = Armor_GetKey;
            m_stCallback.pfnConvertValue = Armor_ConvertValue;
            m_stCallback.pfnFieldProc = Armor_FieldProc;
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

