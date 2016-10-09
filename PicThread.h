#ifndef PICTHREAD_H
#define PICTHREAD_H

#include <QObject>
#include <QThread>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include "MiniWidget.h"
#include <QDebug>
#include <QMessageBox>

class PicThread : public QThread
{
    Q_OBJECT
    enum type{DATA,URL,DOWN,OTHER};      //处理应答的类型
public:
    PicThread(QString musicName, QString musicArtist, QString picFilePath);
    ~PicThread();

signals:
    void downloadPicOk(bool, QString);
protected:
    void run();
public slots:
    void finished(QNetworkReply *reply);

private:
    void startFunc();
    void dealSearch(QNetworkReply *reply);
    void getSongUrl();
    void dealSongId(QNetworkReply *reply);
    void getPic(QNetworkReply *reply);
    QFile picFile;
    QString musicArtist;
    QString picFilePath;
    QString picUrl;
    QString musicName;
    QPixmap *currentPicture;
    int songId;
    type pe;
    QNetworkAccessManager *manager;
};

#endif // PICTHREAD_H
