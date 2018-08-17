#include "global.h"

#define FILE_PREFIX "misc"
#define NAME_PREFIX "mi"

/*
Title 	Misc.txt File Guide
Description 	by Kingpin & Ric Faith
Sent by 	
OVERVIEW

Armor.txt, Misc.txt and Weapons.txt have many identical columns. That's because in fact these 3 text files are part of 1 bigger file : when the game reads these 3 tables, it merges them all, one after another, into one and unique table.These 3 text 
files contain all the base items of the game : normal / exceptional / elite
versions of items like armor, helm, gaunt, shield, weapon, gems, potion, key, scroll ...Incidently, that means you can add columns to any one of these 3 files. For instance if you add the columns , TransmogrifyTMogType,
TMogMin and TMogMax to
Armor.txt and use them for an Helm, then this Helm will be able to be Transmute into another item, something that doesn't look possible at first glance since the 4 columns are not originally in Armor.txt.Note : to add columns in a .txt, don't use D2Excel
, as this program can't do the job. Instead, use MS Excel or another spreadsheet that can import and export tab-delimited .txt files.

RELATED .TXT FilES


This file is using:

* AutoMagic.TxT
* Belt.txt
* Composit.txt
* ItemTypes.txt
* Missiles.txt
* Sound.txt



This file is used by :

* CharStats.txt
* CompCode.txt
* CubeMain.txt
* SetItems.txt
* UniqueItems.txt


COLUMN DESCRIPTIONS :

________________________________________________________________________

name: Reference only, its a comment field.
______________________________________________________________________________

*name: Reference only, its a comment field.
______________________________________________________________________________
szFlavorText: unknown if used
______________________________________________________________________________

compactsave: 1=use ompactsave 0=don't use compactsave. This is used to get a smaller filesize. This will not save
any stats to the item, this means it will not save any quantity, automagic, affixes, damage, armor, durability e.tc.
(This is used by items that don't need any stats stored like Healing potions, gems).

______________________________________________________________________________

version: 0=Classic D2, 100=Expansion (A item set to 100 here cannot
be generated in classic d2).

______________________________________________________________________________

level: base item level (aka a monster with a mlvl of 20 cannot drop a lvl30 armor for eg, used by the "armo#" preset TCs)

______________________________________________________________________________

levelreq: the minimum level you need to have to use that item

______________________________________________________________________________

rarity: 0 = Exclude this item from armor rack, 1 and higher sets the rarity for this item to be droped from an armor rack.(There need to be atleast one armor with rarity 1 othervise the game will crash when you use an armor rack).

______________________________________________________________________________

spawnable: 1=can be sold by NPCs, 0=can never be sold by NPCs (even if you make them sell it thru the vendor columns)

______________________________________________________________________________

speed: Possitive value = slower run, negative value = faster run.

______________________________________________________________________________

nodurability: 1=indestructible, 0=use durability

______________________________________________________________________________

gamble cost: only used by Amulets/Rings.

______________________________________________________________________________

Code : is not needed to be added to string table anymore. This is a 3 letter/number code that need to be unique and not used by other items.

______________________________________________________________________________

alternategfx: This is the code of the DCC to use for a Player Animation. [For instance, the Gothic Shield (code=gts) has kit in its alternategfx column. That means that if a Barbarian equip himself whith that shield, in his A1 (Attack 1) mode animation 
his SH (Shield) layer component will use the DCC BASHKITA11HS.DCC, and NOT the
file BASHGTSA11HS.DCC nor the file BASHBUCA11HS.DCC.

______________________________________________________________________________

name str: If namestr code is not added to a string table it will use that name in the field.If you want a string name with space you need to add it to your string table.

______________________________________________________________________________

component: This tells what layer it should use from composit.txt to show the item on the character. (composit.txt are 16
lines that range from 0 (HD) to 15 (S8) and 16 means "no player animation").

______________________________________________________________________________	

invwidth: width in inventory cells

______________________________________________________________________________	

invheight: height in inventory cells

______________________________________________________________________________

hasinv: 1 can be socketed,0 cannot be socketed (You need to set MaxSock 1/25/40 in itemtypes.txt to at least 1 to have sockets in the item)

________________________________________________________________________

gemsockets: maximum number of sockets

______________________________________________________________________________

gemapplytype: gem effecs 0=weapon, 1=armor/helm, 2=shield (If you add a higher value it wouldn't add the socket)

______________________________________________________________________________

fflippyfile: flip gfx (dropping gfx)

______________________________________________________________________________

invfile: inventory gfx

______________________________________________________________________________

uniqueinvfile: unique inventory gfx

______________________________________________________________________________

special:special: Not used, Comment field.

______________________________________________________________________________

Transmogrify: Whether or not the item can be right clicked and be changed into another item

______________________________________________________________________________

TMogType: The 3 character code which respresents the item that this item becomes when right clicked (see Transmogrify)

______________________________________________________________________________

TMogMin: Min quantity appearing of the item in Transmogrify

______________________________________________________________________________

TMogMax: Min quantity appearing of the item in Transmogrify

______________________________________________________________________________

useable: 0=you cannot rightclick, 1=you can rightclick on this item

______________________________________________________________________________

throwable: can this item be thrown 1=yes, 0=no

______________________________________________________________________________

type: first base type (code from itemtypes.txt)

______________________________________________________________________________

type2: second base type (code from itemtypes.txt)
______________________________________________________________________________

dropsound: tells what sound you use when the item is dropped. The name it uses is from Sound column in sounds.txt

______________________________________________________________________________

dropsfxframe: Number of frames the sound will use when dropped.

_____________________________________________________________________________

usesound: tells what sound you use when the item is used. The name it uses is from Sound column in sounds.txt.

______________________________________________________________________________

unique: 1 = always unique, 0 = not always unique (This is used by questitems to have the item as always unique)

______________________________________________________________________________


transparent: unknown function

______________________________________________________________________________


transtbl: unknown function (But are always using 5)
______________________________________________________________________________


lightradius: Not used.

______________________________________________________________________________

belt: numberic Id from belts.txt (defines number of potion slots)
______________________________________________________________________________


autobelt: Whether or not the item appears in your belt when picked up

______________________________________________________________________________


stackable: can this item be stacked 1=yes, 0=no

______________________________________________________________________________
minstack: min ammount of quantity

______________________________________________________________________________


maxstack: max ammount quantity

______________________________________________________________________________


spawnstack: when randomly spawned, how many in a stack

______________________________________________________________________________


quest: sets if this item is a ques titem

______________________________________________________________________________


questdiffcheck: sets in what difficulty this item is a quest item.

______________________________________________________________________________


missiletype: missile to shoot if you throw this item (id from missiles.txt)

______________________________________________________________________________


spellicon: Which spellicon should be used, when you use the item (eg. the throwing-icon for jav's )

______________________________________________________________________________


pSpell: All temporary potions can use pSpell = 6. This is a parameter for the function that handles the temporary items.

______________________________________________________________________________


state: this parameter is for Overlay effect. this is only visualeffect. (state and cstate1 needs to be the same stat id from states.txt)

______________________________________________________________________________


cstate1: this parameter is used to get a stat from states.txt. It's really important that you remember what stat you have choose when you are going to use stat1. Othervise you will get the known bug, or what it actually is a missunderstanding of how 
temporary items works.

______________________________________________________________________________


cstate2: this is a second parameter. See cstate1 for more information. But you can add two different states to an item.

______________________________________________________________________________


len: This parameter is used to set the time for the temporal items. This cannot be 0.

______________________________________________________________________________

stat1: This tells what stat to add to the player. This stat is entered in cstate1 stat id.

______________________________________________________________________________


calc1: This is what value you want to add.

______________________________________________________________________________

stat2: This tells what stat to add to the player.
This stat is entered in cstate2 stat id.

______________________________________________________________________________


calc1: This is what value you want to add.

_____________________________________________________________________________



calc2: This is what value you want to add.

_____________________________________________________________________________



stat3: This tells what stat to add to the player.

]_____________________________________________________________________________


calc3: This is what value you want to add.

______________________________________________________________________________


spelldesc:
0 = don't use any description or calculation.
1 = use spelldescrtr only
2 = use spelldescrtr and spelldesccalc.

]_____________________________________________________________________________

spelldescstr: This gives an description to your temporal item what it does.

]_____________________________________________________________________________



spelldesccalc: This shows the total effect of all your items for this stats based on stat1-3.

______________________________________________________________________________


durwarning: the dur warning icon to display when the item is about to break

______________________________________________________________________________

_
qntwarning: quantity warning icon to display if you wasted most of the stack

______________________________________________________________________________


gemoffset: unknown

_______________________________________________________________________________

nameable: 1=can be personalized, 0=cannot be

_______________________________________________________________________________

BetterGem: (Gems only) What gem code is the next step up when it's upgraded by a shrine or cube (non=none,else follow "code")

______________________________________________________________________________

bitfield1: set to 1 for leather items, to 3 for metal ones.
______________________________________________________________________________

Vendor Columns: (replace Vendor with the vendor name aka CharsiMin etc)

______________________________________________________________________________

VendorsMin: minimum amount of items of this type the vendor can sell

______________________________________________________________________________

VendorsMax: maximum amount of items of this type the vendor can sell

______________________________________________________________________________

VendorsMagicMin: minimum amount of magic items of this type the vendor can sell

______________________________________________________________________________

VendorsMagicMax: maximum amount of magic items of this type the vendor can sell

______________________________________________________________________________


vendorsMagicLvl: Max magic level an item can get from the affixes.

______________________________________________________________________________

Source Art: unknown

______________________________________________________________________________

Game Art: unknown

______________________________________________________________________________

Transform and invTrans : Index telling which colormap .dat to use for this item
(like 1=dataglobalitemspalettegrey.dat, 8=dataglobalitemspaletteinvgreybrown.dat).
This is telling what are the pixels that will change colors
(only transform brown pixels to dark green ? transform all pxiels to dark green ?). For details, check http://d2mods.xfernet.com/colormaps.php
Transform is for the Animation of the player, while InvTrans is for the
Inventory gfx

_______________________________________________________________________________[u[/u]

SkipName: for items like the viper amulet (which dosent say viperamulet two times) (skips the base name)

______________________________________________________________________________	

NightmareUpgrade: item code of the item the vendor will sell instead

of this item on NM (xxx=no change)
______________________________________________________________________________

HellUpgrade: item code of the item the vendor will sell instead of this item on HELL (xxx=no change)

______________________________________________________________________________


mindam: smite damage for shields/kick damage for boots

______________________________________________________________________________


maxdam: smite damage for shields/kick damage for boots (maximum)

______________________________________________________________________________

PermStoreItem: Boolean will item always be sold by sellers? Item cannot be depletedmultibuy - 0 = Multibuy is not used, 1 = Multibuy is used, when you right click and buying a potion. It will fill up
your belt.
.

______________________________________________________________________________


nameable: 1=can be personalized, 0=cannot be personalized

______________________________________________________________________________

*eol: End of Line

(Formatting by Lord_Drekas)

*/

/*
name:物品参考名,注释用.
*name:同上.
szFlavorText:未知参数
compactsave:1=压缩存档，0=不压缩存档。说明：通常可以使存档更加小，但是诸如与物品有关的“数量”、“魔法前后缀”、“耐久度”等数值将被忽略(主要用于“药水”一类的物品)。
version:物品的版本，0=原版, 100=资料片(如果一个物品的此项数值被设定为100的话，那么它将无法在原版中出现)。
level:物品级别.
levelreq:角色使用该物品所需要的级别.
rarity:0=从装备架中剔除此类物品的任何信息;1或者更大的数字可以调整此类物品的掉宝率。说明:你至少应该拥有1个以上的此项数值不为零的装备，否则游戏就会出错而无法正常运行.
spawnable:是否能够被NPC出售.1=能够被NPC出售,0=无法出售.
speed:控制速度的参数;Possitive value(正值)=速度减慢,negative value(负值)=提升速度.
nodurability:1=无法破坏;0=使用耐久度(durability)值;
cost:价格.
gamble cost:只是用于Amulete/Rings.
code:内部代码;为3个字节(数字或者字母),unique物品必需,定制自己的物品时必备.
alternategfx:DCC代码.说明:当角色使用此物品时所采用的动作.制作动画时使用.
namestr:如果对于物品名称的相应TBL文件中没有定义此物品的名称,就采用这里的名字.如需要,需玩家将名称加入TBL文件中．
component:角色使用此物品时，采用哪一层(Layer);同composit.txt文件关.说明:composit.txt中值从0(HD)到15(S8)的16行．16表示无动画.
invwidth:物品在物品栏中的宽度.
invheight:物品在物品栏中的高度.
hasinv:物品能否被打孔.1=能打孔,0=不能打孔.说明:itemtypes.txt文件中的MaxSock 1/25/40参数下确定孔的数量,修改方法见相关教程，小站上有介绍.
gemsockets:物品所允许的最大孔数.
gemapplytype:宝石类物品所产生的影响;0=武器,1=装备/头盔,2=防具.(其他值无效).
flippyfile:掉落时采用的影象(gfx).
invfile:物品栏中采用的影象(gfx).
uniqueinvfile:unique物品采用的影象(gfx).
special:未使用,注释区.
Transmogrify:物品能否被右键点击是否变为另一物品(item),如id roll.
TMogType:物品被右击时变成的物品code(见Transmogrify).
TMogMin:出现在Transmogrify中物品的最小数量.
TMogMax:出现在Transmogrify中物品的最大数量.
useable:设定右击参数.0=不可以被右键点击,1=可以．
throwable:能否被投掷;1=可以,0=不可以.
type:基本类型(与itemtypes.tx.t关联).
type2:次要类型(与itemtypes.tx.t关联).
dropsound:物品掉落时声音;同sounds.txt关联.
dropsfxframe:物品掉落时的声音采用多少祯.
usesound:物品使用时的声音;同sounds.txt关联.
unique:1=永久性unique物品,0=非永久性unique物品.(任务物品一般是永久性物品,如方块).
transparent:未知参数．
transtbl:未知参数，一般使用5．
lightradius:未使用.
belt:同belts.txt中的数字ID(定义药水的放置数量).
autobelt:物品被捡起时是否出现在腰带中.
stackable:是否为一个整体(比如说"弓箭" ;1=是,0=不是.
minstack:作为整体的最小数量.
maxstack:作为整体的最大数量.
spawnstack:一次售出时的数量.
quest:任务物品时设置.
questdiffcheck:设置任务物品出现在哪个难度.(这两项只对任务物品)
missiletype:如果是投掷物品的,所施放出的Missile数量(同missiles.txt关联).
spellicon:角色使用此物品时采用的图标(spellicon)?,如jav的投掷图标.
pSpell:所有临时性(temporary)药剂使用pSpell=6.处理临时性物品的参数（关于此参数的更多信息，可以查看“资源”栏目中的“Psepll参数全分析”）.
state:持续作用参数(如解毒，融化),只是视觉上的效果.(和cstate1有相同的stat id,与states.txt关联).
cstate1:状态参数,与states.txt关联，从后者获取一个状态.使用stat1时，务必记住你已经选择的状态以保持一致，否则将产生bug.
cstate2:次要参数，相关信息见cstate1.你可以对一件物品加上两个状态.
len:临时性物品持续作用时间参数，不能为0.
stat1:玩家状态1,以cstates1的状态id为入口.如冰冻抵抗.
calc1:设定状态值.
stat2:玩家状态2,以cstates2的状态id为入口.
calc2:设定状态值.
stat3:玩家状态3,无用参数.
calc3:设定状态值,无用参数.
spelldesc:0=不使用任何描述或计算.
1:只使用spelldescstr.
2:使用spelldescstr和spelldesccalc．
spelldescstr:对临时性物品所起作用的描述.
spelldesccalc:状态(stat1-3)总效果计算值.
durwarning:在耐久度降低到多少时出现物品损坏提示(屏幕右方的损坏提示).
qntwarning:如果作为整体物品,数量在下降到多少时出现数量不足提示.
gemoffset:未知参数.
BetterGem:宝石(gem)通过宝石神殿或方块cube升级后的代码(只对宝石有效)，non=没有,其他为"code"值.
bitfield1:装备的内部定义类型.1为布类物品;3为金属类物品.如AkaraMin等等.
Vendor Columns:NPC名字的代替vendor即是每个NPC的以下五行参数.如
VendorsMin:NPC能出售的该物品最小数量.
VendorsMax:NPC能出售的该物品最大数量.
VendorsMagicMin:NPC出售这件物品时其所能包含的魔法属性的最少项.
VendorsMagicMax:NPC出售这件物品时其所能包含的魔法属性的最多项.
VendorsMagicLvl:魔法类物品在出售时所能包含的最大的魔法前后缀级别.同MagicPrefix.txt,MagicSuffix,AutoMagic三个文件关联.
Source Art:未知参数.
Game Art:未知参数.
Transform and invTrans:索引,告诉程序使用哪一个整体动作.
SkipName:是否跳过最初的名称,比如说:viper amulet.
NightmareUpgrade:在"恶梦"难度下,该物品的出售代码(xxx=无变化).
HellUpgrade:在"地狱"难度下,该物品的出售代码(xxx=无变化).
mindam:对鞋类及盾类的最小伤害值.
maxdam:对鞋类及盾类的最大伤害值.
PermStoreItem:NPC出售的该物品无数时,此项一般为1.
multibuy:一次购买时能否多个一起购买.0=不可以,1=可以.(比如当购买药剂时，右键点击可使你腰带全满).
nameable:能否被个人化(如ACT5中的Q3)1=可以,0=不可以.
*eol:行结束标志.
*/

/*
文件名解析：
misc：杂物，在这里指除装备外的一切道具。
此文件中的每一行表示一个道具。


回复

    2楼
    2011-09-07 20:27

    举报 |

    zqtjingzi
    小吧主
    12

由于此文件中的部分列已经在Armor.txthttp：//tieba。baidu。com/f?kz=1201381062或Weapons.txthttp://tieba.baidu.com/p/1201415437中出现并解释过，所以在这里只给出有区别的列的解释。

这些列的含义如下：


回复

    3楼
    2011-09-07 20:27

    举报 |

    zqtjingzi
    小吧主
    12

由于此文件中的部分列已经在
Armor.txt
http：//tieba.baidu.com/f?kz=1201381062
或Weapons.txt
http://tieba.baidu.com/p/1201415437
中出现并解释过，所以在这里只给出有区别的列的解释。

这些列的含义如下：



回复

    4楼
    2011-09-07 20:28

    举报 |

    zqtjingzi
    小吧主
    12

*name：名字的注释

szFlavorText：不知道什么意思的参数，但所有项在此列都没有值。

special：不知道什么意思的参数，但所有项在此列都没有值。

Transmogrify：物品能否被右键点击而变为另一物品，在单机版中似乎没有用到过，但战网中的骰子好像就使用了这一列。

TMogType：当物品被右键点击时变成的物品代码。若不可变或不变可填xxx。

TMogMin：所变成物品的最小数量。

TMogMax：所变成物品的最大数量。

lightradius：不知道什么意思的参数，但在游戏中应该没有被使用。

autobelt：物品被捡起时是否自动出现在腰带中。0代表否，1代表是。

spawnstack：物品生成时的最大数目，一般与maxStack一致。

spellicon：角色使用此物品时在技能栏所采用的图标，一般都用-1，表示用默认值。



回复

    5楼
    2011-09-07 20:29

    举报 |

    zqtjingzi
    小吧主
    12

pSpell：使用此道具时采用什么样的效果。
可能的值与效果如下。
1 = 鉴定卷轴/鉴定之书。
2 = 回城卷轴/回城之书；
3 = 恢复类药水；
4 = 未使用，效果未知；
5 = 百分比恢复类药水（如100%全恢复药水）；
6 = 投掷药水；
7 = 赫拉迪克方块；
8 = 可以被Elixir药水使用，主要功能就是提升经验值；
9 = 耐力值药水或者草药；


回复

    6楼
    2011-09-07 20:29

    举报 |

    zqtjingzi
    小吧主
    12

state：使用此道具对人物状态的影响，与states.txt关联。

cstate1-2：激活state效果的条件，与states.txt关联。若此两列均为空，则始终触发state效果。否则人物当前状态必须与此两列其中一列相符才激活state状态。如只有当中毒后才会激发解毒效果。

len：此道具的持续作用时间，若不需要此项则不填，不能填0。

stat1-3：使用此道具后的效果。

calc1-3：效果参数。

SpellDesc：是否有额外的效果。0代表没有，1代表用SpellDescStr描述额外效果，2代表用SpellDescStr和SpelldescCalc描述额外效果。

spelldescstr：额外效果的效果描述。

spelldesccalc：额外效果的效果参数。

BetterGem：高一级宝石的指针，如无瑕疵的钻石此列的值为完美钻石的代码。非宝石类此列填non。

*/

typedef struct
{//total 424 bytes
    unsigned char vflippyfile[32];  //物品外观所使用的图标指针。
    unsigned char vinvfile[32];     //物品在物品栏中所使用的图标指针。
    unsigned char vuniqueinvfile[32];   //此装备底材对应的唯一物品（暗金）所使用的图标指针。

    unsigned char acPadding[32];

    unsigned char vcode[4]; //32 物品代码。

    unsigned char acPad2[12];

    unsigned char valternategfx[4]; //当角色使用此物品时所采用的动作。

    unsigned int vpSpell;  //使用此道具时采用什么样的效果。
    /*
    可能的值与效果如下。
    1 = 鉴定卷轴/鉴定之书。
    2 = 回城卷轴/回城之书；
    3 = 恢复类药水；
    4 = 未使用，效果未知；
    5 = 百分比恢复类药水（如100%全恢复药水）；
    6 = 投掷药水；
    7 = 赫拉迪克方块；
    8 = 可以被Elixir药水使用，主要功能就是提升经验值；
    9 = 耐力值药水或者草药；
    */

    unsigned short vstate;  //使用此道具对人物状态的影响，与states.txt关联。
    unsigned short vcstate1;//激活state效果的条件，与states.txt关联。若此两列均为空，则始终触发state效果。否则人物当前状态必须与此两列其中一列相符才激活state状态。如只有当中毒后才会激发解毒效果。
    unsigned short vcstate2;//激活state效果的条件，与states.txt关联。若此两列均为空，则始终触发state效果。否则人物当前状态必须与此两列其中一列相符才激活state状态。如只有当中毒后才会激发解毒效果。
    unsigned short vstat1;  //使用此道具后的效果。
    unsigned short vstat2;  //使用此道具后的效果。
    unsigned short vstat3;  //使用此道具后的效果。

    unsigned int vcalc1;    //41 ItemsCode
    unsigned int vcalc2;
    unsigned int vcalc3;

    unsigned int vlen;  //44 ItemsCode

    unsigned short vspelldesc;   //是否有额外的效果。0代表没有，1代表用SpellDescStr描述额外效果，2代表用SpellDescStr和
    unsigned short vspelldescstr;   //strings

    unsigned int vspelldesccalc;    //46 ItemsCode

    unsigned char vBetterGem[4];    //高一级宝石的指针，如无瑕疵的钻石此列的值为完美钻石的代码。非宝石类此列填non。

    unsigned char acPad6[8];

    unsigned char vTMogType[4]; //当物品被右键点击时变成的物品代码。若不可变或不变可填xxx。

    unsigned char acPad7[8];

    unsigned int vgamblemyspcost;   //53 看名字应该是别人在你这赌博时出的价格，但实际上没有这个功能，所以此列应该没有作用。可以肯定的是此列不影响赌博时的价格。

    unsigned char vspeed;   //此防具对速度的降低程度。0代表不降低，数字越大速度越慢。
    unsigned char acPad9[3];

    unsigned char vbitfield1;   //装备的内部定义类型。说明：1为布类物品；3为铁类物品。
    unsigned char acPad10[3];

    unsigned int vcost;   //物品卖出时的基础价格。

    unsigned int vminstack; //可叠加物品生成时的最小数量。
    unsigned int vmaxstack; //可叠加物品一摞的的最大数量。
    unsigned int vspawnstack;   //物品生成时的最大数目，一般与maxStack一致。

    unsigned short vgemoffset;  //不知道什么意思的参数，但都填0。
    unsigned char acPad12[2];

    unsigned short vnamestr;    //名字索引，即tbl中的键名，实际上与Code总是保持一致，不理解为什么要单做此列。
    unsigned char vversion; //物品所适用版本。按轻寒的说法是0代表1.07之前的版本，1代表1.07之后的非资料片版本，100代表资料片。虽然本人没有那么些版本可供实验，但本人相信轻寒的话。
    unsigned char acPad13[1];

    unsigned short vautomyspprefix;//62 自动附带属性。如法球的加血加蓝，圣骑专用盾的加伤害和准确率。与AutoMagic.txt关联。
    unsigned char vmissiletype; //投掷物品专用。投掷出的物品的类型，同missiles.txt文件关联。
    unsigned char bPad;

    unsigned char vrarity;  //稀有度。在同一TC中出现的概率，值越大掉落的概率越大。请参考物品掉落原理。
    unsigned char vlevel;   //物品等级。含义请参考轻寒的物品掉落原理。
    unsigned char vmindam;  //最小伤害值。防具中只有盾牌（盾击）可鞋子（踢击）使用此属性。
    unsigned char vmaxdam;  //最大伤害值。防具中只有盾牌（盾击）可鞋子（踢击）使用此属性。

    unsigned char acPad14[15];
    unsigned char vinvwidth;    //物品在物品栏中的宽度。

    unsigned char vinvheight;   //68 物品在物品栏中的高度。
    unsigned char acPad15[2];
    unsigned char vnodurability;    //没有耐久度，即天生无法破坏。如幻化之刃，但防具中暂时没有。

    unsigned char bPad2;
    unsigned char vcomponent;   //角色使用此物品时，采用哪一层（Layer）；同文件关联。这是我抄来的，我也没理解。
    unsigned char acPad16[7];
    unsigned char vuseable; //能否用右键使用。0表示不可以，1表示可以。
    unsigned short vtype;    //基本类型。同itemtypes.txt关联。

    unsigned short vtype2;   //次要类型；同itemtypes.txt关联。
    unsigned char acPad17[2];

    unsigned short vdropsound;  //物品掉落时的声音；同sounds.txt关联。
    unsigned short vusesound;   //物品使用时的声音；同sounds.txt关联。

    unsigned char vdropsfxframe;    //物品掉落时动画所占的祯数。
    unsigned char vunique;  //此物品是否只能是唯一（暗金）物品。0表示不是，1代表是。如吉得宝此列为1，但在防具中目前还没有这样的物品。
    unsigned char vquest;   //任务物品专用，所属任务的编号。
    unsigned char vquestdiffcheck;  //

    unsigned char vtransparent; //不知道什么意思的参数，但都填0。
    unsigned char vtranstbl;    //不知道什么意思的参数，但都填5。
    unsigned char bPad4;
    unsigned char vlightradius; //不知道什么意思的参数。

    unsigned char vbelt;    //腰带专用，表示在belts.txt中的位置。
    unsigned char vautobelt;    //物品被捡起时是否自动出现在腰带中。0代表否，1代表是。
    unsigned char vstackable;   //同种物品能否叠加。0表示不可以，1表示可以。如箭矢此列为1。
    unsigned char vspawnable;   //是否可在游戏中生成。1代表可以，0代表不可以。不出意外此列都是1。

    char vspellicon;    //角色使用此物品时在技能栏所采用的图标，一般都用-1，表示用默认值。
    unsigned char vdurwarning;  //在耐久度降低到多少时出现物品损坏提示（就是屏幕右方的图标提示）。
    unsigned char vqntwarning;  //可叠加物品专用，在数量在下降到多少时出现数量不足提示。
    unsigned char vhasinv;  //物品是否能够被打孔；1能够打孔，0不能打孔。

    unsigned char vgemsockets;  //物品所允许的最大孔数，不能超过此物品所属类别的最大孔数，否则以类别的为准。
    unsigned char vTransmogrify;    //物品能否被右键点击而变为另一物品，在单机版中似乎没有用到过，但战网中的骰子好像就使用了这一列。
    unsigned char vTMogMin; //所变成物品的最小数量。
    unsigned char vTMogMax; //所变成物品的最大数量。

    unsigned char acPad18[2];
    unsigned char vgemapplytype;    //此物品在镶嵌上宝石类物品后使用宝石的那种效果：0=武器；1=装备/头盔；2=防具。
    unsigned char vlevelreq;    //装备的等级需求。

    unsigned char bPad5;
    unsigned char vTransform;   //动作索引。
    unsigned char vInvTrans;    //动作索引。以上两列据说要协同使用。
    unsigned char vcompactsave; //此物品是否被压缩存储。0代表不压缩，1代表压缩。往往只有**、钥匙这样的没有本身属性的将此列置为1，以节省存储空间。

    unsigned char vSkipName;    //是否不显示底材的名字。如吉得宝。
    unsigned char vNameable;    //是否能够被重命名，即能否被个人化。0表示不能，1表示能。
    unsigned char vAkaraMin;    //名字是***的NPC出售这件物品时的最小数量。
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
    unsigned char vAkaraMax;    //名字是***的NPC出售这件物品时的最大数量。

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

    unsigned char vAkaraMagicMin;   //NPC出售这件物品时其所能包含的魔法属性的最少项。此项不为0，NPC才会出售魔法物品。
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
    unsigned char vAkaraMagicMax;   //NPC出售这件物品时其所能包含的魔法属性的最多项。此项大于1，NPC才会出售有2个属性的魔法物品。
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
    unsigned char vAkaraMagicLvl;   //魔法物品在出售时所能包含的最大的魔法前后缀级别。说明：同MagicPrefix.txt、MagicSuffix、AutoMagic三个文件关联。
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
    unsigned char bPad6;

    unsigned char vNightmareUpgrade[4]; //在“恶梦”难度下，会卖这种物品的NPC改卖什么物品（xxx表示还卖这个）。如轻微治疗药剂hp1在此列的值为hp4，表示在普通难度卖轻微治疗药剂的NPC在恶梦难度改卖强力药剂了。
    unsigned char vHellUpgrade[4];  //在“地狱”难度下，会卖此种物品的NPC改卖什么物品（xxx表示还卖这个）。如轻微治疗药剂hp1在此列的值为hp5，表示在普通难度卖轻微治疗药剂的NPC在恶梦难度改卖超级治疗药剂了。

    unsigned char vPermStoreItem;   //是否总在NPC处有出售。
    unsigned char vmultibuy;    //
    unsigned char acPad20[2];
} ST_LINE_INFO;

typedef struct
{
    unsigned char vcode[5];
} ST_MISC;

static char *m_apcInternalProcess[] =
{
    "name",
    "*eol",
    NULL,
};

static char *m_apcNotUsed[] = 
{
    "*name",
    "throwable",
    "szFlavorText",
    "Source Art",
    "Game Art",
    "special",
    NULL,
};

static unsigned int m_iMiscCount = 0;
static ST_MISC *m_astMisc = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astMisc, ST_MISC);

char *Misc_GetItemUniqueCode(unsigned int id)
{
    unsigned int iWeaponCnt, iArmorCnt, iMiscCnt;

    iWeaponCnt = Weapons_GetWeaponCount();
    iArmorCnt = Armor_GetArmorCount();
    iMiscCnt = m_iMiscCount;

    //weapon
    if ( id < iWeaponCnt )
    {
        return Weapons_GetWeaponCode(id);
    }

    id -= iWeaponCnt;
    //armor
    if ( id < iArmorCnt )
    {
        return Armor_GetArmorCode(id);
    }

    id -= iArmorCnt;
    //misc
    if ( id < iMiscCnt )
    {
        return m_astMisc[id].vcode;
    }

    return NULL;
}

static int Misc_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
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
            sprintf(acOutput, "%s%u", NAME_PREFIX, iLineNo);
        }

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

static int Misc_ConvertValue_Pre(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    int result = 0;

    if ( !strcmp(acKey, "code") )
    {
        strncpy(m_astMisc[m_iMiscCount].vcode, pstLineInfo->vcode, sizeof(pstLineInfo->vcode));
        String_Trim(m_astMisc[m_iMiscCount].vcode);
        m_iMiscCount++;
    }

    return result;
}

static int Misc_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "type") )
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
    else if ( !strcmp(acKey, "dropsound") )
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
    else if ( !strcmp(acKey, "state") )
    {
        pcResult = States_GetStateName(pstLineInfo->vstate);
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
    else if ( !strcmp(acKey, "cstate1") )
    {
        pcResult = States_GetStateName(pstLineInfo->vcstate1);
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
    else if ( !strcmp(acKey, "cstate2") )
    {
        pcResult = States_GetStateName(pstLineInfo->vcstate2);
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
    else if ( !strcmp(acKey, "stat1") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vstat1);
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
    else if ( !strcmp(acKey, "stat2") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vstat2);
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
    else if ( !strcmp(acKey, "stat3") )
    {
        pcResult = ItemStatCost_GetStateName(pstLineInfo->vstat3);
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
            strcpy(acOutput, pstLineInfo->vcode);
        }
        result = 1;
    }
    else if ( !strcmp(acKey, "spelldescstr") )
    {
        pcResult = String_FindString(pstLineInfo->vspelldescstr, "dummy");
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
    else if ( !strcmp(acKey, "rarity") )
    {
        if ( (999 % 256) == pstLineInfo->vrarity )
        {
            strcpy(acOutput, "999");
            result = 1;
        }
    }
    else if ( !strcmp(acKey, "calc1") )
    {
        pcResult = ItemsCode_GetExpression(pstLineInfo->vcalc1);
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
    else if ( !strcmp(acKey, "calc2") )
    {
        pcResult = ItemsCode_GetExpression(pstLineInfo->vcalc2);
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
    else if ( !strcmp(acKey, "calc3") )
    {
        pcResult = ItemsCode_GetExpression(pstLineInfo->vcalc3);
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
    else if ( !strcmp(acKey, "len") )
    {
        pcResult = ItemsCode_GetExpression(pstLineInfo->vlen);
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
    else if ( !strcmp(acKey, "spelldesccalc") )
    {
        pcResult = ItemsCode_GetExpression(pstLineInfo->vspelldesccalc);
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

static void Misc_InitValueMap(ST_VALUE_MAP *pstValueMap, ST_LINE_INFO *pstLineInfo)
{
    INIT_VALUE_BUFFER;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, flippyfile, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invfile, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, uniqueinvfile, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, code, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, alternategfx, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, pSpell, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, state, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cstate1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cstate2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stat1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stat2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stat3, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, spelldesc, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, spelldescstr, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BetterGem, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TMogType, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gamblemyspcost, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, speed, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, bitfield1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, cost, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, minstack, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, maxstack, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, spawnstack, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gemoffset, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, namestr, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, version, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, missiletype, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rarity, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, level, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mindam, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, maxdam, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, automyspprefix, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invwidth, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invheight, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, nodurability, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, component, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, useable, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, type, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, type2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dropsound, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, usesound, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dropsfxframe, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, unique, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, quest, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, questdiffcheck, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, transparent, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, transtbl, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lightradius, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, belt, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, autobelt, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, stackable, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, spawnable, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, spellicon, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, durwarning, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, qntwarning, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, hasinv, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gemsockets, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Transmogrify, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TMogMin, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TMogMax, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gemapplytype, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, levelreq, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Transform, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InvTrans, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, compactsave, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SkipName, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Nameable, UCHAR);
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

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PermStoreItem, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, multibuy, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, calc1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, calc2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, calc3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, len, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, spelldesccalc, UINT);
}

int process_misc(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            MODULE_DEPEND_CALL(armor, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(weapons, acTemplatePath, acBinPath, acTxtPath);

            Misc_InitValueMap(pstValueMap, pstLineInfo);

            m_iMiscCount = 0;

            m_stCallback.pfnConvertValue = Misc_ConvertValue_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(itemtypes, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(sounds, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(states, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(itemstatcost, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(string, acTemplatePath, acBinPath, acTxtPath);

            if ( 0 == ItemsCode_ParseBin(acTemplatePath, acBinPath, acTxtPath) )
            {
                return 0;
            }
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            Misc_InitValueMap(pstValueMap, pstLineInfo);

            m_stCallback.pfnConvertValue = Misc_ConvertValue;
            m_stCallback.pfnFieldProc = Misc_FieldProc;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

