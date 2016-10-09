#ifndef LISTTHREAD_H
#define LISTTHREAD_H

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
#include "ExtensionListWidget.h"

class ListThread : public QThread
{
    Q_OBJECT
public:
    explicit ListThread(QString id,QHash<int,QString> &musicList, bool is_album, ExtensionListWidget *parent = 0);
    ~ListThread();

signals:

protected:
    void run();

public slots:
    void finished(QNetworkReply *reply);

private:
    ExtensionListWidget *parent;
    QHash<int,QString> &musicList;
    QString id;
    QNetworkAccessManager *manager;
    QString url;
    bool is_album;
};

#endif // LISTTHREAD_H
