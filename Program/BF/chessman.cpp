#include "chessman.h"

Chessman::Chessman()
{

}

Chessman::Chessman(int chessmanTopoid,QPoint chessmanCoord,CHESSMAN_COLOR chessmanColor,CHESSMAN_STATE chessmanState)
{
    m_chessmanTopoid = chessmanTopoid;
    m_chessmanColor = chessmanColor;
    m_chessmanCoord = chessmanCoord;
    m_chessmanState = chessmanState;
}
