#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ROM/rom.h"
#include <QDebug>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ChooseROMButton = new QPushButton("Choose ROM...", this);
    ChooseROMButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    QObject::connect(ChooseROMButton, SIGNAL(clicked()), this, SLOT(on_ChooseROMButton_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ChooseROMButton_clicked()
{
//    qDebug() << "File: " << ChooseROM::openFile();
    //ROM::loadROM(ChooseROM::openFile().toStdString().c_str());
    //start new thread
        //load rom

        //start glWindow
}
