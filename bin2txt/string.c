#include "global.h"

typedef struct
{
    char vString[64];
} ST_STRING;

static unsigned int m_iStringCount;
static ST_STRING m_astString[10000];
static unsigned int m_iPatchStringCount;
static ST_STRING m_astPatchString[10000];
static unsigned int m_iExpansionsStringCount;
static ST_STRING m_astExpansionsString[20000];

static int process_string_x(char *acTemplatePath, char *acBinPath, char *acTxtPath)
{
    char acTxtFile[256] = {0};
    FILE *pfTxtHandle = NULL;
    char *pcStart;
    char *pcSkill;
    char *pcAnchor;

    m_iStringCount = 0;
    memset(m_astString, 0, sizeof(m_astString));

    sprintf(acTxtFile, "%s\\%s.txt", acTemplatePath, "string");
    pfTxtHandle = fopen(acTxtFile, "rb");
    if ( pfTxtHandle )
    {
        memset(m_acGlobalBuffer, 0, m_iGlobaBufLength);

        while ( fgets(m_acGlobalBuffer, m_iGlobaBufLength, pfTxtHandle) )
        {
            pcStart = m_acGlobalBuffer;

            pcSkill = pcStart;
            pcAnchor = strchr(pcStart, '\t');
            *pcAnchor = 0;
            pcAnchor++;

            strcpy(m_astString[m_iStringCount].vString, pcSkill);
            m_iStringCount++;

            memset(m_acGlobalBuffer, 0, m_iGlobaBufLength);
        }

        fclose(pfTxtHandle);

        my_printf("%d string\r\n", m_iStringCount);

        File_CopyFile(acTemplatePath, acTxtPath, "string", ".txt");
    }
    else
    {
        my_printf("fail to open %s\r\n", acTxtFile);
        return 0;
    }

    m_iPatchStringCount = 0;
    memset(m_astPatchString, 0, sizeof(m_astPatchString));

    sprintf(acTxtFile, "%s\\%s.txt", acTemplatePath, "patchstring");
    pfTxtHandle = fopen(acTxtFile, "rb");
    if ( pfTxtHandle )
    {
        memset(m_acGlobalBuffer, 0, m_iGlobaBufLength);

        while ( fgets(m_acGlobalBuffer, m_iGlobaBufLength, pfTxtHandle) )
        {
            pcStart = m_acGlobalBuffer;

            pcSkill = pcStart;
            pcAnchor = strchr(pcStart, '\t');
            *pcAnchor = 0;
            pcAnchor++;

            strcpy(m_astPatchString[m_iPatchStringCount].vString, pcSkill);
            m_iPatchStringCount++;

            memset(m_acGlobalBuffer, 0, m_iGlobaBufLength);
        }

        fclose(pfTxtHandle);

        my_printf("%d patchstring\r\n", m_iPatchStringCount);

        File_CopyFile(acTemplatePath, acTxtPath, "patchstring", ".txt");
    }
    else
    {
        my_printf("fail to open %s\r\n", acTxtFile);
        return 0;
    }

    m_iExpansionsStringCount = 0;
    memset(m_astExpansionsString, 0, sizeof(m_astExpansionsString));

    sprintf(acTxtFile, "%s\\%s.txt", acTemplatePath, "expansionstring");
    pfTxtHandle = fopen(acTxtFile, "rb");
    if ( pfTxtHandle )
    {
        memset(m_acGlobalBuffer, 0, m_iGlobaBufLength);

        while ( fgets(m_acGlobalBuffer, m_iGlobaBufLength, pfTxtHandle) )
        {
            pcStart = m_acGlobalBuffer;

            pcSkill = pcStart;
            pcAnchor = strchr(pcStart, '\t');
            *pcAnchor = 0;
            pcAnchor++;

            strcpy(m_astExpansionsString[m_iExpansionsStringCount].vString, pcSkill);
            m_iExpansionsStringCount++;

            memset(m_acGlobalBuffer, 0, m_iGlobaBufLength);
        }

        fclose(pfTxtHandle);

        my_printf("%d expansionstring\r\n", m_iExpansionsStringCount);

        File_CopyFile(acTemplatePath, acTxtPath, "expansionstring", ".txt");
    }
    else
    {
        my_printf("fail to open %s\r\n", acTxtFile);
        return 0;
    }

    return 1;
}

int process_string(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            return process_string_x(acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_OTHER_DEPEND:
        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
        case EN_MODULE_INIT:
        default:
            break;
    }

    return 1;
}

char *String_FindString(unsigned int id, char* pcFilter)
{
    char *pcResult = NULL;

    if ( 0xFFFF <= id  )
    {
        return NULL;
    }

    if ( id < m_iStringCount )
    {
        pcResult = m_astString[id].vString;
    }

    if ( 10000 <= id && (id - 10000) < m_iPatchStringCount )
    {
        pcResult = m_astPatchString[id - 10000].vString;
    }

    if ( 20000 <= id && (id - 20000) < m_iExpansionsStringCount )
    {
        pcResult = m_astExpansionsString[id - 20000].vString;
    }

    if ( pcResult && !strcmp("DescBlank", pcResult) )
    {
        printf("\r\n======%d======\r\n", id);
    }

    if ( NULL != pcResult && NULL != pcFilter && !strcmp(pcResult, pcFilter) )
    {
        return NULL;
    }

    return pcResult;
}

char *String_FindString_2(unsigned int id, char* pcFilter, char* pcFilter2)
{
    char *pcResult = NULL;

    if ( 0xFFFF <= id  )
    {
        return NULL;
    }

    if ( id < m_iStringCount )
    {
        pcResult = m_astString[id].vString;
    }

    if ( 10000 <= id && (id - 10000) < m_iPatchStringCount )
    {
        pcResult = m_astPatchString[id - 10000].vString;
    }

    if ( 20000 <= id && (id - 20000) < m_iExpansionsStringCount )
    {
        pcResult = m_astExpansionsString[id - 20000].vString;
    }

    if ( NULL != pcResult && NULL != pcFilter && !strcmp(pcResult, pcFilter) )
    {
        return NULL;
    }

    if ( NULL != pcResult && NULL != pcFilter2 && !strcmp(pcResult, pcFilter2) )
    {
        return NULL;
    }

    return pcResult;
}

