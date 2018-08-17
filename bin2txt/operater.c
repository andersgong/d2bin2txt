#include "global.h"

typedef struct
{
    unsigned int uiLevel;
    ENUM_OPERATER_LEFTRIGHT enLeftRight;
    ENUM_OPERATER_ARGNUM enArgNum;
    unsigned char *pcOperater;
} ST_OPERATER;

static ST_OPERATER m_astOperater[EN_OPERATER_MAX];

void Operater_Init()
{
    unsigned int i;

    for ( i = 0; i < EN_OPERATER_MAX; i++ )
    {
        m_astOperater[i].uiLevel = MAX_OPERATER_LEVEL;
        m_astOperater[i].enArgNum = EN_OPERATER_ARG_1;
        m_astOperater[i].enLeftRight = EN_OPERATER_LEFT;
        m_astOperater[i].pcOperater = NULL;
    }

    m_astOperater[EN_OPERATER_BRACKET_1].uiLevel = 50;
    m_astOperater[EN_OPERATER_BRACKET_1].pcOperater = "(";
    m_astOperater[EN_OPERATER_BRACKET_1].enArgNum = EN_OPERATER_ARG_1;

    m_astOperater[EN_OPERATER_SMALL].uiLevel = 6;
    m_astOperater[EN_OPERATER_SMALL].pcOperater = "<";
    m_astOperater[EN_OPERATER_SMALL].enArgNum = EN_OPERATER_ARG_2;

    m_astOperater[EN_OPERATER_BIG].uiLevel = 6;
    m_astOperater[EN_OPERATER_BIG].pcOperater = ">";
    m_astOperater[EN_OPERATER_BIG].enArgNum = EN_OPERATER_ARG_2;

    m_astOperater[EN_OPERATER_SMALLEQUAL].uiLevel = 6;
    m_astOperater[EN_OPERATER_SMALLEQUAL].pcOperater = "<=";
    m_astOperater[EN_OPERATER_SMALLEQUAL].enArgNum = EN_OPERATER_ARG_2;

    m_astOperater[EN_OPERATER_BIGEQUAL].uiLevel = 6;
    m_astOperater[EN_OPERATER_BIGEQUAL].pcOperater = ">=";
    m_astOperater[EN_OPERATER_BIGEQUAL].enArgNum = EN_OPERATER_ARG_2;

    m_astOperater[EN_OPERATER_EQUAL].uiLevel = 7;
    m_astOperater[EN_OPERATER_EQUAL].pcOperater = "==";
    m_astOperater[EN_OPERATER_EQUAL].enArgNum = EN_OPERATER_ARG_2;

    m_astOperater[EN_OPERATER_NOTEQUAL].uiLevel = 7;
    m_astOperater[EN_OPERATER_NOTEQUAL].pcOperater = "!=";
    m_astOperater[EN_OPERATER_NOTEQUAL].enArgNum = EN_OPERATER_ARG_2;

    m_astOperater[EN_OPERATER_ADD].uiLevel = 4;
    m_astOperater[EN_OPERATER_ADD].pcOperater = "+";
    m_astOperater[EN_OPERATER_ADD].enArgNum = EN_OPERATER_ARG_2;

    m_astOperater[EN_OPERATER_SUB].uiLevel = 4;
    m_astOperater[EN_OPERATER_SUB].pcOperater = "-";
    m_astOperater[EN_OPERATER_SUB].enArgNum = EN_OPERATER_ARG_2;

    m_astOperater[EN_OPERATER_MULTI].uiLevel = 3;
    m_astOperater[EN_OPERATER_MULTI].pcOperater = "*";
    m_astOperater[EN_OPERATER_MULTI].enArgNum = EN_OPERATER_ARG_2;

    m_astOperater[EN_OPERATER_DIVIDE].uiLevel = 3;
    m_astOperater[EN_OPERATER_DIVIDE].pcOperater = "/";
    m_astOperater[EN_OPERATER_DIVIDE].enArgNum = EN_OPERATER_ARG_2;

    m_astOperater[EN_OPERATER_XOR].uiLevel = 9;
    m_astOperater[EN_OPERATER_XOR].pcOperater = "^";
    m_astOperater[EN_OPERATER_XOR].enArgNum = EN_OPERATER_ARG_2;

    m_astOperater[EN_OPERATER_INVERSION].uiLevel = 2;
    m_astOperater[EN_OPERATER_INVERSION].pcOperater = "-";
    m_astOperater[EN_OPERATER_INVERSION].enArgNum = EN_OPERATER_ARG_1;
    m_astOperater[EN_OPERATER_INVERSION].enLeftRight = EN_OPERATER_RIGHT;

    m_astOperater[EN_OPERATER_CONDITION].uiLevel = 13;
    m_astOperater[EN_OPERATER_CONDITION].pcOperater = "?:";
    m_astOperater[EN_OPERATER_CONDITION].enArgNum = EN_OPERATER_ARG_3;
    m_astOperater[EN_OPERATER_CONDITION].enLeftRight = EN_OPERATER_RIGHT;
}

unsigned char *Operater_GetOpStr(ENUM_OPERATER_TYPE enOpType)
{
    if ( enOpType >= EN_OPERATER_MAX )
    {
        return NULL;
    }

    return m_astOperater[enOpType].pcOperater;
}

unsigned int Operater_GetOpLevel(ENUM_OPERATER_TYPE enOpType)
{
    if ( enOpType >= EN_OPERATER_MAX )
    {
        return MAX_OPERATER_LEVEL;
    }

    return m_astOperater[enOpType].uiLevel;
}

ENUM_OPERATER_LEFTRIGHT Operater_GetLeftRight(ENUM_OPERATER_TYPE enOpType)
{
    if ( enOpType >= EN_OPERATER_MAX )
    {
        return EN_OPERATER_LEFT;
    }

    return m_astOperater[enOpType].enLeftRight;
}

ENUM_OPERATER_ARGNUM Operater_GetArgNum(ENUM_OPERATER_TYPE enOpType)
{
    if ( enOpType >= EN_OPERATER_MAX )
    {
        return EN_OPERATER_ARG_2;
    }

    return m_astOperater[enOpType].enArgNum;
}

