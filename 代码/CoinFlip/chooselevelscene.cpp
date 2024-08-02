#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "playscene.h"
#include <QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{

    //配置选择关卡场景
    this->setFixedSize(420, 588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建退出菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出，实现退出游戏
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    //选择关卡按钮音效
    QSound *chooseSound = new QSound(":/TapButtonSound.wav", this);

    //选择返回按钮音效
    QSound *backSound = new QSound(":/BackButtonSound.wav", this);

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/BackButton.png", ":/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),
                  this->height() - backBtn->height());

    //点击返回
    connect(backBtn, &MyPushButton::clicked, [=](){
        //播放返回按钮音效
        backSound->play();
        qDebug()<<"点击了返回按钮";
        QTimer::singleShot(500, this, [=](){
            //告诉主场景，返回
            emit this->chooseSceneBack();
        });

    });

    //创建选择关卡按钮
    for(int i = 0; i < 20; i++){
        MyPushButton *menuBtn = new MyPushButton(":/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(58 + i%4 * 80, 150 + i/4 * 80);

        //监听每个按钮的点击事件
        connect(menuBtn, &MyPushButton::clicked, [=](){
            //播放选择关卡按钮音效
            chooseSound->play();
            QString str = QString("您选择的是第 %1 关").arg( i+1 );
            qDebug()<<str;

            //进入到游戏场景
            this->hide();//隐藏选关场景
            play = new PlayScene(i+1);//创建游戏场景        
            //设置游戏 场景初始位置
            play->setGeometry(this->geometry());
            play->show();//显示游戏场景
            connect(play, &PlayScene::chooseSceneBack, [=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = NULL;
            });
        });

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(58 + i%4 * 80, 150 + i/4 * 80);

        //设置label上的文字对齐方式 水平居中和垂直居中
        label->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        //设置让鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *e){

    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/OtherSceneBg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //加载标题
    pix.load(":/Title.png");
    painter.drawPixmap( (this->width() - pix.width()) * 0.5, 30,
                        pix.width(), pix.height(), pix);


}
