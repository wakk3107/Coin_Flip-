#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent) :
    QPushButton(parent)
{
}
MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    normalImgPath=normalImg;
    pressedImgPath=pressImg;
    QPixmap pixmap;
    bool ret=pixmap.load(normalImgPath);
    if(!ret)
        qDebug()<<normalImg<<"加载图片失败！";
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}
void MyPushButton::zoom1()
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

}

void MyPushButton::zoom2()
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressedImgPath!="")
    {
        QPixmap pixmap;
        bool ret=pixmap.load(this->pressedImgPath);
        if(!ret)
            qDebug()<<"加载图片失败！";
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()+10));
    }
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{

        QPixmap pixmap;
        bool ret=pixmap.load(this->normalImgPath);
        if(!ret)
            qDebug()<<"加载图片失败！";
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    //让父类执行其它内容
    return QPushButton::mouseReleaseEvent(e);
}

