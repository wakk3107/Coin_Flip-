#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include<QPushButton>
#include <QWidget>
#include<QString>
#include<QDebug>
#include<Qpainter>
#include<QPixmap>
#include<QPropertyAnimation>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = 0);
    MyPushButton(QString normalImg,QString pressImg="");
    QString normalImgPath;
    QString pressedImgPath;
    void zoom1();//向下跳
    void zoom2();//向上跳
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:

};

#endif // MYPUSHBUTTON_H
