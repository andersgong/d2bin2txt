#ifndef __ANDERS_GLOBAL__
#define __ANDERS_GLOBAL__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <io.h>
#include <FCNTL.H>
#include <assert.h>

//#define USE_TEMPLATE
//#define USE_NAME_TOBE_ID

#define MODULE_ID_DEFINE(key) EN_MID_##key

typedef enum
{
    MODULE_ID_DEFINE(arena),
    MODULE_ID_DEFINE(armor),
    MODULE_ID_DEFINE(armtype),
    MODULE_ID_DEFINE(automagic),
    MODULE_ID_DEFINE(automap),
    MODULE_ID_DEFINE(belts),
    MODULE_ID_DEFINE(bodylocs),
    MODULE_ID_DEFINE(books),
    MODULE_ID_DEFINE(charstats),
    MODULE_ID_DEFINE(chartemplate),
    MODULE_ID_DEFINE(colors),
    MODULE_ID_DEFINE(compcode),
    MODULE_ID_DEFINE(composit),
    MODULE_ID_DEFINE(cubemain),
    MODULE_ID_DEFINE(difficultylevels),
    MODULE_ID_DEFINE(elemtypes),
    MODULE_ID_DEFINE(events),
    MODULE_ID_DEFINE(experience),
    MODULE_ID_DEFINE(gamble),
    MODULE_ID_DEFINE(gems),
    MODULE_ID_DEFINE(hiredesc),
    MODULE_ID_DEFINE(hireling),
    MODULE_ID_DEFINE(hitclass),
    MODULE_ID_DEFINE(inventory),
    MODULE_ID_DEFINE(itemratio),
    MODULE_ID_DEFINE(itemstatcost),
    MODULE_ID_DEFINE(itemtypes),
    MODULE_ID_DEFINE(levels),
    MODULE_ID_DEFINE(lowqualityitems),
    MODULE_ID_DEFINE(lvlmaze),
    MODULE_ID_DEFINE(lvlprest),
    MODULE_ID_DEFINE(lvlsub),
    MODULE_ID_DEFINE(lvltypes),
    MODULE_ID_DEFINE(lvlwarp),
    MODULE_ID_DEFINE(magicprefix),
    MODULE_ID_DEFINE(magicsuffix),
    MODULE_ID_DEFINE(misc),
    MODULE_ID_DEFINE(misscalc),
    MODULE_ID_DEFINE(missiles),
    MODULE_ID_DEFINE(monai),
    MODULE_ID_DEFINE(monequip),
    MODULE_ID_DEFINE(monitempercent),
    MODULE_ID_DEFINE(monlvl),
    MODULE_ID_DEFINE(monmode),
    MODULE_ID_DEFINE(monplace),
    MODULE_ID_DEFINE(monpreset),
    MODULE_ID_DEFINE(monprop),
    MODULE_ID_DEFINE(monseq),
    MODULE_ID_DEFINE(monsounds),
    MODULE_ID_DEFINE(monstats),
    MODULE_ID_DEFINE(monstats2),
    MODULE_ID_DEFINE(montype),
    MODULE_ID_DEFINE(monumod),
    MODULE_ID_DEFINE(npc),
    MODULE_ID_DEFINE(objects),
    MODULE_ID_DEFINE(objgroup),
    MODULE_ID_DEFINE(objmode),
    MODULE_ID_DEFINE(objtype),
    MODULE_ID_DEFINE(overlay),
    MODULE_ID_DEFINE(pettype),
    MODULE_ID_DEFINE(playerclass),
    MODULE_ID_DEFINE(plrmode),
    MODULE_ID_DEFINE(plrtype),
    MODULE_ID_DEFINE(properties),
    MODULE_ID_DEFINE(qualityitems),
    MODULE_ID_DEFINE(rareprefix),
    MODULE_ID_DEFINE(raresuffix),
    MODULE_ID_DEFINE(runes),
    MODULE_ID_DEFINE(setitems),
    MODULE_ID_DEFINE(sets),
    MODULE_ID_DEFINE(shrines),
    MODULE_ID_DEFINE(skillcalc),
    MODULE_ID_DEFINE(skilldesc),
    MODULE_ID_DEFINE(skills),
    MODULE_ID_DEFINE(sounds),
    MODULE_ID_DEFINE(states),
    MODULE_ID_DEFINE(storepage),
    MODULE_ID_DEFINE(string),
    MODULE_ID_DEFINE(superuniques),
    MODULE_ID_DEFINE(treasureclassex),
    MODULE_ID_DEFINE(uniqueappellation),
    MODULE_ID_DEFINE(uniqueitems),
    MODULE_ID_DEFINE(uniqueprefix),
    MODULE_ID_DEFINE(uniquesuffix),
    MODULE_ID_DEFINE(uniquetitle),
    MODULE_ID_DEFINE(weapons),

    EN_MID_MAX,
} ENUM_MODULE_ID;

typedef struct
{
    unsigned int iLines; //条目数量
} ST_FILE_HEADER;

typedef enum
{
    EN_VALUE_INT,
    EN_VALUE_UINT,
    EN_VALUE_SHORT,
    EN_VALUE_USHORT,
    EN_VALUE_CHAR,
    EN_VALUE_UCHAR,
    EN_VALUE_STRING,
    EN_VALUE_BIT,
} ENUM_VALUE_TYPE;

typedef enum
{
    EN_MODULE_PHASE_START,

    EN_MODULE_SELF_DEPEND,
    EN_MODULE_OTHER_DEPEND,
    EN_MODULE_RESERVED_1,
    EN_MODULE_RESERVED_2,
    EN_MODULE_INIT,

    EN_MODULE_PHASE_MAX,
} ENUM_MODULE_PHASE;

typedef struct
{
    char *acKeyName;
    void *pvValue;
    ENUM_VALUE_TYPE enValueType;
    int iValueLen;
} ST_VALUE_MAP;

#define INIT_VALUE_BUFFER \
    do {\
        memset(&m_stCallback, 0, sizeof(m_stCallback));\
        memset(m_acLineInfoBuf, 0, m_iLineBufLength);\
        memset(m_acValueMapBuf, 0, m_iValueBufLength);\
        m_iValueMapIndex = 0;\
    } while (0)

#define MODULE_DEPEND_CALL(module, template, bin ,txt) \
    do {\
        int k;\
        ENUM_MODULE_PHASE enCurrentPhase = Get_ModulePhase(MODULE_ID_DEFINE(module));\
        my_printf("\r\n#############depend %s#############\r\n", #module);\
        for ( k = (int)enCurrentPhase + 1; k <= (int)EN_MODULE_SELF_DEPEND; k++ )\
        {\
            my_printf("################phase %d################\r\n", k);\
            Set_ModulePhase(MODULE_ID_DEFINE(module), k);\
            memset(&m_stCallback, 0, sizeof(m_stCallback));\
            memset(m_acLineInfoBuf, 0, m_iLineBufLength);\
            memset(m_acValueMapBuf, 0, m_iValueBufLength);\
            m_iValueMapIndex = 0;\
            if ( 0 != process_##module(template, bin, txt, k) ) \
            {\
                my_printf("################success################\r\n");\
            }\
            else\
            {\
                my_printf("################failed################\r\n");\
                break;\
            }\
        }\
        my_printf("################%s################\r\n\r\n", #module);\
    }while (0)\

#define VALUE_MAP_DEFINE(map, line, key, type) \
    do {\
        map[m_iValueMapIndex].acKeyName = #key;\
        map[m_iValueMapIndex].pvValue = &line->v##key;\
        map[m_iValueMapIndex].enValueType = EN_VALUE_##type;\
        map[m_iValueMapIndex].iValueLen = sizeof(line->v##key);\
        m_iValueMapIndex++;\
    } while (0)

#define VALUE_MAP_DEFINE_2(map, line, key, field, type) \
    do {\
        map[m_iValueMapIndex].acKeyName = #key;\
        map[m_iValueMapIndex].pvValue = &line->v##field;\
        map[m_iValueMapIndex].enValueType = EN_VALUE_##type;\
        map[m_iValueMapIndex].iValueLen = sizeof(line->v##field);\
        m_iValueMapIndex++;\
    } while (0)

#define SETLINES_FUNC_NAME(module) module##_SetLines
#define FINISHED_FUNC_NAME(module) module##_Finished
#define MODULE_SETLINES_FUNC(module, buffer, datastruct) \
    static void module##_SetLines(unsigned int uiLines)\
    {\
        if ( NULL != buffer )\
        {\
            return;\
        }\
        buffer = MemMgr_Malloc(sizeof(datastruct) * uiLines);\
        if ( NULL == buffer )\
        {\
            my_error("malloc fail with %u lines\r\n", uiLines);\
        }\
        else\
        {\
            memset(buffer, 0, sizeof(datastruct) * uiLines);\
        }\
    }\
    static void module##_Finished()\
    {\
        if ( NULL != buffer )\
        {\
            MemMgr_Free(buffer);\
            buffer = NULL;\
        }\
    }

extern void MemMgr_Init();
extern void *MemMgr_Malloc(unsigned int size);
extern void MemMgr_Free(void *pvAddr);
extern void MemMgr_FreeAll();

//获取每一行的key，用于在模板文件中找到对应的内容，并和bin文件中的对应行进行合并
//对于没有key的行，则传空指针，只能根据行号对应了
typedef char * (*fnGetKey) (void *pvLineInfo, char *acKey, unsigned int *iKeyLen);
//转换value的内容，比如根据索引值，到另一文件中查找对应的字符串
typedef int (*fnConvertValue) (void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput);
//bit位处理接口
typedef int (*fnBitProc) (void *pvLineInfo, char *acKey, char *acOutput);
//特殊字段处理接口，当bin文件中没有处理某个字段的时候，可以在这里生成值，否则就直接使用模板文件里的内容
typedef int (*fnFieldProc) (void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput);
//通知该模块，bin文件的行数，便于分配内存
typedef void (*fnSetFileLines)(unsigned int uiLines);
//通知该模块释放内存
typedef void (*fnFinished)();

typedef struct
{
    fnGetKey pfnGetKey;
    fnConvertValue pfnConvertValue;
    fnBitProc pfnBitProc;
    fnFieldProc pfnFieldProc;
    fnSetFileLines pfnSetLines;
    fnFinished pfnFinished;

    char **ppcKeyNotUsed;

    char **ppcKeyNotParsed;

    char **ppcKeyInternalProcess;
} ST_CALLBACK;

//公共临时buffer
#define MAX_FILE_SIZE   (10 * 1024 * 1024)
#define m_iGlobaBufLength   MAX_FILE_SIZE
extern char m_acGlobalBuffer[];
#define m_iLineBufLength   (1024 * 1024)
extern char m_acLineInfoBuf[];
#define m_iValueBufLength   (1024 * 1024)
extern char m_acValueMapBuf[];
extern unsigned int m_iValueMapIndex;
extern ST_CALLBACK m_stCallback;
extern unsigned int Global_GetValueMapCount();

extern int File_GetFileSize(char *pcFileName);
extern int File_CopyFile(char *pcFromPath, char *pcToPath, char *pcFileName, char *pcSuffix);
extern unsigned char *String_Trim(unsigned char *pcValue);
extern void Set_ModulePhase(ENUM_MODULE_ID enMid, ENUM_MODULE_PHASE enPhase);
extern ENUM_MODULE_PHASE Get_ModulePhase(ENUM_MODULE_ID enMid);

#define MAX_OPERATER_LEVEL  0xFF
#define FUNCTION_OPERATER_LEVEL  1
#define SINGLE_OPERATER_LEVEL  1

typedef enum
{
    EN_OPERATER_START = 0x02,

    EN_OPERATER_BRACKET_1 = 0x02,
    EN_OPERATER_SMALL = 0x0a,
    EN_OPERATER_BIG = 0x0b,
    EN_OPERATER_SMALLEQUAL = 0x0c,
    EN_OPERATER_BIGEQUAL = 0x0d,
    EN_OPERATER_EQUAL = 0x0e,
    EN_OPERATER_NOTEQUAL = 0x0f,
    EN_OPERATER_ADD = 0x10,
    EN_OPERATER_SUB = 0x11,
    EN_OPERATER_MULTI = 0x12,
    EN_OPERATER_DIVIDE = 0x13,
    EN_OPERATER_XOR = 0x14,
    EN_OPERATER_INVERSION = 0x15,
    EN_OPERATER_CONDITION = 0x16,

    EN_OPERATER_MAX,
} ENUM_OPERATER_TYPE;

typedef enum
{
    EN_OPERATER_ARG_1,
    EN_OPERATER_ARG_2,
    EN_OPERATER_ARG_3,
} ENUM_OPERATER_ARGNUM;

typedef enum
{
    EN_OPERATER_LEFT,
    EN_OPERATER_RIGHT,
} ENUM_OPERATER_LEFTRIGHT;

extern void Operater_Init();
extern unsigned char *Operater_GetOpStr(ENUM_OPERATER_TYPE enOpType);
extern unsigned int Operater_GetOpLevel(ENUM_OPERATER_TYPE enOpType);
extern ENUM_OPERATER_LEFTRIGHT Operater_GetLeftRight(ENUM_OPERATER_TYPE enOpType);
extern ENUM_OPERATER_ARGNUM Operater_GetArgNum(ENUM_OPERATER_TYPE enOpType);

//文件处理统一入口，合并模板和bin文件的对应内容
extern int process_file(char *acTemplatePath, char *acBinPath, char *acTxtPath, char *pcFilename,
    void *pvLineInfo, int iLineLength, ST_VALUE_MAP *pstValueMap, int iValueCount,
    ST_CALLBACK *pstCallback);
extern int process_file_special_bin(char *acTemplatePath, char *acBinPath, char *acTxtPath, char *pcFilename,
    void *pvLineInfo, int iLineLength, ST_VALUE_MAP *pstValueMap, int iValueCount,
    ST_CALLBACK *pstCallback);

extern unsigned int my_printf( const char *pcFormat,... );
#define my_error my_printf("[error]: %s-%u\r\n\t", __FILE__, __LINE__);my_printf

extern void * Stack_Create(unsigned int uiElemSize, unsigned int uiElemCount);
extern void Stack_Release(void *pvStack);
extern int Stack_Push(void *pvStack, unsigned char *pcElement, unsigned int uiElemSize);
extern int Stack_Pop(void *pvStack, unsigned char **ppcElement);
extern int Stack_IsEmpty(void *pvStack);

//以下是各个模块提供的外部接口
extern int process_arena(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_automap(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_belts(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_armtype(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_string(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *String_FindString(unsigned int id, char* pcFilter);
extern char *String_FindString_2(unsigned int id, char* pcFilter, char* pcFilter2);

extern int process_armor(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *Armor_GetArmorCode(unsigned int id);
extern unsigned int Armor_GetArmorCount();

extern int process_weapons(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *Weapons_GetWeaponCode(unsigned int id);
extern unsigned int Weapons_GetWeaponCount();

extern int process_colors(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *Colors_GetColorCode(unsigned int id);

extern int process_composit(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_compcode(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *Compcode_GetCode(unsigned int id);

extern int process_playerclass(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *PlayerClass_GetClass(unsigned int id);

extern int process_chartemplate(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_storepage(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *StorePage_GetCode(unsigned int id);

extern int process_automagic(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_elemtypes(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *ElemTypes_GetElemStr(unsigned int id);

extern int process_bodylocs(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *BodyLocs_GetLocStr(unsigned int id);

extern int process_hitclass(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *HitClass_GetClassStr(unsigned int id);

extern int process_skilldesc(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *SkillDesc_GetDesc(unsigned int id);

extern int process_overlay(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *Overlay_GetOverlay(unsigned int id);

extern int process_missiles(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *Missiles_GetMissile(unsigned int id);

extern char *PlrMode_GetCode(unsigned int id);
extern int process_plrmode(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_monmode(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *MonMode_GetName(unsigned int id);
extern char *MonMode_GetCode(unsigned int id);

extern int process_events(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *Events_GetEventName(unsigned int id);

extern int SkillsCode_ParseBin(char *acTemplatePath, char *acBinPath, char*acTxtPath);
extern char *SkillsCode_GetExpression(unsigned int id);

extern int SkillDescCode_ParseBin(char *acTemplatePath, char *acBinPath, char*acTxtPath);
extern char *SkillDescCode_GetExpression(unsigned int id);

extern int process_skills(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *Skills_GetSkillName(unsigned int id);

extern int process_sounds(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *Sounds_GetSoundName(unsigned int id);

extern int process_itemtypes(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *ItemTypes_GetItemCode(unsigned int id);

extern int process_states(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *States_GetStateName(unsigned int id);

extern int process_itemstatcost(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *ItemStatCost_GetStateName(unsigned int id);

extern int process_properties(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *Properties_GetProperty(unsigned int id);

extern int process_misc(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *Misc_GetItemUniqueCode(unsigned int id);

extern int process_monstats(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *MonStats_GetStatsName(unsigned int id);

extern int process_pettype(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *Pettype_GetPetType(unsigned int id);

extern int process_charstats(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_books(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_cubemain(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_difficultylevels(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_experience(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_gamble(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_gems(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_hiredesc(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *HireDesc_GetDesc(unsigned int id);

extern int process_hireling(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_inventory(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_itemratio(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_levels(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_lowqualityitems(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_lvlmaze(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_lvlprest(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_lvlsub(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_lvltypes(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_lvlwarp(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_magicprefix(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_magicsuffix(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_misscalc(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *MissCalc_GetCalcCode(unsigned int id);

extern int process_monai(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *MonAi_GetAiName(unsigned int id);

extern int process_monequip(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_monitempercent(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_monlvl(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_monplace(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *MonPlace_GetPlaceName(unsigned int id);

extern int process_monpreset(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_superuniques(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *SuperUniques_GetItemUniqueCode(unsigned int id);

extern int process_monsounds(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *MonSounds_GetItemSoundsCode(unsigned int id);

extern int process_treasureclassex(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *TreasureClassEx_GetItemTreasureClass(unsigned int id);
extern void TreasureClassEx_SetOffset(unsigned int uiOffset);

extern int process_monprop(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *MonProp_GetPropId(unsigned int id);

extern int process_monseq(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *MonSeq_GetSequence(unsigned int id);

extern int process_monstats2(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *MonStats2_GetStatsName(unsigned int id);

extern int process_montype(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *MonType_GetType(unsigned int id);

extern int process_monumod(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_npc(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_objects(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_objgroup(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_objmode(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_objtype(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_plrtype(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_qualityitems(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_rareprefix(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_raresuffix(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_runes(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_setitems(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *SetItems_GetItemUniqueCode(unsigned int id);

extern char *Sets_GetSetName(unsigned int id);
extern int process_sets(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_shrines(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_skillcalc(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *SkillCalc_GetCalc(unsigned int id);

extern int process_uniqueappellation(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_uniqueprefix(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_uniquesuffix(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_uniquetitle(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);

extern int process_uniqueitems(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
extern char *UniqueItems_GetItemUniqueCode(unsigned int id);

extern int ItemsCode_ParseBin(char *acTemplatePath, char *acBinPath, char*acTxtPath);
extern char *ItemsCode_GetExpression(unsigned int id);

extern int MissCode_ParseBin(char *acTemplatePath, char *acBinPath, char*acTxtPath);
extern char *MissCode_GetExpression(unsigned int id);

#ifdef __cplusplus
}
#endif

#endif

