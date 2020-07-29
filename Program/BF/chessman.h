#ifndef CHESSMAN_H
#define CHESSMAN_H

#include "qpainter.h"

enum CHESSMAN_COLOR{
    COLOR_RED = 0,	//红方
    COLOR_BLUE,		//蓝方
};

enum CHESSMAN_STATE
{
    DIE = 0,
    LIVE,
};

class Chessman
{
public:
    Chessman();
    Chessman(int chessmanTopoid,QPoint chessmanCoord,CHESSMAN_COLOR chessmanColor,CHESSMAN_STATE chessmanState);

    void init(int chessmanTopoid, QPoint chessmanCoord, CHESSMAN_COLOR chessmanColor,CHESSMAN_STATE chessmanState)
    {
        m_chessmanTopoid = chessmanTopoid;
        m_chessmanCoord = chessmanCoord;
        m_chessmanColor = chessmanColor;
        m_chessmanState = chessmanState;

    }
    void change(QPoint chessmanTopoid)
    {
        m_chessmanCoord = chessmanTopoid;
    }

public:
    CHESSMAN_COLOR m_chessmanColor;	//红方蓝方
    QPoint m_chessmanCoord;			//位置
    int m_chessmanTopoid;   //棋子的拓扑ID
    CHESSMAN_STATE m_chessmanState;    //是否选中
};

#endif // CHESSMAN_H
