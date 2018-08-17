#include "global.h"

#define FILE_PREFIX "belts"
#define NAME_PREFIX "bl"

typedef struct
{
    unsigned int vId;

    unsigned int vnumboxes;

    unsigned int vbox1left;
    unsigned int vbox1right;
    unsigned int vbox1top;
    unsigned int vbox1bottom;

    unsigned int vbox2left;
    unsigned int vbox2right;
    unsigned int vbox2top;
    unsigned int vbox2bottom;

    unsigned int vbox3left;
    unsigned int vbox3right;
    unsigned int vbox3top;
    unsigned int vbox3bottom;

    unsigned int vbox4left;
    unsigned int vbox4right;
    unsigned int vbox4top;
    unsigned int vbox4bottom;

    unsigned int vbox5left;
    unsigned int vbox5right;
    unsigned int vbox5top;
    unsigned int vbox5bottom;

    unsigned int vbox6left;
    unsigned int vbox6right;
    unsigned int vbox6top;
    unsigned int vbox6bottom;

    unsigned int vbox7left;
    unsigned int vbox7right;
    unsigned int vbox7top;
    unsigned int vbox7bottom;

    unsigned int vbox8left;
    unsigned int vbox8right;
    unsigned int vbox8top;
    unsigned int vbox8bottom;

    unsigned int vbox9left;
    unsigned int vbox9right;
    unsigned int vbox9top;
    unsigned int vbox9bottom;

    unsigned int vbox10left;
    unsigned int vbox10right;
    unsigned int vbox10top;
    unsigned int vbox10bottom;

    unsigned int vbox11left;
    unsigned int vbox11right;
    unsigned int vbox11top;
    unsigned int vbox11bottom;

    unsigned int vbox12left;
    unsigned int vbox12right;
    unsigned int vbox12top;
    unsigned int vbox12bottom;

    unsigned int vbox13left;
    unsigned int vbox13right;
    unsigned int vbox13top;
    unsigned int vbox13bottom;

    unsigned int vbox14left;
    unsigned int vbox14right;
    unsigned int vbox14top;
    unsigned int vbox14bottom;

    unsigned int vbox15left;
    unsigned int vbox15right;
    unsigned int vbox15top;
    unsigned int vbox15bottom;

    unsigned int vbox16left;
    unsigned int vbox16right;
    unsigned int vbox16top;
    unsigned int vbox16bottom;
} ST_LINE_INFO;

static char *m_apcNotUsed[] =
{
    "boxwidth",
    "boxheight",
    NULL,
};

static char *m_apcInternalProcess[] =
{
    "name",
    "*EOL",
    NULL,
};

static unsigned int m_uiBeltsCount = 0;

static int Belts_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
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
            sprintf(acOutput, "%s%u", NAME_PREFIX, m_uiBeltsCount);//pstLineInfo->vId);
            m_uiBeltsCount++;
        }

        return 1;
    }
    else if ( !strcmp(acKey, "*EOL") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

int process_belts(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, numboxes, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box1left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box1right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box1top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box1bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box2left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box2right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box2top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box2bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box3left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box3right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box3top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box3bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box4left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box4right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box4top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box4bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box5left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box5right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box5top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box5bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box6left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box6right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box6top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box6bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box7left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box7right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box7top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box7bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box8left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box8right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box8top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box8bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box9left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box9right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box9top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box9bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box10left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box10right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box10top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box10bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box11left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box11right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box11top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box11bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box12left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box12right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box12top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box12bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box13left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box13right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box13top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box13bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box14left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box14right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box14top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box14bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box15left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box15right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box15top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box15bottom, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box16left, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box16right, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box16top, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, box16bottom, UINT);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_uiBeltsCount = 0;

            m_stCallback.pfnFieldProc = Belts_FieldProc;
            m_stCallback.ppcKeyNotUsed = m_apcNotUsed;
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

