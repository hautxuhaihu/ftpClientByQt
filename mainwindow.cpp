#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::test);
    //ceshi
}

void MainWindow::test(const QString &s){
    qDebug() << s;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_get_clicked()
{
    if(ui->server->text().isEmpty())
    {
        QMessageBox::warning(this,"Error","Please fill in the information");
    }
    else {
        qDebug() << ui->server->text();
    }
}


