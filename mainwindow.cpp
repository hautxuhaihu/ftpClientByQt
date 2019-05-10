#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::test);
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
        ftpGet();
    }
}

void MainWindow::ftpGet(){
// ftpManager->disconnect(SIGNAL(finished(QNetworkReply*)));
 QUrl url(ui->server->text());
 url.setPort(21);
 url.setUserName(ui->username->text());
 url.setPassword(ui->password->text());
 ftpManager.get(QNetworkRequest(url));
// ftpManager2->get(QNetworkRequest(url));
 connect(&ftpManager,SIGNAL(finished(QNetworkReply*)),SLOT(manageGetResult(QNetworkReply*)));//接收返回值
}

void MainWindow::manageGetResult(QNetworkReply *reply)
{
    //基本和managerPut类似
    qDebug()<<reply->error();
    QByteArray data;
    switch(reply->error()){
    case QNetworkReply::NoError:
        data=reply->readAll();//从url中读取文件内容，输出到data中（也可以再将数据写入到文件中，为了方便，这里就权且打印一下吧）
        QMessageBox::information(this,"Put information","Download Success!The file you've got is :"+data);
        break;
    case QNetworkReply::HostNotFoundError:
        QMessageBox::information(this,"Put information","Host Not Found!");
        break;
    case QNetworkReply::AuthenticationRequiredError:
        QMessageBox::information(this,"Put information","Login Failure!");
        break;
    default:
        QMessageBox::information(this,"Put information","Unknown Failure");
        break;
    }
}

void MainWindow::ftpWrite(QByteArray data)
{
    int position= (ui->server->text()).lastIndexOf("/");
    QString fileName= (ui->server->text()).mid(position+1);
    qDebug() << fileName;


}

