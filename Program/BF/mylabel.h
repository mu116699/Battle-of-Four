#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>

class MyLabel : public QLabel
{
public:
    MyLabel();

    MyLabel(const QString & text,QWidget *parent);

    MyLabel(QWidget *parent);

    void mousePressEvent(QMouseEvent *event);
};

#endif // MYLABEL_H
