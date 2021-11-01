#include "mainscene.h"
#include "ui_mainscene.h"
#include"mypushbutton.h"
#include <QTimer>
#include<windows.h>
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setFixedSize(420,688);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("老王带你翻金币");
    connect(ui->actionQuit,&QAction::triggered,[=](){
    this->close();
    });
    //音乐
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);
    MyPushButton* starBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    starBtn->setParent(this);
    starBtn->move(this->width()*0.5-starBtn->width()*0.5,this->height()*0.7);
    chooseScene=new ChooseLevelScene;
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();
        this->show();
    });
    connect(starBtn,&MyPushButton::clicked,[=]()
    {   startSound->play();
        starBtn->zoom1();
        starBtn->zoom2();
        chooseScene->setGeometry(this->geometry());
        this->hide();
        chooseScene->show();
        //监听选择关卡返回信号的按钮；

    });
}
void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":res/Title.png");
    pix=pix.scaled(pix.width()*0.7,pix.height()*0.7);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

MainScene::~MainScene()
{
    delete ui;
}
