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
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QVBoxLayout>
//#include <QAxWidget>

Checkerboard::Checkerboard(QWidget *parent) : QWidget(parent)
{
//   setGeometry(100,100,600,800);
//   this->resize(800,500);
//   this->setMinimumSize(800, 500);
//   this->setMaximumSize(800, 500);

   QPalette palette;
   palette.setBrush(QPalette::Background, QBrush(Qt::cyan));
   this->setPalette(palette);
    paint=new QPainter;
   //init
   chessRed={13,14,15,16};
   chessBlue = {1,2,3,4};

   playChessFlag = true;//红方先手，否子蓝方
   selectFlag = false;
   canMoveFlag = false;
   movedFlag = false;
   machineFlag = false;
   chessmanSelected = QPoint(0,0);
   TopoBoard={{1,{5,2}},{2,{1,6,3}},{3,{2,7,4}},{4,{3,8}},
              {5,{9,6,1}},{6,{5,10,7,2}},{7,{6,11,8,3}},{8,{7,12,4}},
              {9,{13,10,5}},{10,{9,14,11,6}},{11,{10,15,12,7}},{12,{11,16,8}},
              {13,{14,9}},{14,{13,15,10}},{15,{14,16,11}},{16,{15,12}}};
   TopoAndCoord = {{1,{1,1}},{2,{1,2}},{3,{1,3}},{4,{1,4}},{5,{2,1}},{6,{2,2}},{7,{2,3}},{8,{2,4}},
                   {9,{3,1}},{10,{3,2}},{11,{3,3}},{12,{3,4}},{13,{4,1}},{14,{4,2}},{15,{4,3}},{16,{4,4}}};
   TopoColumn={{1,{1,2,3,4}},{2,{5,6,7,8}},{3,{9,10,11,12}},{4,{13,14,15,16}}};//行拓扑
   TopoRow={{1,{1,5,9,13}},{2,{2,6,10,14}},{3,{3,7,11,15}},{4,{4,8,12,16}}};//列拓扑
   chessBoardCoord={{1,QPoint(200,800)},{2,QPoint(400,800)},{3,QPoint(600,800)},{4,QPoint(800,800)},
              {5,QPoint(200,600)},{6,QPoint(400,600)},{7,QPoint(600,600)},{8,QPoint(800,600)},
              {9,QPoint(200,400)},{10,QPoint(400,400)},{11,QPoint(600,400)},{12,QPoint(800,400)},
              {13,QPoint(200,200)},{14,QPoint(400,200)},{15,QPoint(600,200)},{16,QPoint(800,200)}};


   startButton = new QPushButton("Sart the Game",this);
   startButton->setGeometry(100,1000,400,80);
   machine = new QPushButton("Man-Machine",this);
   machine->setGeometry(550,1000,400,80);
   handicap = new QPushButton("Handicap",this);
   handicap->setGeometry(100,1100,400,80);
   help = new QPushButton("Help",this);
   help->setGeometry(550,1100,400,80);

   connect(startButton,SIGNAL(clicked()),this,SLOT(startGame()));
   connect(handicap,SIGNAL(clicked()),this,SLOT(oneHandicap()));
   connect(machine,SIGNAL(clicked()),this,SLOT(oneMachine()));
   connect(help,SIGNAL(clicked()),this,SLOT(oneHelp()));

   //x86-64(已经删除)

   // Android
   welcome = new QLabel("Welcome to Battle of Four!",this);
   welcome->setGeometry(200,0,800,100);
   welcome->setStyleSheet("color:red");// 文本颜色
   welcome->setFont(QFont( "Timers" , 17,  QFont::Bold) );
   thanks = new QLabel("Thanks to Qiaoli Lu, Min Fu,Suqin Zhai, \nDaojian Ge and other friends of Jiyuan,\nusing version 1.0.",this);
   //thanks = new QLabel("XXXXXXXXXXXXXXXXXXXXXXXXXXX \nXXXXXXXXXXXXXXXXXXXXXXXXXXX,\nXXXXXXXXXXXXXXXXX.",this);
   thanks->setGeometry(100,1200,900,180);
   //thanks->setStyleSheet("color:blue");// 文本颜色
   author = new QLabel("Author:Jack Tian©",this);
   author->setGeometry(600,1400,400,80);
   this->setMouseTracking (true);

   img = new MyLabel("Press",this);
   img->setPixmap(QPixmap(":/heart.ico"));
   img->setGeometry(100,1380,200,200);
   title = new QLabel("Test Version",this);
   title->setGeometry(100,1560,400,100);
   test = new QLabel("Thanks for you test!\nPlase record my mistake.\n",this);
   test->setGeometry(100,1600,900,320);

}
Checkerboard::~Checkerboard()
{

}

void Checkerboard::startGame()
{
    if(movedFlag==true)
    {
        if(QMessageBox::Yes == QMessageBox::information(this,QStringLiteral("Start the Game"),
                              QStringLiteral("Restart the game?"),QMessageBox::Yes | QMessageBox:: No))
        {
            chessRed={13,14,15,16};
            chessBlue = {1,2,3,4};
            movedFlag = false;
            playChessFlag = true;
            machineFlag = false;
            repaint();
        }
        else
        {
            close();
        }
    }
    else
    {
        chessRed={13,14,15,16};
        chessBlue = {1,2,3,4};
        playChessFlag = true;
        machineFlag = false;
        repaint();
    }
}

void Checkerboard::oneHandicap()
{
    if(playChessFlag==true)
    {
        playChessFlag =false;
        if((machineFlag==true)&&(playChessFlag==false))
        {
            machineMove(chessBlue);
            killChessman(moveChessTopo);
            playChessFlag =true;
        }
    }
    else
    {
        playChessFlag =true;
    }
}

void Checkerboard::oneMachine()
{
    if(movedFlag==true)
    {
        if(QMessageBox::Yes == QMessageBox::information(this,QStringLiteral("Start the Game"),
                              QStringLiteral("Restart the game?"),QMessageBox::Yes | QMessageBox:: No))
        {
            chessRed={13,14,15,16};
            chessBlue = {1,2,3,4};
            movedFlag = false;
            playChessFlag = true;
            machineFlag = false;
            repaint();
        }
        else
        {
            close();
        }
    }
    else
    {
        chessRed={13,14,15,16};
        chessBlue = {1,2,3,4};
        playChessFlag = true;
        machineFlag = false;
        repaint();
    }
    machineFlag = true;
    repaint();
}

void Checkerboard::oneHelp()
{
//    QDialog *window = new QDialog(this);
//    window->setWindowTitle("Help");
//    window->show();
//    QVBoxLayout *mainLayout = new QVBoxLayout(window);
//    QAxWidget *myWidget = new QAxWidget(this);
//    mainLayout->addWidget(myWidget);
//    myWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));//注册组件UUID
//    myWidget->setObjectName(QString::fromUtf8("my_musicLibraryWebWid"));//设置控件的名称
//    myWidget->setFocusPolicy(Qt::StrongFocus);       //设置控件接收键盘焦点的方式：鼠标单击、Tab键
//    myWidget->setProperty("DisplayAlerts",false);    //不显示任何警告信息。
//    myWidget->setProperty("DisplayScrollBars",true); // 显示滚动条
//    QString webStr = QString("https://github.com/mu116699/Battle-of-Four/blob/master/README.md");//设置要显示的Url  kugou的。
//    myWidget->dynamicCall("Navigate(const QString&)",webStr);
}

void Checkerboard::machineMove(QVector<int> &chess)
{
    QVector<int> total;
    for (int i = 0;i<chess.size();i++) {
        total.push_back(i);
    }

    for (int i = 0;i<chess.size();i++) {
        //棋子随机
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        int usingChess = qrand() % (total.size());
        total.remove(usingChess);
        qDebug()<<"usingChess"<<usingChess;

        QVector<int>chessTopo=TopoBoard.value(chess[usingChess]);

        QVector<int> topoTotal;
        for (int m = 0;m<chessTopo.size();m++) {
            topoTotal.push_back(m);
        }
        for (int j=0;j<chessTopo.size();j++) {
            //方向随机
            qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
            int usingDirection = qrand() % (topoTotal.size());
            topoTotal.remove(usingDirection);
            qDebug()<<"usingDirection"<<usingChess;

            if(getState(chessTopo[usingDirection])==-1)
            {
                chess[usingChess]=chessTopo[usingDirection];
                moveChessTopo = chessTopo[usingDirection];
                return;
            }
        }
    }
}

bool Checkerboard::canMoveChess(QVector<int> chess)
{
    for (int i =0;i<chess.size();i++) {
        //获取行列序号
        QVector<int> RowColumn = TopoAndCoord.value(chess[i]);
        QVector<int> getTopoRowColumn = TopoColumn.value(RowColumn[0]);
        getTopoRowColumn.append(TopoRow.value(RowColumn[1]));
        for (int i = 0;i<getTopoRowColumn.size();i++) {
            if(getState(getTopoRowColumn[i])==-1)
            {
                return true;
            }
        }
    }
    return false;
}

void Checkerboard::rowColumnjudge(QVector<int> getTopoColumn)
{
    //qDebug()<<getState(getTopoColumn[0])<<getState(getTopoColumn[1])<<getState(getTopoColumn[2])<<getState(getTopoColumn[3]);

    if(getState(getTopoColumn[0])==-1)
    {
        if(playChessFlag==false)
        {
            if((getState(getTopoColumn[1])==0)&&(getState(getTopoColumn[2])==0)&&(getState(getTopoColumn[3])==1))
            {
                deleteChessman(chessBlue,getTopoColumn[3]);
                if(chessBlue.size()==1)
                {
                    if(QMessageBox::Yes == QMessageBox::information(this,QStringLiteral("Congratulations"),
                                          QStringLiteral("Red Win!!!\nDo you want to continue?"),QMessageBox::Yes | QMessageBox:: No))
                    {
                        chessRed={13,14,15,16};
                        chessBlue = {1,2,3,4};
                        playChessFlag = true;
                    }
                    else
                    {
                        close();
                    }
                }
            }
            else if((getState(getTopoColumn[1])==1)&&(getState(getTopoColumn[2])==0)&&(getState(getTopoColumn[3])==0))
            {
                deleteChessman(chessBlue,getTopoColumn[1]);
                if(chessBlue.size()==1)
                {
                    if(QMessageBox::Yes == QMessageBox::information(this,QStringLiteral("Congratulations"),
                                       QStringLiteral("Red Win!!!\nDo you want to continue?"),QMessageBox::Yes | QMessageBox:: No))
                    {
                        chessRed={13,14,15,16};
                        chessBlue = {1,2,3,4};
                        playChessFlag = true;
                    }
                    else
                    {
                        close();
                    }
                }
            }
        }
        else
        {
            if((getState(getTopoColumn[1])==1)&&(getState(getTopoColumn[2])==1)&&(getState(getTopoColumn[3])==0))
            {
                deleteChessman(chessRed,getTopoColumn[3]);
                if(chessRed.size()==1)
                {
                    if(QMessageBox::Yes == QMessageBox::information(this,QStringLiteral("Congratulations"),
                                        QStringLiteral("Blue Win!!!\nDo you want to continue?"),QMessageBox::Yes | QMessageBox:: No))
                    {
                        chessRed={13,14,15,16};
                        chessBlue = {1,2,3,4};
                        playChessFlag = true;
                    }
                    else
                    {
                        close();
                    }
                }
            }
            else if((getState(getTopoColumn[1])==0)&&(getState(getTopoColumn[2])==1)&&(getState(getTopoColumn[3])==1))
            {
                deleteChessman(chessRed,getTopoColumn[1]);
                if(chessRed.size()==1)
                {
                    if(QMessageBox::Yes == QMessageBox::information(this,QStringLiteral("Congratulations"),
                                   QStringLiteral("Blue Win!!!\nDo you want to continue?"),QMessageBox::Yes | QMessageBox:: No))
                    {
                        chessRed={13,14,15,16};
                        chessBlue = {1,2,3,4};
                        playChessFlag = true;
                    }
                    else
                    {
                        close();
                    }
                }
            }
        }
    }
    else if (getState(getTopoColumn[3])==-1)
    {
        if(playChessFlag==false)
        {
            if((getState(getTopoColumn[0])==0)&&(getState(getTopoColumn[1])==0)&&(getState(getTopoColumn[2])==1))
            {
                deleteChessman(chessBlue,getTopoColumn[2]);
                if(chessBlue.size()==1)
                {
                    if(QMessageBox::Yes == QMessageBox::information(this,QStringLiteral("Congratulations"),
                              QStringLiteral("Red Win!!!\nDo you want to continue?"),QMessageBox::Yes | QMessageBox:: No))
                    {
                        chessRed={13,14,15,16};
                        chessBlue = {1,2,3,4};
                        playChessFlag = true;
                    }
                    else
                    {
                        close();
                    }
                }
            }
            else if((getState(getTopoColumn[0])==1)&&(getState(getTopoColumn[1])==0)&&(getState(getTopoColumn[2])==0))
            {
                deleteChessman(chessBlue,getTopoColumn[0]);
                if(chessBlue.size()==1)
                {
                    if(QMessageBox::Yes == QMessageBox::information(this,QStringLiteral("Congratulations"),
                             QStringLiteral("Red Win!!!\nDo you want to continue?"),QMessageBox::Yes | QMessageBox:: No))
                    {
                        chessRed={13,14,15,16};
                        chessBlue = {1,2,3,4};
                        playChessFlag = true;
                    }
                    else
                    {
                        close();
                    }
                }
            }
        }
        else
        {
            if((getState(getTopoColumn[0])==1)&&(getState(getTopoColumn[1])==1)&&(getState(getTopoColumn[2])==0))
            {
                deleteChessman(chessRed,getTopoColumn[2]);
                if(chessRed.size()==1)
                {
                    if(QMessageBox::Yes == QMessageBox::information(this,QStringLiteral("Congratulations"),
                       QStringLiteral("Blue Win!!!\nDo you want to continue?"),QMessageBox::Yes | QMessageBox:: No))
                    {
                        chessRed={13,14,15,16};
                        chessBlue = {1,2,3,4};
                        playChessFlag = true;
                    }
                    else
                    {
                        close();
                    }
                }
            }
            else if((getState(getTopoColumn[0])==0)&&(getState(getTopoColumn[1])==1)&&(getState(getTopoColumn[2])==1))
            {
                deleteChessman(chessRed,getTopoColumn[0]);
                if(chessRed.size()==1)
                {
                    if(QMessageBox::Yes == QMessageBox::information(this,QStringLiteral("Congratulations"),
                           QStringLiteral("Blue Win!!!\nDo you want to continue?"),QMessageBox::Yes | QMessageBox:: No))
                    {
                        chessRed={13,14,15,16};
                        chessBlue = {1,2,3,4};
                        playChessFlag = true;
                    }
                    else
                    {
                        close();
                    }
                }
            }
        }
    }
}

void Checkerboard::deleteChessman(QVector<int> &chessman, int delTopo)
{
    for (int i = 0;i<chessman.size();i++)
    {
        if(chessman[i]==delTopo)
        {
            chessman.remove(i);
        }
    }
}

int Checkerboard::getState(int TopoRC)
{
    //移动的位置不能有棋子可以走
    for (int i =0;i<chessRed.size();i++)
    {
        if(chessRed[i]==TopoRC)
            return 0;
    }
    for (int i =0;i<chessBlue.size();i++)
    {
        if(chessBlue[i]==TopoRC)
            return 1;
    }
    return -1;
}


void Checkerboard::killChessman(int moveChessTopo)
{
    //获取行列序号
    QVector<int> RowColumn = TopoAndCoord.value(moveChessTopo);
    //行列判断
    QVector<int> getTopoColumn = TopoColumn.value(RowColumn[0]);
    QVector<int> getTopoRow = TopoRow.value(RowColumn[1]);
    QString str = "Row:";
    rowColumnjudge(getTopoColumn);
    rowColumnjudge(getTopoRow);

    for(int i = 0; i < getTopoRow.size(); ++i)

    {

        str=str+QString::number(getState(getTopoRow[i]));
        str =str+",";

    }
    str =str+"\nCol:";
    for(int i = 0; i < getTopoColumn.size(); ++i)

    {
        str=str+QString::number(getState(getTopoColumn[i]));
        str =str+",";

    }

    test->setText(str);
    canMoveFlag =false;
}

void Checkerboard::paintEvent(QPaintEvent *)
{
    int x=200,y=200;
    paint->begin(this);
    paint->setPen(QPen(Qt::black,4,Qt::SolidLine));
    paint->setBrush(QBrush(Qt::white,Qt::SolidPattern));
//画4条横线
    for(int i=0;i<4;i++)
    {
        paint->drawLine(200,y+200*i,800,y+200*i);
    }
//画4条竖线
    for(int i=0;i<4;i++)
    {
        paint->drawLine(x+200*i,200,x+200*i,800);
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
            paint->drawEllipse(searchBoardCoord(chessRed[i]),50,50);
        }
        paint->setBrush(QBrush(Qt::blue,Qt::SolidPattern));
        for (int i =0;i<chessBlue.size();i++) {
            paint->drawEllipse(searchBoardCoord(chessBlue[i]),50,50);
        }
    }
    else
    {
        if(pCFlag==true)
        {
            paint->setBrush(QBrush(Qt::blue,Qt::SolidPattern));
            for (int i =0;i<chessBlue.size();i++) {
                paint->drawEllipse(searchBoardCoord(chessBlue[i]),50,50);
            }
            paint->setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
            paint->drawEllipse(chessmanSelected,50,50);

            paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));
            for (int i =0;i<chessRed.size();i++) {
                if(chessmanSelected!=searchBoardCoord(chessRed[i]))
                {
                     paint->drawEllipse(searchBoardCoord(chessRed[i]),50,50);
                }
            }
        }
        else
        {
            paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));
            for (int i =0;i<chessRed.size();i++) {
                paint->drawEllipse(searchBoardCoord(chessRed[i]),50,50);
            }
            paint->setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
            paint->drawEllipse(chessmanSelected,50,50);

            paint->setBrush(QBrush(Qt::blue,Qt::SolidPattern));
            for (int i =0;i<chessBlue.size();i++) {
                if(chessmanSelected!=searchBoardCoord(chessBlue[i]))
                {
                     paint->drawEllipse(searchBoardCoord(chessBlue[i]),50,50);
                }
            }
        }
    }
    paint->end();
}
void Checkerboard::mousePressEvent(QMouseEvent * e)
{
    //每次先判断是否有子可走
    if(playChessFlag==true)
    {

        if(false ==canMoveChess(chessRed))
        {
            qDebug()<<"red"<<canMoveChess(chessRed);
            if(QMessageBox::Yes == QMessageBox::information(this,QStringLiteral("Congratulations"),
                                  QStringLiteral("Blue Win!!!\nDo you want to continue?"),QMessageBox::Yes | QMessageBox:: No))
            {
                chessRed={13,14,15,16};
                chessBlue = {1,2,3,4};
                playChessFlag = true;
            }
            else
            {
                close();
            }

          }
    }
    else
    {
        if(false ==canMoveChess(chessBlue))
        {
            qDebug()<<"Blue"<<canMoveChess(chessBlue);
            if(QMessageBox::Yes == QMessageBox::information(this,QStringLiteral("Congratulations"),
                                  QStringLiteral("Red Win!!!\nDo you want to continue?"),QMessageBox::Yes | QMessageBox:: No))
            {
                chessRed={13,14,15,16};
                chessBlue = {1,2,3,4};
            }
            else
            {
                close();
            }

          }
    }
    QPoint mPos = e->pos();
    if(selectFlag==true)
    {
        moveChessman(mPos);
        if(canMoveFlag == true)
        {
            killChessman(moveChessTopo);
        }
    }
    chessmanSelected = selectChessman(playChessFlag,mPos);//选中棋子
    repaint();
}

void Checkerboard::mouseReleaseEvent(QMouseEvent *)
{
    if((machineFlag==true)&&(playChessFlag==false))
    {
        machineMove(chessBlue);
        playChessFlag =true;
        killChessman(moveChessTopo);
        repaint();
    }
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
        if(chessDistance<=2500)
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
                canMoveFlag = true;
                movedFlag = true;
            }
            else
            {
                for (int i =0;i<chessBlue.size();i++) {
                    if(chessBlue[i]==selectChessTopo)
                        chessBlue[i]=moveChessTopo;
                }
                playChessFlag =true;
                selectFlag = false;
                canMoveFlag = true;
                movedFlag = true;
            }
        }
    }

}
QPoint Checkerboard::searchBoardCoord(int topoChessman)
{
    return chessBoardCoord.value(topoChessman);
}
