#include "global.h"

#define FILE_PREFIX "monstats2"
#define NAME_PREFIX "mn"

/*
MonStats2.txt Fileguide
By Nefarius







ID Pointers
Id – Pointer used by MonStats.txt to link to this line. (note, multiple monsters can link to the same line)




Collision Detection I

Height – not used (size in in-game sub-tiles).
OverlayHeight – not used.

pixHeight – not used (size in pixels).

SizeX – X-diameter in sub-tiles, used for collision and proximity checking (-1 to 3)

SizeY – Y-diameter in sub-tiles, used for collision and proximity checking (-1 to 3)




Misc. Settings I
SpawnCol – equivalent to 1.00-1.09 eSpawnCol column, controls which spawning method the game uses to create this unit, originally 0=normal spawning via m1-25 columns, 1=special spawning via DS1 only (special layering setup), 2=spawn via s1-25 columns. 
Due to the changes to levels.txt, this column becomes useless, S1-25 and M1-25 are identical in 1.10+. Setting it to 1 will still prevent them from spawning however.




Weapon Settings
MeleeRng – range in sub-tiles this monster can attack you in (the radius of its melee attacks), works exactly like the range column in weapons.txt

BaseW – base weaponclass, uses the codes from weaponclass.txt – for some AIs (such as that of the Necro Skeleton) this will define which special effects are being applied. (in 1.00-1.06 you could make the necro skeletons work like archers by setting 
the equivalent of this column to “bow” – this no longer works). Note, this will apply all the hardcoded effects of a specific weaponclass to the unit (such as how some modifiers work).

HitClass – has to do with how successful hits are handled by the target, some hitclasses have minor effects, such as making specific sounds on impact, I doubt there is much more to it then some client side effects (but there may yet be some surprises 
here) – probably uses the same hitclasses as used by missiles.




Display / Component Settings

HDv, TRv, LGv, Rav, Lav, RHv, LHv, SHv, S1v, S2v, S3v, S4v, S5v, S6v, S7v, S8v – equipment-graphic type for head, torso, legs, right arm, left arm, right hand, left hand, shield and special 1-8 components. This works just like the AlternateGFX columns 
in weapons.txt – Make sure the monster has the component types you specify If you insert multiple graphic types, separated by a comma (“,”), the game will randomly select a component to use.

HD, TR, LG, RA, LA, RH, LH, SH, S1, S2, S3, S4, S5, S6, S7, S8 – Booleans, these columns control whenever the monster has these components or not. Make sure this matches your COF files.

TotalPieces – Total amount of different components this monster has.

mDT, mNU, mWL, mGH, mA1, mA2, mBL, mSC, mS1, mS2, mS3, mS4, mDD, mKB, mSQ, mRN – booleans (death, stall, walk, gethit, attack 1, attack 2, block, cast, special1-4, corpse, knockback, sequence, run), they control which modes this monster has. Some of 
these have special effects, if you set mGH to 0, the monster will have instant-hit recovery (I.E. golems for example cannot be locked in GH mode, because the game never plays GH anims), mKB is another boolean that controls whenever the monster can be 
knocked back or not (if mKB is false then items with knockback will have no effect on this monster), otherwise the game will pick the GH animation for knockback. SQ defines whenever this unit can use a skill-sequence or not.

dDT, dNU, dWL, dGH, dA1, dA2, dBL, dSC, dS1, dS2, dS3, dS4, dDD, dKB, dSQ, dRN – controls the number of directions the specific animations for each mode have – this must match the values in the COF files. Otherwise you usually get a nice crash.

A1mv, A2mv, SCmv, S1mv, S2mv, S3mv, S4mv – booleans that control whenever the unit can use these modes while moving, on top of the modes WL and RN.



Collision Detection II

NoGfxHitTest – boolean that controls whenever the game uses the x/y diameter settings for collision detection or special, superimposed values.

htTop, htLeft, htWidth, htHeight – the dimensions of the superimposed bounding box, probably using the pivot of the animation as x/y 0.



Misc. Settings II
Restore – has to do with how the game handles the monster, monsters set to 0 are not stored permanently (Izual's Ghost, Natalya, the Familiar Summon (the “eyeball” scout summon the Necro had in the alpha version of D2) , all D2X summons, all non DS1 
based traps (I.E those traps that spawn once and die)), 1 is the default value, that will make the game store and restore the units as needed when the maps load/unload. 2 is a special setting for large constructs, like towers, spawners and catapults.

AutomapCel – what index in Maximap.DC6 is used to display this monster on the AutoMap. (does not update – go cry now you cheaters), to use this NoMap needs to be enabled.

NoMap – boolean, 0=default, 1=use automapCel entry.

NoOvly – boolean, 0=default, 1=disallow specific overlays, used for stationary and unselectable summons, such as bonewalls, traps and the druids ravens.



Selection

isSel – boolean, 1=can be selected, 0=cannot be selected.

alSel – boolean, 1=can be selected, 0=cannot be selected. Used to select allies outside of town (such as Cain in Tristram).

noSel – boolean, 1=can not be selected, 0=can be selected. Used to prevent any form of selection.

shiftSel – boolean, not directly known, used with bonewalls (both the necromancer's bonewalls and big D's boneprison) to prevent them from being properly selected. (I.E. they are selected but no name is ever shown in case of diablo's prison).

corpseSel – boolean, 1=can select corpse, 0=cannot select corpse.




Misc. Settings III

isAtt – boolean, 1=can be attacked, 0=cannot be attacked.

revive – boolean, 1=can be revived, 0=cannot be revived. I don't know whenever this also applies to self-resurrect and the like.

critter – boolean, 1=is a critter, 0=is not a critter. Many of the critter specific effects are applied to the unit via this columns, others are hardcoded to their hcIdx and baseIds, and still others are only appended via levels.txt critter spawning 
columns.

small – boolean, 1=small, 0=not small. Used to get 100% effective knockback.

large – boolean, 1=large, 0=not large. Used to get 25% effective knockback.

soft – probably has to do something with sound effects, 1=is soft, 0=is not soft. Set to 0 only for skeletons and other enemies that lack “flesh”, like wraiths, swarms etc.

inert – boolean, 1=harmless, 0=default. (used for NPCs and some other things)

objCol – boolean, The explanation in the old guide is unclear, I don't know what to look for when testing this. Probably has to do if the unit is handled like an object while alive.

deadCol – boolean, ditto, just that this effects corpses.

unFlatDeath – boolean, applies collision checking to a corpse, set this to 1 to make it impossible to walk over a corpse while it exists.

Shadow – boolean, 1=draw shadow, 0=don't draw a shadow.

noUniqueShift – boolean. 1=don't use random palette from RandTransforms.dat if it spawns as a boss.

compositeDeath – boolean. is the death animation a composite of more then 1 component (1) or just TR-component (0).

localBlood – probably defines the z-offset from where to release blood when hit. (this is not a boolean). Setting the next column to a value is enough to make a unit bleed.

Bleed – 0=don't bleed, 1=small blood missile (missiles 18-19), 2=small and large blood missiles (missiles 20-21), >3 will pick other missiles (I.E. each time a pair of two 3 would allow it to pick 22-23, in case the behavior is still like 1.09).

Light – diameter of the light radius this monster has in sub-tiles, default is no light radius.

light-r, light-g, light-b – RGB values for light-color (255,255,255 = white obviously).

Utrans, Utrans(N), Utrans(H) – defines which palette entry to use on normal, nightmare and hell, from both the units palshift file and transtransforms.dat – used by the game to give act bosses a different color on each difficulty for example.

Heart, Bodypart – broken as of 1.07 – when blizzard introduced TreasureClassEx.txt they broke MonItemPercent.txt, in old days, this column defined which items the unit dropped in addition to their treasureclass (organ and heart drops from alpha diablo 
II). The columns are useless, until someone manages to recreate the functionality MonItemPercent.txt had in 1.00-1.06.

InfernoLen – Length of each inferno sub-animation.

InfernoAnim – mode to use for inferno animation, I assume this uses the numerical ID of the lines on MonMode.txt (9=S2,11=S4 and so on, I'm not sure though)

InfernoRollback – Length of the rollback (I.E. return to frame 1) of the inferno animation.

ResurrectMode – Animation mode to use when resurrected, most use NU, but some such as skeletons have a special skill (SkeletonRaise) that applies a skill sequence to them in MonStats, this is why they have xx in here (or summons, the animation of which 
is controlled by skills.txt) – some others like fallen have special “stand up” animations.

ResurrectSkill – Skill to use when being resurrected, only needed if the skill is also present in MonStats.txt I guess.

EOL – End of Line.

*/

/*
 文件名解析：
Mon：Monster，即怪物。
Stat(s)：State(s)，状态。加个2，表示一些特殊的附加状态
本文件描述了一些特殊怪物的状态属性。
文件中的每一行表示一种怪物。

 Id：怪物索引，与MonStats.txt关联。

Height：无用参数列，可删。

OverlayHeight：无用参数列，可删。

pixHeight：无用参数列，可删。

SizeX：怪物在X方向上的大小，用于计算碰撞体积。

SizeY：怪物在Y方向上的大小，用于计算碰撞体积。

SpawnCol：怪物产生方式。1.11后不再使用，但其效果保留。

MeleeRng：怪物的近战攻击距离。

BaseW：基础攻击类别。与WeaponClass.txt关联。

HitClass：打击类别，与命中和击中效果相关。

 HDv：怪物头部的图像类型。

TRv：怪物躯干的图像类型。

LGv：怪物腿部的图像类型。

Rav：怪物右臂的图像类型。

Lav：怪物左臂的图像类型。

RHv：怪物右手的图像类型。

LHv：怪物左手的图像类型。

SHv：怪物盾牌的图像类型。

S1-8v：怪物特殊部件1-8的图像类型。

说明：如果你想为某个怪物的某个部位指定图像类型请先确定此怪物有此部位，即应参考后面对应列的值。另外：如果对某个部位指定多种类型的话，游戏会随机选择一个。

 HD：怪物是否有头部。

TR：怪物是否有躯干。

LG：怪物是否有腿。

RA：怪物是否有右臂。

LA：怪物是否有左臂。

RH：怪物是否有右手。

LH：怪物是否有左手。

SH：怪物是否有盾牌。

S1-8：怪物是否有特殊部件1-8。

说明：此处对怪物部位的声明必须要与cof文件中所声明的一致。

TotalPieces：怪物总共含有多少个部件。

mDT：怪物是否会死。

mNU：怪物是否会静止不动。

mWL：怪物是否会走。

mGH：怪物是否有打击恢复。

mA1：怪物是否会攻击1。

mA2：怪物是否会攻击2。

mBL：怪物是否会格挡。

mSC：怪物是否会施法。

mS1-4：怪物是否有特殊效果1-4。

mDD：怪物是否有尸体。

mKB：怪物是否会被击退。

mSQ：怪物是否有连续技。

mRN：怪物是否会跑。

 dDT：怪物死亡时可能的朝向数。一些BOSS此列值为1，也就是说它们死亡时总是冲着一个方向。

dNU：怪物不动时可能的朝向数。

dWL：怪物可能的走路方向数。

dGH：怪物打击恢复时的朝向数。

dA1：怪物可能的攻击1方向数。

dA2：怪物可能的攻击2方向数。

dBL：怪物可能的格挡方向数。

dSC：怪物可能的施法方向数。

dS1-4：怪物做1-4号特殊动作1-4时的朝向数。

dDD：怪物尸体的可能朝向数。

dKB：怪物可能被击退的方向数。

dSQ：怪物施放连续技的可能方向数。

dRN：怪物可能的跑步方向数。

A1mv：怪物移动时能否进行攻击1。

A2mv：怪物移动时能否进行攻击2。

SCmv：怪物移动时能否施法。

S1-4mv：怪物移动时能否进行1-4号特殊动作。

NoGfxHitTest：是否使用之前指定的X、Y方向直径进行碰撞计算，如果不是，则使用下面的特殊边界。

htTop：特殊边界之上界。

htLeft：特殊边界之左界。

htWidth：特殊边界之宽度。

htHeight：特殊边界之高度。

Restore：怪物是否始终存在。如衣卒尔的灵魂就不是始终存在的。

AutomapCel：是否在自动地图上显示。

NoMap：是否使用上面的AutomapCel开关。

NoOvly：是否会被覆盖。

isSel：是否能被选中。

alSel：作为同盟时是否能在城外被选中。

noSel：是否绝对不能被选中。

shiftSel：是否能被正常选中。其实这个值我不太清楚……

corpseSel：尸体能否被选中。

 isAtt：是否能被攻击。

revive：是否能被复活。

critter：是否是野外生物，如鸡、蝎子。

small：是否是小型怪物。100%击退效果。

large：是否是大型怪物。25%击退效果。

soft：是否是肉感的。跟打击时的声音有关。

inert：是否是无伤害性的。

objCol：是否像物品一样？？？

deadCol：是否像尸体一样？？？

unFlatDeath：死亡后是否保留碰撞体积。

Shadow：是否有影子。

noUniqueShift：是否能变成金怪。

compositeDeath：死亡动画是否是多个动画复合成的。

localBlood：被击中时出血的位置。

Bleed：出血状态。0=不出血；1=慢出血；2=大出血；3=特殊出血状态。

Light：照亮范围。

light-r, light-g, light-b：照亮光的颜色。

Utrans/(N)/(H)：普通/噩梦/地狱难度下的颜色基调。

Heart：无用参数。

Bodypart：无用参数。

InfernoLen：使用地狱火类似技能时的基础动作帧数。

InfernoAnim：使用地狱火类似技能时的动作类型。

InfernoRollback：使用地狱火类似技能时的收招时间。

ResurrectMode：复活模式。

ResurrectSkill：被复活的技能。

EOL：行尾标志，必须为0。


修正一下，关于Height、OverlayHeight、pixHeight之前说无用是看了别人的资料，但经我自己测试后其实是怪物的高度，以及状态覆盖的位置和具体的像素高度。这些东西会影响怪物在小地图上的准确位置、光环相对于怪物的位置等

*/

typedef struct
{
    unsigned int vId;

#if 1
    unsigned char vBitCombined1;
    unsigned char vBitCombined2;
    unsigned char vBitCombined3;
#else
    unsigned char vcorpseSel : 1;
    unsigned char vshiftSel : 1;
    unsigned char vnoSel : 1;
    unsigned char valSel : 1;

    unsigned char visSel : 1;
    unsigned char vnoOvly : 1;
    unsigned char vnoMap : 1;
    unsigned char vnoGfxHitTest : 1;

    unsigned char vnoUniqueShift : 1;
    unsigned char vShadow : 1;
    unsigned char vcritter : 1;
    unsigned char vsoft : 1;

    unsigned char vlarge : 1;
    unsigned char vsmall : 1;
    unsigned char visAtt : 1;
    unsigned char vrevive : 1;

    unsigned char iPadding1_2 : 3;
    unsigned char vunflatDead : 1;

    unsigned char vdeadCol : 1;
    unsigned char vobjCol : 1;
    unsigned char vinert : 1;
    unsigned char vcompositeDeath : 1;
#endif
    unsigned char iPadding1;

    unsigned char vSizeX;
    unsigned char vSizeY;
    unsigned char vspawnCol;
    unsigned char vHeight;

    unsigned char vOverlayHeight;
    unsigned char vpixHeight;
    unsigned char vMeleeRng;
    unsigned char iPadding3;

    unsigned char vBaseW[4];

    unsigned char vHitClass;
    unsigned char vHDvNum;
    unsigned char vTRvNum;
    unsigned char vLGvNum;

    unsigned char vRavNum;
    unsigned char vLavNum;
    unsigned char vRHvNum;
    unsigned char vLHvNum;

    unsigned char vSHvNum;
    unsigned char vS1vNum;
    unsigned char vS2vNum;
    unsigned char vS3vNum;

    unsigned char vS4vNum;
    unsigned char vS5vNum;
    unsigned char vS6vNum;
    unsigned char vS7vNum;

    unsigned char vS8vNum;
    unsigned char iPadding9;
    unsigned char vHDv[12]; //compcode

    unsigned char vTRv[12];

    unsigned char vLGv[12];

    unsigned char vRav[12];

    unsigned char vLav[12];

    unsigned char vRHv[12];

    unsigned char vLHv[12];

    unsigned char vSHv[12];

    unsigned char vS1v[12];

    unsigned char vS2v[12];

    unsigned char vS3v[12];

    unsigned char vS4v[12];

    unsigned char vS5v[12];

    unsigned char vS6v[12];

    unsigned char vS7v[12];

    unsigned char vS8v[12];

    unsigned short iPadding57;

#if 1
    unsigned char vBitCombined4;
    unsigned char vBitCombined5;
#else
    unsigned char vSH : 1;
    unsigned char vLH : 1;
    unsigned char vRH : 1;
    unsigned char vLA : 1;

    unsigned char vRA : 1;
    unsigned char vLG : 1;
    unsigned char vTR : 1;
    unsigned char vHD : 1;

    unsigned char vS8 : 1;
    unsigned char vS7 : 1;
    unsigned char vS6 : 1;
    unsigned char vS5 : 1;

    unsigned char vS4 : 1;
    unsigned char vS3 : 1;
    unsigned char vS2 : 1;
    unsigned char vS1 : 1;
#endif

    unsigned char iPadding58[2];

    unsigned int vTotalPieces;

#if 1
    unsigned char vBitCombined6;
    unsigned char vBitCombined7;
#else
    unsigned char vmSC : 1;
    unsigned char vmBL : 1;
    unsigned char vmA2 : 1;
    unsigned char vmA1 : 1;

    unsigned char vmGH : 1;
    unsigned char vmWL : 1;
    unsigned char vmNU : 1;
    unsigned char vmDT : 1;

    unsigned char vmRN : 1;
    unsigned char vmSQ : 1;
    unsigned char vmKB : 1;
    unsigned char vmDD : 1;

    unsigned char vmS4 : 1;
    unsigned char vmS3 : 1;
    unsigned char vmS2 : 1;
    unsigned char vmS1 : 1;
#endif

    unsigned short iPadding60;

    unsigned char vdDT;
    unsigned char vdNU;
    unsigned char vdWL;
    unsigned char vdGH;

    unsigned char vdA1;
    unsigned char vdA2;
    unsigned char vdBL;
    unsigned char vdSC;

    unsigned char vdS1;
    unsigned char vdS2;
    unsigned char vdS3;
    unsigned char vdS4;

    unsigned char vdDD;
    unsigned char vdKB;
    unsigned char vdSQ;
    unsigned char vdRN;

#if 1
    unsigned char vBitCombined8;
    unsigned char vBitCombined9;
#else
    unsigned char vSCmv : 1;
    unsigned char iPadding65_1 : 1;
    unsigned char vA2mv : 1;
    unsigned char vA1mv : 1;
    unsigned char iPadding65 : 4;

    unsigned char iPadding65_2 : 4;
    unsigned char vS4mv : 1;
    unsigned char vS3mv : 1;
    unsigned char vS2mv : 1;
    unsigned char vS1mv : 1;
#endif

    unsigned char iPadding65[2];

    unsigned char vInfernoLen;
    unsigned char vInfernoAnim;
    unsigned char vInfernoRollback;
    unsigned char vResurrectMode;   //monmode

    unsigned short vResurrectSkill; //skills
    short vhtTop;

    short vhtLeft;
    short vhtWidth;

    short vhtHeight;
    unsigned short iPadding69;

    unsigned int vautomapCel;

    unsigned char vlocalBlood;
    unsigned char vBleed;
    unsigned char vLight;
    unsigned char vlightmysubr;

    unsigned char vlightmysubg;
    unsigned char vlightmysubb;
    unsigned char vUtrans;
    unsigned char vUtransmybr1Nmybr2;

    unsigned char vUtransmybr1Hmybr2;
    unsigned char acPaddding[3];

    unsigned char vHeart[4];
    unsigned char vBodyPart[4];

    unsigned int vrestore;
} ST_LINE_INFO;//total 308 bytes

typedef struct
{
    unsigned char vId[32];
} ST_MONSTAT;

static char *m_apcInternalProcess[] = 
{
    "EOL",
    NULL,
};

static unsigned int m_iMonStatsCount = 0;
static ST_MONSTAT *m_astMonStats = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astMonStats, ST_MONSTAT);

static int MonStats2_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "EOL") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static int MonStats2_ConvertValue_Pre(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "Id") )
    {
        pcResult = MonStats_GetStatsName(pstLineInfo->vId);

        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            //sprintf(acOutput, "%s%u", NAME_PREFIX, m_iMonStatsCount);
            acOutput[0] = 0;
        }

        strncpy(m_astMonStats[pstLineInfo->vId].vId, acOutput, sizeof(m_astMonStats[pstLineInfo->vId].vId));
        String_Trim(m_astMonStats[pstLineInfo->vId].vId);
        m_iMonStatsCount++;

        result = 1;
    }

    return result;
}

static char *MonStats2_GenerateList(ST_LINE_INFO *pstLineInfo, unsigned int count, unsigned char *pbList, unsigned int uiListNum, char *acOutput)
{
    unsigned int i, j;
    char *pcResult;

    if ( 1 < count )
    {
        acOutput[0] = '"';
        acOutput++;
    }

    for ( i = 0, j = 0; i < uiListNum && j < count; i++ )
    {
        pcResult = Compcode_GetCode(pbList[i]);
        if ( pcResult )
        {
            if ( 0 == j )
            {
                strcpy(acOutput, pcResult);
            }
            else
            {
                sprintf(acOutput, ",%s", pcResult);
            }
            String_Trim(acOutput);
            acOutput += strlen(acOutput);

            j++;
        }
    }

    if ( 1 < count )
    {
        acOutput[0] = '"';
        acOutput++;
    }

    return acOutput;
}

static int MonStats2_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "HDv") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vHDvNum, pstLineInfo->vHDv, sizeof(pstLineInfo->vHDv), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "TRv") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vTRvNum, pstLineInfo->vTRv, sizeof(pstLineInfo->vTRv), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "LGv") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vLGvNum, pstLineInfo->vLGv, sizeof(pstLineInfo->vLGv), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "Rav") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vRavNum, pstLineInfo->vRav, sizeof(pstLineInfo->vRav), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "Lav") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vLavNum, pstLineInfo->vLav, sizeof(pstLineInfo->vLav), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "RHv") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vRHvNum, pstLineInfo->vRHv, sizeof(pstLineInfo->vRHv), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "LHv") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vLHvNum, pstLineInfo->vLHv, sizeof(pstLineInfo->vLHv), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "SHv") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vSHvNum, pstLineInfo->vSHv, sizeof(pstLineInfo->vSHv), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "S1v") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vS1vNum, pstLineInfo->vS1v, sizeof(pstLineInfo->vS1v), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "S2v") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vS2vNum, pstLineInfo->vS2v, sizeof(pstLineInfo->vS2v), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "S3v") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vS3vNum, pstLineInfo->vS3v, sizeof(pstLineInfo->vS3v), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "S4v") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vS4vNum, pstLineInfo->vS4v, sizeof(pstLineInfo->vS4v), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "S5v") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vS5vNum, pstLineInfo->vS5v, sizeof(pstLineInfo->vS5v), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "S6v") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vS6vNum, pstLineInfo->vS6v, sizeof(pstLineInfo->vS6v), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "S7v") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vS7vNum, pstLineInfo->vS7v, sizeof(pstLineInfo->vS7v), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "S8v") )
    {
        MonStats2_GenerateList(pstLineInfo, pstLineInfo->vS8vNum, pstLineInfo->vS8v, sizeof(pstLineInfo->vS8v), acOutput);

        result = 1;
    }
    else if ( !strcmp(acKey, "ResurrectMode") )
    {
        pcResult = MonMode_GetCode(pstLineInfo->vResurrectMode);

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
    else if ( !strcmp(acKey, "ResurrectSkill") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vResurrectSkill);

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
    else if ( !strcmp(acKey, "Id") )
    {
        pcResult = MonStats_GetStatsName(pstLineInfo->vId);

        if ( pcResult )
        {
            strcpy(acOutput, pcResult);
        }
        else
        {
            //sprintf(acOutput, "%s%u", NAME_PREFIX, m_iMonStatsCount);
            acOutput[0] = 0;
        }

        result = 1;
    }

    return result;
}

char *MonStats2_GetStatsName(unsigned int id)
{
    if ( id >= m_iMonStatsCount )
    {
        return NULL;
    }

    return m_astMonStats[id].vId;
}

static int MonStats2_BitProc(void *pvLineInfo, char *acKey, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    int result = 0;

    if ( !strcmp(acKey, "corpseSel") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined1 & (1 << 7)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "shiftSel") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined1 & (1 << 6)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "noSel") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined1 & (1 << 5)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "alSel") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined1 & (1 << 4)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "isSel") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined1 & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "noOvly") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined1 & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "noMap") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined1 & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "noGfxHitTest") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined1 & 1) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "noUniqueShift") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & (1 << 7)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "Shadow") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & (1 << 6)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "critter") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & (1 << 5)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "soft") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & (1 << 4)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "large") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "small") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "isAtt") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "revive") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined2 & 1) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "unflatDead") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined3 & (1 << 4)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "deadCol") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined3 & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "objCol") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined3 & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "inert") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined3 & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "compositeDeath") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined3 & 1) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "SH") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined4 & (1 << 7)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "LH") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined4 & (1 << 6)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "RH") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined4 & (1 << 5)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "LA") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined4 & (1 << 4)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "RA") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined4 & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "LG") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined4 & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "TR") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined4 & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "HD") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined4 & 1) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "S8") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined5 & (1 << 7)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "S7") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined5 & (1 << 6)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "S6") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined5 & (1 << 5)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "S5") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined5 & (1 << 4)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "S4") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined5 & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "S3") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined5 & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "S2") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined5 & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "S1") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined5 & 1) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mSC") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined6 & (1 << 7)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mBL") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined6 & (1 << 6)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mA2") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined6 & (1 << 5)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mA1") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined6 & (1 << 4)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mGH") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined6 & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mWL") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined6 & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mNU") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined6 & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mDT") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined6 & 1) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mRN") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined7 & (1 << 7)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mSQ") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined7 & (1 << 6)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mKB") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined7 & (1 << 5)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mDD") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined7 & (1 << 4)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mS4") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined7 & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mS3") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined7 & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mS2") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined7 & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "mS1") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined7 & 1) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "SCmv") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined8 & (1 << 7)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "A2mv") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined8 & (1 << 5)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "A1mv") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined8 & (1 << 4)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "S4mv") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined9 & (1 << 3)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "S3mv") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined9 & (1 << 2)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "S2mv") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined9 & (1 << 1)) != 0);
        result = 1;
    }
    else if ( !strcmp(acKey, "S1mv") )
    {
        sprintf(acOutput, "%d", (pstLineInfo->vBitCombined9 & 1) != 0);
        result = 1;
    }

    return result;
}

static void MonStats2_InitValueMap(ST_VALUE_MAP *pstValueMap, ST_LINE_INFO *pstLineInfo)
{
    INIT_VALUE_BUFFER;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Id, UINT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, corpseSel, BitCombined1, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, shiftSel, BitCombined1, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, noSel, BitCombined1, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, alSel, BitCombined1, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, isSel, BitCombined1, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, noOvly, BitCombined1, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, noMap, BitCombined1, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, noGfxHitTest, BitCombined1, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, noUniqueShift, BitCombined2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, Shadow, BitCombined2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, critter, BitCombined2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, soft, BitCombined2, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, large, BitCombined2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, small, BitCombined2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, isAtt, BitCombined2, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, revive, BitCombined2, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, unflatDead, BitCombined3, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, deadCol, BitCombined3, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, objCol, BitCombined3, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, inert, BitCombined3, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, compositeDeath, BitCombined3, BIT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SizeX, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SizeY, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, spawnCol, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Height, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, OverlayHeight, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, pixHeight, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MeleeRng, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BaseW, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitClass, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HDv, STRING); //compcode

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TRv, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LGv, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Rav, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Lav, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, RHv, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, LHv, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SHv, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S1v, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S2v, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S3v, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S4v, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S5v, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S6v, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S7v, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, S8v, STRING);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, SH, BitCombined4, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, LH, BitCombined4, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, RH, BitCombined4, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, LA, BitCombined4, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, RA, BitCombined4, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, LG, BitCombined4, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, TR, BitCombined4, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, HD, BitCombined4, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, S8, BitCombined5, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, S7, BitCombined5, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, S6, BitCombined5, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, S5, BitCombined5, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, S4, BitCombined5, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, S3, BitCombined5, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, S2, BitCombined5, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, S1, BitCombined5, BIT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TotalPieces, UINT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mSC, BitCombined6, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mBL, BitCombined6, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mA2, BitCombined6, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mA1, BitCombined6, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mGH, BitCombined6, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mWL, BitCombined6, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mNU, BitCombined6, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mDT, BitCombined6, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mRN, BitCombined7, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mSQ, BitCombined7, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mKB, BitCombined7, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mDD, BitCombined7, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mS4, BitCombined7, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mS3, BitCombined7, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mS2, BitCombined7, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, mS1, BitCombined7, BIT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dDT, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dNU, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dWL, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dGH, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dA1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dA2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dBL, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dSC, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dS1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dS2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dS3, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dS4, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dDD, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dKB, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dSQ, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dRN, UCHAR);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, SCmv, BitCombined8, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, A2mv, BitCombined8, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, A1mv, BitCombined8, BIT);

    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, S4mv, BitCombined9, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, S3mv, BitCombined9, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, S2mv, BitCombined9, BIT);
    VALUE_MAP_DEFINE_2(pstValueMap, pstLineInfo, S1mv, BitCombined9, BIT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InfernoLen, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InfernoAnim, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InfernoRollback, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ResurrectMode, UCHAR);   //monmode

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ResurrectSkill, USHORT); //skills
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, htTop, SHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, htLeft, SHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, htWidth, SHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, htHeight, SHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, automapCel, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, localBlood, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Bleed, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Light, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lightmysubr, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lightmysubg, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, lightmysubb, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Utrans, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Utransmybr1Nmybr2, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Utransmybr1Hmybr2, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Heart, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BodyPart, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, restore, UINT);
}

int process_monstats2(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            MODULE_DEPEND_CALL(monstats, acTemplatePath, acBinPath, acTxtPath);

            MonStats2_InitValueMap(pstValueMap, pstLineInfo);

            m_stCallback.pfnConvertValue = MonStats2_ConvertValue_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            m_iMonStatsCount = 0;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(monstats, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(compcode, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(monmode, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(skills, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            MonStats2_InitValueMap(pstValueMap, pstLineInfo);

            m_stCallback.pfnConvertValue = MonStats2_ConvertValue;
            m_stCallback.pfnBitProc = MonStats2_BitProc;
            m_stCallback.pfnFieldProc = MonStats2_FieldProc;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

