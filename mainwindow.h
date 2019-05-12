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
    void ftpDown();
    void ftpUpload(QByteArray data);
    void ftpWrite(QByteArray data);
    QByteArray ftpRead();
    void initProgressBar();

private slots:
    void on_get_clicked();
    void manageDownResult(QNetworkReply *reply);
    void manageUploadResult(QNetworkReply *reply);
    void on_push_clicked();
    void loadProgress(qint64 bytesSent, qint64 bytesTotal);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager ftpManager;
    QNetworkReply *ftpReply;
    QProgressBar *progressBar;
    QUrl fileUrl;
//    QNetworkAccessManager *ftpManager2 = new QNetworkAccessManager ();
};

#endif // MAINWINDOW_H
