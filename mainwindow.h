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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ftpGet();
    void ftpWrite(QByteArray data);

private slots:
    void test(const QString &s);
    void on_get_clicked();
    void manageGetResult(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager ftpManager;
//    QNetworkAccessManager *ftpManager2 = new QNetworkAccessManager ();
//    QNetworkReply* ftpReply;
};

#endif // MAINWINDOW_H
