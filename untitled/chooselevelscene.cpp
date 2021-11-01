#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include <QTimer>
#include<QLabel>
#include<QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) :
    QMainWindow(parent)
{
    this->setFixedSize(420,688);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡场景");
    QMenuBar * bar=menuBar();
    setMenuBar(bar);
    QMenu * startMenu=bar->addMenu("开始");
    QAction *quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    //选择关卡按钮音效
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //返回按钮
   MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
   backBtn->setParent(this);
   backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
   connect(backBtn,&MyPushButton::clicked,[=](){
            emit this->chooseSceneBack();
            backSound->play();
   });



   //创建关卡按钮
   for(int i=0;i<20;i++)
   {
       MyPushButton *menuBtn=new MyPushButton(":/res/LevelIcon.png");
       menuBtn->setParent(this);
       menuBtn->move(55 + (i%4)*85 , 170+ (i/4)*85);
       connect(menuBtn,&MyPushButton::clicked,[=](){
           chooseSound->play();
           QString str=QString("您选择的是第%1关").arg(i+1);
           qDebug()<<str;
           play=new PlayScene(i+1);
           play->show();
           this->hide();
           connect(play,&PlayScene::chooseSceneBack,[=]()
           {
//               this->hide();
               delete play;
               play=NULL;
               this->show();
           });

       });
       QLabel* label=new QLabel;
       label->setParent(this);
       label->setFixedSize(menuBtn->width(),menuBtn->height());
       label->setText(QString::number(i+1));
       label->move(55 + (i%4)*85 , 170+ (i/4)*85);
       label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
       label->setAttribute(Qt::WA_TransparentForMouseEvents);

   }
}
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
