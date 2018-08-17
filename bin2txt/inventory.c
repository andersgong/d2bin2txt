#include "global.h"

#define FILE_PREFIX "inventory"
#define NAME_PREFIX "iv"

/*
class - a comment field used to describe what this line refers to.

invLeft - left edge of the screen (x).
invRight - right edge of the screen (invLeft + DC6_WIDTH).
invTop - top edge of the screen (y).
invBottom - bottom edge of the screen (invTop + DC6_HEIGHT).

gridX - number of columns in the item grid.
gridY - number of rows in the item grid.
gridLeft - left edge of the grid (x).
gridRight - right edge of the grid (gridLeft + gridBoxWidth * gridX) *see note
gridTop - top edge of the grid (y).
gridBottom - bottom edge of the grid (gridTop + gridBoxHeight * gridY) *see note
gridBoxWidth - the width of each grid cell.
gridBoxHeight - the height of each grid cell.

rArmLeft - the left edge of the right weapon slot (x).
rArmRight - the right edge of the right weapon slot (rArmLeft + rArmWidth).
rArmTop - the top edge of the right weapon slot (y).
rArmBottom - the bottom edge of the right weapon slot (rArmTop + rArmHeight).
rArmWidth - width of the right weapon slot.
rArmHeight - height of the right weapon slot.

torsoLeft - the left edge of the body armor slot (x).
torsoRight - the right edge of the body armor slot (torsoLeft + torsoWidth).
torsoTop - the top edge of the body armor slot (y).
torsoBottom - the bottom edge of the body armor slot (torsoTop + torsoHeight).
torsoWidth - width of the body armor slot.
torsoHeight - height of the body armor slot.

lArmLeft - the left edge of the left weapon slot (x).
lArmRight - the right edge of the left weapon slot (lArmLeft + lArmWidth).
lArmTop - the top edge of the left weapon slot (y).
lArmBottom - the bottom edge of the left weapon slot (lArmTop + lArmHeight).
lArmWidth - width of the left weapon slot.
lArmHeight - height of the left weapon slot.

helmLeft - the left edge of the head gear slot (x).
helmRight - the right edge of the head gear slot (helmLeft + helmWidth).
helmTop - the top edge of the head gear slot (y).
helmBottom - the bottom edge of the head gear slot (helmTop + helmHeight).
helmWidth - width of the head gear slot.
helmHeight - height of the head gear slot.

neckLeft - the left edge of the amulet slot (x).
neckRight - the right edge of the amulet slot (neckLeft + neckWidth).
neckTop - the top edge of the amulet slot (y).
neckBottom - the bottom edge of the amulet slot (neckTop + neckHeight).
neckWidth - width of the amulet slot.
neckHeight - height of the amulet slot.

rHandLeft - the left edge of the right ring slot (x).
rHandRight - the right edge of the right ring slot (rHandLeft + rHandWidth).
rHandTop - the top edge of the right ring slot (y).
rHandBottom - the bottom edge of the right ring slot (rHandTop + rHandHeight).
rHandWidth - width of the right ring slot.
rHandHeight - height of the right ring slot.

lHandLeft - the left edge of the left ring slot (x).
lHandRight - the right edge of the left ring slot (lHandLeft + lHandWidth).
lHandTop - the top edge of the left ring slot (y).
lHandBottom - the bottom edge of the left ring slot (lHandTop + lHandHeight).
lHandWidth - width of the left ring slot.
lHandHeight - height of the left ring slot.

beltLeft - the left edge of the belt slot (x).
beltRight - the right edge of the belt slot (beltLeft + beltWidth).
beltTop - the top edge of the belt slot (y).
beltBottom - the bottom edge of the belt slot (beltTop + beltHeight).
beltWidth - width of the belt slot.
beltHeight - height of the belt slot.

feetLeft - the left edge of the boot slot (x).
feetRight - the right edge of the boot slot (feetLeft + feetWidth).
feetTop - the top edge of the boot slot (y).
feetBottom - the bottom edge of the boot slot (feetTop + feetHeight).
feetWidth - width of the boot slot.
feetHeight - height of the boot slot.

gloveLeft - the left edge of the glove slot (x).
gloveRight - the right edge of the glove slot (gloveLeft + gloveWidth).
gloveTop - the top edge of the glove slot (y).
gloveBottom - the bottom edge of the glove slot (gloveTop + gloveHeight).
gloveWidth - width of the glove slot.
gloveHeight - height of the glove slot.

* Blizzard screwed this up a little bit, their values are off by a few pixels.

*/

/*
第一列参数 — 参数说明
Amazon — 亚马逊物品放置空间（640×480 像素分辨率）
Sorceress — 法师物品放置空间（640×480 像素分辨率）
Necromancer — 死灵法师物品放置空间（640×480 像素分辨率）
Paladin — 圣骑士物品放置空间（640×480 像素分辨率）
Barbarian — 野蛮人物品放置空间（640×480 像素分辨率）
Monster — 交易买卖对话窗口物品放置空间（640×480 像素分辨率）
Trade Page 1 — 多人游戏物品交换窗口上面放置空间（640×480 像素分辨率）
Trade Page 2 — 多人游戏物品交换窗口下面放置空间（640×480 像素分辨率）
Bank Page 1 — 储物箱空间（640×480 像素分辨率）[对应原版]
Transmogrify Box Page 1 — Horadric Cube 放置空间（640×480 像素分辨率）
Guild Vault Page 1 — 未使用的公共放置空间（640×480 像素分辨率）
Trophy Case Page 1 — 未使用的奖励放置空间（640×480 像素分辨率）
Expansion — Expansion
Big Bank Page 1 — 储物箱空间（640×480 像素分辨率）[对应资料片]
Hireling — 雇佣兵物品放置空间（640×480 像素分辨率）
Druid — 德鲁依物品放置空间（640×480 像素分辨率）
Assassin — 刺客物品放置空间（640×480 像素分辨率）
Amazon2 — 亚马逊物品放置空间（800×600 像素分辨率）
Sorceress2 — 法师物品放置空间（800×600 像素分辨率）
Necromancer2 — 死灵法师物品放置空间（800×600 像素分辨率）
Paladin2 — 圣骑士物品放置空间（800×600 像素分辨率）
Barbarian2 — 野蛮人物品放置空间（800×600 像素分辨率）
Monster2 — 交易买卖对话窗口物品放置空间（800×600 像素分辨率）
Trade Page 1-2 — 多人游戏物品交换窗口上面放置空间（800×600 像素分辨率）
Trade Page 2-2 — 多人游戏物品交换窗口下面放置空间（800×600 像素分辨率）
Bank Page2 — 储物箱空间（800×600 像素分辨率）[对应原版]
Transmogrify Box2 — Horadric Cube 放置空间（800×600 像素分辨率）
Guild Vault Page2 — 未使用的公共放置空间（800×600 像素分辨率）
Trophy Case Page2 — 未使用的奖励放置空间（800×600 像素分辨率）
Big Bank Page2 — 储物箱空间（800×600 像素分辨率）[对应资料片]
Hireling2 — 雇佣兵物品放置空间（800×600 像素分辨率）
Druid2 — 德鲁依物品放置空间（800×600 像素分辨率）
Assassin2 — 刺客物品放置空间（800×600 像素分辨率）

第一行参数 — 参数说明
Class — 储存空间处理数据（只作参考标志）
InvLeft — 横坐标或Ｘ坐标—标示图像左边边界的横坐标在屏幕上的相对定位坐标值
InvRight — 横坐标或Ｘ坐标—标示图像右边边界的横坐标在屏幕上的相对定位坐标值
InvTop — 竖坐标或Ｙ坐标—标示图像上部边界的竖坐标在屏幕上的相对定位坐标值
InvBottom — 竖坐标或Ｙ坐标—标示图像底部边界的竖坐标在屏幕上的相对定位坐标值

储存空间相关设定：
GridX — 储存空间每列的格数
GridY — 储存空间每行的格数
GridLeft — 横坐标或Ｘ坐标—标示储存空间左边边界的横坐标在屏幕上的相对定位坐标值
GridRight — 横坐标或Ｘ坐标—标示储存空间右边边界的横坐标在屏幕上的相对定位坐标值
GridTop — 竖坐标或Ｙ坐标—标示储存空间上部边界的竖坐标在屏幕上的相对定位坐标值
GridBottom — 竖坐标或Ｙ坐标—标示储存空间底部边界的竖坐标在屏幕上的相对定位坐标值
GridBoxWidth — 每个格了的宽度（像素值），黙认每格尺寸是29×29，因此通常取值是29。
GridBoxHeight — 每个格了的高度（像素值），黙认每格尺寸是29×29，因此通常取值是29。

人物物品装备空间相关设定：
rArmLeft — 横坐标或Ｘ坐标—标示右臂（武器或盾）装备空间左边边界的横坐标在屏幕上的相对定位坐标值
rArmRight — 横坐标或Ｘ坐标—标示右臂（武器或盾）装备空间右边边界的横坐标在屏幕上的相对定位坐标值
rArmTop — 竖坐标或Ｙ坐标—标示右臂（武器或盾）装备空间上部边界的竖坐标在屏幕上的相对定位坐标值
rArmBottom — 竖坐标或Ｙ坐标—标示右臂（武器或盾）装备空间底部边界的竖坐标在屏幕上的相对定位坐标值
rArmWidth — 右臂（武器或盾）装备空间的宽度（像素值）
rArmHeight — 右臂（武器或盾）装备空间的高度（像素值）

TorsoLeft — 横坐标或Ｘ坐标—标示躯干（装甲）装备空间左边边界的横坐标在屏幕上的相对定位坐标值
TorsoRight — 横坐标或Ｘ坐标—标示躯干（装甲）装备空间右边边界的横坐标在屏幕上的相对定位坐标值
TorsoTop — 竖坐标或Ｙ坐标—标示躯干（装甲）装备空间上部边界的竖坐标在屏幕上的相对定位坐标值
TorsoBottom — 竖坐标或Ｙ坐标—标示躯干（装甲）装备空间底部边界的竖坐标在屏幕上的相对定位坐标值
TorsoWidth — 躯干（装甲）装备空间的宽度（像素值）
TorsoHeight — 躯干（装甲）装备空间的高度（像素值）

lArmLeft — 横坐标或Ｘ坐标—标示左臂（武器或盾）装备空间左边边界的横坐标在屏幕上的相对定位坐标值
lArmRight — 横坐标或Ｘ坐标—标示右臂（武器或盾）装备空间左边边界的横坐标在屏幕上的相对定位坐标值
lArmTop — 竖坐标或Ｙ坐标—标示左臂（武器或盾）装备空间上部边界的竖坐标在屏幕上的相对定位坐标值
lArmBottom — 竖坐标或Ｙ坐标—标示左臂（武器或盾）装备空间底部边界的竖坐标在屏幕上的相对定位坐标值
lArmWidth — 左臂（武器或盾）装备空间的宽度（像素值）
lArmHeight — 左臂（武器或盾）装备空间的高度（像素值）

HeadLeft — 横坐标或Ｘ坐标—标示头部（头盔）装备空间左边边界的横坐标在屏幕上的相对定位坐标值
HeadRight — 横坐标或Ｘ坐标—标示头部（头盔）装备空间右边边界的横坐标在屏幕上的相对定位坐标值
HeadTop — 竖坐标或Ｙ坐标—标示头部（头盔）装备空间上部边界的竖坐标在屏幕上的相对定位坐标值
HeadBottom — 竖坐标或Ｙ坐标—标示头部（头盔）装备空间底部边界的竖坐标在屏幕上的相对定位坐标值
HeadWidth — 头部（头盔）装备空间的宽度（像素值）
HeadHeight — 头部（头盔）装备空间的高度（像素值）

NeckLeft — 横坐标或Ｘ坐标—标示颈部（护身符）装备空间左边边界的横坐标在屏幕上的相对定位坐标值
NeckRight — 横坐标或Ｘ坐标—标示颈部（护身符）装备空间右边边界的横坐标在屏幕上的相对定位坐标值
NeckTop — 竖坐标或Ｙ坐标—标示颈部（护身符）装备空间上部边界的竖坐标在屏幕上的相对定位坐标值
NeckBottom — 竖坐标或Ｙ坐标—标示颈部（护身符）装备空间底部边界的竖坐标在屏幕上的相对定位坐标值
NeckWidth — 颈部（护身符）装备空间的宽度（像素值）
NeckHeight — 颈部（护身符）装备空间的高度（像素值）

rHandLeft — 横坐标或Ｘ坐标—标示右手（戒指）装备空间左边边界的横坐标在屏幕上的相对定位坐标值
rHandRight — 横坐标或Ｘ坐标—标示右手（戒指）装备空间右边边界的横坐标在屏幕上的相对定位坐标值
rHandTop — 竖坐标或Ｙ坐标—标示右手（戒指）装备空间上部边界的竖坐标在屏幕上的相对定位坐标值
rHandBottom — 竖坐标或Ｙ坐标—标示右手（戒指）装备空间底部边界的竖坐标在屏幕上的相对定位坐标值
rHandWidth — 右手（戒指）装备空间的宽度（像素值）
rHandHeight — 右手（戒指）装备空间的高度（像素值）

lHandLeft — 横坐标或Ｘ坐标—标示左手（戒指）装备空间左边边界的横坐标在屏幕上的相对定位坐标值
lHandRight — 横坐标或Ｘ坐标—标示左手（戒指）装备空间右边边界的横坐标在屏幕上的相对定位坐标值
lHandTop — 竖坐标或Ｙ坐标—标示左手（戒指）装备空间上部边界的竖坐标在屏幕上的相对定位坐标值
lHandBottom — 竖坐标或Ｙ坐标—标示左手（戒指）装备空间底部边界的竖坐标在屏幕上的相对定位坐标值
lHandWidth — 左手（戒指）装备空间的宽度（像素值）
lHandHeight — 左手（戒指）装备空间的高度（像素值）

BeltLeft — 横坐标或Ｘ坐标—标示腰带装备空间左边边界的横坐标在屏幕上的相对定位坐标值
BeltRight — 横坐标或Ｘ坐标—标示腰带装备空间右边边界的横坐标在屏幕上的相对定位坐标值
BeltTop — 竖坐标或Ｙ坐标—标示腰带装备空间上部边界的竖坐标在屏幕上的相对定位坐标值
BeltBottom — 竖坐标或Ｙ坐标—标示腰带装备空间底部边界的竖坐标在屏幕上的相对定位坐标值
BeltWidth — 腰带装备空间的宽度（像素值）
BeltHeight — 腰带装备空间的高度（像素值）

FeetLeft — 横坐标或Ｘ坐标—标示靴子装备空间左边边界的横坐标在屏幕上的相对定位坐标值
FeetRight — 横坐标或Ｘ坐标—标示靴子装备空间右边边界的横坐标在屏幕上的相对定位坐标值
FeetTop — 竖坐标或Ｙ坐标—标示靴子装备空间上部边界的竖坐标在屏幕上的相对定位坐标值
FeetBottom — 竖坐标或Ｙ坐标—标示靴子装备空间底部边界的竖坐标在屏幕上的相对定位坐标值
FeetWidth — 靴子装备空间的宽度（像素值）
FeetHeight — 靴子装备空间的高度（像素值）

GlovesLeft — 横坐标或Ｘ坐标—标示手套装备空间左边边界的横坐标在屏幕上的相对定位坐标值
GlovesRight — 横坐标或Ｘ坐标—标示手套装备空间右边边界的横坐标在屏幕上的相对定位坐标值
GlovesTop — 竖坐标或Ｙ坐标—标示手套装备空间上部边界的竖坐标在屏幕上的相对定位坐标值
GlovesBottom — 竖坐标或Ｙ坐标—标示手套装备空间底部边界的竖坐标在屏幕上的相对定位坐标值
GlovesWidth — 手套装备空间的宽度（像素值）
GlovesHeight — 手套装备空间的高度（像素值）

物品储存空间是由多个大小或一的小方格并接组成的二维空间，其数据资料可通过原始的Inventory.txt文件获得，如每个角色的原始储存空间为10×4，我们可以通过“GridX”和“GridY”两个参数所对应的值“10”和“4”而了解此信息。而“GridBoxWidth”和“GridBoxHeight”两 
个参数所对应的值同为29，因而可知每个储放格的尺寸为29×29。看一下在分辨率为800×600下亚马逊储存空间的资料：
Class ┃GridX┃GridY┃GridLeft┃GridRight┃GridTop┃GridBottom┃GridBoxWidth┃GridBoxHeight
Amazon2┃ 10┃ 4┃ 419┃ 706┃ 315┃ 428┃ 29┃ 29
假如你没把高中学的平面数学忘得一干二净的话，根据以上资料你马上就能想像得出“GridTop”坐标大概的位置在什么地主，“GridTop”在范围是从0到600，用图形大致描述如下：

┏0
┃
┃
┃
┃
┃
┃315┈┈┈┈┈┈┈→
┃ ┊
┃ ┊
┃ ┊←—储存空间—→
┃ ┊
┃ ┊
┃428┈┈┈┈┈┈┈→
┃
┃
┃
┃
┃
┗600

从上面草图可见储存空间的竖坐标范围从315到428，两数相减为113，而储存空间有4行，因此113÷4＝28.25，这就与“GridBoxHeight”等于29相对应了。了解了以上情况就有可能根据你预期的设定而对其进行修改。除此之外，你还要对invchar6.dc6
贴图文件进行修正而使之与你修改的参数达到一致的效果。

“GridLeft”和“GridRight”参数的作用也是差不多，而只方向不同而已：

┅┅━━━━━━━━━━━━━━━━━━━━━┓
400 419┈┈┈┈┈┈┈┈┈┈┈706 800
┊←———储存空间——→┊
↓ ↓

坐标之所从400开始原因另一半是用于显示角色状态，交易状态，合成物品等等。以上草图你可以想象得出有什么作用了，就不此多加叙述了。

最后要说的是，以上的数值，都是以像素为基本单位，也可以理解为点，在对Inventory.txt
进行修改扩容时，为了达到完美的显示效果，就必须对相应的贴图文件加以修正。实践证明，这一切的修改，都始于贴图文件的修改，一边修改一边记录各部分图形的原始坐标与位移坐标，在之后的Inventory.txt
文件修改时，你就有了很明确的第一手资料，加加减减很快就可完成修改，而期间出错的唯一可能就是你的数学不及格。至于修改图形所用的软件，必备的可能是Dc6 Creator，而其它的就各有所好了，较好的应该是Fireworks了，简单快捷，资源占用低。
*/

/*
文件名解析：
Inventory：库存，存货。在这里指存储空间。
本文件就是描述了物品栏以及仓库的信息。
此文件中的每一行表示一种存储空间。

每列的含义如下：


回复

    3楼
    2011-09-28 00:00

    举报 |

    zqtjingzi
    小吧主
    12

class：仅用作注释，指明此行描述了哪种存储空间。


回复

    4楼
    2011-09-28 00:00

    举报 |

    zqtjingzi
    小吧主
    12

提前说明：
XXXLeft：表示XXX的左边界的位置。
XXXRight：表示XXX的右边界的位置。
XXXTop：表示XXX的上边界的位置。
XXXBottom：表示XXX的下边界的位置。
XXXWidth：表示XXX的宽度，一般等于（下边界 - 上边界）
XXXHeight：表示XXX的高度，一般等于（右边界 - 左边界）


回复

    5楼
    2011-09-28 00:00

    举报 |

    zqtjingzi
    小吧主
    12

invLeft：
invRight：
invTop：
invBottom：
角色背包整体（包括装备区和物品栏）的大小。实际上按“B”键打开背包后会占据全部右半边的屏幕，但读此文件可以看出实际的背包大小要小于半个屏幕，剩余部分就是由绘有花纹的边框自动填充。

gridX：物品栏有多少列。
gridY：物品栏有多少行。

gridLeft：
gridRight：
gridTop：
gridBottom：
物品栏的大小。
gridBoxWidth：
gridBoxHeight：
物品栏中每个格子的大小。


回复

    6楼
    2011-09-28 00:01

    举报 |

    zqtjingzi
    小吧主
    12

rArmLeft：
rArmRight：
rArmTop：
rArmBottom：
rArmWidth：
rArmHeight：
右手武器区的大小。

torsoLeft：
torsoRight：
torsoTop：
torsoBottom：
torsoWidth：
torsoHeight：
身体衣服区的大小。

lArmLeft：
lArmRight：
lArmTop：
lArmBottom：
lArmWidth：
lArmHeight：
左手武器区的大小。


回复

    7楼
    2011-09-28 00:01

    举报 |

    zqtjingzi
    小吧主
    12

headLeft：
headRight：
headTop：
headBottom：
headWidth：
headHeight：
头盔区的大小。

neckLeft：
neckRight：
neckTop：
neckBottom：
neckWidth：
neckHeight：
颈部项链区的大小。


回复

    8楼
    2011-09-28 00:01

    举报 |

    zqtjingzi
    小吧主
    12

rhandLeft：
rhandRight：
rhandTop：
rhandBottom：
rhandWidth：
rhandHeight：
右手戒指区的大小。

lHandLeft：
lHandRight：
lHandTop：
lHandBottom：
lHandWidth：
lHandHeight：
左手戒指区的大小。

beltLeft：
beltRight：
beltTop：
beltBottom：
beltWidth：
beltHeight：
腰带区的大小。


回复

    9楼
    2011-09-28 00:01

    举报 |

    zqtjingzi
    小吧主
    12

feetLeft：
feetRight：
feetTop：
feetBottom：
feetWidth：
feetHeight：
鞋子区的大小。

gloveLeft：
gloveRight：
gloveTop：
gloveBottom：
gloveWidth：
gloveHeight：
手套区的大小。


回复

    10楼
    2011-09-28 00:01

    举报 |

    zqtjingzi
    小吧主
    12

补充说明：
屏幕左上角为原点，即（0，0）点。所有大小数值单位为像素。


回复

    11楼
    2011-09-28 00:01

    举报 |

    zqtjingzi
    小吧主
    12

特殊说明：
当想实现大背包或大箱子时而改变此文件时，为了显示效果与实际大小的一致性，一定要同时修改对应的dc6文件。
*/

typedef struct
{
    int vinvLeft;
    int vinvRight;
    int vinvTop;
    int vinvBottom;

    char vgridX;
    char vgridY;
    unsigned short iPadding4;

    int vgridLeft;
    int vgridRight;
    int vgridTop;
    int vgridBottom;

    char vgridBoxWidth;
    char vgridBoxHeight;
    unsigned short iPadding9;

    int vrArmLeft;
    int vrArmRight;
    int vrArmTop;
    int vrArmBottom;

    char vrArmWidth;
    char vrArmHeight;
    unsigned short iPadding14;

    int vtorsoLeft;
    int vtorsoRight;
    int vtorsoTop;
    int vtorsoBottom;

    char vtorsoWidth;
    char vtorsoHeight;
    unsigned short iPadding19;

    int vlArmLeft;
    int vlArmRight;
    int vlArmTop;
    int vlArmBottom;

    char vlArmWidth;
    char vlArmHeight;
    unsigned short iPadding24;

    int vheadLeft;
    int vheadRight;
    int vheadTop;
    int vheadBottom;

    char vheadWidth;
    char vheadHeight;
    unsigned short iPadding29;

    int vneckLeft;
    int vneckRight;
    int vneckTop;
    int vneckBottom;

    char vneckWidth;
    char vneckHeight;
    unsigned short iPadding34;

    int vrHandLeft;
    int vrHandRight;
    int vrHandTop;
    int vrHandBottom;

    char vrHandWidth;
    char vrHandHeight;
    unsigned short iPadding39;

    int vlHandLeft;
    int vlHandRight;
    int vlHandTop; 
    int vlHandBottom;

    char vlHandWidth;
    char vlHandHeight;
    unsigned short iPadding44;

    int vbeltLeft;
    int vbeltRight;
    int vbeltTop;
    int vbeltBottom;

    char vbeltWidth;
    char vbeltHeight;
    unsigned short iPadding49;

    int vfeetLeft;
    int vfeetRight;
    int vfeetTop;
    int vfeetBottom;

    char vfeetWidth;
    char vfeetHeight;
    unsigned short iPadding54;

    int vglovesLeft;
    int vglovesRight;
    int vglovesTop;
    int vglovesBottom;

    char vglovesWidth;
    char vglovesHeight;
    unsigned short iPadding59;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "class",
    NULL,
};

static int Inventory_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "class") )
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

int process_inventory(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invLeft, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invRight, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invTop, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, invBottom, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gridX, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gridY, CHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gridLeft, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gridRight, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gridTop, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gridBottom, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gridBoxWidth, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, gridBoxHeight, CHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rArmLeft, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rArmRight, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rArmTop, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rArmBottom, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rArmWidth, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rArmHeight, CHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, torsoLeft, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, torsoRight, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, torsoTop, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, torsoBottom, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, torsoWidth, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, torsoHeight, CHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lArmLeft, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lArmRight, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lArmTop, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lArmBottom, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lArmWidth, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lArmHeight, CHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, headLeft, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, headRight, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, headTop, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, headBottom, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, headWidth, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, headHeight, CHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, neckLeft, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, neckRight, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, neckTop, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, neckBottom, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, neckWidth, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, neckHeight, CHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rHandLeft, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rHandRight, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rHandTop, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rHandBottom, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rHandWidth, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, rHandHeight, CHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lHandLeft, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lHandRight, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lHandTop, INT); 
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lHandBottom, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lHandWidth, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lHandHeight, CHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, beltLeft, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, beltRight, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, beltTop, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, beltBottom, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, beltWidth, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, beltHeight, CHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, feetLeft, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, feetRight, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, feetTop, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, feetBottom, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, feetWidth, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, feetHeight, CHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, glovesLeft, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, glovesRight, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, glovesTop, INT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, glovesBottom, INT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, glovesWidth, CHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, glovesHeight, CHAR);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnFieldProc = Inventory_FieldProc;
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

