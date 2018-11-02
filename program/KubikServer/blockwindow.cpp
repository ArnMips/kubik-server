#include "blockwindow.h"
#include "ui_blockwindow.h"

BlockWindow::BlockWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockWindow)
{
    ui->setupUi(this);

    setWindowFlag(Qt::SplashScreen);
}

BlockWindow::~BlockWindow()
{
    delete ui;
}

//void BlockWindow::activateBlock()
//{
//    showFullScreen();
//    setFocus();
//}

//void BlockWindow::diactivateBlock()
//{
//    close();
//}
