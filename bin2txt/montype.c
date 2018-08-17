#include "global.h"

#define FILE_PREFIX "montype"
#define NAME_PREFIX "mt"

/*
Type: This is the ID-pointer that is used to link this MonType to a monster in MonStats.txt.

Equiv1, Equiv2 and Equiv3: This works exactly like the equiv (for equivalent) columns in ItemTypes.txt. This works in a quite simple but very powerful way, for example the UndeadFetish MonType is linked to both LowUndead and Demon MonTypes, LowUndead is 
linked to the Undead MonType. So in the eyes of the game, a monster with UndeadFetish assigned to it, is all of these four MonTypes.

StrSing: String key for the string displayed for the singular form (Skeleton), note that this is unused, since the only modifier display code that accesses MonType uses StrPlur.

StrPlur: This is the string key for the plural form of this monsters type (Skeletons), this is used by Damage vs. MonType and Attack Rating vs. MonType modifiers. Beware, the display of these modifiers is bugged because blizzard checks the record count 
for the wrong txt file when it fetches the string, to make them show up you have to add dummy entries to monprop.txt (this file needs to have the same or more entries then montype), it is not in anyway or form related to the last line in the file or to 
the CPU type.

*EOL: End of Line, this is needed to prevent M$-Excel from screwing up the file.


Where are MonTypes used?
Not in many places unfortunately, they are used at present for Modifier Exclusion on bosses (MonUMod.txt), this will let you prevent certain monster types from spawning with specific modifiers (Sand Leapers don't get Lightning Enchanted for example). 
The other place is the dmg-mon and att-mon properties.

*/

typedef struct
{
    unsigned short iPadding0;
    unsigned short vequiv1;

    unsigned short vequiv2;
    unsigned short vequiv3;

    unsigned short vstrsing;
    unsigned short vstrplur;
} ST_LINE_INFO;

typedef struct
{
    unsigned char vtype[32];
} ST_MONTYPE;

static char *m_apcInternalProcess[] =
{
    "type",
    "*eol",
    NULL,
};

static unsigned int m_iMonTypeCount = 0;
static ST_MONTYPE *m_astMonType = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astMonType, ST_MONTYPE);

char *MonType_GetType(unsigned int id)
{
    if ( id < m_iMonTypeCount )
    {
        return m_astMonType[id].vtype;
    }

    return NULL;
}

static int MonType_FieldProc_Pre(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "type") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else if ( 0 < iLineNo )
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, iLineNo);
        }
        else
        {
            acOutput[0] = 0;
        }
#else
        sprintf(acOutput, "%s%u", NAME_PREFIX, iLineNo);
#endif

        strncpy(m_astMonType[m_iMonTypeCount].vtype, acOutput, sizeof(m_astMonType[m_iMonTypeCount].vtype));
        String_Trim(m_astMonType[m_iMonTypeCount].vtype);
        m_iMonTypeCount++;

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

static int MonType_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "type") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else if ( 0 < iLineNo )
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, iLineNo);
        }
        else
        {
            acOutput[0] = 0;
        }
#else
        sprintf(acOutput, "%s%u", NAME_PREFIX, iLineNo);
#endif

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

static int MonType_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "equiv1") )
    {
        pcResult = MonType_GetType(pstLineInfo->vequiv1);
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
    else if ( !strcmp(acKey, "equiv2") )
    {
        pcResult = MonType_GetType(pstLineInfo->vequiv2);
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
    else if ( !strcmp(acKey, "equiv3") )
    {
        pcResult = MonType_GetType(pstLineInfo->vequiv3);
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
    else if ( !strcmp(acKey, "strsing") )
    {
        pcResult = String_FindString(pstLineInfo->vstrsing, "dummy");
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
    else if ( !strcmp(acKey, "strplur") )
    {
        pcResult = String_FindString(pstLineInfo->vstrplur, "dummy");
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

int process_montype(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, equiv1, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, equiv2, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, equiv3, USHORT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, strsing, USHORT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, strplur, USHORT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iMonTypeCount = 0;

            m_stCallback.pfnFieldProc = MonType_FieldProc_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(string, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(montype, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            File_CopyFile(acTemplatePath, acTxtPath, "monname", ".txt");

            m_stCallback.pfnConvertValue = MonType_ConvertValue;
            m_stCallback.pfnFieldProc = MonType_FieldProc;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

