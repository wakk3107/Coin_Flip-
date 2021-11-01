#include "playscene.h"
#include<QDebug>
#include<QPainter>
#include<QLabel>
#include<QPixmap>
#include<QPropertyAnimation>
//PlayScene::PlayScene(QObject *parent) :
//    QMainWindow(parent)
//{
//}
PlayScene::PlayScene(int levelNum)
{
    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);

    this->levelIndex=levelNum;
    QString s=QString("你进入了第%1关").arg(levelNum);
    qDebug()<<s;
    //设置窗口固定大小
    this->setFixedSize(420,688);
        //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
        //设置标题
    this->setWindowTitle("翻金币");

        //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
        //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
        //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");
        //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){this->close();});
    //返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButton::clicked,[=](){
             emit this->chooseSceneBack();

    });
    QLabel* label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);

    QString str=QString("LEVEL:%1").arg(this->levelIndex);
    label->setText(str);
    label->setGeometry(QRect(40, this->height() - 100,180, 80));
    //创建金币的背景图片
        for(int i = 0 ; i < 4;i++)
        {
            for(int j = 0 ; j < 4; j++)
            {
               //绘制背景图片
                QPixmap pix=QPixmap(":/res/BoardNode.png");
                QLabel* label = new QLabel;
                label->setGeometry(0,0,pix.width(),pix.height());
                label->setPixmap(pix);
                label->setParent(this);
                label->move(72 + i*pix.width(),220+pix.height()*j);
                //胜利图片显示
                QLabel* winLabel = new QLabel;
                QPixmap tmpPix;
                tmpPix.load(":/res/LevelCompletedDialogBg.png");
                winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
                winLabel->setPixmap(tmpPix);
                winLabel->setParent(this);
                winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());

                dataConfig config;
                for(int i = 0 ; i < 4;i++)
                {
                    for(int j = 0 ; j < 4; j++)
                 {
                      gameArray[i][j] = config.mData[this->levelIndex][i][j];
                      QString str;
                      if(this->gameArray[i][j]==1)
                      {
                       //显示金币
                       str=":/res/Coin0001.png";

                       }
                      else{
                       str=":/res/Coin0008.png";
                       }
                         //创建金币
                         MyCoin * coin = new MyCoin(str);
                         coin->setParent(this);
                         coin->move(80 + i*pix.width(),228+pix.height()*j);
                         coin->posX = i; //记录x坐标
                         coin->posY = j; //记录y坐标
                         coin->flag =gameArray[i][j]; //记录正反标志
                         coinBtn[i][j]=coin;
                         connect(coin,&MyCoin::clicked,[=](){
                             flipSound->play();
                             //qDebug() << "点击的位置： x = " <<  coin->posX << " y = " << coin->posY ;
                             coin->changeFlag();
                             gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0; //数组内部记录的标志同步修改
                             if(coin->posX+1 <=3)
                             {
                                 coinBtn[coin->posX+1][coin->posY]->changeFlag();
                                 this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                             }
                             if(coin->posX-1>=0)
                             {
                                 coinBtn[coin->posX-1][coin->posY]->changeFlag();
                                 this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY]== 0 ? 1 : 0;
                             }
                             if(coin->posY+1<=3)
                             {
                                 coinBtn[coin->posX][coin->posY+1]->changeFlag();
                                 this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                             }
                             if(coin->posY-1>=0)
                             {
                                 coinBtn[coin->posX][coin->posY-1]->changeFlag();
                                 this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                             }
                             this->isWin = true;
                             for(int i = 0 ; i < 4;i++)
                             {
                                 for(int j = 0 ; j < 4; j++)
                                 {
                                     //qDebug() << coinBtn[i][j]->flag ;
                                     if( coinBtn[i][j]->flag == false)
                                     {
                                         this->isWin = false;
                                         break;
                                     }
                                 }
                             }

                             if(this->isWin)
                             {
                                 for(int i = 0 ; i < 4;i++)
                                 {
                                     for(int j = 0 ; j < 4; j++)
                                     {
                                         coinBtn[i][j]->isWin=true;
                                     }
                                 }
                                 winSound->play();
                                 qDebug() << "胜利";
                                 //胜利图片砸下来
                                 QPropertyAnimation* animation=new QPropertyAnimation(winLabel,"geometry");
                                 animation->setDuration(1000);
                                 animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                                 animation->setEndValue(QRect(winLabel->x(),winLabel->y()+184,winLabel->width(),winLabel->height()));
                                 animation->setEasingCurve(QEasingCurve::OutBounce);
                                 animation->start();
                             }



                         });




                    }
                }


            }
        }

}
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":res/Title.png");
    pix=pix.scaled(pix.width()*0.7,pix.height()*0.7);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
