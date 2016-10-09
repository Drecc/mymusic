#ifndef MUSICTHREAD_H
#define MUSICTHREAD_H

#include <QObject>
#include <QThread>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QDomDocument>
#include <QFile>
#include "DownloadWidget.h"
#include <QDebug>
#include <QMessageBox>

class MusicThread : public QThread
{
    Q_OBJECT
public:
    MusicThread(QString musicName, QString musicArtist, QString musicFilePath, DownloadWidget *downWidget);
    ~MusicThread();

signals:
    void downloadMusic(bool, QString);
protected:
    void run();
public slots:
    void getMusicXML(QNetworkReply *reply);
    void replyFinished();
    void getMusic();
private:
    void startFunc();
    void getMusicFromURL(QUrl musicUrl, QString musicFilePath);

    QNetworkAccessManager *manager;
    QNetworkAccessManager *musicManager;
    QNetworkReply *musicReply;
    QFile musicFile;
    QUrl musicUrl;
    QString musicName;
    QString musicArtist;
    QString musicFilePath;

    DownloadWidget *downWidget;
};

#endif // MUSICTHREAD_H
