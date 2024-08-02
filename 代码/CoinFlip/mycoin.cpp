#include "mycoin.h"
#include <QDebug>
//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}


//参数代表传入的是金币还是银币
MyCoin::MyCoin(QString btnImg){

    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret){
        QString str = QString("图片 %1 加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }

    //设置图片固定大小
    this->setFixedSize(pix.width(), pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton(border:0px;)");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面的信号，并翻转金币
    connect(timer1, &QTimer::timeout, [=](){
        QPixmap pix1;
        QString str = QString(":/Coin000%1").arg(this->min++);
        pix1.load(str);

        //设置图片固定大小
        this->setFixedSize(pix1.width(), pix1.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton(border:0px;)");

        //设置图标
        this->setIcon(pix1);

        //设置图标大小
        this->setIconSize(QSize(pix1.width(), pix1.height()));

        //判断 如果翻完了，min = 1
        if(this->min > this->max){
            this->min = 1;
            isAnimation = false;
            timer1->stop();
        }
    });

    //监听反面翻正面的信号，并翻转金币
    connect(timer2, &QTimer::timeout, [=](){
        QPixmap pix2;
        QString str = QString(":/Coin000%1").arg(this->max--);
        pix2.load(str);

        //设置图片固定大小
        this->setFixedSize(pix2.width(), pix2.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton(border:0px;)");

        //设置图标
        this->setIcon(pix2);

        //设置图标大小
        this->setIconSize(QSize(pix2.width(), pix2.height()));

        //判断 如果翻完了，max = 8
        if(this->max < this->min){
            this->max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });
}

//重写 按下
void MyCoin::mousePressEvent(QMouseEvent *e){

    if(this->isAnimation || this->isWin){
        return;
    }
    else{
        QPushButton::mousePressEvent(e);
    }
}

//改变属性
void MyCoin::changeFlag(){

    if(this->flag){
        timer1->start(30);
        isAnimation = true;
        this->flag = false;
    }
    else{
        timer2->start(30);
        isAnimation = true;
        this->flag = true;
    }
}
