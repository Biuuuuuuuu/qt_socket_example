#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s=new QTcpSocket(this);
    ui->pushButton->setText("connecting...");
    ui->pushButton->setEnabled(false);
    s->connectToHost(QHostAddress::LocalHost,11111);
    connect(s,SIGNAL(connected()),this,SLOT(go()));
    connect(s,SIGNAL(disconnected()),this,SLOT(disconnected()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::go(){
    ui->pushButton->setText("发射");
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_pushButton_clicked()
{
    QByteArray msg=ui->textEdit->toPlainText().toUtf8();
    s->write(msg);
    qDebug()<<msg;
}

void MainWindow::disconnected(){
    QString ret=QString::fromUtf8(s->readAll());
    QMessageBox::information(this,"link closing",ret);
    this->close();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->pushButton->setText("connecting...");
    ui->pushButton->setEnabled(false);
    s->connectToHost(QHostAddress::LocalHost,11111);
}
