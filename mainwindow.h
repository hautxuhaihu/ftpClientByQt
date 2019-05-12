#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QMessageBox>
#include <QtDebug>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QString>
#include <QFileDialog>
#include <QScreen>
#include <QProgressBar>
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ftpDown();//从服务器下载文件功能
    void ftpUpload(QByteArray data);//上传文件到服务器
    void ftpWrite(QByteArray data);//将缓冲器中的内容写入文件，并保存
    QByteArray ftpRead();//将计算机中指定的文件的内容读入缓存
    void initProgressBar();//初始化一个进度条

private slots:
    void on_get_clicked();//当点击下载问价时触发函数
    void manageDownResult(QNetworkReply *reply);//当文件下载完毕触发函数
    void manageUploadResult(QNetworkReply *reply);//当文件上传成功触发函数
    void on_push_clicked();//当点击上传文件时触发
    void loadProgress(qint64 bytesSent, qint64 bytesTotal);//实时更新进度条进度

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager ftpManager;
    QNetworkReply *ftpReply;
    QProgressBar *progressBar;
    QUrl fileUrl;
//    QNetworkAccessManager *ftpManager2 = new QNetworkAccessManager ();
};

#endif // MAINWINDOW_H
