#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
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
        fileUrl = QFileDialog::getSaveFileUrl(this,tr("Save File"),QUrl(""),tr("File(*.*)")); //选择路径
        initProgressBar();
        ftpDown();
    }
}

void MainWindow::ftpDown(){
 ftpManager.disconnect(SIGNAL(finished(QNetworkReply*)));
 QUrl url(ui->server->text());
 url.setPort(21);
 url.setUserName(ui->username->text());
 url.setPassword(ui->password->text());
 ftpReply=ftpManager.get(QNetworkRequest(url));
// ftpManager2->get(QNetworkRequest(url))

 connect(ftpReply,SIGNAL(downloadProgress(qint64,qint64)),SLOT(loadProgress(qint64 ,qint64)));
 connect(&ftpManager,SIGNAL(finished(QNetworkReply*)),SLOT(manageDownResult(QNetworkReply*)));//接收返回值
}

void MainWindow::ftpUpload(QByteArray data){
 ftpManager.disconnect(SIGNAL(finished(QNetworkReply*)));
 QUrl url(ui->server->text());
 url.setPort(21);
 url.setUserName(ui->username->text());
 url.setPassword(ui->password->text());
// qDebug() << data;
 ftpReply=ftpManager.put(QNetworkRequest(url),data);

 connect(&ftpManager,SIGNAL(finished(QNetworkReply*)),SLOT(manageUploadResult(QNetworkReply*)));//接收返回值
 connect(ftpReply, SIGNAL(uploadProgress(qint64,qint64)), SLOT(loadProgress(qint64 ,qint64)));
}

void MainWindow::manageDownResult(QNetworkReply *reply)
{
    //基本和managerPut类似
    qDebug() << reply->error();
    QByteArray data;
    switch(reply->error()){
    case QNetworkReply::NoError:
        data=reply->readAll();//从url中读取文件内容，输出到data中（也可以再将数据写入到文件中，为了方便，这里就权且打印一下吧）
        ftpWrite(data);
        QMessageBox::information(this,"Put information","Download Success!");
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

void MainWindow::manageUploadResult(QNetworkReply * reply)
{
    qDebug()<<reply->error();//输出调试信息
    switch(reply->error()){//判断连接后的状态
    case QNetworkReply::NoError:
        ftpManager.disconnect();
        QMessageBox::information(this,"Put information","Upload Success!");
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
//    int position= (ui->server->text()).lastIndexOf("/");
//    QString fileName= (ui->server->text()).mid(position+1);

    QFile ftpFile(fileUrl.toLocalFile());
    ftpFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    ftpFile.write(data);
    ftpFile.close();
}


void MainWindow::on_push_clicked()
{
    if(ui->server->text().isEmpty())
    {
        QMessageBox::warning(this,"Error","Please fill in the information");
    }else {
        fileUrl = QFileDialog::getOpenFileUrl(this,tr("Upload File"),QUrl(""),tr("File(*.*)")); //选择路径
        initProgressBar();
        ftpUpload(ftpRead());
    }
}

QByteArray MainWindow::ftpRead()
{
//    QUrl fileUrl = QFileDialog::getOpenFileUrl(this,tr("Upload File"),QUrl(""),tr("File(*.*)")); //选择路径
    QFile ftpFile(fileUrl.toLocalFile());
    if(!ftpFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open failed." << endl;
        EXIT_FAILURE;
    }
    QByteArray data = ftpFile.readAll();
    ftpFile.close();
    return data;
}

void MainWindow::loadProgress(qint64 bytesSent, qint64 bytesTotal)    //更新进度条
{
       qDebug() << "loaded" << bytesSent << "of" << bytesTotal;
       progressBar->setMaximum(bytesTotal); //最大值
       progressBar->setValue(bytesSent);  //当前值
       if(bytesSent==bytesTotal){
           progressBar->close();
       }
}

void MainWindow::initProgressBar()
{
    progressBar = new QProgressBar ();
    progressBar->setMaximum(100);
    progressBar->setValue(0);
    progressBar->show();
}

