#include "global.h"

#define FILE_PREFIX "monsounds"
#define NAME_PREFIX "mo"

/*
Title 	MonSounds.txt
Description 	by Nefarius
Sent by 	
This used to reside in a table that was located in the data section of D2Client.dll before 1.10.

Id: this column represents the ID pointer you'd use in MonStats.txt to link this sound-index to a monster, read the file guide for that file for more information.

Attack1 and Attack2: the ID pointer of the sound to play for melee attack1 and melee attack2 (respectively), this is an ID pointer from Sounds.txt. This is played when the monster starts attacking.

Weapon1 and Weapon2: this is the ID pointer to another sound, this sound is used by Blizzard for monsters that wield a weapon, it can be used for any monster though.

Att1Del and Att2Del: number of frames to wait (after starting the attack) before playing the sound.

Wea1Del and Wea2Del: number of frames to wait before playing the weapon sound.

Att1Prb and Att2Prb: chance to play the attack sound (not the weapon sound), this is quite obviously x out of 100 icon_wink.gif.

Wea1Vol and Wea2Vol: sets the volume for the weapon sound to something other then what the sound has defined in Sounds.txt, 255 is full volume, 0 would mute the sound.

HitSound: The ID pointer of the sound to play when the monster takes a hit (it doesn't have to get into GH mode for this to play).

DeathSound: The ID pointer of the sound to play when the monster dies.

HitDelay: Time to wait (in frames) before playing the hit-sound, after the monster gets hit.

DeathDelay: Time to wait (in frames) before playing the death sound.

Skill1 to Skill4: Sound to play when the monster enters S1, S2, S3 or S4 modes. This does _not_ refer to the skill columns in monstats.

Footstep: An ID pointer to a sound that is played each loop of the WL animation.

FootstepLayer: This is an additional sound to play when the monster is in the WL animation mode, like the above.

FsCnt: Number of times to play the footstep sound, for a monster with two legs you'd set this to 2 quite obviously.

FsOff: Could be related to the delay in frames between playing the individual footsteps.

FsPrb: Chance to play the footstep sound. Again, x out of 100.

Neutral: An ID pointer to a sound that is played when the monster is neutral (actually, it's played even if the monster isn't in NU mode, see next column for details).

NeuTime: Delay in frames between playing the Neutral sound.

Init: An ID pointer to sounds that should start playing the moment the monster is initialized (AI related I guess), this is mainly used for looping sounds.

Taunt: An ID pointer to the sound that is played when you encounter the monster, which naturally means, the speech of bosses and the like.

Flee: An ID pointer to a sound that is played when the monster retreats, originally, all monsters were meant to escape when they were low on HP, but Blizzard changed this during the alpha of the game, back then this was probably a lot more significant, 
right now it's only used by fallen.

CvtMo1 to CvtMo3: This is related to sounds that are played when certain skills or sequences are used, this contains the initial animation, like WL for the charge skill.

CvtSk1 to CSkMo3: This is like the above, it contains the ID pointer to the skill in question.

CvtTgt1 to CvtTgt3: This is related to sounds that are played when certain skills or sequences are used, this contains the end-animation of the sequence, like A2 for the charge skill.

*/

typedef struct
{
    unsigned int iPadding0;

    unsigned int vAttack1;    //sounds

    unsigned int vAtt1Del;
    unsigned int vAtt1Prb;
    unsigned int vWeapon1;    //sounds
    unsigned int vWea1Del;
    unsigned int vWea1Vol;

    unsigned int vAttack2;    //sounds

    unsigned int vAtt2Del;
    unsigned int vAtt2Prb;
    unsigned int vWeapon2;
    unsigned int vWea2Del;
    unsigned int vWea2Vol;

    unsigned int vHitSound; //sounds

    unsigned int vHitDelay;

    unsigned int vDeathSound;
    unsigned int vDeaDelay;

    unsigned int vSkill1;   //sounds
    unsigned int vSkill2;   //sounds
    unsigned int vSkill3;   //sounds
    unsigned int vSkill4;   //sounds

    unsigned int vFootstep; //sounds
    unsigned int vFootstepLayer;    //sounds

    unsigned int vFsCnt;
    unsigned int vFsOff;
    unsigned int vFsPrb;
    unsigned int vNeutral;  //sounds
    unsigned int vNeuTime;

    unsigned int vInit; //sounds
    unsigned int vTaunt;    //sounds

    unsigned int vFlee; //sounds

    unsigned char vCvtMo1;  //monmode
    unsigned char vCvtTgt1;  //monmode
    unsigned char iPadding31[2];

    unsigned int vCvtSk1;   //skills

    unsigned char vCvtMo2;  //monmode
    unsigned char vCvtTgt2;  //monmode
    unsigned char iPadding33[2];

    unsigned int vCvtSk2;   //skills

    unsigned char vCvtMo3;  //monmode
    unsigned char vCvtTgt3;  //monmode
    unsigned char iPadding35[2];

    unsigned int vCvtSk3;   //skills
} ST_LINE_INFO;

typedef struct
{
    unsigned char vId[32];
} ST_MONSOUND;

static char *m_apcInternalProcess[] = 
{
    "Id",
    "EOL",
    NULL,
};

static unsigned int m_iMonSoundsCount = 0;
static ST_MONSOUND *m_astMonSounds = NULL;

MODULE_SETLINES_FUNC(FILE_PREFIX, m_astMonSounds, ST_MONSOUND);

char *MonSounds_GetItemSoundsCode(unsigned int id)
{
    if ( id < m_iMonSoundsCount )
    {
        return m_astMonSounds[id].vId;
    }

    return NULL;
}

static int MonSounds_FieldProc_Pre(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "Id") )
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

        strncpy(m_astMonSounds[m_iMonSoundsCount].vId, acOutput, sizeof(m_astMonSounds[m_iMonSoundsCount].vId));
        String_Trim(m_astMonSounds[m_iMonSoundsCount].vId);
        m_iMonSoundsCount++;
        return 1;
    }
    else if ( !strcmp(acKey, "EOL") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static int MonSounds_FieldProc(void *pvLineInfo, char *acKey, unsigned int iLineNo, char *pcTemplate, char *acOutput)
{
    if ( !strcmp(acKey, "Id") )
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
    else if ( !strcmp(acKey, "EOL") )
    {
        acOutput[0] = '0';
        acOutput[1] = 0;

        return 1;
    }

    return 0;
}

static int MonSounds_ConvertValue(void *pvLineInfo, char *acKey, char *pcTemplate, char *acOutput)
{
    ST_LINE_INFO *pstLineInfo = pvLineInfo;
    char *pcResult;
    int result = 0;

    if ( !strcmp(acKey, "Attack1") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vAttack1);
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
    else if ( !strcmp(acKey, "Weapon1") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vWeapon1);
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
    else if ( !strcmp(acKey, "Attack2") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vAttack2);
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
    else if ( !strcmp(acKey, "Weapon2") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vWeapon2);
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
    else if ( !strcmp(acKey, "HitSound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vHitSound);
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
    else if ( !strcmp(acKey, "DeathSound") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vDeathSound);
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
    else if ( !strcmp(acKey, "Skill1") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vSkill1);
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
    else if ( !strcmp(acKey, "Skill2") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vSkill2);
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
    else if ( !strcmp(acKey, "Skill3") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vSkill3);
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
    else if ( !strcmp(acKey, "Skill4") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vSkill4);
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
    else if ( !strcmp(acKey, "Footstep") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vFootstep);
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
    else if ( !strcmp(acKey, "FootstepLayer") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vFootstepLayer);
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
    else if ( !strcmp(acKey, "Neutral") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vNeutral);
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
    else if ( !strcmp(acKey, "Init") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vInit);
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
    else if ( !strcmp(acKey, "Taunt") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vTaunt);
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
    else if ( !strcmp(acKey, "Flee") )
    {
        pcResult = Sounds_GetSoundName(pstLineInfo->vFlee);
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
    else if ( !strcmp(acKey, "CvtMo1") )
    {
        pcResult = MonMode_GetCode(pstLineInfo->vCvtMo1);
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
    else if ( !strcmp(acKey, "CvtTgt1") )
    {
        pcResult = MonMode_GetCode(pstLineInfo->vCvtTgt1);
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
    else if ( !strcmp(acKey, "CvtMo2") )
    {
        pcResult = MonMode_GetCode(pstLineInfo->vCvtMo2);
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
    else if ( !strcmp(acKey, "CvtTgt2") )
    {
        pcResult = MonMode_GetCode(pstLineInfo->vCvtTgt2);
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
    else if ( !strcmp(acKey, "CvtMo3") )
    {
        pcResult = MonMode_GetCode(pstLineInfo->vCvtMo3);
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
    else if ( !strcmp(acKey, "CvtTgt3") )
    {
        pcResult = MonMode_GetCode(pstLineInfo->vCvtTgt3);
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
    else if ( !strcmp(acKey, "CvtSk1") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vCvtSk1);
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
    else if ( !strcmp(acKey, "CvtSk2") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vCvtSk2);
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
    else if ( !strcmp(acKey, "CvtSk3") )
    {
        pcResult = Skills_GetSkillName(pstLineInfo->vCvtSk3);
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

int process_monsounds(char *acTemplatePath, char *acBinPath, char *acTxtPath, ENUM_MODULE_PHASE enPhase)
{
    ST_LINE_INFO *pstLineInfo = (ST_LINE_INFO *)m_acLineInfoBuf;

    ST_VALUE_MAP *pstValueMap = (ST_VALUE_MAP *)m_acValueMapBuf;

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Attack1, USHORT);    //sounds
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Weapon1, USHORT);    //sounds

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Att1Del, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Att1Prb, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Wea1Del, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Wea1Vol, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Attack2, USHORT);    //sounds
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Weapon2, USHORT);    //sounds

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Att2Del, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Att2Prb, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Wea2Del, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Wea2Vol, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitSound, UINT); //sounds

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, HitDelay, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DeathSound, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, DeaDelay, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill1, UINT);   //sounds
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill2, UINT);   //sounds
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill3, UINT);   //sounds
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Skill4, UINT);   //sounds

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Footstep, UINT);  //sounds
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FootstepLayer, UINT);    //sounds

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FsCnt, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FsOff, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, FsPrb, UINT);
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Neutral, UINT);  //sounds
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, NeuTime, UINT);

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Init, UINT); //sounds
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Taunt, UINT);    //sounds

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, Flee, UINT); //sounds

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CvtMo1, UCHAR);  //monmode
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CvtTgt1, UCHAR);  //monmode

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CvtSk1, UINT);   //skills

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CvtMo2, UCHAR);  //monmode
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CvtTgt2, UCHAR);  //monmode

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CvtSk2, UINT);   //skills

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CvtMo3, UCHAR);  //monmode
    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CvtTgt3, UCHAR);  //monmode

    VALUE_MAP_DEFINE(pstValueMap, pstLineInfo, CvtSk3, UINT);   //skills

    switch ( enPhase )
    {
        case EN_MODULE_SELF_DEPEND:
            m_iMonSoundsCount = 0;

            m_stCallback.pfnFieldProc = MonSounds_FieldProc_Pre;
            m_stCallback.pfnSetLines = SETLINES_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnFinished = FINISHED_FUNC_NAME(FILE_PREFIX);
            m_stCallback.pfnConvertValue = MonSounds_ConvertValue;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        case EN_MODULE_OTHER_DEPEND:
            MODULE_DEPEND_CALL(sounds, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(monmode, acTemplatePath, acBinPath, acTxtPath);
            MODULE_DEPEND_CALL(skills, acTemplatePath, acBinPath, acTxtPath);
            break;

        case EN_MODULE_RESERVED_1:
        case EN_MODULE_RESERVED_2:
            break;

        case EN_MODULE_INIT:
            m_stCallback.pfnFieldProc = MonSounds_FieldProc;
            m_stCallback.pfnConvertValue = MonSounds_ConvertValue;
            m_stCallback.ppcKeyInternalProcess = m_apcInternalProcess;

            return process_file(acTemplatePath, acBinPath, acTxtPath, FILE_PREFIX, pstLineInfo, sizeof(*pstLineInfo), 
                pstValueMap, Global_GetValueMapCount(), &m_stCallback);
            break;

        default:
            break;
    }

    return 1;
}

