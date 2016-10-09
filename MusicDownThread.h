#ifndef MUSICDOWNTHREAD_H
#define MUSICDOWNTHREAD_H

#include <QObject>
#include <QThread>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QFile>
#include <QDebug>
#include <QMessageBox>

class MusicDownThread : public QThread
{
    Q_OBJECT
public:
    MusicDownThread(QString urlString, QString musicFilePath);
    ~MusicDownThread();
protected:
    void run();
signals:
    void downloadMusic(bool, QString);

public slots:
    void getMusic();
    void finish();
private:
    QFile musicFile;
    QString urlString;
    QString musicFilePath;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QUrl url;
};

#endif // MUSICDOWNTHREAD_H
