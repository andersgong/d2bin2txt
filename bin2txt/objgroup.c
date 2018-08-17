#include "global.h"

#define FILE_PREFIX "objgroup"
#define NAME_PREFIX "og"

/*
Title 	ObjGroup.txt
Description 	by Nefarius
Sent by 	
GroupName: A reference field for internal use, so you know what kind of objects this line will spawn.

Offset: The unique ID number of this group, this is the number you would use in Levels.txt to assign this object group to a level.

ID0 to ID7: This column contains the unique ID numbers of the objects assigned to this object group.

DENSITY0 to DENSITY7: How densly will the level be filled with this object, this works similar to MonDen, however the density of objects is influenced by the objects PopulateFn in Objects.txt to a much higher degree. This column cannot exceed 125, 
higher values make the game to crash.

PROB0 to PROB7: The chance that this object will be picked, this does not use the regular rarity/total_rarity, no: this works on a direct basis, the value entered in this field is the actual chance this object will be spawned. As a result of this the 
game will not spawn other objects from the group if one of them is set to 100, all in all, the total of these columns must not exceed 100 (it should actually equal 100 for best results, but no single object should have 100, it is best to divide 100 by 
number of objects and use that value in this field).

SHRINES: Whenever to use shrine-logic when spawning this object group in a level, note the object must not have DensityX assigned, it also needs to use the proper PopulateFn for this to work.

WELLS: Whenever to use well-logic when spawning this object group in a level, note the object must not have DensityX assigned, it also needs to use the proper PopulateFn for this to work.

*/

typedef struct
{
    unsigned int vID0;
    unsigned int vID1;
    unsigned int vID2;
    unsigned int vID3;
    unsigned int vID4;
    unsigned int vID5;
    unsigned int vID6;
    unsigned int vID7;

    unsigned char vDENSITY0;
    unsigned char vDENSITY1;
    unsigned char vDENSITY2;
    unsigned char vDENSITY3;

    unsigned char vDENSITY4;
    unsigned char vDENSITY5;
    unsigned char vDENSITY6;
    unsigned char vDENSITY7;

    unsigned char vPROB0;
    unsigned char vPROB1;
    unsigned char vPROB2;
    unsigned char vPROB3;

    unsigned char vPROB4;
    unsigned char vPROB5;
    unsigned char vPROB6;
    unsigned char vPROB7;

    unsigned char vSHRINES;
    unsigned char vWELLS;
    unsigned short iPadding12;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "GroupName",
    "Offset",
    NULL,
};

static unsigned int m_iObjGroupCount = 0;

static int ObjGroup_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    int result = 0;

    if ( !strcmp("Offset", acKey) )
    {
#ifdef USE_TEMPLATE
        if ( 0 == pcTemplate[0] )
#endif
        {
            sprintf(acOutput, "%u", m_iObjGroupCount);
            result = 1;
        }

        m_iObjGroupCount++;
    }
    else if ( !strcmp("GroupName", acKey) )
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

        result = 1;
    }

    return result;
}

int process_objgroup(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ID0, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ID1, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ID2, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ID3, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ID4, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ID5, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ID6, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, ID7, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DENSITY0, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DENSITY1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DENSITY2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DENSITY3, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DENSITY4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DENSITY5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DENSITY6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DENSITY7, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PROB0, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PROB1, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PROB2, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PROB3, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PROB4, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PROB5, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PROB6, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, PROB7, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, SHRINES, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, WELLS, UCHAR);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_stCallback.pfnFieldProc = ObjGroup_FieldProc;
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

