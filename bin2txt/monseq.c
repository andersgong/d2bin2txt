#include "global.h"

#define FILE_PREFIX "monseq"
#define NAME_PREFIX "mq"

/*
Title 	MonSeq.txt
Description 	by Nefarius
Sent by 	
MonSeq.txt is a softcoded monster sequence table (the character sequences remain hardcoded), each line herein represents one frame of the sequence, a sequence can have 0xFF lines and the file can hold 0xFF individual sequences. The ID of the sequence (
the first column) is used to group the lines together to a single record.

sequence: The ID of this sequence when used inside the sequence columns of MonStats.txt, this is also what is used to group the various frames associated with this sequence together.

mode: The animation mode to use for this frame of the sequence (this is an ID pointer from MonMode.txt).

frame: The frame from the associated animation mode that will be used for this frame of the sequence, so if you use A1 as the mode, and use 12 as the frame for your first like, then the monster will use frame 12 as the first frame of the animation, 
rather then frame 0.

dir: What direction will the above frame be taken from, most animations have 8 directions.

0 = south west
1 = north west
2 = north east
3 = south east
4 = south
5 = west
6 = north
7 = east

event: What event will this frame trigger.

0 = No event
1 = Melee attack (missiles are only released client-side)
2 = Missile attack (melee attacks will deal no damage)
3 = Play a sound
4 = Launch a spell

eol: End of line, this field prevents M$ Excel from messing up the file, if you fill the empty cells of the previous column with 0 this is not needed.

*/

typedef struct
{
    unsigned short iPadding0;
    unsigned char vmode;   //monmode
    unsigned char vframe;

    unsigned char vdir;
    unsigned char vevent;
} ST_LINE_INFO;

typedef struct
{
    unsigned char vsequence[32];
} ST_MONSEQ;

static char *m_apcInternalProcess[] =
{
    "sequence",
    "eol",
    NULL,
};

static unsigned int m_iMonSeqCount = 0;
static ST_MONSEQ *m_astMonSeq = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astMonSeq, ST_MONSEQ);

static int MonSeq_FieldProc_Pre(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    unsigned int i;

    if ( !strcmp(acKey, "sequence") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else if ( 0 < iLineNo )
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->iPadding0);
        }
        else
        {
            acOutput[0] = 0;
        }
#else
        sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->iPadding0);
#endif

        for ( i = 0; i < m_iMonSeqCount; i++ )
        {
            if ( !strcmp(acOutput, m_astMonSeq[i].vsequence) )
            {
                return 1;
            }
        }

        strncpy(m_astMonSeq[m_iMonSeqCount].vsequence, acOutput, sizeof(m_astMonSeq[m_iMonSeqCount].vsequence));
        m_iMonSeqCount++;
        return 1;
    }
    else if ( !strcmp(acKey, "eol") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static int MonSeq_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "sequence") )
    {
#ifdef USE_TEMPLATE
        if ( 0 != pcTemplate[0] )
        {
            strcpy(acOutput, pcTemplate);
        }
        else if ( 0 < iLineNo )
        {
            sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->iPadding0);
        }
        else
        {
            acOutput[0] = 0;
        }
#else
        sprintf(acOutput, "%s%u", NAME_PREFIX, pstLineInfo->iPadding0);
#endif
        return 1;
    }
    else if ( !strcmp(acKey, "eol") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

char *MonSeq_GetSequence(unsigned int id)
{
    if ( id < m_iMonSeqCount )
    {
        return m_astMonSeq[id].vsequence;
    }

    return NULL;
}

static int MonSeq_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "mode") )
    {
        pcResult = MonMode_GetCode(pstLineInfo->vmode);
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

int process_monseq(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, mode, UCHAR);   //monmode
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, frame, UCHAR);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, dir, UCHAR);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, event, UCHAR);

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iMonSeqCount = 0;

            m_stCallback.pfnFieldProc = MonSeq_FieldProc_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(monmode, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnConvertValue = MonSeq_ConvertValue;
            m_stCallback.pfnFieldProc = MonSeq_FieldProc;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

