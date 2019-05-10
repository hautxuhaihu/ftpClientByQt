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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void test(const QString &s);
    void on_get_clicked();
    void manageGetResult(QNetworkReply *reply);
    void slotGet();


private:
    Ui::MainWindow *ui;
    QNetworkAccessManager ftpManager;
//    QNetworkAccessManager *ftpManager2 = new QNetworkAccessManager ();
//    QNetworkReply* ftpReply;
};

#endif // MAINWINDOW_H
