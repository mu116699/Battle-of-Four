#include "mylabel.h"
#include <QMessageBox>
#include <QMouseEvent>
MyLabel::MyLabel()
{

}

MyLabel::MyLabel(const QString & text,QWidget *parent) : QLabel(parent)
{
    setText(text);
}

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{

}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    //Qt::LeftButton
    //Qt::RightButton
    if(event->button()== Qt::LeftButton)
    {
        QMessageBox::information(this,"BF","Do what you do, love what you love.",
                                 QMessageBox::Yes,QMessageBox::Yes);
    }
}
