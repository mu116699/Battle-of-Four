#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <QWidget>
#include <QPainter>
#include <chessman.h>
#include <QVector>
#include <QMap>
#include <QPoint>
class Checkerboard : public QWidget
{
    Q_OBJECT
public:
    explicit Checkerboard(QWidget *parent = nullptr);
    ~Checkerboard();
signals:

public slots:

public:
QPoint selectChessman(bool pCFlag,QPoint pressPos);//选中棋子
void moveChessman(QPoint pressPos);
void drawChessman(QVector<int> chessRed,QVector<int> chessBlue,bool pCFlag,bool sFlag,QPainter *paint,QPoint chessmanSelected);
QPoint searchBoardCoord(int topoChessman);
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    QPainter *paint;
private:
    Chessman m_SelectedItem;
    bool m_bExistSelectedItem;	//是否已存在选中的棋子
    bool m_bIsRedTurn;		//当前该红方下

    QMap<int,QVector<int>>TopoBoard;//棋格拓扑
    QMap<int,QVector<int>> TopoRow;//行拓扑
    QMap<int,QVector<int>> TopoColumn;//列拓扑
    QMap<int,QPoint> chessBoardCoord;//坐标对应
    //棋子常量
    QVector<int> chessRed;
    QVector<int> chessBlue;

    bool playChessFlag;//该谁下棋了
    bool selectFlag;//是否选中棋子
    QPoint chessmanSelected;//选中棋子

    int selectChessTopo;//选中的点
    int moveChessTopo;//选中的移动点
};

#endif // CHECKERBOARD_H
