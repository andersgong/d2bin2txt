#include "global.h"

#define FILE_PREFIX "itemtypes"

/*
Title 	ItemTypes.txt File Guide (1.2)
Description 	by Nefarius
Sent by 	

ItemTypes.txt File Guide
By Nefarius (1.2 added further notes regarding socket caps and staffmodes brought to my attention by Myhrginoc a (long) while ago)








ItemType – A comment field that contains the “internal name” of this iType, you can basically enter anything you wish here, but since you can add as many comment columns as you wish, there is no reason to use it for another purpose icon_razz.gif.

Code – The ID pointer of this ItemType, this pointer is used in many txt files (armor.txt, cubemain.txt, misc.txt, skills.txt, treasureclassex.txt, weapons.txt), never use the same ID pointer twice, the game will only use the first instance and ignore 
all other occurrences. ID pointers are case sensitive, 3-4 chars long and can contain numbers, letters and symbols.

Equiv1-2 – This is used to define the parent iType, note that an iType can have multiple parents (as will be shown in the cladogram – link below), the only thing you must avoid at all cost is creating infinite loops. I haven't ever tested what happens 
when you create an iType loop, but infinite loops are something you should always avoid.

Fig. 1 - ItemType Diagram by Paul Siramy


Repair – Boolean, 1=Merchants can repair this item type, 0=Merchants cannot repair this iType (note, this also refers to charges being rechargeable).

Body – Boolean, 1=The character can wear this iType, 0=This iType can only be carried in the inventory, cube or stash (and belt if it is set as “beltable” in the other item related txt files)

BodyLoc1-2 – If you have set the previous column to 1, you need to specify the inventory slots in which the item has to be equipped. (the codes used by this field are read from BodyLocs.txt)

Shoots – This column specifies which type of quiver (“ammo&rdquo this iType (in case it is a weapon) requires in order to shoot (you use the ID pointer of the quiver iType here).

Caution: The place it checks which missile to pick (either arrow, bolt, explosive arrow or magic arrow) is buried deep within D2Common.dll, the section can be modified, there is an extensive post discussing this in Code Editing. - Thanks go to Kingpin 
for spotting a silly little mistake in here.

Quiver – The equivalent to the previous column, in here you specify which weapon this quiver is linked to. Make sure the two columns match. (this also uses the ID pointer of course).

Throwable – Can this iType be thrown (determines whenever it uses the quantity and throwing damage columns in Weapons.txt for example).

Reload – Can the this item be re-stacked via drag and drop. 1=Yes, 0=No.

ReEquip – If the ammo runs out, the game will automatically pick the next item of the same iType to be equipped in it's place. 1=Yes, 0=No. (more clearly, when you use up all the arrows in a quiver, the next quiver, if available, will be equipped in 
its place).

AutoStack – Are identical stacks automatically combined when you pick the up? 1=Yes, 0=No. (for example, which you pick up throwing potions or normal javelins, they are automatically combined with those you already have)

Magic – Is this iType always Magic? 1=Yes, 0=No.

Rare – Can this iType spawn as a rare item? 1=Yes, 0=No. Note: If you want an item that spawns only as magic or rare, you need to set the previous column to 1 as well.

Normal – Is this iType always Normal? 1=Yes, 0=No.

Charm – Does this iType function as a charm? 1=Yes, 0=No. Note: This effect is hardcoded, if you need a new charm type, you must use the char iType in one of the equivs.

Gem – Can this iType be inserted into sockets? 1=Yes, 0=No (Link your item to the sock iType instead to achieve this).

Beltable – Can this iType be placed in your characters belt slots? 1=Yes, 0=No. (This requires further tweaking in other txt files).

MaxSock1, MaxSock25, MaxSock40 – Maximum sockets for iLvl 1-25, 26-40 and 40+. The range is hardcoded but the location is known, so you can alter around the range to your liking. On normal, items dropped from monsters are limited to 3, on nightmare to 
4 and on hell to 6 sockets, irregardless of this columns content.

TreasureClass – Can this iType ID Pointer be used as an auto TC in TreasureClassEx.txt. 1=Yes, 0=No. *Such as armo3-99 and weap3-99 etc.

Rarity – Dunno what it does, may have to do with the chance that an armor or weapon rack will pick items of this iType. If it works like other rarity fields, the chance is rarity / total_rarity * 100.

StaffMods – Contains the class code for the character class that should get +skills from this iType (such as wands that can spawn with +Necromancer skills). Note, this only works if the item is not low quality, set or unique. Note, that this uses the 
vanilla min/max skill IDs for each class as the range for the skill pool, so if you add new class skills to the end of the file, you should use automagic.txt instead

CostFormula – Does the game generate the sell/repair/buy prices of this iType based on its modifiers or does it use only the cost specific in the respective item txt files. 2=Organ (probably higher price based on unit that dropped the organ), 1=Yes, 0=
No. Note: Only applies to items that are not unique or set, for those the price is solely controlled by the base item file and by the bonus to price given in SetItems and UniqueItems txt files. The exact functionality remains unknown, as for example 
charms, have this disabled.

Class – Contains the class code for the class that should be able to use this iType (for class specific items).

VarInvGfx – This column contains the sum of randomly picked inventory graphics this iType can have.

InvGfx1-6 – This column contains the file names of the inventory graphics that are randomly picked for this iType, so if you use columns 1-3, you will set VarInvGfx to 3 (duh).

StorePage – The page code for the page a vendor should place this iType in when sold, if you enable the magic tab in D2Client.dll, you need to use the proper code here to put items in that tab. Right now the ones used are weap = weapons1 and 2, armo = 
armor and misc = miscellaneous.

*eol – Always needs to be filled with a value (doesn't have to be 0) in order to prevent M$ Excel and other “re-format happy” spreadsheets from messing up the table bounds.

*/

typedef struct
{
    //ItemType在bin文件中没有体现
    unsigned char vCode[4]; //类型代码，或称索引。在各txt文件中对物品类型进行描述都应该使用此列的值。

    //Equiv1、2，需要到第二轮处理，因为引用了自身的其他字段
    unsigned short vEquiv1;
    unsigned short vEquiv2;

    unsigned char vRepair;  //是否可被修理。0代表不可以，1代表可以。只有此类别中的所有物品都可修理时此类别才算作可修理。
    unsigned char vBody;    //是否是穿在身上的装备。0代表不是，1代表是。
    unsigned char vBodyLoc1;    //装备的位置1。有如下几种位置：rarm右手、larm左手、tors躯干、rrin右戒指、lrin左戒指、neck脖子、feet脚、belt腰带、head头部、glov手套。
    unsigned char vBodyLoc2;    //装备的位置2。有如下几种位置：rarm右手、larm左手、tors躯干、rrin右戒指、lrin左戒指、neck脖子、feet脚、belt腰带、head头部、glov手套。

    //Shoots、Quiver，需要到第二轮处理，因为引用了自身的其他字段
    unsigned short vShoots;
    unsigned short vQuiver;

    unsigned char vThrowable;   //是否为投掷型物品。0表示不是，1表示是。如剑此列为0，标枪此列为1。
    unsigned char vReload;  //是否可以自动补充。0表示不可以，1表示可以。如箭矢射完一筒后会自动换新的一筒（如果你包里有），就是因为此列为1。
    unsigned char vReEquip; //数量使用完后物品是否消失。0表示是，1表示不是。如标枪此列为1，那么即使数量用光了标枪也还在。但箭矢此列为0，所以一个箭袋用完了此箭袋就消失了。
    unsigned char vAutoStack;   //是否自动叠加。0代表不是，1代表是。比如你原来背包里有一个箭袋，捡了一个新的箭袋之后由此列决定是否自动与原有的箭袋合并。

    unsigned char vMagic;   //是否一定是魔法物品（或以上级别）。0代表不是，1代表是。如戒指类此列就为1，表示不会有白色的戒指。
    unsigned char vRare;    //是否能有稀有级别的物品。0代表不能，1代表能。如护身符此列为0，表示不可能出现稀有（亮金）的护身符。
    unsigned char vNormal;  //是否只能是普通（白色）物品。0代表不是，1代表是。如回城卷轴此列为1，武器此列为0。
    unsigned char vCharm;   //是否是护身符。0代表不是，1代表是。

    unsigned char vGem; //是否是宝石。0代表不是，1代表是。
    unsigned char vBeltable;    //是否能放入腰带空间中。0代表不是，1代表是。
    unsigned char vMaxSock1;    //物品等级在1-23之间时的最大孔数。
    unsigned char vMaxSock25;   //物品等级在25-39之间时的最大孔数。

    unsigned char vMaxSock40;   //物品等级大于40级时的最大孔数。
    unsigned char vTreasureClass;   //财宝类型（TC）。是否能单独作为一个财宝类型（TC），实际上只有5种可以。武器、近战武器、装甲、弓、亚马逊弓。
    unsigned char vRarity;  //稀有度。在同一TC中出现的概率，值越大掉落的概率越大。请参考物品掉落原理。
    unsigned char vStaffMods;   //杖上面自带的加单一技能属性。比如法师的杖会加法师的技能，就是因为这列有sor这个值。关联playerclass.txt

    unsigned char vCostFormula; //物品价格计算方法（其实我不太明白这列的含义）。
    unsigned char vClass;   //职业限制。如法球类此列的值为sor，表示只有法师能用法球。关联playerclass.txt
    unsigned char vStorePage;   //此类别下具体物品的信息存储在哪个文件里，或者说此类别属于哪个大类。只有3个大类，防具armo，武器weap，杂物misc。
    unsigned char vVarInvGfx;   //在物品栏中可能出现的外观种类。如戒指类此列值为5，即戒指共有5种外观。

    unsigned char vInvGfx1[32];   //外观图片指针。
    unsigned char vInvGfx2[32];   //外观图片指针。
    unsigned char vInvGfx3[32];   //外观图片指针。
    unsigned char vInvGfx4[32];   //外观图片指针。
    unsigned char vInvGfx5[32];   //外观图片指针。
    unsigned char vInvGfx6[32];   //外观图片指针。
} ST_LINE_INFO;

typedef struct
{
    char vCode[5];
} ST_ITEM_TYPES;

static char *m_apcInternalProcess[] =
{
    "ItemType",
    "*eol",
    NULL,
};

static unsigned int m_iItemTypesCount = 0;
static ST_ITEM_TYPES *m_astItemTypes = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astItemTypes, ST_ITEM_TYPES);

char *ItemTypes_GetItemCode(unsigned int id)
{
    if ( id >= m_iItemTypesCount )
    {
        return NULL;
    }

    return m_astItemTypes[id].vCode;
}

static int ItemTypes_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "BodyLoc1") )
    {
        pcResult = BodyLocs_GetLocStr(pstLineInfo->vBodyLoc1);
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
    else if ( !strcmp(acKey, "BodyLoc2") )
    {
        pcResult = BodyLocs_GetLocStr(pstLineInfo->vBodyLoc2);
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
    else if ( !strcmp(acKey, "StaffMods") )
    {
        pcResult = PlayerClass_GetClass(pstLineInfo->vStaffMods);
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
    else if ( !strcmp(acKey, "Class") )
    {
        pcResult = PlayerClass_GetClass(pstLineInfo->vClass);
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
    else if ( !strcmp(acKey, "StorePage") )
    {
        pcResult = StorePage_GetCode(pstLineInfo->vStorePage);
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
    else if ( !strcmp(acKey, "Equiv1") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vEquiv1);
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
    else if ( !strcmp(acKey, "Equiv2") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vEquiv2);
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
    else if ( !strcmp(acKey, "Shoots") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vShoots);
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
    else if ( !strcmp(acKey, "Quiver") )
    {
        pcResult = ItemTypes_GetItemCode(pstLineInfo->vQuiver);
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

static int ItemTypes_FieldProc_Pre(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "ItemType") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            strncpy(acOutput, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
        }

        strncpy(m_astItemTypes[m_iItemTypesCount].vCode, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
        String_Trim(m_astItemTypes[m_iItemTypesCount].vCode);
        m_iItemTypesCount++;
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

static int ItemTypes_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "ItemType") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else
#endif
        {
            strncpy(acOutput, pstLineInfo->vCode, sizeof(pstLineInfo->vCode));
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

static char *ItemTypes_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    strcpy(pcKey, pstLineInfo->vCode);
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

static unsigned int m_uiTcOffset = 0;

static int ItemTypes_CalcTc(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "TreasureClass") && 0 != pstLineInfo->vTreasureClass )
    {
        m_uiTcOffset += 32;
    }

    return 0;
}

int process_itemtypes(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    int result;
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Code, STRING);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Equiv1, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Equiv2, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Repair, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Body, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BodyLoc1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, BodyLoc2, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Shoots, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Quiver, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Throwable, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Reload, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ReEquip, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, AutoStack, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Magic, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Rare, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Normal, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Charm, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Gem, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Beltable, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxSock1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxSock25, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, MaxSock40, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, TreasureClass, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Rarity, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StaffMods, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CostFormula, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Class, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, StorePage, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, VarInvGfx, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InvGfx1, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InvGfx2, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InvGfx3, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InvGfx4, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InvGfx5, STRING);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, InvGfx6, STRING);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iItemTypesCount = 0;

            //m_stCallback.pfnGetKey = ItemTypes_GetKey;
            m_stCallback.pfnFieldProc = ItemTypes_FieldProc_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;
            m_stCallback.pfnConvertValue = ItemTypes_CalcTc;

            m_uiTcOffset = 0;

            result = process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);

            m_uiTcOffset++;
            TreasureClassEx_SetOffset(m_uiTcOffset);

            return result;
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(bodylocs, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(playerclass, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(storepage, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(itemtypes, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            //m_stCallback.pfnGetKey = ItemTypes_GetKey;
            m_stCallback.pfnConvertValue = ItemTypes_ConvertValue;
            m_stCallback.pfnFieldProc = ItemTypes_FieldProc;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo),
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

