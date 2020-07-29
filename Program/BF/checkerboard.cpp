#include "checkerboard.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmessagebox.h"
#include "chessman.h"

#include <QPainter>
#include <QPalette>
#include <QString>
#include <QMouseEvent>
#include <QDebug>

Checkerboard::Checkerboard(QWidget *parent) : QWidget(parent)
{
//   setGeometry(100,100,600,800);
   this->resize(800,500);
   this->setMinimumSize(800, 500);
   this->setMaximumSize(800, 500);

   QPalette palette;
   palette.setBrush(QPalette::Background, QBrush(Qt::green));
   this->setPalette(palette);
    paint=new QPainter;
   //init
   chessRed={13,14,15,16};
   chessBlue = {1,2,3,4};

   playChessFlag = true;//红方先手，否子蓝方
   selectFlag = false;
   chessmanSelected = QPoint(0,0);
   TopoBoard={{1,{5,2}},{2,{1,6,3}},{3,{2,7,4}},{4,{3,8}},
              {5,{9,6,1}},{6,{5,10,7,2}},{7,{6,11,8,3}},{8,{7,12,4}},
              {9,{13,10,5}},{10,{9,14,11,6}},{11,{10,15,12,7}},{12,{11,16,8}},
              {13,{14,9,0}},{14,{13,15,10}},{15,{14,16,11}},{16,{15,12}}};
   TopoRow={{1,{1,2,3,4}},{2,{5,6,7,8}},{3,{9,10,11,12}},{4,{13,14,15,16}}};//行拓扑
   TopoColumn={{1,{1,5,9,13}},{2,{2,6,10,14}},{3,{3,7,11,15}},{4,{4,8,12,16}}};//列拓扑
   chessBoardCoord={{1,QPoint(100,400)},{2,QPoint(200,400)},{3,QPoint(300,400)},{4,QPoint(400,400)},
              {5,QPoint(100,300)},{6,QPoint(200,300)},{7,QPoint(300,300)},{8,QPoint(400,300)},
              {9,QPoint(100,200)},{10,QPoint(200,200)},{11,QPoint(300,200)},{12,QPoint(400,200)},
              {13,QPoint(100,100)},{14,QPoint(200,100)},{15,QPoint(300,100)},{16,QPoint(400,100)}};

}
Checkerboard::~Checkerboard()
{

}

//Chessman chessmanRed[4];
//Chessman chessmaBlue[4];

void paint_init()
{
    Chessman Chessman[8];
    //void init(int chessmanTopoid, QPoint chessmanCoord, CHESSMAN_COLOR chessmanColor,CHESSMAN_STATE chessmanState)
    Chessman[0].init(0,QPoint(400,400),COLOR_RED,LIVE);
    Chessman[1].init(0,QPoint(100,100),COLOR_RED,LIVE);
    Chessman[2].init(0,QPoint(200,100),COLOR_RED,LIVE);
    Chessman[3].init(0,QPoint(300,100),COLOR_RED,LIVE);
    Chessman[4].init(0,QPoint(400,100),COLOR_BLUE,LIVE);
    Chessman[5].init(0,QPoint(100,400),COLOR_BLUE,LIVE);
    Chessman[6].init(0,QPoint(200,400),COLOR_BLUE,LIVE);
    Chessman[7].init(0,QPoint(300,400),COLOR_BLUE,LIVE);

}

void Checkerboard::paintEvent(QPaintEvent *)
{
    int x=100,y=100;
    paint->begin(this);
    paint->setPen(QPen(Qt::black,4,Qt::SolidLine));
    paint->setBrush(QBrush(Qt::white,Qt::SolidPattern));
//画4条横线
    for(int i=0;i<4;i++)
    {
        paint->drawLine(100,y+100*i,400,y+100*i);
    }
//画4条竖线
    for(int i=0;i<4;i++)
    {
        paint->drawLine(x+100*i,100,x+100*i,400);
    }
//在棋盘正中做两个红棋子
    drawChessman(chessRed,chessBlue,playChessFlag,selectFlag,paint,chessmanSelected);
}
void Checkerboard::drawChessman(QVector<int> chessRed,QVector<int> chessBlue,bool pCFlag,bool sFlag,QPainter *paint,QPoint chessmanSelected)
{

    if(sFlag==false)
    {
        //在棋盘正中做两个红棋子
        paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));
        for (int i =0;i<chessRed.size();i++) {
            paint->drawEllipse(searchBoardCoord(chessRed[i]),20,20);
        }
        paint->setBrush(QBrush(Qt::blue,Qt::SolidPattern));
        for (int i =0;i<chessBlue.size();i++) {
            paint->drawEllipse(searchBoardCoord(chessBlue[i]),20,20);
        }
    }
    else
    {
        if(pCFlag==true)
        {
            paint->setBrush(QBrush(Qt::blue,Qt::SolidPattern));
            for (int i =0;i<chessBlue.size();i++) {
                paint->drawEllipse(searchBoardCoord(chessBlue[i]),20,20);
            }
            paint->setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
            paint->drawEllipse(chessmanSelected,20,20);

            paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));
            for (int i =0;i<chessRed.size();i++) {
                if(chessmanSelected!=searchBoardCoord(chessRed[i]))
                {
                     paint->drawEllipse(searchBoardCoord(chessRed[i]),20,20);
                }
            }
        }
        else
        {
            paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));
            for (int i =0;i<chessRed.size();i++) {
                paint->drawEllipse(searchBoardCoord(chessRed[i]),20,20);
            }
            paint->setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
            paint->drawEllipse(chessmanSelected,20,20);

            paint->setBrush(QBrush(Qt::blue,Qt::SolidPattern));
            for (int i =0;i<chessBlue.size();i++) {
                if(chessmanSelected!=searchBoardCoord(chessBlue[i]))
                {
                     paint->drawEllipse(searchBoardCoord(chessBlue[i]),20,20);
                }
            }
        }
    }
    paint->end();
}
void Checkerboard::mousePressEvent(QMouseEvent * e)
{
    QPoint mPos = e->pos();
    if(selectFlag==true)
    {
        moveChessman(mPos);
    }
    chessmanSelected = selectChessman(playChessFlag,mPos);//选中棋子
    repaint();
}
void Checkerboard::mouseReleaseEvent(QMouseEvent *)
{

}
QPoint Checkerboard::selectChessman(bool pCFlag,QPoint pressPos)
{
    if(pCFlag==true)
    {
        for (int i = 0;i<chessRed.size();i++)
        {
            int chessDistance =(searchBoardCoord(chessRed[i]).x()-pressPos.x())*(searchBoardCoord(chessRed[i]).x()-pressPos.x())+
                    (searchBoardCoord(chessRed[i]).y()-pressPos.y())*(searchBoardCoord(chessRed[i]).y()-pressPos.y());
            if(chessDistance<=400)
            {
                selectFlag=true;
                selectChessTopo = chessRed[i];
                return searchBoardCoord(chessRed[i]);
            }
        }
    }
    else
    {
        for (int i = 0;i<chessBlue.size();i++)
        {
            int chessDistance =(searchBoardCoord(chessBlue[i]).x()-pressPos.x())*(searchBoardCoord(chessBlue[i]).x()-pressPos.x())+
                    (searchBoardCoord(chessBlue[i]).y()-pressPos.y())*(searchBoardCoord(chessBlue[i]).y()-pressPos.y());
            if(chessDistance<=400)
            {
                selectFlag=true;
                selectChessTopo = chessBlue[i];
                return searchBoardCoord(chessBlue[i]);
            }
        }
    }
    selectFlag = false;
    return QPoint(0,0);
}

void Checkerboard::moveChessman(QPoint pressPos)
{
    QVector<int> topoList = TopoBoard.value(selectChessTopo);
    for (int i = 1;i<=chessBoardCoord.size();i++)
    {
        int chessDistance =(chessBoardCoord.value(i).x()-pressPos.x())*(chessBoardCoord.value(i).x()-pressPos.x())+
                (chessBoardCoord.value(i).y()-pressPos.y())*(chessBoardCoord.value(i).y()-pressPos.y());
        if(chessDistance<=400)
        {
            moveChessTopo = chessBoardCoord.key(chessBoardCoord[i]);
        }
    }
    //移动的位置不能有棋子可以走
    for (int i =0;i<chessRed.size();i++)
    {
        if(chessRed[i]==moveChessTopo)
            return;
    }
    for (int i =0;i<chessBlue.size();i++)
    {
        if(chessBlue[i]==moveChessTopo)
            return;
    }
    //如果存在这个拓扑点，就要更新点
    for (int i=0;i<topoList.size();i++)
    {
        if(moveChessTopo==topoList[i])
        {
            if(playChessFlag==true)
            {
                for (int i =0;i<chessRed.size();i++) {
                    if(chessRed[i]==selectChessTopo)
                        chessRed[i]=moveChessTopo;
                }
                playChessFlag =false;
                selectFlag = false;
            }
            else
            {
                for (int i =0;i<chessBlue.size();i++) {
                    if(chessBlue[i]==selectChessTopo)
                        chessBlue[i]=moveChessTopo;
                }
                playChessFlag =true;
                selectFlag = false;
            }
        }
    }

}
QPoint Checkerboard::searchBoardCoord(int topoChessman)
{
    return chessBoardCoord.value(topoChessman);
}
