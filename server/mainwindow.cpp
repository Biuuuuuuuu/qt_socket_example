#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s=new QTcpServer(this);
    connect(s,SIGNAL(newConnection()),this,SLOT(newConnect()));
    qDebug()<<(s->listen(QHostAddress::LocalHost,11111)?"Listen ok":"Listen fail");
    qDebug()<<s->serverAddress().toString();
    qDebug()<<s->serverPort();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnect(){
    qDebug()<<"new connect";
    QTcpSocket* nextsoc=s->nextPendingConnection();
    if(nextsoc)soc.push_back(nextsoc);
    connect(nextsoc,SIGNAL(readyRead()),this,SLOT(read()));
}

void MainWindow::read(){
    qDebug()<<"ready read";
    QTcpSocket* link=qobject_cast<QTcpSocket*>(sender());
    if(!link){
        qDebug()<<"invalid signal sender";
        return;
    }
    QString msg=QString("read message: ")+QString::fromUtf8(link->readAll());
    qDebug()<<msg;
    link->write(msg.toUtf8());
    link->close();
}


