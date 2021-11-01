#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H
#include"playscene.h"
#include <QMainWindow>
#include<mypushbutton.h>
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    PlayScene *play = NULL;
signals:
void chooseSceneBack();
public slots:

};

#endif // CHOOSELEVELSCENE_H
