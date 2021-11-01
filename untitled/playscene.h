#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include"mycoin.h"
#include <QMainWindow>
#include<QMenu>
#include<QMenuBar>
#include"mypushbutton.h"
#include"dataconfig.h"
#include"mycoin.h"
#include<QSound>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QObject *parent = 0);
    PlayScene(int levelNum);
    int levelIndex;
    void paintEvent(QPaintEvent *);
    int gameArray[4][4]; //二维数组数据
    MyCoin * coinBtn[4][4]; //金币按钮数组
    bool isWin = true;
signals:
void chooseSceneBack();
public slots:

};

#endif // PLAYSCENE_H
