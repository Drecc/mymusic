#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrl>
#include <QString>
#include <QHash>
#include <QThread>
#include <QDebug>
#include "ExtensionWidget.h"

class ExtensionWidget;
class SearchThread : public QThread
{
    Q_OBJECT
    enum type{DATA,URL,OTHER};      //处理应答的类型
public:
    SearchThread(QString keyWord, QHash<int,QString> &musicList, QHash<int,QString> &picList,
                 QHash<int, int> &songsId, ExtensionWidget *parent);
    ~SearchThread();

signals:
protected:
    void run();

public slots:
    void finished(QNetworkReply*reply);
private:
    void startFunc();
    void dealSearch(QNetworkReply *reply);
    void getSongsUrl();
    void dealSongId(QNetworkReply *reply);
    QString keyWord;
    ExtensionWidget *parent;
    type pe;
    QNetworkAccessManager *manager;

    QHash<int, QString> &picList;
    QHash<int, QString> &musicList;
    QHash<int, int> &songsId;
};

#endif // SEARCHTHREAD_H
