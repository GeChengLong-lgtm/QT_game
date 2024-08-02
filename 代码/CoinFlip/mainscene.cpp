#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QDebug>
#include "mypushbutton.h"
#include <QTimer>
#include <QSound> //多媒体模块下的音效
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景

    //设置固定大小
    setFixedSize(420, 588);

    //设置图标
    setWindowIcon(QIcon(":/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币主场景");

    //退出按钮实现
    connect(ui->actionquit, &QAction::triggered, [=](){
        this->close();
    });

    //准备开始按钮的音效
    QSound *startSound = new QSound(":/TapButtonSound.wav", this);

    startSound->setLoops(1);
    startSound->play();

    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width()*0.5,
                   this->height() * 0.7);
    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听选择管卡返回按钮的信号
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this, [=](){
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();
        this->show();
    });

    connect(startBtn, &MyPushButton::clicked, [=](){
        qDebug()<<"点击了开始";
        //播放开始音效资源
        startSound->play();
        //做弹起特效
        startBtn->zoom1();
        startBtn->zoom2();

        //延时进入选择关卡场景

        QTimer::singleShot(500, this, [=](){
            //设置choosescene场景的位置
            chooseScene->setGeometry(this->geometry());
            //自身隐藏
            this->hide();
            //显示选择关卡场景
            chooseScene->show();


        });

    });

}

//重写paintevent事件 画背景图
void MainScene::paintEvent(QPaintEvent *ev){

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //画背景上图标
    pix.load(":/Title.png");
    pix = pix.scaled(pix.width()*0.8, pix.height()*0.8);
    painter.drawPixmap(10, 30, pix);


}

MainScene::~MainScene()
{
    delete ui;
}

