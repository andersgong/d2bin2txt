// bin2txt.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdarg.h>
#include "global.h"

typedef int (*fn_process_module)(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase);
typedef struct
{
    char *pcFileName;
    fn_process_module pfnProcessModule;
    ENUM_MODULE_PHASE enPhase;
} ST_MODULE;

#define MODULE_MAP_DEFINE(key) \
    do\
    {\
        m_astProcessModule[MODULE_ID_DEFINE(key)].pcFileName = #key;\
        m_astProcessModule[MODULE_ID_DEFINE(key)].pfnProcessModule = process_##key;\
        m_astProcessModule[MODULE_ID_DEFINE(key)].enPhase = EN_MODULE_PHASE_START;\
    } while (0)

static ST_MODULE m_astProcessModule[EN_MID_MAX];

#define DEBUG_MODULE "all"

void Init_Module()
{
    MODULE_MAP_DEFINE(arena);
    MODULE_MAP_DEFINE(armor);
    MODULE_MAP_DEFINE(armtype);
    MODULE_MAP_DEFINE(automagic);
    MODULE_MAP_DEFINE(automap);
    MODULE_MAP_DEFINE(belts);
    MODULE_MAP_DEFINE(bodylocs);
    MODULE_MAP_DEFINE(books);
    MODULE_MAP_DEFINE(charstats);
    MODULE_MAP_DEFINE(chartemplate);
    MODULE_MAP_DEFINE(colors);
    MODULE_MAP_DEFINE(compcode);
    MODULE_MAP_DEFINE(composit);
    MODULE_MAP_DEFINE(cubemain);
    MODULE_MAP_DEFINE(difficultylevels);
    MODULE_MAP_DEFINE(elemtypes);
    MODULE_MAP_DEFINE(events);
    MODULE_MAP_DEFINE(experience);
    MODULE_MAP_DEFINE(gamble);
    MODULE_MAP_DEFINE(gems);
    MODULE_MAP_DEFINE(hiredesc);
    MODULE_MAP_DEFINE(hireling);
    MODULE_MAP_DEFINE(hitclass);
    MODULE_MAP_DEFINE(inventory);
    MODULE_MAP_DEFINE(itemratio);
    MODULE_MAP_DEFINE(itemstatcost);
    MODULE_MAP_DEFINE(itemtypes);
    MODULE_MAP_DEFINE(levels);
    MODULE_MAP_DEFINE(lowqualityitems);
    MODULE_MAP_DEFINE(lvlmaze);
    MODULE_MAP_DEFINE(lvlprest);
    MODULE_MAP_DEFINE(lvlsub);
    MODULE_MAP_DEFINE(lvltypes);
    MODULE_MAP_DEFINE(lvlwarp);
    MODULE_MAP_DEFINE(magicprefix);
    MODULE_MAP_DEFINE(magicsuffix);
    MODULE_MAP_DEFINE(misc);
    MODULE_MAP_DEFINE(misscalc);
    MODULE_MAP_DEFINE(missiles);
    MODULE_MAP_DEFINE(monai);
    MODULE_MAP_DEFINE(monequip);
    MODULE_MAP_DEFINE(monitempercent);
    MODULE_MAP_DEFINE(monlvl);
    MODULE_MAP_DEFINE(monmode);
    MODULE_MAP_DEFINE(monplace);
    MODULE_MAP_DEFINE(monpreset);
    MODULE_MAP_DEFINE(monprop);
    MODULE_MAP_DEFINE(monseq);
    MODULE_MAP_DEFINE(monsounds);
    MODULE_MAP_DEFINE(monstats);
    MODULE_MAP_DEFINE(monstats2);
    MODULE_MAP_DEFINE(montype);
    MODULE_MAP_DEFINE(monumod);
    MODULE_MAP_DEFINE(npc);
    MODULE_MAP_DEFINE(objects);
    MODULE_MAP_DEFINE(objgroup);
    MODULE_MAP_DEFINE(objmode);
    MODULE_MAP_DEFINE(objtype);
    MODULE_MAP_DEFINE(overlay);
    MODULE_MAP_DEFINE(pettype);
    MODULE_MAP_DEFINE(playerclass);
    MODULE_MAP_DEFINE(plrmode);
    MODULE_MAP_DEFINE(plrtype);
    MODULE_MAP_DEFINE(properties);
    MODULE_MAP_DEFINE(qualityitems);
    MODULE_MAP_DEFINE(rareprefix);
    MODULE_MAP_DEFINE(raresuffix);
    MODULE_MAP_DEFINE(runes);
    MODULE_MAP_DEFINE(setitems);
    MODULE_MAP_DEFINE(sets);
    MODULE_MAP_DEFINE(shrines);
    MODULE_MAP_DEFINE(skillcalc);
    MODULE_MAP_DEFINE(skilldesc);
    MODULE_MAP_DEFINE(skills);
    MODULE_MAP_DEFINE(sounds);
    MODULE_MAP_DEFINE(states);
    MODULE_MAP_DEFINE(storepage);
    MODULE_MAP_DEFINE(string);
    MODULE_MAP_DEFINE(superuniques);
    MODULE_MAP_DEFINE(treasureclassex);
    MODULE_MAP_DEFINE(uniqueappellation);
    MODULE_MAP_DEFINE(uniqueitems);
    MODULE_MAP_DEFINE(uniqueprefix);
    MODULE_MAP_DEFINE(uniquesuffix);
    MODULE_MAP_DEFINE(uniquetitle);
    MODULE_MAP_DEFINE(weapons);
}

void Set_ModulePhase(ENUM_MODULE_ID enMid, ENUM_MODULE_PHASE enPhase)
{
    m_astProcessModule[enMid].enPhase = enPhase;
}

ENUM_MODULE_PHASE Get_ModulePhase(ENUM_MODULE_ID enMid)
{
    return m_astProcessModule[enMid].enPhase;
}

static FILE *m_pfLogHandle = NULL;
static int m_iPrintFlag = 1;

unsigned int my_printf( const char *pcFormat,... )
{
    va_list args;
    unsigned int dwStringLength;
    static char m_acPrintTempBuf[2048];

    if ( 0 == m_iPrintFlag )
    {
        return 0;
    }

    if( NULL == pcFormat )
    {
        return 0;
    }

    va_start(args, pcFormat);
    dwStringLength = vsnprintf( m_acPrintTempBuf, sizeof(m_acPrintTempBuf), pcFormat, args);
    va_end(args);

    if( dwStringLength >= 0 )
    {
        m_acPrintTempBuf[dwStringLength] = 0;
    }

    printf("%s", m_acPrintTempBuf);

    if ( NULL != m_pfLogHandle )
    {
        fwrite(m_acPrintTempBuf, 1, strlen(m_acPrintTempBuf), m_pfLogHandle);
    }

    return dwStringLength;
}

#define MODULE_NAME_TO_ID(name) \
    else if ( !strcmp(#name, pcModuleName) )\
    {\
        return MODULE_ID_DEFINE(name);\
    }

static ENUM_MODULE_ID Get_ModuleId(char *pcModuleName)
{
    if ( !strcmp("all", pcModuleName) )
    {
        return EN_MID_MAX;
    }
    MODULE_NAME_TO_ID(arena)
    MODULE_NAME_TO_ID(armor)
    MODULE_NAME_TO_ID(armtype)
    MODULE_NAME_TO_ID(automagic)
    MODULE_NAME_TO_ID(automap)
    MODULE_NAME_TO_ID(belts)
    MODULE_NAME_TO_ID(bodylocs)
    MODULE_NAME_TO_ID(books)
    MODULE_NAME_TO_ID(charstats)
    MODULE_NAME_TO_ID(chartemplate)
    MODULE_NAME_TO_ID(colors)
    MODULE_NAME_TO_ID(compcode)
    MODULE_NAME_TO_ID(composit)
    MODULE_NAME_TO_ID(cubemain)
    MODULE_NAME_TO_ID(difficultylevels)
    MODULE_NAME_TO_ID(elemtypes)
    MODULE_NAME_TO_ID(events)
    MODULE_NAME_TO_ID(experience)
    MODULE_NAME_TO_ID(gamble)
    MODULE_NAME_TO_ID(gems)
    MODULE_NAME_TO_ID(hiredesc)
    MODULE_NAME_TO_ID(hireling)
    MODULE_NAME_TO_ID(hitclass)
    MODULE_NAME_TO_ID(inventory)
    MODULE_NAME_TO_ID(itemratio)
    MODULE_NAME_TO_ID(itemstatcost)
    MODULE_NAME_TO_ID(itemtypes)
    MODULE_NAME_TO_ID(levels)
    MODULE_NAME_TO_ID(lowqualityitems)
    MODULE_NAME_TO_ID(lvlmaze)
    MODULE_NAME_TO_ID(lvlprest)
    MODULE_NAME_TO_ID(lvlsub)
    MODULE_NAME_TO_ID(lvltypes)
    MODULE_NAME_TO_ID(lvlwarp)
    MODULE_NAME_TO_ID(magicprefix)
    MODULE_NAME_TO_ID(magicsuffix)
    MODULE_NAME_TO_ID(misc)
    MODULE_NAME_TO_ID(misscalc)
    MODULE_NAME_TO_ID(missiles)
    MODULE_NAME_TO_ID(monai)
    MODULE_NAME_TO_ID(monequip)
    MODULE_NAME_TO_ID(monitempercent)
    MODULE_NAME_TO_ID(monlvl)
    MODULE_NAME_TO_ID(monmode)
    MODULE_NAME_TO_ID(monplace)
    MODULE_NAME_TO_ID(monpreset)
    MODULE_NAME_TO_ID(monprop)
    MODULE_NAME_TO_ID(monseq)
    MODULE_NAME_TO_ID(monsounds)
    MODULE_NAME_TO_ID(monstats)
    MODULE_NAME_TO_ID(monstats2)
    MODULE_NAME_TO_ID(montype)
    MODULE_NAME_TO_ID(monumod)
    MODULE_NAME_TO_ID(npc)
    MODULE_NAME_TO_ID(objects)
    MODULE_NAME_TO_ID(objgroup)
    MODULE_NAME_TO_ID(objmode)
    MODULE_NAME_TO_ID(objtype)
    MODULE_NAME_TO_ID(overlay)
    MODULE_NAME_TO_ID(pettype)
    MODULE_NAME_TO_ID(playerclass)
    MODULE_NAME_TO_ID(plrmode)
    MODULE_NAME_TO_ID(plrtype)
    MODULE_NAME_TO_ID(properties)
    MODULE_NAME_TO_ID(qualityitems)
    MODULE_NAME_TO_ID(rareprefix)
    MODULE_NAME_TO_ID(raresuffix)
    MODULE_NAME_TO_ID(runes)
    MODULE_NAME_TO_ID(setitems)
    MODULE_NAME_TO_ID(sets)
    MODULE_NAME_TO_ID(shrines)
    MODULE_NAME_TO_ID(skillcalc)
    MODULE_NAME_TO_ID(skilldesc)
    MODULE_NAME_TO_ID(skills)
    MODULE_NAME_TO_ID(sounds)
    MODULE_NAME_TO_ID(states)
    MODULE_NAME_TO_ID(storepage)
    MODULE_NAME_TO_ID(string)
    MODULE_NAME_TO_ID(superuniques)
    MODULE_NAME_TO_ID(treasureclassex)
    MODULE_NAME_TO_ID(uniqueappellation)
    MODULE_NAME_TO_ID(uniqueitems)
    MODULE_NAME_TO_ID(uniqueprefix)
    MODULE_NAME_TO_ID(uniquesuffix)
    MODULE_NAME_TO_ID(uniquetitle)
    MODULE_NAME_TO_ID(weapons)

    return EN_MID_MAX;
}

static void usage(int argc, char* argv[])
{
/*
-template指定模板文件路径
-bin指定bin文件路径
-output指定输出txt文件的路径
-all处理所有的bin文件
-file指定处理某一个bin文件
*/
    char *pcExeName;

    if ( pcExeName = strrchr(argv[0], '\\') )
    {
        my_printf("Usage: %s [args]\r\n", pcExeName + 1);
    }
    else
    {
        my_printf("Usage: %s [args]\r\n", argv[0]);
    }
    my_printf("    -tc <specific tc offset>\r\n");
    my_printf("    -template <template path>\r\n");
    my_printf("    -bin <bin path>\r\n");
    my_printf("    -output <output txt path>\r\n");
    my_printf("    -all | -file <specific file prefix>\r\n");
}

int main(int argc, char* argv[])
{
    static char acTemplatePath[256] = {0};
    static char acBinPath[256] = {0};
    static char acTxtPath[256] = {0};

    ENUM_MODULE_ID enProcessModule = EN_MID_MAX;

    char acFailedList[100 * 32] = {0};

    char *pcFailed = acFailedList;
    int i;
    int j;
    int iCount = 0;
    int iSuccess = 0;
    int iFail = 0;

    if ( 1 < argc && argv[1] == strstr(argv[1], "-h") )
    {
        usage(argc, argv);
        getchar();
        return 0;
    }

    m_pfLogHandle = fopen("output.txt", "wt");
    MemMgr_Init();

    i = 1;
    j = argc;

    if ( i + 1 < argc && !strcmp("-tc", argv[i]) )
    {
        sscanf(argv[i + 1], "%d", &iCount);
        i += 2;
    }
    else
    {
        iCount = 0;
    }

    //for test
    //iCount = 161;    //原版
    //iCount = 321;  //魔电v15
#ifdef _DEBUG
    iCount = 193;  //宝日8.4
#endif
    my_printf("    tc offset %u\r\n", iCount);
    TreasureClassEx_SetOffset(iCount);
    iCount = 0;

    if ( i + 1 < argc && !strcmp("-template", argv[i]) )
    {
        strcpy(acTemplatePath, argv[i + 1]);
        i += 2;
    }
    else
    {
#ifdef _DEBUG
        strcpy(acTemplatePath, "..\\test\\template");
#else
        strcpy(acTemplatePath, ".\\template");
#endif
    }

    if ( i + 1 < argc && !strcmp("-bin", argv[i]) )
    {
        strcpy(acBinPath, argv[i + 1]);
        i += 2;
    }
    else
    {
#ifdef _DEBUG
        strcpy(acBinPath, "..\\test\\bin");
#else
        strcpy(acBinPath, ".\\bin");
#endif
    }

    if ( i + 1 < argc && !strcmp("-output", argv[i]) )
    {
        strcpy(acTxtPath, argv[i + 1]);
        i += 2;
    }
    else
    {
#ifdef _DEBUG
        strcpy(acTxtPath, "..\\test\\txt");
#else
        strcpy(acTxtPath, ".\\txt");
#endif
    }

    if ( i < argc && !strcmp("-all", argv[i]) )
    {
        enProcessModule = EN_MID_MAX;;
    }
    else if ( i + 1 < argc && !strcmp("-file", argv[i]) )
    {
        enProcessModule = Get_ModuleId(argv[i + 1]);
    }
    else
    {
        enProcessModule = EN_MID_MAX;;
    }

    //for test
    //enProcessModule = MODULE_ID_DEFINE(setitems);

    my_printf("Args:\r\n");
    my_printf("    template path %s\r\n", acTemplatePath);
    my_printf("    bin path %s\r\n", acBinPath);
    my_printf("    output path %s\r\n", acTxtPath);
    if ( EN_MID_MAX == enProcessModule )
    {
        my_printf("    all module\r\n");
    }
    else if ( i + 1 < argc && !strcmp("-file", argv[i]) )
    {
        my_printf("    module %s\r\n", argv[i + 1]);
    }
    else
    {
        my_printf("    all module\r\n");
    }

    my_printf("confirm start?(y/n)");
    scanf("%c", &i);

    if ( 'y' != i && 'Y' != i )
    {
        goto out;
    }

    if ( _access(acTxtPath, 0) ) 
    {
        sprintf(m_acGlobalBuffer, "md %s", acTxtPath);
        system(m_acGlobalBuffer);
    }

    Init_Module();
    Operater_Init();

    iCount = sizeof(m_astProcessModule) / sizeof(m_astProcessModule[0]);
    memset(acFailedList, 0, sizeof(acFailedList));

    if ( EN_MID_MAX > enProcessModule )
    {
        i = enProcessModule;
        if ( m_astProcessModule[i].pcFileName && m_astProcessModule[i].pfnProcessModule )
        {
            if ( !strcmp("all", DEBUG_MODULE) )
            {
                m_iPrintFlag = 1;
            }
            else if ( !strcmp(DEBUG_MODULE, m_astProcessModule[i].pcFileName) )
            {
                m_iPrintFlag = 1;
            }
            else
            {
                m_iPrintFlag = 0;
            }

            my_printf("****************[%d]****************\r\n", i);
            my_printf("****************%s****************\r\n", m_astProcessModule[i].pcFileName);

            for ( j = (int)Get_ModulePhase((ENUM_MODULE_ID)i) + 1; j < (int)EN_MODULE_PHASE_MAX; j++ )
            {
                my_printf("****************phase %d****************\r\n", j);
                Set_ModulePhase((ENUM_MODULE_ID)i, (ENUM_MODULE_PHASE)j);

                memset(&m_stCallback, 0, sizeof(m_stCallback));
                memset(m_acLineInfoBuf, 0, m_iLineBufLength);
                memset(m_acValueMapBuf, 0, m_iValueBufLength);
                m_iValueMapIndex = 0;

                if ( 0 == m_astProcessModule[i].pfnProcessModule(acTemplatePath, acBinPath, acTxtPath, (ENUM_MODULE_PHASE)j) )
                {
                    iFail++;
                    sprintf(pcFailed, "%s\r\n", m_astProcessModule[i].pcFileName);
                    pcFailed += strlen(pcFailed);
                    my_error("****************failed****************\r\n");
                    break;
                }
                else
                {
                    my_printf("****************success****************\r\n");
                }
            }

            if ( j >= EN_MODULE_PHASE_MAX )
            {
                iSuccess++;
            }

            my_printf("****************%s****************\r\n\r\n\r\n", m_astProcessModule[i].pcFileName);
        }
    }
    else
    {
        for ( i = 0; i < iCount; i++ )
        {
            if ( m_astProcessModule[i].pcFileName && m_astProcessModule[i].pfnProcessModule )
            {
                if ( !strcmp("all", DEBUG_MODULE) )
                {
                    m_iPrintFlag = 1;
                }
                else if ( !strcmp(DEBUG_MODULE, m_astProcessModule[i].pcFileName) )
                {
                    m_iPrintFlag = 1;
                }
                else
                {
                    m_iPrintFlag = 0;
                }

                my_printf("****************[%d]****************\r\n", i);
                my_printf("****************%s****************\r\n", m_astProcessModule[i].pcFileName);

                for ( j = (int)Get_ModulePhase((ENUM_MODULE_ID)i) + 1; j < (int)EN_MODULE_PHASE_MAX; j++ )
                {
                    my_printf("****************phase %d****************\r\n", j);
                    Set_ModulePhase((ENUM_MODULE_ID)i, (ENUM_MODULE_PHASE)j);

                    memset(&m_stCallback, 0, sizeof(m_stCallback));
                    memset(m_acLineInfoBuf, 0, m_iLineBufLength);
                    memset(m_acValueMapBuf, 0, m_iValueBufLength);
                    m_iValueMapIndex = 0;

                    if ( 0 == m_astProcessModule[i].pfnProcessModule(acTemplatePath, acBinPath, acTxtPath, (ENUM_MODULE_PHASE)j) )
                    {
                        iFail++;
                        sprintf(pcFailed, "%s\r\n", m_astProcessModule[i].pcFileName);
                        pcFailed += strlen(pcFailed);
                        my_error("****************failed****************\r\n");
                        break;
                    }
                    else
                    {
                        my_printf("****************success****************\r\n");
                    }
                }

                if ( j >= EN_MODULE_PHASE_MAX )
                {
                    iSuccess++;
                }

                my_printf("****************%s****************\r\n\r\n\r\n", m_astProcessModule[i].pcFileName);
            }
        }
    }

    if ( 0 < iFail )
    {
        my_error("finished。。。total %d。。。success %d。。。failed %d!\r\n", iCount, iSuccess, iFail);
        my_error("Failed list:\r\n%s\r\n", acFailedList);
    }
    else
    {
        my_printf("finished。。。total %d。。。success %d!\r\n", iCount, iSuccess);
    }
    my_printf("press RETURN to exit!\r\n");

out:
    if ( NULL != m_pfLogHandle )
    {
        fclose(m_pfLogHandle);
        m_pfLogHandle = NULL;
    }

    MemMgr_FreeAll();

    getchar();
    getchar();

    return 0;
}

#if 0
typedef struct
{
    unsigned int iPadding0;
    unsigned int iPadding1;
    unsigned int iPadding2;
    unsigned int iPadding3;
    unsigned int iPadding4;
    unsigned int iPadding5;
    unsigned int iPadding6;
    unsigned int iPadding7;
    unsigned int iPadding8;
    unsigned int iPadding9;

    unsigned int iPadding10;
    unsigned int iPadding11;
    unsigned int iPadding12;
    unsigned int iPadding13;
    unsigned int iPadding14;
    unsigned int iPadding15;
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

    unsigned int iPadding80;
    unsigned int iPadding81;
    unsigned int iPadding82;
    unsigned int iPadding83;
    unsigned int iPadding84;
    unsigned int iPadding85;
    unsigned int iPadding86;
    unsigned int iPadding87;
    unsigned int iPadding88;
    unsigned int iPadding89;

    unsigned int iPadding90;
    unsigned int iPadding91;
    unsigned int iPadding92;
    unsigned int iPadding93;
    unsigned int iPadding94;
    unsigned int iPadding95;
    unsigned int iPadding96;
    unsigned int iPadding97;
    unsigned int iPadding98;
    unsigned int iPadding99;

    unsigned int iPadding100;
    unsigned int iPadding101;
    unsigned int iPadding102;
    unsigned int iPadding103;
    unsigned int iPadding104;
    unsigned int iPadding105;
    unsigned int iPadding106;
    unsigned int iPadding107;
    unsigned int iPadding108;
    unsigned int iPadding109;

    unsigned int iPadding110;
    unsigned int iPadding111;
    unsigned int iPadding112;
    unsigned int iPadding113;
    unsigned int iPadding114;
    unsigned int iPadding115;
    unsigned int iPadding116;
    unsigned int iPadding117;
    unsigned int iPadding118;
    unsigned int iPadding119;

    unsigned int iPadding120;
    unsigned int iPadding121;
    unsigned int iPadding122;
    unsigned int iPadding123;
    unsigned int iPadding124;
    unsigned int iPadding125;
    unsigned int iPadding126;
    unsigned int iPadding127;
    unsigned int iPadding128;
    unsigned int iPadding129;

    unsigned int iPadding130;
    unsigned int iPadding131;
    unsigned int iPadding132;
    unsigned int iPadding133;
    unsigned int iPadding134;
    unsigned int iPadding135;
    unsigned int iPadding136;
    unsigned int iPadding137;
    unsigned int iPadding138;
    unsigned int iPadding139;

    unsigned int iPadding140;
    unsigned int iPadding141;
    unsigned int iPadding142;
    unsigned int iPadding143;
    unsigned int iPadding144;
    unsigned int iPadding145;
    unsigned int iPadding146;
    unsigned int iPadding147;
    unsigned int iPadding148;
    unsigned int iPadding149;
} ST_LINE_INFO;
#endif

