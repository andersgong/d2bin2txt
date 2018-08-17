#include "global.h"

#define FILE_PREFIX "sounds"
#define NAME_PREFIX "so"

/*
A.sound = 描述性字段。
B.index = 记录ID,使用于其他txt文件。如Levels.txt,SoundEnviron.txt。
C.filename = 解释栏。该声音文件在mpq文件里面的文件名，注意Act1-4的路径为data\global\music\act*\***.wav,在d2music.mpq内;Act5的路径为data\global\music\act5\***.wav,在d2xmusic.wav内。替换或增加声音文件时注意路径。另外，改变文件名无效。(见附录)
D.volume = 解释栏。音量控制，取值0-255；是否起作用取决于music vol栏值，见下。
E.group size = 当音乐文件有多个时(一组),随机播放。有点类似于随机地图。当一组只有一个时,值为0,其他的在该组的第一个文件的该栏填入文件个数,其他取值为0。也就是说只有一个音乐组的第一个文件\值不为0。(我好罗嗦!)
F.loop = 是否循环播放。1=循环播放，0=播放一次。
G/H.fade in/fade out = 音乐淡入或淡出所经历的时间，即声音从消失到指定音量所需要的时间。
I.defer inst = 未知
J.stop inst = 未知
K.duration = 播放时间。意义不清楚,似乎除了几个有关白天和晚上的的声音外,如Act2和Act3(在ID为171和189的声音文件附近),其他均取值0。
L.compound = 控制同时播放的声音数量??不清楚。
M.reverb = 0/1控制是否增加回音效果到声音。
N.falloff = 取值0-4，控制声音随距离减弱的快慢。
O.cache = 0/1控制是否经常在缓存中播放。
P.async only = 0/1控制是否跳过播放不重要的声音如果装载不及时。
Q.priority = 取值0-255，控制声音的变弱次序如果同时有多个音乐播放。换句话说就是控制播放的优先级。
R.stream = 0/1控制声音是否边装载边播放，否则先装载再播放;只对音乐文件有效。
S.stereo = 布尔值，控制立体声，只对音乐文件有效。注意:16bits(位)wav格式，采样率22,050Hz。
T.tracking = 0/1控制声音是否随所依附的音乐组移动,如果组的声音文件数>=2则取值1。
U.solo = 0/1控制该声音文件是否单独播放。
V.music vol = 0/1控制是否使用volume栏的音量值。
W.block 1 = 循环音乐在声音文件中的偏移量。
X.block 2 = 同上。
Y.block 3 = 同上。
*/

typedef struct
{
    unsigned short vIndex;
} ST_LINE_INFO;

static char *m_apcInternalProcess[] =
{
    "Sound",
    NULL,
};

static char *m_apcNotUsed[] =
{
    "FileName",
    "Volume",
    "Group Size",
    "Loop",
    "Fade In",
    "Fade Out",
    "Defer Inst",
    "Stop Inst",
    "Duration",
    "Compound",
    "Reverb",
    "Falloff",
    "Cache",
    "Async Only",
    "Priority",
    "Stream",
    "Stereo",
    "Tracking",
    "Solo",
    "Music Vol",
    "Block 1",
    "Block 2",
    "Block 3",
    NULL,
};

typedef struct
{
    char vSound[64];
} ST_ITEM_SOUNDS;

static unsigned int m_iItemSoundsCount = 0;
static ST_ITEM_SOUNDS *m_astItemSounds = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astItemSounds, ST_ITEM_SOUNDS);

static int Sounds_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    if ( !strcmp(acKey, "Sound") )
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

        strncpy(m_astItemSounds[pstLineInfo->vIndex].vSound, acOutput, sizeof(m_astItemSounds[pstLineInfo->vIndex].vSound));
        m_iItemSoundsCount++;
        return 1;
    }

    return 0;
}

static char *Sounds_GetKey(void *pvLineInfo, char *pcKey, unsigned int *iKeyLen)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;

    memset(pcKey, 0, sizeof(pcKey));
    sprintf(pcKey, "%u", pstLineInfo->vIndex);
    *iKeyLen = (unsigned int)strlen(pcKey);

    return pcKey;
}

static int process_sounds_x(char *acTemplatePath, char *acBinPath, char *acTxtPath)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Index, USHORT);

    m_iItemSoundsCount = 0;

    //m_stCallback.pfnGetKey = Sounds_GetKey;
    m_stCallback.pfnFieldProc = Sounds_FieldProc;
    m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
    m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
    m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;
    m_stCallback.ppcKeyNotUsed = m_apcNotUsed;

    File_CopyFile(acTemplatePath, acTxtPath, "SoundEnviron", ".txt");

    return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
        pstValueMap, Global_GetValueMapCount(), &m_stCallback);
}

int process_sounds(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            return process_sounds_x(acTemplatePath, acBinPath, acTxtPath);
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

char *Sounds_GetSoundName(unsigned int id)
{
    if ( id >= m_iItemSoundsCount )
    {
        return NULL;
    }

    return m_astItemSounds[id].vSound;
}

